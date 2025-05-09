#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <unistd.h>
#include <string.h>
#include "strace.h"
#include "syscalls.h"

int parent_process(pid_t child);

int main(int argc, char **argv, char **env)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s command [args...]\n", argv[0]);
        return (1);
    }

    pid_t child = fork();
    if (child == -1)
    {
        perror("fork");
        return (1);
    }

    if (child == 0)
    {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execve(argv[1], &argv[1], env);
        perror("execve");
        exit(EXIT_FAILURE);
    }
    else
    {
        return parent_process(child);
    }
}

int parent_process(pid_t child)
{
    int status, entry = 0;
    struct user_regs_struct regs;

    while (1)
    {
        if (waitpid(child, &status, 0) == -1)
        {
            perror("waitpid");
            return (1);
        }

        if (WIFEXITED(status))
            break;

        if (ptrace(PTRACE_GETREGS, child, NULL, &regs) == -1)
        {
            perror("ptrace GETREGS");
            return (1);
        }

        entry = !entry;
        if (entry)
        {
            if (regs.orig_rax < SYSCALL_MAX)
                fprintf(stderr, "%s", syscalls_64_g[regs.orig_rax].name);
            else
                fprintf(stderr, "unknown");

            if (regs.orig_rax != 1)
                fprintf(stderr, "\n");
        }

        if (ptrace(PTRACE_SYSCALL, child, NULL, NULL) == -1)
        {
            perror("ptrace SYSCALL");
            return (1);
        }
        fflush(NULL);
    }

    return (0);
}

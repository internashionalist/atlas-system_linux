#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <unistd.h>
#include <string.h>
#include <sys/syscall.h>
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
    int status;
    struct user_regs_struct regs;

    if (waitpid(child, &status, 0) == -1) /* wait for initial syscall entry */
    {
        perror("waitpid");
        return (1);
    }

    if (ptrace(PTRACE_GETREGS, child, NULL, &regs) == -1)
    {
        perror("ptrace GETREGS");
        return (1);
    }

    if (regs.orig_rax < SYSCALL_MAX) /* execve printing */
        fprintf(stderr, "%s\n", syscalls_64_g[regs.orig_rax].name);
    else
        fprintf(stderr, "unknown\n");

    if (ptrace(PTRACE_SYSCALL, child, NULL, NULL) == -1)
    {
        perror("ptrace SYSCALL");
        return (1);
    }

    int entry = 0;

    while (1)
    {
        if (waitpid(child, &status, 0) == -1) /* wait for syscall */
        {
            perror("waitpid");
            return (1);
        }

        if (WIFEXITED(status)) /* child exited */
            break;

        if (ptrace(PTRACE_GETREGS, child, NULL, &regs) == -1) /* get registers */
        {
            perror("ptrace GETREGS");
            return (1);
        }

        if (!entry) /* on syscall exit */
        {
            if (regs.orig_rax < SYSCALL_MAX)
            {
                if (regs.orig_rax == SYS_write)
                    fprintf(stderr, "write");
                else
                    fprintf(stderr, "%s\n", syscalls_64_g[regs.orig_rax].name);
            }
            else
            {
                fprintf(stderr, "unknown\n");
            }
            if (regs.orig_rax == SYS_write)
                fflush(stderr);
        }

        if (ptrace(PTRACE_SYSCALL, child, NULL, NULL) == -1) /* continue tracing */
        {
            perror("ptrace SYSCALL");
            return (1);
        }
        entry = !entry; /* toggle entry flag */
        fflush(NULL);
    }
    fprintf(stderr, "\n");

    return (0);
}

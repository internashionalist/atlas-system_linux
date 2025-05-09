#include <string.h>
#include "strace.h"


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
        perror("you forked up");
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
        int status;
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

#if defined(__x86_64__)
            unsigned long syscall_num = regs.orig_rax;
#elif defined(__i386__)
            unsigned long syscall_num = regs.orig_eax;
#else
#error "Unsupported architecture"
#endif

            const char *syscall_name = (
				syscall_num < SYSCALL_MAX) ? syscalls_64_g[
				syscall_num].name : "unknown";
            printf("%s\n", syscall_name);

            if (ptrace(PTRACE_SYSCALL, child, NULL, NULL) == -1)
            {
                perror("ptrace SYSCALL");
                return (1);
            }
        }
    }

    return (0);
}

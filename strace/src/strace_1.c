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
        fflush(stdout);
        fflush(NULL);
        execve(argv[1], &argv[1], env);
        perror("execve");
        exit(EXIT_FAILURE);
    }
    else
    {
        int status;
        struct user_regs_struct regs;
        int in_syscall = 0;
        const char *syscall_name = NULL;

        while (1)
        {
            if (waitpid(child, &status, 0) == -1)
            {
                perror("waitpid");
                return (1);
            }

            if (WIFEXITED(status)) {
                printf("exit_group\n");
                break;
            }

            if (ptrace(PTRACE_GETREGS, child, NULL, &regs) == -1)
            {
                perror("ptrace GETREGS");
                return (1);
            }

            if (!in_syscall)
            {
#if defined(__x86_64__)
                unsigned long syscall_num = regs.orig_rax;
#elif defined(__i386__)
                unsigned long syscall_num = regs.orig_eax;
#else
#error "Unsupported architecture"
#endif

                syscall_name = (
                    syscall_num < SYSCALL_MAX && syscalls_64_g[syscall_num].name) ?
                    syscalls_64_g[syscall_num].name : "unknown";
                fflush(stdout);
                if (strcmp(syscall_name, "write") == 0)
                    printf("write");
                else if (strcmp(syscall_name, "exit_group") == 0)
                    ;  // Defer to WIFEXITED handling for final print
                else
                    printf("%s\n", syscall_name);
                fflush(stderr);
            }

            if (in_syscall && strcmp(syscall_name, "write") == 0)
            {
                char output[4096];
                ssize_t len = read(1, output, sizeof(output) - 1);
                if (len > 0)
                {
                    output[len] = '\0';
                    printf("write%s\n", output);
                }
            }

            in_syscall = 1 - in_syscall;

            if (ptrace(PTRACE_SYSCALL, child, NULL, NULL) == -1)
            {
                perror("ptrace SYSCALL");
                return (1);
            }
        }
    }

    return (0);
}

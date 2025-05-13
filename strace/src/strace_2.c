

#include "strace.h"
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

extern char **environ;

/**
 * get_syscall_name - returns the name that corresponds to a syscall number
 * @nr: syscall number
 *
 * Return: pointer to the string containing the name, or "unknown"
 */
static const char *get_syscall_name(size_t nr)
{
	size_t i;

	for (i = 0; i < SYSCALL_MAX; ++i)
	{
		if (syscalls_64_g[i].nr == nr)
			return (syscalls_64_g[i].name); /* if found */
	}
	return ("unknown");
}

/**
 * parent_process - trace a child process and print each intercepted syscall
 * @child: PID of the child process
 *
 * Return: always 0
 */
int parent_process(pid_t child)
{
	int status;
	struct user_regs_struct regs;
	int in_syscall = 0;
	unsigned long syscall_nr = 0;

	/* wait for the child’s first stop */
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		return (0);
	ptrace(PTRACE_SETOPTIONS, child, 0, PTRACE_O_TRACESYSGOOD);

	while (1)
	{
		ptrace(PTRACE_SYSCALL, child, 0, 0);	/* wait for syscall */
		waitpid(child, &status, 0);				/* wait for syscall stop */

		if (WIFEXITED(status))
			break;

		if (!WIFSTOPPED(status) || (WSTOPSIG(status) & 0x80) == 0)
			continue;

		ptrace(PTRACE_GETREGS, child, 0, &regs);	/* get registers */

		if (!in_syscall)							/* syscall entry */
		{
			syscall_nr = regs.orig_rax;

			if (syscall_nr == 60 || syscall_nr == 231) /* exit syscall */
			{
				printf("%s = ?\n", get_syscall_name(syscall_nr));
				fflush(stdout);
				in_syscall = 0;
			}
			else
			{
				in_syscall = 1;						/* expect matching exit */
			}
		}
		else										/* syscall exit */
		{
			{
				const char *name = get_syscall_name(syscall_nr);
				long long sret = (long long)regs.rax; /* syscall return value */
				unsigned long long uret = (unsigned long long)regs.rax;

				if (sret == 0)						/* syscall failed */
					printf("%s = 0\n", name);
				else
					printf("%s = 0x%llx\n", name, uret);
			}
			fflush(stdout);
			in_syscall = 0;
		}
	}
	return (0);
}

/**
 * main - entry point. fork, trace the child, and exec the given command
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char *argv[])
{
	pid_t child;

	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s command [args...]\n", argv[0]);
		return (1);
	}

	child = fork();
	if (child == -1)
	{
		perror("fork");
		return (1);
	}

	if (child == 0)
	{
		if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1)
		{
			perror("ptrace");
			exit(EXIT_FAILURE);
		}
		/* stop until the parent is ready */
		raise(SIGSTOP);

		/* execute the requested command */
		execve(argv[1], &argv[1], environ);

		/* ff execve returns, it failed */
		fprintf(stderr, "execve: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	return (parent_process(child));
}

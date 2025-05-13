#include "strace.h"
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

extern char **environ;

/**
 * get_syscall_name - return the name that corresponds to a syscall number
 * @nr: syscall number
 *
 * Return: pointer to the string containing the name, or "unknown"
 */
static const char *get_syscall_name(size_t nr)
{
	if (nr < SYSCALL_MAX)
		return (syscalls_64_g[nr].name);
	return ("unknown");
}

/**
 * parent_process - trace hild process and print each intercepted syscall
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
	int seen_execve = 0;

	/* wait for the child’s first stop */
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		return (0);
	ptrace(PTRACE_SETOPTIONS, child, 0, PTRACE_O_TRACESYSGOOD);

	while (1)
	{
		ptrace(PTRACE_SYSCALL, child, 0, 0);
		waitpid(child, &status, 0);

		if (WIFEXITED(status))
			break;

		/* only handle real syscall stops */
		if (!WIFSTOPPED(status) || (WSTOPSIG(status) & 0x80) == 0)
			continue;

		/* get register state */
		ptrace(PTRACE_GETREGS, child, 0, &regs);

		if (!in_syscall) /* syscall entry */
		{
			syscall_nr = regs.orig_rax;

			if (!seen_execve && syscall_nr != 59)
			{
				in_syscall = 1;  /* balance the exit half */
				continue;
			}

			/* exit / exit_group */
			if (syscall_nr == 60 || syscall_nr == 231)
			{
				printf("%s = ?\n", get_syscall_name(syscall_nr));
				fflush(stdout);
				in_syscall = 0;
			}
			else
			{
				in_syscall = 1; /* expect matching exit */
			}
		}
		else /* syscall exit */
		{
			if (seen_execve || syscall_nr == 59)
			{
				const char *name = get_syscall_name(syscall_nr);
				long long sret = (long long)regs.rax;
				unsigned long long uret = (unsigned long long)regs.rax;

				if (sret == 0)
					printf("%s = 0\n", name);
				else
					printf("%s = 0x%llx\n", name, uret);
				if (syscall_nr == 59)
					seen_execve = 1;
			}
			fflush(stdout);
			in_syscall = 0;
		}
	}
	return (0);
}

/**
 * main - entry point. Fork, trace the child, and exec the given command
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
		/* prevent traced program's own output from mixing with trace */
		int devnull_fd = open("/dev/null", O_WRONLY);
		if (devnull_fd != -1)
			dup2(devnull_fd, STDOUT_FILENO);

		/* execute the requested command */
		execve(argv[1], &argv[1], environ);

		/* iff execve returns, it failed */
		fprintf(stderr, "execve: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	return (parent_process(child));
}

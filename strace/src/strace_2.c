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

/**
 * main -	entry point to function
 * @argc:	number of arguments
 * @argv:	argument vector
 *
 * Return:	0 on success, 1 on failure
 */

int main(int argc, char **argv, char **env)
{
	if (argc < 2)					/* check for args */
	{
		perror("needs more args, yo");
		return (1);
	}

	pid_t child = fork();			/* fork a child process */
	if (child == -1)				/* error check */
	{
		perror("you forked up");
		return (1);
	}

	if (child == 0)					/* child process */
	{
		ptrace(PTRACE_TRACEME, 0, NULL, NULL); /* trace child */
		execve(argv[1], &argv[1], env);
		perror("covfefe");
		exit(EXIT_FAILURE);
	}

	int status, in_syscall = 0;		/* syscall flag */
	struct user_regs_struct regs;	/* register struct */
	unsigned long syscall_num;
	long return_val;

	while (1)
	{
		if (waitpid(child, &status, 0) == -1)
		{
			perror("waitpid");
			return (1);
		}

		if (WIFEXITED(status))
			break;

		if (ptrace(PTRACE_GETREGS, child, NULL, &regs) == -1) /* get registers */
		{
			perror("ptrace GETREGS");
			return (1);
		}

		syscall_num = (unsigned long)regs.orig_rax; /* get syscall number */

		if (in_syscall) 
		{
			return_val = regs.rax;
			fprintf(stderr, " = %#lx\n", return_val);
		}
		else						/* not in syscall */
		{
			if (syscall_num < SYSCALL_MAX)
				fprintf(stderr, "%s", syscalls_64_g[syscall_num].name);
			else
				fprintf(stderr, "unknown");
			fflush(stderr);
		}

		if (ptrace(PTRACE_SYSCALL, child, NULL, NULL) == -1)
		{
			perror("ptrace SYSCALL");
			return (1);
		}

		in_syscall = !in_syscall;
	}

	fprintf(stderr, "exit_group = ?\n"); /* print exit_group syscall */
	return (0);
}

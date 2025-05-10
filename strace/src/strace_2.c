#include <errno.h>
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

#define MAX_ADDRESSES 256

/**
 * write_output - safely prints string from traced memory
 * @child: PID of the child process
 * @addr: address in memory to read from
 * @len: number of bytes to read
 */
void write_output(pid_t child, unsigned long addr, size_t len)
{
	unsigned long word;
	size_t bytes_read = 0;

	while (bytes_read < len)
	{
		word = ptrace(PTRACE_PEEKDATA, child, addr + bytes_read, NULL);
		if ((long)word == -1 && errno != 0)
			break;

		for (size_t i = 0; i < sizeof(word) && bytes_read < len; i++, bytes_read++)
		{
			char c = (word >> (i * 8)) & 0xff;
			fprintf(stdout, "%c", c);
		}
	}
}


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

		in_syscall = !in_syscall;

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
			return_val = (long)regs.rax;
			const char *name = (syscall_num < SYSCALL_MAX) ? syscalls_64_g[
				syscall_num].name : "unknown";

			if (strcmp(name, "write") == 0)
			{
				printf("write");
				write_output(child, regs.rsi, (size_t)regs.rdx);
			}
			else
			{
				printf("%s", name);
			}

			if (return_val == -1 && errno != 0)
				printf(" = -1\n");
			else if (return_val >= 0 && return_val < 0x1000)
				printf(" = ADDR%lu\n", (unsigned long)return_val);
			else
				printf(" = %ld\n", return_val);
		}

		if (ptrace(PTRACE_SYSCALL, child, NULL, NULL) == -1)
		{
			perror("ptrace SYSCALL");
			return (1);
		}
	}

	printf("exit_group = ?\n"); /* print exit_group syscall */
	return (0);
}

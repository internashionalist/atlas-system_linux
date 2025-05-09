#include <sys/types.h>
#include <sys/ptrace.h> /* PTRACE_GETREGSET */
#include <sys/wait.h>
#include <sys/user.h> /* struct user_regs_struct */
#include <sys/uio.h> /* struct iovec */
#include <linux/unistd.h> /* syscall numbers */
#include <linux/ptrace.h>  // For NT_PRSTATUS and PTRACE_GETREGSET
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <elf.h>
#include "strace.h"

/**
 * parent_proc -	handles parent process
 * @child:			the child PID
 *
 * 
 * Return:			0 on success, 1 on error
 */
int parent_proc(pid_t child)
{
	int status, entry = 0; /* syscall entry number */
	struct user_regs_struct regs; /* struct to hold registers */

	while (1)
	{
		if (waitpid(child, &status, 0) == -1) /* dead child */
			perror("waitpid");

		if (WIFEXITED(status)) /* child exit */
			break;

		struct iovec iov =
		{
			.iov_base = &regs, /* pointer to the struct */
			.iov_len = sizeof(regs) /* struct size */
		};
		/* get registers */
		ptrace(PTRACE_GETREGSET, child, (void*)NT_PRSTATUS, &iov);

		if (entry == 0 || entry % 2 != 0) /* if valid syscall */
			fprintf(stderr, "%llu\n", regs.orig_rax);

		if (ptrace(PTRACE_SYSCALL, child, NULL, NULL) == -1)
			return (1);

		entry++;
		fflush(NULL);
	}
	return (0);
}

/**
 * main -	entry point for the strace program
 * @argc:	number of arguments
 * @argv:	argument vector
 * @env:	environment variables
 *
 * Return:	0 on success, 1 on error
 */
int main(int argc, char **argv, char **env)
{
	if (argc < 2) /* arg check */
	{
		perror("construct additional pylons!");
		return (1);
	}

	pid_t child = fork(); /* fork child */
	if (child == 0)
	{
		ptrace(PTRACE_TRACEME, 0, NULL, NULL); /* trace child */
		execve(argv[1], &argv[1], env); /* execute child */
	else
	{
		parent_proc(child); /* parent process */
	}
	return (0);
}

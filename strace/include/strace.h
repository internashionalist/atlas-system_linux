#ifndef STRACE_H
#define STRACE_H

#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "syscalls.h"

int parent_proc(pid_t child);

#endif

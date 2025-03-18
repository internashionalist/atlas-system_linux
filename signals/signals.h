#ifndef _SIGNALS_H_
#define _SIGNALS_H_

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * struct sigaction -   structure for signal handling
 * @sa_handler:         pointer to the signal handling function
 * @sa_flags:           flags that modify the behavior of the signal
 * @sa_mask:            set of signals to be blocked during execution
 *                      of the handler
 *
 * Description: used by the sigaction system call to specify how a signal
 *              should be handled.
 */
typedef struct sigaction sigaction_t;

int handle_signal(void);
void (*current_handler_signal(void))(int);
int handle_sigaction(void);
void (*current_handler_sigaction(void))(int);
int trace_signal_sender(void);
int pid_exist(pid_t pid);

#endif

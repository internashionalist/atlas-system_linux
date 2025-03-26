# Signals: Inter-Office Memos for Programs

![signal](https://github.com/internashionalist/atlas-system_linux/blob/main/signals/signal.jpg)

	Your program is working away at its desk, when there's a ding and a little window in the corner of
	the screen. Signals are notifications sent to your program to alert it that something needs its
	attention - whether it’s an error, a user command, or a message from another process. The operating
	system or another process decides it’s time to break into your program’s routine. 

	For example, if you press Control-C in a terminal, your program receives a SIGINT signal. This
	signal might be delivered by the system (like when your program makes a mistake such as trying to
	access invalid memory) or by another process that needs to communicate with your application.

	By default, signals come with preset behaviors. Many signals are designed to terminate the program
	immediately. For instance, if your program receives a SIGTERM (termination) signal and hasn’t set up
	any special instructions, it will simply shut down. In other cases, like with SIGSEGV (segmentation
	fault), the program will not only stop but might also generate a core dump—a snapshot of the
	program’s state useful for debugging.

	However, your program can choose to handle these signals in a custom way. Suppose you set up a
	handler for SIGINT that prints a friendly message instead of closing your program. In that case,
	when you press Control-C, the handler takes over. The process might log the event, clean up
	resources, or even ignore the signal entirely. The difference is significant: without a custom
	handler, the signal’s default action (like termination) takes place immediately.

	Here’s a simple C example that shows the difference:
```
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handle_sigint(int signum)
{
	printf("Caught SIGINT (%d)!\n", signum);
}

int main(void)
{
	signal(SIGINT, handle_sigint);
	printf("Process PID: %d\n", getpid());
	while (1)
	{
		sleep(1);
	}
	return EXIT_SUCCESS;
}
```

	In this snippet, pressing Control-C sends a SIGINT. Instead of terminating, the program calls
	handle_sigint, which prints a message. This gives your program a chance to handle the situation more
	gracefully.

	In summary, signals are a vital tool that allows processes to communicate asynchronously. They
	ensure that your program can respond to unexpected events—whether those events require an immediate
	shutdown or just a gentle nudge to check something important. By setting up your own signal
	handlers, you gain control over how your program behaves when these interruptions occur, making your
	software more resilient and adaptable in a busy computing environment.

# Multithreading
### Concepts
For this project, we expect you to look at this concept:
- [EYNTK - Multithreading](https://intranet.atlasschool.com/concepts/941)
### Resources
#### Read or Watch:
- [pthread.h](https://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread.h.html)
- [Concurrency vs. Parallelism](https://howtodoinjava.com/java/multi-threading/concurrency-vs-parallelism/)
### Learning Objectives
At the end of this project, you are expected to be able to [explain to anyone](https://fs.blog/feynman-learning-technique/), without the help of Google:
- What is a thread
- What are the differences between a thread and a process
- What is the difference between Concurrency and Parallelism
- How to create a thread
- How to properly exit a thread
- How to handle mutual execution
- What is a deadlock
- What is a race condition
### Requirements
#### General
- Allowed editors: `vi`, `vim`, `emacs`
- All your files will be compiled on Ubuntu 14.04 LTS
- Your C programs and functions will be compiled with `gcc 4.8.4` using the flags `-Wall` `-Werror` `-Wextra` and `-pedantic`
- All your files should end with a new line
- A `README.md` file, at the root of the folder of the project, is mandatory
- Your code should use the `Betty` style. It will be checked using [betty-style.pl](https://github.com/hs-hq/Betty/blob/master/betty-style.pl) and [betty-doc.pl](https://github.com/hs-hq/Betty/blob/master/betty-doc.pl)
- You are not allowed to have more than 5 functions per file
- The prototypes of all your functions should be included in your header file called `multithreading.h`
- Don’t forget to push your header files
- All your header files should be include guarded
- You are allowed to use `global` variables
- You are allowed to use `static` functions and variables
#### Betty Compliance
- All the C source files in your directory and subdirectories must be [Betty-compliant](https://github.com/hs-hq/betty)
### Allowed Functions and System Calls
- Unless specified otherwise, you are allowed to use the C standard library
### Data structures
Here are the data structures used throughout this project, make sure to include them in your header file `multithreading.h`.
```
#include <stddef.h>
#include <stdint.h>

/**
 * struct pixel_s - RGB pixel
 *
 * @r: Red component
 * @g: Green component
 * @b: Blue component
 */
typedef struct pixel_s
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} pixel_t;

/**
 * struct img_s - Image
 *
 * @w:      Image width
 * @h:      Image height
 * @pixels: Array of pixels
 */
typedef struct img_s
{
    size_t w;
    size_t h;
    pixel_t *pixels;
} img_t;

/**
 * struct kernel_s - Convolution kernel
 *
 * @size:   Size of the matrix (both width and height)
 * @matrix: Kernel matrix
 */
typedef struct kernel_s
{
    size_t size;
    float **matrix;
} kernel_t;

/**
 * struct blur_portion_s - Information needed to blur a portion of an image
 *
 * @img:      Source image
 * @img_blur: Destination image
 * @x:        X position of the portion in the image
 * @y:        Y position of the portion in the image
 * @w:        Width of the portion
 * @h:        Height of the portion
 * @kernel:   Convolution kernel to use
 */
typedef struct blur_portion_s
{
    img_t const *img;
    img_t *img_blur;
    size_t x;
    size_t y;
    size_t w;
    size_t h;
    kernel_t const *kernel;
} blur_portion_t;
```
### Manual QA Review
#### It is your responsibility to request a review for your work on the Task #3 from a peer before the project’s deadline. If no peers have been reviewed, you should request a review from a TA or staff member.
#
#### 0. Thread entry point
Write a function that will serve as the entry point to a new thread.
- Prototype: `void *thread_entry(void *arg);`, where:
    - `arg` holds the address of a string that must be printed and followed by a new line.
- Make sure to respect the order in which strings are printed out in the following example:
```
alex@~/multithreading$ cat 0-main.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "multithreading.h"

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS
 */
int main(void)
{
    pthread_t tid;

    pthread_create(&tid, NULL, &thread_entry, "Holberton School");

    sleep(1);
    printf("Created thread ID -> %lu\n", tid);

    thread_entry("C is fun");
    printf("Should not be printed\n");
    return (EXIT_SUCCESS);
}
alex@~/multithreading$ gcc -Wall -Wextra -Werror -pedantic -g3 0-main.c 0-thread_entry.c -o 0-thread_entry -pthread
alex@~/multithreading$ ./0-thread_entry
Holberton School
Created thread ID -> 139851772159744
C is fun
alex@~/multithreading$
```
#### Repo:
- GitHub repository: `atlas-system_linux`
- Directory: `multithreading`
- File: `0-thread_entry.c`
#
#### 1. Thread Logger
Write a function that uses the `printf` family to print out a given formatted string.
- Prototype: `int tprintf(char const *format, ...);`
- The output must be preceded by the calling thread ID, as the following output shows.
```
alex@~/multithreading$ cat 1-main.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "multithreading.h"

/**
 * _thread_entry - Thread entry point. Prints out a string
 *
 * @arg: Unused
 *
 * Return: NULL
 */
void *_thread_entry(__attribute__((unused))void *arg)
{
    tprintf("Hello from thread\n");
    return (NULL);
}

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS
 */
int main(void)
{
    pthread_t tid;

    pthread_create(&tid, NULL, &_thread_entry, NULL);
    pthread_join(tid, NULL);

    tprintf("Hello from main thread\n");

    return (EXIT_SUCCESS);
}
alex@~/multithreading$ gcc -Wall -Wextra -Werror -pedantic -g3 1-main.c 1-tprintf.c -o 1-tprintf -pthread
alex@~/multithreading$ ./1-tprintf
[140095003338496] Hello from thread
[140095011714880] Hello from main thread
alex@~/multithreading$ ./1-tprintf
[139794647717632] Hello from thread
[139794656094016] Hello from main thread
alex@~/multithreading$
```
#### Repo:
- GitHub repository: `atlas-system_linux`
- Directory: `multithreading`
- File: `1-tprintf.c`
#
#### 4. Thread logger v2
Write a function that uses the printf family to print out a given formatted string.

- This time, you will also have to use a mutex to avoid race conditions. As you know, a mutex needs to be initialized, and destroyed, but we don’t want to have to do that ourselves in our main.c program. Please read about Constructors and Destructors with GCC and it should all make sense :).

- Prototype: int tprintf(char const *format, ...);
- The output must be preceded by the calling thread ID, as the following output shows.
- Tip: You are allowed to use global variables - Don’t forget to run Betty with the option --allow-global-variables
- NOTE: In the following example, we first compile with our first version of tprintf to show the consequence of the race condition.
```
alex@~/multithreading$ cat 20-main.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "multithreading.h"

#define NB_THREADS  10

/**
 * _thread_entry - Thread entry point. Prints out a string
 *
 * @arg: Unused
 *
 * Return: NULL
 */
void *_thread_entry(__attribute__((unused))void *arg)
{
    tprintf("Hello from thread\n");
    return (NULL);
}

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS
 */
int main(void)
{
    pthread_t tid[NB_THREADS];
    int i;

    for (i = 0; i < NB_THREADS; i++)
        pthread_create(&tid[i], NULL, &_thread_entry, NULL);

    tprintf("Hello from main thread\n");

    for (i = 0; i < NB_THREADS; i++)
        pthread_join(tid[i], NULL);

    return (EXIT_SUCCESS);
}
alex@~/multithreading$ gcc -Wall -Wextra -Werror -pedantic -g3 20-main.c 1-tprintf.c -o 20-tprintf -pthread
alex@~/multithreading$ ./20-tprintf
[139996670035712] [139996678428416] [139996686821120] [139996695197504] Hello from thread
[139996644857600] Hello from thread
[139996628072192] Hello from thread
[139996619679488] Hello from thread
Hello from main thread
Hello from thread
Hello from thread
[139996611286784] Hello from thread
[139996661643008] Hello from thread
[139996636464896] Hello from thread
[139996653250304] Hello from thread
alex@~/multithreading$ gcc -Wall -Wextra -Werror -pedantic -g3 20-main.c 20-tprintf.c -o 20-tprintf -pthread
alex@~/multithreading$ ./20-tprintf
[140146877490944] Hello from thread
[140146852312832] Hello from thread
[140146843920128] Hello from thread
[140146860705536] Hello from thread
[140146835527424] Hello from thread
[140146869098240] Hello from thread
[140146818742016] Hello from thread
[140146885867328] Hello from main thread
[140146810349312] Hello from thread
[140146801956608] Hello from thread
[140146827134720] Hello from thread
alex@~/multithreading$
```
#### Repo:
- GitHub repository: atlas-system_linux
- Directory: multithreading
- File: 20-tprintf.c
#
#### 5. Number to prime factors
Write a function that factorizes a number into a list of prime factors.

- Prototype: list_t *prime_factors(char const *s);, where
  - s is the string representation of the number to factorize. This number will be positive and fit into an unsigned long
- Your code will be compiled with the file list.c
  - list.h
  - list.c
- NOTE: This task does not require multithreading, and will not be linked to the pthread library.
```
alex@~/multithreading$ cat 21-main.c
#include <stdlib.h>
#include <stdio.h>
#include "multithreading.h"

/**
 * print_factors - Print a nmber and its prime factorization
 *
 * @s:       Number as string
 * @factors: List of prime factors
 */
static void print_factors(char const *s, list_t const *factors)
{
    node_t const *factor;

    printf("%s =", s);
    for (factor = factors->head; factor; factor = factor->next)
    {
        unsigned long n = *((unsigned long *)factor->content);

        printf("%s %lu", factor->prev ? " *" : "", n);
    }
    printf("\n");
}

/**
 * main - Entry point
 *
 * @ac: Arguments count
 * @av: Arguments vector
 *
 * Return: EXIT_SUCCESS upon success, EXIT_FAILURE otherwise
 */
int main(int ac, char **av)
{
    size_t i;

    if (ac < 2)
    {
        fprintf(stderr, "Usage: %s n\n", av[0]);
        return (EXIT_FAILURE);
    }

    for (i = 1; i < (size_t)ac; i++)
    {
        list_t *factors;

        factors = prime_factors(av[i]);
        print_factors(av[i], factors);
        list_destroy(factors, free);
        free(factors);
    }

    return (EXIT_SUCCESS);
}
alex@~/multithreading$ gcc -Wall -Wextra -Werror -pedantic -g3 21-main.c 21-prime_factors.c list.c -o 21-prime_factors
alex@~/multithreading$ ./21-prime_factors 745 872346 79283472974
745 = 5 * 149
872346 = 2 * 3 * 145391
79283472974 = 2 * 757 * 52366891
alex@~/multithreading$ ./21-prime_factors 1048576
1048576 = 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2
alex@~/multithreading$ ./21-prime_factors 18446744073709551612 18446744073709551609 18446744073709551608
18446744073709551612 = 2 * 2 * 3 * 715827883 * 2147483647
18446744073709551609 = 3 * 3 * 818923289 * 2502845209
18446744073709551608 = 2 * 2 * 2 * 2305843009213693951
alex@~/multithreading$
```
#### Repo:
- GitHub repository: atlas-system_linux
- Directory: multithreading
- File: 21-prime_factors.c
#
#### 6. Number to prime factors v2
The goal of this task is to reproduce the previous task, and to improve it using a thread pool. The tread pool will have for purpose to execute a list of tasks.

For this task, you will have to write 3 functions (all in the same file):

- Create task
  - Prototype: task_t *create_task(task_entry_t entry, void *param);, where
    - entry is a pointer to the entry function of the task,
    - param is the parameter that will later be passed to the entry function
  - This function must return a pointer to the created task structure
- Destroy task
  - Prototype: void destroy_task(task_t *task);, where
    - task is a pointer to the task to destroy
- Execute task list - Thread entry
  - Prototype: void *exec_tasks(list_t const *tasks);, where
    - tasks is a pointer to the list of tasks to be executed
  - This function serves as a thread entry
  - This function can safely return NULL as its return value will not be retrieved
  - This function must go through the list of tasks and execute them, but there’s a challenge:
    - Multiple thread will be going through the list of tasks, and a task must only be executed once
  - You must use tprintf to print when a task is started, and completed

Structures
```
typedef void *(*task_entry_t)(void *);

/**
 * enum task_status_e - Task statuses
 *
 * @PENDING: Task is pending
 * @STARTED: Task has been started
 * @SUCCESS: Task has completed successfully
 * @FAILURE: Task has completed with issues
 */
typedef enum task_status_e
{
    PENDING = 0,
    STARTED,
    SUCCESS,
    FAILURE
} task_status_t;

/**
 * struct task_s - Executable task structure
 *
 * @entry:  Pointer to a function to serve as the task entry
 * @param:  Address to a custom content to be passed to the entry function
 * @status: Task status, default to PENDING
 * @result: Stores the return value of the entry function
 * @lock:   Task mutex
 */
typedef struct task_s
{
    task_entry_t    entry;
    void        *param;
    task_status_t   status;
    void        *result;
    pthread_mutex_t lock;
} task_t;
```

Example
```
alex@~/multithreading$ cat 22-main.c
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "multithreading.h"

#define NB_THREADS  8

/**
 * print_task_result - Print the result of a task
 *
 * @task: Pointer to the task to print the result of
 */
void print_task_result(task_t *task)
{

    list_t *factors = (list_t *)task->result;
    node_t *factor;

    printf("%s =", (char *)task->param);
    for (factor = factors->head; factor; factor = factor->next)
    {
        unsigned long n = *((unsigned long *)factor->content);

        printf("%s %lu", factor->prev ? " *" : "", n);
    }
    printf("\n");
}

/**
 * main - Entry point
 *
 * @ac: Arguments count
 * @av: Arguments vector
 *
 * Return: EXIT_SUCCESS upon success, EXIT_FAILURE otherwise
 */
int main(int ac, char **av)
{
    list_t tasks;
    pthread_t threads[NB_THREADS];
    size_t i;

    if (ac < 2)
    {
        fprintf(stderr, "Usage: %s n\n", av[0]);
        return (EXIT_FAILURE);
    }

    if (!list_init(&tasks))
        return (EXIT_FAILURE);

    for (i = 1; i < (size_t)ac; i++)
        list_add(&tasks,
            create_task((task_entry_t)prime_factors, av[i]));

    printf("Executing %lu tasks on %u threads\n", tasks.size, NB_THREADS);

    for (i = 0; i < NB_THREADS; i++)
        pthread_create(&threads[i], NULL,
            (void *(*) (void *))exec_tasks, &tasks);
    for (i = 0; i < NB_THREADS; i++)
        pthread_join(threads[i], NULL);

    list_each(&tasks, (node_func_t)print_task_result);

    list_destroy(&tasks, (node_func_t)destroy_task);

    return (EXIT_SUCCESS);
}
alex@~/multithreading$ gcc -Wall -Wextra -Werror -pedantic -g3 22-main.c 22-prime_factors.c 21-prime_factors.c list.c 20-tprintf.c -o 22-prime_factors -pthread
alex@~/multithreading$ ./22-prime_factors 234 23456 908345 9803475893 389475 9384 7538 4753876348956746 4985 39485734 9587398 7938475839 324 3453450
Executing 14 tasks on 8 threads
[139770218567424] [00] Started
[139770218567424] [00] Success
[139770218567424] [08] Started
[139770218567424] [08] Success
[139770218567424] [09] Started
[139770218567424] [09] Success
[139770218567424] [10] Started
[139770218567424] [10] Success
[139770218567424] [11] Started
[139770218567424] [11] Success
[139770218567424] [12] Started
[139770218567424] [12] Success
[139770218567424] [13] Started
[139770218567424] [13] Success
[139770159818496] [07] Started
[139770159818496] [07] Success
[139770201782016] [02] Started
[139770201782016] [02] Success
[139770184996608] [04] Started
[139770184996608] [04] Success
[139770168211200] [06] Started
[139770168211200] [06] Success
[139770193389312] [03] Started
[139770193389312] [03] Success
[139770176603904] [05] Started
[139770176603904] [05] Success
[139770210174720] [01] Started
[139770210174720] [01] Success
234 = 2 * 3 * 3 * 13
23456 = 2 * 2 * 2 * 2 * 2 * 733
908345 = 5 * 181669
9803475893 = 1153 * 8502581
389475 = 3 * 3 * 3 * 5 * 5 * 577
9384 = 2 * 2 * 2 * 3 * 17 * 23
7538 = 2 * 3769
4753876348956746 = 2 * 11 * 67 * 89 * 89 * 3373 * 120713
4985 = 5 * 997
39485734 = 2 * 37 * 47 * 11353
9587398 = 2 * 2141 * 2239
7938475839 = 3 * 3 * 7 * 7 * 17 * 53 * 19979
324 = 2 * 2 * 3 * 3 * 3 * 3
3453450 = 2 * 3 * 5 * 5 * 7 * 11 * 13 * 23
alex@~/multithreading$
```
#### Repo:
- GitHub repository: atlas-system_linux
- Directory: multithreading
- File: 22-prime_factors.c
#

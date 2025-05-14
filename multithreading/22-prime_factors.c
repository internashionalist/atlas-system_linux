#include <stdlib.h>
#include <pthread.h>
#include "multithreading.h"
#include "list.h"

/**
 * create_task -	create and initialize a new task structure
 * @entry:			pointer to the entry function to execute
 * @param:			argument to pass to the entry function
 *
 * This function allocates memory for a task structure, initializes it with
 * provided parameters, and sets the status to PENDING. It also initializes
 * the mutex lock for the task.
 *
 * Return:			pointer to the allocated task_t, or NULL on failure
 */
task_t *create_task(task_entry_t entry, void *param)
{
	task_t *t; /* struct to hold task info */

	if (!entry) /* NULL / empty check */
		return (NULL);

	t = malloc(sizeof(*t)); /* allocate memory for task */
	if (!t)
		return (NULL);

	t->entry = entry;
	t->param = param;
	t->status = PENDING;
	t->result = NULL;

	if (mutex_init(&t->lock) != 0) /* init mutex */
	{
		free(t);
		return (NULL);
	}

	return (t); /* return pointer to task */
}

/**
 * destroy_task -	free a task structure and its resources
 * @task:			pointer to task to destroy
 *
 * This function frees the memory for the task struct and destroys its
 * mutex lock.
 *
 * Return:			void
 */
void destroy_task(task_t *task)
{
	if (!task)
		return;

	mutex_destroy(&task->lock);
	free(task);
}

/**
 * claim_task -		attempt to mark a task as STARTED
 * @task:			task to claim
 *
 * Return:			1 if the task was successfully claimed,
 *					0 otherwise (already started or failed)
 */
static int claim_task(task_t *task)
{
	int ret = 0; /* return value */

	if (!task) /* NULL / empty check */
		return (0);

	if (pthread_mutex_trylock(&task->lock) == 0) /* try lock */
	{
		if (task->status == PENDING) /* check status */
		{
			task->status = STARTED; /* mark as started */
			ret = 1;
		}
		pthread_mutex_unlock(&task->lock); /* if pending, unlock */
	}

	return (ret);
}

/**
 * exec_tasks -		thread entry that executes tasks in a shared list
 * @tasks:			pointer to list containing task_t* nodes
 *
 * This function iterates over the list repeatedly, claiming tasks that are
 * PENDING. A claimed task is executed only once, and its result is stored
 * in the task structure. It continues until all tasks are either STARTED or
 * completed.
 *
 * Return: NULL
 */
void *exec_tasks(list_t const *tasks)
{
	int work_done; /* flag to track if work was done, just like it says */

	if (!tasks) /* NULL/empty check */
		return (NULL);

	do {
		work_done = 0;

		for (node_t *node = tasks->head; node; node = node->next)
		{
			task_t *task = node->content;

			if (!task)
				continue;

			/* try claiming task */
			if (!claim_task(task))
				continue; /* if already started by another thread */

			/* if this point reached, there's a task to execute! */
			work_done = 1;

			tprintf("Started\n");

			/* execute the task */
			void *res = task->entry(task->param);

			/* update status & result */
			pthread_mutex_lock(&task->lock);
			task->result = res;
			task->status = SUCCESS;
			pthread_mutex_unlock(&task->lock);

			tprintf("Success\n");
		}
	} while (work_done); /* repeat until no more tasks to execute */

	return (NULL); /* NULL means complete */
}

#include <pthread.h>
#include <stdlib.h>
#include "multithreading.h"
#include "list.h"

/* global task sequence counter for unique indices across all threads */
static pthread_mutex_t idx_mutex = PTHREAD_MUTEX_INITIALIZER;
static size_t g_task_idx;

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

	/* free the list */
	if (task->result)
	{
		list_destroy((list_t *)task->result, free);
		free(task->result);
	}

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
 * process_pending_tasks -	iterate through list and execute new tasks
 * @tasks:					pointer to list containing task_t nodes
 *
 * This function scans the task list, finds a PENDING task, claims it,
 * runs the entry function, stores the result, prints the Started/Success
 * output, and returns.
 *
 * Return: 1 if a task was started, 0 otherwise
 */
static int process_pending_tasks(list_t const *tasks)
{
	int did_work = 0;

	for (node_t *node = tasks->head; node; node = node->next)
	{
		task_t *task = node->content;
		size_t task_id;

		if (!task)
			continue;
		if (!claim_task(task))
			continue;

		/* claim succeeded */
		pthread_mutex_lock(&idx_mutex);
		task_id = g_task_idx++;
		pthread_mutex_unlock(&idx_mutex);

		tprintf("[%02zu] Started\n", task_id);

		void *res = task->entry(task->param);

		pthread_mutex_lock(&task->lock);
		task->result = res;
		task->status = SUCCESS;
		pthread_mutex_unlock(&task->lock);

		tprintf("[%02zu] Success\n", task_id);

		did_work = 1;
	}
	return (did_work);
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
	if (!tasks)
		return (NULL);

	while (process_pending_tasks(tasks))
		; /* repeat until no task is left to run */

	return (NULL);
}

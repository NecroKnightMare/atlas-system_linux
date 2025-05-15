#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "multithreading.h"

/**
 * create_task - Creates a new task structure
 * @entry: Pointer to the function that will be executed by the task
 * @param: Custom parameter that will be passed to the function
 *
 * Return: Pointer to the newly created task, or NULL on failure
 */
task_t *create_task(task_entry_t entry, void *param)
{
    task_t *task;

    /* Allocate memory for the task */
    task = malloc(sizeof(task_t));
    if (!task)
        return (NULL);

    /* Initialize task attributes */
    task->entry = entry;
    task->param = param;
    task->status = PENDING;
    task->result = NULL;

    /* Initialize the task mutex to ensure thread safety */
    pthread_mutex_init(&task->lock, NULL);

    return (task);
}

/**
 * destroy_task - Cleans up memory and destroys a task
 * @task: Pointer to the task to be destroyed
 *
 * Description: Frees any allocated results, destroys mutex,
 * and prevents memory leaks.
 */
void destroy_task(task_t *task)
{
    if (!task)
        return;

    /* Free dynamically allocated task result */
    if (task->result)
        list_destroy((list_t *)task->result, free);

    /* Destroy the mutex to free system resources */
    pthread_mutex_destroy(&task->lock);

    free(task);
}

/**
 * exec_tasks - Executes tasks from the task list in a multithreaded environment
 * @tasks: Pointer to the list of tasks to be executed
 *
 * Return: NULL (intended as a thread entry function)
 *
 * Description:
 * This function ensures that each task is executed only once.
 * It uses mutex locking to prevent race conditions when multiple
 * threads traverse the list.
 */
void *exec_tasks(list_t const *tasks)
{
    node_t *node;
    task_t *task;

    if (!tasks)
        return (NULL);

    /* Iterate over the list of tasks */
    for (node = tasks->head; node; node = node->next)
    {
        task = (task_t *)node->content;

        /* Ensure only one thread executes each task */
        pthread_mutex_lock(&print_lock);
        if (task->status == PENDING)
        {
            task->status = STARTED;
            tprintf("[Task Started]\n");

            /* Execute the task and store the result */
            task->result = task->entry(task->param);
            task->status = (task->result) ? SUCCESS : FAILURE;

            tprintf("[Task Completed]\n");
        }
        pthread_mutex_unlock(print_lock);
    }
    return (NULL);
}

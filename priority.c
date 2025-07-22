#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include <time.h>

struct TASK
{

    int priority;
    int id;
    struct TASK *next;
    struct TASK *previous;
};

typedef struct TASK TASK;

TASK *create_new_task(int priority, int id);
TASK *add_task_before_current(TASK *current_queue, int priority, int id);
TASK *add_task_after_current(TASK *current_queue, int priority, int id);
TASK *delete_first_task(TASK *current_queue);

TASK *enqueue(TASK *queue, int priority, int id);
TASK *dequeue(TASK *queue);
size_t queue_get_size(TASK *queue);
TASK *queue;

int main()
{

    srand(time(NULL));
    int N = 10000;

    for (int i = 0; i < N; i++)
    {
        queue = enqueue(queue, rand() % N, i);
    }
    printf("size=%d\n", N);
    while (queue_get_size(queue) > 0)
    {
        queue = dequeue(queue);
    }
    return 0;
}
/**
 * @brief create new task with no link to other task
 */
TASK *create_new_task(int priority, int id)
{
    TASK *current = (TASK *)malloc(sizeof(TASK));
    current->id = id;
    current->priority = priority;
    current->previous = NULL;
    current->next = NULL;
    return current;
}

/**
 * @brief create task before current task
 */
TASK *add_task_before_current(TASK *current_queue, int priority, int id)
{
    TASK *current = current_queue;
    if (current == NULL)
    {
        current = create_new_task(priority, id);
        return current;
    }
    TASK *new_node = create_new_task(priority, id);
    new_node->next = current;
    if (current->previous == NULL)
    {
        current->previous = new_node;
        return current;
    }
    else
    {
        TASK *temp_pre = current->previous;
        temp_pre->next = new_node;
        new_node->previous = temp_pre;
        current->previous = new_node;
        return current;
    }
}

/**
 * @brief create task after current task
 */
TASK *add_task_after_current(TASK *current_queue, int priority, int id)
{
    TASK *current = current_queue;
    if (current == NULL)
    {
        current = create_new_task(priority, id);
        return current;
    }
    TASK *new_node = create_new_task(priority, id);
    new_node->previous = current;
    if (current->next == NULL)
    {
        current->next = new_node;
        return current;
    }
    else
    {
        TASK *temp_pre = current->next;
        temp_pre->previous = new_node;
        new_node->next = temp_pre;
        current->next = new_node;
        return current;
    }
}

/**
 * @brief create task and stack it to queue following high-order priority and fifo rule
 */
TASK *enqueue(TASK *queue, int priority, int id)
{
    TASK *current = queue;
    if (current == NULL)
    {
        current = create_new_task(priority, id);
        return current;
    }
    TASK *last_current;
    while (current != NULL)
    {
        if (current->priority < priority)
        {
            current = add_task_before_current(current, priority, id);
            while (current->previous != NULL)
            {
                current = current->previous;
            }
            return current;
        }
        else if (current->priority == priority)
        {
            current = add_task_after_current(current, priority, id);
            return queue;
        }
        else if (current->priority > priority)
        {
            last_current = current;
            current = current->next;
        }
    }
    TASK *new_node = create_new_task(priority, id);
    last_current->next = new_node;
    new_node->previous = last_current;
    return queue;
}

/**
 * @brief delete the header task of queue and return the next task
 */
TASK *delete_first_task(TASK *current_queue)
{
    TASK *current = current_queue;
    if (current != NULL)
    {
        TASK *temp = current->next;
        free(current);
        return temp;
    }
    else
    {
        return NULL;
    }
}

/**
 * @brief print the header task and return the next task that will be printed out
 */
TASK *dequeue(TASK *queue)
{
    printf("Running task with priority=%d and id=%d\n", queue->priority, queue->id);
    return delete_first_task(queue);
}

/**
 * @brief get current size of queue
 */
size_t queue_get_size(TASK *queue)
{
    size_t count = 0;
    while (queue != NULL)
    {
        count++;
        queue = queue->next;
    }
    return count;
}
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include <time.h>

typedef struct TASK TASK;

struct TASK
{

    int priority;
    int id;
    struct TASK *next;
    struct TASK *previous;
};

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
    int N = rand() % 100;

    for (int i = 0; i < N; i++)
    {
        queue = enqueue(queue, rand() % 100, i);
    }
    printf("size=%d\n", N);
    while (queue_get_size(queue) > 0)
    {
        queue = dequeue(queue);
    }

    return 0;
}

TASK *create_new_task(int priority, int id)
{
    TASK *current = (TASK *)malloc(sizeof(TASK));
    current->id = id;
    current->priority = priority;
    current->previous = NULL;
    current->next = NULL;
    return current;
}

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
            while (current->previous != NULL)
            {
                current = current->previous;
            }
            return current;
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
    current = last_current;
    while (current->previous != NULL)
    {
        current = current->previous;
    }
    return current;
}

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

TASK *dequeue(TASK *queue)
{
    printf("Running task with priority=%d and id=%d\n", queue->priority, queue->id);
    return delete_first_task(queue);
}

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
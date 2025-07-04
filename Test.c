#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define MAX_MINUTE 1440
#define HOUR_12PM 720

typedef struct
{
    int a;
    int b;
} Job;

void swap_int(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = *a;
}

int check_hours(Job *job, int n)
{
    int check_hours = 0;
    for (int i = 0; i < n; i++)
    {
        if (job[i].a <= HOUR_12PM)
        {
            check_hours++;
        }
    }
    float check30 = (float)check_hours / (float)n;
    if (check30 > (float)(1 / 3))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int check_job_condition(Job *job)
{
    if ((job->a >= job->b))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void generate_jobs(Job *job, int n)
{
    int check_hour = 0;
    float check30 = 0;
    for (int i = 0; i < n; i++)
    {
        while (check_job_condition(job + i))
        {
            job[i].a = rand() % MAX_MINUTE;
            job[i].b = rand() % MAX_MINUTE;
            if (job[i].a > job[i].b)
            {
                swap_int(&job[i].a, &job[i].b);
            }
        }
    }
    while (check_hours(job, n) == 0)
    {
        for (int i = 0; i < n; i++)
        {
            if (job[i].a > HOUR_12PM)
            {
                job[i].a = rand() % HOUR_12PM;
            }
        }
    }
}

int job_hours(Job *job, int index, int n)
{
    if (index >= n)
    {
        return 0;
    }
    return job[index].b - job[index].a;
}

void swap_job(Job *a, Job *b)
{
    Job temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort_job(Job *job, int n)
{
    for (int i = 0; i < n; i++)
    {
        int swapped = 0;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (job_hours(job, j, n) > job_hours(job, j + 1, n))
            {
                swap_job(job + j, job + j + 1);
                swapped = 1;
            }
        }
        if (swapped == 0)
        {
            break;
        }
    }
}

int pick_job(Job *job, int n)
{
    int sum_of_hours = 0;
    int pick = 0;
    bubble_sort_job(job, n);
    for (int i = 0; i < n; i++)
    {
        if (sum_of_hours <= 1440)
        {
            sum_of_hours += job_hours(job, i, n);
            pick++;
        }
        else
        {
            break;
        }
    }
    return pick;
}

int main()
{
    srand(time(NULL));
    int N;
    do
    {
        N = rand() % 100;
    } while (N <= 10);

    Job *job;
    job = calloc(N, sizeof(Job));

    generate_jobs(job, N);
    printf("Yeu cau 1\n%d \n", N);
    for (int i = 0; i < N; i++)
    {
        printf("(%d ; %d)\n", job[i].a, job[i].b);
    }

    int pick = pick_job(job, N);
    printf("\n\nYeu cau 2:\n\n%d\n", pick);
    for (int i = 0; i < pick; i++)
    {
        printf("(%d ; %d)\n", job[i].a, job[i].b);
    }

    free(job);
    return 0;
}
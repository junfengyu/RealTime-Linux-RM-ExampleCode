#include <pthread.h>
#include <sched.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_TASKS 3

typedef struct {
    int period; // in milliseconds
    int computation_time; // in milliseconds
    int priority;
    int cpu; // CPU core to which the task is assigned
} task_t;

task_t tasks[NUM_TASKS] = {
    {1000, 100, 0, 0}, // Task 1: Period 1000ms, Computation Time 100ms, CPU 0
    {500, 50, 0, 1},   // Task 2: Period 500ms, Computation Time 50ms, CPU 1
    {250, 25, 0, 2}    // Task 3: Period 250ms, Computation Time 25ms, CPU 2
};

void *task_function(void *arg) {
    task_t *task = (task_t *)arg;
    struct timespec next_activation;
    clock_gettime(CLOCK_MONOTONIC, &next_activation);

    while (1) {
        next_activation.tv_sec += task->period / 1000;
        next_activation.tv_nsec += (task->period % 1000) * 1000000;

        if (next_activation.tv_nsec >= 1000000000) {
            next_activation.tv_sec += 1;
            next_activation.tv_nsec -= 1000000000;
        }

        // Simulate task computation
        printf("Task with period %d ms on CPU %d is running.\n", task->period, task->cpu);
        usleep(task->computation_time * 1000);

        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &next_activation, NULL);
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_TASKS];
    struct sched_param param;
    int max_priority = sched_get_priority_max(SCHED_FIFO);

    // Assign priorities to tasks based on RM scheduling
    for (int i = 0; i < NUM_TASKS; i++) {
        tasks[i].priority = max_priority - i;
    }

    // Create threads for each task
    for (int i = 0; i < NUM_TASKS; i++) {
        pthread_attr_t attr;
        cpu_set_t cpuset;

        pthread_attr_init(&attr);
        pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
        param.sched_priority = tasks[i].priority;
        pthread_attr_setschedparam(&attr, &param);
        pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);

        // Set CPU affinity
        CPU_ZERO(&cpuset);
        CPU_SET(tasks[i].cpu, &cpuset);
        if (pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpuset) != 0) {
            perror("Failed to set CPU affinity");
            exit(1);
        }

        if (pthread_create(&threads[i], &attr, task_function, (void *)&tasks[i]) != 0) {
            perror("Failed to create thread");
            exit(1);
        }

        pthread_attr_destroy(&attr);
    }

    // Join threads (although in a real RTOS, tasks would typically run indefinitely)
    for (int i = 0; i < NUM_TASKS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

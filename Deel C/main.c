#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

char filename1[35];
pthread_mutex_t lock;

void *thread_func_1(void *vargp)
{

    int *interval = (int *)vargp;
    printf("Thread interval: %d\n", *interval);

    FILE *logfile;

    while (1)
    {
        pthread_mutex_lock(&lock);
        logfile = fopen(filename1, "a");
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        fprintf(logfile, "%d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        fclose(logfile);
        pthread_mutex_unlock(&lock);

        sleep(*interval);
    }

    return NULL;
}

int main(int argc, char **argv)
{

    strcpy(filename1, argv[1]);
    strcat(filename1, ".txt");
    printf("filename = %s\n", filename1);

    for (int i = 0; i < argc; i++)
    {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }

    pthread_t thread_1;
    for (int i = 2; i < argc; i++)
    {
        printf("i = %d\n", i);
        int interval = 0;
        interval = atoi(argv[i]);
        //printf("Create thread with interval => %d\n", interval);

        pthread_create(&thread_1, NULL, thread_func_1, (void *)&interval);
    }

    // Create a thread
    pthread_join(thread_1, NULL);
    pthread_mutex_destroy(&lock);

    return 0;
}

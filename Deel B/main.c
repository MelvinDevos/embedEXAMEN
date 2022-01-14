#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

int time1 = 0;
int time2 = 0;
char filename1[35];
char filename2[35];

void *thread_func_1(void *vargp)
{

    FILE *logfile;

    while (1)
    {
        logfile = fopen(filename1, "a");
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        fprintf(logfile, "%d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        fclose(logfile);

        sleep(time1);
    }

    return NULL;
}

void *thread_func_2(void *vargp)
{
    FILE *logfile;

    while (1)
    {
        logfile = fopen(filename2, "a");
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        fprintf(logfile, "%d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        fclose(logfile);

        sleep(time2);
    }

    return NULL;
}

int main(int argc, char **argv)
{
    for (int i = 0; i < argc; i++)
    {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    strcpy(filename1, argv[1]);
    strcat(filename1, ".txt");
    strcpy(filename2, argv[3]);
    strcat(filename2, ".txt");
    printf("filename1 = %s\n", filename1);
    printf("filename2 = %s\n", filename2);

    time1 = atoi(argv[2]);
    time2 = atoi(argv[4]);

    // Create a thread
    pthread_t thread_1;
    pthread_t thread_2;

    pthread_create(&thread_1, NULL, thread_func_1, NULL);
    pthread_create(&thread_2, NULL, thread_func_2, NULL);

    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);

    return 0;
}

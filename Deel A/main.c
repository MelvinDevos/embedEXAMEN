#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{

    for (int i = 0; i < argc; i++)
    {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    FILE *logfile;
    char filename[35];
    strcpy(filename, argv[1]);
    strcat(filename, ".txt");

    printf("filename = %s\n", filename);
    while (1)
    {

        logfile = fopen(filename, "a");
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        fprintf(logfile, "%d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        fclose(logfile);

        printf("Written to logfile!\n");

        sleep(atoi(argv[2]));
    }

    return 0;
}
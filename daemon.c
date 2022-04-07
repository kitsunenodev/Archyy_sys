//
// Created by franc on 30/03/2022.
//
#include <string.h>
#include <unistd.h>
#include <string.h>
#include "daemon.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>


void startdemon(){
    pid_t pid= fork();
    if(pid == -1) {
        printf("Erreur durant la creation du processus fils");
        exit(-1);
    }
    if(pid > 0){
        exit(0);
    }
    if(setsid < 0){
        printf("Erreur lors du chagement de l'ID de session");
        exit(-1);
    }
    pid = fork();
    if(pid == -1) {
        printf("Erreur durant la creation du processus fils");
        exit(-1);
    }
    if(pid > 0){
        exit(0);
    }
    FILE* ficpid = fopen(TEMPOFIC, "w");
    fprintf(ficpid, "%d", pid );
    fclose(ficpid);

    if(mkfifo(INVOCTOD, 0644) != 0){
        perror("Erreur lors de la creation du pipe");
        exit(-1);
    }
    if(mkfifo(DTOINVOC, 0644) != 0){
        perror("Erreur lors de la creation du pipe");
        unlink(INVOCTOD);
        exit(-1);
    }
    int rd_daemon = open(INVOCTOD, O_RDONLY);
    FILE* f_rd_daemon = fdopen(rd_daemon, "r");
    char rd_value[BUFFER];
    time_t clock = time(NULL);
    while (69){
        fscanf(f_rd_daemon, "%s", rd_value);
        if(strcmp(rd_value, "date") == 0){
            int wr_daemon = open(DTOINVOC, O_WRONLY);
            FILE* f_wr_daemon = fdopen(wr_daemon, "w");
            time_t currentdate= time(NULL);
            struct tm date = *localtime(&currentdate);
            fprintf(f_wr_daemon, "%d/%d/%d", date.tm_mday, date.tm_mon+1, date.tm_year + 1900);
            fclose(f_wr_daemon);
            close(wr_daemon);
        }
        if(strcmp(rd_value, "timer") == 0){
            int wr_daemon = open(DTOINVOC, O_WRONLY);
            FILE* f_wr_daemon = fdopen(wr_daemon, "w");
            fprintf(f_wr_daemon, "%ld", time(NULL) - clock);
            fclose(f_wr_daemon);
            close(wr_daemon);

        }
        if(strcmp(rd_value, "reset") == 0){
            clock = time(NULL);
        }



    }
}
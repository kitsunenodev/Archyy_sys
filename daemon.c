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
    fprintf(ficpid, "%d", getpid());
    fclose(ficpid);

    if(mkfifo(INVOCTOD, 0644) != 0){
        perror("Erreur lors de la creation du pipe");
        exit(-1);
    }

    char rd_value[TAILLE];
    time_t clock = time(NULL);
    int nb_reset = 0;
    while (1){
        int rd_daemon = open(INVOCTOD, O_RDONLY);
        read(rd_daemon, rd_value, TAILLE);
        close(rd_daemon);

        if(strcmp(rd_value, "date") == 0){
            int wr_daemon = open(INVOCTOD, O_WRONLY);
            time_t currentdate= time(NULL);
            struct tm date = *localtime(&currentdate);
            char value[TAILLE];
            sprintf(value, "%d/%d/%d", date.tm_mday, date.tm_mon+1, date.tm_year + 1900);
            write(wr_daemon, value, TAILLE);
            close(wr_daemon);
        }
        if(strcmp(rd_value, "timer") == 0){
            int wr_daemon = open(INVOCTOD, O_WRONLY);
            char value[TAILLE];
            sprintf(value, "%ld", time(NULL) - clock);
            write(wr_daemon, value, TAILLE);
            close(wr_daemon);

        }
        if(strcmp(rd_value, "reset") == 0){
            clock = time(NULL);
            nb_reset++;
        }
        if(strcmp(rd_value, "nbreset") == 0){
            int wr_daemon = open(INVOCTOD, O_WRONLY);
            char value[TAILLE];
            sprintf(value, "%d", nb_reset);
            write(wr_daemon, value, TAILLE);
            close(wr_daemon);
        }
    }
}
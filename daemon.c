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
    while (69){

    }
}
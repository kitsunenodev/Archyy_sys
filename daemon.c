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

    int nombre;
    FILE* pipef;
    char *path_fichier = "./tmp/pipe2.txt", chaine[50];
    printf("%d",access(path_fichier,F_OK));
    nombre = open(path_fichier, O_RDONLY);
    pipef = fdopen(nombre,"r");
    int nombre2;
    FILE* pipef2;
    char *path_fichier2 = "./tmp/pipe2.txt";
    if(mkfifo(path_fichier2, 0644) != 0) /* création du fichier */
    {
        perror("Problème de création du noeud de tube");
        exit(1);
    }
    nombre2 = open(path_fichier2, O_WRONLY);
    pipef2 = fdopen(nombre2,"r");
    while (666)
    {
        fscanf(pipef,"%s", chaine);
        if(strcmp(chaine, "date") == 0){
        fprintf(pipef2, "test\n");
        unlink(path_fichier2);
        }
        if(strcmp(chaine, "timer") == 0){
        }
        if(strcmp(chaine, "reset") == 0){
        }
    }
}
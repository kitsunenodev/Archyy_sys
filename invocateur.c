//
// Created by franc on 07/04/2022.
//

#include "invocateur.h"
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "daemon.h"
void help(){ //fonction qui fait apparaitre l'aide dans le terminal
    printf("WALLA TU TE DEMERDE FRERE\n");
    //ici test de tube només
    int nombre;
    FILE* mon_fichier = fopen("pipe", "r");
    char* path_monfichier = "./tmp/pipe.txt";
    if(mkfifo(path_monfichier, 0644) != 0)
    {
    perror("Problème de création du noeud de tube");
    exit(1);
    }
    nombre = open(path_monfichier, O_WRONLY);
    mon_fichier = fdopen(nombre,"w");
    fprintf(mon_fichier,"coucou\n");
    unlink(path_monfichier);
    exit(0);
    //fin test
} 
void stop(){ //recherche le pid du daemon dans un fichier et viens le tuer.
    if (isalive()) {
        FILE *pidfic = fopen(TEMPOFIC, "r");
        fclose(pidfic);
        int pid;
        kill(pid, SIGKILL);
        remove(TEMPOFIC);
    }
}

int isalive(){ //fonction qui retourne 0 si daemon est mort 
    return !access(TEMPOFIC, F_OK);
}

void restart(){ //redémare le daemon
    stop();
    startdemon();
}
void state(){ //fontion qui fait apparaitre l'état du daémon
    if(isalive()){
        printf("Votre Daemon est Demarré\n");
    } else{
        printf("Votre Daemon est éteint\n");
    }
}
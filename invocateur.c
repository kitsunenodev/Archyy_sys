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
void state(){
    if(isalive()){
        printf("Demarré\n");
    } else{
        printf("éteint\n");
    }
}
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
#include <signal.h>
#include <time.h>
#include "daemon.h"

void help(){
    printf("Daemon Help\n"
           "arguments:\n"
           "\n"
           "--help\t\tshow this message\n"
           "\n"
           "--start\t\tlaunch the daemon and print something\n"
           "\n"
           "--stop\t\tkill the daemon\n"
           "\n"
           "--restart\tkill and launch the daemon\n"
           "\n"
           "--state\t\tprint the curent state of the daemon [\n"
           "\n"
           "--date\t\tprint the curent date\n"
           "\n"
           "--timer\t\tset a timer and show it\n"
           "\n"
           "--resettimer\treset the timer\n"
           "\n"
           "--nombrereset\t show how many time the timer of the actual instance of the daemon has been reset\n"
           "\n"
           "--roll\t roll a random number between 1 and 6\n");

    exit(0);
} 
void stop(){ //recherche le pid du daemon dans un fichier et viens le tuer.
    if (isalive()) {
        int pid;
        FILE *pidfic = fopen(TEMPOFIC, "r");
        fscanf(pidfic,"%d", &pid);
        fclose(pidfic);
        remove(TEMPOFIC);
        unlink(INVOCTOD);
        kill(pid, SIGKILL);
    }
}

int isalive(){ //fonction qui retourne 0 si daemon est mort
    return !access(TEMPOFIC, F_OK);

}

void state(){ //fontion qui fait apparaitre l'état du daemon
    if(isalive()){
        printf("Votre Daemon est Demarré\n");
    } else{
        printf("Votre Daemon est éteint\n");
    }
}

void date(){
    int wr_invoc = open(INVOCTOD, O_WRONLY);
    write(wr_invoc, "date", TAILLE);
    close(wr_invoc);
    int rd_invoc = open(INVOCTOD, O_RDONLY);
    char rd_value[TAILLE];
    read(rd_invoc, rd_value, TAILLE);
    close(rd_invoc);
    printf("%s\n", rd_value);
}

void timer(){
    int wr_invoc = open(INVOCTOD, O_WRONLY);
    write(wr_invoc, "timer", TAILLE);
    close(wr_invoc);
    int rd_invoc = open(INVOCTOD, O_RDONLY);
    char rd_value[TAILLE];
    read(rd_invoc, rd_value, TAILLE);
    close(rd_invoc);
    printf("%s\n", rd_value);
}
void resettimer(){
    int wr_invoc = open(INVOCTOD, O_WRONLY);
    write(wr_invoc, "reset", TAILLE);
    close(wr_invoc);
}
void nombrerest(){
    int wr_invoc = open(INVOCTOD, O_WRONLY);
    write(wr_invoc, "nbreset", TAILLE);
    close(wr_invoc);
    int rd_invoc = open(INVOCTOD, O_RDONLY);
    char rd_value[TAILLE];
    read(rd_invoc, rd_value, TAILLE);
    close(rd_invoc);
    printf("%s\n", rd_value);
}
int rolled;
int roll(){
    srand((unsigned)time(NULL));
    rolled = rand()%6 + 1;;
    return rolled;
}
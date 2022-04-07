#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "daemon.h"
#include "invocateur.h"

int main(int argc,char* argv[]){

    if(argc != 2){
        printf("Erreur, le nombre d'argument est incorect");
        exit(-1);
    }
    if(!strcmp(argv[1], "--start")){
        startdemon();
    }
    if(!strcmp(argv[1] , "--stop")){
        stop();
    }
    if(!strcmp(argv[1] , "--restart")){
        restart();
    }
    if(!strcmp(argv[1] , "--state")){
        state();
    }
    if(!strcmp(argv[1] , "--help")){
        help();
    }
    return 0;
}
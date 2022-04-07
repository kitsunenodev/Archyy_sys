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
    else{
        if(!strcmp(argv[1], "--start")){
            startdemon();
            exit(0);
        }
        if(!strcmp(argv[1] , "--stop")){
            stop();
            exit(0);
        }
        if(!strcmp(argv[1] , "--restart")){
            restart();
            exit(0);
        }
        if(!strcmp(argv[1] , "--state")){
            state();
            exit(0);
        }
        if(!strcmp(argv[1] , "--help")){
            help();
            exit(0);
        }
        else{
        printf("bad argument type --help for more informations\n");
        exit(-1);
        }
    }
    
    return 0;
}
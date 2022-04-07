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
            if (isalive()){
                printf("Le demon est deja demarré\n");
                exit(-1);
            }
            startdemon();
            exit(0);
        }
        if(!strcmp(argv[1] , "--stop")){
            stop();
            exit(0);
        }
        if(!strcmp(argv[1] , "--restart")){
            stop();
            startdemon();
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
        if(!strcmp(argv[1] , "--date")){
            int wr_invoc = open(INVOCTOD, O_WRONLY);
            write(wr_invoc, "date", BUFFER);
            close(wr_invoc);
            int rd_invoc = open(INVOCTOD, O_RDONLY);
            char rd_value[BUFFER];
            read(rd_invoc, rd_value, BUFFER);
            close(rd_invoc);
            printf("%s\n", rd_value);
            exit(0);
        }
        if(!strcmp(argv[1] , "--timer")){
            int wr_invoc = open(INVOCTOD, O_WRONLY);
            write(wr_invoc, "timer", BUFFER);
            close(wr_invoc);
            int rd_invoc = open(INVOCTOD, O_RDONLY);
            char rd_value[BUFFER];
            read(rd_invoc, rd_value, BUFFER);
            close(rd_invoc);
            printf("%s\n", rd_value);
            exit(0);
        }
        if(!strcmp(argv[1] , "--resettimer")){
            int wr_invoc = open(INVOCTOD, O_WRONLY);
            write(wr_invoc, "reset", BUFFER);
            close(wr_invoc);
            exit(0);
        }
        if(!strcmp(argv[1] , "--nombrereset")){
            int wr_invoc = open(INVOCTOD, O_WRONLY);
            write(wr_invoc, "nbreset", BUFFER);
            close(wr_invoc);
            int rd_invoc = open(INVOCTOD, O_RDONLY);
            char rd_value[BUFFER];
            read(rd_invoc, rd_value, BUFFER);
            close(rd_invoc);
            printf("%s\n", rd_value);
            exit(0);
        }
        else{
        printf("bad argument type --help for more informations\n");
        exit(-1);
        }
    }
    return 0;
}
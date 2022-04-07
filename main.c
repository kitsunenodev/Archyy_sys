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
                printf("Le demon est deja demarré");
                exit(-1)
            }
            if (mkfifo)
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
        if(!strcmp(argv[1] , "--date")){
            int wr_invoc = open(INVOCTOD, O_WRONLY);
            FILE* f_wr_invoc = fdopen(wr_invoc, "w");
            fprintf(f_wr_invoc, "date");
            int rd_invoc = open(DTOINVOC, O_RDONLY);
            FILE* f_rd_invoc = fdopen(rd_invoc, "r");
            char rd_value[BUFFER];
            fscanf(f_rd_invoc, "%s", rd_value);
            fclose(f_rd_invoc);
            close(rd_invoc);
            printf("%s\n", rd_value);
            exit(0);
        }
        if(!strcmp(argv[1] , "--timer")){
            int wr_invoc = open(INVOCTOD, O_WRONLY);
            FILE* f_wr_invoc = fdopen(wr_invoc, "w");
            fprintf(f_wr_invoc, "timer");
            int rd_invoc = open(DTOINVOC, O_RDONLY);
            FILE* f_rd_invoc = fdopen(rd_invoc, "r");
            char rd_value[BUFFER];
            fscanf(f_rd_invoc, "%s", rd_value);
            fclose(f_rd_invoc);
            close(rd_invoc);
            printf("%s\n", rd_value);
            exit(0);
        }
        if(!strcmp(argv[1] , "--resettimer")){
            int wr_invoc = open(INVOCTOD, O_WRONLY);
            FILE* f_wr_invoc = fdopen(wr_invoc, "w");
            fprintf(f_wr_invoc, "reset");
            printf("Timer reset\n");
            exit(0);
        }
        else{
        printf("bad argument type --help for more informations\n");
        exit(-1);
        }
    }
    return 0;
}
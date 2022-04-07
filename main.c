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
        if(!strcmp(argv[1] , "--date")){
            int nombre;
            FILE* pipef;
            char* path_fichier = "./tmp/pipe.txt";
            if(mkfifo(path_fichier, 0644) != 0) /* création du fichier */
            {
                perror("Problème de création du noeud de tube");
                exit(1);
            }
            nombre = open(path_fichier, O_WRONLY);
            pipef = fdopen(nombre, "w");
            fprintf(pipef,"date\n");
            unlink(path_fichier);
            int nombre2;
            FILE* pipef2;
            char *path_fichier2 = "./tmp/pipe2.txt", chaine[50];
            nombre2 = open(path_fichier2, O_RDONLY);
            pipef2 = fdopen(nombre2, "r");
            fscanf(pipef2,"%s", chaine);
            while (strcmp(chaine, "date") == 0){
                fscanf(pipef2,"%s", chaine);
            }
            printf("%s", chaine);
            unlink(path_fichier2);
            nombre = open(path_fichier, O_WRONLY);
            pipef = fdopen(nombre, "w");
            fprintf(pipef,"0\n");
            exit(0);
        }
        if(!strcmp(argv[1] , "--timer")){
            exit(0);
        }
        if(!strcmp(argv[1] , "--resettimer")){
            exit(0);
        }
        else{
        printf("bad argument type --help for more informations\n");
        exit(-1);
        }
    }
    return 0;
}
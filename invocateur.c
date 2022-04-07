//
// Created by franc on 07/04/2022.
//

#include "invocateur.h"
#include <stdio.h>
#include <stdlib.h>
#include "daemon.h"
void help(){
    printf("WALLA TU TE DEMERDE FRERE\n");
}
void stop(){
    if (isalive()) {
        FILE *pidfic = fopen(TEMPOFIC, "r");

        fclose(pidfic);
        kill(pid, SIGKILL);
        remove(TEMPOFIC);
    }
}

int isalive(){
    return !access(TEMPOFIC, F_OK);
}

void restart(){
    stop();
    startdemon();
}
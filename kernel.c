//
// Created by jason on 2020-02-15.
//
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "shell.h"
#include "ram.h"
#include "cpu.h"
#include "pcb.h"



PCB *currPCB;
//int myinit(FILE *file);

int main(int argc, const char *argv[]){

    initRAM();
    initCPU();

    int result = shellUI();
    return result;
}


int myInit(FILE *file){
    PCB *pcb;
    int result;
    result = addToRAM(file, &start, &end);
    if (result >=0){
        pcb = makePCB(start,end);
        if(pcb != NULL){
            addToReady(pcb);
            return 0;
        }
    }

    return 1;
}
void terminate(PCB *p){

    clearRAM(p->start, p->end);
    free(p);
}

void scheduler(){

    int result;
    initCPU();



    while(getHead() != NULL){
//        printPCB();
        currPCB = getFromReady();
        if(currPCB != NULL){
            setCPU(currPCB->PC);
            result = run(2);
            if (result ==2){
                terminate(currPCB);
            } else{
                addToReady(currPCB);
            }

        }
    }
}


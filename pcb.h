//
// Created by jason on 2020-02-15.
//

#ifndef PCB_H
#define PCB_H

typedef struct PCB_REC{
    int PC; int start; int end; struct PCB_REC *next;
}PCB;

PCB *makePCB(int start, int end);
void printPCB();
void addToReady(PCB *pcb);
PCB  *getFromReady();
PCB *getHead();


#endif //PCB_H

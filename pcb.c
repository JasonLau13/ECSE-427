
#include <stdio.h>
#include <stdlib.h>
#include "pcb.h"
//#include "kernel.h"

//PCB *head= NULL, *tail = NULL;
 //Ready Queue
 PCB *head = NULL, *tail = NULL;


void printPCB(){
    PCB *foo = head;
    while (foo!=NULL){
        printf("Addr: %d\n" , foo->start);
        foo = foo->next;
    }

}

PCB *makePCB( int start, int end){
    PCB *pcb;
//    if (f == NULL) return NULL;
    pcb = (PCB*)malloc(sizeof(PCB));
    if(pcb == NULL) return  NULL;

    pcb->PC = start;
    pcb->start = start;
    pcb->end = end;
    pcb->next = NULL;

    return pcb;
}

PCB *getHead(){
    return head;
}

void addToReady(PCB *p){
//    p->next = NULL;
    if (head == NULL){
        head = p;
        tail = p;
    }
    else {
        tail->next= p;
        tail = p;
    }
}

PCB *getFromReady(){
        PCB *dispatch;
        if(head == NULL){
        return NULL;
     }
        dispatch = head;
        head = head->next;
        dispatch->next = NULL;

    if (head == NULL){
        tail = NULL;
    }
    return  dispatch;
}

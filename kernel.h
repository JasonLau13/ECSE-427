//
// Created by jason on 2020-02-15.
//

#ifndef KERNEL_H
#define KERNEL_H

#include "pcb.h"
int myInit(FILE *file);
void scheduler();
extern PCB *currPCB;
#endif //UNTITLED1_KERNEL_H

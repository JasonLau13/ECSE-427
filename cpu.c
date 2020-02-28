//
// Created by jason on 2020-02-15.
//

#include <stdio.h>
#include "ram.h"
#include "pcb.h"
#include "interpreter.h"
#include "kernel.h"
#include <string.h>

#define sizeOfCurrentInstruction 1000

struct CPU{ int IP; char IR[sizeOfCurrentInstruction]; int quanta;}cpu;

void initCPU(){
    cpu.quanta = 2;
    cpu.IP = 0;
    cpu.IR[0] = '\0';
}

void setCPU(int PC){
    cpu.IP = PC;
    cpu.IR[0] = '\0';
}

int run(int quanta){
    int result;
    int curInstruction = currPCB->PC;
    int endInstruction = currPCB->end;
    cpu.IP++;
    cpu.quanta = quanta;
//    in_file_flag =1;
    while (cpu.quanta > 0){
            strcpy(cpu.IR, ram[curInstruction]);
            quitProgram=0;
            if (curInstruction < endInstruction+1 ) {
                result = interpret(cpu.IR);
                if (result != 0) {
                    return result;
                }
                if (curInstruction == endInstruction) {
//                    in_file_flag = 0;
                    return 2;
                }
                cpu.IP++;
                curInstruction++;
                cpu.quanta--;
            }
        }
    currPCB->PC = curInstruction;
    return  0;
}

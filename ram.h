//
// Created by jason on 2020-02-15.
//

#ifndef RAM_H
#define RAM_H

void initRAM();
int addToRAM(FILE *p,int *startAddr, int *endAddr);
void clearRAM(int startAddr, int endAddr);
extern char* ram[1000];
extern int start;
extern int end;

#endif

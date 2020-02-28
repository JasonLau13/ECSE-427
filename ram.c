//
// Created by jason on 2020-02-15.
//

#include <stdio.h>
#include <string.h>
#define MEM_LENGTH 1000
char *ram[MEM_LENGTH];
int i=0;
int start;
int end;
void initRAM(){
    int i;
    for(i = 0; i < MEM_LENGTH; i++){
        ram[i] = NULL;
    }
}

int addToRAM(FILE *file, int *startAddr , int *endAddr){
    char *line = NULL;
    size_t linecap = 0;
//   else{
       start = i;
        while (!feof(file)){
//            printf("i ==  %d\n", i);
            getline(&line, &linecap, file);
            if(i<MEM_LENGTH){
                ram[i] = strdup(line);
//                printf("Line: %s\n", ram[i]);
            } else {
                printf("Memory error\n");
                return -1;
            }
            i++;
        }
        end = i-1;
        return end;
//    }

}

void clearRAM(int startAddr, int endAddr){
    for(i = startAddr; i < endAddr+1; i++){
        ram[i]=NULL;
    }

}
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <strings.h>
#include "utils.h"


void clearBuffer(){
    char un;
    while (true)
    {
        un = getchar();
        if (un == '\n')
        {
            break;
        }
    }
}

void clearCaracter(char *clear){
    clear[strcspn(clear, "\n")] = '\0'; 
}

void changeAny(const char *changeOrig, char *changeDest, int maxBuffer){
    int i;
    for (i = 0; changeOrig[i] != '\0' && i < maxBuffer - 1; i++)
    {
        changeDest[i] = changeOrig[i];
    }
    changeDest[i] = '\0';
}



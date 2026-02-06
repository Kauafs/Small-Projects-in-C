#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include "crypto.h"

void crypto(char *strcryp){
    char uniq = 'a';
    int key = 5;
    int len;
    int grd;

    len = strlen(strcryp);

   for (int i = 0; i < len ; i++)
   {
        if (strcryp[i] >= 'a' && strcryp[i] <= 'z')
        {
            grd = ((strcryp[i] - uniq)  + key) % 26 + uniq;
            strcryp[i] = grd;
        }   
   }
}

void decrypt(char *strdecry){
    char uniq = 'a';
    int key = 5;
    int len;
    int grd;

    len = strlen(strdecry);

   for (int i = 0; i < len ; i++)
   {
        if (strdecry[i] >= 'a' && strdecry[i] <= 'z')
        {
            grd = (((strdecry[i] - uniq) - key + 26) % 26) + uniq;
            strdecry[i] = grd;
        }   
   }
}
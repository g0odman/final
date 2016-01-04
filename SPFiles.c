#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SPHashTable.h"
#include "SP_Tree.h"
#define MAX_LINE_SIZE 200
void getVariables(int argc, char **argv, SP_HASH *variables){
    for(int i =1; i < argc; i++){
        if(argv[i][0] == '-' && argv[i][1] == 'v'){
            FILE *fp = fopen(argv[i+1],"r");
            char * line = (char *) malloc(MAX_LINE_SIZE+1);
            while(fgets(line,MAX_LINE_SIZE,fp) != NULL){
                char *variable = strtok(line,"\r\t\n ");
                strtok(NULL,"\r\t\n ");
                char *value = strtok(NULL,"\r\t\n ");
                long val = strtol(value, NULL,10);
                SP_HASH_ERROR msg;
                spHashInsert(*variables,variable,val,&msg);
            }
            free(line);
        }
    }
}

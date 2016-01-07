#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SPHashTable.h"
#include "SP_Tree.h"
#include "SPFiles.h"
#define MAX_LINE_SIZE 200
bool init(int argc,char **argv,SP_HASH *variables, FILE **fp){
    if(!isValidCommandLineArgumentsList(argc,argv))
        return false;
    //create hashtable:
    *variables = spHashCreate(NULL);
    //read variables from file, if given:
    if(!getVariables(argc,argv,variables))
        return false;
    
    //check whether to print to file, or stdout:
    *fp = toPrint(argc,argv);
    if(*fp == NULL){
        return false;
    }
    return true;

}

bool isValidCommandLineArgumentsList(int argc, char** argv){
    if (argc % 2 == 0 || argc > 5){
        printf("Invalid command line arguments, use [-v filename1] [-o filename2]");
        return false;
    }
    for(int i = 1;i < argc; i+=2){
        if((strcmp(argv[i],"-v") != 0&&(strcmp(argv[i],"-o") != 0))){
            printf("Invalid command line arguments, use [-v filename1] [-o filename2]");
            return false;
        }
    }
    if(argc == 5){
        if(strcmp(argv[1] ,argv[3])==0){
            printf("Invalid command line arguments, use [-v filename1] [-o filename2]");
           return false;
        }
        if(strcmp(argv[2],argv[4]) ==0){
            printf("Files must be different");
            return false;
        }
    }
    return true;
}
bool getVariables(int argc, char **argv, SP_HASH *variables){
    for(int i =1; i < argc; i++){
    	//search for command that gives filename:
        if(argv[i][0] == '-' && argv[i][1] == 'v'){
        	//if found, try and open file:
            FILE *fp = fopen(argv[i+1],"r");//Check if error
            if(fp ==NULL){
                printf("Variable init file doesn't exist or is not readable\n");
                spHashDestroy(*variables);
                return false;
            }
            //read from file:
            char * line = (char *) malloc(MAX_LINE_SIZE+1);
            while(fgets(line,MAX_LINE_SIZE,fp) != NULL){
            	//get variable name and value:
                char *variable = strtok(line,"\r\t\n ");
                strtok(NULL,"\r\t\n ");
                char *value = strtok(NULL,"\r\t\n ");
                //convert value to number
                long val = strtol(value, NULL,10);
                SP_HASH_ERROR msg;
                //insert the var with the value into the hashtable:
                spHashInsert(*variables,variable,val,&msg);
            }
            free(line);
            fclose(fp);
            return true;
        }
    }
    return true;
}

FILE *toPrint(int argc, char **argv){
    for(int i =1; i < argc; i++){
        if(argv[i][0] == '-' && argv[i][1] == 'o'){
            return fopen(argv[i+1],"w");
        }
    }
    return stdout;
}

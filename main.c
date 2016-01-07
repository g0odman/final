#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "SP_Aux.h"
#include "SPHashTable.h"
#include "SPFiles.h"
#define MAX_LINE_LENGTH 1024
#define MAX_OUT_LINE 100

int main(int argc, char ** argv){
	
	//allocate buffer to read and write to:
    char *line = (char*)malloc(MAX_LINE_LENGTH +1);
    char *out = (char*) malloc(MAX_OUT_LINE+1);
    //allocate space for filename, if needed:
    char *filename = NULL;
    //create hashtable:
    SP_HASH variables = spHashCreate(NULL);
    //read variables from file, if given:
    getVariables(argc,argv,&variables);
    //check whether to print to file, or stdout:
    bool p = toPrint(argc,argv,&filename);
    FILE *fp =p? fopen(filename,"w"):stdout;
    //main loop:
    while (fgets(line,MAX_LINE_LENGTH,stdin)!=NULL){
        if(isExit(line))//exit, if exit code was recieved
            break;
        if(parse(line,variables,out)){ //parses line, see SP_Aux
            fprintf(fp,"%s",out);
        }
    }
    //free all memory:
    free(line);
    free(out);
    spHashDestroy(variables);
    if(p){
        fclose(fp);
        free(filename);
    } 
    if(printf("Exiting...\n") < 0)
        exit(EXIT_FAILURE);
    return 0;
}

#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "SP_Aux.h"
#include "SPHashTable.h"
#include "SPFiles.h"
#define MAX_LINE_LENGTH 1024
#define MAX_OUT_LINE 100

int main(int argc, char ** argv){
	
    SP_HASH variables;
    FILE *fp = NULL;
    if(!init(argc,argv,&variables,&fp))
        return 1;
	//allocate buffer to read and write to:
    char *line = (char*)malloc(MAX_LINE_LENGTH +1);
    char *out = (char*) malloc(MAX_OUT_LINE+1);
    if(line ==NULL || out == NULL){ //malloc failed
        printf("Unexpected error occured!\n");
        exit(EXIT_FAILURE);
    }
    //main loop:
    while (fgets(line,MAX_LINE_LENGTH,stdin)!=NULL){
        if(isExit(line))//exit, if exit code was recieved
            break;
        parse(line,variables,out); //parses line, see SP_Aux
        if(fprintf(fp,"%s",out) < 0)
            exit(EXIT_FAILURE);
    }
    if(fprintf(fp,"(<>)\nExiting...\n") < 0)
        exit(EXIT_FAILURE);

    if(fp != stdout)
        fclose(fp);
    //free all memory:
    free(line);
    free(out);
    spHashDestroy(variables);

    return 0;
}

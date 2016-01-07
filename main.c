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
    fclose(fp);

    if(printf("Exiting...\n") < 0)
        exit(EXIT_FAILURE);
    return 0;
}

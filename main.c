#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "SP_Aux.h"
#include "SPHashTable.h"
#include "SPFiles.h"
#define MAX_LINE_LENGTH 1024
#define MAX_OUT_LINE 100

int main(int argc, char ** argv){
	
	//allocate buffer to read to:
    char *line = (char*)malloc(MAX_LINE_LENGTH +1);
    char *out = (char*) malloc(MAX_OUT_LINE+1);
    char *filename = NULL;
    SP_HASH variables = spHashCreate(NULL);
    getVariables(argc,argv,&variables);
    bool p = toPrint(argc,argv,&filename);
    FILE *fp = fopen(filename,"w");
    //main loop:
    while (fgets(line,MAX_LINE_LENGTH,stdin)!=NULL){
        if(isExit(line))//Exit code was recieved
            break;
        if(parse(line,variables,out)){ //see SP_Aux
            if(p)
                fprintf(fp,"%s",out);
            else
                printf("%s",out);
        }
    }
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

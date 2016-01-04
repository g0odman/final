#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "SP_Aux.h"
#include "SPHashTable.h"
#include "SPFiles.h"
#define MAX_LINE_LENGTH 1024

int main(int argc, char ** argv){
	
	//allocate buffer to read to:
    char *line = (char*)malloc(MAX_LINE_LENGTH +1);
    SP_HASH variables =getVariables(argc,argv);

    
    //main loop:
    while (fgets(line,MAX_LINE_LENGTH,stdin)!=NULL){
        if(isExit(line))//Exit code was recieved
            break;
        parse(line,variables); //see SP_Aux
        
    }
    free(line);
    spHashDestroy(variables);
    
    if(printf("Exiting...\n") < 0)
        exit(EXIT_FAILURE);
    return 0;
}

#include <stdio.h>
#include "SPHashTable.h"
SP_HASH getVariables(int argc, char **argv){
    SP_HASH variables = spHashCreate(NULL);
    for(int i =1; i < argc; i++){
        if(argv[i][0] == '-' && argv[i][1] == 'v'){
            FILE *fp = fopen(argv[i+1],"r+");
            printf("h\n");
            fprintf(fp, "This is testing for fprintf...\n");
            fclose(fp);
        }
    }
    return variables;
}

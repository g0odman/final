#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "SP_Aux.h"
#include "SPHashTable.h"

char *antiAntlr(SP_TREE *tree);
/**
 *  Main function, parses given input and calculates result. Prints
 *  all necsesary things.
 */
bool parse(char * line,SP_HASH variables, char *s){
	//check whether exit command:
    //make tree and validate that they were succesfull:
    SP_HASH_ERROR msg = 0;

    bool valid = true;
    SP_TREE *root = split(line,variables, &msg);
    //evaluate:
    if(root->type==ASSIGNMENT){
        assign(root, variables, &msg);
        spTreeDestroy(root);
        return false;
    }
    double out =  spTreeEval(root,&valid,variables,&msg);
    char * expr = antiAntlr(root);
    if(valid)
        sprintf(s, "%s\nres = %f\n",expr, out);
    else
        sprintf(s,"%s\nInvalid Result\n",expr);
    free(expr);
    spTreeDestroy(root);
    //In case function was successful
    return true;
}
void assign(SP_TREE *root, SP_HASH variables, SP_HASH_ERROR *msg){
    bool valid = true;
    char *variable = getRootStr(root->children[0]);
    double value=  spTreeEval(root->children[1],&valid,variables, msg);
    if(valid)
        spHashInsert(variables,variable, value, msg);
}


SP_TREE *split(char *line,SP_HASH variables, SP_HASH_ERROR* msg){
    //Value for node
    SP_TREE *new;

    if((new = spTreeCreate()) == NULL){
        quit(new,line,variables,msg,true);
    }
    //j is the number of brackets seen, i is the current place
    int j = 1,i=1;
    while(j > 0){  //recursively parse children:
        if(line[i] == '(' && (++j) == 2){
        	//if closed brackets on child, parse it:
            if(!spTreePush(new,split(line+i,variables,msg))){
                //If parsing failed, exit function and check print value
                quit(new,line,variables,msg,printf("Unexpected error occured!") >= 0);
            }
        }
        //Go up one level
        if(line[i] == ')')
            j--;
        i++;
    }
    //Copy the relevant string for this node:
    int length = 1;
    while(line[length] != '(' && line[length] != ')') { length++; }
    length--;
	char * temp = malloc(length+1);
    if(temp == NULL)
        quit(new,line,variables,msg,true);
	strncpy(temp,line +1,length);
    temp[length] = '\0';
    if(!setValue(new,temp)){
        free(line);
        quit(new,line,variables,msg,true);
    }
    free(temp);
    return new;
}

double operate(double x, double y, SP_TREE_TYPE op, bool * valid){
    *valid = (isValid(op,x,y) ? *valid : false);
    //perform relevant op on inputs
    switch (op){
        case PLUS:
            return x + y;
        case MINUS:
            return  x - y;
        case MULTIPLICATION:
            return  x * y;
        case DIVISION:
            return  x / y;
        case DOLLAR:
            return ((y-x+1)*(y+x))/2;
        case MAXIMUM:
            return x>y ? x: y;
        case MINIMUM:
            return x<y ? x: y;
        default :
            return 0;
    }
}

bool isValid(SP_TREE_TYPE op, double x, double y){
	//test relevant case for op:
    switch(op){
        case DIVISION:
            return  y != 0;
        case DOLLAR:
            return y >= x && ((int) y == y) && ((int)x == x);
        default:
            return true;
    }
}

double spTreeEval(SP_TREE *tree, bool * valid, SP_HASH variables, SP_HASH_ERROR* msg){

    //leaf, return value:
    switch(tree->type){
        case NUMBER:
            return atoi(getRootStr(tree));
        case VARIABLE:
            return spHashGetValue(variables, getRootStr(tree), msg);
        case AVERAGE:
        case MEDIAN:
            return average(tree,valid,variables,msg);
        default:
            break;
    }


    //otherwise, calculate op on first child, first:
    double out = spTreeEval(tree->children[0],valid,variables,msg);

    //In case of a unary operator
    if(tree->size == 1)
        return operate(0,out,tree->type,valid);

    //then continue recursively calculating children,
    //and performing the op on them
    for(int i=1; i < tree->size; i++){
        double temp = spTreeEval(tree->children[i], valid, variables, msg);
        out = operate(out,temp,tree->type,valid);
    }

    return out;
}
int compare(const void *a, const void *b){
    if(*((double*) a)>*((double*) b))
        return 1;
    else
        return (int)(*(double *)b-*(double *)a);
}
double average(SP_TREE *tree, bool *valid, SP_HASH variables, SP_HASH_ERROR *msg){
    double * arr = malloc(tree->size*sizeof(double));
    double ans = 0;
    for(int i = 0; i < tree->size; i++){
        arr[i] = spTreeEval(tree->children[i],valid,variables,msg);
    }
    if(tree->type ==AVERAGE){
        double sum = 0;
        for(int i =0; i< tree->size;i++)
            sum += arr[i];
        ans = sum/tree->size;
    }
    else{//case MEDIAN:
        qsort(arr,tree->size,sizeof(double),compare);
        if(tree->size %2)
            ans = arr[tree->size/2];
        ans = (arr[tree->size/2 -1] + arr[tree->size/2])/2;
    }
    free(arr);
    return ans;
}
bool cond(char *a){
    if(strlen(a) ==1 && (a[0] == ')' || a[0] == '(' || a[0] == ','))
        return false;
    return getType(a) == VARIABLE || getType(a) == NUMBER;
}
char * concat(char *a, char *b){
    char *out = (char *)calloc(1,sizeof(char)*(strlen(a)+strlen(b) +1));
    strcpy(out,a);
    strcat(out,b);
    if(cond(a))
        free(a);
    if(cond(b))
        free(b);
    return out;
}
char *antiAntlr(SP_TREE *tree){
    if(tree==NULL)
        return (char *)calloc(1,sizeof(char));
    if(tree->type == VARIABLE || tree->type == NUMBER){
        char *out = malloc((strlen(tree->value)+1)*sizeof(char));
        strcpy(out,tree->value);
        return out;
    }
    if(tree->size ==1)
        return concat(concat(concat("(",getRootStr(tree)),antiAntlr(tree->children[0])),")");
    char * out = "";
    switch(tree->type){
        case AVERAGE:
        case MINIMUM:
        case MEDIAN:
        case MAXIMUM:
            out = concat(getRootStr(tree),"(");
            for(int i = 0; i < tree->size;i++)
                out =concat(out,concat(antiAntlr(tree->children[i]),","));
            out[strlen(out)-1] = ')';
            break;
        default:
            out = concat("(",antiAntlr(tree->children[0]));
            out = concat(out,getRootStr(tree));
            out = concat(out,antiAntlr(tree->children[1]));
            out = concat(out,")");
            break;
        }
    return out;
}

//Check that the function is the correct length and correct string
bool isExit(char *line){
    return(strlen(line) == 5 &&strncmp(line,"(<>)", 4) == 0);
}

void quit(SP_TREE *tree, char *line,SP_HASH variables, SP_HASH_ERROR* msg,bool val){
    if(tree != NULL)
        spTreeDestroy(tree);
    if(variables != NULL)
        spHashDestroy(variables);
    free(line);
    free(msg);

    exit(val ? EXIT_SUCCESS : EXIT_FAILURE );
}

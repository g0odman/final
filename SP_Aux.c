#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "SP_Aux.h"
#include "SPHashTable.h"

/**
 *  Main function, parses given input and calculates result. Prints
 *  all necsesary things.
 */
void parse(char * line,SP_HASH variables, char *s){
	//check whether exit command:
    //make tree and validate that they were succesfull:
    SP_HASH_ERROR msg = 0;

    bool valid = true;
    SP_TREE *root = split(line,variables, &msg);
    //Generate string representation
    //evaluate:
    char * expr = antiAntlr(root);
    bracket(expr);
    if(root->type==ASSIGNMENT){
        char *variable = getRootStr(root->children[0]);
        valid = assign(root, variables, &msg);
        if(valid)
            sprintf(s, "%s\n%s = %.2f\n",expr,variable,spHashGetValue(variables, variable, &msg));
        else
            sprintf(s,"%s\nInvalid Assignment\n",expr);
    }
    else{
        double out =  spTreeEval(root,&valid,variables,&msg);
        if(valid)
            sprintf(s, "%s\nres = %.2f\n",expr, out);
        else
            sprintf(s,"%s\nInvalid Result\n",expr);
        free(expr);
    }
    spTreeDestroy(root);
    //In case function was successful
}

bool assign(SP_TREE *root, SP_HASH variables, SP_HASH_ERROR *msg){
    bool valid = true;
    char *variable = getRootStr(root->children[0]);
    double value=  spTreeEval(root->children[1],&valid,variables, msg);
    //Check that the function returned a valid result.
    if(valid){
        spHashInsert(variables,variable, value, msg);
        if(*msg != SUCCESS){
            printf("Unexpected error occured!\n");
            exit(EXIT_FAILURE);
        }
    }
    return valid;
}


SP_TREE *split(char *line,SP_HASH variables, SP_HASH_ERROR* msg){
    //Value for node
    SP_TREE *new = spTreeCreate();

    if(new == NULL){
        printf("Unexpected error occured!\n");
        exit(EXIT_FAILURE);
    }
    //j is the number of brackets seen, i is the current place
    int j = 1,i=1;
    while(j > 0){  //recursively parse children:
        if(line[i] == '(' && (++j) == 2){
        	//if closed brackets on child, parse it:
            if(!spTreePush(new,split(line+i,variables,msg))){
                //If parsing failed, exit function and check print value
                quit(new,line,variables,printf("Unexpected error occured!") >= 0);
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
    if(temp == NULL){
        printf("Unexpected error occured!\n");
        exit(EXIT_FAILURE);
    }
	strncpy(temp,line +1,length);
    temp[length] = '\0';
    if(!setValue(new,temp)){
        free(line);
        quit(new,line,variables,true);
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
        default ://Shouldn't reach here.
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
        default: //Other operations are always valid
            return true;
    }
}

double spTreeEval(SP_TREE *tree, bool * valid, SP_HASH variables, SP_HASH_ERROR* msg){

    double out = 0;
    //leaf, return value:
    switch(tree->type){
        case NUMBER:
            return atoi(getRootStr(tree));
        case VARIABLE: 
            out = spHashGetValue(variables, getRootStr(tree), msg);
            if(*msg != SUCCESS)
                *valid = false;
            return out; 
        case AVERAGE:
        case MEDIAN:
            return average(tree,valid,variables,msg);
        default:
            break;
    }


    //otherwise, calculate op on first child, first:
    out = spTreeEval(tree->children[0],valid,variables,msg);

    //In case of a unary operator
    if(tree->size == 1)
        return operate(0,out,tree->type,valid);

    //then continue recursively calculating children,
    for(int i=1; i < tree->size; i++){
        double temp = spTreeEval(tree->children[i], valid, variables, msg);
        out = operate(out,temp,tree->type,valid);
    }

    return out;
}
//Auxillary function, used by the sort in median
int compare(const void *a, const void *b){
    if(*((double*) a)>*((double*) b))
        return 1;
    else
        return (int)(*(double *)b-*(double *)a);
}

double average(SP_TREE *tree, bool *valid, SP_HASH variables, SP_HASH_ERROR *msg){
    if(tree->size ==1)
        return spTreeEval(tree->children[0],valid,variables,msg);
    double * arr = malloc(tree->size*sizeof(double));
    if(arr ==NULL){
        printf("Unexpected error occured!\n");
        exit(EXIT_FAILURE);
    }

    double ans = 0;
    for(int i = 0; i < tree->size; i++){
        arr[i] = spTreeEval(tree->children[i],valid,variables,msg);
    }
    if(tree->type == AVERAGE){
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

//Auxillary function, used to check if we should free in concat
bool cond(char *a){
    if(strlen(a) ==1 && (a[0] == ')' || a[0] == '(' || a[0] == ','))
        return false;
    return getType(a) == VARIABLE || getType(a) == NUMBER;
}
//Auxillary function ofr antiAntlr, concatenates two strings and,
//Depending on te result of cond, frees them
char * concat(char *a, char *b){
    char *out = (char *)calloc(1,sizeof(char)*(strlen(a)+strlen(b) +1));
    if(out == NULL){
        printf("Unexpected error occured!\n");
        exit(EXIT_FAILURE);
    }
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
        return "";
    //Make a fresh copy of the string
    if(tree->type == VARIABLE || tree->type == NUMBER){
        char *out = malloc((strlen(tree->value)+1)*sizeof(char));
        if(out ==NULL){
            printf("Unexpected error occured!\n");
            exit(EXIT_FAILURE);
        }
        strcpy(out,tree->value);
        return out;
    }
    char * out = "(";
    switch(tree->type){
        case AVERAGE:
        case MINIMUM:
        case MEDIAN:
        case MAXIMUM:
            out = concat(out,getRootStr(tree));
            out = concat(out,"(");
            for(int i = 0; i < tree->size;i++)
                out =concat(out,concat(antiAntlr(tree->children[i]),","));
            out[strlen(out)-1] = ')';
            break;
        default:
            //Unary operator, add parentheses
            if(tree->size ==1)
                out =  concat(concat(concat(out,getRootStr(tree)),antiAntlr(tree->children[0])),")");
            else{
                out = concat(out,antiAntlr(tree->children[0]));
                out = concat(out,getRootStr(tree));
                out = concat(out,antiAntlr(tree->children[1]));
            }
            break;
    }
    out = concat(out,")");
    return out;
}

void bracket(char * s){
    if(s[0] != '('){
        s = concat("(",s);
        s = concat(s,")");
    }
}
//Check that the function is the correct length and correct string
bool isExit(char *line){
    return(strlen(line) == 5 &&strncmp(line,"(<>)", 4) == 0);
}

void quit(SP_TREE *tree, char *line, SP_HASH variables, bool val){
    if(tree != NULL)
        spTreeDestroy(tree);
    if(variables != NULL)
        spHashDestroy(variables);
    if(line != NULL)
        free(line);
    exit(val ? EXIT_SUCCESS : EXIT_FAILURE );
}

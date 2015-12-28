#include <string.h>
#include "SP_Tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * Create a new empty Tree.
 *
 * @return
 *		A pointer to a new empty Tree, if any error occurred NULL is returned.
 */
SP_TREE* spTreeCreate() {
	
    //allocate pointer:
    SP_TREE *s;
    if((s = (SP_TREE*)malloc(sizeof(SP_TREE)))==NULL)
        return NULL;
    
    //initialize:
    s->children = malloc(sizeof(SP_TREE *)*MAX_CHILD_NUM);
    if(s->children ==NULL){
        free(s);
        return NULL;
    }
    memset(s->children, 0, MAX_CHILD_NUM); //set to NULL
    s->value = NULL;
    s->size = 0;
    return s;
}
    

/**
 * Free all allocation associated with the Tree.
 * @param
 * SP_TREE* Tree - Pointer to a Tree which will be deleted.
 * 					 After invoking spTreeDestroy, Tree will no longer be valid to use.
 * 					 If Tree==NULL nothing happens.
 */
void spTreeDestroy(SP_TREE* tree) {
	//check node isn't null:
    if(tree == NULL) { return; }
	
    for(int i =0; i<tree->size; i++){
        if(tree->children[i] != NULL){
        	spTreeDestroy(tree->children[i]);
        }
    }

    free(tree->children);
    if(tree->value != NULL){ free(tree->value); }
	free(tree);
}

/**
 * Pushes a child to the tree.
 * @param
 * SP_TREE* Tree - Pointer to a Tree into which the child will be inserted.
 *
 * SP_TREE *child - child to be inserted.
 *
 * @return -
 *          boolean indicating whether the push was succesful.
 */
bool spTreePush(SP_TREE* tree,SP_TREE *child) {
    if(child == NULL)
        return false;

    if(tree->size == MAX_CHILD_NUM)
        return false;

    tree->children[tree->size] = child;
    tree->size ++;

    return true;
}

/**
 * Returns a pointer to the string of the root node.
 *
 * @param
 * SP_TREE* Tree - Pointer to a Tree from which to extract string.
 * 
 * @return
 *              A copy of the substring representing the root.
 */
char * getRootStr(SP_TREE *tree){
    return tree->value;
}

/**
 * Returns a pointer to the index-th child of the root.
 *
 * @param
 * SP_TREE* Tree - Pointer to a Tree from which to take the child.
 *
 * int index - Child for which value is to be returned.
 * 
 * @return
 *              A pointer to the relevant child
 */
SP_TREE * getChildAtIndex(SP_TREE *tree,int index){
    return tree->children[index];
}

/**
 * Returns a copy of the string of the index-th child.
 *
 * @param
 * SP_TREE* Tree - Tree whose value is to be set.
 *
 * char *s - String to be inserted.
 * 
 * @return
 *              A boolean indicating whether the insertion was successful.
 */
bool setValue(SP_TREE *tree,char *s){
	//copy string:
    if(s == NULL || strlen(s)==0)
        return false;
    if((tree->value = malloc(strlen(s)+1)) == NULL)
        return false;
    strcpy(tree->value,s);

    //update type:
    tree->type = getType(s);

    return true;
}

/**
 * Recieve a string and check its type
 *
 *
 * @param
 * 		char * token - An input token. Checks if it is valid,
 * 				and if so then find its type.
 * @return
 *              The type of the token (as an enum).
 */
SP_TREE_TYPE getType(char *s){

	//Check if it is a number
    if(strlen(s)!=1 || (s[0] >= '0' && s[0] <= '9')) { return NUMBER; }

    //return the correct value
    switch(s[0]) {
        case '+'  :
             return PLUS;
        case '-'  :
             return MINUS;
        case '$'  :
             return DOLLAR;
        case '*'  :
             return MULTIPLICATION;
        case '/'  :
             return DIVISION;
        default : /* Optional */
             return UNKNOWN;
    }
}


#ifndef SP_TREE_H_
#define SP_TREE_H_
#include <stdbool.h>

/**
 * At any moment, the tree will have at most 10 children
 */
#define MAX_CHILD_NUM	10


/*************************************************
 * Definition of an element for the tree. The tree
 * element has a value and a type. The value is
 * not defined for all types beside NUMBER type. That
 * is if the type is NUMBER then the value field holds
 * the value of that number, otherwise the value is not defined.
 *************************************************/
typedef enum {
	PLUS,
	MINUS,
	MULTIPLICATION,
	DIVISION,
	DOLLAR,
	NUMBER,
	UNKNOWN
} SP_TREE_TYPE;

/**
 * This is a declaration of struct which represent a tree.
 * You will need to define the tree in SP_Tree.c
 * You can do so by copying the following code to SP_Tree.c:
 *
 * struct sp_tree_struct {
 * 		//Definition goes here
 * };
 */
/**
 * This struct represents a Tree.
 * 
 * 		int size - represents the amount of elements currently in Tree
 * 		SP_Tree_ELEMENT value - the value of this node
 * 		SP_Tree_ELEMENT *next - pointer to next element in linked list
 * 		int pointerCounter - number of pointers to this node, for delete.
 *
 */
typedef struct SP_TREE SP_TREE;
struct SP_TREE{
    SP_TREE_TYPE type;
    int size;
    char* value;
    struct SP_TREE **children;
};


/**
 * Create a new empty tree.
 *
 * Messages:
 * 		P_TREE_ERROR_ALLOCATION_FAILED - In case allocation failed.
 * 		SP_TREE_SUCCESS - In case creation of the tree succeeded.
 *
 * @param
 * 		SP_TREE_MSG* msg - Pointer which has the memory location where the message
 * 					   		will be stored. if msg==NULL then the function doesn't
 * 							set the value of *msg.
 * @return
 *		A pointer to a new empty tree, if any error occurred NULL is returned.
 */
SP_TREE* spTreeCreate();

/**
 * Free all allocation associated with the tree.
 * @param
 * SP_TREE* tree - Pointer to a tree which will be deleted.
 * 					 After invoking spTreeDestroy, tree will no longer be valid to use.
 * 					 If tree==NULL nothing happens.
 */
void spTreeDestroy(SP_TREE* tree);
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
bool spTreePush(SP_TREE* tree,SP_TREE *child);
/**
 * Returns a copy of the string of the root node.
 *
 * @param
 * SP_TREE* Tree - Pointer to a Tree from which to extract string.
 * 
 * @return
 *              A copy of the substring representing the root.
 */

char * getRootStr(SP_TREE *tree);

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
SP_TREE * getChild(SP_TREE *tree,int index);

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
bool setValue(SP_TREE *tree,char *s);

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
SP_TREE_TYPE getType(char *s);

#endif /* SP_TREE_H_ */

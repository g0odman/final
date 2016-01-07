#ifndef SP_Aux_H_
#define SP_Aux_H_
#include "SP_Tree.h"
#include "SPHashTable.h"


/**
 * Recieve a line and parse it
 *
 *
 * @param
 * 		string line - An input line, check if it is valid.
 * 				If so then parse it and print result, else
 * 				print error.
 * @return
 *              The result of the equation.
 */
bool parse(char * line, SP_HASH variables,char *out);

/**
 * create SP_TREE from string
 *
 *
 * @param
 * 		string line - An input line, split it according to 
 * 				LISP style brackets.
 * 				print error.
 * @return
 *              A SP_TREE representing the string.
 */
SP_TREE *split(char *line,SP_HASH variables, SP_HASH_ERROR* msg);

/**
 * Perform the given mathematical operation on the two input numbers.
 *
 *
 * @param
 * 		double x - The first number
 * @param
 * 		double y - the second number;
 * @param
 * 		SP_TREE_TYPE op - The operation to perform.
 * @param
 * 		bool *valid- A pointer to a boolean indicating
 * 		    whether or not the operation is valid.
 * @return
 *              The result of the mathematical operation
 */
double operate(double x,double y, SP_TREE_TYPE op, bool * valid);

/**
 * Check if a given mathematical operation is valid.
 *
 *
 * @param
 * 		double x - The first number
 * @param
 * 		double y - the second number;
 * @param
 * 		SP_TREE_TYPE op - The operation to perform.
 * @return
 *              Whether the operation was valid or not.
 */
bool isValid(SP_TREE_TYPE op, double x, double y);

/**
 * Recursively evaluate the tree.
 *
 *
 * @param
 * 		SP_TREE *tree - The tree to evaluate.
 * @param
 * 		bool *valid - A boolean checking whether the result was valid or not.
 * @return
 *          The result of the mathematical operation from the tree 
 *                  down.
 */
double spTreeEval(SP_TREE *tree, bool * valid, SP_HASH variables, SP_HASH_ERROR* msg);
/**
 * Checks if the input string was an exit string
 *
 * @param
 * 		char *line - A line to check.
 * @return
 *        A boolean indicating whether the strin was an exit code.
 */
bool isExit(char *line);

/**
 * Exits the program and frees all allocated memory while chcking
 * that exiting was indeed succesful
 *
 * @param
 *      SP_TREE *tree - A tree to destroy using spTreeDestroy.
 * @param
 * 		char *line - A string to free.
 * @param
 *      bool val - A boolean indicating whehter or not exiting was successful.
 */
void quit(SP_TREE *tree, char *line,SP_HASH variables, SP_HASH_ERROR* msg,bool val);

/**
 * If the input was an assignment and the expression to the right
 * of the equals sign was valid, assigns the value returned to
 * the variable.
 *
 * @param
 *      SP_TREE *root - The root of the expression to evaluate.
 * @param
 * 		char *variables - The hash table containing the 
 * 		variables assigned up to this point
 * @param
 *      SP_HASH_ERROR *msg - A pointer to a message.
 */
void assign(SP_TREE *root, SP_HASH variables,SP_HASH_ERROR *msg);

/**
 * If the operation was median or average, we need to perform 
 * different operations than other operations, this function 
 * returns either the median of the children or the average.
 *
 * @param
 *      SP_TREE *tree - The root of the expression to evaluate.
 * @param
 *      bool * valid - A boolean checking whether the operations
 *      up to this point were valid, and on exit contains that 
 *      value for this operation.
 * @param
 * 		char *variables - The hash table containing the 
 * 		variables assigned up to this point
 * @param
 *      SP_HASH_ERROR *msg - A pointer to a message.
 * @return
 *      The result of the operation.
 *
 */
double average(SP_TREE *tree, bool *valid,SP_HASH variables, SP_HASH_ERROR *msg);

/**
 * Parses a lisp-tree and returns a mathematical expression.
 *
 * @param
 *      SP_TREE *tree - The root of the expression to evaluate.
 * @return
 *      The mathematical expression in its normal form.
 *
 */
char *antiAntlr(SP_TREE *tree);

#endif /* SP_Aux_H_ */

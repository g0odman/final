/**
 * Reads command line arguments, checks whether they are valid.
 * If so continues, if not then calls getVaraibles and toPrint
 * In order to initialize variables and print to the right
 * FILE *, eiht stdout or the given file.
 *
 * @param
 *       int argc - the number of command line arguments.
 * @param
 *       char **argv - the command line arguments.
 * @param
 * 		SP_HASH *variables - A pointer to be updated to contain
 * 		    the hash table.
 * @param
 * 		FILE *fp - A pointer to be updated to the correct
 * 		        output stream.
 * @return
 *      A boolean indicating whether the program is valid.
 *
 */
bool init(int argc,char **argv,SP_HASH *variables, FILE **fp);
/**
 * Reads command line arguments, and checks whether a file
 * is given from which to read initialization to variables.
 * If given, load initialization into given hashtable of
 * variables
 *
 */
bool isValidCommandLineArgumentsList(int argc, char** argv);
/**
 * Reads given command line arguments, checks if the user input
 * a variable file, if so initializes the variables and returns
 * the new hash table at the address variables points to.
 */
bool getVariables(int argc, char **argv, SP_HASH *variables);

/**
 * Reads given command line arguments, checks if the user input 
 * an output file, if so checks whether it is open to writing
 * and returns it, else returns stdout.
 */
FILE *toPrint(int argc, char **argv);

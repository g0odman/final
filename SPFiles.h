
/**
 * Reads command line arguments, and checks whether a file
 * is given from which to read initialization to variables.
 * If given, load initialization into given hashtable of
 * variables
 *
 */
void getVariables(int argc, char **argv, SP_HASH *variables);

/**
 * Reads given command line arguments, and if given a filename
 * to write to, copies it to *filename and returns true. Otherwise
 * returns false.
 */
bool toPrint(int argc, char **argv, char **filename);

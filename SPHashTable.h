/*
 * spHashTable.h
 *
 *  This struct represents a hash table, containing strings and
 *  double values.
 */

#ifndef SPHASHTABLE_H_
#define SPHASHTABLE_H_

#include <stdbool.h>

//define struct SH_HASH in spHashTable.c
typedef struct SP_HASH_TABLE *SP_HASH;

typedef enum SP_HASH_ERROR{
	SUCCESS = 0,
	NOT_FOUND_ELEMENT = -1,
	DUPLICATE_ELEMENT = -2,
	ALLOC_FAILED = -3,
	INVALID_ARG = -4,
	UNKNOWN_FAILURE = -5,
} SP_HASH_ERROR;

/**
 * Returns a new hash table.
 *
 * If malloc fails, returns NULL. If msg==NULL, ignore. Otherwise
 * set msg to the following:
 * *msg = SUCCESS - if successful
 * *msg = ALLOC_FAILED - if fails to allocate
 *
 */
SP_HASH spHashCreate(SP_HASH_ERROR* msg);

/**
 * Frees all memory associated with the hash table. If h==NULL,
 * do nothing.
 */
void spHashDestroy(SP_HASH h);

/**
 * Returns the number of elements currently in the hash table,
 * or -1 if h==NULL.
 */
int spHashGetSize(SP_HASH h);

/**
 * Inserts a new element into the hash table h, with value val
 * and with key str. If an element exists with key str, replaces
 * its value with val.
 *
 * If msg != NULL, it will contain the following:
 * INVALID_ARG - if h == NULL str == NULL
 * ALLOC_FAILED - if fails to insert
 * UNKNOWN_FAILURE - if an unknown failure occurs
 * SUCCESS - if successful
 */
void spHashInsert(SP_HASH h, char* str, double val, SP_HASH_ERROR* msg);

/**
 * Returns the value of the element with key str in hash table h.
 *
 * If msg != NULL, it will contain the following values:
 * INVALID_ARG - if h==NULL or str==NULL
 * UNKNOWN_FAILURE - if a failure occurs.
 * NOT_FOUND_ELEMENT - if no element with key str exists.
 * SUCCESS - if successful
 */
double spHashGetValue(SP_HASH h, char* str, SP_HASH_ERROR* msg);

/**
 * Deletes element with key str in hash table h.
 *
 * If msg != NULL, sets it to the following:
 * INVALID_ARG - if h == NULL or str == NULL
 * UNKNOWN_FAILURE - if an unknown error occurs
 * ELEMENT_NOT_FOUND - if h contains no element with key str
 * SUCCESS - if successful
 */
void spHashDelete(SP_HASH h, char* str, SP_HASH_ERROR* msg);

#endif /* SPHASHTABLE_H_ */

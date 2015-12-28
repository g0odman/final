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
typedef struct SP_HASH_TABLE* SP_HASH;

typedef enum SP_HASH_ERROR{
	SUCCESS = 0,
	NOT_FOUND_ELEMENT = -1,
	DUPLICATE_ELEMENT = -2,
	ALLOC_FAILED = -3,
	INVALID_ARG = -4,
	UNKNOWN_FAILURE = -5,
} SP_HASH_ERROR;

/**
 * bla
 */
SP_HASH spHashCreate(SP_HASH_ERROR* msg);

/**
 * bla
 */
void spHashDestroy(SP_HASH h);

/**
 * bla
 */
int spHashGetSize(SP_HASH h);

/**
 * bla
 */
void spHashInsert(SP_HASH h, char* str, double val, SP_HASH_ERROR* msg);

/**
 * bla
 */
double* spHashGetValue(SP_HASH h, char* str, SP_HASH_ERROR* msg);

/**
 * bla
 */
void spHashDelete(SP_HASH h, char* str, SP_HASH_ERROR* msg);

#endif /* SPHASHTABLE_H_ */

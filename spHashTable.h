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
	FAILURE = -1,
} SP_HASH_ERROR;

/**
 * bla
 */
SP_HASH spHashCreate(SP_HASH_ERROR* msg);

/**
 * bla
 */
void spHashDestroy(SP_HASH h, SP_HASH_ERROR* msg);

/**
 * bla
 */
int spHashGetSize(SP_HASH h, SP_HASH_ERROR* msg);

/**
 * bla
 */
void spHashInsert(SP_HASH h, SP_HASH_ERROR* msg);

/**
 * bla
 */
double spHashGetValue(SP_HASH h, SP_HASH_ERROR* msg);

/**
 * bla
 *
 * true = element found
 * false = not found
 */
bool spHashDelete(SP_HASH h, SP_HASH_ERROR* msg);

#endif /* SPHASHTABLE_H_ */

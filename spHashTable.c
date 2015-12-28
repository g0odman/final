#include "spHashTable.h"
#include <stdlib.h>

#define FIRST_PRIME 571
#define COEFFICIENT_PRIME 31
#define NUMBER_OF_ENTRIES 100

struct SP_HASH_TABLE{
	SPList l;
};

//"private" hash function:
int hash_str(const char* s);

SP_HASH spHashCreate(SP_HASH_ERROR* msg);

void spHashDestroy(SP_HASH h, SP_HASH_ERROR* msg);

int spHashGetSize(SP_HASH h, SP_HASH_ERROR* msg);

void spHashInsert(SP_HASH h, SP_HASH_ERROR* msg);

double spHashGetValue(SP_HASH h, SP_HASH_ERROR* msg);

bool spHashDelete(SP_HASH h, SP_HASH_ERROR* msg);

int hash_str(const char* s){
	if(s == NULL){
		return -1;
	}
	else{
		int hash = FIRST_PRIME;
		for(const char* ind=s; (*ind)!='\0'; ind++){
			hash = COEFFICIENT_PRIME*hash + (int)(*ind);
			hash %= NUMBER_OF_ENTRIES;
		}
		return hash;
	}
}

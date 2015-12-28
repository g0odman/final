#include "spHashTable.h"
#include <stdlib.h>

#define FIRST_PRIME 571
#define COEFFICIENT_PRIME 31
#define NUMBER_OF_ENTRIES 100

struct SP_HASH_TABLE{
	SPList l[NUMBER_OF_ENTRIES];
	int size;
};

//"private" hash function:
int hash_str(const char* s);


SP_HASH spHashCreate(SP_HASH_ERROR* msg){
	//allocate memory, and check allocation
	SP_HASH toRet = (SP_HASH)malloc(sizeof(*SP_HASH));
	if(toRet==NULL){
		if(msg!=NULL){*msg=ALLOC_FAILED;};
		return NULL;
	}
	//allocate lists and check:
	for(int i=0; i<NUMBER_OF_ENTRIES; ++i){
		toRet->l[i] = listCreate();
		if(toRet->l[i]==NULL){
			if(msg!=NULL){ *msg=ALLOC_FAILED; };
			return NULL;
		}
	}
	toRet->size = 0;
	if(msg!=NULL){ *msg=SUCCESS; };
	return toRet;
}

void spHashDestroy(SP_HASH h){
	if(h == NULL){ return; };
	//free lists:
	for(int i=0; i<NUMBER_OF_ENTRIES; ++i){
		spListDestroy(h->l[i]);
	}
	free(h);
}

int spHashGetSize(SP_HASH h){
	if(h==NULL){ return -1; };
	return h->size;
}

void spHashInsert(SP_HASH h, char* str, double val, SP_HASH_ERROR* msg){
	int hash_index = hash_str(str); //the hash of the string
	SPListElement e = createElement(str, val); //create element
	if(e==NULL){
		if(msg!=NULL){ *msg = ALLOC_FAILED; };
		return;
	}

	//make sure no duplicates
	for(SPListElement curr=spListGetFirst(h->l[hash_index]);
			curr!=NULL; curr=spListGetNext(h->l[hash_index])){
		if(isElementStrEquals(curr, getElementstr(e))){
			if(msg!=NULL){ *msg = DUPLICATE_ELEMENT; };
			return;
		}
	}
	//insert:
	if(spListInsertFirst(h->l[hash_index], e) != SP_LIST_SUCCESS){
		if(msg!=NULL){ *msg = ALLOC_FAILED; };
		return;
	}
	h->size++;
	destroyElement(e); //free it, because a copy is used.
}

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

#include "SPHashTable.h"
#include "SPListElement.h"
#include "SPList.h"
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
	SP_HASH toRet = (SP_HASH)malloc(sizeof(*toRet));
	if(toRet==NULL){
		if(msg!=NULL){*msg=ALLOC_FAILED;};
		return NULL;
	}
	//allocate lists and check:
	for(int i=0; i<NUMBER_OF_ENTRIES; ++i){
		toRet->l[i] = listCreate();
		if(toRet->l[i]==NULL){
			if(msg!=NULL){ *msg=ALLOC_FAILED; };
			//if failed, free memory:
			for(int j=0; j++; j<i){ listDestroy(toRet->l[j]); }
			free(toRet);
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
		listDestroy(h->l[i]);
	}
	free(h);
}

int spHashGetSize(SP_HASH h){
	if(h==NULL){ return -1; };
	return h->size;
}

void spHashInsert(SP_HASH h, char* str, double val, SP_HASH_ERROR* msg){
	//check validity of args:
	if(str==NULL || h==NULL){
		if(msg!=NULL) {*msg=INVALID_ARG; };
		return;
	}

	int hash_index = hash_str(str); //the hash of the string
	SPListElement e = createElement(str, val); //create element
	if(e==NULL){
		if(msg!=NULL){ *msg = ALLOC_FAILED; };
		return;
	}

	//if duplicate, change value:
	for(SPListElement curr=listGetFirst(h->l[hash_index]);
			curr!=NULL; curr=listGetNext(h->l[hash_index])){
		if(isElementStrEquals(curr, getElementStr(e))){
			if(setELementValue(curr, val) != SP_ELEMENT_SUCCESS){
				if(msg!=NULL){ *msg = UNKNOWN_FAILURE; };
			} else {
				if(msg!=NULL){ *msg = SUCCESS; };
			}
			destroyElement(e);
			return;
		}
	}
	//insert:
	if(listInsertFirst(h->l[hash_index], e) != SP_LIST_SUCCESS){
		if(msg!=NULL){ *msg = UNKNOWN_FAILURE; };
		return;
	}
	h->size++;
	destroyElement(e); //free it, because a copy is used.
	if(msg!=NULL){ *msg = SUCCESS; };
}

double spHashGetValue(SP_HASH h, char* str, SP_HASH_ERROR* msg){
	//check validity:
	if(str==NULL || h==NULL){
		if(msg!=NULL) {*msg=INVALID_ARG; };
		return 0;
	}
	//search:
	int hash_index = hash_str(str); //calculate hash
	for(SPListElement curr=listGetFirst(h->l[hash_index]);
			curr!=NULL; curr=listGetNext(h->l[hash_index])){
		if(isElementStrEquals(curr, str)){
			//found:
			double* toRet = getElementValue(curr);
			if(toRet == NULL){
				if(msg!=NULL) {*msg=UNKNOWN_FAILURE; };
				return 0;
			}
			if(msg!=NULL) {*msg=SUCCESS; };
			int val = *toRet;
			free(toRet);
			return val;
		}
	}
	//not found:
	if(msg!=NULL) {*msg=NOT_FOUND_ELEMENT; };
	return 0;
}

void spHashDelete(SP_HASH h, char* str, SP_HASH_ERROR* msg){
	//check validity of args:
	if(str==NULL || h==NULL){
		if(msg!=NULL) {*msg=INVALID_ARG; };
		return;
	}

	int hash_index = hash_str(str);
	for(SPListElement curr=listGetFirst(h->l[hash_index]);
				curr!=NULL; curr=listGetNext(h->l[hash_index])){
		if(isElementStrEquals(curr, str)){ //found
			if(listRemoveCurrent(h->l[hash_index]) != SP_LIST_SUCCESS){
				if(msg!=NULL) { *msg=UNKNOWN_FAILURE; };
				return;
			}
			h->size--;
			if(msg!=NULL) { *msg=SUCCESS; };
			return;
		}
	}

	//not found:
	if(msg!=NULL) { *msg=NOT_FOUND_ELEMENT; };
	return;
}


//"private" hash function:
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

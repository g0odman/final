/*
 * spHashTableTester.c
 *
 *  Tests for spHashTable.c
 */
#include "spHashTable.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define FAIL(msg) do {\
		fprintf(stderr,"%s Line %d: %s", __FILE__, __LINE__, msg);\
		return false;\
	} while(0)

#define ASSERT_TRUE(expression) do { \
                if(!((expression))) { \
                        FAIL("expression is false :: "); \
                } \
        } while (0)

#define ASSERT_FALSE(expression) do { \
                if((expression)) { \
                        FAIL("expression is true  ::"); \
                } \
		} while (0)

#define RUN_TEST(f) do { \
			if(f()==true){ \
				fprintf(stderr, "%s  PASSS\n",#f);\
			}else{ fprintf(stderr, "%s  FAIL\n",#f);\
			} }while (0)

bool TEST1(){
	//make hash table
	SP_HASH_ERROR msg;
	SP_HASH h = spHashCreate(&msg);
	ASSERT_TRUE(h!=NULL && msg == SUCCESS);
	ASSERT_TRUE(spHashGetSize(h) == 0);

	return true;
}

int main(){
	RUN_TEST(TEST1);
	return 0;
}

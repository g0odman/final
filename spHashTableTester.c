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
	char* str1 = "yes";
	char* str2 = "no";
	double val;
	SP_HASH_ERROR msg;
	SP_HASH h = spHashCreate(&msg);
	ASSERT_TRUE(h!=NULL && msg == SUCCESS);
	ASSERT_TRUE(spHashGetSize(h) == 0);

	spHashInsert(h, str1, 13, &msg);
	ASSERT_TRUE(msg == SUCCESS && spHashGetSize(h) == 1);
	val = spHashGetValue(h, str1, &msg);
	ASSERT_TRUE(msg==SUCCESS && val==13);

	spHashInsert(h, str2, 12, &msg);
	ASSERT_TRUE(msg==SUCCESS && spHashGetSize(h) == 2);
	val = spHashGetValue(h, str2, &msg);
	ASSERT_TRUE(msg==SUCCESS && val==12);

	spHashInsert(h, str1, 1, &msg);
	ASSERT_TRUE(msg==SUCCESS && spHashGetSize(h) == 2);
	val = spHashGetValue(h, str1, &msg);
	ASSERT_TRUE(msg==SUCCESS && val==1);

	spHashDelete(h, str2, &msg);
	ASSERT_TRUE(msg==SUCCESS && spHashGetSize(h) == 1);
	val = spHashGetValue(h, str2, &msg);
	ASSERT_TRUE(msg==NOT_FOUND_ELEMENT);
	val = spHashGetValue(h, str1, &msg);
	ASSERT_TRUE(msg==SUCCESS && val==1);

	spHashDelete(h, str1, &msg);
	ASSERT_TRUE(msg==SUCCESS && spHashGetSize(h) == 0);
	val = spHashGetValue(h, str2, &msg);
	ASSERT_TRUE(msg==NOT_FOUND_ELEMENT);
	val = spHashGetValue(h, str1, &msg);
	ASSERT_TRUE(msg==NOT_FOUND_ELEMENT);

	spHashDestroy(h);

	return true;
}

int main(){
	RUN_TEST(TEST1);
	return 0;
}

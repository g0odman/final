all: 
	cd SP; make all
	$(MAKE) SPCalculator
SPCalculator: SPList.o SPListElement.o #Extends dependency list
	#Put your commands here

SPList.o: SPList.c SPList.h SPListElement.h
	gcc -std=c99 -Wall -Werror -pedantic-errors -c SPList.c

SPListElement.o: SPListElement.c SPListElement.h
	gcc -std=c99 -Wall -Werror -pedantic-errors -c SPListElement.c 

SPHashTable.o: SPList.o SPListElement.o SPHashTable.h SPHashTable.c
	gcc -std=c99 -Wall -Werror -pedantic-errors -c SPHashTable.c

SPHashTableTester.o: SPHashTable.o SPHashTableTester.c
	gcc -std=c99 -Wall -Werror -pedantic-errors -c SPHashTableTester.c

HashTester: SPHashTableTester.o SPHashTable.o SPListElement.o SPList.o
	gcc -std=c99 -Wall -Werror -pedantic-errors SPHashTableTester.o SPHashTable.o SPListElement.o SPList.o -o HashTester
	
clean:
	cd SP; make clean
	rm -fr SPList.o SPListElement.o #Extend to remove other object files you created.
	
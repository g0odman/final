all: 
	cd SP; make all
	$(MAKE) SPCalculator
SPCalculator: main.o SP_Aux.o SP_Tree.o SPHashTable.o SPFiles.o
	gcc -std=c99 -Wall -Werror -pedantic-errors  main.o SPFiles.o SP_Aux.o SP_Tree.o SPHashTable.o SPList.o SPListElement.o -o SPCalculator

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

main.o: main.c SP_Aux.h SP_Tree.h
	gcc -std=c99 -Wall -Werror -pedantic-errors -c main.c 

SP_Tree.o: SP_Tree.c SP_Tree.h
	    gcc -std=c99 -Wall -Werror -pedantic-errors -c SP_Tree.c

SP_Aux.o: SP_Aux.c SP_Aux.h SPHashTable.h
	    gcc -std=c99 -Wall -Werror -pedantic-errors -c -ggdb SP_Aux.c

SPFiles.o: SPFiles.c SPFiles.h SPHashTable.h
	    gcc -std=c99 -Wall -Werror -pedantic-errors -c SPFiles.c

clean:
	cd SP; make clean
	rm -fr SPList.o SPListElement.o SPHashTable.o SP_Aux.o SP_Files.o main.o SP_Tree.o
	

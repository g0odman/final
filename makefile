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
	
ex3: 	main.o SP_Aux.o SP_Tree.o SPHashTable.o
	gcc -std=c99 -Wall -Werror -pedantic-errors  main.o SP_Aux.o SP_Tree.o SPHashTable.o SPList.o SPListElement.o -o ex3

main.o: main.c SP_Aux.h SP_Tree.h
	gcc -std=c99 -Wall -Werror -pedantic-errors -c main.c 

SP_Tree.o: SP_Tree.c SP_Tree.h
	    gcc -std=c99 -Wall -Werror -pedantic-errors -c SP_Tree.c

SP_Aux.o: SP_Aux.c SP_Aux.h SPHashTable.h
	    gcc -std=c99 -Wall -Werror -pedantic-errors -c SP_Aux.c

clean:
	cd SP; make clean
	rm -fr SPList.o SPListElement.o #Extend to remove other object files you created.
	

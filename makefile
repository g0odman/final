all: 
	cd SP; make all
	$(MAKE) SPCalculator
SPCalculator: SPList.o SPListElement.o #Extends dependency list
	#Put your commands here

SPList.o: SPList.c SPList.h SPListElement.h
	gcc -std=c99 -Wall -Werror -pedantic-errors -c SPList.c

SPListElement.o: SPListElement.c SPListElement.h
	gcc -std=c99 -Wall -Werror -pedantic-errors -c SPListElement.c 
	
clean:
	cd SP; make clean
	rm -fr SPList.o SPListElement.o #Extend to remove other object files you created.
	
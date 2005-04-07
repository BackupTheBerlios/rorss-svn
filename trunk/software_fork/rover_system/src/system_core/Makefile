CC=g++ $(FLAGS)
CFLAGS=-thread
LIBS=-lpthread
INC=-I../

all: system_core.o utilities.o
	echo -n " `pwd`/system_core.o " >> ../../tmp/_LOCAL_OBJECTS
	echo -n "`pwd`/utilities.o" >> ../../tmp/_OBJECTS
	echo -n " $(LIBS) " >> ../../tmp/_LIBS
	echo "System-core done."

system_core.o: system_core.cpp system_core.h 
	$(CC) $(INC) system_core.cpp -c 

utilities.o: utilities.cpp utilities.h
	$(CC) $(INC) utilities.cpp -c
 
clean:
	rm -f *.o
	echo "Cleaned system core"

.PHONY: all clean

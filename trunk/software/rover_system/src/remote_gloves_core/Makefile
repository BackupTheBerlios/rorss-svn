CC=g++ $(FLAGS)
CFLAGS=-thread
LIBS=-lpthread
INC=-I../

all: remote_gloves_core.o
	echo -n " `pwd`/remote_gloves_core.o " >> ../../tmp/_REMOTE_OBJECTS
	echo -n " $(LIBS) " >> ../../tmp/_LIBS
	echo "Remote Gloves Core done."

remote_gloves_core.o: remote_gloves_core.cpp  
	$(CC) $(INC) remote_gloves_core.cpp -c 

clean:
	rm -f *.o
	echo "Cleaned remote gloves core"

.PHONY: all clean

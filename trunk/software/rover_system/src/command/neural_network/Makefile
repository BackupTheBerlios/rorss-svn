CC=g++  $(FLAGS)
PROJECTROOT=../../
LIBS= -l annie
INC=-I${PROJECTROOT}

all: neural_network.o 
	echo -n " $(LIBS) " >> ${PROJECTROOT}../tmp/_LIBS
	echo -n " `pwd`/neural_network.o " >> ${PROJECTROOT}../tmp/_OBJECTS
	echo -e "\tNeural Network Subsystem Done."

neural_network.o: neural_network.cpp neural_network.h
	$(CC) $(INC) -c neural_network.cpp

clean:
	rm -f *.o

tests:
	echo "Makefile not finished for tests"

.SILENT:
.PHONY: clean tests

CC=g++   $(FLAGS)
PROJECTROOT:=../../
INC:=-I${PROJECTROOT}
LIBS=

all: interpreter.o 
	echo -n " $(LIBS) " >> ${PROJECTROOT}../tmp/_LIBS
	echo -n " `pwd`/interpreter.o " >> ${PROJECTROOT}../tmp/_OBJECTS
	echo -e "\tInterpreter sub-system Done."

interpreter.o: interpreter.cpp
	$(CC) $(INC) -c interpreter.cpp

clean:
	rm -f *.o

.PHONY: all clean
.SILENT:

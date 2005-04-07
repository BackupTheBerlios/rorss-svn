CC=g++  $(FLAGS)
PROJECTROOT=../
LIBS=

all: interpreter neural_network command.o  
	echo -n " $(LIBS) "         >> ${PROJECTROOT}../tmp/_LIBS
	echo -n " `pwd`/command.o " >> ${PROJECTROOT}../tmp/_OBJECTS
	echo "Command Sub-system Done."


interpreter: 
	echo -e "\tInterpreter....  "
	cd interpreter && make 

neural_network:
	echo -e "\tNeural Network..."
	cd neural_network && make 


command.o: command.cpp command.h
	echo "building command.o "
	$(CC) -I $(PROJECTROOT) -c command.cpp

clean:
	rm -f *.o
	cd neural_network && make clean
	cd interpreter    && make clean
	echo "Cleaned Command Sub-system"

.PHONY: all clean neural_network interpreter
.SILENT:

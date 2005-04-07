CC=g++ $(FLAGS)
LIBS=-lfglove
PROJECTROOT=../
INC=-I${PROJECTROOT}

all: glove_data.o glove_listen.o hand_class.o network_functionality.o
	echo -n " $(LIBS) " >> ${PROJECTROOT}../tmp/_LIBS
	echo -n " `pwd`/glove_listen.o " >> ${PROJECTROOT}../tmp/_LOCAL_OBJECTS
	echo -n " `pwd`/glove_data.o " >> ${PROJECTROOT}../tmp/_REMOTE_OBJECTS
	echo -n " `pwd`/hand_class.o " >> ${PROJECTROOT}../tmp/_OBJECTS
	echo -n " `pwd`/network_functionality.o " >> ${PROJECTROOT}../tmp/_OBJECTS
	echo -e "\tGlove(local) Sub-system Done."

glove_listen.o: network_functionality.h glove_listen.cpp
	$(CC) $(INC) -c glove_listen.cpp

glove_data.o: glove.h glove_data.cpp
	$(CC) $(INC) -c glove_data.cpp

hand_class.o: hand_class.h hand_class.cpp
	$(CC) $(INC) -c hand_class.cpp
	
network_functionality.o: glove.h network_functionality.h network_functionality.cpp
	$(CC) $(INC) -c network_functionality.cpp
		
		
clean:
	rm -f *.o
	echo "Cleaned gloves"
	
.PHONY: all
.SILENT:

CC = g++  $(FLAGS)
SOURCES = micro_controller_comm.cpp micro_controller_comm_thread.cpp
LIBS    = -lpthread
PROJECTROOT =../
INC=-I${PROJECTROOT}
OBJS = $(SOURCES:*.cpp=*.o)

all: micro_controller_comm.o
	echo -n " `pwd`/micro_controller_comm.o `pwd`/micro_controller_comm_thread.o " >> ${PROJECTROOT}../tmp/_OBJECTS
	echo -n " $(LIBS) " >> ${PROJECTROOT}../tmp/_LIBS
	echo "Micro Controller Sub-system done."

micro_controller_comm.o: micro_controller_comm.cpp micro_controller_comm_thread.cpp micro_controller_comm.h
	$(CC) ${INC} -I${PROJECTROOT}system_core -c micro_controller_comm.cpp micro_controller_comm_thread.cpp

clean:
	rm -f *.o
	echo "Cleaned Micro Controller comm"

.PHONY: all clean
.SILENT:

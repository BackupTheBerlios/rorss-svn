
CC=g++  $(FLAGS)
INCLUDES = 
LIBS = 
OUTPUT_PATH =install_space
EXECUTABLE_NAME =rover_system
REMOTE_EXECUTABLE_NAME =remote_gloves
TMP=tmp/

all: sub_systems rover_onboard_system remote_gloves_client 
	echo "All Done."
	
initialize:
	rm -vf ${TMP}_LIBS
	rm -vf ${TMP}_*OBJECTS
	echo -n "$(LIBS) " >> ${TMP}_LIBS
	echo "INITIALIZED."

sub_systems: initialize
	cd src && make
	cd ..

rover_onboard_system: 
	echo "Building local Rover System.... "
	$(CC) -o $(OUTPUT_PATH)/bin/$(EXECUTABLE_NAME) `cat ${TMP}_OBJECTS` `cat ${TMP}_LOCAL_OBJECTS` `cat ${TMP}_LIBS`
	
remote_gloves_client: 
	echo "Building Remote Gloves Application...."
	$(CC) -o $(OUTPUT_PATH)/bin/$(REMOTE_EXECUTABLE_NAME) `cat ${TMP}_OBJECTS` `cat ${TMP}_REMOTE_OBJECTS` `cat ${TMP}_LIBS`

clean: initialize
	cd src && make clean

.SILENT:

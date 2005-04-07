
CC=g++  $(FLAGS)
INCLUDES = 
LIBS = 
PROJECTROOT = "../"

all:  command gloves micro_controller_comm vision trainer system_core remote_gloves_core 
	echo -e "\nAll Done."

local: all


gloves:
	echo -e "\nGloves sub-system..."
	export PROJECTROOT
	cd gloves/ &&  $(MAKE) 

command: 
	echo -e "\nCommand sub-system..."
	export PROJECTROOT
	cd command/ &&  $(MAKE) 
	
vision:
	echo -e "\nVision sub-system..."
	export PROJECTROOT
	cd vision/ &&  $(MAKE) 
	
micro_controller_comm:
	echo -e "\nMicro Controller sub-system..."
	export PROJECTROOT
	cd micro_controller_comm && $(MAKE) 

trainer:
	#echo -e "\nGlove Trainer builder under consturction... not built"
	#export PROJECTROOT
	#cd trainer/ && $(MAKE) $(MAKEFLAGS)

system_core:
	echo -e "\nSystem-core..."
	export PROJECTROOT
	cd system_core/ &&  $(MAKE) 

remote_gloves_core:
	echo -e "\nRemote Gloves Core..."
	export PROJECTROOT
	cd remote_gloves_core/ && $(MAKE) 

clean:
	for each in `ls -d */`; do cd $$each; make clean; cd ..; done
 

.PHONY: command gloves vision micro_controller_comm trainer system_core remote_gloves_core	
.SILENT:

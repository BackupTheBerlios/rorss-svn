# $Id$

BIN = run_rover
CC = sdcc
CC_FLAGS = -I/usr/share -I./ --iram-size 128
LIBS =

all:	gloves modules astronaut rover
	@echo "All done."

gloves:
	@echo "  Making (knitting) gloves"
	cd gloves
	make
	cd ..

modules:
	@echo "  Making (kernel) modules"
	cd modules
	make
	cd ..

astronaut:
	@echo "  Making (spawning) astronaut"
	cd astronaut
	make
	cd ..

rover:
	@echo "  Making rover"
	cd rover
	make
	cd ..

clean:
	@echo Cleaning the directory...
	cd gloves
	make clean
	cd ../modules
	make clean
	cd ../astronaut
	make clean
	cd ../rover
	make clean
	cd ..
	@echo Done.

pizza:
	@echo "Mmmmm..... delicious!  =P"

1337:
	@echo "Wheeeeeeee!!!!!!11!!111oneoneoneone!!"


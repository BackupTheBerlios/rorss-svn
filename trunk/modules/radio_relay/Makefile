# $Id$

BIN = run_modules
CC = sdcc
CC_FLAGS = -I/usr/share -I./ --iram-size 128
LIBS =
SOURCES = radio_relay.c
CLEAN_THESE = *.asm *.ihx *.lnk *.lst *.map *.mem *.rel *.rst *.sym # remove these files with a 'make clean'

all:	
	for f in $(SOURCES); do \
		$(CC) $(CC_FLAGS) $$f ; \
	done ;
	@echo "Done."

clean:	

        for f in `ls $(CLEAN_THESE)`; do \
		rm $$f ; \
	done ;
	@echo "Cleaned"

pizza:
	@echo "Mmmmm..... delicious!  =P"


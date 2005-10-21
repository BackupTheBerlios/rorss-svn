# $Id$

BIN = run_rover
CC = sdcc
CC_FLAGS = -I/usr/share -I./ --iram-size 128
LIBS =
SOURCES = comm.c run_rover.c

all:	
	for f in $(SOURCES); do \
		$(CC) $(CC_FLAGS) $$f ; \
	done ;
	@echo "Done."

clean:	
	@rm *.asm *.ihx *.lnk *.lst *.map *.mem *.rel *.rst *.sym
	@echo "Cleaned"

pizza:
	@echo "Mmmmm..... delicious!  =P"


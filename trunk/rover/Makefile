# $Id$

BIN = run_rover
CC = sdcc
CC_FLAGS = -I/usr/share -I./ -I../ --iram-size 128
CC_FLAGS_DBG = ${CC_FLAGS} --debug
LIBS =
SOURCES = comm.c pwm.c unistd.c # all the sources except the one containing main()
RELS = comm.rel pwm.rel unistd.rel # this line should be the same as the above, with 'rel' replacing 'c'
MAIN_PROG = run_rover.c # the source file containing main()
CLEAN_THESE = *.asm *.ihx *.lnk *.lst *.map *.mem *.rel *.rst *.sym *.adb *.cdb # remove these files with a 'make clean'

debug:
	# Compile sources
	for f in $(SOURCES); do \
		$(CC) -c $(CC_FLAGS_DBG) $$f || break ; \
	done ;
	
	# Link with main program
	$(CC) $(CC_FLAGS_DBG) $(MAIN_PROG) $(RELS)
	
	@echo "Done."

all:	
	# Compile sources
	for f in $(SOURCES); do \
		$(CC) -c $(CC_FLAGS) $$f || break ; \
	done ;
	
	# Link with main program
	$(CC) $(CC_FLAGS) $(MAIN_PROG) $(RELS)
	
	@echo "Done."

clean:	

	for f in `ls $(CLEAN_THESE)`; do \
		rm $$f ; \
	done ;		
	@echo "Cleaned"

pizza:
	@echo "Mmmmm..... delicious!  =P"


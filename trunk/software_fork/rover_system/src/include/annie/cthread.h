#ifndef CTHREAD_H
#define CTHREAD_H

#include "defines.h"
#include "Exception.h"

namespace annie	{
class  TerminatedException : Exception	{
public:
	TerminatedException() : Exception("Terminated during waiting on event") {}
};

char getLastKeyPressed();
char waitForKey();

/// also initializes video
void initControlThread(uint winW = 600, uint winH = 600);

/** 
 * nicely terminates CT
 * Must be called even if you don't want to terminate the thread prematurely
 */
void goodbyeControlThread();

///change the screen size
void changeWindowSize(uint winW, uint winH, bool wait=true);

///redraw the screen
void forceRedraw(bool wait=true);

class Video;
Video *getVideo();
}	//annie;
#endif

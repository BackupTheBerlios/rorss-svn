#ifndef _ann_
#define _ann_

//#include <pthread.h>
#include <annie/annie.h>
#include "gloves/glove.h" // for hand struct


#define INPUTS  14

using namespace annie;

struct classification_struct {
	VECTOR output;
};


	
class ann_class {

	friend void *ann_thread(void *none);
	protected:
		void updateInputs();
		pthread_mutex_t network_lock;                 // lock for locking out others when retrieveing data
		MultiLayerNetwork *neural_net;
		classification_struct classifications; 
		real input[INPUTS];
		hand_struct l_hand, r_hand;

		bool autoupdate;
		timespec cycle_delay;
		
		
	public:
		ann_class();
		~ann_class();
	
		void autoUpdateOn();
		void autoUpdateOff();
		bool autoUpdateState();
		void updateInputs(const hand_struct &hand);
		void getOutput( classification_struct &output );       // data retrieval function which automatically goes through locking process
		bool trylock();
		bool lock();
		bool unlock();
};

void *ann_thread(void *none);                        // started with each instance of ann_class... gathers the data

#endif


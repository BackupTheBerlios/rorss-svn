#ifndef _hand_class
#define _hand_class

#include <pthread.h>

struct hand_struct {
	float thumb;
	float index;
	float middle;
	float ring;
	float little;
	float pitch;
	float roll;
	bool  scaled;
	long unsigned int timestamp;
};
	
class hand_class {

	friend void glove_thread();
	private:
		pthread_mutex_t hand_lock;                 // lock for locking out others when retrieveing data
	
	public:
		hand_class();
		~hand_class();
		float thumb;
		float index;
		float middle;
		float ring;
		float little;
		float pitch;
		float roll;
		bool  scaled;
		long unsigned int timestamp;              // variable indicating when the data was last updated

		void get_hand( hand_struct &hand );       // data retrieval function which automatically goes through locking process
		void set_hand( hand_struct hand );
		void print();
		bool trylock();
		bool lock();
		bool unlock();

};
#endif

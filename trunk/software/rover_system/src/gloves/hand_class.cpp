#include "hand_class.h"	
#include <iostream>
using namespace std;
/* Class Function definitions */


hand_class::hand_class()
	{
	pthread_mutex_init( &hand_lock, NULL);
	pthread_mutex_unlock(&hand_lock);
	}

hand_class::~hand_class()
	{
	pthread_mutex_destroy( &hand_lock);
	}

void hand_class::get_hand( hand_struct &hand)
	{
	lock();
	hand.timestamp = timestamp;
	hand.thumb     = thumb;
	hand.index     = index;
	hand.middle    = middle;
	hand.ring      = ring;
	hand.little    = little;
	hand.pitch     = pitch;
	hand.roll      = roll;
	unlock();
	}

void hand_class::set_hand( hand_struct hand)
	{
	lock();
	timestamp	= hand.timestamp ;
	thumb		= hand.thumb     ;
	index		= hand.index     ;
	middle		= hand.middle    ;
	ring		= hand.ring      ;
	little		= hand.little    ;
	pitch		= hand.pitch     ;
	roll		= hand.roll      ;
	unlock();
	}
	

void hand_class::print()
	{
	lock();
	cout<<"T:"<<timestamp<<" Tmb:"<<thumb<<" ind:"<<index<<" mid:"<<middle<<" rng:"<<ring<<" lit:"<<little<<" pit:"<<pitch<<" rol:"<<roll<<endl;
	unlock();
	}

bool hand_class::trylock()
	{
	if (pthread_mutex_trylock( &hand_lock ) != 0 )
		return false;
	else
		return true;
	}
	
bool hand_class::lock()
	{
	pthread_mutex_lock( &hand_lock );
	}
	
bool hand_class::unlock()
	{
	pthread_mutex_unlock ( &hand_lock );	
	}

	

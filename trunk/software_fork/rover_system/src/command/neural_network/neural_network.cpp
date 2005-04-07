#include <iostream>
#include <unistd.h>
#include <pthread.h>

#include "neural_network.h"
#include "system_core/system_core.h"
#define null 0

using namespace std;
	
ann_class NNetwork; // these should be listed in glove_externs.h


void *ann_thread(void *none)
	{	
		
/* Main loop */		
	while(true)	
		{
		if( NNetwork.autoupdate )
			{
			Left_Hand.get_hand(NNetwork.l_hand);
			Right_Hand.get_hand(NNetwork.r_hand);
			//NNetwork.updateInputs(NNetwork);
			NNetwork.lock();
			NNetwork.classifications.output = NNetwork.neural_net->getOutput(NNetwork.input);
			NNetwork.unlock();
			}
		nanosleep(&NNetwork.cycle_delay,NULL);
		}
/* Main Loop end */
	}

	
	
	
/* Class Function definitions */


ann_class::ann_class()
	{
	pthread_mutex_init( &network_lock, NULL);
	char filename[]="../data/neuralnetwork.net";
	neural_net = null;
	autoupdate=true;
	cycle_delay.tv_sec = 0;
	cycle_delay.tv_nsec = 2000000;
	
	try
		{
		neural_net =  new MultiLayerNetwork(filename);
		}
	catch(...)
		{
		cerr<<"Failed to open "<<filename<<" !"<<endl;
		}
	}

ann_class::~ann_class()
	{
	pthread_mutex_destroy( &network_lock);
	}

void ann_class::updateInputs( const hand_struct &hand)
	{
	lock();
	input[0]=hand.thumb;
	input[1]=hand.index; 
	input[2]=hand.middle;
	input[3]=hand.ring;
	input[4]=hand.little;
	input[5]=hand.index;
	input[6]=hand.index;	
	unlock();
	}

void ann_class::getOutput( classification_struct &output)
	{
	lock();
	output.output = classifications.output;
	unlock();
	}
	
bool ann_class::trylock()
	{
	if (pthread_mutex_trylock( &network_lock ) != 0 )
		return false;
	else
		return true;
	}
	
bool ann_class::lock()
	{
	pthread_mutex_lock( &network_lock );
	}
	
bool ann_class::unlock()
	{
	pthread_mutex_unlock ( &network_lock );	
	}

	

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include "micro_controller_comm.h"
#include "micro_controller_comm_externs.h"

/* Class Function definitions */
mobil_class::mobil_class (void)
{
	int i;
	pthread_mutex_init (&mobil_lock, NULL);  // initializes the thread
	// Initializes the devices.
	// Sets values for mode and magnitude to be zero.
	for(i=0; i<NUMDEVICES ; i++)
		{

		local[i].mode      = remote[i].mode      = 0;  
		local[i].magnitude = remote[i].magnitude = 0;

		if(i >= 0x7 && i <= 0xC )                // encoders are not writable
			local[i].writable  = remote[i].writable  = false ;
		else
			local[i].writable  = remote[i].writable  = true ;
		}
}

mobil_class::~mobil_class (void)
{
  pthread_mutex_destroy (&mobil_lock);
}

void mobil_class::get_devices(device_t *&devices)
{
	static int i;
	lock ();
	// Assigns values for the devices array
	// Sets the mode magnitute and whether or not its writable.
	for(i=0; i<NUMDEVICES; i++)
		{
		devices[i].mode      = local[i].mode;    
		devices[i].magnitude = local[i].magnitude;
		devices[i].writable  = local[i].writable;
		}
	unlock();
}

void mobil_class::get_device (device_t  &device, device_id id)
{
	lock ();
	device.mode      = local[id].mode;
	device.magnitude = local[id].magnitude;
	unlock();
}

// Checks to see if command is locked, otherwise sends code somewhere else
bool mobil_class::trylock (void)
{
  if (pthread_mutex_trylock (&mobil_lock) != 0)
    {
      return false;
    }
  else
    {
      return true;
    }
}


bool mobil_class::lock (void)
{
  pthread_mutex_lock (&mobil_lock);
}

bool mobil_class::unlock (void)
{
  pthread_mutex_unlock (&mobil_lock);
}


/*
filename: system_core.cpp

description: int main

*/
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "micro_controller_comm.h"

char *Device_Port1 = "/dev/ttyS0" ;
char *Device_Port2 = "/dev/ttyS1" ;

int main(int argv, char **argc)
{
	pthread_t micro_controller_comm_thread_id;

	pthread_create( &micro_controller_comm_thread_id,       NULL, micro_controller_comm_thread,       NULL );

	while (true)
		{}

	return 0;
}

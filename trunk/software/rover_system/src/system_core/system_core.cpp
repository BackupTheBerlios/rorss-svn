/*
filename: system_core.cpp

description: int main

*/
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include "system_core.h"
#include "gloves/glove.h"
#include "command/interpreter/interpreter.h"
#include "command/command.h"

using namespace std;


int main(int argv, char **argc)
{

	pthread_t glove_thread_id;
	pthread_t trainer_app_thread_id;
	pthread_t command_module_thread_id;
	pthread_t micro_controller_comm_thread_id;
	pthread_t vision_module_thread_id;
	cout<<"Rover Software System version 0.5 built last modified 2004.11.03"<<endl;
	cout<<"Copyright 2004 Penn State Mars Society"<<endl;
	cout<<endl;
	cout<<"starting glove data module"<<endl;
	pthread_create( &glove_thread_id,       NULL, glove_thread,       NULL );
	//cout<<"starting glove trainer module..."<<endl;
	//pthread_create( &trainer_app_thread_id, NULL, trainer_app_thread, NULL );
	cout<<"starting microcontroller communications module..."<<endl;
	pthread_create(&micro_controller_comm_thread_id, NULL, micro_controller_comm_thread, NULL );
	//cout<<"starting vision module..."<<endl;
	//pthread_create(&vision_module_thread_id, NULL, vision_module_thread, NULL );
	cout<<"starting command module..."<<endl;
	pthread_create(&command_module_thread_id, NULL, command_module_thread, NULL );
		
	

	//pthread_join(trainer_app_thread_id,NULL);
	pthread_join(command_module_thread_id,NULL);
	pthread_join(micro_controller_comm_thread_id,NULL);
	pthread_join(glove_thread_id,NULL);
	//pthread_join(vision_module_thread_id,NULL);
	return 0;
}

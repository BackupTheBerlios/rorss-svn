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
#include "../gloves/src/glove.h"
#include "../command/interpreter/src/interpreter.h"

using namespace std;


int main(int argv, char **argc)
{

	pthread_t glove_thread_id;
	pthread_t remote_glove_thread_id;

	
	pthread_create( &glove_thread_id,       NULL, glove_thread,       NULL );
	pthread_create( &remote_glove_thread_id, NULL, interpreter_thread, NULL );
	cout<<"4"<<endl;

	while (true)
		{}

	return 0;
}

#include "system_core/system_core.h"
#include "interpreter/interpreter.h"

void *command_module_thread(void *none)
	{
	pthread_t ann_thread_id;
	pthread_t interpreter_thread_id;

//	pthread_create( &ann_thread_id,          NULL, ann_thread,          NULL );
	pthread_create( &interpreter_thread_id,  NULL, interpreter_thread,  NULL );

//	pthread_join(ann_thread_id, NULL);
	pthread_join(interpreter_thread_id, NULL );
	}

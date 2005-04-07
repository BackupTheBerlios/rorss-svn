
#include "gloves/glove.h"
#include "gloves/glove_externs.h"
#include "gloves/network_functionality.h"

using namespace std;


int main(int argv, char **argc)
{

	pthread_t glove_thread_id;
	pthread_t net_out_thread_id;
	
	pthread_create( &glove_thread_id,   NULL, glove_thread, NULL );
	pthread_create( &net_out_thread_id, NULL, net_out_thread, NULL );

	pthread_join( glove_thread_id,NULL);
	pthread_join( net_out_thread_id,NULL);

	return 0;
}

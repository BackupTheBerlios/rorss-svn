#include "network_functionality.h"
#include <iostream>
using namespace std;

hand_class Left_Hand, Right_Hand ; // these should be listed in glove_externs.h

// for local (receiving)
void *glove_thread(void* arg)
	{
	using namespace local_tcp_glove_ns;
	listen_initialize_connection();
	while(true)
		{
		receive_and_update(&Left_Hand);
		receive_and_update(&Right_Hand);
		}
	}

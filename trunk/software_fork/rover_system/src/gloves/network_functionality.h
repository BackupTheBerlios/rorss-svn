#ifndef _network_functionality
#define _network_functionality
#include "system_core/system_core.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <vector>
#include <fstream>
#include <iostream>
#include "glove.h"
#include "glove_externs.h"


namespace remote_tcp_glove_ns
{
	extern int    connect_socket;
	extern struct sockaddr_in destination_info;
	//struct hand_struct l_hand;
};

namespace local_tcp_glove_ns
{
	extern int       listen_socket, new_socket;
	extern socklen_t sin_size     ;
	extern struct    sockaddr_in  listen_info  ;
	extern struct    sockaddr_in  new_info     ;
};	

void remote_initialize_connection();
void send(struct hand_struct *hand_local);
void receive_and_update(hand_class *hand);
void listen_initialize_connection();
void *net_out_thread(void *arg);
#endif

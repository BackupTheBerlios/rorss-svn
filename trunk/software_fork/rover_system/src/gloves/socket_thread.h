#ifndef __SOCKET_THREAD_H
#define __SOCKET_THREAD_H

#include "../src/glove.h"

extern bool isequal(hand_class h1, hand_class h2);
extern void copy(hand_class h1, hand_class h2);

class server_thread 
{
private: hand_class temp_Left_Hand, temp_Right_Hand;
         char serv_address[16];
         int backlog;
         int portnumber;
         int accept_val;
         friend void *serverrun(void*);
public:  server_thread(char serv_addr[] ,int portnumber, int backlog = 2);
         ~server_thread();
};

class client_thread
{
private: hand_class temp_Left_Hand, temp_Right_Hand;
         char serv_address[16];
         int portnumber;
         int sock_val;
         friend void *clientrun(void*);
public:  client_thread(char serv_addr[],int portnumber);
         ~client_thread();
};

#endif

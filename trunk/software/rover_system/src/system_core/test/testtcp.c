#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>


int main(int argc, char **argv)
{
	FILE         listen_socket;
	FILE         new_socket   ;
	sockaddr_in  listen_info  ;
	sockaddr_in  new_info     ;
	char[255]    buffer       ;
	
	listen_info.sin_family      = AF_INET;         // host byte order
	listen_info.sin_port        = htons(1025);     // short, network byte order
   listen_info.sin_addr.s_addr = inet_addr("127.0.0.1");	

	
	listen_socket = socket(AF_INET, SOCK_STREAM, 0);
	
   bind(listen_socket, 
		 (struct sockaddr *)&listen_info, 
		  sizeof(struct sockaddr));
	memset(&(listen_info.sin_zero), '\0', 8);      // zero the rest of the struct

	listen(listen_socket,5);
	
	new_socket = accept(listen_socket, (struct sockaddr *)&new_info,sizeof(struct sockaddr_in));
	recv(new_socket, (void *)buffer, 255,0);
	printf("received: %s",buffer);
	exit();
	
}
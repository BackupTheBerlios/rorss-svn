#include "network_functionality.h"
#include "hand_class.h"
#include <netdb.h>

/*//////////////////////////////
//
//    File: Network_functionality.cpp
//    Description:
//             Definitions of functions to handel network contections to the gloves
//
//
//
*/


#define null 0
#define TRUE  1
#define FALSE 0
#define DEFAULT_PORT=4444
#define DEFAULT_ADDRESS="127.0.0.1"




using namespace std;
//using namespace boost;

namespace remote_tcp_glove_ns
{
	int    connect_socket;
	struct sockaddr_in destination_info;
};

namespace local_tcp_glove_ns
{
	int       listen_socket, new_socket;
	socklen_t sin_size     ;		//necessary here?
	struct    sockaddr_in  listen_info  ;
	struct    sockaddr_in  new_info     ;
};


//maintains output
void *net_out_thread(void *arg)
	{
	using namespace remote_tcp_glove_ns;
	struct hand_struct lhand_fromglove,rhand_fromglove;
	remote_initialize_connection();

	while(true)
		{
		Left_Hand.get_hand(lhand_fromglove);
		Right_Hand.get_hand(rhand_fromglove);
		send(&lhand_fromglove);
		send(&rhand_fromglove);
		//delay
		}
	}

// remote connection
void remote_initialize_connection()
	{
	using namespace remote_tcp_glove_ns;

	char string_port[F_NAME_LEN]="";
	char string_address[F_NAME_LEN]="";
	char default_address[]=DEFAULT_ADDRESS;
	char *address;
	int  port;

	if( null == get_var_from_file("../data/config", "PORT", string_port, F_NAME_LEN) ) //if port data file not found
		port = DEFAULT_PORT;
	else
		port = atoi(string_port);

	if( null == get_var_from_file("../data/config", "IPADDRESS", string_address, F_NAME_LEN) ) //if IP data file not found
		address = default_address;
	else
		address = string_address;


	connect_socket = socket(AF_INET, SOCK_STREAM, 0);  //creates new socket

	if( -1 == connect_socket )
		cerr<< "Error creating socket:"<<strerror(errno) <<endl;

	destination_info.sin_family      = AF_INET;            // AF_INET is TCP/IP
	destination_info.sin_port        = htons(port);        // converts port from host byte order to network byte order
	destination_info.sin_addr.s_addr = inet_addr(address); // converts from string of standard notation to network byte order
	memset(&(destination_info.sin_zero), '\0', 8);         // fill the rest of the struct with null

	cerr<<"Attempting to connect to host "<<address<<" on port "<<port;
	if( 0 >= connect(connect_socket, (struct sockaddr *)&destination_info, sizeof(struct sockaddr_in) ) ) // try to connect to remote listening port
		cerr<<"Error connecting to host: "<<strerror(errno)<<endl;
	}

void send(struct hand_struct *hand_local)	//sends information through socket
	{
	using namespace remote_tcp_glove_ns;

	static char         *hand_loc_char_ptr;
	hand_loc_char_ptr=(char *)hand_local;
	static unsigned int remaining;
	static unsigned int amt_sent;

	for( remaining = sizeof(struct hand_struct); remaining > 0;)
		{
		if ( -1 == (amt_sent = send(connect_socket, &hand_loc_char_ptr[sizeof(struct hand_struct)-remaining], remaining, 0)))
			{
			cerr<<"failed to read"<<endl;
			break;
			}

		remaining -= amt_sent;
		}
	fsync();//flushes buffer
	return;
	}





//for local (receiving)
void listen_initialize_connection()
	{
	using namespace local_tcp_glove_ns;

	char string_port[F_NAME_LEN]="";
	int  port;
	if( null == get_var_from_file("../data/config", "PORT", string_port, F_NAME_LEN) )
		port = DEFAULT_PORT;
	else
		port = atoi(string_port);

	listen_info.sin_family      = AF_INET;             // Internet protocal family
	listen_info.sin_port        = htons(port);         // which port to listen on
	listen_info.sin_addr.s_addr = htonl(INADDR_ANY);
	memset(&(listen_info.sin_zero), '\0', 8);          // zero the rest of the struct

	listen_socket = socket(AF_INET, SOCK_STREAM, 0); 	//Internet socket, tcpip

	if( -1 == listen_socket )
		cerr<< "Error getting valid socket:"<<strerror(errno)<<endl;

	if( -1 == bind(listen_socket, (struct sockaddr *)&listen_info,  sizeof(struct sockaddr)) )
		cerr<< "Error binding socket: "<<strerror(errno)<<endl;

	if( -1 == listen(listen_socket,5) )
		cerr<<"Error setting socket to listen: "<< strerror(errno)<<endl;

	sin_size = sizeof(struct sockaddr_in) ;

	cerr<<"Listening on port "<<port<<endl;
	new_socket = accept(listen_socket, (struct sockaddr *)&new_info, &sin_size );
	if( -1 == new_socket )
		cerr<<"Error accepting new connection: "<< strerror(errno) <<endl;
	else
		cerr<<"Accepting new socket"<<endl;

	}

void receive_and_update(hand_class *hand)
	{
	using namespace local_tcp_glove_ns;

	static char         *hand_char_ptr = (char *)(new hand_struct);
	static unsigned int  remaining;  // amount of data left to read
	static unsigned int  amt_sent;  // temporary for amount left

	for( remaining_data = sizeof(struct hand_struct); remaining_data > 0;)
		{
		if ( -1 == (amt_sent = recv(new_socket, &hand_char_ptr[sizeof(struct hand_struct)-remaining], remaining, 0)))
			{cerr<<"failed to read"<<endl; break; }
		remaining -= amt_sent;
		}

	hand->set_hand(*((hand_struct*)hand_char_ptr));
	return;
	}





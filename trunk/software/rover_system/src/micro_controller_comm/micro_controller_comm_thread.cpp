#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/timeb.h>
#include <iostream>
#include "micro_controller_comm.h"
#include "../system_core/system_core.h"
#include "micro_controller_comm_thread.h"
using namespace std;
timeb old_time;
timeb new_time;
int epoch=0;

mobil_class micro_controller_comm;

/*
start process_input  thread
start process_output thread
	
	process_input thread
	loop:
		wait untill begin-packet-byte arrives (0xff)
		if next bytes valid...(below 0xf and 0xff)
			then update local var
		else
			return to waiting for next begin-packet-byte
		delay

	process_ouput thread
	loop:
		loop through all devices
			if remote var != local var
				send packet to "fix it"
		delay

*/

// Name: serial_io_ns
// Creates a namespace (class like object) for the serial input/output
// The purpose is this acts like a class giving functions access to the
// data and methods, without making them global.

namespace serial_io_ns
{
	int  fd_serial_port; // stores the serial port for the file descripter
	int  bytes_available;  // stores the bytes available to the in the serial buffer
	struct termios oldtio,newtio;  // creates two terminal input/output
					// structures old and new to save the old settings for the serial port
};
// Pointers for debugging
void* test_input(void *none);
void* keyboard_input(void *arg); // allows you to send specific numbers (build the packets by hand)


void* micro_controller_comm_thread(void *arg)
{
	char device_name[F_NAME_LEN]; // Stores the path to the device file
	get_var_from_file("../data/config", "HC12_PORT", device_name , F_NAME_LEN); // get the serial port from the config file
	
	if(device_name == NULL)
	{
		cout<<"falling back on default for HC12_PORT: /dev/ttyS0"<<endl;
		initialize_serial_port("/dev/ttyS0");  // "dev/ttySO" is first serial port on the computer
	}
	else
		initialize_serial_port(device_name);

	
	//initialize_serial_port(device_name);
	// Creates two threads read and write id, these threads store the description
	pthread_t read_thread_id; 
	pthread_t write_thread_id;
	//pthread_t keyboard_thread_id;
	
	// pthread_create starts the thread
	// pthread_create  Parameters are pointers to (description, function attribs, function, funtion  argument)
	pthread_create( &read_thread_id,     NULL, read_thread,       NULL );
	pthread_create( &write_thread_id,    NULL, write_thread,       NULL );
	//pthread_create( &keyboard_thread_id, NULL, keyboard_input,       NULL );

	// pthread_join pauses until the threads are finished execution
	// parameters are pointers to the thread description and a variable to hold the return value
	pthread_join(read_thread_id, NULL);
	pthread_join(write_thread_id, NULL );
	//pthread_join(keyboard_thread_id, NULL );
}


void* read_thread(void *arg)
{
	using namespace serial_io_ns;
	unsigned char temp; 

	unsigned char next_byte;
	unsigned char device;
	unsigned char mode;
	unsigned char magnitude;
	
	while(true)
	{
		do	next_byte = get_byte();
		while (next_byte != 0xff);  // scrolls through the input until it finds the new packet marker
		
		next_byte = get_byte();
		// separating the fields of the first byte of the packet into device and mode
		device    = next_byte>>4; 
		mode      = next_byte&0x0f;
		
		magnitude = get_byte();
		
		if( device != 0xf && mode != 0xf && magnitude != 0xff ) // check for the validity of packet fields
		{
			cerr<<"device is:\t"   <<(int)device<<endl;
			cerr<<"mode is:\t"     <<(int)mode<<endl;
			cerr<<"magnitude is:\t"<<(int)magnitude<<endl;
			micro_controller_comm.remote[device].mode      = mode;
			micro_controller_comm.remote[device].magnitude = magnitude;
		}
		else // out put an error message
		{
			if( device == 0xf )
				cerr<<"invalid device "<<device<<endl;
			if( mode   == 0xf )
				cerr<<"invalid mode "<<mode<<endl;
			if( magnitude == 0xff )
				cerr<<"invalid magnitude "<<magnitude<<endl;
			
			cerr<<"Reseting read position, waiting for next packet"<<endl;
			//error?
		}
		//some delay here
	}
}

void *write_thread(void *arg)
{
	int i;
	
	while(true)
	{
		for(i=1;i<NUMDEVICES;i++)
		{
			
			if(   (micro_controller_comm.local[i].mode      != micro_controller_comm.remote[i].mode ) 
				|| (micro_controller_comm.local[i].magnitude != micro_controller_comm.remote[i].magnitude) ) 
			{
					
					if ( ! micro_controller_comm.remote[i].writable ) // if its not writable you have no business changing it... 
					{                                 // putting it back the way it was
							cout<<"Got new values for feedback device"<<i<<endl;
							cout<<"mode="<<(int)micro_controller_comm.remote[i].mode<<"   magnitude="<<
												(int)micro_controller_comm.remote[i].magnitude<<endl<<endl;
							micro_controller_comm.local[i].mode      = micro_controller_comm.remote[i].mode;
							micro_controller_comm.local[i].magnitude = micro_controller_comm.remote[i].magnitude;
							micro_controller_comm.local[i].writable  = micro_controller_comm.remote[i].writable;
					}
					else
					{
							//cout<<"Difference detected in device "<<i<<endl;
							//cout<<"Got     mode="<<(int)micro_controller_comm.remote[i].mode<<"\t  mag="<<
													(int)micro_controller_comm.remote[i].magnitude<<endl;
							//cout<<"Sending mode="<<(int)micro_controller_comm.local[i].mode<< "\t  mag="<<
												(int)micro_controller_comm.local[i].magnitude<<endl<<endl;

							epoch++; // Debugging variable to find out the rate of packet transmission
							
							write_packet(i, micro_controller_comm.local[i].mode, 
												 micro_controller_comm.local[i].magnitude);
					}
			}
			else
			{
					//if(epoch > 0)
					//	{
					//	cout<<epoch<<" loops untill change registered"<<endl;
					//	epoch= 0 ;
					//	}
			}
		}
		
		
		// some delay here
	}
}






// retrieves a new packet

unsigned char get_byte()    //unsigned char &retchar)
{
	static unsigned char retchar;
	using namespace serial_io_ns;
	read(fd_serial_port, &retchar, 1);
	//cerr<<retchar<<" thats it"<<endl;
	return retchar;
}


void write_packet		(unsigned char device, 
							 unsigned char mode, 
							 unsigned char magnitude)
{
	using namespace serial_io_ns;
	static unsigned char buff[3]; // storage space to write the buffer into
	static timespec cycle_delay;  // stores the length of the delay
	cycle_delay.tv_sec = 0;
	cycle_delay.tv_nsec = 100000;

	// keep it the program from interpreting the magnitude as a marker 
        if (magnitude == 0xff) //reserve ff for packet marker
                magnitude = 0xfe;
	
	buff[0]= 0xff;  // marker bit
	buff[1]= (device<<4) | (mode & 0x0f); // combining the two variables into a single bit
	buff[2]= magnitude; // stores the magnitude
	
	if (!fd_serial_port)
	{
		cerr<<"fd not open"<<endl;
		return;
	}

	// if both values are valid start writing
	if ( (device < 16) && (mode < 16) )
	{
		//write(fd_serial_port, buff, 3);
		for(int i=0; i<3;i ++)
		{
			write(fd_serial_port, buff+i, 1);
			//printf("Byte #%i is : %i\n",i,(char)(*(buff+i)));
			nanosleep(&cycle_delay,NULL);
		}
		printf(".");
	}
	else
	{
		cerr<<"invalid device or mode. Not sending data"<<endl;
	}
	return;
}




int initialize_serial_port(const char *serial_port)
{
	using namespace serial_io_ns;
	
	
	/* 	Open serial device for reading and writing and not as controlling*/
	fd_serial_port = open(serial_port, O_RDWR | O_NOCTTY ); //| O_NDELAY );
	
	if (fd_serial_port <0) 
	{
		cerr<<"Exiting on fail to open microcontroller's serial port: "<<flush;
		perror(serial_port); // translates error code into an error string
		exit(-1); // exits out of the entire program
	}
	
	tcgetattr(fd_serial_port,&oldtio); /* save current port settings */
	

	fcntl(fd_serial_port, F_SETFL, FASYNC);     // set to asynchronous mode
	//fcntl(fd_serial_port, F_SETFL, FNDELAY);        // would be non blockingmode; 
	
	bzero(&newtio, sizeof(newtio));  // sets the entire structure to zero
	// input and output speed
	cfsetispeed(&newtio, BAUDRATE);             // posix baud compliance
	cfsetospeed(&newtio, BAUDRATE);             // posix baud compliance
	newtio.c_cflag = BAUDRATE                   // baud rate duh
						| CRTSCTS                    // hardware flow control
						| CS8                        // 8 data bits
						| CLOCAL                     // do not...
						| CREAD                      // monopolize serial port
						| PARENB                     // use parity bit
						& ~PARODD                    // even parity (not odd)
						& ~CSTOPB ;                  // one stop bit  (not 2 stop bits)
	newtio.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);  // set to raw input
   newtio.c_iflag = INPCK                      // enable parity checking
						| IGNPAR ;                    // ignore parity errors
						//| ISTRIP
						//| IGNBRK;                    // ignore break
   newtio.c_oflag &= ~OPOST;                   // raw output
	newtio.c_lflag = 0;                         // set input mode (non-canonical, no echo,...) 
	newtio.c_cc[VTIME]    = 0;                  // inter-character timer unused 
	newtio.c_cc[VMIN]     = 1;                  // blocking read until 1 char received 
	
	tcflush(fd_serial_port, TCIFLUSH);          //flush serial port
	tcsetattr(fd_serial_port,TCSANOW,&newtio);  //activate new settings
	
	cerr<<"Initialized Serial Port -"<<endl;
	return 0;
}


void *test_input(void *arg)
{
	using namespace serial_io_ns;
	unsigned char bla;
	printf("In read thread\n");
	write_packet(0x41,0x41,0x41);
	while(true)
	{
		//bla='a';
		//write(fd_serial_port,&bla,1);
		//printf("got byte: ");
		//printf("%i\n",get_byte());		
		cerr<<(int)get_byte()<<" ";
	}
}

void *keyboard_input(void *arg)
{
	int device, temp, mode, magnitude;
	device_t local_device;
	while(true)
	{
		cout<<"Device   :";
		cin>>temp;
		if(temp == -1)
			exit(0);
		else if(temp == -2)
		{
			//micro_controller_comm.remote[device].mode      = mode;
			//micro_controller_comm.remote[device].magnitude = magnitude;
			cout<<"device is:\t"   <<(int)device<<endl;
			cout<<"mode is:\t"     <<(int)(micro_controller_comm.remote[device].mode)<<endl;
			cout<<"magnitude is:\t"<<(int)(micro_controller_comm.remote[device].magnitude)<<endl;
		}
		else
		{
			device=temp;
		
			cout<<"Mode     :";
			cin>>mode;
			cout<<"Magnitude:";
			cin>>magnitude;
			cout<<endl;
	
			micro_controller_comm.local[device].mode      = mode;
			micro_controller_comm.local[device].magnitude = magnitude;
			}
		}
	
	}



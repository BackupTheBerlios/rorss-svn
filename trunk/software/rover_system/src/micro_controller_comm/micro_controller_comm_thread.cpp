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

namespace serial_io_ns
	{
	int  fd_serial_port;
	int  bytes_available;
	struct termios oldtio,newtio;
	};

void *test_input(void *none);
void *keyboard_input(void *arg);


void* micro_controller_comm_thread(void *arg)
	{
	char device_name[F_NAME_LEN];
	get_var_from_file("../data/config", "HC12_PORT", device_name , F_NAME_LEN);
	
	if(device_name == NULL)
		{
		cout<<"falling back on default for HC12_PORT: /dev/ttyS0"<<endl;
		initialize_serial_port("/dev/ttyS0");
		}
	else
		initialize_serial_port(device_name);

	
	//initialize_serial_port(device_name);
	pthread_t read_thread_id;
	pthread_t write_thread_id;
	//pthread_t keyboard_thread_id;

	pthread_create( &read_thread_id,     NULL, read_thread,       NULL );
	pthread_create( &write_thread_id,    NULL, write_thread,       NULL );
	//pthread_create( &keyboard_thread_id, NULL, keyboard_input,       NULL );

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
		while (next_byte != 0xff);
		
		next_byte = get_byte();
		
		device    = next_byte>>4;
		mode      = next_byte&0x0f;
		
		magnitude = get_byte();
		
		if( device != 0xf && mode != 0xf && magnitude != 0xff ) // this is probably not right
			{
			cerr<<"device is:\t"   <<(int)device<<endl;
			cerr<<"mode is:\t"     <<(int)mode<<endl;
			cerr<<"magnitude is:\t"<<(int)magnitude<<endl;
			micro_controller_comm.remote[device].mode      = mode;
			micro_controller_comm.remote[device].magnitude = magnitude;
			}
		else
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
							cout<<"mode="<<(int)micro_controller_comm.remote[i].mode<<"   magnitude="<<(int)micro_controller_comm.remote[i].magnitude<<endl<<endl;
							micro_controller_comm.local[i].mode      = micro_controller_comm.remote[i].mode;
							micro_controller_comm.local[i].magnitude = micro_controller_comm.remote[i].magnitude;
							micro_controller_comm.local[i].writable  = micro_controller_comm.remote[i].writable;
							}
					else
							{
							//cout<<"Difference detected in device "<<i<<endl;
							//cout<<"Got     mode="<<(int)micro_controller_comm.remote[i].mode<<"\t  mag="<<(int)micro_controller_comm.remote[i].magnitude<<endl;
							//cout<<"Sending mode="<<(int)micro_controller_comm.local[i].mode<< "\t  mag="<<(int)micro_controller_comm.local[i].magnitude<<endl<<endl;

							epoch++;
							
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
	static unsigned char buff[3];
	static timespec cycle_delay;
	cycle_delay.tv_sec = 0;
	cycle_delay.tv_nsec = 100000;

	
	buff[0]= 0xff;
	buff[1]= (device<<4) | (mode & 0x0f);
	buff[2]= magnitude;
	
	if (!fd_serial_port)
		{
		cerr<<"fd not open"<<endl;
		return;
		}

	if (magnitude == 0xff) //reserve ff for begin byte
		magnitude = 0xfe;
	
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
		perror(serial_port); 
		exit(-1); 
		}
	
	tcgetattr(fd_serial_port,&oldtio); /* save current port settings */
	

	fcntl(fd_serial_port, F_SETFL, FASYNC);     // set to asynchronous mode
	//fcntl(fd_serial_port, F_SETFL, FNDELAY);        // would be non blockingmode; 
	
	bzero(&newtio, sizeof(newtio));
	
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


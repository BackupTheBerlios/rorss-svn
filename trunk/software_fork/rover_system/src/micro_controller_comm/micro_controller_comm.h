#ifndef __MOBILITY_H
#define __MOBILITY_H
#include <termios.h>
#define NUMDEVICES 15
#define BAUDRATE   B38400  /* baudrate settings are defined in <asm/termbits.h>, which is included by <termios.h> */

enum device_id 
			{
			HC12                   =0x0, 
			LEFT_MOTOR             =0x1, 
			RIGHT_MOTOR            =0x2, 
			STEPPER                =0x3, 
			SAMPLE_DEVICE          =0x4,
			MICRO_ROVER            =0x5,
			BATTERY_MONITOR        =0x6,
			STEPPER_ENCODER        =0x7,
			FRONT_LEFT_ENCODER     =0x8,
			FRONT_RIGHT_ENCODER    =0x9,
			BACK_LEFT_ENCODER      =0xA,
			BACK_RIGHT_ENCODER     =0xB,
			SAMPLE_DEVICE_FEEDBACK =0xC
			};

void write_packet(	unsigned char device,
					unsigned char mode, 
					unsigned char magnitude);
				
void* write_thread(void *arg);
void* read_thread (void *arg);
int initialize_serial_port(const char *serial_port);


struct device_t
{
    unsigned char mode;
    unsigned char magnitude;
    bool writable;
};


class mobil_class
	{
	friend void* write_thread(void *arg);
	friend void* read_thread (void *arg);
	friend void* keyboard_input(void *arg);
	
	private:
		pthread_mutex_t mobil_lock;
		device_t remote[NUMDEVICES];
	
	public:
		mobil_class();
		~mobil_class();
		
		device_t local [NUMDEVICES];
		void get_devices(device_t *&devices);
		void get_device(device_t  &device, device_id id);
		bool trylock();
		bool lock();
		bool unlock();
	};

void *micro_controller_comm_thread(void *none);

#endif


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include "fglove.h"
#include "glove.h"
#include "system_core/system_core.h"

char *Device_Port1;
char *Device_Port2;


	
hand_class Left_Hand, Right_Hand ; // these should be listed in glove_externs.h

#ifndef NETWORK_GLOVE
// Thread grabbing the data directly from the glove. 
// should be run where ever the gloves actually are.
void *glove_thread(void *none)
	{
	fdGlove *GloveL      = NULL;
	fdGlove *GloveR      = NULL;
	fdGlove *tempglove   = NULL;
	
	char lg_default[F_NAME_LEN] = "/dev/usb/ttyUSB0";
	char lg_config [F_NAME_LEN] = "";
	char rg_default[F_NAME_LEN] = "/dev/usb/ttyUSB1";
	char rg_config [F_NAME_LEN] = "";
	char temp_string[F_NAME_LEN];
	bool lg_enabled;
	bool rg_enabled;
	
	if( NULL == get_var_from_file(CONFIG_FILE_PATH, "L_GLOVE_PORT", lg_config, F_NAME_LEN) )
		Device_Port1 = lg_default;
	else
		Device_Port1 = lg_config;
		
	if( NULL == get_var_from_file(CONFIG_FILE_PATH , "R_GLOVE_PORT", rg_config, F_NAME_LEN) )
		Device_Port2 = rg_default;
	else
		Device_Port2 = rg_config;
	
	lg_enabled = string_to_bool(get_var_from_file(CONFIG_FILE_PATH, "L_GLOVE_ENABLED", temp_string, F_NAME_LEN),true);
	rg_enabled = string_to_bool(get_var_from_file(CONFIG_FILE_PATH, "R_GLOVE_ENABLED", temp_string, F_NAME_LEN),true);

/* Initilization */
	if(lg_enabled)
		{
		GloveL = fdOpen(Device_Port1)	;                             //fdSomething functions are part of the fglove library
		if( Device_Port1 && ! GloveL )
			{ 
			fprintf(stderr,"GLOVE MODULE: Could not open %s\n", Device_Port1);
			exit(1);
			}
		if( GloveL && (fdGetGloveType(GloveL) != FD_GLOVE7) )      
			{
			fprintf(stderr,"GLOVE MODULE: Unknown, or unsupported glove type\n");
			exit(1);
			}
		if( GloveL && (fdGetGloveHand(GloveL) != FD_HAND_LEFT) )
			{
			fprintf(stderr,"GLOVE MODULE: Wrong glove, switch glove ports \n");
			exit(1);
			}
		fprintf(stderr,"GLOVE MODULE: Left Glove ENABLED\n");
		}
	else
		fprintf(stderr,"GLOVE MODULE: Left Glove DISABLED\n");
	
	if(rg_enabled)
		{
		GloveR = fdOpen(Device_Port2) ;
		if( Device_Port2 && ! GloveR )
			{ 
			fprintf(stderr,"GLOVE MODULE: Could not open %s\n", Device_Port2);
			exit(1);
			}
		if( GloveR && (fdGetGloveType(GloveR) != FD_GLOVE7) )
			{
			fprintf(stderr,"GLOVE MODULE: Unknown, or unsupported glove type\n");
			exit(1);
			}
		if( GloveR && (fdGetGloveHand(GloveR) != FD_HAND_RIGHT) )
			{
			fprintf(stderr,"GLOVE MODULE: Wrong glove, switch glove ports \n");
			exit(1);
			}
		fprintf(stderr,"GLOVE MODULE: Right Glove ENABLED\n");
		}
	else
		fprintf(stderr,"GLOVE MODULE: Right Glove DISABLED\n");
/* end initilization */
		
		
/* Main loop */		
	while(true)	
		{
		if( GloveL && lg_enabled )
			{
			Left_Hand.lock();
			Left_Hand.thumb  = fdGetSensorScaled(GloveL,FD_THUMBNEAR);
			Left_Hand.index  = fdGetSensorScaled(GloveL,FD_INDEXNEAR);
			Left_Hand.middle = fdGetSensorScaled(GloveL,FD_MIDDLENEAR);
			Left_Hand.ring   = fdGetSensorScaled(GloveL,FD_RINGNEAR);
			Left_Hand.little = fdGetSensorScaled(GloveL,FD_LITTLENEAR);
			Left_Hand.roll   = fdGetSensorScaled(GloveL,FD_ROLL);
			Left_Hand.pitch  = fdGetSensorScaled(GloveL,FD_PITCH);
			// Left_Hand.updateStamp();
			Left_Hand.unlock();
			}
		if( GloveR && rg_enabled )
			{
			Right_Hand.lock();
			Right_Hand.thumb  = fdGetSensorScaled(GloveR,FD_THUMBNEAR);
			Right_Hand.index  = fdGetSensorScaled(GloveR,FD_INDEXNEAR);
			Right_Hand.middle = fdGetSensorScaled(GloveR,FD_MIDDLENEAR);
			Right_Hand.ring   = fdGetSensorScaled(GloveR,FD_RINGNEAR);
			Right_Hand.little = fdGetSensorScaled(GloveR,FD_LITTLENEAR);
			Right_Hand.roll   = fdGetSensorScaled(GloveR,FD_ROLL);
			Right_Hand.pitch  = fdGetSensorScaled(GloveR,FD_PITCH);
			// Right_Hand.updateStamp();
			Right_Hand.unlock();
			}
		}
/* Main Loop end */
	}
#endif 
	
	

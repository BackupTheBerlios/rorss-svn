#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
#include "system_core/system_core.h"
//#include "system_core/system_core_externs.h"
#include "command/neural_network/neural_network.h"
#include "gloves/glove.h"
#include "micro_controller_comm/micro_controller_comm_externs.h"
#include "micro_controller_comm/micro_controller_comm.h"



void *interpreter_thread(void *none)
	{
	// bla
	cout<<"Interpreter thread running"<<endl;
	hand_struct local_left_hand, local_right_hand;
	classification_struct nn_output;
	bool first_time=true;
	
	while (true)
		{
		Left_Hand.get_hand(  local_left_hand  );
		Right_Hand.get_hand( local_right_hand );
		//NNetwork.getOutput(nn_output);
		
		if(local_right_hand.thumb > 0.2)
			 micro_controller_comm.local[RIGHT_MOTOR].magnitude=(int)(local_right_hand.thumb*254);
		else micro_controller_comm.local[RIGHT_MOTOR].magnitude=0;
			
		/* if(local_right_hand.thumb > 0.2)
			 micro_controller_comm.local[]=(int)(local_right_hand.thumb*254);
		else micro_controller_comm.local[]=0;
			
		if(local_right_hand.thumb > 0.2)
			 micro_controller_comm.local[]=(int)(local_right_hand.thumb*254);
		else micro_controller_comm.local[]=0;
		 */
		}
	}
	
	

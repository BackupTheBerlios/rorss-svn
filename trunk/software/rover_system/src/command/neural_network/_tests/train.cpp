/*
 */

#include <iostream>
#include <ctime> 
#include <annie.h>

#define INPUTS 7
#define OUTPUTS 5
#define HIDDEN1 4

#define EPOCHS 1000
#define LEARNING_RATE 0.8
#verbose true

using namespace std;

//All members of the NeuralNetwork library are in this namespace
using namespace annie;

//create the input and output vectors
real input1[INPUTS], output1[OUTPUTS];
//Create a network with 7 inputs
MultiLayerNetwork net(INPUTS);
//Create a training set, 7 inputs, 5 output
TrainingSet T(INPUTS,OUTPUTS);
//Output storage;
VECTOR output; 

void initilize_nework()
	{
		try
			{
			//TwoLayerNetwork net(7,4,5);
			cout<<"Initilizing..."<<endl;
			srand(123);
			cout<<"Adding hidden layer: 4 nodes"<<endl;
			net.addLayer(HIDDEN1);
			cout<<"done."<<endl;
			cout<<"Adding output layer: 5 nodes"<<endl;
			net.addLayer(OUTPUTS);
			cout<<"done."<<endl;
			int i,j;
			for(i=0;i<net.getLayerCount();i++)
				{
				cout<<"connecting layer "<<i<<" to layer "<<i-1<<"...";
				net.connectLayer(i);
				cout<<"Done."<<endl;
				}
			
			for(i=0;i<INPUTS; i++)
				input1[i]=0;
			
			for(i=0;i<OUTPUTS; i++)
				output1[i]=0;
			
			cout<<"Initilization complete."<<endl
			}
		catch (Exception &e)
			{	
			cout<<e.what();
			}
		
	}


void update_network()
	{
	try
		{
		T.addIOpair(input1,output1);
		net.train(T,EPOCHS,LEARNING_RATE,VERBOSE);
		output=net.getOutput(input1);
		}
	catch (Exception &e)
		{	
		cout<<e.what();
		}
	}

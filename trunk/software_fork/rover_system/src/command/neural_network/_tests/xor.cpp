/*
 */

#include <iostream>
#include <ctime> 
#include <annie.h>


using namespace std;

//All members of the NeuralNetwork library are in this namespace
using namespace annie;

int main()
{
	//srand((unsigned)time(NULL));
	srand(123);

	//Set the input/output training values
	real input1[7], output1[5];

	try
		{
		//TwoLayerNetwork net(2,3,4);
		//net.connectAll();
		MultiLayerNetwork net(7);
		net.addLayer(4);
		net.addLayer(5);
		int i,j;
		for(i=0;i<net.getLayerCount();i++)
			{
			cout<<"connecting layer "<<i<<" to layer "<<i-1<<"...";
			net.connectLayer(i);
			cout<<"Done."<<endl;
			}

		//Create a training set, 2 inputs, 1 output
		TrainingSet T(7,5);
		//Add the various sample data to the training set
		char cont=0;
		int category;
		cout<<"Training:"<<endl;
		do
			{
			cout<<"Finger1 (0-1): ";
			cin>>input1[0];
			cout<<"Finger2 (0-1): ";
			cin>>input1[1];
			cout<<"Finger3 (0-1): ";
			cin>>input1[2];
			cout<<"Finger4 (0-1): ";
			cin>>input1[3];
			cout<<"Finger5 (0-1): ";
			cin>>input1[4];
			cout<<"Pitch   (0-1): ";
			cin>>input1[5];
			cout<<"Roll    (0-1): ";
			cin>>input1[6];
			
			cout<<"Category(1-4): ";
			cin>>category;
			switch(category)
				{
				case 1:  output1[0]=1; output1[1]=0; output1[2]=0; output1[3]=0; output1[4]=0; break;
				case 2:  output1[0]=0; output1[1]=1; output1[2]=0; output1[3]=0; output1[4]=0; break;
				case 3:  output1[0]=0; output1[1]=0; output1[2]=1; output1[3]=0; output1[4]=0; break;
				case 4:  output1[0]=0; output1[1]=0; output1[2]=0; output1[3]=1; output1[4]=0; break;
				default: output1[0]=0; output1[0]=0; output1[0]=0; output1[0]=0; output1[4]=0; break;
				}
			
			cout<<"i "<<input1[0]<<endl;
			cout<<"\n/////";
			for(i=0;i<input1[0]*10;i++)
				{
				cout<<"*";
				}
			
			for(j=1;j<5;j++)
				{
				cout<<"\n\\\\\\\\\\\\\\";
				for(i=0;i<input1[j]*10;i++)
					{
					cout<<"*";
					}
				}
			T.addIOpair(input1,output1);
	      cout<<endl<<"Continue y/n?:";
			cin>>cont;
			}
		while(cont == 'y');
			
				
		//T.addIOpair(input1,output1);
		//T.addIOpair(input2,output2);
		//T.addIOpair(input3,output3);
		//T.addIOpair(input4,output4);

		//Outputs will be placed in this vector
		VECTOR output; 

		cout<<"Results before training:"<<endl;
		output=net.getOutput(input1);	cout<<input1<<"\t"<<output[0]<<endl;
		//output=net.getOutput(input2);	cout<<"1 XOR 0 = "<<output[0]<<endl;
		//output=net.getOutput(input3);	cout<<"0 XOR 1 = "<<output[0]<<endl;
		//output=net.getOutput(input4);	cout<<"1 XOR 1 = "<<output[0]<<endl;

		cout<<"Training the network...please be patient if the no. of epochs is large"<<endl;

		//Train the network using the training set provided
		int epochs=10000;
		net.train(T,10000,0.8);
		cout<<"Results after training "<<epochs<<" epochs"<<endl;
		
		do
			{
			cout<<"Finger1 (0-1): ";
			cin>>input1[0];
			cout<<"Finger2 (0-1): ";
			cin>>input1[1];
			cout<<"Finger3 (0-1): ";
			cin>>input1[2];
			cout<<"Finger4 (0-1): ";
			cin>>input1[3];
			cout<<"Finger5 (0-1): ";
			cin>>input1[4];
			cout<<"Pitch   (0-1): ";
			cin>>input1[5];
			cout<<"Roll    (0-1): ";
			cin>>input1[6];
			output=net.getOutput(input1);	cout<<output[0]<<"  "<<output[1]<<"  "<<output[2]<<"  "<<output[3]<<"  ."<<endl;
	      cout<<endl<<"Continue y/n?:";
			cin>>cont;
			}
		while(cont == 'y');
			
		//output=net.getOutput(input2);	cout<<"0.5, 0.5 "<<output[0]<<"  "<<output[1]<<"  "<<output[2]<<"  "<<output[3]<<endl;
		//output=net.getOutput(input3);	cout<<"0.0, 0.5 "<<output[0]<<"  "<<output[1]<<"  "<<output[2]<<"  "<<output[3]<<endl;
		//output=net.getOutput(input4);	cout<<"0.0, 0.0 "<<output[0]<<"  "<<output[1]<<"  "<<output[2]<<"  "<<output[3]<<endl;
	}
	catch (Exception &e)
	{
		cout<<e.what();
	}
	return 0;
}

#ifndef _train
#define _train
#include <annie.h>
void initialize_network();
void update_network();
void add_training_pair();
void evaluate();

using namespace annie;
extern MultiLayerNetwork net;
extern real input1[];
extern real output1[];
extern TrainingSet T;
extern VECTOR output; 
#endif


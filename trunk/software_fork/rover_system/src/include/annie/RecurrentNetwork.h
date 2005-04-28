/**
 * $Id: RecurrentNetwork.h,v 1.1 2004/06/28 08:01:29 opx Exp $
 * @author op
 */
#ifndef RECURRENTNETWORK_H
#define RECURRENTNETWORK_H

#include "Network.h"
#include "InputLayer.h"
#include "RecurrentNeuron.h"

namespace annie {

/// implementation detail, don't bother :)
typedef TLayer<RecurrentNeuron> RecurrentLayer;
		
/** Recurrent network - here the real fun begins!
  ?? do not explicitly talkabout RNeutons?
  tinkabout CTRNN & DRNN a bit
  The RN has two types of neurons: 
  - <code>InputNeuron</code>s - they provide the (usual) way to feed external inputs
  - <code>RecurrentNeuron</code>s and their descendants - they do the stuff.

  Outputs are read from some (or all) of the recurrent neurons
  */

/// RN constructed from a genotype
//GeneticRN(list<VECTOR> genotype);

class RecurrentNetwork : public Network	{
public:
	static const int INPUT_NEURONS_LABEL_OFFSET;
	/**
	 * If the counts are specified, default neurons are added.
	 * You can add new neurons anytime you want - it's your newtork, anyway..
	 */
	RecurrentNetwork(uint initialInputCount=0, uint initialRecurrenCount=0);

	void addInput(real initialValue=0);
	void addInput(InputNeuron *in) { _inputs.addNeuron(in); }

	/// add a recurrent neuron
	void addNeuron(real bias=0, real activation=0);
	void addNeuron(RecurrentNeuron *n) { _neurons.addNeuron(n); }

	/// Returns "RecurrentNetwork"
	virtual const char* getClassName() const { return "RecurrentNetwork"; }

	/// number of input "neurons"
	virtual uint getInputCount() const { return _inputs.size(); }

	/// number of recurrent neurons
	virtual uint getOutputCount() const { return _neurons.size(); }

	/** 
	 * Actualise the input "neuron's" vector.
	 * This is usually called before each step(), but it's not neccesary.
	 */
	virtual void setInput(const Vector &input);

	/// get a recurrent neuron
	RecurrentNeuron &getNeuron(uint index) { return _neurons[index]; }
	RecurrentNeuron &operator[](uint index) { return getNeuron(index); }
	
	InputNeuron &getInputNeuron(uint index) { return _inputs[index]; };

	/**
	 * Force recurrent neuron's activations (usually done at startup)
	 * TODO: activations || outputs ?
	 */
	virtual void resetActivations(const Vector &activations);

	/// Steps the network in time (asynchronously)
	virtual void step();
	
	/** get the output of particular neuron 
	 * (usually, we're only interested in some neurons, not all)
	 */
	virtual real getNeuronOutput(uint neuron) { return _neurons[neuron].getOutput(); }

	/**
	 * Just get the current state of recurrent neurons
	 */
	virtual Vector getOutput() const;

	/**
	 * Set input neurons, step and return all recurrent neuron's activations
	 */
	virtual Vector getOutput(const Vector &input);

	///NOT IMPLEMENTED by default
	virtual void save(const std::string &filename) { throw Exception("Not implemented"); }
   protected:
	InputLayer _inputs;
	RecurrentLayer _neurons;
	uint _time;	//TODO: is it good for something?
};

} //namespace annie
#endif // _H

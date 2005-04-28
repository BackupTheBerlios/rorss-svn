#ifndef _RECURRENTNEURON_H
#define _RECURRENTNEURON_H

#include "SimpleNeuron.h"
#include "defines.h"
#include <vector>

namespace annie
{

/** A neuron used for recurrent networks.
  * These neurons have a concept of time. Thus, their output starts from an initial 
  * state and then as time progresses their output may change.
  *
  * Recurrent networks allow cycles in the graph formed by connections between
  * neurons, which are not allowed by simple multi-layer networks. For example,
  * consider a network in which a recurrent neuron is connected to itself.
  * Output now becomes time dependent.
  * output(time=0) = an initial, fixed value.
  * output(time=1) = weight_of_link * output(0)
  * output(time=t) = weight_of_link * output(t-1) etc.
  *
  * A recurrent neuron has all the features of a simple neuron and adds the concept
  * of time, hence the RecurrentNeuron class is a sub-class of the SimpleNeuron class
  *
  * major changes:
  * 6/2004	OP: 	As it is no longer used in Hopfield, it was reworked (just a little bit) to fit into the more general RecurrentNetwork. Storing of time and initialState was removed to save time/space. Also, bias is on by default (set it to 0, if you don't want it)
  *
  * @author asim
  * @author op
  */
class RecurrentNeuron : public SimpleNeuron
{
public:
	/** Creates a recurrent neuron.
	  * The default initial value is 0, thus at time=0 the output
	  * of the neuron will be 0. To change use reset
	  * @param label The label to give to the neuron
	  * @param hasBias Allow this neuron to have a bias?
	  * @see reset
	  */
	RecurrentNeuron(int label, real bias, real activation=0.);
	
	void setActivationFunction(ActivationFunction f)	{ _activationFunction = f; _outputCache = _activationFunction(_activationCache); }

	/** 
	 * Recompute output.
	 */
	virtual void update();

#define NONSENSE { ASSERT(0); throw Exception("Doesn't have sense in RecurrentNeuron"); }
	virtual void invalidateOutputCache() {}

	/** Returns the last output of the neuron. At time 0 this will be
	  * the initial value which is set using reset(), and which is
	  * zero by default. Otherwise it will be the output computed before last step() 
	  * @return the output of this neuron at the current time
	  */
	virtual real getOutput() const ;

	/// Returns "RecurrentNeuron"
	virtual const char* getClassName() const { return _RECURRENT_NEURON_STRING; }

	/** Resets the neuron to given state
	  * @param initialActivation The forced activation neuron.
	  */
	virtual void reset(real initialActivation);

	/// Not sensible
	virtual void calculateNewWeights(real learningRate) NONSENSE


	/// Not sensible
	virtual void setDesiredOutput(real desired) NONSENSE
protected:
	virtual void _recacheOutput() const {}
	real _bias;
};

}; //namespace annie
#endif // define _RECURRENTNEURON_H


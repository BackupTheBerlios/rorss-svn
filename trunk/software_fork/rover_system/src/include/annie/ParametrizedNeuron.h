#ifndef _PARAMETRIZEDNEURON_H
#define _PARAMETRIZEDNEURON_H

#include "AbstractNeuron.h"
#include "defines.h"

namespace annie
{

typedef real(*ParametrizedActivationFunction)(real, real parameter);

/// Sigmoidal activation with slope modifier lambda <b>f(x) = 1/(1+e^(lambda*x))</b>
real psigmoid(real x, real lambda);

/// Derivative of the sigmoidal function
real dpsigmoid(real x, real lambda);

/**
 * Neuron with a parametrized activation function 
 *
 * If the parameter is adaptive, the modification can lie in <code>_recacheError</code>, for example.
 *
 * Status: untested
 */
class ParametrizedNeuron : public AbstractNeuron
{
protected:
	/// The derivative of the activation function, required for gradient descent training
	ParametrizedActivationFunction _dParametrizedActivationFunction;

	/// Current parameter of the activation function
	///XXX: setParameter ??
	real _parameter;

	/// @see Neuron::_recacheOutput
	virtual void _recacheOutput();

	/// @see Neuron::_recacheError
	virtual void _recacheError();

public:
	/** Creates a simple neuron with the given label.
	  * @param label The label to be given to the neuron
	  * @param hasBias true if the neuron is allowed to have a bias, false otherwise. Default is true
	  * @see removeBias
	  */
	ParametrizedNeuron(int label, real initialParameter=1.0, bool hasBias = true);

	/** Sets the desired output of the neuron.
	  * Should be called only for output neurons, i.e., those whose output is not
	  * connected to anyone else. Setting the desired output at these neurons
	  * will form the basis of error backpropagation
	  * @param desired The desired output of this neuron
	  * @throws Exception if the neuron is not an output neuron
	  */
	virtual void setDesiredOutput(real desired);

	/// Returns "ParametrizedNeuron"
	virtual const char *getClassName();
};



}; //namespace annie


#endif // define _GABNEURON_H


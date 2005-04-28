#ifndef _GABNEURON_H
#define _GABNEURON_H

#include "ParametrizedNeuron.h"
#include "defines.h"

namespace annie
{

/**
 * Neuron for Gain Adaptive BP
 *
 * status: not finished. But I don't want to remove it because it needs just a little bit work if someone needs it. It can speedup the BP and help with overlearning
 *
 * This neuron modifies learning parameter <code>lambda</code> given equation:
 * 	
 * 	l_tmp = labda ??? - co je teda OLD???
 * 	l_new += l_tmp -edx  +  a(l_tmp - l_old)
 * 	
 * 	(e - eta, a - alpha
 *	d - delta, 
 *	x - ???
 * 	)
 */
class GABNeuron : public ParametrizedNeuron {
public:
	/** Creates a simple neuron with the given label.
	  * @param label The label to be given to the neuron
	  * @param hasBias true if the neuron is allowed to have a bias, false otherwise. Default is true
	  * @see removeBias
	  */
	GABNeuron(int label, real initialParameter=1.0, bool hasBias = true);

	/// Returns "GABNeuron"
	virtual const char *getClassName();
};

}; //namespace annie


#endif // define _GABNEURON_H

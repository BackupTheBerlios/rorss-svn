/**
 */
#ifndef KOHONEN_H
#define KOHONEN_H

#include "Exception.h"
#include "Network.h"
#include "SimpleNeuron.h"
#include "InputNeuron.h"
#include "InputLayer.h"
#include <string>

namespace annie
{
class TrainingSet;
/*
OPT: this could be much more tuned... no activationFunction, .., hasBias..
TODO: think about labels..
 the neuron output gives DISTANCE of the neuron from the input.
 TODO activation == output
*/
class KohonenNeuron : public SimpleNeuron	{
public:
	KohonenNeuron(int label);
	static const real RANDOM_WEIGHTS_DEV;	//devation of ramdom weights from mid
	void adaptTowards(const Vector &input, real nbWeight, real learningParam);
	void randomizeWeights();
protected:
	virtual void _recacheOutput() const;
	void setWeights(const Vector &w);
};


/**
	Class used as a template to the KohonenNetwork network.
*/
#if 0
class Topology	{
public:
	/**
	Not optimized for rectangle neighborhood (which is typical..)
	*/
	real getNeighborWeight(uint srcNeuron, destNeuron, real nbSize);

};
#endif

class Topology	{
public:
	/**
	 * Not optimized for rectangle neighborhood (which is typical..)
	 */
	virtual real getNeighborWeight(uint srcNeuron, uint destNeuron, real nbSize) const = 0;

	/**
	 * Function ONLY relevant for visualization - true for the neurons which should be connected by a line
	 * calling for srcNeuron == destNeuron will also return true (and is useless :)
	 */
	virtual bool isGridNeighbor(uint srcNeuron, uint destNeuron) const = 0;
	
	/// total number of neurons in this topology
	uint getTotalCount() const { return totalCount; }

	/**
	 * maximal dimension of 2 neurons present in this topology
	 * this is supposed to be constant for given topology instance
	 */
	real getMaxDim() const	{ return maxDim; }
protected:
	uint totalCount;
	real maxDim;
};

/**
 * Note: it is closely tied to Topology - the meaning NeighborhoodSize depends on the Topology used
 *
 * the 
 */
class KohonenParameters	{
public:
	static const char * const NB, *const LP;
	KohonenParameters(real initNB, real initLP, PublicValues &ctrl=defaultControl) : control(ctrl)  { setNB(initNB); setLP(initLP); }

	///will always be called PRIOR to ant get* functions
	virtual void nextIteration()	= 0;

	/// current size of neighborhood. >=0
	real getNeighborhoodSize() const;

	/// alpha
	real getLearningParam() const;
protected:
	void setNB(real nb);
	void setLP(real lp);

	PublicValues &control;
};

/**
 * Static kohonen parameters - don't change unless changed by the user
 */
class StaticKohonenParameters	: public KohonenParameters {
public:
	StaticKohonenParameters(real initNB, real initLP) : KohonenParameters(initNB, initLP)	{}
	virtual void nextIteration()	{}
};

/*abstract*/ class DynamicKohonenParameters	: public KohonenParameters {
public:
	/* setting 'em initially to 0, because they'll be replaced in  nextIteration()*/
	virtual void nextIteration()	{ ++_step; recompute(); }
	virtual void recompute() = 0;
	uint getStep() const { assert(_step); return _step; }
protected:
	DynamicKohonenParameters() : KohonenParameters(1., 1.), _step(1)	{ }
private:
	uint _step;	//time step; \in [1, ..]
};

/**
  learningParam = e ^ (- slope * ( ln (time) ^ 2 ) )
  neighborHoodSize = (MAX_NB_SIZE) * learningParam 

	TODO: set slope according to the number of epochs ...
 */
class StandardKohonenParameters	: public DynamicKohonenParameters {
public:
	StandardKohonenParameters(real maxNB, real slope) : _slope(-slope), _maxNB(maxNB) {  }
	virtual void recompute();
protected:
	real _slope, _maxNB;
};

/*
a ~ t^-p

--> e^-p*log^2(t)
*/

//template <class Topology> ???give + and -ses for templatization..

/**
 * Todo: getOutput (&& getWin*) doesn't give anything sensible in this impl. !!!!!!!!
 *
 */
class KohonenNetwork : public Network
{
public:
	enum { INPUT_LAYER, OUTPUT_LAYER };
	static const real MAX_OUTPUT, MIN_OUTPUT;
	static const real TERMINATING_LP;	///default LP threshold

	KohonenNetwork(uint inputs, const Topology &topology, KohonenParameters &params, PublicValues &ctrl=defaultControl);
	/**
	 T.get
	 InputSize() == inputs;
	 OutputSize == 0
	 individual epochs are published via "epoch" control variable
	 TODO: can be stopped via "stopTraining" CV
	*/
	/**
	 * Train the net until learningParameter reaches given threshold
	 */
	void train(TrainingSet &T, real terminatingLP=TERMINATING_LP);

	/// alternative to training via train. You can train one-by-one example directly, but should must call iterateTime() to control the dynamic
	void trainExample(const Vector &input);
	
	//void train(TrainingSet &T, uint epochs);

	/**
	 * version of getOutput for Kohonen
	 * @return the winning neuron's index
	 */ 
	uint getWinnerOutput(const Vector &input);
	
	/**
	 * version of  getWinnerOutput based on the current state of network. Reasonable to call only after previous get*Output
	 */
	uint getWinner() const;

	/**
	 * Warning - this raw output function doesn't give much sense!
	 */
	virtual Vector getOutput(const Vector &input);
	const Layer &getOutputLayer() const	{ return _outputLayer; }
	virtual const char *getClassName() const	{ return "KohonenNetwork"; }

	/**
	 * Get vector representing the given cluster - input weights of given neuron
	 */
	virtual Vector getCluster(uint cluserNum) const;

	virtual void save(const std::string &filename)	{ throw Exception("not implemented"); } //TODO

	const Topology &getTopology() const { return topology; }
protected:
	void connectLayers();
	void randomizeWeights();
	real getNBSize() const	{ return parameters.getNeighborhoodSize(); }
	real getLearningParam() const	{ return parameters.getLearningParam(); }
	void _setInput(const Vector &input);

	InputLayer _inputLayer;
	Layer _outputLayer;
	const Topology &topology;
	KohonenParameters &parameters;
	PublicValues &control;
	mutable uint _winner;	//<current winner
	mutable bool _winnerValid;
};

}	//annie
#endif //_H

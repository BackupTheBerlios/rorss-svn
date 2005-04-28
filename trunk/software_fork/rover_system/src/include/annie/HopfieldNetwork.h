#ifndef HOPFIELDNETWORK_H
#define HOPFIELDNETWORK_H

/**
 * $Id: HopfieldNetwork.h,v 1.3 2004/06/17 16:32:22 opx Exp $
 * @author asim
 * @author op
 */

#include "Network.h"
#include "Matrix.h"
#include <vector>

namespace annie {

/** Similar to the signum function, but used for non-bipolar Hopfield networks.
  * @param x A real value
  * @return 0 if x<=0, 1 otherwise.
  */
real isPositive(real x);

/** A Hopfield network - content addressable memory and energy.
  *
  * This class is an abstract base for real implementations of Hopfield
  * 	- either use HopfieldNewtork
  * 	- or derive HopfieldBase and define your own getWeight function (this allows to save space and use larger number of neurons - see examples/hdither.cc)
  * 
  * The Hopfield network is considered a landmark in the field of neural computing.
  * This model can store a number of patterns and retrieve the correct pattern starting
  * from a noisy or incomplete pattern so that a network can be trained to identify
  * patterns or images. Hopfield proposed this model as a model of biological memory
  * (often called "content addressable memory"), similar to the way a human brain
  * recognizes an image based on the past experience or learning.
  *
  * Hopfield also introduced another important idea by establishing a new connection
  * between computation and physics with the concept of energy in his model and showed
  * that computation can be viewed as a transition to lower energy states.
  *
  * OPT: it would be faster to attach weights by a template instead of inerhitance
  */
/*abstract*/ class HopfieldBase : public Network	{
protected:
	/// true if patterns are bipolar (ie, elements are -1 or 1), false if not (elements are 0 or 1)
	bool _bipolar;

	/// The number of patterns that have been given to the network to be stored
	int _nPatterns;
	int _time;

	HopfieldBase() : Network(0,0), _neurons(0) {}

	struct	NData {
		Vector _biases;
		//		Vector _activations;
		Vector _outputs;
		ActivationFunction _function;	//one for all
		void setSize(uint size) {
			_biases.resize(size); _outputs.resize(size);
		}
		NData(uint size, ActivationFunction f=signum) : _biases(size), _outputs(size), _function(f) {}
	} _neurons;
	
	///conv to discrete value acc to _bipolar
	int real2int(real r) const;
	///neuron interface
	typedef uint Nid;
	real _getBias(Nid i);
	void _setBias(Nid i, real bias);
	void _setNeuronOutput(Nid n, real a) { _neurons._outputs[n] = a; }
	real _getNeuronOutput(Nid n) const	{ return _neurons._outputs[n]; }
public:
	/*virtual void setActivation(Nid n, real a) = 0;
	virtual real getOutput(Nid n, real a) = 0;*/

	virtual real getWeight(uint from, uint to) const = 0;
	virtual void setWeight(uint from, uint to, real weight) = 0;	///not necessarily implemented in all childs

	/** Creates a Hopfield network, which can store binary patterns.
	  * Diagonal elments of the weight matrix will be zero.
	  * @param size The size/number of bits of/in the patterns to be stored
	  * @param bias true if the neurons are to have a bias, false otherwise
	  * @param bipolar true if patterns are bipolar (elements are -1 or 1), false if not
	  *					(elements are 0 or 1).
	  */
	HopfieldBase(uint size, bool bias=false, bool bipolar=true);

	virtual ~HopfieldBase()	{}

	///NOT IMPLEMENTED by default
	virtual void save(const std::string &filename) { throw Exception("Not implemented"); }

	/// Returns the energy at the current state of the network.
	virtual real getEnergy();

	/** Returns the energy of the supplied pattern.
	  * Energy of a pattern depends on the weight matrix
	  */
	virtual real getEnergy(int pattern[]);

	/// Returns the size of the patterns that can be stored (i.e., length of the pattern vector)
	virtual uint getSize() const;

	/// Steps the network in time
	virtual void step();
	
	/** The number of steps the network has taken since the last call to getOutput
	  * @see getNextOutput
	  * @see getOutput
	  */
	virtual int getTime();

	///set random activations
	void randomize();

	/// Returns "HopfieldNetwork"
	virtual const char* getClassName() const;


	/* Given an input pattern, keeps iterating through time till the network
	  * output converges. Ofcourse, it is possible that this never happens
	  * and hence a timeout has to be specified.
	  * \todo Implement this!
	  * @param pattern The initial input pattern given to the network
	  * @param updateAll Determines type of updating (synchronous, asynchronous)
	  * @param timeout The maximum number of iteration to try convergence for
	     * @return false if the network output didn't converge till the timeout, true otherwise
	  */
	//virtual bool converge(int pattern[], bool updateAll, int timeout);

	/** Get the bias at the given neuron
	  * @param i The neuron whose bias is wanted
	  * @return The bias
	  */
	virtual real getBias(uint i);

	/** Sets the bias of the given neuron.
	  * @param i The neuron whose bias is to be set
	  * @param bias The bias value to give the ith neuron
	  */
	virtual void setBias(uint i, real bias);

	/** Sets the initial output of the neurons to the values
	  * in the given array and resets time to 0.
	  * @param pattern An array containing the initial outputs of the 
	  *                neurons. The array must contain getSize() elements
	  */
	virtual void setInput(int pattern[]);

	/** Sets the initial output of the neuron to the values
	  * in the given vector of integers and sets time to 0.
	  * @param pattern A vector of integers containing the initial outputs
	  *                of the neurons. The vector must contain getSize()
	  *                elements, each -1 or 1 (if bipolar) or 0 or 1 if not.
	  */
	virtual void setInput(const std::vector<int> &pattern);

	/** Sets the initial output of the neurons to the values
	  * in the given vector and sets time to 0.
	  */
	virtual void setInput(const Vector &pattern);

	/** Returns the current outputs of the neurons.
	  * @return A vector v, where v[i] = current output at the ith neuron
	  */
	virtual Vector getOutput() const;

	/// getOutput clamped to {0,1} or {-1.1}
	std::vector<int> getOutputInt() const;

	/** Steps the network through one unit of time and returns
	  * the output.
	  * @return A vector v, where v[i] = output of the ith neuron
	  */
	virtual Vector getNextOutput();

	/** The HopfieldNetwork generally deals with vectors of integers
	  * only because the neurons are binary.
	  * But since this class implements the Network class, it must
	  * provide this function as well, which returns the same thing
	  * as setInput() following by getOutput() would, except that the
	  * neuron's output will be of type real instead of int
	  */
	virtual Vector getOutput(const Vector &input);

	/** Sets the initial input of the network and then steps through
	  * time, returning true if the network converges before the given
	  * timeout.
	  * @param pattern The initial output of the network
	  * @param timeout The maximum number of steps the network should go through
	  * @return true if the pattern converges within the timeout, false otherwise
	  */
	virtual bool propagate(int pattern[], uint timeout);

	/** Sets the initial input of the network and then steps through
	  * time, returning true if the network converges before the given
	  * timeout.
	  * @param pattern The initial output of the network
	  * @param timeout The maximum number of steps the network should go through
	  * @return true if the pattern converges within the timeout, false otherwise
	  */
	virtual bool propagate(const std::vector<int> &pattern, uint timeout);

	///the save as discrete version, but may have problems w/ convergence (real values must stand still, not only the ints
	virtual bool HopfieldBase::propagate(const Vector &pattern, uint timeout);
};

/**
 * A "standard" incarnation of the Hopfield network usable form most purposes.
 * It will have problems with large number of neurons (because the weights for 'em need ^2 memory)
 */
class HopfieldNetwork : public HopfieldBase {
protected:
	/// The weight matrix of the network
	Matrix *_weightMatrix;

	virtual real getWeight(uint from, uint to) const;
public:
	HopfieldNetwork(uint size, bool bias=false, bool bipolar=true);

	/** Loads a Hopfield network from a file.
	  * @see save
	  * @param filename The name of the filename to load the network from
	  * @throws Exception on any error
	  */
	HopfieldNetwork(const char *filename);
	
	/// Cleans up memory by getting rid of the weight matrix
	~HopfieldNetwork();

	/** Saves the network to a file
	  * \todo Implement this!
	  * @param filename The name of the file to store the network into so that it
	  *					can be loaded from there later
	  */
	virtual void save(const std::string &filename);

	/** Sets the weight between the ith and jth neuron.
	  * Since the weights are symmetruc, the weight between
	  * neuron i and neuron j will be the same as the weight
	  * between neuron j and neuron i, which will be the same
	  * as the weight supplied.
	  * @param i The ith neuron
	  * @param j The jth neuron
	  * @param weight The weight of the link (i,j) and (j,i)
	  */
	virtual void setWeight(uint i, uint j, real weight);

	/// Returns a copy of the weight matrix that is used by this network
	virtual Matrix getWeightMatrix();

	/** Adds a pattern to the network by making suitable adjustments to the weight
	  * matrix.
	  * @param pattern The bipolar pattern (of getSize() length) to be stored
	  * @throws Exception If the given pattern is not bipolar (i.e., consisting of only -1s and 1s) and
	  *			the network is designed for bipolar patters or if the pattern does not consist of 0s and 1s
	  */
	virtual void addPattern(int pattern[]);

	/** The number of patterns that the network has been instructed to store
	  * This will be the same as the number of calls to addPattern
	  * @see addPattern
	  */
	virtual uint getPatternCount();
};


}
; //namespace annie
#endif // define _HOPFIELDNETWORK_H


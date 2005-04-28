#ifndef KANAL
#define KANAL

#include "Control.h"
#include "defines.h"
#include "EucledianTopology.h"

namespace annie	{

#define AXES 2
		
class KohonenAnalyzer : public Video::Redrawer	{
  public:
	struct Outs	{
		uint arr[AXES];
		Outs(uint x, uint y)    {
			arr[0] = x;
			arr[1] = y;
		}
	};
	KohonenAnalyzer(uint inputs, const Outs &outputs, PublicValues &ctrl=defaultControl) : control(ctrl), _topology(outputs.arr), _parameters(_topology.getMaxDim(), control["slope"]), _net(inputs, _topology, _parameters)	{}
	
	/**
	 * Shows the current state of the kohonen network
	 * (draw point for the most active neuron)
	 */		
	virtual void draw();

	/**
	 * Train the analyzing kohonen while training the mlp
	 */
	virtual void calibrate()=0;

	/// do the analysis
	virtual void trainAndAnalyze(uint epochs)=0;

	uint getInputCount() const { return _net.getInputCount(); }
	const KohonenNetwork &getNet() const { return _net; }

  protected:
	///do one training step. doesn't iterateTime(), caller must take care of it himself
	void calibrateStep(const Vector &in);
	void analyzeStep(const Vector &in);

	PublicValues &control;
	typedef EucledianTopology<AXES> MyTopology;
	MyTopology _topology;
	StandardKohonenParameters _parameters;
	KohonenNetwork _net;
};

/**
 * Analyzes MLP using Kohonen
 */
class MLPKohonenAnalyzer : public KohonenAnalyzer	{
  public:
	MLPKohonenAnalyzer(const Outs &outputs, MultiLayerNetwork &net, TrainingSet &ts) : KohonenAnalyzer(net.getLinksCount(), outputs), analyzedNet(net), ts(ts)	{
		net.setControl(mlpControl);
	}
	virtual void calibrate();
	virtual void trainAndAnalyze(uint epochs);
  protected:
	/// get the current weights of the analyzedNet
	void getWeights(Vector &v) const;

	/// do one epoch with the MLP and adapt and/or display the analyzing Kohonen
	void loop(uint epochs, bool adapt, bool draw);
	
	PublicValues mlpControl;
	MultiLayerNetwork &analyzedNet;
	TrainingSet &ts;
};

void runKohonenAnalyzer(KohonenAnalyzer &ka);

} //annie
#endif //_H

/**
 * Utility classes for Kohonen - drawing
 * 
 * @author OP
 */
#ifndef KOHONEN_DRAW_H
#define KOHONEN_DRAW_H

#include "../Kohonen.h"
#include "../Video.h"
#include "../TrainingSet.h"

namespace annie	{

/**
 * Draws examples and progress of the Kohonen clustering using OpenGL
 * --> Should be called from the redraw thread
 */
class KohonenDraw : public Video::Redrawer 	{
  public:
	KohonenDraw(const KohonenNetwork *net) : topology(net->getTopology()), net(net) {}
	
	/// draws all
	virtual void draw();

	/**
	 * draws current state of Kohonen clusters
	 * @param control["drawLines"] - whether to connect the clusters by lines
	 */ 
	void drawClusters();

  protected:
	const Topology &topology;
	const KohonenNetwork *net;
	void warn();
	void unWarn();
	void drawPosition(const Vector &v);
	void drawPosition(const Neuron &n);

};

class ExKohonenDraw : public KohonenDraw	{
  public:
	ExKohonenDraw(const KohonenNetwork *net, TrainingSet &inputs) : KohonenDraw(net), inputs(inputs) {}

	/// draw the input training set
	void drawExamples();
	virtual void draw();

	/**
	 * Set another examples to be drawed at drawExamples. Must have correct dimension
	 * @param ts won't be modified except for iterating
	 */
	///ref !! void setExamples(TrainingSet &ts)	{ inputs = ts; }

  protected:
	TrainingSet &inputs;
};

}	//annie
#endif // _H

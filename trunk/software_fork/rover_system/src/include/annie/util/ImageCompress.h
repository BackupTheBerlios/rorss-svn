/**
 * Image compression using NNs
 * $Id: ImageCompress.h,v 1.1 2004/06/16 10:53:30 opx Exp $
 * @author OP
 */

#ifndef IMAGE_COMPRESS_H
#define IMAGE_COMPRESS_H

#include "annie/defines.h"
#include "annie/MultiLayerNetwork.h"
#include <vector>

namespace annie	{
class TrainingSet;
class Image;
/**
 * (usually lossy) image compressor.
 */
/*abstract */class ImageCompressor	{
  public:
	virtual ~ImageCompressor() {}	//be happy, my dear compiler :)
	class PartialListener	{
	  public:
		virtual void showProgress(const Image &partialResult) = 0;
	};
	virtual Image *compress(const Image &i) = 0;

	/** 
	 * Use this if you want to display the partial results.
	 * Note that it's up to implementation if and when it will call listener.
	 */
	void setPartialListener(PartialListener *pl)	{   _partialListener = pl; }
  protected:
	void showPartialProgress(const Image &partialResult)	{ if( _partialListener)  _partialListener->showProgress(partialResult); }
	ImageCompressor() :  _partialListener(NULL) {}
  private:
	PartialListener *_partialListener;
};

///container for images
typedef std::vector<annie::Image *> Images;

/**
 * Compress image by dividing it to squares.
 * Implementations will typically choose a number of distinct squares
 */
/*abstract */class TileCompressor : public ImageCompressor	{
  public:
	TileCompressor(uint partSize) : _partSize(partSize) {}
	uint getPartSize()	const {	return _partSize; }
	virtual Image *compress(const Image &i);
	virtual Image *compressTiles(const Images &images) = 0;
 
	/**
	 * Cut the image into the parts
	 */
	Images cut(const Image &source) const;
  protected:
	uint _partSize;	//<some implementations may allow to change it during lifetime
	uint _px, _py;	//< valid only during compress - count of cols and rows
};

/** 
 * the input image should be grayed because we only take the first color component into account
 * supports partial progress displaying
 */ 
class MLPCompressor : public TileCompressor, public ValueUpdateListener		///yeah, yeah - ValueUpdateListener	should have been inner class
{
  public:
	enum { RESHOW = 20 };	//redraw period
	/**
	 * @param hidden? number of neurons in the respective layer - if 0, no such layer
	 */
	MLPCompressor(uint partSize, uint hidden1, uint hidden2, PublicValues &pv = defaultControl);
	virtual Image *compressTiles(const Images &images);
	virtual void valueChanged(const Value &val);
	
	///direct manipulation with the net - not needed for standard opraration. be careful!
	MultiLayerNetwork &getNet() { return _net; }

	///if you want the examples used inside ..
	void fillExamples(const Images &images, TrainingSet &dest);	//TS is not a result because pass by value of TS is slowwwww
  protected:
	MultiLayerNetwork _net;
	std::vector<Vector> vectored;	//< vectored tiles

	//construct result using vectored and the net
	Image *getResult();
	Creal _reshow;	//re-show period
};



	
		
	// utility functions for creating images
	Images makeSubimages(const annie::Image &i, unsigned xSize, unsigned ySize);

	/// make vector from each tile. Only the 1st byte of each color component is taken into account (to reduce dimensionalyty for MLP)
	/// retuens the outExamples and the same stored as identity in TrainingSet
	TrainingSet *makeSubImageExamples(const Images &outImages, std::vector<Vector> &outExamples);

	/**
	 * generic ImageCompressor utilization
	 * uses ["input"] as the input file
	 * @param gray whether to gray the input image before processing
	 */
	void runCompressor(ImageCompressor &ic, const char *image, bool graay=false);

}	//annie
#endif

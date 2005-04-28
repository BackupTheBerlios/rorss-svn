#ifndef _E_T_H
#define _E_T_H

#include <vector>
#include "defines.h"
namespace annie	{

/**
 * Function that can be sampled in discrete time steps
 */
typedef real (*TimeSeriesCreatingFunction)(unsigned time);

/**
 * Store for samples
 */
typedef std::vector<real> SamplesContainer;


/**
 * Sample the given function
 */
void sampleFunction(TimeSeriesCreatingFunction f, unsigned from, unsigned to, SamplesContainer &out);

/**
 * Make time-series examples from the given sample set.
 *
 * Examples will look like s[j],...,s[j+inputs-1] --> s[j+inputs],...,s[j+inputs+outputs-1]
 */
class TrainingSet;
TrainingSet *makeExamples(unsigned inputs, unsigned outputs, const SamplesContainer &samples, int from=0, int to=-1);

} //namespace annie
#endif //_H

#ifndef KOHONENT_H
#define KOHONENT_H

#include "Kohonen.h"

namespace annie {

/**
 * Standard eucledian topology
 * OPT: zounds
 */		
template<uint T_dimensions>
class EucledianTopology : public Topology	{
public:
	/**
	 * The coordinates are [0 ... plane_size-1] for each plane
	 */
	typedef uint Axes[T_dimensions];
	EucledianTopology (const Axes &sizes);

	virtual real getNeighborWeight(uint srcNeuron, uint destNeuron, real nbSize) const;
	virtual bool isGridNeighbor(uint srcNeuron, uint destNeuron) const;

	uint getSize(uint axis) const	{ return sizes[axis]; }
	void id2Axes(uint id, Axes &out) const;
	Vector axes2Vector(const Axes &a) const;
	Axes sizes;
};

template<uint T_dimensions>
EucledianTopology<T_dimensions>::EucledianTopology(const EucledianTopology::Axes &sizes)	{
	totalCount = 1;
	real mxd_2 = 0.;
	for(uint i=0; i<T_dimensions; i++)	{
		this->sizes[i] = sizes[i];
		totalCount *= sizes[i];
		mxd_2 += sizes[i] * sizes[i];
	}
	maxDim = sqrt(mxd_2);
}

template<uint T_dimensions>
void EucledianTopology<T_dimensions>::id2Axes(uint id, EucledianTopology::Axes &indexes)	const{
    for(uint i=0; i<T_dimensions; i++)	{
    indexes[i] = id % sizes[i];
	    id /= sizes[i];
    }
}

template<uint T_dimensions>
Vector EucledianTopology<T_dimensions>::axes2Vector(const Axes &a)	const {
    Vector out(T_dimensions);
    for(uint i=0; i<T_dimensions; i++)
    out[i] = a[i];
    return out;
}

template<uint T_dimensions>
real EucledianTopology<T_dimensions>::getNeighborWeight(uint srcNeuron, uint destNeuron, real nbSize) const {
	assert(srcNeuron < totalCount);
	assert(destNeuron < totalCount);

	Axes a;
	id2Axes(srcNeuron, a);
	Vector sa = axes2Vector(a);
	id2Axes(destNeuron, a);
	Vector da = axes2Vector(a);

	//	cout << "dist: " << srcNeuron << " to " << destNeuron << " = " << sa.distance(da) << endl;

	if(sa.distance(da) <= nbSize) return 1.0;
	else return 0.;
}

template<uint T_dimensions>
bool EucledianTopology<T_dimensions>::isGridNeighbor(uint srcNeuron, uint destNeuron) const	{

	return getNeighborWeight(srcNeuron, destNeuron, 1.) == 1.;
	/*	Axes a, b;
	 *	id2Axes(srcNeuron, a);
		id2Axes(destNeuron, b);
		for(uint i=0; i<T_dimensions; i++) if(abs((int)a[i] - (int)b[i]) <= 1) return true;
		return false;*/
}

} //annie
#endif //_H

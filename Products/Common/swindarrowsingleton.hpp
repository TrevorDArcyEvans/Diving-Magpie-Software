#ifndef _SWindArrowSingleton_hpp
#define _SWindArrowSingleton_hpp

#include "windplot.h"

class SPencil;

class SWindArrowSingleton
{
private:

	static IWindVane*	sm_VaneIFace;

	SWindArrowSingleton () {}

public:

	static IWindVane* Instance ();
	static void Destroy ();
};//SWindArrowSingleton

#endif


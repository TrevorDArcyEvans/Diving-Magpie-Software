#ifndef _SGlobalBox_hpp
#define _SGlobalBox_hpp

#include "SPoints.hpp"

class SGlobalBox:public SSimpleGlobalBox
{
public:

	SGlobalBox () {}
	virtual ~SGlobalBox () {}

	SPaperBox CreatePaperBox (const SProjection& Projection) const;
};//SGlobalBox

#endif



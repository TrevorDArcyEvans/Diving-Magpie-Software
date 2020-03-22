#ifndef _SGeometricAlgorithms_hpp
#define _SGeometricAlgorithms_hpp

class CPoint;

namespace SGeometricAlgorithms
{
	bool FillContains (const CPoint& Point,const CPoint* Fillarea,int FillSize);
	bool LineContains (const CPoint& Point,const CPoint* Polyline,int LineSize,short LineWidth);
}//SGeometricAlgorithms

#endif

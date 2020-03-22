#ifndef __SColourStates_hpp
#define __SColourStates_hpp

#include <afx.h>

enum EColours {BAD = 0,
			   RED,
			   AMB,
			   YLO,
			   GRN,
			   WHT,
			   BLU};

class SColourStates
{
public:

	static CString Convert  (EColours Val);
	static CString Convert  (int Val);
	static EColours Convert (const CString& Name);
	static int GetMapColour (EColours Val);
	static int GetMapColour (short Val);
};//SColourStates

#endif

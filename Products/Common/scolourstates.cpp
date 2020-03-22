#include "stdafx.h"
#include "SColourStates.hpp"
#include "SColourTable.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString SColourStates::Convert  
(
	EColours Val
)
{
	switch (Val)
	{
		default:	return "none";
		case RED:	return "RED";
		case AMB:	return "AMB";
		case YLO:	return "YLO";
		case GRN:	return "GRN";
		case WHT:	return "WHT";
		case BLU:	return "BLU";
	}//switch
}//SColourStates::Convert

CString SColourStates::Convert  
(
	int Val
)
{
	return Convert ((EColours)Val);
}//SColourStates::Convert

EColours SColourStates::Convert 
(
	const CString& Name
)
{
	if (Name == "RED")
		return RED;
	else if (Name == "AMB")
		return AMB;
	else if (Name == "YLO")
		return YLO;
	else if (Name == "GRN")
		return GRN;
	else if (Name == "WHT")
		return WHT;
	else if (Name == "BLU")
		return BLU;
	else
		return BAD;
	//if
}//SColourStates::Convert

int SColourStates::GetMapColour 
(
	EColours Val
)
{
	switch (Val)
	{
		default:	return SColourTable::COLOUR_BLACK;
		case WHT:	return SColourTable::STATE_WHT;
		case RED:	return SColourTable::STATE_RED;
		case BLU:	return SColourTable::STATE_BLU;
		case GRN:	return SColourTable::STATE_GRN;
		case YLO:	return SColourTable::STATE_YLO;
		case AMB:	return SColourTable::STATE_AMB;
	}//switch
}//SColourStates::GetMapColour

int SColourStates::GetMapColour 
(
	short Val
)
{
	return GetMapColour ((EColours)Val);
}//SColourStates::GetMapColour


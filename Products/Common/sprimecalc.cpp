#include "stdafx.h"
#include <math.h>
#include "SPrimeCalc.hpp"
#include "SPrimeDialog.h"

void SPrimeCalc::EntryPoint ()
{
	CUIntArray Factors;

	for (unsigned int i = 2; i > 0; i++)
	{
		bool Prime = true;

		float Root = sqrt (i);

		for (int FacI = 0; FacI < Factors.GetSize (); FacI++)
		{
			if (Factors[FacI] > Root)
				break;
			//if

			if ((i % Factors[FacI]) == 0)
			{
				Prime = false;
				break;
			}//if
		}//for

		if (Prime)
		{
			Factors.Add (i);
			m_Dlg->SetVal (i);
		}//if
	}//for
}//SPrimeCalc::EntryPoint





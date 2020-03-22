#ifndef _STaskMem_h
#define _STaskMem_h

#include "SException.hpp"

// Template class to call CoTaskMemAlloc but in a type safe way and throwing exceptions
template <class T>
class STaskMem
{
public:

	static T* AllocArray (int ElemCount) 
	{
//		Do the allocation
		T* RetVal = (T*)CoTaskMemAlloc (ElemCount * sizeof (T));

//		Check for out of memory
		if (!RetVal)
			throw SComException (E_OUTOFMEMORY);
		//if

		return RetVal;
	}
};//STaskMem

#endif

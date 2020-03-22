#ifndef _SSingletonCounter_h
#define _SSingletonCounter_h

// Template to link count any singleton
// Singleton must provide static Destroy ()
// Construct will increment
// Destruct will decrement
// Last destruct will destroy singleton
template <class T>
class SSingletonCounter
{
private:

	static int sm_Count;

public:

	SSingletonCounter () {sm_Count++;}
	~SSingletonCounter () 
	{
		if (--sm_Count == 0)
			T::Destroy ();
		//if
	}
};//SSingletonCounter

template <class T>
int SSingletonCounter<T>::sm_Count = 0;

#endif





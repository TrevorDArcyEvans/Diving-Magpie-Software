#ifndef _SAutoNullPtr_h
#define _SAutoNullPtr_h

// Template for a smart pointer which is only smart 
// in that it initializes automatically to null
// Useful in a collection of pointers which need null pointers
// when it extends
template <class T>
class SAutoNullPtr
{
private:

    T*  m_Ptr;      // The actual pointer

public:

    SAutoNullPtr (T* Ptr = 0):m_Ptr (Ptr) {}

//  Automatic copy constructor and assignment operator are fine

    T& operator *  () const {return *m_Ptr;}
    T* operator -> () const {return m_Ptr;}

    bool operator == (const SAutoNullPtr <T>& RVal) const {return m_Ptr == RVal.m_Ptr;}

    operator T* () const {return m_Ptr;}        // Convert to T*
};//SAutoNullPtr

#endif






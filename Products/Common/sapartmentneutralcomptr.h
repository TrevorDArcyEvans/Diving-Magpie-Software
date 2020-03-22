#ifndef _SApartmentNeutralComPtr_h
#define _SApartmentNeutralComPtr_h

#include "SMethodLock.hpp"

// Stores a COM interface pointer in an apratment neutral way
// SetPointer can be called in one apartment and GetPointer in another
template <typename T>
class SApartmentNeutralComPtr
{
private:

    HGLOBAL             m_ApartmentNeutralPtr;          // This is the neutral form
    HRESULT             m_Status;                       // Last error to occur
    SCriticalSection    m_Section;

public:

    SApartmentNeutralComPtr (CComPtr<T> PtrIn = 0);     // Calls SetPointer
    virtual ~SApartmentNeutralComPtr ();

    HRESULT SetPointer (CComPtr<T> PtrIn);              // Pass in a pointer to convert to neutral form
    CComPtr<T> GetPointer ();                           // Get the pointer in a form readable in current apartment

    HRESULT GetStatus () const {return m_Status;}

    operator bool () const {return m_ApartmentNeutralPtr != 0;} // Test for valid data
    operator CComPtr<T> () {return GetPointer ();}              // Type conversion
    SApartmentNeutralComPtr& operator = (const CComPtr<T>& RVal)// Assignment 
    {
        SetPointer (RVal); return *this;
    }
};//SApartmentNeutralComPtr

template <typename T>
SApartmentNeutralComPtr<T>::SApartmentNeutralComPtr
(
    CComPtr<T> PtrIn
)
:m_ApartmentNeutralPtr (0),
 m_Status (S_OK)
{
    if (PtrIn)
        SetPointer (PtrIn);
    //if
}//SApartmentNeutralComPtr<T>::SApartmentNeutralComPtr

template <typename T>
SApartmentNeutralComPtr<T>::~SApartmentNeutralComPtr ()
{
//  Not sure if we need any clear-up here - JK
}//SApartmentNeutralComPtr<T>::~SApartmentNeutralComPtr

template <typename T>
HRESULT SApartmentNeutralComPtr<T>::SetPointer
(
    CComPtr<T> PtrIn
)
{
    SMethodLock Lock (m_Section);

    IStream* Stream = 0; 

    m_ApartmentNeutralPtr = 0;

//  alloc and wrap block of memory
    m_Status = CreateStreamOnHGlobal (0,FALSE,&Stream);

    if (SUCCEEDED (m_Status)) 
    {
//      write marshaled object reference to memory
        m_Status = CoMarshalInterface(Stream,
                                __uuidof (T), 
                                PtrIn,
                                MSHCTX_INPROC, 
                                0,
                                MSHLFLAGS_NORMAL);

//      extract handle to underlying memory
        if (SUCCEEDED(m_Status))
            m_Status = GetHGlobalFromStream(Stream,&m_ApartmentNeutralPtr);
        //if

        Stream->Release();
    }//if

    return m_Status;
}//SApartmentNeutralComPtr<T>::SetPointer

template <typename T>
CComPtr<T> SApartmentNeutralComPtr<T>::GetPointer () 
{
    SMethodLock Lock (m_Section);

    IStream* Stream = 0; 
    
    CComPtr <T> RetVal;

//  wrap block of existing memory passed on input
    m_Status = CreateStreamOnHGlobal (m_ApartmentNeutralPtr,FALSE,&Stream);
    
    if (SUCCEEDED(m_Status)) 
    {
//      get a pointer to the object that is legal in this apt.
        m_Status = CoUnmarshalInterface (Stream, 
                                   __uuidof (T),
                                   (void**)&RetVal);
        Stream->Release();
    }//if

    return RetVal;
}//SApartmentNeutralComPtr<T>::GetPointer ()

#endif


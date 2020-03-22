#ifndef _SErrorLog_h
#define _SErrorLog_h

#include "LogEvent.h"

// this is a series of ugly macros to log where errors occur.
//
// Unfortunately, they must be implemented as macros since this is the only
// that the __LINE__ macro will be expanded correctly.  Declaring these to 
// be inline functions will not work as the __LINE__ macro will then be the
// line where the function is defined and not where it is called.
//
// Macros are bad (see any book on C/C++ programming), so programmer beware!


#ifndef ASSERT
    #ifndef _ASSERT
        #include <assert>
        #define ASSERT      assert
    #else
        #define ASSERT      _ASSERT
    #endif
#endif


// STEST_HR(x)
// throws a COM exception if a COM call fails and logs where it occurred
#ifdef _UNICODE
#define         STEST_HR(x) \
    { \
    HRESULT         hrTemp = (x); \
    if (!SUCCEEDED(hrTemp)) \
        { \
        LogEvent(_T("Exception thrown in %S at line %d"), __FILE__, __LINE__); \
        throw _com_error(hrTemp); \
        } \
    }
#else
#define         STEST_HR(x) \
    { \
    HRESULT         hrTemp = (x); \
    if (!SUCCEEDED(hrTemp)) \
        { \
        LogEvent(_T("Exception thrown in %s at line %d"), __FILE__, __LINE__); \
        throw _com_error(hrTemp); \
        } \
    }
#endif


// SASSERT_BOOL_COM(exp)
// throws an E_UNEXPECTED exception if a (boolean) logical condition is not 
// met and logs where it occurred
//
// notes
//      most useful when used with the STEST_HR(x) macro above and *lots* of
//      exception handling
#ifdef _UNICODE
#define         SASSERT_BOOL_COM(exp) \
    if (true != (exp)) \
        { \
        LogEvent(_T("Assertion failed in %S at line %d"), __FILE__, __LINE__); \
        throw E_UNEXPECTED; \
        }
#else
#define         SASSERT_BOOL_COM(exp) \
    if (true != (exp)) \
        { \
        LogEvent(_T("Assertion failed in %s at line %d"), __FILE__, __LINE__); \
        throw E_UNEXPECTED; \
        }
#endif


// SASSERT_BOOL(exp)
// throws an exception if a (boolean) logical condition is not met and 
// logs where it occurred
//
// notes
//      most useful when used with the STEST_HR(x) macro above and *lots* of
//      exception handling
#ifdef _UNICODE
#define         SASSERT_BOOL(exp) \
    if (true != (exp)) \
        { \
        LogEvent(_T("Assertion failed in %S at line %d"), __FILE__, __LINE__); \
        throw; \
        }
#else
#define         SASSERT_BOOL(exp) \
    if (true != (exp)) \
        { \
        LogEvent(_T("Assertion failed in %s at line %d"), __FILE__, __LINE__); \
        throw; \
        }
#endif


// SASSERT(exp)
// same as a normal ASSERT but will log an error in Release mode
//
// notes
//      this is similar to the normal ASSERT ie will stop errors in
//      Debug but *not* in Release - beware!
//
//      SASSERT_BOOL_COM(exp) may be more appropriate in some circumstances
//      where error handling may still be needed at runtime
//
// see also
//      SASSERT_BOOL_COM(exp)
#ifdef _UNICODE
#define         SASSERT(exp) \
    { \
    bool            bRetVal = (exp); \
    if (true != bRetVal) \
        { \
        LogEvent(_T("Assertion failed in %S at line %d"), __FILE__, __LINE__); \
        ASSERT(bRetVal); \
        } \
    }
#else
#define         SASSERT(exp) \
    { \
    bool            bRetVal = (exp); \
    if (true != bRetVal) \
        { \
        LogEvent(_T("Assertion failed in %s at line %d"), __FILE__, __LINE__); \
        ASSERT(bRetVal); \
        } \
    }
#endif


#endif

#ifndef _StringToLatLong_h
#define _StringToLatLong_h

// Converts, for example "53°12'34"N" to 53.2094444, returns false if cannot be parsed
bool StringToLatLong (LPCTSTR AsString,TCHAR NSorEW,double& AsDouble);

#endif


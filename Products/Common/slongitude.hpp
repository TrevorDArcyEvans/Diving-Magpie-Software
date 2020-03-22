#ifndef __SLongitude_hpp
#define __SLongitude_hpp

class SLongitudeDelta;

class SLongitude
{
friend class SLongitudeDelta;

private:

	double	m_Value;

//	Addition isn't allowed, but putting it here avoids implict converios to doubles
	SLongitude operator + (const SLongitude& RVal) const;
	SLongitude operator + (double RVal) const;

public:

	SLongitude (double Val = 0.0):m_Value (Val) {}
	SLongitude (const SLongitude& RVal):m_Value (RVal.m_Value) {}

	operator double () const;

	SLongitude& operator = (const SLongitude& RVal);

	bool operator == (const SLongitude& RVal) const;

	SLongitude operator + (const SLongitudeDelta& RVal) const;
	SLongitude& operator += (const SLongitudeDelta& RVal);
	SLongitude operator - () const;
	SLongitude operator - (const SLongitudeDelta& RVal) const;
	SLongitude& operator -= (const SLongitudeDelta& RVal);

	SLongitudeDelta operator - (const SLongitude& RVal) const;

	bool Between (const SLongitude& Start,const SLongitude& Finish,const SLongitudeDelta& Direction,bool Inclusive = true) const;
	bool Between (const SLongitude& Start,const SLongitude& Finish) const;

	SLongitudeDelta Separation (const SLongitude& To,const SLongitudeDelta& Direction) const;

	SLongitude Midway (const SLongitude& RVal,bool Shortest = false) const;
};//SLongitude

class SLongitudeDelta
{
friend class SLongitude;

private:

	double	m_Value;

public:

	SLongitudeDelta (double Val = 0.0):m_Value (Val) {}

	SLongitudeDelta (const SLongitudeDelta& RVal):m_Value (RVal.m_Value) {}

	operator double () const;

	SLongitudeDelta& operator = (const SLongitudeDelta& RVal);

	bool operator == (const SLongitudeDelta& RVal) const;

	SLongitudeDelta operator + (const SLongitudeDelta& RVal) const;
	SLongitudeDelta& operator += (const SLongitudeDelta& RVal);
	SLongitudeDelta operator - () const;
	SLongitudeDelta operator - (const SLongitudeDelta& RVal) const;
	SLongitudeDelta& operator -= (const SLongitudeDelta& RVal);

	SLongitudeDelta operator * (double RVal) const;
	SLongitudeDelta operator / (double RVal) const;

	SLongitudeDelta operator * (int RVal) const;
	SLongitudeDelta operator / (int RVal) const;

	double operator / (const SLongitudeDelta& RVal) const;
};//SLongitudeDelta

#endif


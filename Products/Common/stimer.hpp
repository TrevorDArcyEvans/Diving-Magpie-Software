#ifndef __STimer_hpp
#define __STimer_hpp

#include <vector>

class STimer;

class ITimeoutable
{
friend class STimer;

private:

	virtual void Timeout () = 0;
};//ITimeoutable

class STimer
{
private:

	UINT							m_ID;
	bool							m_Started;
	bool							m_Repeat;
	DWORD							m_Period;
									
	ITimeoutable*					m_CallbackObject;

	static std::vector <STimer*>	sm_These;

	void static CALLBACK TimerCallback (HWND Window,UINT Msg,UINT ID,DWORD Time);

protected:

	virtual void DoCallback ();

	STimer (DWORD Period,bool Repeat = true, bool StartNow = true);

	void SetPeriod (DWORD Period) {m_Period = Period;}
	void CreateTimer (DWORD Period,bool Repeat = true,bool StartNow = true);

public:

	STimer (DWORD Period,ITimeoutable* CallbackObj,bool Repeat = true, bool StartNow = true);
	STimer ();

	virtual ~STimer ();

	void CreateTimer (DWORD Period,ITimeoutable* CallbackObj,bool Repeat = true,bool StartNow = true);

	void Start ();
	void Stop  ();
};//STimer

#endif


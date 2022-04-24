#pragma once
#include "Base.h"
#include "Timer.h"


class CTimer_Manager final : public CBase
{
	DECLARE_SINGLETON(CTimer_Manager);
public:
	CTimer_Manager();
	virtual ~CTimer_Manager();

public :
	HRESULT Add_Timer(const _tchar* pTag);
	_float Compute_DeltaTime(const _tchar* pTag);
private :
	map<const _tchar*, class CTimer*>			m_Timers;
	typedef map<const _tchar*, class CTimer*>	TIMERS;
private :
	CTimer* Find_Timer(const _tchar* pTag);
public :
	virtual void Free() override;
};


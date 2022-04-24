#include "stdafx.h"
#include "Timer_Manager.h"

IMPLEMENT_SINGLETON(CTimer_Manager)

CTimer_Manager::CTimer_Manager()
{
}


CTimer_Manager::~CTimer_Manager()
{
}

HRESULT CTimer_Manager::Add_Timer(const _tchar* pTag)
{
	if (NULL == Find_Timer(pTag))
	{
		CTimer* pTimer = CTimer::Create();
		pTimer->AddRef();
		m_Timers.emplace(pTag, pTimer);
		pTimer->Release();
		return S_OK;
	}
	return E_FAIL;
}
_float CTimer_Manager::Compute_DeltaTime(const _tchar* pTag)
{
	CTimer* pTimer = Find_Timer(pTag);

	if (pTimer)
	{
		pTimer->AddRef();
		_float deltaTime = pTimer->Compute_TimeDelta();
		pTimer->Release();
		return deltaTime;
	}
	return 0.0f;
}

CTimer* CTimer_Manager::Find_Timer(const _tchar* pTag)
{
	auto	iter = find_if(m_Timers.begin(), m_Timers.end(), [&](TIMERS::value_type Pair)->_bool
	{
		return !lstrcmp(pTag, Pair.first);
	});
	
	if (iter == m_Timers.end())
		return NULL;

	return iter->second;
}

void CTimer_Manager::Free()
{
	for (auto& elem : m_Timers)
	{
		Safe_Release(elem.second);
	}
}

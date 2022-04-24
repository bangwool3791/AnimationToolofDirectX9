#pragma once

#include "Base.h"


class CTimer final : public CBase
{
public:
	CTimer();
	virtual ~CTimer() = default;

public:
	FORCEINLINE HRESULT CTimer::NativeConstruct()
	{
		//메인보드가 갖고 있는 고해상도 타이머의 누적값을 얻어오는 함수
		QueryPerformanceCounter(&m_CurrentTime);		// 1000
		QueryPerformanceCounter(&m_OldTime);			// 1020	
		QueryPerformanceCounter(&m_OriginTime);			// 1030

														// 고해상도 타이머의 주파수를 얻어오는 함수, 주파수는 cpu 초당 클럭수 주기를 말함
		QueryPerformanceFrequency(&m_CpuTick);			// 1600000

		return S_OK;
	}

	float CTimer::Compute_TimeDelta(void)
	{
		QueryPerformanceCounter(&m_CurrentTime);	// 2000	//	3000 // 4000 // 5000

		if (m_CurrentTime.QuadPart - m_OriginTime.QuadPart > m_CpuTick.QuadPart)
		{
			QueryPerformanceFrequency(&m_CpuTick);
			m_OriginTime = m_CurrentTime;
		}

		m_fTimeDelta = float(m_CurrentTime.QuadPart - m_OldTime.QuadPart) / m_CpuTick.QuadPart;

		m_OldTime = m_CurrentTime;

		return m_fTimeDelta;

	}

private:
	LARGE_INTEGER		m_CurrentTime;
	LARGE_INTEGER		m_OldTime;
	LARGE_INTEGER		m_OriginTime;
	LARGE_INTEGER		m_CpuTick;

	float				m_fTimeDelta;

public:
	static CTimer* Create();
	virtual void Free() override;
};



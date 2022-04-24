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
		//���κ��尡 ���� �ִ� ���ػ� Ÿ�̸��� �������� ������ �Լ�
		QueryPerformanceCounter(&m_CurrentTime);		// 1000
		QueryPerformanceCounter(&m_OldTime);			// 1020	
		QueryPerformanceCounter(&m_OriginTime);			// 1030

														// ���ػ� Ÿ�̸��� ���ļ��� ������ �Լ�, ���ļ��� cpu �ʴ� Ŭ���� �ֱ⸦ ����
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



#pragma once

#include "Engine_Defines.h"

/* 객체의 레퍼런스 카운트를 관리한다. */

class CBase abstract
{	
protected:
	FORCEINLINE CBase() = default;
	virtual ~CBase() = default;

public:
	FORCEINLINE unsigned long CBase::AddRef()
	{
		return ++m_dwRefCnt;
	}

	FORCEINLINE unsigned long CBase::Release()
	{
		if (0 == m_dwRefCnt)
		{
			Free();

			delete this;

			return 0;
		}

		else
			return m_dwRefCnt--;
	}

private:
	unsigned long			m_dwRefCnt = 0;

public:
	virtual void Free() = 0;

};



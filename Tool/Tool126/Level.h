#pragma once
#include "Base.h"

class CLevel abstract : public CBase
{
protected:
	CLevel(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CLevel() = default;
public:
	virtual HRESULT NativeConstruct();
	virtual void	Tick(_float fDeltaTime);
	virtual HRESULT Render();
protected:
	LPDIRECT3DDEVICE9 m_pGraphicDev = nullptr;
public:
	virtual void Free();
};



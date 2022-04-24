#pragma once
#include "Level.h"

class CLevel_Loading final : public CLevel
{
private:
	CLevel_Loading(LEVEL eNextLevel, LPDIRECT3DDEVICE9 pDevice);
	virtual ~CLevel_Loading() = default;
public:
	virtual HRESULT NativeConstruct();
	virtual void	Tick(_float fDeltaTime);
	virtual HRESULT Render();
private:
	LEVEL m_eNextLevel = LEVEL_END;
public :
	static CLevel_Loading* Create(LEVEL eNextLevel, LPDIRECT3DDEVICE9 pDevice);
	virtual void Free();
};

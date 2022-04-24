#pragma once
#include "Level.h"
#include "GameInstance.h"
class CLevel_GamePlay : public CLevel
{
public:
	CLevel_GamePlay(LPDIRECT3DDEVICE9 _pDevice);
	virtual ~CLevel_GamePlay() = default;
public:
	virtual HRESULT NativeConstruct();
	virtual void	Tick(_float _fDeltaTime);
	virtual HRESULT Render();
private:
public:
	static CLevel_GamePlay* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual void Free();
};


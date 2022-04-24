#pragma once
#include "Base.h"
#include "Level.h"


class CLevel_Manager final : public CBase
{
DECLARE_SINGLETON(CLevel_Manager)
private:
	CLevel_Manager();
	virtual ~CLevel_Manager() = default;
public :
	HRESULT Open_Level(_uint eNextLevel, CLevel* pLevel);
	virtual HRESULT NativeConstruct();
	virtual void	Tick(_float fDeltaTime);
	virtual HRESULT Render();
private :
	class CLevel* m_pCurrentLevel = nullptr;
	_uint   m_eNextLevel = -1;
public :
	virtual void Free();
};

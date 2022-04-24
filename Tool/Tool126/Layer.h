#pragma once
#include "Base.h"
#include "GameObject.h"


class CLayer : public CBase
{
private:
	FORCEINLINE CLayer::CLayer()
	{

	}

	virtual ~CLayer() = default;
public :

	FORCEINLINE void CLayer::Tick(_float fDeltaTime)
	{
		GAMEOBJECTLIST::iterator iter = m_listGameObject.begin();
		GAMEOBJECTLIST::iterator iter_end = m_listGameObject.end();

		for (; iter != iter_end; ++iter)
		{
			(*iter)->Tick(fDeltaTime);
		}
	}

	FORCEINLINE void CLayer::Late_Tick(_float fDeltaTime)
	{
		GAMEOBJECTLIST::iterator iter = m_listGameObject.begin();
		GAMEOBJECTLIST::iterator iter_end = m_listGameObject.end();

		for (; iter != iter_end; ++iter)
		{
			(*iter)->Late_Tick(fDeltaTime);
		}
	}

	HRESULT Render();
	HRESULT	Add_Object(CGameObject* _pGameObject);
	CGameObject* Get_Object()
	{
		return *m_listGameObject.begin();
	}
private :
	list<CGameObject*> m_listGameObject;
	typedef list<CGameObject*> GAMEOBJECTLIST;
private :
	FORCEINLINE HRESULT Native_Construct();
public :
	static CLayer* Create();
	virtual void Free() override;

};



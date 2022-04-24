#pragma once
#include "Base.h"
#include "GameInstance.h"
#include "Test.h"

class CLoader : public CBase
{
public:
	//m_stCriticalSection 초기화를 진행하자.
	CLoader(LEVEL _eNextLevel, LPDIRECT3DDEVICE9 _pDevice);
	virtual ~CLoader() = default;
public :
	FORCEINLINE HANDLE Get_Therad() const{ return m_hThread; }
	FORCEINLINE LEVEL  Get_Level()  const { return m_eNextLevel; }
	FORCEINLINE _bool  Get_IsEnd()  const { return m_isEnd; }
	FORCEINLINE void  Set_IsEnd(_bool _flag)  {  m_isEnd = _flag; }
	FORCEINLINE CRITICAL_SECTION& Get_CriticalSection() { return m_stCriticalSection; }
	FORCEINLINE _tchar*  Get_String()  { return m_szLoadingText; }
	FORCEINLINE _uint   Loading_Logo()
	{
		//현재 상태를 TCHAR형 배열에 텍스트로 저장한다.
		lstrcpy(m_szLoadingText, TEXT("텍스쳐를 로딩중입니다."));

		////지연을 위한 delay 반복문
		//for (_uint i = 0; i < 999999999; ++i)
		//{
		//	int a = 10;
		//}

		//lstrcpy(m_szLoadingText, TEXT("모델을 생성중입니다."));

		//for (_uint i = 0; i < 999999999; ++i)
		//{
		//	int a = 10;
		//}

		lstrcpy(m_szLoadingText, TEXT("로딩이 완료되었습니다."));
		//로딩이 끝나면 스레드 로딩의 결과를 나타내는 bool 변수 true
		m_isEnd = true;
		return _uint();
	}
	FORCEINLINE _uint	Loading_GamePlay()
	{
		lstrcpy(m_szLoadingText, TEXT("게임오브젝트를 로딩중입니다."));

		////지연을 위한 delay 반복문
		//for (_uint i = 0; i < 999999999; ++i)
		//{
		//	int a = 10;
		//}

		m_isEnd = true;

		return _uint();
	}
private :
	HRESULT NativeConstruct();
private :
	LEVEL m_eNextLevel = LEVEL_END;
	HANDLE	m_hThread;
	CRITICAL_SECTION m_stCriticalSection;
	LPDIRECT3DDEVICE9 m_pGraphicDev = NULL;
	_tchar            m_szLoadingText[50];
	bool	m_isEnd = false;
public :
	static CLoader* Create(LEVEL _eNextLevel, LPDIRECT3DDEVICE9 _pDevice);
	void Free() override;
};
END

#pragma once
#include "Base.h"
#include "GameInstance.h"
#include "Test.h"

class CLoader : public CBase
{
public:
	//m_stCriticalSection �ʱ�ȭ�� ��������.
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
		//���� ���¸� TCHAR�� �迭�� �ؽ�Ʈ�� �����Ѵ�.
		lstrcpy(m_szLoadingText, TEXT("�ؽ��ĸ� �ε����Դϴ�."));

		////������ ���� delay �ݺ���
		//for (_uint i = 0; i < 999999999; ++i)
		//{
		//	int a = 10;
		//}

		//lstrcpy(m_szLoadingText, TEXT("���� �������Դϴ�."));

		//for (_uint i = 0; i < 999999999; ++i)
		//{
		//	int a = 10;
		//}

		lstrcpy(m_szLoadingText, TEXT("�ε��� �Ϸ�Ǿ����ϴ�."));
		//�ε��� ������ ������ �ε��� ����� ��Ÿ���� bool ���� true
		m_isEnd = true;
		return _uint();
	}
	FORCEINLINE _uint	Loading_GamePlay()
	{
		lstrcpy(m_szLoadingText, TEXT("���ӿ�����Ʈ�� �ε����Դϴ�."));

		////������ ���� delay �ݺ���
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

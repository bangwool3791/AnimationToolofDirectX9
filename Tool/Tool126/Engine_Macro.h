#pragma once

#define SHIFT_OPERATOR(num) >> num & 0x01

#define MSGBOX(Text) MessageBox(0, Text, TEXT("Error"), MB_OK);

#define BEGIN(SpaceName) namespace SpaceName { 
#define END 

#ifdef ENGINE_EXPORTS
#define ENGINE_DLL _declspec(dllexport)
#else
#define ENGINE_DLL _declspec(dllimport)
#endif
#define NO_COPY(ClassName)								\
ClassName(const ClassName&) = delete;					\
ClassName& operator=(const ClassName&) = delete;

#define DECLARE_SINGLETON(ClassName)					\
		NO_COPY(ClassName)								\
public :												\
	static ClassName* Get_Instance();					\
	static unsigned long Destroy_Instance();			\
private:												\
	static ClassName* m_pInstance;

#define IMPLEMENT_SINGLETON(ClassName)					\
ClassName* ClassName::m_pInstance = nullptr;			\
ClassName* ClassName::Get_Instance()					\
{														\
	if (nullptr == m_pInstance)							\
		m_pInstance = new ClassName;					\
	return m_pInstance;									\
}														\
unsigned long ClassName::Destroy_Instance()				\
{														\
	unsigned long dwCount = 0;							\
	if (m_pInstance)									\
	{													\
		dwCount = m_pInstance->Release();               \
		if(!dwCount)									\
			m_pInstance = nullptr;						\
	}													\
	return dwCount;										\
														\
}					
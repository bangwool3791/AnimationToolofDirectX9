#pragma once

#include "Base.h"

class CGraphic_Device final : public CBase
{
	DECLARE_SINGLETON(CGraphic_Device)

public :
	unsigned long CGraphic_Device::Debug_Destroy()
	{														
		unsigned long dwCount = 0;		
		cout << "[Debug_Destroy] " << endl;
		if (m_pInstance)									
		{								
			dwCount = m_pInstance->Release();     
			cout << "[dwCount] "<< dwCount << endl;
			if (!dwCount)									
				m_pInstance = nullptr;						
		}													
			return dwCount;										
	}
private:
	CGraphic_Device();
	~CGraphic_Device();
	// com 객체 : 언어와의 통신 규약을 갖고 하드웨어를 통제하여 각종 기능을 제공하는 객체
public:
	HRESULT		InitDevice(const GRAPHIC_DEVICE_DESC& _stGpDev, LPDIRECT3DDEVICE9* _ppDevice);
	void		Render_Begin(void);
	void		Render_End(HWND hWnd = NULL);
private:
	FORCEINLINE LPDIRECT3DDEVICE9			Get_Device(void) { return m_pGraphicDev; }
	FORCEINLINE LPD3DXSPRITE				Get_Sprite(void) { return m_pSprite; }
	FORCEINLINE LPD3DXFONT					Get_Font(void) { return m_pFont; }
	void		SetParameters(D3DPRESENT_PARAMETERS& d3dpp);

private:
	LPDIRECT3D9				m_p3D;
	LPDIRECT3DDEVICE9		m_pGraphicDev;

	// dx 상에서 2d 이미지를 출력해주는 com객체
	LPD3DXSPRITE			m_pSprite;
	LPD3DXFONT				m_pFont;
	GRAPHIC_DEVICE_DESC	    m_stGpDev;

public :
	virtual void		Free();

};
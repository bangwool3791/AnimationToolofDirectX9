#pragma once

#include "Base.h"

class CInput_Device final : public CBase
{
	DECLARE_SINGLETON(CInput_Device)

public:
	//마우스의 이동이 x,y축인지 휠인지 구분하는 이넘 상수
	enum DIMM { DIMM_X, DIMM_Y, DIMM_WHEEL, DIMM_END };
	//마우스 버튼의 클릭이 왼쪽 또는 오른쪽 또는 휠인지 구분하는 이넘 상수
	enum DIMB { DIMB_LBUTTON, DIMB_RBUTTON, DIMB_WHEEL, DIMB_END };


private:
	CInput_Device();
	virtual ~CInput_Device() = default;


public:
	//키 입력을 받아오는 함수
	_byte Get_DIKeyState(_ubyte byKeyID) {
		return m_KeyState[byKeyID];
	}
	//마우스의 x축 y축 이동 상태를 가져오는 함수
	_long Get_DIMMoveState(DIMM eMouseMoveID) {		
		return *((_long*)&m_MouseState + eMouseMoveID);
	}
	//마우스의 왼쪽, 오른쪽, 휠 클릭 여부를 가져오는 함수
	_byte Get_DIMButtonState(DIMB eMouseButtonID) {
		return m_MouseState.rgbButtons[eMouseButtonID];
	}
public:
	//입력 장치를 초기화 하는 함수
	HRESULT Initialize_Input_Device(HINSTANCE hInst, HWND hWnd);
	//입력 장치의 상태를 업데이트하는 함수
	void Update_InputDeviceState();

//	0000 0000 0000 0000 
//&	1000 0000 0000 0000
//    0000 0000 0000 0000
//	
//
//	GetKeyState(VK_RETURN) & 0x8001

private:
	//입력 장치를 받아오는 다이렉트 디바이스
	LPDIRECTINPUT8				m_pInput = nullptr;
	//다이렉트 입력에서 사용 할 키보드 장치
	LPDIRECTINPUTDEVICE8		m_pKeyBoard = nullptr;
	//다이렉트 입력에서 사용 할 마우스 장치
	LPDIRECTINPUTDEVICE8		m_pMouse = nullptr;

private:
	//키 입력에 대한 매크로를 담는 byte 배열
	_byte						m_KeyState[256];
	//마우스의 x,y,휠, 이동한 픽셀의 값을 가져오는 구조체
	DIMOUSESTATE				m_MouseState;


public:
	virtual void Free() override;
};
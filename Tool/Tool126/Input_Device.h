#pragma once

#include "Base.h"

class CInput_Device final : public CBase
{
	DECLARE_SINGLETON(CInput_Device)

public:
	//���콺�� �̵��� x,y������ ������ �����ϴ� �̳� ���
	enum DIMM { DIMM_X, DIMM_Y, DIMM_WHEEL, DIMM_END };
	//���콺 ��ư�� Ŭ���� ���� �Ǵ� ������ �Ǵ� ������ �����ϴ� �̳� ���
	enum DIMB { DIMB_LBUTTON, DIMB_RBUTTON, DIMB_WHEEL, DIMB_END };


private:
	CInput_Device();
	virtual ~CInput_Device() = default;


public:
	//Ű �Է��� �޾ƿ��� �Լ�
	_byte Get_DIKeyState(_ubyte byKeyID) {
		return m_KeyState[byKeyID];
	}
	//���콺�� x�� y�� �̵� ���¸� �������� �Լ�
	_long Get_DIMMoveState(DIMM eMouseMoveID) {		
		return *((_long*)&m_MouseState + eMouseMoveID);
	}
	//���콺�� ����, ������, �� Ŭ�� ���θ� �������� �Լ�
	_byte Get_DIMButtonState(DIMB eMouseButtonID) {
		return m_MouseState.rgbButtons[eMouseButtonID];
	}
public:
	//�Է� ��ġ�� �ʱ�ȭ �ϴ� �Լ�
	HRESULT Initialize_Input_Device(HINSTANCE hInst, HWND hWnd);
	//�Է� ��ġ�� ���¸� ������Ʈ�ϴ� �Լ�
	void Update_InputDeviceState();

//	0000 0000 0000 0000 
//&	1000 0000 0000 0000
//    0000 0000 0000 0000
//	
//
//	GetKeyState(VK_RETURN) & 0x8001

private:
	//�Է� ��ġ�� �޾ƿ��� ���̷�Ʈ ����̽�
	LPDIRECTINPUT8				m_pInput = nullptr;
	//���̷�Ʈ �Է¿��� ��� �� Ű���� ��ġ
	LPDIRECTINPUTDEVICE8		m_pKeyBoard = nullptr;
	//���̷�Ʈ �Է¿��� ��� �� ���콺 ��ġ
	LPDIRECTINPUTDEVICE8		m_pMouse = nullptr;

private:
	//Ű �Է¿� ���� ��ũ�θ� ��� byte �迭
	_byte						m_KeyState[256];
	//���콺�� x,y,��, �̵��� �ȼ��� ���� �������� ����ü
	DIMOUSESTATE				m_MouseState;


public:
	virtual void Free() override;
};
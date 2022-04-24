#include "stdafx.h"
#include "Input_Device.h"

IMPLEMENT_SINGLETON(CInput_Device)

CInput_Device::CInput_Device()
{
}
//���̷�Ʈ �Է� ��ġ�� �ʱ�ȭ ���ִ� �Լ�
HRESULT CInput_Device::Initialize_Input_Device(HINSTANCE hInst, HWND hWnd)
{
	/*
	GUID (Globally Unique Identifier)�� Ư�� ���� ���, 
	�ϵ����, ����Ʈ����, ����, ����� ����, �����ͺ��̽� �׸� �� ��Ÿ �׸��� �����ϰ� �ĺ��ϱ� ���� Windows � ü�� �Ǵ� 
	�ٸ� Windows ���� ���α׷����� ���� 128 ��Ʈ �����Դϴ�.
	*/
	//���̷�Ʈ �Է� ��ġ�� DirecInput8Create�� �ʱ�ȭ �� ��

	if (FAILED(DirectInput8Create(AfxGetInstanceHandle(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, nullptr)))
		return E_FAIL;

	/* Ű���� �İ�ü�� �����Ѵ�. */
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pKeyBoard, nullptr)))
		return E_FAIL;
	//Ű���� �Է� ���� ������ ������ ���Ѵ�.
	if (FAILED(m_pKeyBoard->SetDataFormat(&c_dfDIKeyboard)))
		return E_FAIL;
	
	if (FAILED(m_pKeyBoard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
		return E_FAIL;

	if (FAILED(m_pKeyBoard->Acquire()))
		return E_FAIL;

	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pMouse, nullptr)))
		return E_FAIL;

	if (FAILED(m_pMouse->SetDataFormat(&c_dfDIMouse)))
		return E_FAIL;

	//���콺 �İ�ü�� �����Ѵ�.
	//���콺 �Է� ��ġ�� ��ȭ ���� ������ ��׶��忡�� �����Ѵ�.
	//�� ���Ӱ� �ٸ� ���ø����̼� ���� ��ȯ�� �߻��ϴ����, ���� ���ø����̼��� ���콺 �������� ���� �ʰ� �����Ѵ�.
	//��׶��尡 �ƴ� ���(�� �κ��� Ȯ������ �ʴ�.) �ٸ� ���ø����̼ǰ��� ��ȯ�� �߻��ϸ� ���� ������ ���콺 �������� �Ҿ�, ���콺 �Է� ��ġ�� �ٽ� �޾ƿ;��ϴ�
	//��찡 ���� ���� �ִٰ� �����ߴ�. Ȯ�������� ����	
	if (FAILED(m_pMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
		return E_FAIL;

	if (FAILED(m_pMouse->Acquire()))
		return E_FAIL;

	return S_OK;
}

void CInput_Device::Update_InputDeviceState()
{
	if (nullptr == m_pKeyBoard ||
		nullptr == m_pMouse)
		return;
	
	//Ű������ ���¸� �޾ƿ´�. ���ۿ� ������ ũ�⸦ �Է��Ѵ�.
	if (FAILED(m_pKeyBoard->GetDeviceState(256, m_KeyState)))
		return;
	//���콺�� x,y,�� �̵� ����, L,R,���� Ŭ�� ���¸� �޾ƿ´�.
	if (FAILED(m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_MouseState)))
		return;
}

void CInput_Device::Free()
{

}

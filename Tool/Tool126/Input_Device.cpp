#include "stdafx.h"
#include "Input_Device.h"

IMPLEMENT_SINGLETON(CInput_Device)

CInput_Device::CInput_Device()
{
}
//다이렉트 입력 장치를 초기화 해주는 함수
HRESULT CInput_Device::Initialize_Input_Device(HINSTANCE hInst, HWND hWnd)
{
	/*
	GUID (Globally Unique Identifier)는 특정 구성 요소, 
	하드웨어, 소프트웨어, 파일, 사용자 계정, 데이터베이스 항목 및 기타 항목을 고유하게 식별하기 위해 Windows 운영 체제 또는 
	다른 Windows 응용 프로그램에서 만든 128 비트 숫자입니다.
	*/
	//다이렉트 입력 장치를 DirecInput8Create로 초기화 한 후

	if (FAILED(DirectInput8Create(AfxGetInstanceHandle(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, nullptr)))
		return E_FAIL;

	/* 키보드 컴객체를 생성한다. */
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pKeyBoard, nullptr)))
		return E_FAIL;
	//키보드 입력 상태 데이터 포맷을 셋한다.
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

	//마우스 컴객체를 생성한다.
	//마우스 입력 장치의 변화 상태 감지를 백그라운드에서 실행한다.
	//즉 게임과 다른 어플리케이션 간의 전환이 발생하더라고, 게임 어플리케이션의 마우스 독점권을 잃지 않고 유지한다.
	//백그라운드가 아닐 경우(이 부분은 확실하지 않다.) 다른 어플리케이션과의 전환이 발생하면 게임 어플이 마우스 독점권을 잃어, 마우스 입력 장치를 다시 받아와야하는
	//경우가 있을 수도 있다고 이해했다. 확실하지는 않음	
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
	
	//키보드의 상태를 받아온다. 버퍼와 버퍼의 크기를 입력한다.
	if (FAILED(m_pKeyBoard->GetDeviceState(256, m_KeyState)))
		return;
	//마우스의 x,y,휠 이동 상태, L,R,휠의 클릭 상태를 받아온다.
	if (FAILED(m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_MouseState)))
		return;
}

void CInput_Device::Free()
{

}

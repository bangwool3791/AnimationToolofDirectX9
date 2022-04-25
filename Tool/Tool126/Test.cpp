#include "stdafx.h"
#include "Test.h"
#include "GameInstance.h"

vector<CTransform*> g_vecBoneTransfrom;
vector<CVIBuffer_Cube*> g_vecAniCube;
vector<CTest::TEST_STRUCT> g_vecAniInfo;
CTest* g_pTest;
void CTest::Tick(_float _fDeltaTime)
{
	__super::Tick(_fDeltaTime);
	//_float3 vPos = m_pBoneRootTransForm->Get_State(Engine::STATE_POSITION);
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	if (nullptr == pGameInstance)
		return;

	if (!g_vecBoneTransfrom.size())
		return;

	if (m_eAniMemoState != m_eAniState)
	{
		Clear_Flag(m_eAniState, _fDeltaTime);
		m_eAniMemoState = m_eAniState;
	}

	Safe_AddRef(pGameInstance);

	_float  fDir = 0.f;

	if (g_vecAniInfo[m_eAniState].uMotion SHIFT_OPERATOR(INV_ROOT))
		Set_Animation(ROOT, g_vecAniInfo[m_eAniState].m_varr[ROOT],
			g_vecAniInfo[m_eAniState].m_farr[ROOT], g_vecBoneTransfrom[ROOT]);

	if (g_vecAniInfo[m_eAniState].uMotion SHIFT_OPERATOR(INV_PELVIS))
		Set_Animation(PELVIS, g_vecAniInfo[m_eAniState].m_varr[PELVIS], 
			g_vecAniInfo[m_eAniState].m_farr[PELVIS], g_vecBoneTransfrom[PELVIS]);

	if (g_vecAniInfo[m_eAniState].uMotion SHIFT_OPERATOR(INV_SPINE))
		Set_Animation(SPINE, g_vecAniInfo[m_eAniState].m_varr[SPINE], 
			g_vecAniInfo[m_eAniState].m_farr[SPINE], g_vecBoneTransfrom[SPINE]);

	if (g_vecAniInfo[m_eAniState].uMotion SHIFT_OPERATOR(INV_NECK))
		Set_Animation(NECK, g_vecAniInfo[m_eAniState].m_varr[NECK], 
			g_vecAniInfo[m_eAniState].m_farr[NECK], g_vecBoneTransfrom[NECK]);

	if (g_vecAniInfo[m_eAniState].uMotion SHIFT_OPERATOR(INV_LEFTLEG))
		Set_Animation(LEFTLEG, g_vecAniInfo[m_eAniState].m_varr[LEFTLEG], 
			g_vecAniInfo[m_eAniState].m_farr[LEFTLEG], g_vecBoneTransfrom[LEFTLEG]);

	if (g_vecAniInfo[m_eAniState].uMotion SHIFT_OPERATOR(INV_RIGHTLEG))
		Set_Animation(RIGHTLEG, g_vecAniInfo[m_eAniState].m_varr[RIGHTLEG], 
			g_vecAniInfo[m_eAniState].m_farr[RIGHTLEG], g_vecBoneTransfrom[RIGHTLEG]);

	if (g_vecAniInfo[m_eAniState].uMotion SHIFT_OPERATOR(INV_LEFTARM))
		Set_Animation(LEFTARM, g_vecAniInfo[m_eAniState].m_varr[LEFTARM], 
			g_vecAniInfo[m_eAniState].m_farr[LEFTARM], g_vecBoneTransfrom[LEFTARM]);

	if (g_vecAniInfo[m_eAniState].uMotion SHIFT_OPERATOR(INV_RIGHTARM))
		Set_Animation(RIGHTARM, g_vecAniInfo[m_eAniState].m_varr[RIGHTARM], 
			g_vecAniInfo[m_eAniState].m_farr[RIGHTARM], g_vecBoneTransfrom[RIGHTARM]);
	//Modifying
	if (g_vecAniInfo[m_eAniState].uMotion SHIFT_OPERATOR(INV_LEFTELBOW))
		Set_Animation(LEFTELBOW, g_vecAniInfo[m_eAniState].m_varr[LEFTELBOW], 
			g_vecAniInfo[m_eAniState].m_farr[LEFTELBOW], g_vecBoneTransfrom[LEFTELBOW]);

	if (g_vecAniInfo[m_eAniState].uMotion SHIFT_OPERATOR(INV_RIGHTELBOW))
		Set_Animation(RIGHTELBOW, g_vecAniInfo[m_eAniState].m_varr[RIGHTELBOW], 
			g_vecAniInfo[m_eAniState].m_farr[RIGHTELBOW], g_vecBoneTransfrom[RIGHTELBOW]);

	if (g_vecAniInfo[m_eAniState].uMotion SHIFT_OPERATOR(INV_LEFTANKLE))
		Set_Animation(LEFTANKLE, g_vecAniInfo[m_eAniState].m_varr[LEFTANKLE], 
			g_vecAniInfo[m_eAniState].m_farr[LEFTANKLE], g_vecBoneTransfrom[LEFTANKLE]);

	if (g_vecAniInfo[m_eAniState].uMotion SHIFT_OPERATOR(INV_RIGHTANKLE))
		Set_Animation(RIGHTANKLE, g_vecAniInfo[m_eAniState].m_varr[RIGHTANKLE], 
			g_vecAniInfo[m_eAniState].m_farr[RIGHTANKLE], g_vecBoneTransfrom[RIGHTANKLE]);

	//if (GetAsyncKeyState('W') < 0)
	//{
	//	m_pBoneRootTransForm->Go_Straight(_fDeltaTime);
	//}
	//if (GetAsyncKeyState('S') < 0)
	//{
	//	m_pBoneRootTransForm->Go_Backward(_fDeltaTime);
	//}
	//if (GetAsyncKeyState('A') < 0)
	//{
	//	m_pBoneRootTransForm->Turn(_float3(0.f, 1.f, 0.f), _fDeltaTime);
	//}
	//if (GetAsyncKeyState('D') < 0)
	//{
	//	m_pBoneRootTransForm->Turn(_float3(0.f, 1.f, 0.f), -_fDeltaTime);
	//}

	if (g_vecAniInfo[m_eAniState].uMotion SHIFT_OPERATOR(INV_ROOT))
	if (g_vecAniInfo[m_eAniState].uFlag[ROOT] >> INV_ANI_SET & 0x01)
		if (!(g_vecAniInfo[m_eAniState].uFlag[ROOT] >> INV_ANI_END & 0x01))
	{
		_float fResult = g_vecBoneTransfrom[ROOT]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[ROOT], _fDeltaTime);

		switch (m_eAniState)
		{
		case TEST_STATE_DIE:
			if (fResult >= g_vecAniInfo[m_eAniState].fAngle[ROOT])
			{
				g_vecAniInfo[m_eAniState].uFlag[ROOT] |= (0x01 << INV_ANI_END);
			}
			break;
		}
	}

	if (g_vecAniInfo[m_eAniState].uMotion SHIFT_OPERATOR(INV_SPINE))
		if (g_vecAniInfo[m_eAniState].uFlag[SPINE] >> INV_ANI_SET & 0x01)
			if (!(g_vecAniInfo[m_eAniState].uFlag[SPINE] >> INV_ANI_END & 0x01))
			{
				_float fResult = g_vecBoneTransfrom[SPINE]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[SPINE], _fDeltaTime);

				switch (m_eAniState)
				{
				case TEST_STATE_DIE:
					if (fResult >= g_vecAniInfo[m_eAniState].fAngle[SPINE])
					{
						g_vecAniInfo[m_eAniState].uFlag[SPINE] |= (0x01 << INV_ANI_END);
					}
					break;
				}
			}

	if (g_vecAniInfo[m_eAniState].uMotion SHIFT_OPERATOR(INV_SPINE))
	if (g_vecAniInfo[m_eAniState].uFlag[SPINE] >> INV_ANI_SET & 0x01)
		if (!(g_vecAniInfo[m_eAniState].uFlag[SPINE] >> INV_ANI_END & 0x01))
		{
			_float fResult = g_vecBoneTransfrom[SPINE]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[SPINE], _fDeltaTime);

			switch (m_eAniState)
			{
			case TEST_STATE_DIE:
				if (fResult >= g_vecAniInfo[m_eAniState].fAngle[SPINE])
				{
					g_vecAniInfo[m_eAniState].uFlag[SPINE] |= (0x01 << INV_ANI_END);
				}
				break;
			}
		}

	if (g_vecAniInfo[m_eAniState].uMotion SHIFT_OPERATOR(INV_PELVIS))
	if (g_vecAniInfo[m_eAniState].uFlag[PELVIS] >> INV_ANI_SET & 0x01)
		if (!(g_vecAniInfo[m_eAniState].uFlag[PELVIS] >> INV_ANI_END & 0x01))
		{
			_float fResult = g_vecBoneTransfrom[PELVIS]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[PELVIS], _fDeltaTime);

			switch (m_eAniState)
			{
			case TEST_STATE_DIE:
				if (fResult >= g_vecAniInfo[m_eAniState].fAngle[PELVIS])
				{
					g_vecAniInfo[m_eAniState].uFlag[PELVIS] |= (0x01 << INV_ANI_END);
				}
				break;
			}
		}

	if (g_vecAniInfo[m_eAniState].uMotion SHIFT_OPERATOR(INV_LEFTLEG))
	if (g_vecAniInfo[m_eAniState].uFlag[LEFTLEG] >> INV_ANI_SET & 0x01)
		if (!(g_vecAniInfo[m_eAniState].uFlag[LEFTLEG] >> INV_ANI_END & 0x01))
		{
			_float fResult = g_vecBoneTransfrom[LEFTLEG]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[LEFTLEG], _fDeltaTime);

			switch (m_eAniState)
			{
			case TEST_STATE_DIE:
				if (fResult >= g_vecAniInfo[m_eAniState].fAngle[LEFTLEG])
				{
					g_vecAniInfo[m_eAniState].uFlag[LEFTLEG] |= (0x01 << INV_ANI_END);
				}
				break;
			}
		}

	if (g_vecAniInfo[m_eAniState].uMotion SHIFT_OPERATOR(INV_NECK))
		if (g_vecAniInfo[m_eAniState].uFlag[NECK] >> INV_ANI_SET & 0x01)
			if (!(g_vecAniInfo[m_eAniState].uFlag[NECK] >> INV_ANI_END & 0x01))
			{
				_float fResult = g_vecBoneTransfrom[NECK]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[NECK], _fDeltaTime);

				switch (m_eAniState)
				{
				case TEST_STATE_DIE:
					if (fResult >= g_vecAniInfo[m_eAniState].fAngle[NECK])
					{
						g_vecAniInfo[m_eAniState].uFlag[NECK] |= (0x01 << INV_ANI_END);
					}
					break;
				}

			}
	if (g_vecAniInfo[m_eAniState].uMotion SHIFT_OPERATOR(INV_RIGHTLEG))
	if (g_vecAniInfo[m_eAniState].uFlag[RIGHTLEG] >> INV_ANI_SET & 0x01)
		if (!(g_vecAniInfo[m_eAniState].uFlag[RIGHTLEG] >> INV_ANI_END & 0x01))
		{
			_float fResult = g_vecBoneTransfrom[RIGHTLEG]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[RIGHTLEG], _fDeltaTime);

			switch (m_eAniState)
			{
			case TEST_STATE_DIE:
				if (fResult >= g_vecAniInfo[m_eAniState].fAngle[RIGHTLEG])
				{
					g_vecAniInfo[m_eAniState].uFlag[RIGHTLEG] |= (0x01 << INV_ANI_END);
				}
				break;
			}
		}

	if (g_vecAniInfo[m_eAniState].uMotion SHIFT_OPERATOR(INV_LEFTARM))
	if (g_vecAniInfo[m_eAniState].uFlag[LEFTARM] >> INV_ANI_SET & 0x01)
		if (!(g_vecAniInfo[m_eAniState].uFlag[LEFTARM] >> INV_ANI_END & 0x01))
		{
			_float fResult = g_vecBoneTransfrom[LEFTARM]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[LEFTARM], _fDeltaTime);

			switch (m_eAniState)
			{
			case TEST_STATE_DIE:
				if (fResult >= g_vecAniInfo[m_eAniState].fAngle[LEFTARM])
				{
					g_vecAniInfo[m_eAniState].uFlag[LEFTARM] |= (0x01 << INV_ANI_END);
				}
				break;
			}
		}

	if (g_vecAniInfo[m_eAniState].uMotion SHIFT_OPERATOR(INV_RIGHTARM))
	if (g_vecAniInfo[m_eAniState].uFlag[RIGHTARM] >> INV_ANI_SET & 0x01)
		if (!(g_vecAniInfo[m_eAniState].uFlag[RIGHTARM] >> INV_ANI_END & 0x01))
		{
			_float fResult = g_vecBoneTransfrom[RIGHTARM]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[RIGHTARM], _fDeltaTime);

			switch (m_eAniState)
			{
			case TEST_STATE_DIE:
				if (fResult >= g_vecAniInfo[m_eAniState].fAngle[RIGHTARM])
				{
					g_vecAniInfo[m_eAniState].uFlag[RIGHTARM] |= (0x01 << INV_ANI_END);
				}
				break;
			}
		}
	
	if (g_vecAniInfo[m_eAniState].uMotion SHIFT_OPERATOR(INV_LEFTELBOW))
	if (g_vecAniInfo[m_eAniState].uFlag[LEFTELBOW] >> INV_ANI_SET & 0x01)
		if (!(g_vecAniInfo[m_eAniState].uFlag[LEFTELBOW] >> INV_ANI_END & 0x01))
		{
			_float fResult = g_vecBoneTransfrom[LEFTELBOW]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[LEFTELBOW], _fDeltaTime);

			switch (m_eAniState)
			{
			case TEST_STATE_DIE:
				if (fResult >= g_vecAniInfo[m_eAniState].fAngle[LEFTELBOW])
				{
					g_vecAniInfo[m_eAniState].uFlag[LEFTELBOW] |= (0x01 << INV_ANI_END);
				}
				break;
			}
		}

	if (g_vecAniInfo[m_eAniState].uMotion SHIFT_OPERATOR(INV_RIGHTELBOW))
	if (g_vecAniInfo[m_eAniState].uFlag[RIGHTELBOW] >> INV_ANI_SET & 0x01)
		if (!(g_vecAniInfo[m_eAniState].uFlag[RIGHTELBOW] >> INV_ANI_END & 0x01))
		{
			_float fResult = g_vecBoneTransfrom[RIGHTELBOW]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[RIGHTELBOW], _fDeltaTime);

			switch (m_eAniState)
			{
			case TEST_STATE_DIE:
				if (fResult >= g_vecAniInfo[m_eAniState].fAngle[RIGHTELBOW])
				{
					g_vecAniInfo[m_eAniState].uFlag[RIGHTELBOW] |= (0x01 << INV_ANI_END);
				}
				break;
			}
		}

	if (g_vecAniInfo[m_eAniState].uMotion SHIFT_OPERATOR(INV_LEFTANKLE))
	if (g_vecAniInfo[m_eAniState].uFlag[LEFTANKLE] >> INV_ANI_SET & 0x01)
		if (!(g_vecAniInfo[m_eAniState].uFlag[LEFTANKLE] >> INV_ANI_END & 0x01))
		{
			_float fResult = g_vecBoneTransfrom[LEFTANKLE]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[LEFTANKLE], _fDeltaTime);

			switch (m_eAniState)
			{
			case TEST_STATE_DIE:
				if (fResult >= g_vecAniInfo[m_eAniState].fAngle[LEFTANKLE])
				{
					g_vecAniInfo[m_eAniState].uFlag[LEFTANKLE] |= (0x01 << INV_ANI_END);
				}
				break;
			}
		}

	if (g_vecAniInfo[m_eAniState].uMotion SHIFT_OPERATOR(INV_RIGHTANKLE))
	if (g_vecAniInfo[m_eAniState].uFlag[RIGHTANKLE] >> INV_ANI_SET & 0x01)
		if (!(g_vecAniInfo[m_eAniState].uFlag[RIGHTANKLE] >> INV_ANI_END & 0x01))
		{
			_float fResult = g_vecBoneTransfrom[RIGHTANKLE]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[RIGHTANKLE], _fDeltaTime);

			switch (m_eAniState)
			{
			case TEST_STATE_DIE:
				if (fResult >= g_vecAniInfo[m_eAniState].fAngle[RIGHTANKLE])
				{
					g_vecAniInfo[m_eAniState].uFlag[RIGHTANKLE] |= (0x01 << INV_ANI_END);
				}
				break;
			}
		}

	if (GetAsyncKeyState('1') < 0)
	{
		Clear_Flag(m_eAniState, _fDeltaTime);
		m_eAniState = TEST_STATE_STUN;
	}

	if (GetAsyncKeyState('2') < 0)
	{
		Clear_Flag(m_eAniState, _fDeltaTime);
		m_eAniState = TEST_STATE_ATTACK;
	}

	if (GetAsyncKeyState('3') < 0)
	{
		Clear_Flag(m_eAniState, _fDeltaTime);
		m_eAniState = TEST_STATE_IDLE;
	}
	
	//static _long MouseMove = 0;

	//if (MouseMove = pGameInstance->Get_DIMMoveState(CInput_Device::DIMM_X))
	//{
	//	m_pBoneRootTransForm->Turn(_float3(0.f, 1.f, 0.f), _fDeltaTime * MouseMove * 0.1f);
	//	MouseMove = 0;
	//}

	//if (MouseMove = pGameInstance->Get_DIMMoveState(CInput_Device::DIMM_Y))
	//{
	//	m_pBoneRootTransForm->Turn(m_pBoneRootTransForm->Get_State(STATE_RIGHT), _fDeltaTime * MouseMove * 0.1f);
	//	MouseMove = 0;
	//}

	Safe_Release(pGameInstance);
}

void CTest::Late_Tick(_float _fDeltaTime)
{
	__super::Late_Tick(_fDeltaTime);
	m_pRendererCom->Add_RenderList(Engine::RENDER_PRIORITY, this);
}

HRESULT CTest::Render()
{
	if (!m_pGraphicDev) //|| !m_pBoneRootCube || !m_pBonePelvisCube || !m_pBoneSpineCube)
		return E_FAIL;

	if (__super::Render())
		return E_FAIL;

	g_pBone->Render();
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &g_vecBoneTransfrom[NECK]->Get_BindMatrix());
	g_vecAniCube[ANI_RECT_HEAD]->Render();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &g_vecBoneTransfrom[SPINE]->Get_BindMatrix());
	g_vecAniCube[ANI_RECT_BODY]->Render();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &g_vecBoneTransfrom[LEFTLEG]->Get_BindMatrix());
	g_vecAniCube[ANI_RECT_LEFT_LEG]->Render();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &g_vecBoneTransfrom[RIGHTLEG]->Get_BindMatrix());
	g_vecAniCube[ANI_RECT_RIGHT_LEG]->Render();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &g_vecBoneTransfrom[LEFTARM]->Get_BindMatrix());
	g_vecAniCube[ANI_RECT_LEFT_ARM]->Render();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &g_vecBoneTransfrom[RIGHTARM]->Get_BindMatrix());
	g_vecAniCube[ANI_RECT_RIGHT_ARM]->Render();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &g_vecBoneTransfrom[LEFTELBOW]->Get_BindMatrix());
	g_vecAniCube[ANI_RECT_LEFT_ELBOW]->Render();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &g_vecBoneTransfrom[RIGHTELBOW]->Get_BindMatrix());
	g_vecAniCube[ANI_RECT_RIGHT_ELBOW]->Render();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &g_vecBoneTransfrom[LEFTANKLE]->Get_BindMatrix());
	g_vecAniCube[ANI_RECT_LEFT_ANKLE]->Render();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &g_vecBoneTransfrom[RIGHTANKLE]->Get_BindMatrix());
	g_vecAniCube[ANI_RECT_RIGHT_ANKLE]->Render();

	return S_OK;
}

HRESULT CTest::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CTest::NativeConstruct(void* pArg)
{
	if (!m_pGraphicDev)
		return E_FAIL;

	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	//1111 1111
	//root - pelvis - spine - neck - leftleg - rightleg - leftarm - rightarm
	//0001 1111
	//x axis - y axis - z axis - plus - minus
	//Set Trans class the Angle
	_float fAngle = 0.f;
	g_vecAniInfo.reserve(TEST_STATE_END);
	//파일에서는 구조체의 배열을 받아온다.
	TEST_STRUCT stTest;
	ZeroMemory(&stTest, sizeof(TEST_STRUCT));
	stTest.uMotion = 0b000011110000;
	stTest.uDir[LEFTLEG] = (0x01 << INV_XAXIS) | (0x01 << INV_PLUS);
	stTest.uDir[RIGHTLEG] = (0x01 << INV_XAXIS) | (0x01 << INV_MINUS);
	stTest.uDir[LEFTARM] = (0x01 << INV_XAXIS) | (0x01 << INV_MINUS);
	stTest.uDir[RIGHTARM] = (0x01 << INV_XAXIS) | (0x01 << INV_PLUS);

	stTest.fAngle[LEFTLEG] = Engine::Math::PI / 3.f;
	stTest.fAngle[RIGHTLEG] = Engine::Math::PI / 3.f;
	stTest.fAngle[LEFTARM] = Engine::Math::PI / 3.f;
	stTest.fAngle[RIGHTARM] = Engine::Math::PI / 3.f;

	g_vecAniInfo.emplace_back(stTest);

	stTest.uMotion = 0b01010011;
	stTest.uDir[PELVIS] = (0x01 << INV_XAXIS) | (0x01 << INV_PLUS);
	stTest.fAngle[PELVIS] = Engine::Math::PI * 0.3;

	stTest.uDir[NECK] = (0x01 << INV_YAXIS) | (0x01 << INV_PLUS);
	stTest.fAngle[NECK] = Engine::Math::PI * 0.5;

	stTest.uDir[LEFTARM] = (0x01 << INV_XAXIS) | (0x01 << INV_ZAXIS) | (0x01 << INV_PLUS);
	stTest.fAngle[LEFTARM] = Engine::Math::PI * 0.3;

	stTest.uDir[RIGHTARM] = (0x01 << INV_XAXIS) | (0x01 << INV_ZAXIS) | (0x01 << INV_PLUS);
	stTest.fAngle[RIGHTARM] = Engine::Math::PI * 0.3;

	g_vecAniInfo.emplace_back(stTest);

	stTest.uMotion = 0x80;
	stTest.uDir[ROOT] = (0x01 << INV_XAXIS) | (0x01 << INV_PLUS);
	stTest.fAngle[ROOT] = Engine::Math::PI * 0.7;

	g_vecAniInfo.emplace_back(stTest);

	stTest.uMotion = 0x80;
	stTest.uDir[ROOT] = (0x01 << INV_XAXIS) | (0x01 << INV_PLUS);
	stTest.fAngle[ROOT] = Engine::Math::PI * 0.5;

	g_vecAniInfo.emplace_back(stTest);

	return S_OK;
}

HRESULT CTest::SetUp_Components()
{
	CGameInstance* pGameInstace = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstace);

	m_pRendererCom = (CRenderer*)pGameInstace->Clone_ComponentObject(0, Engine::KEY_COMPONENT_RENDERER, NULL);
	_float arrAniHeadRadius[4] = { 0.5f, 0.5f, -0.5f, 1.f };
	m_pAniHeadCube = (CVIBuffer_Cube*)pGameInstace->Clone_ComponentObject(0, Engine::KEY_COMPONENT_VI_CUBE, arrAniHeadRadius);
	_float arrAniBodyRadius[4] = { 0.5f, 0.5f, -0.5f, 0.f };
	m_pAniBodyCube = (CVIBuffer_Cube*)pGameInstace->Clone_ComponentObject(0, Engine::KEY_COMPONENT_VI_CUBE, arrAniBodyRadius);
	_float arrAniLeftLegRadius[4] = { 0.5f, 1.f, -1.f, -1.f };
	m_pAniLeftLegCube = (CVIBuffer_Cube*)pGameInstace->Clone_ComponentObject(0, Engine::KEY_COMPONENT_VI_CUBE, arrAniLeftLegRadius);
	_float arrAniRightLegRadius[4] = { 0.5f, 1.f, -1.f, -1.f };
	m_pAniRightLegCube = (CVIBuffer_Cube*)pGameInstace->Clone_ComponentObject(0, Engine::KEY_COMPONENT_VI_CUBE, arrAniRightLegRadius);
	_float arrAniLeftArmRadius[4] = { 0.5f, 1.f, -1.f, -1.f };
	m_pAniLeftArmCube = (CVIBuffer_Cube*)pGameInstace->Clone_ComponentObject(0, Engine::KEY_COMPONENT_VI_CUBE, arrAniLeftArmRadius);
	_float arrAniRightArmRadius[4] = { 0.5f, 1.f, -1.f, -1.f };
	m_pAniRightArmCube = (CVIBuffer_Cube*)pGameInstace->Clone_ComponentObject(0, Engine::KEY_COMPONENT_VI_CUBE, arrAniRightArmRadius);
	_float arrAniLeftElbowRadius[4] = { 0.5f, 0.5f, -0.5f, 1.f };
	m_pAniLeftElbowCube = (CVIBuffer_Cube*)pGameInstace->Clone_ComponentObject(0, Engine::KEY_COMPONENT_VI_CUBE, arrAniLeftElbowRadius);
	_float arrAniRightElbowRadius[4] = { 0.5f, 0.5f, -0.5f, 1.f };
	m_pAniRightElbowCube = (CVIBuffer_Cube*)pGameInstace->Clone_ComponentObject(0, Engine::KEY_COMPONENT_VI_CUBE, arrAniRightElbowRadius);
	_float arrAniLeftAnkleRadius[4] = { 0.5f, 0.5f, -0.5f, -1.f };
	m_pAniLeftAnkleCube = (CVIBuffer_Cube*)pGameInstace->Clone_ComponentObject(0, Engine::KEY_COMPONENT_VI_CUBE, arrAniLeftAnkleRadius);
	_float arrAniRightAnkleRadius[4] = { 0.5f, 0.5f, -0.5f, -1.f };
	m_pAniRightAnkleCube = (CVIBuffer_Cube*)pGameInstace->Clone_ComponentObject(0, Engine::KEY_COMPONENT_VI_CUBE, arrAniRightAnkleRadius);

	if (NULL == m_pRendererCom)// || NULL == m_pBoneRootCube || NULL == m_pBonePelvisCube)
	{
		Safe_Release(m_pRendererCom);
		Safe_Release(pGameInstace);
		//Safe_Release(m_pBoneRootCube);
		//Safe_Release(m_pBonePelvisCube);
		//Safe_Release(m_pBoneSpineCube);
		MSGBOX(TEXT("Failed to Init CTest"));
		return E_FAIL;
	}

	m_pBone = g_pBone = (CBone*)pGameInstace->Clone_ComponentObject(0, Engine::KEY_COMPONENT_BONE, NULL);
	if (!m_pBone)
		return E_FAIL;
	//Width, Top, Bottom, Pos
	_float arrBoneRadius[4] = { 0.05f, 0.05f, -0.05f, 0.f };
	//이거 본 클래스 안에서 함수화 시킬 것
	TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(TRANSFORMDESC));
	D3DXMatrixIdentity(&TransformDesc.LocalMatrix);
	D3DXMatrixIdentity(&TransformDesc.WorldMatrix);
	TransformDesc.fDir = 1.f;
	//add to root
	TransformDesc.vLocalPos = _float3{ 0.f, 0.f, 0.f };
	TransformDesc.fLocalAngle = 0.f;
	TransformDesc.vAxis = _float3{ 0.f, 0.f, 0.f };
	TransformDesc.LocalMatrix = Set_Matrix(TransformDesc.vLocalPos, TransformDesc.vAxis, TransformDesc.fLocalAngle);
	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = 1.f;

	m_pBone->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_ROOT, TransformDesc, arrBoneRadius);

	m_pBoneRootTransForm = (CTransform*)m_pBone->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_ROOT);

	//add to pelvis
	TransformDesc.vLocalPos = _float3{ 0.f, 1.f, 0.f };
	TransformDesc.fLocalAngle = 0.f;//Engine::Math::PI * 0.5;
	TransformDesc.vAxis = _float3{ -1.f, 0.f, 0.f };
	TransformDesc.LocalMatrix = Set_Matrix(TransformDesc.vLocalPos, TransformDesc.vAxis, TransformDesc.fLocalAngle);
	m_pBone->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_PELVIS, TransformDesc, arrBoneRadius);
	m_pBonePelvisTransForm = (CTransform*)m_pBone->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_PELVIS);

	//add to spine
	TransformDesc.vLocalPos = _float3{ 0.f, 1.f, 0.f };
	TransformDesc.fLocalAngle = 0.f;
	TransformDesc.vAxis = _float3{ 0.f, 0.f, 0.f };
	TransformDesc.LocalMatrix = Set_Matrix(TransformDesc.vLocalPos, TransformDesc.vAxis, TransformDesc.fLocalAngle);
	m_pBone->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_SPINE, TransformDesc, arrBoneRadius);
	m_pBoneSpineTransForm = (CTransform*)m_pBone->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_SPINE);

	//add to Neck
	TransformDesc.vLocalPos = _float3{ 0.f, 1.f, 0.f };
	TransformDesc.fLocalAngle = 0.f;
	TransformDesc.vAxis = _float3{ 0.f, 0.f, 0.f };
	TransformDesc.LocalMatrix = Set_Matrix(TransformDesc.vLocalPos, TransformDesc.vAxis, TransformDesc.fLocalAngle);
	m_pBone->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_NECK, TransformDesc, arrBoneRadius);
	m_pBoneNeckTransForm = (CTransform*)m_pBone->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_NECK);

	//add to LeftLeg
	TransformDesc.vLocalPos = _float3{ 1.f, 0.f, 0.f };
	TransformDesc.fLocalAngle = 0.f;
	TransformDesc.vAxis = _float3{ 0.f, 0.f, 0.f };
	TransformDesc.LocalMatrix = Set_Matrix(TransformDesc.vLocalPos, TransformDesc.vAxis, TransformDesc.fLocalAngle);
	m_pBone->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTLEG, TransformDesc, arrBoneRadius);
	m_pBoneLeftLegTransForm = (CTransform*)m_pBone->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTLEG);

	//add to RightLeg
	TransformDesc.vLocalPos = _float3{ 1.f * -1.f, 0.f, 0.f };
	TransformDesc.fLocalAngle = 0.f;
	TransformDesc.vAxis = _float3{ 0.f, 0.f, 0.f };
	TransformDesc.LocalMatrix = Set_Matrix(TransformDesc.vLocalPos, TransformDesc.vAxis, TransformDesc.fLocalAngle);
	m_pBone->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTLEG, TransformDesc, arrBoneRadius);
	m_pBoneRightLegTransForm = (CTransform*)m_pBone->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTLEG);

	//add to LeftArm
	TransformDesc.vLocalPos = _float3{ 1.f, 1.f, 0.f };
	TransformDesc.fLocalAngle = 0.f;
	TransformDesc.vAxis = _float3{ 0.f, 0.f, 0.f };
	TransformDesc.LocalMatrix = Set_Matrix(TransformDesc.vLocalPos, TransformDesc.vAxis, TransformDesc.fLocalAngle);
	m_pBone->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTARM, TransformDesc, arrBoneRadius);
	m_pBoneLeftArmTransForm = (CTransform*)m_pBone->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTARM);

	//add to RightArm
	TransformDesc.vLocalPos = _float3{ 1.f * -1.f, 1.f, 0.f };
	TransformDesc.fLocalAngle = 0.f;
	TransformDesc.vAxis = _float3{ 0.f, 0.f, 0.f };
	TransformDesc.LocalMatrix = Set_Matrix(TransformDesc.vLocalPos, TransformDesc.vAxis, TransformDesc.fLocalAngle);
	m_pBone->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTARM, TransformDesc, arrBoneRadius);
	m_pBoneRightArmTransForm = (CTransform*)m_pBone->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTARM);

	//Left Elbow
	TransformDesc.vLocalPos = _float3{ 0.f, -1.5f, 0.f };
	TransformDesc.fLocalAngle = Engine::Math::PI * 0.5f;
	TransformDesc.vAxis = _float3{ 1.f, 0.f, 0.f };
	TransformDesc.LocalMatrix = Set_Matrix(TransformDesc.vLocalPos, TransformDesc.vAxis, TransformDesc.fLocalAngle);
	m_pBone->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTELBOW, TransformDesc, arrBoneRadius);
	m_pBoneLeftElbowTransForm = (CTransform*)m_pBone->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTELBOW);

	//Right Elbow
	TransformDesc.vLocalPos = _float3{ 0.f, -1.5f, 0.f };
	TransformDesc.fLocalAngle = Engine::Math::PI * 0.5f;
	TransformDesc.vAxis = _float3{ 1.f, 0.f, 0.f };
	TransformDesc.LocalMatrix = Set_Matrix(TransformDesc.vLocalPos, TransformDesc.vAxis, TransformDesc.fLocalAngle);
	m_pBone->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTELBOW, TransformDesc, arrBoneRadius);
	m_pBoneRightElbowTransForm = (CTransform*)m_pBone->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTELBOW);

	//Left Elbow
	TransformDesc.vLocalPos = _float3{ 0.f, -1.5f, 0.f };
	TransformDesc.fLocalAngle = Engine::Math::PI * 0.5f;
	TransformDesc.vAxis = _float3{ 1.f, 0.f, 0.f };
	TransformDesc.LocalMatrix = Set_Matrix(TransformDesc.vLocalPos, TransformDesc.vAxis, TransformDesc.fLocalAngle);
	m_pBone->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTANKLE, TransformDesc, arrBoneRadius);
	m_pBoneLeftAnkleTransForm = (CTransform*)m_pBone->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTANKLE);

	//Right Elbow
	TransformDesc.vLocalPos = _float3{ 0.f, -1.5f, 0.f };
	TransformDesc.fLocalAngle = Engine::Math::PI * 0.5f;
	TransformDesc.vAxis = _float3{ 1.f, 0.f, 0.f };
	TransformDesc.LocalMatrix = Set_Matrix(TransformDesc.vLocalPos, TransformDesc.vAxis, TransformDesc.fLocalAngle);
	m_pBone->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTANKLE, TransformDesc, arrBoneRadius);
	m_pBoneRightAnkleTransForm = (CTransform*)m_pBone->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTANKLE);

	//bine root

	//bind pelvis
	m_pBone->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_ROOT, Engine::KEY_BONE_PELVIS);
	//bind spine
	m_pBone->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_PELVIS, Engine::KEY_BONE_SPINE);
	//bind neck
	m_pBone->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_SPINE, Engine::KEY_BONE_NECK);
	//bind left leg
	m_pBone->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_PELVIS, Engine::KEY_BONE_LEFTLEG);
	//bind right leg
	m_pBone->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_PELVIS, Engine::KEY_BONE_RIGHTLEG);
	//bind right arm
	m_pBone->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_SPINE, Engine::KEY_BONE_LEFTARM);
	//bind right leg
	m_pBone->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_SPINE, Engine::KEY_BONE_RIGHTARM);
	//bind left elbow
	m_pBone->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTARM, Engine::KEY_BONE_LEFTELBOW);
	//bind right elbow
	m_pBone->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTARM, Engine::KEY_BONE_RIGHTELBOW);
	//bind left ankle
	m_pBone->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTLEG, Engine::KEY_BONE_LEFTANKLE);
	//bind right ankle
	m_pBone->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTLEG, Engine::KEY_BONE_RIGHTANKLE);
	//Release local component
	Safe_AddRef(m_pRendererCom);
	Safe_Release(pGameInstace);

	//pushback Bone Pointer used ToolView
	g_vecBoneTransfrom.push_back(m_pBoneRootTransForm);
	g_vecBoneTransfrom.push_back(m_pBonePelvisTransForm);
	g_vecBoneTransfrom.push_back(m_pBoneSpineTransForm);
	g_vecBoneTransfrom.push_back(m_pBoneNeckTransForm);
	g_vecBoneTransfrom.push_back(m_pBoneLeftLegTransForm);
	g_vecBoneTransfrom.push_back(m_pBoneRightLegTransForm);
	g_vecBoneTransfrom.push_back(m_pBoneLeftArmTransForm);
	g_vecBoneTransfrom.push_back(m_pBoneRightArmTransForm);
	g_vecBoneTransfrom.push_back(m_pBoneLeftElbowTransForm);
	g_vecBoneTransfrom.push_back(m_pBoneRightElbowTransForm);
	g_vecBoneTransfrom.push_back(m_pBoneLeftAnkleTransForm);
	g_vecBoneTransfrom.push_back(m_pBoneRightAnkleTransForm);

	g_vecAniCube.push_back(m_pAniHeadCube);
	g_vecAniCube.push_back(m_pAniBodyCube);
	g_vecAniCube.push_back(m_pAniLeftArmCube);
	g_vecAniCube.push_back(m_pAniRightArmCube);
	g_vecAniCube.push_back(m_pAniLeftLegCube);
	g_vecAniCube.push_back(m_pAniRightLegCube);
	g_vecAniCube.push_back(m_pAniLeftElbowCube);
	g_vecAniCube.push_back(m_pAniRightElbowCube);
	g_vecAniCube.push_back(m_pAniLeftAnkleCube);
	g_vecAniCube.push_back(m_pAniRightAnkleCube);
	return S_OK;
}

CTest* CTest::Clone(void* pArg)
{
	CTest * pInstance = new CTest(*this);
	g_pTest = pInstance;
	if (!pInstance)
		return NULL;

	if (FAILED(pInstance->NativeConstruct(pArg)))
		return NULL;

	//if (FAILED(m_pBoneRootCube->NativeConstruct(pArg)))
	//{
	//	
	//}
	return pInstance;
}

void CTest::Free()
{
	cout << "[CTest Free]" << endl;
	__super::Free();
	Safe_Release(m_pRendererCom);

	//Safe_Release(m_pBoneRootTransForm);

	//Safe_Release(m_pBonePelvisTransForm);

	//Safe_Release(m_pBoneSpineTransForm);

	//Safe_Release(m_pBoneNeckTransForm);

	//Safe_Release(m_pBoneLeftLegTransForm);

	//Safe_Release(m_pBoneRightLegTransForm);

	//Safe_Release(m_pBoneLeftArmTransForm);

	//Safe_Release(m_pBoneRightArmTransForm);

	//Safe_Release(m_pBoneLeftElbowTransForm);
	//Safe_Release(m_pBoneRightElbowTransForm);

	//Safe_Release(m_pBoneLeftAnkleTransForm);
	//Safe_Release(m_pBoneRightAnkleTransForm);
	//Release Bone
	//Safe_Release(m_pBone);

	//Safe_Release(m_pAniHeadCube);
	//Safe_Release(m_pAniBodyCube);
	//Safe_Release(m_pAniLeftLegCube);
	//Safe_Release(m_pAniRightLegCube);
	//Safe_Release(m_pAniLeftArmCube);
	//Safe_Release(m_pAniRightArmCube);
	//Safe_Release(m_pAniLeftElbowCube);
	//Safe_Release(m_pAniRightElbowCube);
	//Safe_Release(m_pAniLeftAnkleCube);
	//Safe_Release(m_pAniRightAnkleCube);
}

void CTest::Clear_Flag(TEST_STATE eState, _float _fDeltaTime)
{
	m_pBone->Clear_BoneAngle(Engine::BONE_LAYER_PLAYER);

	if (g_vecAniInfo[m_eAniState].uFlag[ROOT] >> INV_ANI_SET & 0x01)
		g_vecBoneTransfrom[ROOT]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[ROOT], _fDeltaTime);
	if (g_vecAniInfo[m_eAniState].uFlag[PELVIS] >> INV_ANI_SET & 0x01)
		g_vecBoneTransfrom[PELVIS]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[PELVIS], _fDeltaTime);
	if (g_vecAniInfo[m_eAniState].uFlag[SPINE] >> INV_ANI_SET & 0x01)
		g_vecBoneTransfrom[SPINE]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[SPINE], _fDeltaTime);
	if (g_vecAniInfo[m_eAniState].uFlag[LEFTLEG] >> INV_ANI_SET & 0x01)
		g_vecBoneTransfrom[LEFTLEG]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[LEFTLEG], _fDeltaTime);
	if (g_vecAniInfo[m_eAniState].uFlag[RIGHTLEG] >> INV_ANI_SET & 0x01)
		g_vecBoneTransfrom[RIGHTLEG]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[RIGHTLEG], _fDeltaTime);
	if (g_vecAniInfo[m_eAniState].uFlag[LEFTARM] >> INV_ANI_SET & 0x01)
		g_vecBoneTransfrom[LEFTARM]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[LEFTARM], _fDeltaTime);
	if (g_vecAniInfo[m_eAniState].uFlag[RIGHTARM] >> INV_ANI_SET & 0x01)
		g_vecBoneTransfrom[RIGHTARM]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[RIGHTARM], _fDeltaTime);

	for (int i = 0; i < ANIMATION_STATE_END; ++i)
	{
		g_vecAniInfo[eState].uFlag[i] = 0x00;
	}
	//m_eAniState = TEST_STATE_IDLE;
}

void CTest::Set_Animation(ANIMATION_STATE eState, _float3& vAxis, _float fDir, CTransform* _pTransForm)
{
	if (!(g_vecAniInfo[m_eAniState].uFlag[eState] >> INV_ANI_SET))
	{
		if (g_vecAniInfo[m_eAniState].uDir[eState] >> INV_XAXIS && 0x01)
			vAxis.x = TRUE;
		else if (g_vecAniInfo[m_eAniState].uDir[eState] >> INV_YAXIS & 0x01)
			vAxis.y = TRUE;
		else if (g_vecAniInfo[m_eAniState].uDir[eState] >> INV_ZAXIS & 0x01)
			vAxis.z = TRUE;

		if (g_vecAniInfo[m_eAniState].uDir[eState] >> INV_PLUS & 0x01)
			fDir = 1.f;
		else if (g_vecAniInfo[m_eAniState].uDir[eState] >> INV_MINUS & 0x01)
			fDir = -1.f;

		g_vecAniInfo[m_eAniState].uFlag[eState] = 0x01 << (INV_ANI_SET);

		_pTransForm->Set_Animation(g_vecAniInfo[m_eAniState].fAngle[eState], fDir);
	}
}
#include "stdafx.h"
#include "Test.h"
#include "GameInstance.h"

vector<vector<CTransform*>> g_vecBoneTransfrom;
vector<CVIBuffer_Cube*> g_vecAniCube;
vector<CTest::TEST_STRUCT> g_vecAniInfo;
CTest* g_pTest;
vector<CBone *> g_pBone;

void CTest::Tick(_float _fDeltaTime)
{
	__super::Tick(_fDeltaTime);
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	if (nullptr == pGameInstance)
		return;

	if (!g_vecBoneTransfrom[m_eAniState].size())
		return;

	if (m_eAniMemoState != m_eAniState)
	{
		Clear_Flag(m_eAniState, _fDeltaTime);
		m_eAniMemoState = m_eAniState;
	}
	Safe_AddRef(pGameInstance);

	_float  fDir = 0.f;
	//수정
	if (g_vecAniInfo[m_eAniState].uMotion SHIFT_OPERATOR(INV_ROOT))
			if (!(g_vecAniInfo[m_eAniState].uFlag[ROOT] >> INV_ANI_END & 0x01))
			{
				_float fResult = g_vecBoneTransfrom[m_eAniState][ROOT]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[ROOT], _fDeltaTime);

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
			if (!(g_vecAniInfo[m_eAniState].uFlag[SPINE] >> INV_ANI_END & 0x01))
			{
				_float fResult = g_vecBoneTransfrom[m_eAniState][SPINE]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[SPINE], _fDeltaTime);

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
			if (!(g_vecAniInfo[m_eAniState].uFlag[SPINE] >> INV_ANI_END & 0x01))
			{
				_float fResult = g_vecBoneTransfrom[m_eAniState][SPINE]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[SPINE], _fDeltaTime);

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
			if (!(g_vecAniInfo[m_eAniState].uFlag[PELVIS] >> INV_ANI_END & 0x01))
			{
				_float fResult = g_vecBoneTransfrom[m_eAniState][PELVIS]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[PELVIS], _fDeltaTime);

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
			if (!(g_vecAniInfo[m_eAniState].uFlag[LEFTLEG] >> INV_ANI_END & 0x01))
			{
				_float fResult = g_vecBoneTransfrom[m_eAniState][LEFTLEG]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[LEFTLEG], _fDeltaTime);

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
			if (!(g_vecAniInfo[m_eAniState].uFlag[NECK] >> INV_ANI_END & 0x01))
			{
				_float fResult = g_vecBoneTransfrom[m_eAniState][NECK]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[NECK], _fDeltaTime);

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
			if (!(g_vecAniInfo[m_eAniState].uFlag[RIGHTLEG] >> INV_ANI_END & 0x01))
			{
				_float fResult = g_vecBoneTransfrom[m_eAniState][RIGHTLEG]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[RIGHTLEG], _fDeltaTime);

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
			if (!(g_vecAniInfo[m_eAniState].uFlag[LEFTARM] >> INV_ANI_END & 0x01))
			{
				_float fResult = g_vecBoneTransfrom[m_eAniState][LEFTARM]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[LEFTARM], _fDeltaTime);

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
			if (!(g_vecAniInfo[m_eAniState].uFlag[RIGHTARM] >> INV_ANI_END & 0x01))
			{
				_float fResult = g_vecBoneTransfrom[m_eAniState][RIGHTARM]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[RIGHTARM], _fDeltaTime);

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
			if (!(g_vecAniInfo[m_eAniState].uFlag[LEFTELBOW] >> INV_ANI_END & 0x01))
			{
				_float fResult = g_vecBoneTransfrom[m_eAniState][LEFTELBOW]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[LEFTELBOW], _fDeltaTime);

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
			if (!(g_vecAniInfo[m_eAniState].uFlag[RIGHTELBOW] >> INV_ANI_END & 0x01))
			{
				_float fResult = g_vecBoneTransfrom[m_eAniState][RIGHTELBOW]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[RIGHTELBOW], _fDeltaTime);

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
			if (!(g_vecAniInfo[m_eAniState].uFlag[LEFTANKLE] >> INV_ANI_END & 0x01))
			{
				_float fResult = g_vecBoneTransfrom[m_eAniState][LEFTANKLE]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[LEFTANKLE], _fDeltaTime);

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
			if (!(g_vecAniInfo[m_eAniState].uFlag[RIGHTANKLE] >> INV_ANI_END & 0x01))
			{
				_float fResult = g_vecBoneTransfrom[m_eAniState][RIGHTANKLE]->Turn_Local(g_vecAniInfo[m_eAniState].m_varr[RIGHTANKLE], _fDeltaTime);

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

	g_pBone[m_eAniState]->Render();
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &g_vecBoneTransfrom[m_eAniState][NECK]->Get_BindMatrix());
	g_vecAniCube[ANI_RECT_HEAD]->Render();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &g_vecBoneTransfrom[m_eAniState][SPINE]->Get_BindMatrix());
	g_vecAniCube[ANI_RECT_BODY]->Render();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &g_vecBoneTransfrom[m_eAniState][LEFTLEG]->Get_BindMatrix());
	g_vecAniCube[ANI_RECT_LEFT_LEG]->Render();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &g_vecBoneTransfrom[m_eAniState][RIGHTLEG]->Get_BindMatrix());
	g_vecAniCube[ANI_RECT_RIGHT_LEG]->Render();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &g_vecBoneTransfrom[m_eAniState][LEFTARM]->Get_BindMatrix());
	g_vecAniCube[ANI_RECT_LEFT_ARM]->Render();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &g_vecBoneTransfrom[m_eAniState][RIGHTARM]->Get_BindMatrix());
	g_vecAniCube[ANI_RECT_RIGHT_ARM]->Render();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &g_vecBoneTransfrom[m_eAniState][LEFTELBOW]->Get_BindMatrix());
	g_vecAniCube[ANI_RECT_LEFT_ELBOW]->Render();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &g_vecBoneTransfrom[m_eAniState][RIGHTELBOW]->Get_BindMatrix());
	g_vecAniCube[ANI_RECT_RIGHT_ELBOW]->Render();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &g_vecBoneTransfrom[m_eAniState][LEFTANKLE]->Get_BindMatrix());
	g_vecAniCube[ANI_RECT_LEFT_ANKLE]->Render();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &g_vecBoneTransfrom[m_eAniState][RIGHTANKLE]->Get_BindMatrix());
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

	g_vecAniInfo.push_back(stTest);
	g_vecAniInfo.push_back(stTest);
	g_vecAniInfo.push_back(stTest);
	g_vecAniInfo.push_back(stTest);
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
	_float arrAniLeftLegRadius[4] = { 0.5f, 0.5f, -0.5f, -1.f };
	m_pAniLeftLegCube = (CVIBuffer_Cube*)pGameInstace->Clone_ComponentObject(0, Engine::KEY_COMPONENT_VI_CUBE, arrAniLeftLegRadius);
	_float arrAniRightLegRadius[4] = { 0.5f, 0.5f, -0.5f, -1.f };
	m_pAniRightLegCube = (CVIBuffer_Cube*)pGameInstace->Clone_ComponentObject(0, Engine::KEY_COMPONENT_VI_CUBE, arrAniRightLegRadius);
	_float arrAniLeftArmRadius[4] = { 0.5f, 0.5f, -0.5f, -1.f };
	m_pAniLeftArmCube = (CVIBuffer_Cube*)pGameInstace->Clone_ComponentObject(0, Engine::KEY_COMPONENT_VI_CUBE, arrAniLeftArmRadius);
	_float arrAniRightArmRadius[4] = { 0.5f, 0.5f, -0.5f, -1.f };
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

	m_pBone.push_back((CBone*)pGameInstace->Clone_ComponentObject(0, Engine::KEY_COMPONENT_BONE, NULL));
	m_pBone.push_back((CBone*)pGameInstace->Clone_ComponentObject(0, Engine::KEY_COMPONENT_BONE, NULL));
	m_pBone.push_back((CBone*)pGameInstace->Clone_ComponentObject(0, Engine::KEY_COMPONENT_BONE, NULL));
	m_pBone.push_back((CBone*)pGameInstace->Clone_ComponentObject(0, Engine::KEY_COMPONENT_BONE, NULL));
	g_pBone = m_pBone;
	//Width, Top, Bottom, Pos
	_float arrBoneRadius[4] = { 0.025f, 0.025f, -0.025f, 0.f };
	//이거 본 클래스 안에서 함수화 시킬 것
	TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(TRANSFORMDESC));
	D3DXMatrixIdentity(&TransformDesc.LocalMatrix);
	D3DXMatrixIdentity(&TransformDesc.WorldMatrix);
	TransformDesc.fDir = 1.f;
	//add to root
	TransformDesc.vLocalPos = _float3{ 0.f, 0.f, 0.f };
	TransformDesc.fLocalAngle = 0.f;
	TransformDesc.vAxis = _float3{ 1.f, 0.f, 0.f };
	TransformDesc.LocalMatrix = Set_Matrix(TransformDesc.vLocalPos, TransformDesc.vAxis, TransformDesc.fLocalAngle);
	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = 1.f;

	//Release local component
	Safe_AddRef(m_pRendererCom);
	Safe_Release(pGameInstace);

	//pushback Bone Pointer used ToolView
	g_vecBoneTransfrom.push_back(vector<CTransform*>());
	g_vecBoneTransfrom.push_back(vector<CTransform*>());
	g_vecBoneTransfrom.push_back(vector<CTransform*>());
	g_vecBoneTransfrom.push_back(vector<CTransform*>());

	for (int i = 0; i < TEST_STATE_END; ++i)
	{
		m_pBone[i]->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_ROOT, TransformDesc, arrBoneRadius);

		m_pBoneRootTransForm = (CTransform*)m_pBone[i]->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_ROOT);

		//add to pelvis
		TransformDesc.vLocalPos = _float3{ 0.f, 1.f, 0.f };
		TransformDesc.LocalMatrix = Set_Matrix(TransformDesc.vLocalPos, TransformDesc.vAxis, TransformDesc.fLocalAngle);
		m_pBone[i]->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_PELVIS, TransformDesc, arrBoneRadius);
		m_pBonePelvisTransForm = (CTransform*)m_pBone[i]->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_PELVIS);

		//add to spine
		TransformDesc.vLocalPos = _float3{ 0.f, 1.f, 0.f };
		TransformDesc.LocalMatrix = Set_Matrix(TransformDesc.vLocalPos, TransformDesc.vAxis, TransformDesc.fLocalAngle);
		m_pBone[i]->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_SPINE, TransformDesc, arrBoneRadius);
		m_pBoneSpineTransForm = (CTransform*)m_pBone[i]->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_SPINE);

		//add to Neck
		TransformDesc.vLocalPos = _float3{ 0.f, 1.f, 0.f };
		TransformDesc.LocalMatrix = Set_Matrix(TransformDesc.vLocalPos, TransformDesc.vAxis, TransformDesc.fLocalAngle);
		m_pBone[i]->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_NECK, TransformDesc, arrBoneRadius);
		m_pBoneNeckTransForm = (CTransform*)m_pBone[i]->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_NECK);

		//add to LeftLeg
		TransformDesc.vLocalPos = _float3{ 1.f, 0.f, 0.f };
		TransformDesc.LocalMatrix = Set_Matrix(TransformDesc.vLocalPos, TransformDesc.vAxis, TransformDesc.fLocalAngle);
		m_pBone[i]->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTLEG, TransformDesc, arrBoneRadius);
		m_pBoneLeftLegTransForm = (CTransform*)m_pBone[i]->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTLEG);

		//add to RightLeg
		TransformDesc.vLocalPos = _float3{ 1.f * -1.f, 0.f, 0.f };
		TransformDesc.LocalMatrix = Set_Matrix(TransformDesc.vLocalPos, TransformDesc.vAxis, TransformDesc.fLocalAngle);
		m_pBone[i]->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTLEG, TransformDesc, arrBoneRadius);
		m_pBoneRightLegTransForm = (CTransform*)m_pBone[i]->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTLEG);

		//add to LeftArm
		TransformDesc.vLocalPos = _float3{ 1.f, 1.f, 0.f };
		TransformDesc.LocalMatrix = Set_Matrix(TransformDesc.vLocalPos, TransformDesc.vAxis, TransformDesc.fLocalAngle);
		m_pBone[i]->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTARM, TransformDesc, arrBoneRadius);
		m_pBoneLeftArmTransForm = (CTransform*)m_pBone[i]->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTARM);

		//add to RightArm
		TransformDesc.vLocalPos = _float3{ 1.f * -1.f, 1.f, 0.f };
		TransformDesc.fLocalAngle = 0.f;
		TransformDesc.LocalMatrix = Set_Matrix(TransformDesc.vLocalPos, TransformDesc.vAxis, TransformDesc.fLocalAngle);
		m_pBone[i]->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTARM, TransformDesc, arrBoneRadius);
		m_pBoneRightArmTransForm = (CTransform*)m_pBone[i]->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTARM);

		//Left Elbow
		TransformDesc.vLocalPos = _float3{ 0.f, -1.5f, 0.f };
		TransformDesc.fLocalAngle = Engine::Math::PI * 0.5f;
		TransformDesc.vAxis = _float3{ 1.f, 0.f, 0.f };
		TransformDesc.LocalMatrix = Set_Matrix(TransformDesc.vLocalPos, TransformDesc.vAxis, TransformDesc.fLocalAngle);
		m_pBone[i]->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTELBOW, TransformDesc, arrBoneRadius);
		m_pBoneLeftElbowTransForm = (CTransform*)m_pBone[i]->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTELBOW);

		//Right Elbow
		TransformDesc.vLocalPos = _float3{ 0.f, -1.5f, 0.f };
		TransformDesc.fLocalAngle = Engine::Math::PI * 0.5f;
		TransformDesc.vAxis = _float3{ 1.f, 0.f, 0.f };
		TransformDesc.LocalMatrix = Set_Matrix(TransformDesc.vLocalPos, TransformDesc.vAxis, TransformDesc.fLocalAngle);
		m_pBone[i]->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTELBOW, TransformDesc, arrBoneRadius);
		m_pBoneRightElbowTransForm = (CTransform*)m_pBone[i]->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTELBOW);

		//Left Elbow
		TransformDesc.vLocalPos = _float3{ 0.f, -1.5f, 0.f };
		TransformDesc.fLocalAngle = Engine::Math::PI * 0.5f;
		TransformDesc.vAxis = _float3{ 1.f, 0.f, 0.f };
		TransformDesc.LocalMatrix = Set_Matrix(TransformDesc.vLocalPos, TransformDesc.vAxis, TransformDesc.fLocalAngle);
		m_pBone[i]->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTANKLE, TransformDesc, arrBoneRadius);
		m_pBoneLeftAnkleTransForm = (CTransform*)m_pBone[i]->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTANKLE);

		//Right Elbow
		TransformDesc.vLocalPos = _float3{ 0.f, -1.5f, 0.f };
		TransformDesc.fLocalAngle = Engine::Math::PI * 0.5f;
		TransformDesc.vAxis = _float3{ 1.f, 0.f, 0.f };
		TransformDesc.LocalMatrix = Set_Matrix(TransformDesc.vLocalPos, TransformDesc.vAxis, TransformDesc.fLocalAngle);
		m_pBone[i]->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTANKLE, TransformDesc, arrBoneRadius);
		m_pBoneRightAnkleTransForm = (CTransform*)m_pBone[i]->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTANKLE);

		//bine root

		//bind pelvis
		m_pBone[i]->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_ROOT, Engine::KEY_BONE_PELVIS);
		//bind spine
		m_pBone[i]->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_PELVIS, Engine::KEY_BONE_SPINE);
		//bind neck
		m_pBone[i]->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_SPINE, Engine::KEY_BONE_NECK);
		//bind left leg
		m_pBone[i]->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_PELVIS, Engine::KEY_BONE_LEFTLEG);
		//bind right leg
		m_pBone[i]->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_PELVIS, Engine::KEY_BONE_RIGHTLEG);
		//bind right arm
		m_pBone[i]->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_SPINE, Engine::KEY_BONE_LEFTARM);
		//bind right leg
		m_pBone[i]->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_SPINE, Engine::KEY_BONE_RIGHTARM);
		//bind left elbow
		m_pBone[i]->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTARM, Engine::KEY_BONE_LEFTELBOW);
		//bind right elbow
		m_pBone[i]->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTARM, Engine::KEY_BONE_RIGHTELBOW);
		//bind left ankle
		m_pBone[i]->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTLEG, Engine::KEY_BONE_LEFTANKLE);
		//bind right ankle
		m_pBone[i]->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTLEG, Engine::KEY_BONE_RIGHTANKLE);

		g_vecBoneTransfrom[i].push_back(m_pBoneRootTransForm);
		g_vecBoneTransfrom[i].push_back(m_pBonePelvisTransForm);
		g_vecBoneTransfrom[i].push_back(m_pBoneSpineTransForm);
		g_vecBoneTransfrom[i].push_back(m_pBoneNeckTransForm);
		g_vecBoneTransfrom[i].push_back(m_pBoneLeftLegTransForm);
		g_vecBoneTransfrom[i].push_back(m_pBoneRightLegTransForm);
		g_vecBoneTransfrom[i].push_back(m_pBoneLeftArmTransForm);
		g_vecBoneTransfrom[i].push_back(m_pBoneRightArmTransForm);
		g_vecBoneTransfrom[i].push_back(m_pBoneLeftElbowTransForm);
		g_vecBoneTransfrom[i].push_back(m_pBoneRightElbowTransForm);
		g_vecBoneTransfrom[i].push_back(m_pBoneLeftAnkleTransForm);
		g_vecBoneTransfrom[i].push_back(m_pBoneRightAnkleTransForm);
	}

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

	return pInstance;
}

void CTest::Free()
{
	cout << "[CTest Free]" << endl;
	__super::Free();
	Safe_Release(m_pRendererCom);

	for (int j = 0; j < CTest::TEST_STATE_END; ++j)
	{
		Safe_Release(g_pBone[j]);
	}

	for (int j = 0; j < CTest::ANI_RECT_END; ++j)
	{
		Safe_Release(g_vecAniCube[j]);
	}
}

void CTest::Clear_Flag(TEST_STATE eState, _float _fDeltaTime)
{
	//m_pBone[eState]->Clear_BoneAngle(Engine::BONE_LAYER_PLAYER);
}

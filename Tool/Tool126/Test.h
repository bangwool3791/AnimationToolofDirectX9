#pragma once
#include "GameObject.h"
#include "Renderer.h"
#include "VIBuffer_Cube.h"
#include "GameInstance.h"

class CTest final : public CGameObject
{
public :
	enum TEST_STATE{TEST_STATE_IDLE, TEST_STATE_ATTACK, TEST_STATE_STUN, TEST_STATE_DIE, TEST_STATE_END};

	enum ANIMATION_STATE{ROOT, PELVIS, SPINE, NECK, LEFTLEG, RIGHTLEG, LEFTARM, RIGHTARM,
		LEFTELBOW, RIGHTELBOW, LEFTANKLE, RIGHTANKLE, ANIMATION_STATE_END};
	enum INVERSE_ANIMATION_STATE {
		INV_RIGHTANKLE , INV_LEFTANKLE, INV_RIGHTELBOW, INV_LEFTELBOW, INV_RIGHTARM, INV_LEFTARM, INV_RIGHTLEG, INV_LEFTLEG,
		INV_NECK, INV_SPINE, INV_PELVIS, INV_ROOT};

	enum ANIMATION_RECT{
		ANI_RECT_HEAD, 
		ANI_RECT_BODY, 
		ANI_RECT_LEFT_LEG,
		ANI_RECT_RIGHT_LEG, 
		ANI_RECT_LEFT_ARM, 
		ANI_RECT_RIGHT_ARM,
		ANI_RECT_LEFT_ELBOW,
		ANI_RECT_RIGHT_ELBOW,
		ANI_RECT_LEFT_ANKLE,
		ANI_RECT_RIGHT_ANKLE,
		ANI_RECT_END
	};
	enum ANIMATION_PLAY{ANI_PLAY, ANI_SET, ANI_END};
	enum INVERSE_ANIMATION_PLAY { INV_ANI_END, INV_ANI_SET, INV_ANI_PLAY };

	enum DIR_STATE{XAXIS, YAXIS, ZASIX, PLUS, MINUS, DIR_STATE_END};
	enum INVERSE_DIR_STATE {INV_MINUS, INV_PLUS, INV_ZAXIS, INV_YAXIS, INV_XAXIS};
	//flag Set후 초기화 하는 함수 필요.
	typedef struct tagTestStruct
	{
		//[UI]애니메이션 바디 선택 콤보박스
		//맵으로 데이터 변경 필요.
		//1111 1111
		//root - pelvis - spine - neck - leftleg - rightleg - leftarm - rightarm
		//[UI] 라디오버튼
		_Uint32t uMotion = 0;
		//0001 1111
		//x axis - y axis - z axis - plus - minus
		//[UI] 라디오버튼
		_Uint32t uDir[ANIMATION_STATE_END];
		//Set Trans class the Angle
		//[UI] NumericUpDown
		_float fAngle[ANIMATION_STATE_END];
		_Uint32t uFlag[ANIMATION_STATE_END];
		_float3 m_varr[ANIMATION_STATE_END];
		_float m_farr[ANIMATION_STATE_END];

		tagTestStruct::tagTestStruct()
		{
			for (int i = 0; i < ANIMATION_STATE_END; ++i)
			{
				uDir[i] = 0x00;
				fAngle[i] = 0.f;
				uFlag[i] = 0x00;
				m_varr[i] = _float3{ 0.f, 0.f, 0.f };
				m_farr[i] = 0.f;
			}
		}
	}TEST_STRUCT;

	TEST_STATE* Get_TestState()
	{
		return &m_eAniState;
	}

	void Set_TestState(TEST_STATE _eState)
	{
		m_eAniState = _eState;
	}

private :
	TEST_STATE m_eAniState = TEST_STATE_IDLE;
	TEST_STATE m_eAniMemoState = TEST_STATE_IDLE;
public :
	void Clear_Flag(TEST_STATE eState, _float _fDeltaTime);
public:
	explicit CTest::CTest(LPDIRECT3DDEVICE9 _pDevice)
		:CGameObject(_pDevice)
	{
	}

	explicit CTest::CTest(const CTest& _rhs)
		: CGameObject(_rhs)
	{
	}

	virtual ~CTest() = default;
public:
	virtual void Tick(_float _fDeltaTime) override;
	virtual void Late_Tick(_float _fDeltaTime) override;
	virtual HRESULT Render() override;
protected:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg) override;
private :
	void Set_Animation(ANIMATION_STATE eState, _float3& vAxis, _float fDir, CTransform* _pTransForm);

private:
	HRESULT SetUp_Components();
	//root
	CTransform* m_pBoneRootTransForm = NULL;
	//pelvis
	CTransform* m_pBonePelvisTransForm = NULL;
	//spine
	CTransform* m_pBoneSpineTransForm = NULL;
	//neck
	CTransform* m_pBoneNeckTransForm = NULL;
	//left leg
	CTransform* m_pBoneLeftLegTransForm = NULL;
	//right leg
	CTransform* m_pBoneRightLegTransForm = NULL;
	//left arm
	CTransform* m_pBoneLeftArmTransForm = NULL;
	//Right arm
	CTransform* m_pBoneRightArmTransForm = NULL;
	//Left Elbow
	CTransform* m_pBoneLeftElbowTransForm = NULL;
	//Right Elbow
	CTransform* m_pBoneRightElbowTransForm = NULL;
	//Left Ankle
	CTransform* m_pBoneLeftAnkleTransForm = NULL;
	//Right Ankle
	CTransform* m_pBoneRightAnkleTransForm = NULL;

	//Ani VIBuffer Member Pointer
	//head
	CVIBuffer_Cube* m_pAniHeadCube = NULL;
	//body
	CVIBuffer_Cube* m_pAniBodyCube = NULL;
	//left leg
	CVIBuffer_Cube* m_pAniLeftLegCube = NULL;
	//right leg
	CVIBuffer_Cube* m_pAniRightLegCube = NULL;
	//left arm
	CVIBuffer_Cube* m_pAniLeftArmCube = NULL;
	//Right arm
	CVIBuffer_Cube* m_pAniRightArmCube = NULL;
	//Left Elbow
	CVIBuffer_Cube* m_pAniLeftElbowCube = NULL;
	//Right Elbow
	CVIBuffer_Cube* m_pAniRightElbowCube = NULL;
	//Left Ankle
	CVIBuffer_Cube* m_pAniLeftAnkleCube = NULL;
	//Right Ankle
	CVIBuffer_Cube* m_pAniRightAnkleCube = NULL;
private :
	CBone * m_pBone = NULL;

public :
		void Mouse_X(_float _fDeltaTime, _float _MouseMove)
		{
			m_pBoneRootTransForm->Turn(m_pBoneRootTransForm->Get_State(STATE_RIGHT), _fDeltaTime * _MouseMove * 0.1f);
		}

		void Mouse_Y(_float _fDeltaTime, _float _MouseMove)
		{
			m_pBoneRootTransForm->Turn(_float3(0.f, 1.f, 0.f), _fDeltaTime * _MouseMove * 0.1f);
		}

public:
	FORCEINLINE static CTest* CTest::Create(LPDIRECT3DDEVICE9 _pDevice)
	{
		CTest * pInstance = new CTest(_pDevice);
		if (!pInstance)
			return NULL;

		if (FAILED(pInstance->NativeConstruct_Prototype()))
			return NULL;

		return pInstance;
	}
	virtual CTest* Clone(void* pArg);
	virtual void Free();
};


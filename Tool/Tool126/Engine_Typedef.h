#pragma once
//자료형을 새로 디파인하여 사용한다.
namespace Engine
{
	enum LEVEL { LEVEL_STATIC, LEVEL_LOADING, LEVEL_LOGO, LEVEL_GAMEPLAY, LEVEL_END };

	//ObjectMgr Key String
	const TCHAR KEY_LEVEL_LOGO[20] = L"LOGO_TAG";
	const TCHAR KEY_LEVEL_GAME[20] = L"GAME_TAG";
	const TCHAR KEY_OBJECT_BACKGROUND[20] = L"BACK_GROUND_TAG";
	const TCHAR KEY_OBJECT_TEST[20] = L"TEST_OBJECT_TAG";
	//ModelMgr Key String
	const TCHAR KEY_COMPONENT_VI_RECT[50] = L"Prototype_Component_VIBuffer_Rect";
	const TCHAR KEY_COMPONENT_VI_CUBE[50] = L"Prototype_Component_VIBuffer_Cube";
	const TCHAR KEY_COMPONENT_RENDERER[50] = L"Prototype_Component_Rederer";
	const TCHAR KEY_COMPONENT_TRANSFORM[50] = L"Prototype_Component_TransForm";
	const TCHAR KEY_COMPONENT_BONE[50] = L"Prototype_Component_Bone";
	//Bone Key String
	const TCHAR KEY_BONE_ROOT[50] = L"Bone_Root";
	const TCHAR KEY_BONE_PELVIS[50] = L"Bone_Pelvis";
	const TCHAR KEY_BONE_SPINE[50] = L"Bone_Spine";
	const TCHAR KEY_BONE_NECK[50] = L"Bone_Neck";
	const TCHAR KEY_BONE_LEFTLEG[50] = L"Bone_LeftLeg";
	const TCHAR KEY_BONE_RIGHTLEG[50] = L"Bone_RightLeg";

	const TCHAR KEY_BONE_LEFTARM[50] = L"Bone_LeftArm";
	const TCHAR KEY_BONE_RIGHTARM[50] = L"Bone_RightArm";

	const TCHAR KEY_BONE_LEFTELBOW[50] = L"Bone_LeftElbow";
	const TCHAR KEY_BONE_RIGHTELBOW[50] = L"Bone_RightElbow";

	const TCHAR KEY_BONE_LEFTANKLE[50] = L"Bone_LeftAnkle";
	const TCHAR KEY_BONE_RIGHTANKLE[50] = L"Bone_RightAnkle";

	enum BONE_LAYER { BONE_LAYER_PLAYER, BONE_LAYER_MONSTER, BONE_LAYER_ELBOW, BONE_LAYER_END };
	enum RENDERGROUP { RENDER_PRIORITY, RENDER_NONALPHABLEND, RENDER_ALPHABLEND, RENDER_UI, RENDER_END };
	enum STATE { STATE_RIGHT, STATE_UP, STATE_LOOK, STATE_POSITION, STATE_END };
	enum AXIS { AXISX, AXISY, AXISZ};
	typedef unsigned char				_ubyte;
	typedef signed char					_byte;

	typedef unsigned short				_ushort;
	typedef signed short				_short;

	typedef unsigned long				_ulong;
	typedef signed long					_long;

	typedef unsigned int				_uint;
	typedef signed int					_int;

	typedef float						_float;
	typedef double						_double;

	typedef bool						_bool;
	typedef wchar_t						_tchar;

	typedef D3DXVECTOR2					_float2;

	typedef D3DXVECTOR3					_float3;

	typedef D3DXVECTOR4					_float4;

	typedef D3DXMATRIX					_float4x4;
}
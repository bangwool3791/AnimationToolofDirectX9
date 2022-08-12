#include <d3d9.h>

namespace Engine
{
	typedef struct tagVertexPositionTexture
	{
		float x, y, z;
		float u, v;
		static const DWORD FVF;
		tagVertexPositionTexture() {}
		tagVertexPositionTexture(float _x, float _y, float _z, float _u, float _v)
		{
			x = _x; y = _y; z = _z;
			u = _u; v = _v;
		}
	}VertexPositionTexture;

	typedef struct tagVertex_Texture
	{
		D3DXVECTOR3		vPosition;
		D3DXVECTOR3		vNormalLighting;
		DWORD			dwDiffuse;
		D3DXVECTOR2		vTexUV;
	}VTXTEX;

	typedef struct tagFaceIndices16
	{
		unsigned short		_0, _1, _2;
	}FACEINDICES16;

	typedef struct tagFaceIndices32
	{
		unsigned long		_0, _1, _2;
	}FACEINDICES32;

	enum MODE { MODE_FULLMODE, MODE_WINMODE, MODE_END };

	typedef struct Graphic_Device_Desc
	{
		MODE eWindMode = MODE_END;
		HWND hWnd = 0;
		unsigned int iWinCX = 0;
		unsigned int iWinCY = 0;
	}GRAPHIC_DEVICE_DESC;

	typedef struct tagTransDesc
	{
		_float3 vRight;
		_float3 vUp;
		_float3 vLook;
		_float3 vPos;
	}TRANSDESC;

	typedef struct tagTransformDesc
	{
		_float      fDir = 1.f;
		_float		fMaxAngle = 0.f;
		_float		fLocalAngle = 0.f;//비저장 데이터
		_float3		vLocalPos;//비저장데이터
		_float3     vAxis = D3DXVECTOR3{ 1.f, 0.f, 0.f };//비저장데이터
		_float		fInitAngle = 0.f;
		_float		fSpeedPerSec = 0.f;
		_float		fRotationPerSec = 0.f;
		_float4x4   LocalMatrix;
		_float4x4   WorldMatrix;
		TCHAR*      szKey = NULL;
	}TRANSFORMDESC;
}
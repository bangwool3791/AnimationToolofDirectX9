#pragma once
#include <stdint.h>
namespace Engine
{
	template <typename T, typename C>
	FORCEINLINE HRESULT Bone_Render(T& Transform, C& Cube)
	{
		if (FAILED(Transform->Bind_OnGraphicDevice()))
			return E_FAIL;

		if (Cube->Render())
			return E_FAIL;

		return S_OK;
	}

	FORCEINLINE D3DXMATRIX Set_Matrix(D3DXVECTOR3 vPos, D3DXVECTOR3 vAxis, float fAngle)
	{
		D3DXMATRIX Matrix;
		ZeroMemory(&Matrix, sizeof(D3DXMATRIX));
		D3DXMatrixRotationAxis(&Matrix, &vAxis, fAngle);
		Matrix.m[3][0] = vPos.x;
		Matrix.m[3][1] = vPos.y;
		Matrix.m[3][2] = vPos.z;
		Matrix.m[3][3] = 1;
		return Matrix;
	}
	template <typename T>
	FORCEINLINE void Set_TransDesc(T& TransformDesc, D3DXMATRIX Matrix, float _rotationsec, float _speedsec)
	{
		TransformDesc.LocalMatrix = Matrix;
		TransformDesc.fRotationPerSec = _rotationsec;
		TransformDesc.fSpeedPerSec = _speedsec;
	}

	template <typename T>
	FORCEINLINE uint64_t Safe_AddRef(T& pInstance)
	{
		uint64_t dwRefCnt = 0;
		if (pInstance)
			dwRefCnt = pInstance->AddRef();

		return dwRefCnt;
	}

	template <typename T>
	FORCEINLINE uint64_t Safe_Release(T& pInstance)
	{
		uint64_t dwRefCnt = 0;
		if (pInstance)
		{
			dwRefCnt = pInstance->Release();

			if (!dwRefCnt)
				pInstance = nullptr;
		}

		return dwRefCnt;
	}

	template <typename T>
	FORCEINLINE uint64_t Check_Ref(T& pInstance)
	{
		uint64_t dwRefCnt = 0;
		if (pInstance)
		{
			dwRefCnt = pInstance->Return_Ref();
		}

		return dwRefCnt;
	}

	template <typename T>
	void Safe_Delete(T& pPointer)
	{
		if (pPointer)
		{
			delete pPointer;
			pPointer = nullptr;
		}
	}

	template <typename T>
	FORCEINLINE void Safe_Delete_Array(T& pPointer)
	{
		if (pPointer)
		{
			delete[] pPointer;
			pPointer = nullptr;
		}
	}
};

#include "VIBuffer.h"

class CVIBuffer_Rect final : public CVIBuffer
{
public:
	FORCEINLINE CVIBuffer_Rect(LPDIRECT3DDEVICE9 pDev) : CVIBuffer(pDev)
	{
	}
	FORCEINLINE CVIBuffer_Rect(const CVIBuffer_Rect& Rhs) : CVIBuffer(Rhs)
	{
	}
	virtual ~CVIBuffer_Rect() = default;
private :
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
public :
	static CVIBuffer_Rect* Create(LPDIRECT3DDEVICE9 pDev);
	virtual CComponent* Clone(void* pArg);
	virtual void Free();
};

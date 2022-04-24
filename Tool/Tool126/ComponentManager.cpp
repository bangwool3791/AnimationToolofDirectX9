#include "stdafx.h"
#include "ComponentManager.h"

IMPLEMENT_SINGLETON(CComponent_Manager)

void CComponent_Manager::Free()
{
	cout << "[CComponent_Manager Free]" << endl;

	MAPCOMPONENT::iterator BeginIter;
	MAPCOMPONENT::iterator EndIter;
	for (size_t i = 0; i < m_iLayerIndex; ++i)
	{
		BeginIter = m_MapProCom[i].begin();
		EndIter = m_MapProCom[i].end();

		while (BeginIter != EndIter)
		{
			Safe_Release(BeginIter->second);
			++BeginIter;
		}
		m_MapProCom[i].swap(MAPCOMPONENT());
		m_MapProCom[i].clear();
	}
	Safe_Delete_Array(m_MapProCom);
}
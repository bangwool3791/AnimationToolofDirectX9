#pragma once
#include "ChildForm.h"
#include <fstream>

#include "Test.h"
extern vector<vector<CTransform*>> g_vecBoneTransfrom;
extern vector<CVIBuffer_Cube*> g_vecAniCube;
extern vector<CTest::TEST_STRUCT> g_vecAniInfo;
extern CTest* g_pTest;
extern CRITICAL_SECTION g_CriticalSection;
extern vector<CBone*> g_pBone;
const int   LEN_POS = 2;
const int	LEN_BONE = 2;
const int	LEN_ANI_CUBE = 2;
const int	LEN_ANI_INFO = 2;
const int TOTAL_LEN_SIZE = LEN_POS + LEN_BONE + LEN_ANI_CUBE + LEN_ANI_INFO;

class CParser
{
public :
	enum PARSER_STATE{BONE, ANIMATION, ANIMATION_INFO};
	enum DATA_STATE{LEN_STEP1,LEN_STEP2, DATA};
public :
	typedef struct tagParser
	{
		CTransform* pTransform = NULL;
		CVIBuffer_Cube* pVIBuffer_Cube = NULL;
		CTest::TEST_STRUCT* pTestStruct = NULL;
	}ST_PARSER;
public:
	CParser()
	{
		m_iAniCubeIndex = sizeof(TRANSFORMDESC) * CTest::ANIMATION_STATE_END;
		m_iBoneIndex = sizeof(CVIBuffer_Cube::STSHAPE) * CTest::ANI_RECT_END;
		m_iAniInfoIndex = sizeof(CTest::TEST_STRUCT) * CTest::TEST_STATE_END;
		//수정
		m_iToTalIndex = m_iAniCubeIndex + m_iBoneIndex * m_iAniInfoIndex + m_iAniInfoIndex + TOTAL_LEN_SIZE + 1;
	}
	virtual ~CParser();
private :
	_ubyte*		 m_WriteBuffer = NULL;
	_ubyte*		 m_ReadBuffer = NULL;
	int			 m_iWriteFileIndex = 0;
	int			 m_iToTalIndex = 0;
	int			 m_iAniCubeIndex = 0;
	int          m_iBoneIndex = 0;
	int			m_iAniInfoIndex = 0;
public :
	HRESULT Save_Process_Animation()
	{
		m_iWriteFileIndex = 0;

		m_WriteBuffer = new _ubyte[m_iToTalIndex];
	
		//m_WriteBuffer = (char*)&buffer;

		ZeroMemory(m_WriteBuffer, sizeof(_ubyte) * m_iToTalIndex);

		m_WriteBuffer[m_iWriteFileIndex] = (m_iToTalIndex >> 8) & 0xFF;
		++m_iWriteFileIndex;
		m_WriteBuffer[m_iWriteFileIndex] = m_iToTalIndex & 0xFF;
		++m_iWriteFileIndex;

		m_WriteBuffer[m_iWriteFileIndex] = ((CTest::TEST_STATE_END * CTest::ANIMATION_STATE_END) >> 8) & 0xFF;
		++m_iWriteFileIndex;
		m_WriteBuffer[m_iWriteFileIndex] = (CTest::TEST_STATE_END * CTest::ANIMATION_STATE_END) & 0xFF;
		++m_iWriteFileIndex;

		int iIndex = 0;
		for (int i = 0; i < CTest::TEST_STATE_END; ++i)
		{
			for (iIndex = 0; iIndex < CTest::ANIMATION_STATE_END; ++iIndex)
			{
				char* Array = NULL;
				EnterCriticalSection(&g_CriticalSection);
				Array = (char*)g_vecBoneTransfrom[i][iIndex]->Get_TansDesc();

				for (int i = 0; i < sizeof(TRANSFORMDESC); ++i)
				{
					m_WriteBuffer[m_iWriteFileIndex] = Array[i];
					++m_iWriteFileIndex;
				}
				LeaveCriticalSection(&g_CriticalSection);
			}
		}


		m_WriteBuffer[m_iWriteFileIndex] = (CTest::ANI_RECT_END >> 8) & 0xFF;
		++m_iWriteFileIndex;
		m_WriteBuffer[m_iWriteFileIndex] = CTest::ANI_RECT_END & 0xFF;
		++m_iWriteFileIndex;

		for (iIndex = 0; iIndex < CTest::ANI_RECT_END; ++iIndex)
		{
			char* Array = NULL;

			EnterCriticalSection(&g_CriticalSection);
			Array = (char*)g_vecAniCube[iIndex]->Get_ShapeInfo();
			CVIBuffer_Cube::STSHAPE st = *(CVIBuffer_Cube::STSHAPE*)Array;
			cout << "ST SHPAE Width" << st.fWidth << endl;
			cout << "ST SHPAE Top" << st.fTop << endl;
			cout << "ST SHPAE Bottom" << st.fBottom << endl;
			cout << "ST SHPAE Pos" << st.fPos << endl;

			for (int i = 0; i < sizeof(CVIBuffer_Cube::STSHAPE); ++i)
			{
				m_WriteBuffer[m_iWriteFileIndex] = Array[i];
				++m_iWriteFileIndex;
			}
			LeaveCriticalSection(&g_CriticalSection);
		}

		m_WriteBuffer[m_iWriteFileIndex] = (CTest::TEST_STATE_END >> 8) & 0xFF;
		++m_iWriteFileIndex;
		m_WriteBuffer[m_iWriteFileIndex] = CTest::TEST_STATE_END & 0xFF;
		++m_iWriteFileIndex;

		for (iIndex = 0; iIndex < CTest::TEST_STATE_END; ++iIndex)
		{
			char* Array = NULL;

			EnterCriticalSection(&g_CriticalSection);
			Array = (char*)&g_vecAniInfo[iIndex];
			cout << "인포저장 확인 " << g_vecAniInfo[iIndex].uMotion << endl;
			for (int i = 0; i < sizeof(CTest::TEST_STRUCT); ++i)
			{
				m_WriteBuffer[m_iWriteFileIndex] = Array[i];
				++m_iWriteFileIndex;
			}
			LeaveCriticalSection(&g_CriticalSection);
		}

		if (m_iWriteFileIndex == m_iToTalIndex - 1)
		{
			int i = 0;
		}

		iIndex = 0;
		ofstream outfile("animation.bin", ios::out | ios::binary);

		while (iIndex < m_iWriteFileIndex)
		{
			outfile.write((char*)&m_WriteBuffer[iIndex], 1);

			if (outfile.rdstate() != ios::goodbit)
				cerr << "write error!!";
			iIndex+= 1;
		}

		outfile.close();
		return S_OK;
	}

	HRESULT Load_Process_Animation()
	{
		ifstream infile("animation.bin", ios::in | ios::binary);

		int FileIndex = 0;
		_ubyte szLen[2];
		ZeroMemory(&szLen, 0);
		infile.read((char*)szLen, 2);

		unsigned int ReadDataSize = (szLen[0] << 8) & 0xFF00;
		ReadDataSize += (szLen[1] & 0xFF);

		_ubyte* ReadBuffer = new _ubyte[ReadDataSize + 1];

		ZeroMemory(ReadBuffer, sizeof(_ubyte) * ReadDataSize + 1);

		int iIndex = 0;

		while (iIndex < ReadDataSize)
		{
			infile.read((char*)ReadBuffer, 1);
			++ReadBuffer;
			++iIndex;
		}

		ReadBuffer -= ReadDataSize;

		if (iIndex == ReadDataSize)
		{
			cout << "Read Index check" << endl;
		}

		int iCase = BONE;
		int iDataCase = LEN_STEP1;
		uint16_t Len = 0;
		int iDataIndex = 0;
		int iBoneIndex = 0;

		TRANSFORMDESC * pTranformDesc;
		CVIBuffer_Cube::STSHAPE * pShape;
		CTest::TEST_STRUCT * pTestStruct;

		byte* pArray = NULL;

		CGameInstance* pIns = CGameInstance::Get_Instance();
		Safe_AddRef(pIns);

		_float arrBoneRadius[4] = { 0.05f, 0.05f, -0.05f, 0.f };

		for(int index = 0; index < ReadDataSize;++index)
		{

				switch (iDataCase)
				{
				case LEN_STEP1:
					Len = (ReadBuffer[index] << 8) & 0xFF00;
					iDataCase = LEN_STEP2;
					cout << "데이터 스탭 1" << endl;
					break;
				case LEN_STEP2:
					Len += (ReadBuffer[index] << 0) & 0xFF;
					iDataCase = DATA;
					cout << "데이터 스탭 2" << endl;
					break;
				case DATA:
					switch (iCase)
					{
					case BONE:
						for (int i = 0; i < sizeof(TRANSFORMDESC); ++i)
						{
							if (0 == i)
							{
								pTranformDesc = new TRANSFORMDESC;
								pArray = (byte*)pTranformDesc;
							}

							pArray[i] = ReadBuffer[index];

							index++;

							if (sizeof(TRANSFORMDESC) - 1 == i)
							{
								switch (iDataIndex % CTest::ANIMATION_STATE_END)
								{
								case CTest::ROOT:
									g_pBone[iBoneIndex]->EraseBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_ROOT);
									g_pBone[iBoneIndex]->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_ROOT, *(TRANSFORMDESC*)pArray, arrBoneRadius);
									g_vecBoneTransfrom[iBoneIndex][CTest::ROOT] = ((CTransform*)g_pBone[iBoneIndex]->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_ROOT));
									break;
								case CTest::PELVIS:
									g_pBone[iBoneIndex]->EraseBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_PELVIS);
									g_pBone[iBoneIndex]->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_PELVIS, *(TRANSFORMDESC*)pArray, arrBoneRadius);
									g_vecBoneTransfrom[iBoneIndex][CTest::PELVIS] = ((CTransform*)g_pBone[iBoneIndex]->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_PELVIS));
									g_pBone[iBoneIndex]->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_ROOT, Engine::KEY_BONE_PELVIS);
									wcout << "본 정보 [PELVIS] " << ((TRANSFORMDESC*)pArray)->szKey << endl;
								
									break;
								case CTest::SPINE:
									g_pBone[iBoneIndex]->EraseBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_SPINE);
									g_pBone[iBoneIndex]->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_SPINE, *(TRANSFORMDESC*)pArray, arrBoneRadius);
									g_vecBoneTransfrom[iBoneIndex][CTest::SPINE] = ((CTransform*)g_pBone[iBoneIndex]->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_SPINE));
									g_pBone[iBoneIndex]->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_PELVIS, Engine::KEY_BONE_SPINE);
									
									break;
								case CTest::NECK:
									g_pBone[iBoneIndex]->EraseBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_NECK);
									g_pBone[iBoneIndex]->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_NECK, *(TRANSFORMDESC*)pArray, arrBoneRadius);
									g_vecBoneTransfrom[iBoneIndex][CTest::NECK] = ((CTransform*)g_pBone[iBoneIndex]->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_NECK));
									g_pBone[iBoneIndex]->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_SPINE, Engine::KEY_BONE_NECK);
							
									break;
								case CTest::LEFTLEG:
									g_pBone[iBoneIndex]->EraseBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTLEG);
									g_pBone[iBoneIndex]->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTLEG, *(TRANSFORMDESC*)pArray, arrBoneRadius);
									g_vecBoneTransfrom[iBoneIndex][CTest::LEFTLEG] = ((CTransform*)g_pBone[iBoneIndex]->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTLEG));
									g_pBone[iBoneIndex]->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_PELVIS, Engine::KEY_BONE_LEFTLEG);
						
									break;
								case CTest::RIGHTLEG:
									g_pBone[iBoneIndex]->EraseBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTLEG);
									g_pBone[iBoneIndex]->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTLEG, *(TRANSFORMDESC*)pArray, arrBoneRadius);
									g_vecBoneTransfrom[iBoneIndex][CTest::RIGHTLEG] = ((CTransform*)g_pBone[iBoneIndex]->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTLEG));
									g_pBone[iBoneIndex]->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_PELVIS, Engine::KEY_BONE_RIGHTLEG);
							
									break;
								case CTest::LEFTARM:
									g_pBone[iBoneIndex]->EraseBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTARM);
									g_pBone[iBoneIndex]->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTARM, *(TRANSFORMDESC*)pArray, arrBoneRadius);
									g_vecBoneTransfrom[iBoneIndex][CTest::LEFTARM] = ((CTransform*)g_pBone[iBoneIndex]->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTARM));
									g_pBone[iBoneIndex]->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_SPINE, Engine::KEY_BONE_LEFTARM);
									break;
								case CTest::RIGHTARM:
									g_pBone[iBoneIndex]->EraseBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTARM);
									g_pBone[iBoneIndex]->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTARM, *(TRANSFORMDESC*)pArray, arrBoneRadius);
									g_vecBoneTransfrom[iBoneIndex][CTest::RIGHTARM] = ((CTransform*)g_pBone[iBoneIndex]->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTARM));
									g_pBone[iBoneIndex]->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_SPINE, Engine::KEY_BONE_RIGHTARM);

									break;
								case CTest::LEFTELBOW:
									g_pBone[iBoneIndex]->EraseBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTELBOW);
									g_pBone[iBoneIndex]->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTELBOW, *(TRANSFORMDESC*)pArray, arrBoneRadius);
									g_vecBoneTransfrom[iBoneIndex][CTest::LEFTELBOW] = ((CTransform*)g_pBone[iBoneIndex]->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTELBOW));
									g_pBone[iBoneIndex]->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTARM, Engine::KEY_BONE_LEFTELBOW);

									break;
								case CTest::RIGHTELBOW:
									g_pBone[iBoneIndex]->EraseBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTELBOW);
									g_pBone[iBoneIndex]->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTELBOW, *(TRANSFORMDESC*)pArray, arrBoneRadius);
									g_vecBoneTransfrom[iBoneIndex][CTest::RIGHTELBOW] = ((CTransform*)g_pBone[iBoneIndex]->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTELBOW));
									g_pBone[iBoneIndex]->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTARM, Engine::KEY_BONE_RIGHTELBOW);
									break;
								case CTest::LEFTANKLE:
									g_pBone[iBoneIndex]->EraseBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTANKLE);
									g_pBone[iBoneIndex]->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTANKLE, *(TRANSFORMDESC*)pArray, arrBoneRadius);
									g_vecBoneTransfrom[iBoneIndex][CTest::LEFTANKLE] = ((CTransform*)g_pBone[iBoneIndex]->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTANKLE));
									g_pBone[iBoneIndex]->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_LEFTLEG, Engine::KEY_BONE_LEFTANKLE);

									break;
								case CTest::RIGHTANKLE:
									g_pBone[iBoneIndex]->EraseBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTANKLE);
									g_pBone[iBoneIndex]->Add_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTANKLE, *(TRANSFORMDESC*)pArray, arrBoneRadius);
									g_vecBoneTransfrom[iBoneIndex][CTest::RIGHTANKLE] = ((CTransform*)g_pBone[iBoneIndex]->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTANKLE));
									g_pBone[iBoneIndex]->Setting_ParentBone(BONE_LAYER_PLAYER, Engine::KEY_BONE_RIGHTLEG, Engine::KEY_BONE_RIGHTANKLE);
									++iBoneIndex;
									break;

								}
								++iDataIndex;
								index--;
								Safe_Delete(pTranformDesc);
							}
							//인덱스 증가 위치 헷갈리지 말것
						}
						//cout << "[인덱스] " << index << endl;
						if (iDataIndex == Len)
						{
							cout << "뼈 파싱 완료" << endl;
							iDataIndex = 0;
							iDataCase = LEN_STEP1;
							iCase = ANIMATION;
							Len = 0;
						}
						break;
					case ANIMATION:
						for (int i = 0; i < sizeof(CVIBuffer_Cube::STSHAPE); ++i)
						{
							if (0 == i)
							{
								pShape = new CVIBuffer_Cube::STSHAPE;
								pArray = (byte*)pShape;
							}

							pArray[i] = ReadBuffer[index];

							index++;

							if (sizeof(CVIBuffer_Cube::STSHAPE) -1 == i)
							{
								CVIBuffer_Cube::STSHAPE st;
								EnterCriticalSection(&g_CriticalSection);
								switch (iDataIndex)
								{
								case CTest::ANI_RECT_HEAD:
									st = *(CVIBuffer_Cube::STSHAPE*)pArray;
									Safe_Release(g_vecAniCube[CTest::ANI_RECT_HEAD]);
									g_vecAniCube[CTest::ANI_RECT_HEAD] = (CVIBuffer_Cube*)pIns->Clone_ComponentObject(
										LEVEL_STATIC, KEY_COMPONENT_VI_CUBE, (CVIBuffer_Cube::STSHAPE*)pArray);
									cout << "ANI HEAD " << endl;
									break;
								case CTest::ANI_RECT_BODY:
									Safe_Release(g_vecAniCube[CTest::ANI_RECT_BODY]);
									g_vecAniCube[CTest::ANI_RECT_BODY] = (CVIBuffer_Cube*)pIns->Clone_ComponentObject(
										LEVEL_STATIC, KEY_COMPONENT_VI_CUBE, (CVIBuffer_Cube::STSHAPE*)pArray);
									break;
								case CTest::ANI_RECT_LEFT_LEG:
									Safe_Release(g_vecAniCube[CTest::ANI_RECT_LEFT_LEG]);
									g_vecAniCube[CTest::ANI_RECT_LEFT_LEG] = (CVIBuffer_Cube*)pIns->Clone_ComponentObject(
										LEVEL_STATIC, KEY_COMPONENT_VI_CUBE, (CVIBuffer_Cube::STSHAPE*)pArray);
									break;
								case CTest::ANI_RECT_RIGHT_LEG:
									Safe_Release(g_vecAniCube[CTest::ANI_RECT_RIGHT_LEG]);
									g_vecAniCube[CTest::ANI_RECT_RIGHT_LEG] = (CVIBuffer_Cube*)pIns->Clone_ComponentObject(
										LEVEL_STATIC, KEY_COMPONENT_VI_CUBE, (CVIBuffer_Cube::STSHAPE*)pArray);
									break;
								case CTest::ANI_RECT_LEFT_ARM:
									Safe_Release(g_vecAniCube[CTest::ANI_RECT_LEFT_ARM]);
									g_vecAniCube[CTest::ANI_RECT_LEFT_ARM] = (CVIBuffer_Cube*)pIns->Clone_ComponentObject(
										LEVEL_STATIC, KEY_COMPONENT_VI_CUBE, (CVIBuffer_Cube::STSHAPE*)pArray);
									break;
								case CTest::ANI_RECT_RIGHT_ARM:
									Safe_Release(g_vecAniCube[CTest::ANI_RECT_RIGHT_ARM]);
									g_vecAniCube[CTest::ANI_RECT_RIGHT_ARM] = (CVIBuffer_Cube*)pIns->Clone_ComponentObject(
										LEVEL_STATIC, KEY_COMPONENT_VI_CUBE, (CVIBuffer_Cube::STSHAPE*)pArray);
									break;
								case CTest::ANI_RECT_LEFT_ELBOW:
									Safe_Release(g_vecAniCube[CTest::ANI_RECT_LEFT_ELBOW]);
									g_vecAniCube[CTest::ANI_RECT_LEFT_ELBOW] = (CVIBuffer_Cube*)pIns->Clone_ComponentObject(
										LEVEL_STATIC, KEY_COMPONENT_VI_CUBE, (CVIBuffer_Cube::STSHAPE*)pArray);
									break;
								case CTest::ANI_RECT_RIGHT_ELBOW:
									Safe_Release(g_vecAniCube[CTest::ANI_RECT_RIGHT_ELBOW]);
									g_vecAniCube[CTest::ANI_RECT_RIGHT_ELBOW] = (CVIBuffer_Cube*)pIns->Clone_ComponentObject(
										LEVEL_STATIC, KEY_COMPONENT_VI_CUBE, (CVIBuffer_Cube::STSHAPE*)pArray);
									break;
								case CTest::ANI_RECT_LEFT_ANKLE:
									Safe_Release(g_vecAniCube[CTest::ANI_RECT_LEFT_ANKLE]);
									g_vecAniCube[CTest::ANI_RECT_LEFT_ANKLE] = (CVIBuffer_Cube*)pIns->Clone_ComponentObject(
										LEVEL_STATIC, KEY_COMPONENT_VI_CUBE, (CVIBuffer_Cube::STSHAPE*)pArray);
									break;
								case CTest::ANI_RECT_RIGHT_ANKLE:
									Safe_Release(g_vecAniCube[CTest::ANI_RECT_RIGHT_ANKLE]);
									g_vecAniCube[CTest::ANI_RECT_RIGHT_ANKLE] = (CVIBuffer_Cube*)pIns->Clone_ComponentObject(
										LEVEL_STATIC, KEY_COMPONENT_VI_CUBE, (CVIBuffer_Cube::STSHAPE*)pArray);
									break;
								}
								LeaveCriticalSection(&g_CriticalSection);
								index--;
								Safe_Delete(pShape);
							}
						}
						++iDataIndex;

						if (iDataIndex == Len)
						{
							iDataIndex = 0;
							iDataCase = LEN_STEP1;
							iCase = ANIMATION_INFO;
							Len = 0;
						}
						break;
					case ANIMATION_INFO:
						for (int i = 0; i < sizeof(CTest::TEST_STRUCT); ++i)
						{
							if (0 == i)
							{
								pTestStruct = new CTest::TEST_STRUCT;
								pArray = (byte*)pTestStruct;
							}

							pArray[i] = ReadBuffer[index];
							//TEST_STATE_IDLE
							index++;
							if (sizeof(CTest::TEST_STRUCT)-1 == i)
							{
								switch (iDataIndex)
								{
								case CTest::TEST_STATE_IDLE:
									g_vecAniInfo[CTest::TEST_STATE_IDLE] = *(CTest::TEST_STRUCT*)pArray;
									cout << "인포로드 확인1 " << g_vecAniInfo[CTest::TEST_STATE_IDLE].uMotion << endl;
									break;
								case CTest::TEST_STATE_ATTACK:
									g_vecAniInfo[CTest::TEST_STATE_ATTACK] = *(CTest::TEST_STRUCT*)pArray;
									cout << "인포로드 확인2 " << g_vecAniInfo[CTest::TEST_STATE_ATTACK].uMotion << endl;
									break;
								case CTest::TEST_STATE_STUN:
									g_vecAniInfo[CTest::TEST_STATE_STUN] = *(CTest::TEST_STRUCT*)pArray;
									cout << "인포로드 확인3 " << g_vecAniInfo[CTest::TEST_STATE_STUN].uMotion << endl;
									break;
								case CTest::TEST_STATE_DIE:
									g_vecAniInfo[CTest::TEST_STATE_DIE] = *(CTest::TEST_STRUCT*)pArray;
									cout << "인포로드 확인4 " << g_vecAniInfo[CTest::TEST_STATE_DIE].uMotion << endl;
									break;
								}
								index--;
								delete pTestStruct;
							}
						}
						++iDataIndex;
						if (iDataIndex == Len)
						{
							cout << "여기 들어옴" << endl;
							iDataIndex = 0;
							iDataCase = LEN_STEP1;
							return S_OK;
						}
						break;
					}
					break;
				}
		}
		infile.close();

		Safe_Delete_Array(ReadBuffer);

		return E_FAIL;
	}
};


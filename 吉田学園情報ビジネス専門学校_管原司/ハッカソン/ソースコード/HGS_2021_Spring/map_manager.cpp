//=============================================================================
//
// �X�R�A�Ǘ����� [score.cpp]
// Author : �ѐ�ї���
//
//=============================================================================

//*****************************************************************************
// �x������
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include <stdio.h>
#include "manager.h"
#include "scene.h"
#include "map_manager.h"
#include <cmath>
#include "block.h"
#include "normal_block.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMap::CMap(int nPriority) : CScene(nPriority)
{
	memset(m_aMapIndex, 0, sizeof(m_aMapIndex));
	memset(m_apBlock, NULL, sizeof(m_apBlock));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMap::~CMap()
{
}
//=============================================================================
// ��������
//=============================================================================
CMap * CMap::Create(void)
{
	CMap *pMap = NULL;

	if (pMap == NULL)
	{
		pMap = new CMap;
		pMap->Init();
	}

	return pMap;
}
//=============================================================================
// �}�b�v���[�h����
//=============================================================================
void CMap::MapLoad(void)
{
	FILE * pfile = fopen("Data/Text/maptest.csv", "r");

	//csv�ǂݎ�菈��
	char str[2048];
	int nRowIndex = 0; //�s
	int nColIndex = 0; //��
	if (pfile != NULL)
	{
		//��s�擾
		while (fgets(str, 2048, pfile) != NULL)
		{
			char * cTokStr;
			cTokStr = strtok(str, ",");
			while (cTokStr != NULL)
			{
				//#���܂܂�Ă���Δ�����
				char cSearchStr = '#';//�Ώە���
				strchr(cTokStr, cSearchStr);
				//�܂܂�Ă��Ȃ�������o��
				if (strchr(cTokStr, cSearchStr) == NULL)
				{
					//�s��Ƀu���b�N�̃^�C�v���i�[
					m_aMapIndex[nRowIndex][nColIndex] = (TYPE)atoi(cTokStr);
					//���̗��
					nColIndex++;
				}
				cTokStr = strtok(NULL, ",");//NULL������
			}

			nRowIndex++;
			nColIndex = 0;
		}
		fclose(pfile);
	}
	else
	{

	}
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CMap::Init(void)
{
	SetObjType(CScene::OBJTYPE_NONE);

	//�}�b�v���[�h
	MapLoad();

	for (int nCountRow = 0; nCountRow < MAX_ROW; nCountRow++)
	{
		for (int nCountCol = 0; nCountCol < MAX_COL; nCountCol++)
		{
			switch (m_aMapIndex[nCountRow][nCountCol])
			{
			case TYPE_AIR://��C
						  //�������Ȃ�
				break;
			case TYPE_BLOCK://�V��
				CNormalBlock::Create(D3DXVECTOR3(nCountCol * BLOCK_SIZE, nCountRow * BLOCK_SIZE, 0.0f), D3DXVECTOR3(BLOCK_SIZE, BLOCK_SIZE, 0.0f));
				break;
			default:
				break;
			}
		}
	}

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CMap::Uninit(void)
{
	Release();
}
//=============================================================================
// �X�V����
//=============================================================================
void CMap::Update(void)
{
}
//=============================================================================
// �`�揈��
//=============================================================================
void CMap::Draw(void)
{
}
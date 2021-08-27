//******************************************************************************
// �}�b�v[map.cpp]
// Author : �ǌ��i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "../3D/Model/Object/3d_obj.h"
#include "../3D/3DPolygon/floor.h"
#include "../3D/Model/Block/floor_block.h"
#include "../3D/Model/Block/needle_block.h"
#include "../3D/Model/Object/button.h"
#include "../3D/Model/Object/gate.h"
#include "../3D/Model/Object/gate_roof.h"
#include "../3D/Model/Object/tree.h"
#include "../3D/Model/Object/stone.h"
#include "../3D/Model/Block/wood_block.h"
#include "../3D/Model/Object/wood.h"
#include "map.h"
//******************************************************************************
//	�}�N����`
//******************************************************************************
#define GAME_FLOOR_TEXT			("data/Map/Text/Game_Floor.csv")																										// �}�b�v
#define GAME_BLOCK_TEXT			("data/Map/Text/Game_Map.csv")																										// ��
#define GAME_BACK_OBJ_TEXT		("data/Map/Text/Game_BackObj.csv")																									// �w�i�I�u�W�F�N�g
#define TUTORIAL_FLOOR_TEXT		("data/Map/Text/Tutorial_Floor.csv")																							// �}�b�v
#define TUTORIAL_BLOCK_TEXT		("data/Map/Text/Tutorial_Map.csv")																							// ��
#define TUTORIAL_BACK_OBJ_TEXT	("data/Map/Text/Tutorial_BackObj.csv")																							// �w�i�I�u�W�F�N�g
#define FLOOR_SIZE				(D3DXVECTOR3(180.0f,0.0f,180.0f))																								// ���̃T�C�Y
#define FLOOR_POS				(D3DXVECTOR3(nCountCol * FLOOR_SIZE.x - 1000.0f,-45.0f,nCountRow * FLOOR_SIZE.z - 400.0f))										// ���̈ʒu
#define FLOOR_ROT				(D3DXVECTOR3(0.0f,0.0f,0.0f))																									// ���̌���
#define FLOOR_COL				(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))																								// �F
#define BLOCK_SIZE				(D3DXVECTOR3(30.0f,30.0f,30.0f))																								// �u���b�N�̃T�C�Y
#define BLOCK_POS				(D3DXVECTOR3(nCountCol * BLOCK_SIZE.x - 290.0f,nCountRow * -BLOCK_SIZE.y + 150.0f ,-200.0f))									// �u���b�N�̈ʒu
#define BLOCK_ROT				(D3DXVECTOR3(0.0f,0.0f,0.0f))																									// �u���b�N�̌���
#define NEEDLE_SIZE				(D3DXVECTOR3(30.0f,15.0f,30.0f))																								// �j�̃T�C�Y
#define NEEDLE_POS				(D3DXVECTOR3(nCountCol * NEEDLE_SIZE.x - 290.0f,nCountRow * -NEEDLE_SIZE.y * 2 + 150.0f ,-200.0f))								// �u���b�N�̈ʒu
#define BUTTON_SIZE				(D3DXVECTOR3(30.0f,10.0f,30.0f))																								// �{�^���T�C�Y
#define BUTTON_POS				(D3DXVECTOR3(nCountCol * BUTTON_SIZE.x - 290.0f,nCountRow * -BLOCK_SIZE.y + BUTTON_SIZE.y * 1.5f + 150.0f ,-200.0f))			// �{�^���̈ʒu
#define BUTTON_ROT				(D3DXVECTOR3(0.0f,0.0f,0.0f))																									// ����
#define GATE_SIZE				(D3DXVECTOR3(30.5f,37.0f,30.0f))																								// ���T�C�Y
#define GATE_POS				(D3DXVECTOR3(nCountCol * BLOCK_SIZE.x - BLOCK_SIZE.x / 2 - 290.0f,nCountRow * -BLOCK_SIZE.y + GATE_SIZE.y + 150.0f ,-200.0f))	// ���̈ʒu
#define GATE_ROT				(D3DXVECTOR3(0.0f,D3DXToRadian(90.0f),0.0f))																					// ������
#define GATE_ROOF_SIZE			(D3DXVECTOR3(30.0f,37.0f,20.0f))																								// ���̉����̃T�C�Y
#define GATE_ROOF_POS			(D3DXVECTOR3(nCountCol * GATE_ROOF_SIZE.x - 290.0f,nCountRow * -BLOCK_SIZE.y + GATE_ROOF_SIZE.y + 150.0f ,-200.0f))				// ���̉����̈ʒu
#define GATE_ROOF_ROT			(D3DXVECTOR3(0.0f,D3DXToRadian(270.0f),0.0f))																					// ���̉���
#define TREE_SIZE				(D3DXVECTOR3(180.0f,180.0f,180.0f))																								// �؂̃T�C�Y
#define TREE_POS				(D3DXVECTOR3(nCountCol * TREE_SIZE.x - 1000.0f,-45.0f,nCountRow * TREE_SIZE.z - 400.0f))										// �؂̈ʒu
#define STONE_0_SIZE			(D3DXVECTOR3(30.0f,30.0f,30.0f))																								// �΂̃T�C�Y
#define STONE_0_POS				(D3DXVECTOR3(nCountCol * FLOOR_SIZE.x - 1000.0f,-45.0f,nCountRow * FLOOR_SIZE.z - 400.0f))										// �΂̈ʒu
#define STONE_1_SIZE			(D3DXVECTOR3(60.0f,60.0f,30.0f))																								// �΂̃T�C�Y
#define STONE_1_POS				(D3DXVECTOR3(nCountCol * FLOOR_SIZE.x - 1000.0f,-45.0f,nCountRow * FLOOR_SIZE.z - 400.0f))										// �΂̈ʒu
#define STONE_2_SIZE			(D3DXVECTOR3(120.0f,100.0f,30.0f))																								// �΂̃T�C�Y
#define STONE_2_POS				(D3DXVECTOR3(nCountCol * FLOOR_SIZE.x - 1000.0f,-45.0f,nCountRow * FLOOR_SIZE.z - 400.0f))										// �΂̈ʒu
#define BYTE_NUM				(1024)																															// �ő�o�C�g��
#define WOOD_SIZE				(D3DXVECTOR3(100.0f,200.0f,200.0f))																								// �؂̃T�C�Y
#define WOOD_POS				(D3DXVECTOR3(nCountCol * BLOCK_SIZE.x - 290.0f,nCountRow * -BLOCK_SIZE.y + 150.0f,- 200.0f))									// �؂̈ʒu
#define GATE_BLCOK_POS			(D3DXVECTOR3(GATE_ROOF_POS.x,GATE_ROOF_POS.y + GATE_ROOF_SIZE.y,GATE_ROOF_POS.z))												// ���̃u���b�N�̈ʒu
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CMap::CMap()
{
	m_apFloorIndex		= NULL;		// �s��
	m_apObjIndex		= NULL;		// �s��
	m_apBackObjIndex	= NULL;		// �s��
	m_nRow				= INIT_INT;	// �c
	m_nCol				= INIT_INT;	// ��
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CMap::~CMap()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CMap * CMap::Create(TYPE type)
{
	// CMap�̃|�C���^
	CMap *pMap = NULL;

	// NULL�̏ꍇ
	if (pMap == NULL)
	{
		// �������m��
		pMap = new CMap;

		// NULL�łȂ��ꍇ
		if (pMap != NULL)
		{
			// ��ޑ��
			pMap->m_Type = type;

			// ������
			pMap->Init();
		}
	}
	// �|�C���^��Ԃ�
	return pMap;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CMap::Init(void)
{
	// �}�b�v����
	MapCreate();

	// �I��
	Uninit();
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CMap::Uninit(void)
{
	// �j��
	Release();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CMap::Update(void)
{
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CMap::Draw(void)
{
}
//******************************************************************************
// �}�b�v����
//******************************************************************************
void CMap::MapCreate(void)
{
	// ������
	FloorCreate();

	// �u���b�N����
	BlockCreate();

	// �w�i�I�u�W�F�N�g����
	BackObjCreate();
}
//******************************************************************************
// ���̐���
//******************************************************************************
void CMap::FloorCreate(void)
{
	// ���̃e�L�X�g�̍s��̐��ǂݍ���
	SetRowCol(LOAD_TYPE_FLOOR);

	// ���̏��ǂݍ���
	FloorLoad();

	// NULL�łȂ��ꍇ
	if (m_apFloorIndex != NULL)
	{
		// �s����
		for (int nCountRow = INIT_INT; nCountRow < m_nRow; nCountRow++)
		{
			// �񕪉�
			for (int nCountCol = INIT_INT; nCountCol < m_nCol; nCountCol++)
			{
				switch (m_apFloorIndex[nCountRow][nCountCol])
				{
					// ��
				case FLOOR_TYPE_GLASS:
					// ������
					CFloor::Create(FLOOR_POS, FLOOR_ROT, FLOOR_SIZE, FLOOR_COL);
					break;

				default:
					break;
				}
			}
		}
		// �s����
		for (int nCntRow = INIT_INT; nCntRow < m_nRow; nCntRow++)
		{
			// �������j��
			delete[] m_apFloorIndex[nCntRow];
		}
		// �������j��
		delete[] m_apFloorIndex;
	}
}
//******************************************************************************
// ���̓ǂݍ���
//******************************************************************************
void CMap::FloorLoad()
{
	// FILE�̃|�C���^
	FILE * pfile = NULL;

	// GAME�̏ꍇ
	if (m_Type == TYPE_GAME)
	{
		// �t�@�C���ǂݍ���
		pfile = fopen(GAME_FLOOR_TEXT, "r");
	}
	// TYPE_TUTORIAL�̏ꍇ
	if (m_Type == TYPE_TUTORIAL)
	{
		// �t�@�C���ǂݍ���
		pfile = fopen(TUTORIAL_FLOOR_TEXT, "r");
	}

	// csv�ǂݎ�菈��
	char str[BYTE_NUM];

	// �s
	int nRowIndex = INIT_INT;

	// ��
	int nColIndex = INIT_INT;

	// NULL�łȂ��ꍇ
	if (pfile != NULL)
	{
		if (m_apFloorIndex == NULL)
		{
			// �������m��
			m_apFloorIndex = new FLOOR_TYPE*[m_nRow];

			// NULL�łȂ��ꍇ
			if (m_apFloorIndex != NULL)
			{
				// �s����
				for (int nCnt = INIT_INT; nCnt < m_nRow; nCnt++)
				{
					// �񕪉�
					m_apFloorIndex[nCnt] = new FLOOR_TYPE[m_nCol];
				}
				// ��s�擾
				while (fgets(str, BYTE_NUM, pfile) != NULL)
				{
					char * cTokStr;

					cTokStr = strtok(str, ",");

					// #���܂܂�Ă���Δ�����
					char cSearchStr = '#';

					// �Ώە���
					strchr(cTokStr, cSearchStr);

					// NULL�ɂȂ�܂�
					while (cTokStr != NULL)
					{
						// #���܂܂�Ă���Δ�����
						char cSearchStr = '#';

						// �Ώە���
						strchr(cTokStr, cSearchStr);

						// �܂܂�Ă��Ȃ�������o��
						if (strchr(cTokStr, cSearchStr) == NULL)
						{
							// �s��Ƀu���b�N�̃^�C�v���i�[
							m_apFloorIndex[nRowIndex][nColIndex] = (FLOOR_TYPE)atoi(cTokStr);

							// ���̗��
							nColIndex++;
						}
						// NULL������
						cTokStr = strtok(NULL, ",");
					}
					// �C���N�������g
					nRowIndex++;

					// 0��
					nColIndex = INIT_INT;
				}
			}
		}
		// �t�@�C�������
		fclose(pfile);
	}
	else
	{
		return;
	}
}
//******************************************************************************
// �u���b�N����
//******************************************************************************
void CMap::BlockCreate(void)
{
	// ���̃e�L�X�g�̍s��̐��ǂݍ���
	SetRowCol(LOAD_TYPE_BLOCK);

	// ���̏��ǂݍ���
	BlockLoad();

	// NULL�łȂ��ꍇ
	if (m_apObjIndex != NULL)
	{
		// �s����
		for (int nCountRow = INIT_INT; nCountRow < m_nRow; nCountRow++)
		{
			// �񕪉�
			for (int nCountCol = INIT_INT; nCountCol < m_nCol; nCountCol++)
			{
				switch (m_apObjIndex[nCountRow][nCountCol])
				{
					// ����
				case OBJ_TYPE_NONE:
					break;
					// ��
				case OBJ_TYPE_NORMAL_BLOCK:
					// ������
					CFloor_Block::Create(BLOCK_POS, BLOCK_ROT, BLOCK_SIZE, CFloor_Block::TYPE_NORMAL);
					break;
					// �j
				case OBJ_TYPE_NEEDLE:
					// �j����
					CNeedle_Block::Create(NEEDLE_POS, BLOCK_ROT, NEEDLE_SIZE);
					break;
					// �{�^��
				case OBJ_TYPE_BUTTON:
					// ������
					CFloor_Block::Create(BLOCK_POS, BLOCK_ROT, BLOCK_SIZE, CFloor_Block::TYPE_NORMAL);
					// �{�^������
					CButton::Create(BUTTON_POS, BUTTON_ROT, BUTTON_SIZE);
					break;
					// �{�^��
				case OBJ_TYPE_GATE:
					// ������
					CFloor_Block::Create(GATE_BLCOK_POS, BLOCK_ROT, BLOCK_SIZE, CFloor_Block::TYPE_NORMAL);
					// ������
					CFloor_Block::Create(BLOCK_POS, BLOCK_ROT, BLOCK_SIZE, CFloor_Block::TYPE_NORMAL);
					// ������
					CGate::Create(GATE_POS, GATE_ROT, GATE_SIZE);
					// ������
					CGate_Roof::Create(GATE_ROOF_POS, GATE_ROOF_ROT, GATE_ROOF_SIZE);
					break;
					// �`�F�b�N�|�C���g
				case OBJ_TYPE_CHECK_POINT:
					// ������
					CFloor_Block::Create(BLOCK_POS, BLOCK_ROT, BLOCK_SIZE, CFloor_Block::TYPE_CHECK_POINT);
					break;
					// �I��
				case OBJ_TYPE_END:
					// ������
					CFloor_Block::Create(BLOCK_POS, BLOCK_ROT, BLOCK_SIZE, CFloor_Block::TYPE_END);
					break;
					// �ؔ�
				case OBJ_TYPE_WOOD_BOX:
					// �ؔ�����
					CWood_Block::Create(BLOCK_POS, BLOCK_ROT, BLOCK_SIZE);
					break;
				case OBJ_TYPE_WOOD:
					// �ؐ���
					CWood::Create(WOOD_POS, WOOD_SIZE);
					break;
				case OBJ_TYPE_ENEMY_CREATE:
					// ������
					CFloor_Block::Create(BLOCK_POS, BLOCK_ROT, BLOCK_SIZE, CFloor_Block::TYPE_ENEMY_CREATE);
					break;
				default:
					break;
				}
			}
		}
		// �s����
		for (int nCntRow = INIT_INT; nCntRow < m_nRow; nCntRow++)
		{
			// �������j��
			delete[] m_apObjIndex[nCntRow];
		}
		// �������j��
		delete[] m_apObjIndex;
	}
}
//******************************************************************************
// �u���b�N�ǂݍ���
//******************************************************************************
void CMap::BlockLoad(void)
{
	// FILE�̃|�C���^
	FILE * pfile = NULL;

	// GAME�̏ꍇ
	if (m_Type == TYPE_GAME)
	{
		// �t�@�C���ǂݍ���
		pfile = fopen(GAME_BLOCK_TEXT, "r");
	}
	// TYPE_TUTORIAL�̏ꍇ
	if (m_Type == TYPE_TUTORIAL)
	{
		// �t�@�C���ǂݍ���
		pfile = fopen(TUTORIAL_BLOCK_TEXT, "r");
	}
	// csv�ǂݎ�菈��
	char str[BYTE_NUM];

	// �s
	int nRowIndex = INIT_INT;

	// ��
	int nColIndex = INIT_INT;

	// NULL�łȂ��ꍇ
	if (pfile != NULL)
	{
		if (m_apObjIndex == NULL)
		{
			// �������m��
			m_apObjIndex = new OBJ_TYPE*[m_nRow];

			// NULL�łȂ��ꍇ
			if (m_apObjIndex != NULL)
			{
				// �s����
				for (int nCnt = INIT_INT; nCnt < m_nRow; nCnt++)
				{
					// �񕪉�
					m_apObjIndex[nCnt] = new OBJ_TYPE[m_nCol];
				}
				// ��s�擾
				while (fgets(str, BYTE_NUM, pfile) != NULL)
				{
					char * cTokStr;

					cTokStr = strtok(str, ",");

					// #���܂܂�Ă���Δ�����
					char cSearchStr = '#';

					// �Ώە���
					strchr(cTokStr, cSearchStr);

					// NULL�ɂȂ�܂�
					while (cTokStr != NULL)
					{
						// #���܂܂�Ă���Δ�����
						char cSearchStr = '#';

						// �Ώە���
						strchr(cTokStr, cSearchStr);

						// �܂܂�Ă��Ȃ�������o��
						if (strchr(cTokStr, cSearchStr) == NULL)
						{
							// �s��Ƀu���b�N�̃^�C�v���i�[
							m_apObjIndex[nRowIndex][nColIndex] = (OBJ_TYPE)atoi(cTokStr);

							// ���̗��
							nColIndex++;
						}
						// NULL������
						cTokStr = strtok(NULL, ",");
					}
					// �C���N�������g
					nRowIndex++;

					// 0��
					nColIndex = INIT_INT;
				}
			}
		}
		// �t�@�C�������
		fclose(pfile);
	}
	else
	{
		return;
	}
}
//******************************************************************************
// �w�i�I�u�W�F�N�g����
//******************************************************************************
void CMap::BackObjCreate(void)
{
	// ���̃e�L�X�g�̍s��̐��ǂݍ���
	SetRowCol(LOAD_TYPE_BACK_OBJ);

	// ���̏��ǂݍ���
	BackObjLoad();

	// NULL�łȂ��ꍇ
	if (m_apBackObjIndex != NULL)
	{
		// �s����
		for (int nCountRow = INIT_INT; nCountRow < m_nRow; nCountRow++)
		{
			// �񕪉�
			for (int nCountCol = INIT_INT; nCountCol < m_nCol; nCountCol++)
			{
				switch (m_apBackObjIndex[nCountRow][nCountCol])
				{
					// ����
				case BACK_OBJ_NONE:
					break;
					// �ؐ���
				case BACK_OBJ_TREE:
					CTree::Create(TREE_POS, TREE_SIZE);
					break;
				case BACK_OBJ_STONE_0:
					CStone::Create(STONE_0_POS, STONE_0_SIZE, C3D_Obj::TYPE_STONE_0);
					break;
				case BACK_OBJ_STONE_1:
					CStone::Create(STONE_1_POS, STONE_1_SIZE, C3D_Obj::TYPE_STONE_1);
					break;
				case BACK_OBJ_STONE_2:
					CStone::Create(STONE_2_POS, STONE_2_SIZE, C3D_Obj::TYPE_STONE_2);
					break;
				default:
					break;
				}
			}
		}
		// �s����
		for (int nCntRow = INIT_INT; nCntRow < m_nRow; nCntRow++)
		{
			// �������j��
			delete[] m_apBackObjIndex[nCntRow];
		}
		// �������j��
		delete[] m_apBackObjIndex;
	}
}
//******************************************************************************
// �w�i�I�u�W�F�N�g�ǂݍ���
//******************************************************************************
void CMap::BackObjLoad(void)
{
	// FILE�̃|�C���^
	FILE * pfile = NULL;

	// GAME�̏ꍇ
	if (m_Type == TYPE_GAME)
	{
		// �t�@�C���ǂݍ���
		pfile = fopen(GAME_BACK_OBJ_TEXT, "r");
	}
	// GAME�̏ꍇ
	if (m_Type == TYPE_TUTORIAL)
	{
		// �t�@�C���ǂݍ���
		pfile = fopen(TUTORIAL_BACK_OBJ_TEXT, "r");
	}
	// csv�ǂݎ�菈��
	char str[BYTE_NUM];

	// �s
	int nRowIndex = INIT_INT;

	// ��
	int nColIndex = INIT_INT;

	// NULL�łȂ��ꍇ
	if (pfile != NULL)
	{
		if (m_apBackObjIndex == NULL)
		{
			// �������m��
			m_apBackObjIndex = new BACK_OBJ_TYPE*[m_nRow];

			// NULL�łȂ��ꍇ
			if (m_apBackObjIndex != NULL)
			{
				// �s����
				for (int nCnt = INIT_INT; nCnt < m_nRow; nCnt++)
				{
					// �񕪉�
					m_apBackObjIndex[nCnt] = new BACK_OBJ_TYPE[m_nCol];
				}
				// ��s�擾
				while (fgets(str, BYTE_NUM, pfile) != NULL)
				{
					char * cTokStr;

					cTokStr = strtok(str, ",");

					// #���܂܂�Ă���Δ�����
					char cSearchStr = '#';

					// �Ώە���
					strchr(cTokStr, cSearchStr);

					// NULL�ɂȂ�܂�
					while (cTokStr != NULL)
					{
						// #���܂܂�Ă���Δ�����
						char cSearchStr = '#';

						// �Ώە���
						strchr(cTokStr, cSearchStr);

						// �܂܂�Ă��Ȃ�������o��
						if (strchr(cTokStr, cSearchStr) == NULL)
						{
							// �s��Ƀu���b�N�̃^�C�v���i�[
							m_apBackObjIndex[nRowIndex][nColIndex] = (BACK_OBJ_TYPE)atoi(cTokStr);

							// ���̗��
							nColIndex++;
						}
						// NULL������
						cTokStr = strtok(NULL, ",");
					}
					// �C���N�������g
					nRowIndex++;

					// 0��
					nColIndex = INIT_INT;
				}
			}
		}
		// �t�@�C�������
		fclose(pfile);
	}
	else
	{
		return;
	}
}
//******************************************************************************
// �s�Ɨ�ݒ�
//******************************************************************************
void CMap::SetRowCol(LOAD_TYPE load_type)
{
	FILE * pfile = NULL;

	// NULL�̏ꍇ
	if (pfile == NULL)
	{
		// LOAD_TYPE_FLOOR�̏ꍇ
		if (load_type == LOAD_TYPE_FLOOR)
		{
			// GAME�̏ꍇ
			if (m_Type == TYPE_GAME)
			{
				pfile = fopen(GAME_FLOOR_TEXT, "r");
			}
			// TUTORIAL�̏ꍇ
			if (m_Type == TYPE_TUTORIAL)
			{
				pfile = fopen(TUTORIAL_FLOOR_TEXT, "r");
			}
		}
		// LOAD_TYPE_BLOCK�̏ꍇ
		if (load_type == LOAD_TYPE_BLOCK)
		{
			// GAME�̏ꍇ
			if (m_Type == TYPE_GAME)
			{
				pfile = fopen(GAME_BLOCK_TEXT, "r");
			}
			// TUTORIAL�̏ꍇ
			if (m_Type == TYPE_TUTORIAL)
			{
				pfile = fopen(TUTORIAL_BLOCK_TEXT, "r");
			}
		}
		// LOAD_TYPE_BACK_OBJ�̏ꍇ
		if (load_type == LOAD_TYPE_BACK_OBJ)
		{
			// GAME�̏ꍇ
			if (m_Type == TYPE_GAME)
			{
				pfile = fopen(GAME_BACK_OBJ_TEXT, "r");
			}
			// TUTORIAL�̏ꍇ
			if (m_Type == TYPE_TUTORIAL)
			{
				pfile = fopen(TUTORIAL_BACK_OBJ_TEXT, "r");
			}
		}
		// �s������
		m_nRow = INIT_INT;

		// �񏉊���
		m_nCol = INIT_INT;

		// csv�ǂݎ�菈��
		char str[BYTE_NUM];

		// �s
		int nRowIndex = INIT_INT;

		// ��
		int nColIndex = INIT_INT;

		// NULL�łȂ��ꍇ
		if (pfile != NULL)
		{
			// ��s�擾
			while (fgets(str, BYTE_NUM, pfile) != NULL)
			{
				char * cTokStr;

				cTokStr = strtok(str, ",");

				// NULL�ɂȂ�܂�
				while (cTokStr != NULL)
				{
					// #���܂܂�Ă���Δ�����
					char cSearchStr = '#';

					// �Ώە���
					strchr(cTokStr, cSearchStr);

					// �܂܂�Ă��Ȃ�������o��
					if (strchr(cTokStr, cSearchStr) == NULL)
					{
						// ���̗��
						nColIndex++;
					}

					// NULL������
					cTokStr = strtok(NULL, ",");
				}
				// ��ۑ�
				m_nCol = nColIndex;

				// 0��
				nColIndex = INIT_INT;

				// �C���N�������g
				nRowIndex++;

				// �s�ۑ�
				m_nRow = nRowIndex;
			}
			// �t�@�C�������
			fclose(pfile);
		}
		else
		{
			return;
		}
	}
}
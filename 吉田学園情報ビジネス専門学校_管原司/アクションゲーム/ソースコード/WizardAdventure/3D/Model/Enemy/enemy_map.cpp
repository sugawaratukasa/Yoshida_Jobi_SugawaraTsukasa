//******************************************************************************
// �G�̐��� [enemy_map.cpp]
// Author : �ǌ��@�i
//******************************************************************************
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "enemy.h"
#include "ghost.h"
#include "../3D/Model/Block/floor_block.h"
#include "enemy_map.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define OBJ_TEXT	("data/Map/Text/Enemy_Map.csv")																			// �e�L�X�g�̃p�X
#define BLOCK_SIZE	(D3DXVECTOR3(30.0f,30.0f,30.0f))																		// �u���b�N�̃T�C�Y
#define BLOCK_ROT	(D3DXVECTOR3(0.0f,0.0f,0.0f))																			// ����
#define BLOCK_POS	(D3DXVECTOR3(nCountCol * BLOCK_SIZE.x + m_pos.x - 500,nCountRow * -BLOCK_SIZE.y + 150.0f ,-200.0f))		// �u���b�N�̈ʒu
#define ENEMY_SIZE	(D3DXVECTOR3(30.0f,30.0f,30.0f))																		// �G�̃T�C�Y
#define ENEMY_POS	(D3DXVECTOR3(nCountCol * ENEMY_SIZE.x + m_pos.x - 500.0f,nCountRow * -ENEMY_SIZE.y + 150.0f ,-200.0f))	// �G�̈ʒu
#define BYTE_NUM	(1024)																									// �ǂݎ��镶����
#define MIN_ENEMY	(0)																										// �G�̍ŏ���
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CEnemy_Map::CEnemy_Map(int nPriority) : CScene(nPriority)
{
	m_apObjIndex	= NULL;
	m_nRow			= INIT_INT;
	m_nCol			= INIT_INT;
	m_pos			= INIT_D3DXVECTOR3;
	memset(m_apEnemy, NULL, sizeof(m_apEnemy));
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CEnemy_Map::~CEnemy_Map()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CEnemy_Map * CEnemy_Map::Create(D3DXVECTOR3 pos)
{
	// CEnemy_Map�̃|�C���^
	CEnemy_Map *pEnemy_Map = NULL;

	// NULL�̏ꍇ
	if (pEnemy_Map == NULL)
	{
		// �������m��
		pEnemy_Map = new CEnemy_Map;

		// NULL�łȂ��ꍇ
		if (pEnemy_Map != NULL)
		{
			// �ʒu���
			pEnemy_Map->m_pos = pos;

			// �������֐�
			pEnemy_Map->Init();
		}
	}
	// �|�C���^��Ԃ�
	return pEnemy_Map;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CEnemy_Map::Init(void)
{
	// �I�u�W�F�N�g�^�C�v�ݒ�
	SetObjType(OBJTYPE_ENEMY_MAP);

	// ����
	ObjCreate();
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CEnemy_Map::Uninit(void)
{
	// �j��
	Release();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CEnemy_Map::Update(void)
{
	// ��Ԃ̃J�E���g
	int nEnemyNum = INIT_INT;
	// �ő吔���J��Ԃ�
	for (int nCnt = INIT_INT; nCnt < MAX_ENEMY; nCnt++)
	{
		// NULL�łȂ��ꍇ
		if (m_apEnemy[nCnt] != NULL)
		{
			// �C���N�������g
			nEnemyNum++;

			// ��Ԏ擾
			int nState = m_apEnemy[nCnt]->GetState();

			// ���S��Ԃ̏ꍇ
			if (nState == CEnemy::STATE_DEAD)
			{
				m_apEnemy[nCnt] = NULL;

				// �f�N�������g
				nEnemyNum--;
			}
		}
	}
	// nEnemyNum��0�̏ꍇ
	if (nEnemyNum == MIN_ENEMY)
	{
		// true��
		m_bEnd = true;
	}
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CEnemy_Map::Draw(void)
{
}
//******************************************************************************
// �u���b�N����
//******************************************************************************
void CEnemy_Map::ObjCreate(void)
{
	// ���̃e�L�X�g�̍s��̐��ǂݍ���
	SetRowCol();

	// ���̏��ǂݍ���
	ObjLoad();

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
					// �u���b�N
				case OBJ_TYPE_BLOCK:
					// �u���b�N����
					CFloor_Block::Create(BLOCK_POS, BLOCK_ROT, BLOCK_SIZE, CFloor_Block::TYPE_ENEMY);
					break;
				case OBJ_TYPE_ENEMY_FIRE:
					// �΂̓G����
					for (int nCnt = INIT_INT; nCnt < MAX_ENEMY; nCnt++)
					{
						if (m_apEnemy[nCnt] == NULL)
						{
							m_apEnemy[nCnt] = CGhost::Create(ENEMY_POS, ENEMY_SIZE, CGhost::TYPE_FIRE);
							break;
						}
					}
					break;
				case OBJ_TYPE_ENEMY_ICE:
					// �X�̓G����
					for (int nCnt = INIT_INT; nCnt < MAX_ENEMY; nCnt++)
					{
						if (m_apEnemy[nCnt] == NULL)
						{
							m_apEnemy[nCnt] = CGhost::Create(ENEMY_POS, ENEMY_SIZE, CGhost::TYPE_ICE);
							break;
						}
					}
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
void CEnemy_Map::ObjLoad(void)
{
	// �t�@�C���ǂݍ���
	FILE * pfile = fopen(OBJ_TEXT, "r");

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
// �s�Ɨ�ݒ�
//******************************************************************************
void CEnemy_Map::SetRowCol(void)
{
	FILE * pfile = NULL;

	// NULL�̏ꍇ
	if (pfile == NULL)
	{
		// �t�@�C���ǂݍ���
		pfile = fopen(OBJ_TEXT, "r");

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
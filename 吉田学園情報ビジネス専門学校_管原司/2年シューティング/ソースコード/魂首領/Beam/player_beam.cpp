//******************************************************************************
// �v���C���[�̃r�[���̏��� [player_beam.cpp]
// Author : �ǌ��@�i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "../System/main.h"
#include "../System/renderer.h"
#include "../System/scene.h"
#include "../System/scene2d.h"
#include "../Enemy/enemy.h"
#include "beam.h"
#include "../Particle/particle.h"
#include "../Particle/particle_beam.h"
#include "../Boss/boss.h"
#include "../Boss/boss_left.h"
#include "../Boss/boss_right.h"
#include "player_beam.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define EFFECT_POS			(D3DXVECTOR3(EnemyPos.x, EnemyPos.y + EnemySize.y / 2, EnemyPos.z))	// �G�t�F�N�g�̈ʒu
#define EFFECT_POS2			(D3DXVECTOR3(pos.x, BossPos.y + BossSize.y / 2, pos.z))				// �G�t�F�N�g�̈ʒu
#define EFFECT_POS3			(D3DXVECTOR3(pos.x, Boss_RightPos.y + Boss_RightSize.y / 2, pos.z))	// �G�t�F�N�g�̈ʒu
#define EFFECT_POS4			(D3DXVECTOR3(pos.x, Boss_LeftPos.y + Boss_LeftSize.y / 2, pos.z))	// �G�t�F�N�g�̈ʒu
#define EFFECT_ROT			(D3DXVECTOR3(0.0f,0.0f,fAngle))										// �G�t�F�N�g�̌���
#define EFFECT_SIZE			(size * 1.5f)														// �G�t�F�N�g�T�C�Y
#define BEAM_COLOR			(D3DXCOLOR(0.0f,0.5f,1.0f,1.0f))									// �r�[���̐F
#define BEAM_COLOR2			(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))									// �r�[���̐F
#define EFFECT_COLOR		(D3DXCOLOR(0.0f,0.1f,1.0f,1.0f))									// �r�[���̐F
#define EFFECT_COLOR2		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))									// �r�[���̐F
#define BEAM_NUM_0			(0)																	// �z���1�Ԗ�
#define BEAM_NUM_1			(1)																	// �z���2�Ԗ�
#define DAMAGE				(3)																	// �_���[�W
#define DEVIDE_VALUE		(2)																	// ���鐔
#define RANDUM_ANGLE		(360 - 180)															// �ʓx�����_��
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CPlayer_Beam::CPlayer_Beam(int nPriority) : CScene(nPriority)
{
	memset(m_apBeam, NULL, sizeof(m_apBeam));
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CPlayer_Beam::~CPlayer_Beam()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CPlayer_Beam * CPlayer_Beam::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CBeam�N���X�̃|�C���^
	CPlayer_Beam *pPlayer_Beam;

	// �������m��
	pPlayer_Beam = new CPlayer_Beam;

	// ������
	pPlayer_Beam->Init();

	// �r�[������
	pPlayer_Beam->BeamCreate(pos,size);

	// �|�C���^��Ԃ�
	return pPlayer_Beam;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CPlayer_Beam::Init(void)
{
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CPlayer_Beam::Uninit(void)
{
	// �j��
	Release();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CPlayer_Beam::Update(void)
{
	// �����蔻��
	Collision();
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CPlayer_Beam::Draw(void)
{
}
//******************************************************************************
// �r�[������
//******************************************************************************
void CPlayer_Beam::BeamCreate(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �r�[������
	m_apBeam[BEAM_NUM_0] = CBeam::Create(pos,
		size,
		BEAM_COLOR2,
		CBeam::TEX_TYPE_01);

	m_apBeam[BEAM_NUM_1] = CBeam::Create(pos,
		size,
		BEAM_COLOR,
		CBeam::TEX_TYPE_02);
}
//******************************************************************************
// �r�[���j��
//******************************************************************************
void CPlayer_Beam::ReleaseAllBeam(void)
{
	// �ő吔����
	for (int nCnt = INIT_INT; nCnt < BEAM_MAX_NUM; nCnt++)
	{
		// �j��
		m_apBeam[nCnt]->Release();
	}

	// �I��
	Uninit();
	return;
}
//******************************************************************************
// �����蔻��
//******************************************************************************
void CPlayer_Beam::Collision(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = m_apBeam[BEAM_NUM_0]->GetPosition();

	// �T�C�Y�擾
	D3DXVECTOR3 size = m_apBeam[BEAM_NUM_0]->GetSize();

	// �T�C�Y�擾
	float fSize = m_apBeam[BEAM_NUM_0]->GetSizeY();

	// CScene�^�̃|�C���^
	CScene *pScene = NULL;

	//**************************************************************************
	// �G�̓����蔻��
	//**************************************************************************
	do
	{
		// �I�u�W�F�^�C�v���G�̏ꍇ
		pScene = GetScene(OBJTYPE_ENEMY);

		// NULL�łȂ��ꍇ
		if (pScene != NULL)
		{
			// �I�u�W�F�N�g�^�C�v�擾
			OBJTYPE objType = pScene->GetObjType();

			// OBJTYPE_ENEMY�̏ꍇ
			if (objType == OBJTYPE_ENEMY)
			{
				// �G�̈ʒu
				D3DXVECTOR3 EnemyPos = ((CEnemy*)pScene)->GetPosition();

				// �G�̃T�C�Y
				D3DXVECTOR3 EnemySize = ((CEnemy*)pScene)->GetSize();

				D3DXVECTOR3 box1Max = D3DXVECTOR3(size.x / DEVIDE_VALUE, size.y / DEVIDE_VALUE, size.z / DEVIDE_VALUE) + pos;
				D3DXVECTOR3 box1Min = D3DXVECTOR3(-size.x / DEVIDE_VALUE, -fSize / DEVIDE_VALUE, -size.z / DEVIDE_VALUE) + pos;
				D3DXVECTOR3 box2Max = D3DXVECTOR3(EnemySize.x / DEVIDE_VALUE, EnemySize.y / DEVIDE_VALUE, EnemySize.z / DEVIDE_VALUE) + EnemyPos;
				D3DXVECTOR3 box2Min = D3DXVECTOR3(-EnemySize.x / DEVIDE_VALUE, -EnemySize.y / DEVIDE_VALUE, -EnemySize.z / DEVIDE_VALUE) + EnemyPos;

				if (box1Max.y > box2Min.y&&
					box1Min.y < box2Max.y&&
					box1Max.x > box2Min.x&&
					box1Min.x < box2Max.x)
				{
					// �T�C�Y���
					fSize = (pos.y + fSize / DEVIDE_VALUE) - (EnemyPos.y + EnemySize.y / DEVIDE_VALUE);

					// �r�[���̐��J��Ԃ�
					for (int nCnt = INIT_INT; nCnt < BEAM_MAX_NUM; nCnt++)
					{
						// �T�C�Y�ݒ�
						m_apBeam[nCnt]->SetSizeY(fSize);
					}

					// ����
					float fAngle = float(rand() % RANDUM_ANGLE);

					// �G�t�F�N�g����
					CParticle_Beam::Create(EFFECT_POS, EFFECT_SIZE, EFFECT_ROT, EFFECT_COLOR, CParticle::TEX_TYPE_FLASH);

					// �G�Ƀ_���[�W��^����
					((CEnemy*)pScene)->HitEnemy(DAMAGE);
				}
			} 
		}
	} while (pScene != NULL);

	//**************************************************************************
	// �{�X�̓����蔻��
	//**************************************************************************
	do
	{
		// �I�u�W�F�^�C�v���G�̏ꍇ
		pScene = GetScene(OBJTYPE_BOSS);

		// NULL�łȂ��ꍇ
		if (pScene != NULL)
		{
			// �I�u�W�F�N�g�^�C�v�擾
			OBJTYPE objType = pScene->GetObjType();

			// OBJTYPE_ENEMY�̏ꍇ
			if (objType == OBJTYPE_BOSS)
			{
				// �G�̈ʒu
				D3DXVECTOR3 BossPos = ((CBoss*)pScene)->GetPosition();

				// �G�̃T�C�Y
				D3DXVECTOR3 BossSize = ((CBoss*)pScene)->GetCollisionSize();

				D3DXVECTOR3 box1Max = D3DXVECTOR3(size.x / DEVIDE_VALUE, size.y / DEVIDE_VALUE, size.z / DEVIDE_VALUE) + pos;
				D3DXVECTOR3 box1Min = D3DXVECTOR3(-size.x / DEVIDE_VALUE, -fSize / DEVIDE_VALUE, -size.z / DEVIDE_VALUE) + pos;
				D3DXVECTOR3 box2Max = D3DXVECTOR3(BossSize.x / DEVIDE_VALUE, BossSize.y / DEVIDE_VALUE, BossSize.z / DEVIDE_VALUE) + BossPos;
				D3DXVECTOR3 box2Min = D3DXVECTOR3(-BossSize.x / DEVIDE_VALUE, -BossSize.y / DEVIDE_VALUE, -BossSize.z / DEVIDE_VALUE) + BossPos;

				if (box1Max.y > box2Min.y&&
					box1Min.y < box2Max.y&&
					box1Max.x > box2Min.x&&
					box1Min.x < box2Max.x)
				{
					// �T�C�Y���
					fSize = (pos.y + fSize / DEVIDE_VALUE) - (BossPos.y + BossSize.y / DEVIDE_VALUE);

					// �r�[���̐��J��Ԃ�
					for (int nCnt = INIT_INT; nCnt < BEAM_MAX_NUM; nCnt++)
					{
						// �T�C�Y�ݒ�
						m_apBeam[nCnt]->SetSizeY(fSize);
					}

					// ����
					float fAngle = float(rand() % RANDUM_ANGLE);

					// �G�t�F�N�g����
					CParticle_Beam::Create(EFFECT_POS2, EFFECT_SIZE, EFFECT_ROT, EFFECT_COLOR, CParticle::TEX_TYPE_FLASH);

					// �G�Ƀ_���[�W��^����
					((CBoss*)pScene)->HitBoss(DAMAGE);
				}
			}
		}
	} while (pScene != NULL);

	//**************************************************************************
	// �{�X�E�̓����蔻��
	//**************************************************************************
	do
	{
		// �I�u�W�F�^�C�v���G�̏ꍇ
		pScene = GetScene(OBJTYPE_BOSS_RIGHT);

		// NULL�łȂ��ꍇ
		if (pScene != NULL)
		{
			// �I�u�W�F�N�g�^�C�v�擾
			OBJTYPE objType = pScene->GetObjType();

			// OBJTYPE_ENEMY�̏ꍇ
			if (objType == OBJTYPE_BOSS_RIGHT)
			{
				// �G�̈ʒu
				D3DXVECTOR3 Boss_RightPos = ((CBoss_Right*)pScene)->GetPosition();

				// �G�̃T�C�Y
				D3DXVECTOR3 Boss_RightSize = ((CBoss_Right*)pScene)->GetSize();

				D3DXVECTOR3 box1Max = D3DXVECTOR3(size.x / DEVIDE_VALUE, size.y / DEVIDE_VALUE, size.z / DEVIDE_VALUE) + pos;
				D3DXVECTOR3 box1Min = D3DXVECTOR3(-size.x / DEVIDE_VALUE, -fSize / DEVIDE_VALUE, -size.z / DEVIDE_VALUE) + pos;
				D3DXVECTOR3 box2Max = D3DXVECTOR3(Boss_RightSize.x / DEVIDE_VALUE, Boss_RightSize.y / DEVIDE_VALUE, Boss_RightSize.z / DEVIDE_VALUE) + Boss_RightPos;
				D3DXVECTOR3 box2Min = D3DXVECTOR3(-Boss_RightSize.x / DEVIDE_VALUE, -Boss_RightSize.y / DEVIDE_VALUE, -Boss_RightSize.z / DEVIDE_VALUE) + Boss_RightPos;

				if (box1Max.y > box2Min.y&&
					box1Min.y < box2Max.y&&
					box1Max.x > box2Min.x&&
					box1Min.x < box2Max.x)
				{
					// �T�C�Y���
					fSize = (pos.y + fSize / DEVIDE_VALUE) - (Boss_RightPos.y + Boss_RightSize.y / DEVIDE_VALUE);

					// �r�[���̐��J��Ԃ�
					for (int nCnt = INIT_INT; nCnt < BEAM_MAX_NUM; nCnt++)
					{
						// �T�C�Y�ݒ�
						m_apBeam[nCnt]->SetSizeY(fSize);
					}

					// ����
					float fAngle = float(rand() % RANDUM_ANGLE);

					// �G�t�F�N�g����
					CParticle_Beam::Create(EFFECT_POS3, EFFECT_SIZE, EFFECT_ROT, EFFECT_COLOR, CParticle::TEX_TYPE_FLASH);

					// �G�Ƀ_���[�W��^����
					((CBoss_Right*)pScene)->Hit(DAMAGE);
				}
			}
		}
	} while (pScene != NULL);

	//**************************************************************************
	// �{�X���̓����蔻��
	//**************************************************************************
	do
	{
		// �I�u�W�F�^�C�v���G�̏ꍇ
		pScene = GetScene(OBJTYPE_BOSS_LEFT);

		// NULL�łȂ��ꍇ
		if (pScene != NULL)
		{
			// �I�u�W�F�N�g�^�C�v�擾
			OBJTYPE objType = pScene->GetObjType();

			// OBJTYPE_ENEMY�̏ꍇ
			if (objType == OBJTYPE_BOSS_LEFT)
			{
				// �G�̈ʒu
				D3DXVECTOR3 Boss_LeftPos = ((CBoss_Left*)pScene)->GetPosition();

				// �G�̃T�C�Y
				D3DXVECTOR3 Boss_LeftSize = ((CBoss_Left*)pScene)->GetSize();

				D3DXVECTOR3 box1Max = D3DXVECTOR3(size.x / DEVIDE_VALUE, size.y / DEVIDE_VALUE, size.z / DEVIDE_VALUE) + pos;
				D3DXVECTOR3 box1Min = D3DXVECTOR3(-size.x / DEVIDE_VALUE, -fSize / DEVIDE_VALUE, -size.z / DEVIDE_VALUE) + pos;
				D3DXVECTOR3 box2Max = D3DXVECTOR3(Boss_LeftSize.x / DEVIDE_VALUE, Boss_LeftSize.y / DEVIDE_VALUE, Boss_LeftSize.z / DEVIDE_VALUE) + Boss_LeftPos;
				D3DXVECTOR3 box2Min = D3DXVECTOR3(-Boss_LeftSize.x / DEVIDE_VALUE, -Boss_LeftSize.y / DEVIDE_VALUE, -Boss_LeftSize.z / DEVIDE_VALUE) + Boss_LeftPos;

				if (box1Max.y > box2Min.y&&
					box1Min.y < box2Max.y&&
					box1Max.x > box2Min.x&&
					box1Min.x < box2Max.x)
				{
					// �T�C�Y���
					fSize = (pos.y + fSize / DEVIDE_VALUE) - (Boss_LeftPos.y + Boss_LeftSize.y / DEVIDE_VALUE);

					// �r�[���̐��J��Ԃ�
					for (int nCnt = INIT_INT; nCnt < BEAM_MAX_NUM; nCnt++)
					{
						// �T�C�Y�ݒ�
						m_apBeam[nCnt]->SetSizeY(fSize);
					}

					// ����
					float fAngle = float(rand() % RANDUM_ANGLE);

					// �G�t�F�N�g����
					CParticle_Beam::Create(EFFECT_POS4, EFFECT_SIZE, EFFECT_ROT, EFFECT_COLOR, CParticle::TEX_TYPE_FLASH);

					// �G�Ƀ_���[�W��^����
					((CBoss_Left*)pScene)->Hit(DAMAGE);
				}
			}
		}
	} while (pScene != NULL);
}
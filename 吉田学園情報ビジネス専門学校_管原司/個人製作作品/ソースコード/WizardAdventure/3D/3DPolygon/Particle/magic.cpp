//******************************************************************************
// ���@ [magic.cpp]
// Author : �ǌ��@�i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "particle.h"
#include "manager.h"
#include "../3D/Model/Enemy/enemy.h"
#include "../3D/Model/Enemy/ghost.h"
#include "../3D/Model/player.h"
#include "../3D/Model/Object/3d_obj.h"
#include "../3D/Model/Block/block.h"
#include "collision.h"
#include "Particle_Effect/particle_effect.h"
#include "../3D/Model/Object/wood.h"
#include "sound.h"
#include "magic.h"

//******************************************************************************
// �}�N����`
//******************************************************************************
#define MAX_TEXT			 (1024)										// �e�L�X�g�̍ő吔
#define FIRE_BALL_TEXT		 ("data/Effect/FireBall_Data.txt")			// �e�L�X�g
#define ICE_BALL_TEXT		 ("data/Effect/IceBall_Data.txt")			// �e�L�X�g
#define ENEMY_FIRE_BALL_TEXT ("data/Effect/Enemy_FireBall_Data.txt")	// �e�L�X�g
#define ENEMY_ICE_BALL_TEXT	 ("data/Effect/Enemy_IceBall_Data.txt")		// �e�L�X�g
#define REMAINDER			 (0)										// �]��0
#define MAX_LIFE			 (150)										// ���C�t�̍ő吔
#define MIN_LIFE			 (0)										// ���C�t�̍ŏ���
#define MOVE_VALUE			 (2.5f)										// �ړ���
#define SIZE				 (20.0f)									// �T�C�Y
#define DAMAGE				 (20)										// �_���[�W
#define WEAK_DAMAGE			 (100)										// ��_�_���[�W
#define DEVIDE				 (10)										// ���鐔
#define SIZE_XYZ			 (D3DXVECTOR3(20.0f,20.0f,20.0f))			// �T�C�Y
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CMagic::CMagic()
{
	m_pos			= INIT_D3DXVECTOR3;
	m_nCount		= INIT_INT;
	m_nCreateCount	= INIT_INT;
	m_nLife			= INIT_INT;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CMagic::~CMagic()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CMagic * CMagic::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE type)
{
	// CMagic�̃|�C���^
	CMagic *pMagic;

	// �������m��
	pMagic = new CMagic;

	// �ʒu���
	pMagic->m_pos = pos;

	// �ړ��ʑ��
	pMagic->m_move = move;

	// �ʒu���
	pMagic->m_Type = type;

	// ������
	pMagic->Init();

	// �|�C���^��Ԃ�
	return pMagic;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CMagic::Init(void)
{
	// ���C�t�ݒ�
	m_nLife = MAX_LIFE;

	// �^�C�v
	switch (m_Type)
	{
		// �΋�
	case TYPE_FIRE_BALL:
		// �e�L�X�g�t�@�C���ǂݍ���
		sprintf(m_cText, FIRE_BALL_TEXT);
		//�I�u�W�F�N�g�^�C�v�ݒ�
		SetObjType(OBJTYPE_MAGIC);
		break;
		// �X��
	case TYPE_ICE_BALL:
		// �e�L�X�g�t�@�C���ǂݍ���
		sprintf(m_cText, ICE_BALL_TEXT);
		//�I�u�W�F�N�g�^�C�v�ݒ�
		SetObjType(OBJTYPE_MAGIC);
		break;
		// �G�̉΋�
	case TYPE_ENEMY_FIRE_BALL:
		// �e�L�X�g�t�@�C���ǂݍ���
		sprintf(m_cText, ENEMY_FIRE_BALL_TEXT);
		//�I�u�W�F�N�g�^�C�v�ݒ�
		SetObjType(OBJTYPE_ENEMY_MAGIC);
		break;
	case TYPE_ENEMY_ICE_BALL:
		// �e�L�X�g�t�@�C���ǂݍ���
		sprintf(m_cText, ENEMY_ICE_BALL_TEXT);
		//�I�u�W�F�N�g�^�C�v�ݒ�
		SetObjType(OBJTYPE_ENEMY_MAGIC);
		break;
	}

	// �ǂݍ���
	Load(m_cText);
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CMagic::Uninit(void)
{
	// �j��
	Release();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CMagic::Update(void)
{
	// �C���N�������g
	m_nCount++;

	// �f�N�������g
	m_nLife--;

	// �]�肪0�̏ꍇ
	if (m_nCount % m_nCreateCount == REMAINDER)
	{
		CParticle::Create(m_pos, m_cText);
	}
	// ���C�t��0�ȉ��ɂȂ�����
	if (m_nLife <= MIN_LIFE)
	{
		// �I��
		Uninit();
		return;
	}

	// �ړ�
	m_pos += m_move;

	// �����蔻��
	Collision();
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CMagic::Draw(void)
{
}
//******************************************************************************
// �����蔻��֐�
//******************************************************************************
void CMagic::Collision(void)
{
	// �T�E���h�擾
	CSound *pSound = CManager::GetSound();

	// CScene�̃|�C���^
	CScene *pScene = NULL;

	// �΋��ƕX���̏ꍇ
	if (m_Type == TYPE_FIRE_BALL || m_Type == TYPE_ICE_BALL)
	{
		do
		{
			// �V�[���擾
			pScene = GetScene(OBJTYPE_ENEMY);
			// NULL�łȂ��ꍇ
			if (pScene != NULL)
			{
				// �I�u�W�F�N�g�^�C�v�擾
				OBJTYPE objtype = pScene->GetObjType();

				// OBJTYPE_ENEMY�̏ꍇ
				if (objtype == OBJTYPE_ENEMY)
				{
					// �ʒu�擾
					D3DXVECTOR3 EnemyPos = ((CEnemy*)pScene)->GetPos();
					D3DXVECTOR3 EnemySize = ((CEnemy*)pScene)->GetSize();
					int nType = ((CGhost*)pScene)->GetType();
					// �~�`�̓����蔻��
					if (CCollision::SphereCollision(m_pos, SIZE, EnemyPos, EnemySize.x) == true)
					{
						// �΋��œG���΂̏ꍇ
						if (m_Type == TYPE_FIRE_BALL && nType == CGhost::TYPE_FIRE)
						{
							// �������Đ�
							pSound->PlaySoundA(CSound::SOUND_LABEL_SE_FIRE_EXPLOSION);

							// �G�t�F�N�g����
							CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_FIRE_EXPLOSION);
							CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_FIRE_EXPLOSION_2);

							// �_���[�W
							((CEnemy*)pScene)->Hit(DAMAGE);
							Uninit();
							return;
						}
						// �΋��œG���X�̏ꍇ
						if (m_Type == TYPE_FIRE_BALL && nType == CGhost::TYPE_ICE)
						{
							// �������Đ�
							pSound->PlaySoundA(CSound::SOUND_LABEL_SE_FIRE_EXPLOSION);
							// �G�t�F�N�g����
							CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_FIRE_EXPLOSION);
							CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_FIRE_EXPLOSION_2);

							// �_���[�W
							((CEnemy*)pScene)->Hit(WEAK_DAMAGE);
							Uninit();
							return;
						}
						// �X���œG���X�̏ꍇ
						if (m_Type == TYPE_ICE_BALL && nType == CGhost::TYPE_ICE)
						{
							// �������Đ�
							pSound->PlaySoundA(CSound::SOUND_LABEL_SE_ICE_EXPLOSION);
							// �G�t�F�N�g����
							CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ICE_EXPLOSION);
							CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ICE_EXPLOSION_2);

							// �_���[�W
							((CEnemy*)pScene)->Hit(DAMAGE);
							Uninit();
							return;
						}
						// �X���œG���΂̏ꍇ
						if (m_Type == TYPE_ICE_BALL && nType == CGhost::TYPE_FIRE)
						{
							// �������Đ�
							pSound->PlaySoundA(CSound::SOUND_LABEL_SE_ICE_EXPLOSION);
							// �G�t�F�N�g����
							CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ICE_EXPLOSION);
							CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ICE_EXPLOSION_2);

							// �_���[�W
							((CEnemy*)pScene)->Hit(WEAK_DAMAGE);
							Uninit();
							return;
						}
					}
				}
			}
		} while (pScene != NULL);
	}
	// �G�̉΋��ƕX���̏ꍇ
	if (m_Type == TYPE_ENEMY_FIRE_BALL || m_Type == TYPE_ENEMY_ICE_BALL)
	{
		do
		{
			// �V�[���擾
			pScene = GetScene(OBJTYPE_PLAYER);
			// NULL�łȂ��ꍇ
			if (pScene != NULL)
			{
				// �I�u�W�F�N�g�^�C�v�擾
				OBJTYPE objtype = pScene->GetObjType();

				// OBJTYPE_ENEMY�̏ꍇ
				if (objtype == OBJTYPE_PLAYER)
				{
					// �ʒu
					D3DXVECTOR3 PlayerPos;

					// �ʒu�擾
					PlayerPos.x = ((CPlayer*)pScene)->GetMtxWorld(CPlayer::PARTS_UNDER_BODY)._41;
					PlayerPos.y = ((CPlayer*)pScene)->GetMtxWorld(CPlayer::PARTS_UNDER_BODY)._42;
					PlayerPos.z = ((CPlayer*)pScene)->GetMtxWorld(CPlayer::PARTS_UNDER_BODY)._43;

					// �T�C�Y�擾
					D3DXVECTOR3 PlayerSize = ((CPlayer*)pScene)->GetSize();

					// �~�`�̓����蔻��
					if (CCollision::SphereCollision(m_pos, SIZE, PlayerPos, PlayerSize.x / DEVIDE) == true)
					{
						// �q�b�g
						((CPlayer*)pScene)->Hit(DAMAGE);

						// �΂̏ꍇ
						if (m_Type == TYPE_ENEMY_FIRE_BALL)
						{
							// �G�t�F�N�g����
							CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ENEMY_FIRE_EXPLOSION);
							CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ENEMY_FIRE_EXPLOSION_2);
						}
						// �X�̏ꍇ
						if (m_Type == TYPE_ENEMY_ICE_BALL)
						{
							// �G�t�F�N�g����
							CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ICE_EXPLOSION);
							CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ICE_EXPLOSION_2);
						}

						// �I��
						Uninit();
						return;
					}
				}
			}
			// NULL�ɂȂ�܂ŌJ��Ԃ�
		} while (pScene != NULL);
	}
	do
	{
		// �V�[���擾
		pScene = GetScene(OBJTYPE_MAP_OBJ);
		// NULL�łȂ��ꍇ
		if (pScene != NULL)
		{
			// �I�u�W�F�N�g�^�C�v�擾
			OBJTYPE objtype = pScene->GetObjType();

			// OBJTYPE_ENEMY�̏ꍇ
			if (objtype == OBJTYPE_MAP_OBJ)
			{
				// �ʒu�擾
				D3DXVECTOR3 ObjPos = ((C3D_Obj*)pScene)->GetPos();

				// �T�C�Y�擾
				D3DXVECTOR3 ObjSize = ((C3D_Obj*)pScene)->GetSize();

				// �~�`�̓����蔻��
				if (CCollision::RectangleCollision(m_pos, SIZE_XYZ, ObjPos, ObjSize) == true)
				{
					// �΂̏ꍇ
					if (m_Type == TYPE_FIRE_BALL)
					{
						// �������Đ�
						pSound->PlaySoundA(CSound::SOUND_LABEL_SE_FIRE_EXPLOSION);

						// �G�t�F�N�g����
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_FIRE_EXPLOSION);
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_FIRE_EXPLOSION_2);

						// �^�C�v�擾
						int n3D_ObjType = ((C3D_Obj*)pScene)->GetType();

						// �^�C�v�����u���b�N�̏ꍇ
						if (n3D_ObjType == C3D_Obj::TYPE_WOOD)
						{
							// �G�t�F�N�g����
							CParticle_Effect::Create(ObjPos, CParticle_Effect::TYPE_WOOD_EFFECT);
							CParticle_Effect::Create(ObjPos, CParticle_Effect::TYPE_WOOD_EFFECT_2);
							// �I��
							((C3D_Obj*)pScene)->Uninit();
						}
					}
					// �X�̏ꍇ
					if (m_Type == TYPE_ICE_BALL)
					{
						// �������Đ�
						pSound->PlaySoundA(CSound::SOUND_LABEL_SE_ICE_EXPLOSION);

						// �G�t�F�N�g����
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ICE_EXPLOSION);
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ICE_EXPLOSION_2);
					}
					// �΂̏ꍇ
					if (m_Type == TYPE_ENEMY_FIRE_BALL)
					{
						// �G�t�F�N�g����
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ENEMY_FIRE_EXPLOSION);
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ENEMY_FIRE_EXPLOSION_2);
					}
					// �X�̏ꍇ
					if (m_Type == TYPE_ENEMY_ICE_BALL)
					{
						// �G�t�F�N�g����
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ICE_EXPLOSION);
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ICE_EXPLOSION_2);
					}
					// �I��
					Uninit();
					return;
				}
			}
		}
		// NULL�ɂȂ�܂ŌJ��Ԃ�
	} while (pScene != NULL);
	do
	{
		// �V�[���擾
		pScene = GetScene(OBJTYPE_BLOCK);
		// NULL�łȂ��ꍇ
		if (pScene != NULL)
		{
			// �I�u�W�F�N�g�^�C�v�擾
			OBJTYPE objtype = pScene->GetObjType();

			// OBJTYPE_ENEMY�̏ꍇ
			if (objtype == OBJTYPE_BLOCK)
			{
				// �ʒu�擾
				D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

				// �T�C�Y�擾
				D3DXVECTOR3 BlockSize = ((CBlock*)pScene)->GetSize();

				// �~�`�̓����蔻��
				if (CCollision::RectangleCollision(m_pos, SIZE_XYZ, BlockPos, BlockSize) == true)
				{
					// �΂̏ꍇ
					if (m_Type == TYPE_FIRE_BALL)
					{
						// �������Đ�
						pSound->PlaySoundA(CSound::SOUND_LABEL_SE_FIRE_EXPLOSION);

						// �G�t�F�N�g����
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_FIRE_EXPLOSION);
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_FIRE_EXPLOSION_2);
					}
					// �X�̏ꍇ
					if (m_Type == TYPE_ICE_BALL)
					{
						// �������Đ�
						pSound->PlaySoundA(CSound::SOUND_LABEL_SE_ICE_EXPLOSION);

						// �G�t�F�N�g����
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ICE_EXPLOSION);
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ICE_EXPLOSION_2);
					}
					// �΂̏ꍇ
					if (m_Type == TYPE_ENEMY_FIRE_BALL)
					{
						// �G�t�F�N�g����
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ENEMY_FIRE_EXPLOSION);
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ENEMY_FIRE_EXPLOSION_2);
					}
					// �X�̏ꍇ
					if (m_Type == TYPE_ENEMY_ICE_BALL)
					{
						// �G�t�F�N�g����
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ICE_EXPLOSION);
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ICE_EXPLOSION_2);
					}
					// �I��
					Uninit();
					return;
				}
			}
		}
		// NULL�ɂȂ�܂ŌJ��Ԃ�
	} while (pScene != NULL);
}
//******************************************************************************
// �ǂݍ��݊֐�
//******************************************************************************
void CMagic::Load(const char * cText)
{
	// �ǂݍ��ݗp
	char cReedText[MAX_TEXT];

	// �����̔��ʗp
	char cHeadText[MAX_TEXT];

	// �g��Ȃ�����
	char cDie[MAX_TEXT];

	// �t�@�C���|�C���^
	FILE *pFile = NULL;

	// NULL�̏ꍇ
	if (pFile == NULL)
	{
		//�t�@�C�����J��
		pFile = fopen(cText, "r");

		// NULL�łȂ��ꍇ
		if (pFile != NULL)
		{
			// SCRIPT�̕�����������܂�
			while (strcmp(cHeadText, "SCRIPT") != INIT_INT)
			{
				// �e�L�X�g����cReedText��������ǂݍ���
				fgets(cReedText, sizeof(cReedText), pFile);

				// �ǂݍ��񂾕�������cHeadText�Ɋi�[
				sscanf(cReedText, "%s", &cHeadText);
			}
			// cHeadText��SCRIPT��������
			if (strcmp(cHeadText, "SCRIPT") == INIT_INT)
			{
				// END_SCRIPT�̕�����������܂�
				while (strcmp(cHeadText, "END_SCRIPT") != INIT_INT)
				{
					// �e�L�X�g����cReedText��������ǂݍ���
					fgets(cReedText, sizeof(cReedText), pFile);

					// �ǂݍ��񂾕�������cHeadText�Ɋi�[
					sscanf(cReedText, "%s", &cHeadText);

					// cHeadText��MOTIONSET��������
					if (strcmp(cHeadText, "SETTINGS") == INIT_INT)
					{
						// END_MOTIONSET�̕�����������܂�
						while (strcmp(cHeadText, "END_SETTINGS") != INIT_INT)
						{
							// �e�L�X�g����cReedText��������ǂݍ���
							fgets(cReedText, sizeof(cReedText), pFile);

							// �ǂݍ��񂾕�������cHeadText�Ɋi�[
							sscanf(cReedText, "%s", &cHeadText);

							// cHeadText��ALPHA_BLEND�̏ꍇ
							if (strcmp(cHeadText, "CREATE_COUNT") == INIT_INT)
							{
								// ����m_bAlpha_Blend�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nCreateCount);
							}
						}
					}
				}
				// �t�@�C�������
				fclose(pFile);
			}
			// �J���Ȃ�������
			else
			{
				printf("�t�@�C�����J�������o���܂���ł����B\n");
			}
		}
	}
}
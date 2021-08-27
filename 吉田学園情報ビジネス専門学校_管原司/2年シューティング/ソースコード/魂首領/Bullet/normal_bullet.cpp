//******************************************************************************
// �e [normal_bullet.cpp]
// Author : �ǌ��@�i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "../System/main.h"
#include "../System/manager.h"
#include "../System/renderer.h"
#include "../System/scene.h"
#include "../System/scene2d.h"
#include "../Mode/game.h"
#include "bullet.h"
#include "../Enemy/normal_enemy.h"
#include "../Enemy/enemy.h"
#include "../Player/player.h"
#include "normal_bullet.h"
#include "../Boss/boss.h"
#include "../Boss/boss_left.h"
#include "../Boss/boss_right.h"
#include "../UI/score.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define ENEMY_DAMAGE			(10)		// �G�ɗ^����_���[�W
#define BOSS_MAIN_DAMAGE		(40)		// �{�X�̒��S�ɗ^����_���[�W
#define BOSS_DAMAGE				(20)		// �{�X�̒��S�ɗ^����_���[�W
#define ADD_SCORE				(100)		// �X�R�A���Z�l
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CNormal_Bullet::CNormal_Bullet(int nPriority) : CBullet(nPriority)
{
	m_move = INIT_D3DXVECTOR3;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CNormal_Bullet::~CNormal_Bullet()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CNormal_Bullet * CNormal_Bullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLOR col, CBullet::TEX_TYPE textype)
{
	// CNormal_Bullet�|�C���^
	CNormal_Bullet * pNormalBullet;

	// �������m��
	pNormalBullet = new CNormal_Bullet;

	// �e�̏��ݒ�
	pNormalBullet->SetBullet(pos, rot, size, col, textype, CScene::OBJTYPE_PLAYER_BULLET);

	// �ړ��ʑ��
	pNormalBullet->m_move = move;

	// ������
	pNormalBullet->Init();

	// �|�C���^��Ԃ�
	return pNormalBullet;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CNormal_Bullet::Init(void)
{
	// ������
	CBullet::Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CNormal_Bullet::Uninit(void)
{
	// �I��
	CBullet::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CNormal_Bullet::Update(void)
{
	// �X�V
	CBullet::Update();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// �q�b�g����
	HitEnemy();

	//�ʒu�X�V
	pos.x += m_move.x;
	pos.y += m_move.y;

	// �ʒu���W�ݒ�
	SetPosition(pos);
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CNormal_Bullet::Draw(void)
{
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

	// ���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �`��
	CBullet::Draw();

	// ���ɖ߂�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//******************************************************************************
// �q�b�g���菈��
//******************************************************************************
void CNormal_Bullet::HitEnemy(void)
{
	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// �X�R�A�̎擾
	CScore * pScore = CGame::GetScore();

	// �{�X�擾
	CBoss * pBoss = CGame::GetBoss();

	// CScene�^�̃|�C���^
	CScene *pScene = NULL;
	do
	{
		// �I�u�W�F�^�C�v���G�̏ꍇ
		pScene = GetScene(OBJTYPE_ENEMY);

		// NULL�`�F�b�N
		if (pScene != NULL)
		{
			// �I�u�W�F�^�C�v�擾
			OBJTYPE objType = pScene->GetObjType();
			// �I�u�W�F�N�g�^�C�v���G
			if (objType == OBJTYPE_ENEMY)
			{
				// ���W�ƃT�C�Y�擾
				D3DXVECTOR3 EnemyPos = ((CEnemy*)pScene)->GetPosition();
				D3DXVECTOR3 EnemySize = ((CEnemy*)pScene)->GetSize();

				// �����蔻��
				if (Collision(pos, EnemyPos, size, EnemySize) == true)
				{
					// �G�Ƀ_���[�W��^����
					((CEnemy*)pScene)->HitEnemy(ENEMY_DAMAGE);
					// �X�R�A���Z
					pScore->AddScore(ADD_SCORE);
					// �e������
					Uninit();
					return;
				}
			}
		}
	} while (pScene != NULL);

	// �{�X�̓����蔻��
	do
	{
		// �I�u�W�F�^�C�v���G�̏ꍇ
		pScene = GetScene(OBJTYPE_BOSS);
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_BOSS)
			{
				// ���W�ƃT�C�Y�擾
				D3DXVECTOR3 BossPos = ((CBoss*)pScene)->GetPosition();
				D3DXVECTOR3 BossSize = ((CBoss*)pScene)->GetSize();

				// �����蔻��
				if (Collision(pos, BossPos, size, BossSize) == true)
				{
					// �G�Ƀ_���[�W��^����
					((CBoss*)pScene)->HitBoss(BOSS_MAIN_DAMAGE);
					// �X�R�A���Z
					pScore->AddScore(ADD_SCORE);
					// �e������
					Uninit();
					return;
				}
			}
		}
	} while (pScene != NULL);

	// �{�X�̉E�����蔻��
	do
	{
		// �I�u�W�F�^�C�v���G�̏ꍇ
		pScene = GetScene(OBJTYPE_BOSS_RIGHT);
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_BOSS_RIGHT)
			{
				// ���W�ƃT�C�Y�擾
				D3DXVECTOR3 BossRightPos = ((CBoss_Right*)pScene)->GetPosition();
				D3DXVECTOR3 BossRightSize = ((CBoss_Right*)pScene)->GetSize();

				// �����蔻��
				if (Collision(pos, BossRightPos, size, BossRightSize) == true)
				{
					// �G�Ƀ_���[�W��^����
					((CBoss_Right*)pScene)->Hit(BOSS_DAMAGE);
					// �X�R�A���Z
					pScore->AddScore(ADD_SCORE);
					// �e������
					Uninit();
					return;
				}
			}
		}
	} while (pScene != NULL);

	// �{�X�̍������蔻��
	do
	{
		// �I�u�W�F�^�C�v���G�̏ꍇ
		pScene = GetScene(OBJTYPE_BOSS_LEFT);
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_BOSS_LEFT)
			{
				// ���W�ƃT�C�Y�擾
				D3DXVECTOR3 BossLeftPos = ((CBoss_Left*)pScene)->GetPosition();
				D3DXVECTOR3 BossLeftSize = ((CBoss_Left*)pScene)->GetSize();

				// �����蔻��
				if (Collision(pos, BossLeftPos, size, BossLeftSize) == true)
				{
					// �G�Ƀ_���[�W��^����
					((CBoss_Left*)pScene)->Hit(BOSS_DAMAGE);
					// �X�R�A���Z
					pScore->AddScore(ADD_SCORE);
					// �e������
					Uninit();
					return;
				}
			}
		}
	} while (pScene != NULL);
}
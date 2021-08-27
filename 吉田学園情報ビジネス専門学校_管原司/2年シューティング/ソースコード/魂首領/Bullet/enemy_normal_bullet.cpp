//******************************************************************************
// �G�̒e [enemy_normal_bullet.cpp]
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
#include "../Enemy/enemy.h"
#include "../Player/player.h"
#include "normal_bullet.h"
#include "enemy_normal_bullet.h"
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CEnemy_Normal_Bullet::CEnemy_Normal_Bullet(int nPriority) : CBullet(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CEnemy_Normal_Bullet::~CEnemy_Normal_Bullet()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CEnemy_Normal_Bullet * CEnemy_Normal_Bullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLOR col, CBullet::TEX_TYPE textype)
{
	// CNormal_Bullet�|�C���^
	CEnemy_Normal_Bullet * pEnemy_Normal_Bullet;

	// �������m��
	pEnemy_Normal_Bullet = new CEnemy_Normal_Bullet;

	// �e�̏��ݒ�
	pEnemy_Normal_Bullet->SetBullet(pos, rot, size, col, textype, CScene::OBJTYPE_ENEMY_BULLET);

	// �ړ��ʑ��
	pEnemy_Normal_Bullet->m_move = move;

	// ������
	pEnemy_Normal_Bullet->Init();

	// �|�C���^��Ԃ�
	return pEnemy_Normal_Bullet;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CEnemy_Normal_Bullet::Init(void)
{
	// ������
	CBullet::Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CEnemy_Normal_Bullet::Uninit(void)
{
	// �I��
	CBullet::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CEnemy_Normal_Bullet::Update(void)
{
	// �X�V
	CBullet::Update();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// �q�b�g����
	HitPlayer();

	//�ʒu�X�V
	pos.x += m_move.x;
	pos.y += m_move.y;

	// �ʒu���W�ݒ�
	SetPosition(pos);
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CEnemy_Normal_Bullet::Draw(void)
{
	// �`��
	CBullet::Draw();
}
//******************************************************************************
// �q�b�g�����֐�
//******************************************************************************
void CEnemy_Normal_Bullet::HitPlayer(void)
{
	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// CScene�N���X�̃|�C���^
	CScene * pScene = NULL;

	// �G�̓����蔻��
	do
	{
		// �I�u�W�F�^�C�v���G�̏ꍇ
		pScene = GetScene(OBJTYPE_PLAYER);
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_PLAYER)
			{
				// ���W�ƃT�C�Y�擾
				D3DXVECTOR3 PlayerPos = ((CPlayer*)pScene)->GetPosition();
				D3DXVECTOR3 PlayerSize = ((CPlayer*)pScene)->GetCollisionSize();

				// �����蔻��
				if (Collision(pos, PlayerPos, size, PlayerSize) == true)
				{
					// �G�Ƀ_���[�W��^����
					((CPlayer*)pScene)->HitPlayer();
					// �e������
					Uninit();
					return;
				}
			}
		}
	} while (pScene != NULL);
}

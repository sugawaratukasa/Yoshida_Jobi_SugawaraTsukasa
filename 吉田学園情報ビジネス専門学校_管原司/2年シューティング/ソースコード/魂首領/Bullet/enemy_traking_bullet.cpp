//******************************************************************************
// �_�������e [enemy_traking_bullet.cpp]
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
#include "enemy_traking_bullet.h"
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CEnemy_Traking_Bullet::CEnemy_Traking_Bullet(int nPriority) : CBullet(nPriority)
{
	m_move		= INIT_D3DXVECTOR3;
	m_fAngle	= INIT_FLOAT;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CEnemy_Traking_Bullet::~CEnemy_Traking_Bullet()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CEnemy_Traking_Bullet * CEnemy_Traking_Bullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLOR col, CBullet::TEX_TYPE textype)
{
	// CNormal_Bullet�|�C���^
	CEnemy_Traking_Bullet * pEnemy_Traking_Bullet;

	// �������m��
	pEnemy_Traking_Bullet = new CEnemy_Traking_Bullet;

	// �e�̏��ݒ�
	pEnemy_Traking_Bullet->SetBullet(pos, rot, size, col, textype, CScene::OBJTYPE_ENEMY_BULLET);

	// �ړ��ʑ��
	pEnemy_Traking_Bullet->m_move = move;

	// ������
	pEnemy_Traking_Bullet->Init();

	// �|�C���^��Ԃ�
	return pEnemy_Traking_Bullet;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CEnemy_Traking_Bullet::Init(void)
{
	// ������
	CBullet::Init();

	// �v���C���[�̎擾
	CPlayer * pPlayer = CGame::GetPlayer();
	
	// �v���C���[�̈ʒu���W�擾
	D3DXVECTOR3 PlayerPos = pPlayer->GetPosition();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �p�x�Z�o
	m_fAngle = atan2f(PlayerPos.y - pos.y, PlayerPos.x - pos.x);

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CEnemy_Traking_Bullet::Uninit(void)
{
	// �I��
	CBullet::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CEnemy_Traking_Bullet::Update(void)
{
	// �X�V
	CBullet::Update();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// �q�b�g��������
	HitPlayer();

	// �p�x���
	float fRad = m_fAngle;

	// �ʒu�X�V
	pos.x += m_move.x * cosf(fRad);
	pos.y += m_move.y * sinf(fRad);

	// �ʒu���W�ݒ�
	SetPosition(pos);
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CEnemy_Traking_Bullet::Draw(void)
{
	// �`��
	CBullet::Draw();
}
//******************************************************************************
// �q�b�g�����֐�
//******************************************************************************
void CEnemy_Traking_Bullet::HitPlayer(void)
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
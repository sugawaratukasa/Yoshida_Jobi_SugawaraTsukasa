//******************************************************************************
// �ʏ�̓G [normal_enemy.cpp]
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
#include "../Player/player.h"
#include "../Bullet/bullet.h"
#include "../Bullet/enemy_traking_bullet.h"
#include "../Polygon/item.h"
#include "../Particle/particle.h"
#include "../Particle/particle_explosion.h"
#include "enemy.h"
#include "normal_enemy.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define BULLET_MOVE_VALUE			(D3DXVECTOR3(5.0f,5.0f,0.0f))		// �e�̈ړ���
#define MOVE_VALUE					(D3DXVECTOR3(0.0f,2.0f,0.0f))		// �ړ���
#define BULLET_ROT					(D3DXVECTOR3(0.0f,0.0f,0.0f))		// �e�̌���
#define ENEMY_TRAKING_BULLET_SIZE	(D3DXVECTOR3(20.0f,20.0f,0.0f))		// ���x��1�̒e�̃T�C�Y
#define COLOR						(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// �F
#define ATTACK_COUNT				(60)								// �U���J�E���g
#define BULLET_NUMDER				(2)									// �e�̐�
#define INIT_ATTACK_COUNT			(0)									// �U���J�E���g������
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CNormal_Enemy::CNormal_Enemy(int nPriority) : CEnemy(nPriority)
{
	m_nAttackCount = INIT_INT;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CNormal_Enemy::~CNormal_Enemy()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CNormal_Enemy * CNormal_Enemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife, TEX_TYPE tex_type)
{
	// CNormal_Enemy�N���X�̃|�C���^
	CNormal_Enemy * pNormal_Enemy;

	// �������m��
	pNormal_Enemy = new CNormal_Enemy;

	// �G�̏��ݒ�
	pNormal_Enemy->SetEnemy(pos, rot, size, nLife, tex_type, CScene::OBJTYPE_ENEMY);

	// ������
	pNormal_Enemy->Init();

	// �|�C���^��Ԃ�
	return pNormal_Enemy;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CNormal_Enemy::Init(void)
{
	// ������
	CEnemy::Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CNormal_Enemy::Uninit(void)
{
	// �I��
	CEnemy::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CNormal_Enemy::Update(void)
{
	// �X�V
	CEnemy::Update();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �ړ���
	D3DXVECTOR3 move = MOVE_VALUE;

	// �U������
	Attack();

	// �ړ�
	pos.y += move.y;

	// �ʒu���W�ݒ�
	SetPosition(pos);
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CNormal_Enemy::Draw(void)
{
	// �`��
	CEnemy::Draw();
}
//******************************************************************************
// �U�������֐�
//******************************************************************************
void CNormal_Enemy::Attack(void)
{
	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �C���N�������g
	m_nAttackCount++;

	// 60���܂�0�̎�
	if (m_nAttackCount == ATTACK_COUNT)
	{
		// �񔭐���
		for (int nCount = INIT_INT; nCount < BULLET_NUMDER; nCount++)
		{
			CEnemy_Traking_Bullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z),
				BULLET_ROT,
				ENEMY_TRAKING_BULLET_SIZE,
				D3DXVECTOR3(BULLET_MOVE_VALUE.x + nCount, BULLET_MOVE_VALUE.y + nCount, BULLET_MOVE_VALUE.z),
				COLOR,
				CBullet::TEX_TYPE_ENEMY_NORMAL);
		}
		// �J�E���g��0�ɂ���
		m_nAttackCount = INIT_ATTACK_COUNT;
	}
}
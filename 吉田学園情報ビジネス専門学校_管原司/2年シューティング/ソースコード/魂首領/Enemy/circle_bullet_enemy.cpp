//******************************************************************************
// �~�`�̒e���o���G [circle_bullet_enemy.cpp]
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
#include "../Mode/game.h""
#include "../Player/player.h"
#include "../Bullet/bullet.h"
#include "../Bullet/enemy_normal_bullet.h"
#include "enemy.h"
#include "../Mode/game.h"
#include "../Polygon/item.h"
#include "circle_bullet_enemy.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define BULLET_MOVE_VALUE			(D3DXVECTOR3(5.0f,5.0f,0.0f))		// �e�̈ړ���
#define MOVE_VALUE					(D3DXVECTOR3(0.0f,2.0f,0.0f))		// �ړ���
#define BULLET_ROT					(D3DXVECTOR3(0.0f,0.0f,0.0f))		// �e�̌���
#define ITEM_SIZE					(D3DXVECTOR3(40.0f,40.0f,0.0f))		// �A�C�e���T�C�Y
#define ENEMY_NORMAL_BULLET_SIZE	(D3DXVECTOR3(20.0f,20.0f,0.0f))		// �e�̃T�C�Y
#define BULLET_COLOR				(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// �e�̐F
#define ATTACK_COUNT				(100)								// �U���J�E���g
#define BULLET_NUMBER				(20)								// �e��
#define BULLET_RADIAN				(360)								// �p�x

// �e�̈ړ�
#define BULLET_MOVE		(D3DXVECTOR3(cosf(D3DXToRadian(nCount * (BULLET_RADIAN / BULLET_NUMBER)))*BULLET_MOVE_VALUE.x, sinf(D3DXToRadian(nCount * (BULLET_RADIAN / BULLET_NUMBER)))*BULLET_MOVE_VALUE.y, 0.0f))
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CCirecle_Bullet_Enemy::CCirecle_Bullet_Enemy(int nPriority) : CEnemy(nPriority)
{
	m_nAttackCount = INIT_INT;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CCirecle_Bullet_Enemy::~CCirecle_Bullet_Enemy()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CCirecle_Bullet_Enemy * CCirecle_Bullet_Enemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife, TEX_TYPE tex_type, DROP_ITEM drop_item)
{
	// CNormal_Enemy�N���X�̃|�C���^
	CCirecle_Bullet_Enemy * pCirecle_Bullet_Enemy;

	// �������m��
	pCirecle_Bullet_Enemy = new CCirecle_Bullet_Enemy;

	// �G�̏��ݒ�
	pCirecle_Bullet_Enemy->SetEnemy(pos, rot, size, nLife, tex_type, CScene::OBJTYPE_ENEMY);

	// ���Ƃ��A�C�e���ݒ�
	pCirecle_Bullet_Enemy->m_DropItem = drop_item;

	// ������
	pCirecle_Bullet_Enemy->Init();

	// �|�C���^��Ԃ�
	return pCirecle_Bullet_Enemy;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CCirecle_Bullet_Enemy::Init(void)
{
	// ������
	CEnemy::Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CCirecle_Bullet_Enemy::Uninit(void)
{
	// �I��
	CEnemy::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CCirecle_Bullet_Enemy::Update(void)
{
	// �X�V
	CEnemy::Update();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �ړ���
	D3DXVECTOR3 move = MOVE_VALUE;

	// ��Ԏ擾
	int nState = CEnemy::GetState();

	// �U������
	Attack();

	// ���S��ԂȂ�
	if (nState == STATE_DEATH)
	{
		// DROP_ITEM_POWERUP�̏ꍇ
		if (m_DropItem == DROP_ITEM_POWERUP)
		{
			// �p���[�A�b�v�A�C�e������
			CItem::Create(pos, ITEM_SIZE, CItem::TYPE_POWERUP);
		}
		// DROP_ITEM_BOM�̏ꍇ
		if (m_DropItem == DROP_ITEM_BOM)
		{
			CItem::Create(pos, ITEM_SIZE, CItem::TYPE_BOM);
		}
	}

	// �ړ�
	pos.x += move.x;
	pos.y += move.y;

	// �ʒu���W�ݒ�
	SetPosition(pos);
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CCirecle_Bullet_Enemy::Draw(void)
{
	// �`��
	CEnemy::Draw();
}
//******************************************************************************
// �U�������֐�
//******************************************************************************
void CCirecle_Bullet_Enemy::Attack(void)
{
	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �C���N�������g
	m_nAttackCount++;

	// �J�E���g����100�̏ꍇ
	if (m_nAttackCount == ATTACK_COUNT)
	{
		// 20��J��Ԃ�
		for (int nCount = INIT_INT; nCount < BULLET_NUMBER; nCount++)
		{
			// �e����
			CEnemy_Normal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z),
				BULLET_ROT,
				ENEMY_NORMAL_BULLET_SIZE,
				BULLET_MOVE,
				BULLET_COLOR,
				CBullet::TEX_TYPE_ENEMY_NORMAL);
		}
		// �J�E���g����0�ɂ���
		m_nAttackCount = 0;
	}
}
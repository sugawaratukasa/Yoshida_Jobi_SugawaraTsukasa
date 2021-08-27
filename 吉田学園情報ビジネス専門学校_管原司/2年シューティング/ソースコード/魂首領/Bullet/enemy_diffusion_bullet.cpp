//******************************************************************************
// �g�U�e [enemy_diffudion_bullet.cpp]
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
#include "enemy_normal_bullet.h"
#include "enemy_diffusion_bullet.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define BULLET_ROT					(D3DXVECTOR3(0.0f,0.0f,0.0f))		// �e�̌���
#define ENEMY_NORMAL_BULLET_SIZE	(D3DXVECTOR3(20.0f,20.0f,0.0f))		// �e�̃T�C�Y
#define BULLET_COLOR				(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// �e�̐F
#define DIFF_BULLET_COUNT			(80)								// �g�U�e�J�E���g
#define BULLET_NUMBER				(20)								// �e�̐�
#define BULLET_SPEED				(5.0f)								// �e�̃X�s�[�h
#define BULLET_RADIAN				(360)								// �ʓx
#define BULLET_RADIAN_DEVIDE		(20)								// �ʓx�̏��Z�l
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CEnemy_Diffusion_Bullet::CEnemy_Diffusion_Bullet(int nPriority) : CBullet(nPriority)
{
	m_nDifCount = INIT_INT;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CEnemy_Diffusion_Bullet::~CEnemy_Diffusion_Bullet()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CEnemy_Diffusion_Bullet * CEnemy_Diffusion_Bullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLOR col, CBullet::TEX_TYPE textype)
{
	// CNormal_Bullet�|�C���^
	CEnemy_Diffusion_Bullet * pEnemy_Diffusion_Bullet;

	// �������m��
	pEnemy_Diffusion_Bullet = new CEnemy_Diffusion_Bullet;

	// �e�̏��ݒ�
	pEnemy_Diffusion_Bullet->SetBullet(pos, rot, size, col, textype, CScene::OBJTYPE_ENEMY_BULLET);

	// �ړ��ʑ��
	pEnemy_Diffusion_Bullet->m_move = move;

	// ������
	pEnemy_Diffusion_Bullet->Init();

	// �|�C���^��Ԃ�
	return pEnemy_Diffusion_Bullet;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CEnemy_Diffusion_Bullet::Init(void)
{
	// ������
	CBullet::Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CEnemy_Diffusion_Bullet::Uninit(void)
{
	// �I��
	CBullet::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CEnemy_Diffusion_Bullet::Update(void)
{
	// �X�V
	CBullet::Update();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �C���N�������g
	m_nDifCount++;

	// �J�E���g80�ȏ�̏ꍇ
	if (m_nDifCount >= DIFF_BULLET_COUNT)
	{
		// 20��J��Ԃ�
		for (int nCount = INIT_INT; nCount < BULLET_NUMBER; nCount++)
		{
			// �~�`�e����
			CEnemy_Normal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z),
				BULLET_ROT,
				ENEMY_NORMAL_BULLET_SIZE,
				D3DXVECTOR3(cosf(D3DXToRadian(nCount * (BULLET_RADIAN / BULLET_RADIAN_DEVIDE)))*BULLET_SPEED,
					sinf(D3DXToRadian(nCount * (BULLET_RADIAN / BULLET_RADIAN_DEVIDE)))*BULLET_SPEED, 
					0.0f),
				BULLET_COLOR,
				CBullet::TEX_TYPE_ENEMY_NORMAL);
		}

		//�I��
		Uninit();
		return;
	}

	// �ړ�
	pos.x += m_move.x;
	pos.y += m_move.y;

	// �ʒu���W�X�V
	SetPosition(pos);
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CEnemy_Diffusion_Bullet::Draw(void)
{
	// �`��
	CBullet::Draw();
}
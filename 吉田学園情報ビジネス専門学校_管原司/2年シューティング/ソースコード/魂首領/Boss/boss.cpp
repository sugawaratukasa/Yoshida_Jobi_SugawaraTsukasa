//******************************************************************************
// �{�X [boss.cpp]
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
#include "../Bullet/bullet.h"
#include "../Bullet/enemy_traking_bullet.h"
#include "../Bullet/enemy_normal_bullet.h"
#include "../Bullet/enemy_diffusion_bullet.h"
#include "../Player/player.h"
#include "../Mode/game.h"
#include "boss.h"
#include "boss_left.h"
#include "boss_right.h"
#include "../Polygon/fade.h"
#include "../Particle/particle.h"
#include "../Particle/particle_explosion.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define TEXTURE						("data/Texture/Enemy/BossMain2.png")// �e�N�X�`��
#define BOSS_MAIN_SIZE				(D3DXVECTOR3(150.0f,150.0f,0.0f))	// �{�X�̒����̃T�C�Y
#define BOSS_LEFT_SIZE				(D3DXVECTOR3(150.0f,150.0f,0.0f))	// �{�X�̍��̃T�C�Y
#define BOSS_RIGHT_SIZE				(D3DXVECTOR3(150.0f,150.0f,0.0f))	// �{�X�̉E�̃T�C�Y
#define BULLET_MOVE_VALUE			(D3DXVECTOR3(5.0f,5.0f,0.0f))		// �ړ���
#define BULLET_TRAKING_MOVE_VALUE	(D3DXVECTOR3(6.0f,6.0f,0.0f))		// �_�������e�̈ړ���
#define BULLET_DIFFUSION_MOVE_VALUE	(D3DXVECTOR3(0.0f,2.0f,0.0f))		// �g�U�e�̈ړ���
#define INIT_MOVE					(D3DXVECTOR3(0.0f,0.0f,0.0f))		// �ړ�������
#define BULLET_ROT					(D3DXVECTOR3(0.0f,0.0f,0.0f))		// �e�̌���
#define ENEMY_TRAKING_BULLET_SIZE	(D3DXVECTOR3(20.0f,20.0f,0.0f))		// ���x��1�̒e�̃T�C�Y
#define FIFFUSION_BULLET_SIZE		(D3DXVECTOR3(100.0f,100.0f,0.0f))	// �e�̃T�C�Y
#define COLOR						(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// �F
#define RED_COLOR					(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))	// �ԐF
#define BULLET_COLOR				(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// �e�̐F
#define BOSS_LIFE					(4000)								// �{�X�̃��C�t
#define DIVIDE_VALUE				(2)									// ���Z�l
#define INIT_ATTACK_COUNT			(0)									// �U����0
#define REMAINDER_VALUE				(0)									// ���܂�0
#define ATTACK_COUNT				(60)								// �U���J�E���g
#define ATTACK_COUNT2				(100)								// �U���J�E���g2
#define ATTACK_COUNT3				(250)								// �U���J�E���g3
#define BULLET_TRAKING_TIMES		(3)									// �_�������e�̐�
#define BULLET_TRAKING_TIMES2		(4)									// �_�������e�̐�2
#define DAMAGE_COUNT_MIN			(0)									// �_���[�W�J�E���g�ŏ�
#define DAMAGE_COUNT				(10)								// �_���[�W�J�E���g
#define LIFE_MIN					(0)									// ���C�t�ŏ��l
#define DEATH_COUNT					(90)								// ���S�J�E���g
#define EXPLOSION_COUNT				(4)									// �����J�E���g
#define RANDUM_POSX_VALUE			(600)								// �ʒu���WX�����_�����l
#define RANDUM_POSX_VALUE2			(300)								// �ʒu���WX�����_�����l2
#define RANDUM_POSY_VALUE			(200)								// �ʒu���WY�����_�����l
#define RANDUM_POSY_VALUE2			(100)								// �ʒu���WY�����_�����l2
#define RANDUM_SIZE_VALUE_MIN		(5)									// �����_���T�C�Y
#define RANDUM_SIZE_VALUE_MAX		(8)									// �����_���T�C�Y2
#define STATE_MOVE_VALUE			(2.0f)								// �ړ���
#define STATE_MOVE_VALUE_MIN		(0.0f)								// �ړ���
#define STATE_POS_VALUE				(200.0f)							// �ʒu��
#define MOVE_VALUE					(3.0f)								// �ړ���
#define SIZE_DEVIDE_VALUE			(3)									// �T�C�Y�����鐔
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPDIRECT3DTEXTURE9 CBoss::m_pTexture = NULL;
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CBoss::CBoss(int nPriority) : CScene2d(nPriority)
{
	m_CollisionSize			= INIT_D3DXVECTOR3;
	m_move					= INIT_D3DXVECTOR3;
	m_nLife					= INIT_INT;
	m_nAttackCount			= INIT_INT;
	m_nDamageCount			= INIT_INT;
	m_nSetCount				= INIT_INT;
	m_nDeathCount			= INIT_INT;
	m_State					= STATE_NONE;
	m_bMove					= false;
	m_bLifeHalf				= false;
}
//******************************************************************************
//�f�X�g���N�^
//******************************************************************************
CBoss::~CBoss()
{
}
//******************************************************************************
// �e�N�X�`���ǂݍ���
//******************************************************************************
HRESULT CBoss::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE, &m_pTexture);
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���j��
//******************************************************************************
void CBoss::Unload(void)
{
		// �e�N�X�`���̔j��
		if (m_pTexture != NULL)
		{
			m_pTexture->Release();
			m_pTexture = NULL;
		}
}
//******************************************************************************
// �����֐�
//******************************************************************************
CBoss * CBoss::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �{�X�|�C���^
	CBoss * pBoss;

	// �������m��
	pBoss = new CBoss;

	// �ʒu���W�ݒ�
	pBoss->SetPosition(pos);

	// �T�C�Y�ݒ�
	pBoss->SetSize(size);

	// ���
	pBoss->m_CollisionSize = size;

	// �J���[�ݒ�
	pBoss->SetRGBA(COLOR);

	// �e�N�X�`���󂯓n��
	pBoss->BindTexture(m_pTexture);

	// �J���[�ݒ�
	pBoss->SetObjType(OBJTYPE_BOSS);

	// ������
	pBoss->Init();

	// �|�C���^��Ԃ�
	return pBoss;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CBoss::Init()
{

	// �����蔻��
	m_CollisionSize.y = m_CollisionSize.y / SIZE_DEVIDE_VALUE;

	// �̗�
	m_nLife = BOSS_LIFE;

	// ���
	m_State = STATE_MOVE;

	// ������
	CScene2d::Init();

	// ������
	CBoss_Left::Create(BOSS_LEFT_SIZE, BOSS_LEFT_SIZE);

	// �E����
	CBoss_Right::Create(BOSS_RIGHT_SIZE, BOSS_RIGHT_SIZE);

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CBoss::Uninit(void)
{
	//�I��
	CScene2d::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CBoss::Update(void)
{
	// �X�V
	CScene2d::Update();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// ��ԏ���
	State();

	// �ʒu�X�V
	pos.x += m_move.x;
	pos.y += m_move.y;

	// ���W�ݒ�
	SetPosition(pos);

}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CBoss::Draw(void)
{
	// �`��
	CScene2d::Draw();
}
//******************************************************************************
// �q�b�g����
//******************************************************************************
void CBoss::HitBoss(int nDamage)
{
	// �ړ���ԂłȂ��ꍇ
	if (m_State != STATE_MOVE)
	{
		// �̗͌��Z
		m_nLife -= nDamage;

		// State��Damage��
		m_State = STATE_DAMAGE;
	}
}
//******************************************************************************
// �U�������֐�
//******************************************************************************
void CBoss::Attack(void)
{
	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �v���C���[�擾
	CPlayer * pPlayer = CGame::GetPlayer();

	// �v���C���[��bom���{�X��p�ɕύX
	pPlayer->SetBossBom(true);

	if (m_State == STATE_NORMAL|| m_State == STATE_DAMAGE)
	{
		// ���C�t�������ȏ�̏ꍇ
		if (m_bLifeHalf == false)
		{
			// �C���N�������g
			m_nAttackCount++;

			// 100���܂�0�̏ꍇ
			if (m_nAttackCount % ATTACK_COUNT2 == REMAINDER_VALUE)
			{
				// 3��J��Ԃ�
				for (int nCount = INIT_INT; nCount < BULLET_TRAKING_TIMES; nCount++)
				{
					// �_�������e����
					CEnemy_Traking_Bullet::Create(pos,
						BULLET_ROT,
						ENEMY_TRAKING_BULLET_SIZE,
						D3DXVECTOR3(BULLET_TRAKING_MOVE_VALUE.x + nCount, BULLET_TRAKING_MOVE_VALUE.y + nCount, BULLET_TRAKING_MOVE_VALUE.z),
						BULLET_COLOR,
						CBullet::TEX_TYPE_ENEMY_NORMAL);
				}
			}
			// �g�U�e
			if (m_nAttackCount % ATTACK_COUNT3 == REMAINDER_VALUE)
			{
				// �g�U�e����
				CEnemy_Diffusion_Bullet::Create(pos,
					BULLET_ROT,
					FIFFUSION_BULLET_SIZE,
					D3DXVECTOR3(BULLET_DIFFUSION_MOVE_VALUE.x, BULLET_DIFFUSION_MOVE_VALUE.y, BULLET_DIFFUSION_MOVE_VALUE.z),
					BULLET_COLOR,
					CBullet::TEX_TYPE_ENEMY_NORMAL);
			}
		}
		// ���C�t�������ȉ��ɂȂ����ꍇ
		if (m_nLife <= BOSS_LIFE / DIVIDE_VALUE)
		{
			// �J�E���g��0��
			m_nAttackCount = INIT_ATTACK_COUNT;
			// true��
			m_bLifeHalf = true;
		}
		// ���C�t�������ȉ��̏ꍇ
		if (m_bLifeHalf == true)
		{
			// �C���N�������g
			m_nAttackCount++;

			// 60���܂�0�̏ꍇ
			if (m_nAttackCount % ATTACK_COUNT == REMAINDER_VALUE)
			{
				for (int nCount = INIT_INT; nCount < BULLET_TRAKING_TIMES2; nCount++)
				{
					// �_�������e����
					CEnemy_Traking_Bullet::Create(pos,
						BULLET_ROT,
						ENEMY_TRAKING_BULLET_SIZE,
						D3DXVECTOR3(BULLET_TRAKING_MOVE_VALUE.x + nCount, BULLET_TRAKING_MOVE_VALUE.y + nCount, BULLET_TRAKING_MOVE_VALUE.z),
						BULLET_COLOR,
						CBullet::TEX_TYPE_ENEMY_NORMAL);
				}
			}
		}
	}
}
//******************************************************************************
// ��ԏ����֐�
//******************************************************************************
void CBoss::State(void)
{
	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �ŏ��̈ړ�
	if (m_State == STATE_MOVE)
	{
		// �ړ��ʂ�2.0f��
		m_move.y = STATE_MOVE_VALUE;

		// �ʒu���W��200.0f�ɂȂ����ꍇ
		if (pos.y >= STATE_POS_VALUE)
		{
			// �ړ��ʂ�0��
			m_move.y = STATE_MOVE_VALUE_MIN;

			// �ʏ��Ԃ�
			m_State = STATE_NORMAL;
		}
	}
	// �{�X���ړ�����������
	if (m_State == STATE_NORMAL || m_State == STATE_DAMAGE)
	{
		// �ړ�����
		Move();

		// �U������
		Attack();
	}
	// State���m�[�}���̏ꍇ
	if (m_State == STATE_NORMAL)
	{
		// �J���[��ʏ�ɂ���
		SetRGBA(COLOR);
	}
	// State��Damage�̏ꍇ
	if (m_State == STATE_DAMAGE)
	{
		// �_���[�W�J�E���g�̃C���N�������g
		m_nDamageCount++;

		// �Ԃ�����
		SetRGBA(RED_COLOR);

		// �J�E���g��2���܂�0�̎�
		if (m_nDamageCount % DIVIDE_VALUE == REMAINDER_VALUE)
		{
			// �J���[��ʏ�ɖ߂�
			SetRGBA(COLOR);
		}
		// �J�E���g��10�ɂȂ�����
		if (m_nDamageCount == DAMAGE_COUNT)
		{
			// State���m�[�}����
			m_State = STATE_NORMAL;

			// �J�E���g��0�ɂȂ�����
			m_nDamageCount = DAMAGE_COUNT_MIN;
		}
	}
	// ���S���o��Ԃ̏ꍇ
	if (m_State == STATE_DEATH_EFFECT)
	{
		// �ړ��ʂ�0��
		m_move = INIT_MOVE;

		// �e�S�j��
		CBullet::AllReleaseBullet();
	}
	// ���C�t��0�ɂȂ����ꍇ
	if (m_nLife <= LIFE_MIN)
	{
		// ���S�G�t�F�N�g�������
		m_State = STATE_DEATH_EFFECT;

		// ���S����
		Death();
	}
	// ���S��Ԃ̏ꍇ
	if (m_State == STATE_DEATH)
	{
		// �t�F�[�h�J�n
		CFade::Create(FADE_POS, FADE_SIZE, CSceneManager::MODE_RESULT);

		// �I��
		Uninit();
		return;
	}
}
//******************************************************************************
// �ړ������֐�
//******************************************************************************
void CBoss::Move(void)
{
	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();
	
	if (m_State != STATE_MOVE ||  m_State != STATE_DEATH_EFFECT || m_State != STATE_DEATH )
	{
		// false�̏ꍇ
		if (m_bMove == false)
		{
			m_move.x = MOVE_VALUE;
		}
		// ���ړ�
		if (pos.x + BOSS_RIGHT_SIZE.x + BOSS_RIGHT_SIZE.x / DIVIDE_VALUE >= MAX_GAME_WIDTH)
		{
			m_move.x = -MOVE_VALUE;
			m_bMove = true;
		}
		// �E�ړ�
		if (pos.x - BOSS_LEFT_SIZE.x - BOSS_LEFT_SIZE.x / DIVIDE_VALUE <= MIN_GAME_WIDTH)
		{
			m_move.x = MOVE_VALUE;
			m_bMove = true;
		}
		// ���W�ݒ�
		SetPosition(pos);
	}
}
//******************************************************************************
// ���S����
//******************************************************************************
void CBoss::Death(void)
{
	// �ʒu���W
	D3DXVECTOR3 pos = GetPosition();

	// �T�C�Y�����_����
	float fSize = float(rand() % RANDUM_SIZE_VALUE_MIN + RANDUM_SIZE_VALUE_MAX);
	// �ʒu�������_����
	float fPosX = float(rand() % RANDUM_POSX_VALUE - RANDUM_POSX_VALUE2);
	float fPosY = float(rand() % RANDUM_POSY_VALUE - RANDUM_POSY_VALUE2);

	// �T�C�Y
	D3DXVECTOR3 size = D3DXVECTOR3(fSize, fSize, 0.0f);

	// �ʒu
	D3DXVECTOR3 Explosion_Pos = D3DXVECTOR3(pos.x + fPosX, pos.y + fPosY, 0.0f);

	// �C���N�������g
	m_nDeathCount++;

	// 3���܂�0
	if (m_nDeathCount % EXPLOSION_COUNT == REMAINDER_VALUE)
	{
		// ��������
		CParticle_Explosion::CreateExplosionEffect(Explosion_Pos,size,CParticle_Explosion::TYPE_ENEMY);
	}
	// m_nDeathCount��60�ɂȂ����ꍇ
	if (m_nDeathCount == DEATH_COUNT)
	{
		m_State = STATE_DEATH;
	}
}
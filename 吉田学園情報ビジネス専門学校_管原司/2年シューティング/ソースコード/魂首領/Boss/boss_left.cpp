//******************************************************************************
// �{�X�� [boss_left.h]
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
//******************************************************************************
// �}�N����`
//******************************************************************************
#define TEXTURE						("data/Texture/Enemy/BossLeft2.png")// �e�N�X�`��
#define BULLET_NORMAL_MOVE_VALUE	(D3DXVECTOR3(2.0f,6.0f,0.0f))		// �ʏ�e�̈ړ���
#define BULLET_SPINING_MOVE_VALUE	(D3DXVECTOR3(3.0f,3.0f,0.0f))		// ��]�e�̈ړ���
#define BOSS_LEFT_SIZE				(D3DXVECTOR3(150.0f,150.0f,0.0f))	// �{�X�̍��̃T�C�Y
#define BULLET_ROT					(D3DXVECTOR3(0.0f,0.0f,0.0f))		// �e�̌���
#define ENEMY_NORMAL_BULLET_SIZE	(D3DXVECTOR3(20.0f,20.0f,0.0f))		// �e�̃T�C�Y
#define COLOR						(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// �F
#define RED_COLOR					(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))	// �ԐF
#define DEVIDE_VALUE				(2)									// �����
#define REMAINDER_VALUE				(0)									// �]��
#define DAMAGE_COUNT				(10)								// �_���[�W�J�E���g
#define INIT_DAMAGE_COUNT			(0)									// �_���[�W�J�E���g������
#define ATTACK_COUNT				(60)								// �U���J�E���g
#define ATTACK_COUNT2				(100)								// �U���J�E���g2
#define BULLET_NUMBER				(2)									// �e�̐�
#define BULLET_DEVIDE_BALUE			(3)									// �e���ˊԊu
#define BULLET_RADIAN				(360)								// �e�̔��ˌʓx
#define BULLET_RADIAN_DEVIDE		(20)								// �ʓx�̏��Z�l
// ��]�e�̈ړ�
#define ROTATION_BULLET_MOVE		(D3DXVECTOR3(cosf(D3DXToRadian(m_nHalfLife_AttackCount / BULLET_DEVIDE_BALUE * (BULLET_RADIAN / BULLET_RADIAN_DEVIDE)))*BULLET_SPINING_MOVE_VALUE.x, sinf(D3DXToRadian(m_nHalfLife_AttackCount / BULLET_DEVIDE_BALUE * (BULLET_RADIAN / BULLET_RADIAN_DEVIDE)))*BULLET_SPINING_MOVE_VALUE.y,0.0f))
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPDIRECT3DTEXTURE9 CBoss_Left::m_pTexture = NULL;
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CBoss_Left::CBoss_Left(int nPriority) : CScene2d(nPriority)
{
	m_State					= STATE_NONE;
	m_nAttackCount			= INIT_INT;
	m_nDamageCount			= INIT_INT;
	m_nHalfLife_AttackCount = INIT_INT;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CBoss_Left::~CBoss_Left()
{
}
//******************************************************************************
// �e�N�X�`���ǂݍ���
//******************************************************************************
HRESULT CBoss_Left::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE, &m_pTexture);
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���j��
//******************************************************************************
void CBoss_Left::Unload(void)
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
CBoss_Left * CBoss_Left::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �{�X�|�C���^
	CBoss_Left * pBoss_Left;

	// �������m��
	pBoss_Left = new CBoss_Left;

	// �ʒu���W�ݒ�
	pBoss_Left->SetPosition(pos);

	// �T�C�Y�ݒ�
	pBoss_Left->SetSize(size);

	// �J���[�ݒ�
	pBoss_Left->SetRGBA(COLOR);

	// �I�u�W�F�^�C�v�ݒ�
	pBoss_Left->SetObjType(OBJTYPE_BOSS_LEFT);

	// �e�N�X�`���󂯓n��
	pBoss_Left->BindTexture(m_pTexture);

	// ������
	pBoss_Left->Init();

	// �|�C���^��Ԃ�
	return pBoss_Left;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CBoss_Left::Init(void)
{
	// ��Ԃ�ʏ��
	m_State = STATE_NORMAL;

	// ������
	CScene2d::Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CBoss_Left::Uninit(void)
{
	// �I��
	CScene2d::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CBoss_Left::Update(void)
{
	// �X�V
	CScene2d::Update();

	// �v���C���[�̎擾
	CBoss * pBoss = CGame::GetBoss();

	// �v���C���[�̈ʒu���W�擾
	D3DXVECTOR3 BossPos = pBoss->GetPosition();

	// ��ԏ���
	State();

	// �U������
	Attack();

	// �ʒu���W�ݒ�
	SetPosition(D3DXVECTOR3(BossPos.x - BOSS_LEFT_SIZE.x, BossPos.y, BossPos.z));

}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CBoss_Left::Draw(void)
{
	// �`��
	CScene2d::Draw();
}
//******************************************************************************
// �q�b�g�����֐�
//******************************************************************************
void CBoss_Left::Hit(int nDamage)
{
	// �v���C���[�̎擾
	CBoss * pBoss = CGame::GetBoss();

	// �{�X�Ƀ_���[�W
	pBoss->HitBoss(nDamage);

	// �_���[�W��Ԃ�
	m_State = STATE_DAMAGE;

}
//******************************************************************************
// ��ԏ����֐�
//******************************************************************************
void CBoss_Left::State(void)
{

	// ��Ԃ��m�[�}���̏ꍇ
	if (m_State == STATE_NORMAL)
	{
		//�J���[��ʏ�ɂ���
		SetRGBA(COLOR);
	}
	// ��Ԃ�Damage�̏ꍇ
	if (m_State == STATE_DAMAGE)
	{
		// �J�E���g�C���N�������g
		m_nDamageCount++;

		// �Ԃ�����
		SetRGBA(RED_COLOR);

		//�J�E���g��2���܂�0�̎�
		if (m_nDamageCount % DEVIDE_VALUE == REMAINDER_VALUE)
		{
			//�J���[��ʏ�ɖ߂�
			SetRGBA(COLOR);
		}

		// �J�E���g��10�ɂȂ�����
		if (m_nDamageCount == DAMAGE_COUNT)
		{
			// ��Ԃ�ʏ��
			m_State = STATE_NORMAL;
			// �J�E���g��0�ɂȂ�����
			m_nDamageCount = INIT_DAMAGE_COUNT;
		}
	}
}
//******************************************************************************
// �U�������֐�
//******************************************************************************
void CBoss_Left::Attack(void)
{
	// �{�X�̎擾
	CBoss * pBoss = CGame::GetBoss();

	// �{�X�̃��C�t�擾
	bool bHalfLife = pBoss->GetHalfLife();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �{�X�̏�Ԏ擾
	int BossState = pBoss->GetState();

	if (BossState == CBoss::STATE_NORMAL || BossState == CBoss::STATE_DAMAGE)
	{
		// ���C�t�������ȏ�̏ꍇ
		if (bHalfLife == false)
		{
			// �C���N�������g
			m_nAttackCount++;

			// 60���܂�0�̏ꍇ
			if (m_nAttackCount % ATTACK_COUNT == REMAINDER_VALUE)
			{
				// ���E2���e����
				for (int nCount = INIT_INT; nCount < BULLET_NUMBER; nCount++)
				{
					// �e����
					CEnemy_Normal_Bullet::Create(D3DXVECTOR3(pos.x - BOSS_LEFT_SIZE.x / DEVIDE_VALUE, pos.y + BOSS_LEFT_SIZE.y / DEVIDE_VALUE, pos.z),
						BULLET_ROT,
						ENEMY_NORMAL_BULLET_SIZE,
						D3DXVECTOR3(BULLET_NORMAL_MOVE_VALUE.x + nCount, BULLET_NORMAL_MOVE_VALUE.y, 0.0f),
						COLOR,
						CBullet::TEX_TYPE_ENEMY_NORMAL);
				}
			}
		}
		// ���C�t�������ȉ��̏ꍇ
		if (bHalfLife == true)
		{
			m_nHalfLife_AttackCount++;

			// �J�E���g��100�ȏ�̏ꍇ
			if (m_nHalfLife_AttackCount >= ATTACK_COUNT2)
			{
				// 3���܂�0�̎�
				if (m_nHalfLife_AttackCount % BULLET_DEVIDE_BALUE == REMAINDER_VALUE)
				{
					// ��]�e����
					CEnemy_Normal_Bullet::Create(D3DXVECTOR3(pos.x + BOSS_LEFT_SIZE.x / DEVIDE_VALUE, pos.y + BOSS_LEFT_SIZE.y / DEVIDE_VALUE, pos.z),
						BULLET_ROT,
						ENEMY_NORMAL_BULLET_SIZE,
						ROTATION_BULLET_MOVE,
						COLOR,
						CBullet::TEX_TYPE_ENEMY_NORMAL);
				}
			}
		}
	}
}
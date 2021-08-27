//******************************************************************************
// �D�̖C�� [ship_battery_enemy.cpp]
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
#include "../Player/player.h"
#include "../Bullet/bullet.h"
#include "../Bullet/enemy_traking_bullet.h"
#include "../Mode/game.h"
#include "enemy.h"
#include "ship.h"
#include "ship_battery.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define BULLET_MOVE_VALUE			(D3DXVECTOR3(5.0f + nCount,5.0f + nCount,0.0f))		// �e�X�s�[�h
#define ENEMY_TRAKING_BULLET_SIZE	(D3DXVECTOR3(20.0f,20.0f,0.0f))						// ���x��1�̒e�̃T�C�Y
#define BULLET_COLOR_VALUE			(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))					// �e�̐F
#define BULLET_ROT_VALUE			(D3DXVECTOR3(0.0f,0.0f,0.0f))						// �����̒l
#define BULLET_SHOT_COUNT			(4)													// ���ː�
#define ATTACK_COUNT				(100)												// �U���J�E���g
#define HALF_DEVIDE					(2)													// ����2
#define COUNT_REMAINDER				(0)													// �]��
#define RADIAN						(90.0f)												// �p�x
#define ROT_RATE_MOVE				(0.2f)												// ����

//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CShip_Battery::CShip_Battery(int nPriority) : CEnemy(nPriority)
{
	m_pos			= INIT_D3DXVECTOR3;
	m_nAttackCount	= INIT_INT;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CShip_Battery::~CShip_Battery()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CShip_Battery * CShip_Battery::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife, TEX_TYPE tex_type)
{
	// CShip_Battery�N���X�̃|�C���^
	CShip_Battery * pShip_Battery;

	// �������m��
	pShip_Battery = new CShip_Battery;

	// �G�̏��ݒ�
	pShip_Battery->SetEnemy(pos, rot, size, nLife, tex_type, CScene::OBJTYPE_ENEMY);

	// �ʒu���W���
	pShip_Battery->m_pos = pos;

	// ������
	pShip_Battery->Init();

	// �|�C���^��Ԃ�
	return pShip_Battery;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CShip_Battery::Init(void)
{
	// ������
	CEnemy::Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CShip_Battery::Uninit(void)
{
	// �I��
	CEnemy::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CShip_Battery::Update(void)
{
	// �X�V
	CEnemy::Update();

	// �D�̎擾
	CShip * pShip = CGame::GetShip();

	// �D�̍��W�擾
	D3DXVECTOR3 ShipPos;
	ShipPos = pShip->GetPosition();

	// �ʒu���W�ݒ�
	SetPosition(ShipPos + m_pos);

	// �U������
	Attack();
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CShip_Battery::Draw(void)
{
	// �`��
	CEnemy::Draw();
}
//******************************************************************************
// �U�������֐�
//******************************************************************************
void CShip_Battery::Attack(void)
{
	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// �v���C���[�̎擾
	CPlayer * pPlayer = CGame::GetPlayer();

	// �v���C���[�̍��W�擾
	D3DXVECTOR3 PlayerPos = pPlayer->GetPosition();

	// �v���C���[�̏��擾
	int nPlayerState = INIT_INT;
	nPlayerState = pPlayer->GetPlayerState();

	// �v���C���[�̏�Ԃ��ʏ�܂��̓_���[�W��Ԃ̏ꍇ
	if (nPlayerState == CPlayer::STATE_NORMAL || nPlayerState == CPlayer::STATE_DAMAGE)
	{
		// �v���C���[�ւ̊p�x
		float fAngle = atan2f(PlayerPos.x - pos.x, PlayerPos.y - pos.y);

		// �e���ւ̔��a
		float fLength = size.y / HALF_DEVIDE;

		// �e����pos
		D3DXVECTOR3 Battery_Muzle_Pos = INIT_D3DXVECTOR3;

		// ����
		D3DXVECTOR3 rot = GetRot();

		// �O�̌���
		D3DXVECTOR3 rotDest = INIT_D3DXVECTOR3;

		// �U���J�E���g�C���N�������g
		m_nAttackCount++;

		//���W�����߂�
		Battery_Muzle_Pos.x = pos.x - cosf(fAngle + D3DXToRadian(RADIAN)) * fLength;
		Battery_Muzle_Pos.y = pos.y + sinf(fAngle + D3DXToRadian(RADIAN)) * fLength;

		// ����
		rotDest.z = fAngle;

		// rot�Ɋp�x����
		rot.z += (rotDest.z - rot.z) * ROT_RATE_MOVE;

		//�U������
		if (m_nAttackCount % ATTACK_COUNT == COUNT_REMAINDER)
		{
			for (int nCount = INIT_INT; nCount < BULLET_SHOT_COUNT; nCount++)
			{
				// 4���_�������e����
				CEnemy_Traking_Bullet::Create(D3DXVECTOR3(Battery_Muzle_Pos.x, Battery_Muzle_Pos.y, Battery_Muzle_Pos.z),
					BULLET_ROT_VALUE,
					ENEMY_TRAKING_BULLET_SIZE,
					BULLET_MOVE_VALUE,
					BULLET_COLOR_VALUE,
					CBullet::TEX_TYPE_ENEMY_NORMAL);
			}
		}
		// �����̐ݒ�
		SetRot(rot);
	}
}
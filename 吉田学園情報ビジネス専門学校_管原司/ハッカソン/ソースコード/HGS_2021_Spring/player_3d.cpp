//=============================================================================
//
// �v���C���[ [player.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "keyboard.h"
#include "joystick.h"
#include "scene2d.h"
#include "mode_game.h"
#include "player_3d.h"
#include "speedup.h"
#include "logo_over.h"
#include "logo_clear.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/Player.png")
#define SIZE (D3DXVECTOR3(200.0f,200.0f,0.0))
#define SPEED (15.0f)
#define CAMERA_DISTANCE (1000.0f)
#define GRAVITY (-4.5f)
#define JUMP_POWER (80.0f)
#define FLOOR (900.0f)
#define ADD_SPEED_VALUE (0.2f)
#define COLLISION_SIZE (D3DXVECTOR3(100.0f,300.0f,0.0f))
#define KNOCKBACK_VALUE (10.0f) //�m�b�N�o�b�N�ړ���(��)
#define KNOCKBACK_VALUE_UP (-60.0f) //�m�b�N�o�b�N�ړ���(�����)
#define DEATH_ADD_ROT (0.3f)//���񂾎��̉�]��
//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CPlayer3d::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

													//=============================================================================
													// �R���X�g���N�^
													//=============================================================================
CPlayer3d::CPlayer3d(int nPriority)
{
	m_Move = INITIAL_D3DXVECTOR3;						//�ړ���
	m_PositionOld = INITIAL_D3DXVECTOR3;				//�ߋ��̈ʒu
	m_CollisionSize = INITIAL_D3DXVECTOR3;				//�Փ˔���p�T�C�Y
	m_nSurvivalTime = 0;										//��������
	m_fCameraDistance = 0.0f;							//�J�����Ƃ̋���
	m_bJump = false;									//�W�����v
	m_State = STATE_NONE;								//���
	memset(&m_bIsCollision, 0, sizeof(m_bIsCollision));//����������
	m_nCounterAnim = 0;
	m_nPattarnAnim = 0;
	m_fAddSpeed = 1.0f;
	m_nCreateCount = 0;
	m_bSyagami = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer3d::~CPlayer3d()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CPlayer3d::TextureLoad(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		TEXTURE,						// �t�@�C���̖��O
		&m_pTexture);					// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CPlayer3d::TextureUnload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		//�e�N�X�`���̔j�������֐��Ăяo��
		m_pTexture->Release();
		//�e�N�X�`����NULL�ɂ���
		m_pTexture = NULL;
	}
}

//=============================================================================
// ���������֐�
//=============================================================================
CPlayer3d * CPlayer3d::Create(D3DXVECTOR3 Position)
{
	//�v���C���[�̃|�C���^
	CPlayer3d * pPlayer = NULL;
	//�v���C���[��NULL�̏ꍇ
	if (pPlayer == NULL)
	{
		//�v���C���[�̃������m��
		pPlayer = new CPlayer3d;
		//�v���C���[��NULL�ł͂Ȃ��ꍇ
		if (pPlayer != NULL)
		{
			//�v���C���[�̈ʒu��ݒ肷��
			pPlayer->SetPosition(Position);
			//�v���C���[�̌�����ݒ肷��
			pPlayer->SetRotation(D3DXVECTOR3(D3DXToRadian(0.0f), D3DXToRadian(0.0f), D3DXToRadian(0.0f)));
			//�v���C���[�̃T�C�Y��ݒ肷��
			pPlayer->SetSize(SIZE);
			//�v���C���[�̏����������֐��Ăяo��
			pPlayer->Init();
		}
	}
	//�v���C���[�̃|�C���^��Ԃ�
	return pPlayer;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CPlayer3d::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(m_nPattarnAnim * 0.2f, 0.0f);
	aTexture[1] = D3DXVECTOR2(m_nPattarnAnim * 0.2f + 0.2f, 0.0f);
	aTexture[2] = D3DXVECTOR2(m_nPattarnAnim * 0.2f, 1.0f);
	aTexture[3] = D3DXVECTOR2(m_nPattarnAnim * 0.2f + 0.2f, 1.0f);
	//�|���S��3D�̏����������֐��Ăяo��
	CPolygon3d::Init();
	//�Փ˔���p�T�C�Y�̎擾
	m_CollisionSize = COLLISION_SIZE;
	//�ړ����x�̏����ݒ�
	m_fSpeed = SPEED;
	//�J�����Ƃ̋����������ݒ�
	m_fCameraDistance = CAMERA_DISTANCE;
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CPlayer3d::Uninit(void)
{
	//�|���S��3D�̏I�������֐��Ăяo��
	CPolygon3d::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CPlayer3d::Update(void)
{
	//�ߋ��̈ʒu��ۑ�����
	m_PositionOld = GetPosition();

	//�ʏ��Ԃ̃e�N�X�`��
	m_nPattarnAnim = 0;

	if (m_State == STATE_DEATH)//���񂾂Ƃ����邭�邳����
	{
		D3DXVECTOR3 Rot = GetRotation();

		Rot.z += DEATH_ADD_ROT;
		SetRotation(Rot);
	}
	if (m_bJump == true)
	{
		D3DXVECTOR3 Rot = GetRotation();
		Rot.z += DEATH_ADD_ROT;
		SetRotation(Rot);
		m_nPattarnAnim = 1;
	}
	else if (m_bJump != true && m_State != STATE_DEATH)
	{
		D3DXVECTOR3 Rot = GetRotation();
		Rot.z = D3DXToRadian(0.0f);
		SetRotation(Rot);
		m_nPattarnAnim = 0;
	}
	if (m_bSyagami == true)
	{
		m_nPattarnAnim = 2;
	}
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(m_nPattarnAnim * 0.2f, 0.0f);
	aTexture[1] = D3DXVECTOR2(m_nPattarnAnim * 0.2f + 0.2f, 0.0f);
	aTexture[2] = D3DXVECTOR2(m_nPattarnAnim * 0.2f, 1.0f);
	aTexture[3] = D3DXVECTOR2(m_nPattarnAnim * 0.2f + 0.2f, 1.0f);
	//�|���S��3D�̍X�V�����֐��Ăяo��
	CPolygon3d::Update();
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�ʒu�̐ݒ�
	SetPosition(GetPosition() + m_Move);
	//�ړ������֐��Ăяo��
	Move();
	//���͏����֐��Ăяo��
	Input();
	//�������Ԃ����Z����
	m_nSurvivalTime++;
	if (m_nSurvivalTime % 500 == 0 && m_nSurvivalTime != 0)
	{
		m_fAddSpeed += ADD_SPEED_VALUE;
		CSpeedUp::Create();
		if (m_nSurvivalTime >= 7200)
		{
			if (m_nCreateCount == 0)
			{
				CClearLogo::Create();
				m_nCreateCount++;
			}
		}
	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CPlayer3d::Draw(void)
{
	//�|���S��3D�̕`�揈���֐��Ăяo��
	CPolygon3d::Draw();
}

//=============================================================================
// �ړ��ʃZ�b�g
//=============================================================================
void CPlayer3d::SetMove(D3DXVECTOR3 Move)
{
	m_Move = Move;
}

//=============================================================================
// �����蔻��Z�b�g
//=============================================================================
void CPlayer3d::SetCollisionSize(D3DXVECTOR3 CollisionSize)
{
	m_CollisionSize = CollisionSize;
}

//=============================================================================
// ���
//=============================================================================
void CPlayer3d::SetState(STATE state)
{
	m_State = state;
}

//=============================================================================
// ���S����
//=============================================================================
void CPlayer3d::Death(D3DXVECTOR3 HitPos)
{
	CSound * pSound = CManager::GetSound();
	float fKnockBackRot = 0.0f; //�m�b�N�o�b�N����
	D3DXVECTOR3 distance; //�v���C���[�ƓG�̋���
	if (m_State != STATE_DEATH)
	{
		m_State = STATE_DEATH;
		if (pSound != NULL)
		{
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_PLAYER_DAMAGE);
		}

		distance = GetPosition() - HitPos;

		fKnockBackRot = atan2f((HitPos.x - GetPosition().x), (HitPos.y - GetPosition().y));	//�v���C���[���猩�����������G�̂���������v�Z
																							//���̋t�����ɂԂ���΂�
		SetMove(D3DXVECTOR3(sinf(fKnockBackRot - D3DXToRadian(180))*KNOCKBACK_VALUE, KNOCKBACK_VALUE_UP, cosf(fKnockBackRot - D3DXToRadian(180))*KNOCKBACK_VALUE));
		COverLogo::Create();
	}
}

void CPlayer3d::SetIsCollision(CBlock::IS_COLLISION isCollision)
{
	m_bIsCollision = isCollision;
}

//=============================================================================
// ���͏����֐�
//=============================================================================
void CPlayer3d::Input(void)
{
	//�L�[�{�[�h�̎擾
	CKeyboard * pKeyboard = CManager::GetKeyboard();
	//�W���C�X�e�B�b�N�̎擾
	CJoystick * pJoystick = CManager::GetJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = pJoystick->GetDevice();
	DIJOYSTATE js;
	//�W���C�X�e�B�b�N�̐U���擾
	LPDIRECTINPUTEFFECT pDIEffect = CJoystick::GetEffect();
	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	//�Q�[�����[�h�̎擾
	CGameMode * pGameMode = CManager::GetGameMode();

	if (m_State != STATE_DEATH)
	{
		if (pKeyboard->GetKeyboardPress(DIK_LSHIFT) || pKeyboard->GetKeyboardPress(DIK_RSHIFT) || pJoystick->GetJoystickPress(JS_A))
		{
			m_CollisionSize.y = 50;
			m_nPattarnAnim = 2;
			m_bSyagami = true;
		}
		else
		{
			m_CollisionSize = COLLISION_SIZE;
			m_bSyagami = false;
		}
		if (m_bSyagami == false)
		{
			if (pKeyboard->GetKeyboardTrigger(DIK_SPACE) || pJoystick->GetJoystickTrigger(JS_X))
			{
				//�����W�����v���Ă��Ȃ�������
				if (m_bJump == false)
				{
					m_bIsCollision.bIsTop = false;
					//�W�����v��
					m_Move.y -= JUMP_POWER * m_fAddSpeed;
					//�W�����v��Ԃɂ���
					m_bJump = true;
				}
			}
		}

	}
}

//=============================================================================
// �ړ������֐�
//=============================================================================
void CPlayer3d::Move(void)
{
	//�ʒu���擾
	D3DXVECTOR3 Position = GetPosition();
	//�������S��Ԃ���Ȃ��Ƃ�
	if (m_State != STATE_DEATH)
	{
		//�ړ�������
		m_Move.x = m_fSpeed * m_fAddSpeed;
		////�W�����v���Ă�Ƃ�
		//if (m_bJump == true)
		//{
		//	//�d�͂�������
		//	m_Move.y -= GRAVITY;
		//}
	}
	if (Position.y >= FLOOR - GetSize().y / 2 && m_State != STATE_DEATH)
	{
		m_Move.y = 0.0f;
		SetPosition(D3DXVECTOR3(GetPosition().x, FLOOR - GetSize().y / 2, 0.0f));
		//�W�����v��Ԃɂ���
		m_bJump = false;
	}
	else
	{
		m_Move.y -= GRAVITY* m_fAddSpeed;
	}
}

//=============================================================================
// �ړ��\�͈͏����֐�
//=============================================================================
D3DXVECTOR3 CPlayer3d::MovableRange()
{
	//�ʒu���擾����
	D3DXVECTOR3 Position = GetPosition();
	//�T�C�Y���擾����
	D3DXVECTOR3 Size = GetSize();
	if (Position.y >= SCREEN_HEIGHT)
	{
		m_Move.y = 0.0f;

	}
	return Position;
}
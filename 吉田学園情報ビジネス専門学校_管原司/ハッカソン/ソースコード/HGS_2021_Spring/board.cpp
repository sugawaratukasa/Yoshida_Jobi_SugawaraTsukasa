//=============================================================================
//
// �{�[�h [board.cpp]
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
#include "board.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/board.png")
#define SIZE (D3DXVECTOR3(250.0f,50.0f,0.0))
#define SPEED (0.0f)
#define CAMERA_DISTANCE (500.0f)
#define GRAVITY (50.5f)
#define JUMP_POWER (150.0f)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBoard::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

												//=============================================================================
												// �R���X�g���N�^
												//=============================================================================
CBoard::CBoard(int nPriority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBoard::~CBoard()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CBoard::TextureLoad(void)
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
void CBoard::TextureUnload(void)
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
CBoard * CBoard::Create()
{
	//�{�[�h�̃|�C���^
	CBoard * pBoard = NULL;
	//�v���C���[��NULL�̏ꍇ
	if (pBoard == NULL)
	{
		//�v���C���[�̃������m��
		pBoard = new CBoard;
		//�v���C���[��NULL�ł͂Ȃ��ꍇ
		if (pBoard != NULL)
		{
			//�v���C���[�̌�����ݒ肷��
			pBoard->SetRotation(D3DXVECTOR3(D3DXToRadian(0.0f), D3DXToRadian(0.0f), D3DXToRadian(0.0f)));
			//�v���C���[�̃T�C�Y��ݒ肷��
			pBoard->SetSize(SIZE);
			//�v���C���[�̏����������֐��Ăяo��
			pBoard->Init();
		}
	}
	//�v���C���[�̃|�C���^��Ԃ�
	return pBoard;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CBoard::Init(void)
{
	//�v���C���[�̎擾
	CPlayer3d * pPlayer = CGameMode::GetPlayer3d();
	//�����v���C���[�̃|�W�V������NULL����Ȃ��ꍇ
	if (pPlayer != NULL)
	{
		//�v���C���[�̈ʒu���擾����
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
		//�v���C���[�̃T�C�Y���擾����
		D3DXVECTOR3 PlayerSize = pPlayer->GetSize();
		//�ʒu��ݒ肷��
		SetPosition(D3DXVECTOR3(PlayerPosition.x, 900.0f, PlayerPosition.z));
	}
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//�|���S��3D�̏����������֐��Ăяo��
	CPolygon3d::Init();
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CBoard::Uninit(void)
{
	//�|���S��3D�̏I�������֐��Ăяo��
	CPolygon3d::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CBoard::Update(void)
{
	//�|���S��3D�̍X�V�����֐��Ăяo��
	CPolygon3d::Update();
	//�v���C���[�̎擾
	CPlayer3d * pPlayer = CGameMode::GetPlayer3d();
	//�����v���C���[�̃|�W�V������NULL����Ȃ��ꍇ
	if (pPlayer != NULL)
	{
		if (pPlayer->GetState() != CPlayer3d::STATE_DEATH)
		{
			//�v���C���[�̈ʒu���擾����
			D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
			//�v���C���[�̃T�C�Y���擾����
			D3DXVECTOR3 PlayerSize = pPlayer->GetSize();
			//�ʒu��ݒ肷��
			SetPosition(D3DXVECTOR3(PlayerPosition.x, 900.0f, PlayerPosition.z));
		}

	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CBoard::Draw(void)
{
	//�|���S��3D�̕`�揈���֐��Ăяo��
	CPolygon3d::Draw();
}

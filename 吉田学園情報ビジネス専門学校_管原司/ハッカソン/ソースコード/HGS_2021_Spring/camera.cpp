//=============================================================================
//
// �J���� [camera.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "mode_game.h"
#include "renderer.h"
#include "keyboard.h"
#include "joystick.h"
#include "camera.h"
#include "player_3d.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define INITIAL_POSITION_V (D3DXVECTOR3(0.0f, 0.0f, 0.0f))		//���_�̏����l
#define INITIAL_POSITION_R (D3DXVECTOR3(0.0f,0.0f,0.0f))		//�����_�̏����l
#define INITIAL_VECTOR_U (D3DXVECTOR3(0.0f,0.0f,0.0f))			//������x�N�g��
#define INITIAL_ROTAION (D3DXVECTOR3(D3DXToRadian(0.0f),D3DXToRadian(0.0f),D3DXToRadian(0.0f)))		//��]�̏����l
#define INITIAL_DISTANCE (0.0f)									//�����̏����l
#define INITIAL_PLAYER_DISTANCE (0.0f)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
	m_PositionV = INITIAL_POSITION_V;				//���_�̈ʒu
	m_PositionR = INITIAL_POSITION_R;				//�����_�̈ʒu
	m_VectorU = INITIAL_VECTOR_U;					//������x�N�g��
	m_Rotation = INITIAL_ROTAION;					//��]
	m_fDistance = INITIAL_DISTANCE;					//���_�ƒ����_�̋���
	m_fPlayerDistance = INITIAL_PLAYER_DISTANCE;	//�v���C���[�ƃJ�����̋���
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CCamera::Init(void)
{
	//�v���C���[�̎擾
	CPlayer3d * pPlayer = CGameMode::GetPlayer3d();
	//�����v���C���[��NULL����Ȃ��ꍇ
	if (pPlayer != NULL)
	{
		//�v���C���[�̈ʒu��ݒ�
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
		//�v���C���[�Ƃ̋������w�肷��
		m_fPlayerDistance = pPlayer->GetCameraDistance();
		//������x�N�g�����w�肷��
		m_VectorU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		m_PositionV = D3DXVECTOR3(PlayerPosition.x, PlayerPosition.y, PlayerPosition.z + m_fPlayerDistance);
		m_PositionR = PlayerPosition;
	}
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CCamera::Update(void)
{
	//�v���C���[�̎擾
	CPlayer3d * pPlayer = CGameMode::GetPlayer3d();
	//�����v���C���[��NULL����Ȃ��ꍇ
	if (pPlayer != NULL)
	{
		if (pPlayer->GetState() != CPlayer3d::STATE_DEATH)
		{
			//�v���C���[�̈ʒu��ݒ�
			D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
			//������x�N�g�����w�肷��
			m_VectorU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			m_PositionV = D3DXVECTOR3(PlayerPosition.x + 550.0f, 0.0f, PlayerPosition.z + m_fPlayerDistance);
			m_PositionR = D3DXVECTOR3(PlayerPosition.x + 550.0f, 0.0f, PlayerPosition.z);
		}
	}
}

//=============================================================================
// �J�����ݒ�֐�
//=============================================================================
void CCamera::SetCamera(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_MtxView);
	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_MtxView, &m_PositionV, &m_PositionR, &m_VectorU);
	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_MtxView);
	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_MtxProjection);
	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_MtxProjection, D3DXToRadian(-90.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 10000.0f);
	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_MtxProjection);
}
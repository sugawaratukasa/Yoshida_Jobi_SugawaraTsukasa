//******************************************************************************
// �J���� [camera.cpp]
// Author : �ǌ��i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "camera.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define VECU_VALUE			(D3DXVECTOR3(0.0f,1.0f,0.0f))	// vecu�l
#define ROT_VALUE			(D3DXToRadian(1.0f))			// �J�����̋��ʍ��W�̈ړ�
#define PHI_VALUE			(D3DXToRadian(90.0f))			// phi�l
#define THETA_VALUE			(D3DXToRadian(270.0f))			// theta�l
#define DISTANCE_VALUE		(500.0f)						// ����
#define FOV_VALUE			(45.0f)							// ����p
#define MAX_DRAW_DISTANCE	(5000.0f)						// �ő�`�拗��
#define MIN_DRAW_DISTANCE	(10.0f)							// �ŏ��`�拗��
#define DEVIDE_VALUE		(3)								// ���鐔
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CCamera::CCamera()
{
	posV		= INIT_D3DXVECTOR3;
	posR		= INIT_D3DXVECTOR3;
	vecU		= INIT_D3DXVECTOR3;
	m_fPhi		= INIT_FLOAT;
	m_fTheta	= INIT_FLOAT;
	memset(mtxProjection, NULL, sizeof(mtxProjection));
	memset(mtxView, NULL, sizeof(mtxView));
}

//******************************************************************************
// �f�N�������g
//******************************************************************************
CCamera::~CCamera()
{

}

//******************************************************************************
// ����������
//******************************************************************************
void CCamera::Init(void)
{
	posV = INIT_D3DXVECTOR3;
	posR = INIT_D3DXVECTOR3;
	vecU = VECU_VALUE;
	m_fPhi = PHI_VALUE;
	m_fTheta = THETA_VALUE;
	memset(mtxProjection, NULL, sizeof(mtxProjection));
	memset(mtxView, NULL, sizeof(mtxView));
}

//******************************************************************************
// �I������
//******************************************************************************
void CCamera::Uninit(void)
{

}

//******************************************************************************
// �X�V����
//******************************************************************************
void CCamera::Update(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �����_
	posR.x = (sinf(m_fTheta)*cosf(m_fPhi));
	posR.y = cosf(m_fTheta);
	posR.z = (sinf(m_fTheta)*sinf(m_fPhi));

	// ����
	m_fDistance = DISTANCE_VALUE;

	// ���_	
	posV.x = m_fDistance*(sinf(m_fTheta)*cosf(m_fPhi));
	posV.y = m_fDistance*cosf(m_fTheta);
	posV.z = m_fDistance*(sinf(m_fTheta)*sinf(m_fPhi));

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&mtxView, &posV, &posR, &vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&mtxProjection, FOV_VALUE, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, MIN_DRAW_DISTANCE, MAX_DRAW_DISTANCE);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
}
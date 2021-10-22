//******************************************************************************
// �J���� [camera.cpp]
// Author : �ǌ��i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "scene.h"
#include "../3D/Model/player.h"
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
#define MOVE_VALUE			(2.0f)							// �ړ���
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CCamera::CCamera()
{
	m_posV		= INIT_D3DXVECTOR3;
	m_posR		= INIT_D3DXVECTOR3;
	m_vecU		= INIT_D3DXVECTOR3;
	AddPosV		= INIT_FLOAT;
	m_fPhi		= INIT_FLOAT;
	m_fTheta	= INIT_FLOAT;
	memset(m_mtxProjection, NULL, sizeof(m_mtxProjection));
	memset(m_mtxView, NULL, sizeof(m_mtxView));
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
	m_posV		= INIT_D3DXVECTOR3;
	m_posR		= INIT_D3DXVECTOR3;
	m_vecU		= VECU_VALUE;
	m_fPhi		= PHI_VALUE;
	m_fTheta	= THETA_VALUE;
	memset(m_mtxProjection, NULL, sizeof(m_mtxProjection));
	memset(m_mtxView, NULL, sizeof(m_mtxView));
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
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pKeyborad = CManager::GetInputKeyboard();

	// �V�[��
	CScene *pScene = NULL;

	D3DXVECTOR3 PlayerPos;
	do
	{
		// �I�u�W�F�^�C�v��PLAYER�̏ꍇ
		pScene = CScene::GetScene(CScene::OBJTYPE_PLAYER);

		// NULL�`�F�b�N
		if (pScene != NULL)
		{
			// �I�u�W�F�^�C�v�擾
			CScene::OBJTYPE objType = pScene->GetObjType();

			// �I�u�W�F�N�g�^�C�v���G
			if (objType == CScene::OBJTYPE_PLAYER)
			{
				// ���W�ƃT�C�Y�擾
				PlayerPos = ((CPlayer*)pScene)->GetPos();
			}
		}
	} while (pScene != NULL);

	// �����_
	m_posR.x = AddPosV + (sinf(m_fTheta)*cosf(m_fPhi));
	m_posR.y = cosf(m_fTheta);
	m_posR.z = (sinf(m_fTheta)*sinf(m_fPhi));

	// ����
	m_fDistance = DISTANCE_VALUE;

	// ���_	
	m_posV.x = AddPosV + (sinf(m_fTheta)*cosf(m_fPhi)) *  m_fDistance;
	m_posV.y = (cosf(m_fTheta)) * m_fDistance;
	m_posV.z = (sinf(m_fTheta)*sinf(m_fPhi))  * m_fDistance;

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);
	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);
	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);
	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, FOV_VALUE, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, MIN_DRAW_DISTANCE, MAX_DRAW_DISTANCE);
	//D3DXMatrixOrthoLH(&m_mtxProjection, (float)SCREEN_WIDTH / DEVIDE_VALUE, (float)SCREEN_HEIGHT / DEVIDE_VALUE, MIN_DRAW_DISTANCE, MAX_DRAW_DISTANCE);
	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}
//******************************************************************************
// �ړ������֐�
//******************************************************************************
void CCamera::Move(float fMove)
{
	// �ړ�
	AddPosV += fMove;
}
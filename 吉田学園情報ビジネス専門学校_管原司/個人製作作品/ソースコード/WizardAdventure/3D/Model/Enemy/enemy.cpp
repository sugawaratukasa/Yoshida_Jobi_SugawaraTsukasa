//******************************************************************************
// �G[enemy.cpp]
// Author : �ǌ� �i
//******************************************************************************

//******************************************************************************
//�C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "../3D/Model/model.h"
#include "collision.h"
#include "camera.h"
#include "enemy.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define GHOST_TEXT	("data/Model/Enemy/Ghost.x")	// �p�X
#define MIN_LIFE	(0)								// ���C�t�̍ŏ��l
//******************************************************************************
//�ÓI�����o�ϐ�
//******************************************************************************
LPD3DXMESH CEnemy::m_pMesh = NULL;
LPD3DXBUFFER CEnemy::m_pBuffMat = NULL;
DWORD CEnemy::m_nNumMat = NULL;
char* CEnemy::m_apFileName = { GHOST_TEXT };
LPDIRECT3DTEXTURE9 CEnemy::m_apTexture = NULL;
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CEnemy::CEnemy(int nPriority) :CScene(nPriority)
{
	m_pos		= INIT_D3DXVECTOR3;
	m_rot		= INIT_D3DXVECTOR3;
	m_size		= INIT_D3DXVECTOR3;
	m_pModel	= NULL;
	m_State		= STATE_NORMAL;
	m_nLife		= INIT_INT;
	m_bDraw		= true;
	memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));
}

//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CEnemy::~CEnemy()
{

}

//******************************************************************************
// ���f���̓ǂݍ���
//******************************************************************************
HRESULT CEnemy::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(m_apFileName,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat,
			NULL,
			&m_nNumMat,
			&m_pMesh
		);

	// �ǂݍ��݃e�N�X�`��
	LoadTexture();

	return S_OK;
}
//******************************************************************************
// ���f���̔j��
//******************************************************************************
void CEnemy::Unload(void)
{
		// ���b�V���̔j��
		if (m_pMesh != NULL)
		{
			m_pMesh->Release();
			m_pMesh = NULL;
		}
		// �}�e���A���̔j��
		if (m_pBuffMat != NULL)
		{
			m_pBuffMat->Release();
			m_pBuffMat = NULL;
		}
		if (m_nNumMat != NULL)
		{
			m_nNumMat = NULL;
		}


	// �e�N�X�`���j��
	UnloadTexture();
}
//******************************************************************************
// �e�N�X�`���ǂݍ���
//******************************************************************************
HRESULT CEnemy::LoadTexture(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// �}�e���A���������o��
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = INIT_INT; nCntMat < (signed)m_nNumMat; nCntMat++)
		{
			// �g�p���Ă���e�N�X�`��������Γǂݍ���
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				// �e�N�X�`���ǂݍ���
				if (FAILED(D3DXCreateTextureFromFile(
					pDevice,
					pMat[nCntMat].pTextureFilename,
					&m_apTexture)))
				{
					return E_FAIL;
				}
			}
		}

	return S_OK;
}
//******************************************************************************
// �e�N�X�`���ǂݍ���
//******************************************************************************
void CEnemy::UnloadTexture(void)
{
	for (int nCntMat = INIT_INT; nCntMat < (signed)m_nNumMat; nCntMat++)
	{
		// NULL�łȂ��ꍇ
		if (m_apTexture!= NULL)
		{
			// �e�N�X�`��Release
			m_apTexture->Release();

			// m_pTexture��NULL��
			m_apTexture= NULL;

		}
	}
}

//******************************************************************************
// ����������
//******************************************************************************
HRESULT CEnemy::Init(void)
{
	// ���f���̐���
	m_pModel = CModel::Create();

	for (int nCntMat = INIT_INT; nCntMat < (signed)m_nNumMat; nCntMat++)
	{
		// �e�N�X�`���̃o�C���h
		m_pModel->BindTexture(m_apTexture);
	}

	// ���f���̃o�C���h
	m_pModel->BindModel(m_pMesh, m_pBuffMat, m_nNumMat, -1);

	// ���ݒ�
	m_pModel->SetModel(m_pos, m_rot, m_size);

	return S_OK;
}

//******************************************************************************
// �I������
//******************************************************************************
void CEnemy::Uninit(void)
{
	// NULL�łȂ��ꍇ
	if (m_pModel != NULL)
	{
		// ���f���N���X�̏I������
		m_pModel->Uninit();

		// NULL��
		m_pModel = NULL;
	}
	// �j��
	Release();
}

//******************************************************************************
// �X�V����
//******************************************************************************
void CEnemy::Update(void)
{
	// �ʒu�X�V
	m_pModel->SetModel(m_pos, m_rot, m_size);

	// �J�����̈ʒu�擾
	D3DXVECTOR3 CameraPos = CManager::GetCamera()->GetPos();

	// �`�攻��
	// �͈͊O�̏ꍇ
	if (m_pos.x > CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE2 || m_pos.x < CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE2)
	{
		// true�̏ꍇ
		if (m_bDraw == true)
		{
			// false��
			m_bDraw = false;
		}
	}
	// �͈͓��̏ꍇ
	if (m_pos.x < CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE2 && m_pos.x > CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE2)
	{
		// false�̏ꍇ
		if (m_bDraw == false)
		{
			// true��
			m_bDraw = true;
		}
	}
	// ���C�t���ŏ��l�ȉ��ɂȂ�����
	if (m_nLife <= MIN_LIFE)
	{
		// ��Ԃ����S��Ԃ�
		m_State = STATE_DEAD;

		// �I��
		Uninit();
		return;
	}
}

//******************************************************************************
// �`�揈��
//******************************************************************************
void CEnemy::Draw(void)
{
	//�����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	m_pModel->SetWorldMatrix(m_mtxWorld);

	// true�̏ꍇ
	if (m_bDraw == true)
	{
		// ���f���N���X�̕`�揈��
		m_pModel->Draw();
	}
}
//******************************************************************************
// �q�b�g
//******************************************************************************
void CEnemy::Hit(int nDamage)
{
	// ���Z
	m_nLife -= nDamage;
}
//******************************************************************************
// ���ݒ�
//******************************************************************************
void CEnemy::SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife)
{
	m_pos	= pos;
	m_rot	= rot;
	m_size	= size;
	m_nLife = nLife;
	// �I�u�W�F�N�g�^�C�v�ݒ�
	SetObjType(OBJTYPE_ENEMY);
}
//******************************************************************************
// �ʒu�ݒ�
//******************************************************************************
void CEnemy::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//******************************************************************************
// �����ݒ�
//******************************************************************************
void CEnemy::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//******************************************************************************
// �T�C�Y�ݒ�
//******************************************************************************
void CEnemy::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}
//******************************************************************************
// �̗͐ݒ�
//******************************************************************************
void CEnemy::SetLife(int nLife)
{
	m_nLife = nLife;
}
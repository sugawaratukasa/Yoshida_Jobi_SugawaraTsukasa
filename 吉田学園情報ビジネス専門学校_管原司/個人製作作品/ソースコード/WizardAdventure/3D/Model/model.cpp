//******************************************************************************
// ���f������ [model.cpp]
// Author : �ǌ� �i
//******************************************************************************

//******************************************************************************
//�C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "camera.h"
#include "model.h"
//******************************************************************************
//�C���N�������g
//******************************************************************************
CModel::CModel()
{
	m_pMesh				= NULL;
	m_pBuffMat			= NULL;
	m_nNumMat			= NULL;
	m_pParent			= NULL;
	m_pTexture			= NULL;
	m_pos				= INIT_D3DXVECTOR3;
	m_rot				= INIT_D3DXVECTOR3;
	m_size				= INIT_D3DXVECTOR3;
	m_nldxModelParent	= INIT_INT;
	memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));
}
//******************************************************************************
//�f�N�������g
//******************************************************************************
CModel::~CModel()
{

}

//******************************************************************************
// ���[�V�����N���X�̃C���X�^���X����
//******************************************************************************
CModel * CModel::Create()
{
	// CModel�|�C���^����
	CModel *pModel;

	// CModel�^�̃������m��
	pModel = new CModel;

	// ������
	pModel->Init();

	// �|�C���^��Ԃ�
	return pModel;
}

//******************************************************************************
//����������
//******************************************************************************
HRESULT CModel::Init()
{
	return S_OK;
}

//******************************************************************************
//�I������
//******************************************************************************
void CModel::Uninit(void)
{
	// ���b�V����NULL��
	m_pMesh	= NULL;

	// �o�b�t�@��NULL��
	m_pBuffMat = NULL;

	// �}�e���A����NULL��
	m_nNumMat = NULL;

	// �e��NULL��
	m_pParent = NULL;

	// ���[���h���W��0�N���A
	memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));
}

//******************************************************************************
//�X�V����
//******************************************************************************
void CModel::Update(void)
{
}

//******************************************************************************
//�`�揈��
//******************************************************************************
void CModel::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL*pMat;
	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pBuffMat != NULL)
	{
		//�}�e���A���f�[�^�ւ̃|�C���^���擾����
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	}

	D3DXMATRIX mtxParent;
	if (m_pParent != NULL)
	{
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{
		pDevice->GetTransform(D3DTS_WORLD2, &mtxParent);
	}

	//���f���p�[�c�ɐe�̃}�g���b�N�X���|�����킹�邱�ƂŁA�ʒu���]��e�ɒǏ]������
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾����
	pDevice->GetMaterial(&matDef);

	for (int nCntMat = INIT_INT; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		pDevice->SetTexture(0, m_pTexture);

		// �F
		pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

		// NULL�łȂ��ꍇ
		if (m_pMesh != NULL)
		{

			//���f���p�[�c�̕`��
			m_pMesh->DrawSubset(nCntMat);
		}
	}

	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
}

//******************************************************************************
// ���f���̃e�N�X�`���ݒ�
//******************************************************************************
void CModel::BindModel(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD nNumMat, int nldxModelParent)
{
	// ���b�V���A�}�e���A�����̃|�C���^�A�}�e���A�����̐��A�e���f���̃C���f�b�N�X�̃o�C���h�A�e�N�X�`���̏��
	m_pMesh = pMesh;
	m_pBuffMat = pBuffMat;
	m_nNumMat = nNumMat;
	m_nldxModelParent = nldxModelParent;
}

//******************************************************************************
// ���f���̃e�N�X�`���ݒ�
//******************************************************************************
void CModel::BindTexture(LPDIRECT3DTEXTURE9 Texture)
{
	m_pTexture= Texture;
}

//=============================================================================
// ���f���̏ꏊ�A�p�x�ݒ�
//=============================================================================
void CModel::SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	m_pos = pos;
	m_rot = rot;
	m_size = size;
}
//******************************************************************************
// �ʒu�ݒ�
//******************************************************************************
void CModel::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//******************************************************************************
// �����ݒ�
//******************************************************************************
void CModel::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//******************************************************************************
// �T�C�Y�ݒ�
//******************************************************************************
void CModel::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

// ���f���̃y�A�����g�̏��̎󂯎��
//******************************************************************************
void CModel::SetParent(CModel *cmodel)
{
	// �|�C���^�̎󂯎��
	m_pParent = cmodel;
}

//******************************************************************************
// ���f���̍s��̃Z�b�g
//******************************************************************************
void CModel::SetWorldMatrix(D3DXMATRIX mtxWorld)
{
	m_mtxWorld = mtxWorld;
}
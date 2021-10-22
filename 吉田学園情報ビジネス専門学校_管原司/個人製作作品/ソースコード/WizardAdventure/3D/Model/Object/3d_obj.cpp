//******************************************************************************
// �u���b�N[block.cpp]
// Author : �ǌ� �i
//******************************************************************************

//******************************************************************************
//�C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "../3D/3DPolygon/scene3d.h"
#include "input.h"
#include "joystick.h"
#include "../3D/Model/model.h"
#include "../3D/3DPolygon/frame.h"
#include "collision.h"
#include "../3D/Model/player.h"
#include "../3D/Model/Block/block.h"
#include "camera.h"
#include "3d_obj.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define FLOOR_BLOCK		("data/Model/Object/floor_01.x")	// ��
#define NEEDLE_BLOCK	("data/Model/Object/Needle.x")		// �j
#define BLOCK_WOOD		("data/Model/Object/box.x")			// �ؔ�
#define BLOCK_STOON		("data/Model/Object/box_2.x")		// �΂̔�
#define BUTTON			("data/Model/Object/Button.x")		// �{�^��
#define GATE			("data/Model/Object/Gate_2.x")		// ��
#define GATEROOF		("data/Model/Object/GateRoof.x")	// ������
#define TREE			("data/Model/Object/Tree.x")		// ��
#define STONE_0			("data/Model/Object/stone000.x")	// ��
#define STONE_1			("data/Model/Object/stone001.x")	// ��
#define STONE_2			("data/Model/Object/stone002.x")	// ��
#define WOOD			("data/Model/Object/wood.x")		// ��
//******************************************************************************
//�ÓI�����o�ϐ�
//******************************************************************************
LPD3DXMESH C3D_Obj::m_pMesh[TYPE_MAX] = {};
LPD3DXBUFFER C3D_Obj::m_pBuffMat[TYPE_MAX] = {};
DWORD C3D_Obj::m_nNumMat[TYPE_MAX] = {};
char* C3D_Obj::m_apFileName[TYPE_MAX] = { FLOOR_BLOCK,NEEDLE_BLOCK,BLOCK_WOOD, BLOCK_STOON ,BUTTON, GATE, GATEROOF, TREE,STONE_0, STONE_1, STONE_2, WOOD };
LPDIRECT3DTEXTURE9 C3D_Obj::m_apTexture[TYPE_MAX] = {};
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
C3D_Obj::C3D_Obj(int nPriority) :CScene(nPriority)
{
	m_pos		= INIT_D3DXVECTOR3;
	m_rot		= INIT_D3DXVECTOR3;
	m_size		= INIT_D3DXVECTOR3;
	m_pModel	= NULL;
	m_Type		= TYPE_NONE;
	m_bDraw		= true;
	memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));
}

//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
C3D_Obj::~C3D_Obj()
{

}

//******************************************************************************
// ���f���̓ǂݍ���
//******************************************************************************
HRESULT C3D_Obj::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCnt = INIT_INT; nCnt < TYPE_MAX; nCnt++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(m_apFileName[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat[nCnt],
			NULL,
			&m_nNumMat[nCnt],
			&m_pMesh[nCnt]
		);
	}

	// �ǂݍ��݃e�N�X�`��
	LoadTexture();

	return S_OK;
}
//******************************************************************************
// ���f���̔j��
//******************************************************************************
void C3D_Obj::Unload(void)
{
	for (int nCnt = INIT_INT; nCnt < TYPE_MAX; nCnt++)
	{
		// ���b�V���̔j��
		if (m_pMesh[nCnt] != NULL)
		{
			m_pMesh[nCnt]->Release();
			m_pMesh[nCnt] = NULL;
		}
		// �}�e���A���̔j��
		if (m_pBuffMat[nCnt] != NULL)
		{
			m_pBuffMat[nCnt]->Release();
			m_pBuffMat[nCnt] = NULL;
		}
		if (m_nNumMat[nCnt] != NULL)
		{
			m_nNumMat[nCnt] = NULL;
		}
	}

	// �e�N�X�`���j��
	UnloadTexture();
}
//******************************************************************************
// �e�N�X�`���ǂݍ���
//******************************************************************************
HRESULT C3D_Obj::LoadTexture(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`������
	for (int nCount = INIT_INT; nCount < TYPE_MAX; nCount++)
	{
		// �}�e���A���������o��
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat[nCount]->GetBufferPointer();
		for (int nCntMat = INIT_INT; nCntMat < (signed)m_nNumMat[nCount]; nCntMat++)
		{
			// �g�p���Ă���e�N�X�`��������Γǂݍ���
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				// �e�N�X�`���ǂݍ���
				if (FAILED(D3DXCreateTextureFromFile(
					pDevice,
					pMat[nCntMat].pTextureFilename,
					&m_apTexture[nCount])))
				{
					return E_FAIL;
				}
			}
		}
	}

	return S_OK;
}
//******************************************************************************
// �e�N�X�`���ǂݍ���
//******************************************************************************
void C3D_Obj::UnloadTexture(void)
{
	for (int nCnt = INIT_INT; nCnt < TYPE_MAX; nCnt++)
	{
		for (int nCntMat = INIT_INT; nCntMat < (signed)m_nNumMat[nCnt]; nCntMat++)
		{
			// NULL�łȂ��ꍇ
			if (m_apTexture[nCnt] != NULL)
			{
				// �e�N�X�`��Release
				m_apTexture[nCnt]->Release();

				// m_pTexture��NULL��
				m_apTexture[nCnt] = NULL;

			}
		}
	}
}

//******************************************************************************
// ����������
//******************************************************************************
HRESULT C3D_Obj::Init(void)
{
	// ���f���̐���
	m_pModel = CModel::Create();

	for (int nCntMat = INIT_INT; nCntMat < (signed)m_nNumMat[m_Type]; nCntMat++)
	{
		// �e�N�X�`���̃o�C���h
		m_pModel->BindTexture(m_apTexture[m_Type]);
	}

	// ���f���̃o�C���h
	m_pModel->BindModel(m_pMesh[m_Type], m_pBuffMat[m_Type], m_nNumMat[m_Type], -1);

	// ���ݒ�
	m_pModel->SetModel(m_pos, m_rot, m_size);

	return S_OK;
}

//******************************************************************************
// �I������
//******************************************************************************
void C3D_Obj::Uninit(void)
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
void C3D_Obj::Update(void)
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
}

//******************************************************************************
// �`�揈��
//******************************************************************************
void C3D_Obj::Draw(void)
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
// ���ݒ�
//******************************************************************************
void C3D_Obj::SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, TYPE type)
{
	m_pos = pos;
	m_rot = rot;
	m_size = size;
	m_Type = type;

	// �I�u�W�F�N�g�^�C�v�ݒ�
	SetObjType(OBJTYPE_MAP_OBJ);
}
//******************************************************************************
// �ʒu�ݒ�
//******************************************************************************
void C3D_Obj::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//******************************************************************************
// �����ݒ�
//******************************************************************************
void C3D_Obj::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//******************************************************************************
// �T�C�Y�ݒ�
//******************************************************************************
void C3D_Obj::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}
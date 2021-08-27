//=============================================================================
//
// 3D�|���S���Ǘ� [polygon3d.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene3d.h"
#include "polygon_3d.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define INITIAL_SCALE (1.0f)	//�g�k�̏����l
#define INITIAL_ANGLE (0.0f)	//�p�x�̏����l
#define INITIAL_LENGTH (0.0f)	//�����̏����l

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPolygon3d::CPolygon3d(int nPriority) : CScene3d(nPriority)
{
	m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;	//���_�o�b�t�@�ւ̃|�C���^
						//�e�N�X�`�����W
	m_aTex[0] = D3DXVECTOR2(0.0f, 0.0f);
	m_aTex[1] = D3DXVECTOR2(1.0f, 0.0f);
	m_aTex[2] = D3DXVECTOR2(0.0f, 1.0f);
	m_aTex[3] = D3DXVECTOR2(1.0f, 1.0f);
	m_Color = INITIAL_D3DXCOLOR;					//���_�J���[
	m_fScale = INITIAL_SCALE;						//�k��
	m_fAngle = INITIAL_ANGLE;						//�p�x
	m_fLength = INITIAL_LENGTH;						//����
	memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));	//���[���h�}�g���N�X
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPolygon3d::~CPolygon3d()
{
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CPolygon3d::Init(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�Ƀ����_���[�̃f�o�C�X����
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	//���_����ݒ�
	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//�����̐ݒ�
	m_fLength = sqrtf((float)(((GetSize().x / 2) * (GetSize().x / 2)) + ((GetSize().y / 2) * (GetSize().y / 2))));
	//�p�x�̐ݒ�
	m_fAngle = atan2f((GetSize().y / 2), (GetSize().x / 2));
	//���_���W�̐ݒ�
	pVtx[0].pos.x = -cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[0].pos.y = -sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = +cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[1].pos.y = -sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = -cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[2].pos.y = +sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = +cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[3].pos.y = +sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[3].pos.z = 0.0f;
	//�@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[1].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[2].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[3].nor = D3DXVECTOR3(0, 1, 0);
	//���_�J���[�̐ݒ�
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;
	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = m_aTex[0];
	pVtx[1].tex = m_aTex[1];
	pVtx[2].tex = m_aTex[2];
	pVtx[3].tex = m_aTex[3];
	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CPolygon3d::Uninit(void)
{
	//�������_�o�b�t�@�̃|�C���^��NULL����Ȃ��ꍇ
	if (m_pVtxBuff != NULL)
	{
		//���_�o�b�t�@��j������
		m_pVtxBuff->Release();
		//���_�o�b�t�@�̃|�C���^��NULL�ɂ���
		m_pVtxBuff = NULL;
	}
	//�j�������֐��Ăяo��
	Release();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CPolygon3d::Update(void)
{
	// ���_����ݒ�
	VERTEX_3D *pVtx;
	//�����̐ݒ�
	m_fLength = sqrtf((float)(((GetSize().x / 2) * (GetSize().x / 2)) + ((GetSize().y / 2) * (GetSize().y / 2))));
	//�p�x�̐ݒ�
	m_fAngle = atan2f((GetSize().y / 2), (GetSize().x / 2));
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos.x = -cosf(m_fAngle) * m_fLength  * m_fScale;
	pVtx[0].pos.y = -sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = +cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[1].pos.y = -sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = -cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[2].pos.y = +sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = +cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[3].pos.y = +sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[3].pos.z = 0.0f;
	//�@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[1].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[2].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[3].nor = D3DXVECTOR3(0, 1, 0);
	//���_�J���[�̐ݒ�
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;
	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = m_aTex[0];
	pVtx[1].tex = m_aTex[1];
	pVtx[2].tex = m_aTex[2];
	pVtx[3].tex = m_aTex[3];
	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CPolygon3d::Draw(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�Ƀ����_���[�̃f�o�C�X����
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	ZeroMemory(&matDef, sizeof(matDef));
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRotation().y, GetRotation().x, GetRotation().z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	D3DXMatrixTranslation(&mtxTrans, GetPosition().x, GetPosition().y, GetPosition().z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	pDevice->SetTexture(0, m_pTexture);
	matDef.Ambient = m_Color;
	pDevice->SetMaterial(&matDef);
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	ZeroMemory(&matDef, sizeof(matDef));
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// �e�N�X�`����UV���W�ݒ�֐�
//=============================================================================
void CPolygon3d::SetTexture(D3DXVECTOR2 aTexture[NUM_VERTEX])
{
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		//�e�N�X�`����UV���W�̊��蓖��
		m_aTex[nCount] = aTexture[nCount];
	}
}
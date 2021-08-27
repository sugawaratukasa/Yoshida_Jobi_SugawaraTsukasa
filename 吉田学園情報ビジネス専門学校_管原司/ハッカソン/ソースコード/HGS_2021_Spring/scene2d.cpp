//=============================================================================
//
// 2D�V�[���Ǘ����� [scene2d.cpp]
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
#include "scene2d.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define INITIAL_SCALE (1.0f)
#define INITIAL_ANGLE (0.0f)
#define INITIAL_LENGTH (0.0f)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene2d::CScene2d(int nPriority) : CScene(nPriority)
{
	m_pTexture = NULL;										//�e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;										//���_�o�b�t�@�ւ̃|�C���^
	m_Position = INITIAL_D3DXVECTOR3;						//���W
	m_Size = INITIAL_D3DXVECTOR3;							//�T�C�Y
	m_Color = INITIAL_D3DXCOLOR;							//�J���[
	m_Rotation = INITIAL_ROTATION;							//��]
	memset(m_aVtxPosition, NULL, sizeof(m_aVtxPosition));	//���_���W
	memset(m_aTexture, NULL, sizeof(m_aTexture));			//�e�N�X�`����UV���W
	m_fScale = INITIAL_SCALE;								//�k��
	m_fAngle = INITIAL_ANGLE;								//�p�x
	m_fLength = INITIAL_LENGTH;								//����
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene2d::~CScene2d()
{
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CScene2d::Init(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�Ƀ����_���[�̃f�o�C�X����
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//���_����ݒ�
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//�����̐ݒ�
	m_fLength = sqrtf((float)(((m_Size.x / 2) * (m_Size.x / 2)) + ((m_Size.y / 2) * (m_Size.y / 2))));
	//�p�x�̐ݒ�
	m_fAngle = atan2f((m_Size.y / 2), (m_Size.x / 2));
	//���_���W�̐ݒ�
	pVtx[0].pos.x = m_Position.x - cosf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[0].pos.y = m_Position.y - sinf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_Position.x + cosf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[1].pos.y = m_Position.y - sinf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_Position.x - cosf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[2].pos.y = m_Position.y + sinf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_Position.x + cosf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[3].pos.y = m_Position.y + sinf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[3].pos.z = 0.0f;
	//���Z���̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[�̐ݒ�
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;
	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = m_aTexture[0];
	pVtx[1].tex = m_aTexture[1];
	pVtx[2].tex = m_aTexture[2];
	pVtx[3].tex = m_aTexture[3];
	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CScene2d::Uninit(void)
{
	//�������_�o�b�t�@�̃|�C���^��NULL����Ȃ��ꍇ
	if (m_pVtxBuff != NULL)
	{
		//���_�o�b�t�@�̔j��
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
void CScene2d::Update(void)
{
	//���_����ݒ�
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//�����̐ݒ�
	m_fLength = sqrtf((float)(((m_Size.x / 2) * (m_Size.x / 2)) + ((m_Size.y / 2) * (m_Size.y / 2))));
	//�p�x�̐ݒ�
	m_fAngle = atan2f((m_Size.y / 2), (m_Size.x / 2));
	//���_���W�̐ݒ�
	pVtx[0].pos.x = m_Position.x - cosf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[0].pos.y = m_Position.y - sinf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_Position.x + cosf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[1].pos.y = m_Position.y - sinf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_Position.x - cosf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[2].pos.y = m_Position.y + sinf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_Position.x + cosf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[3].pos.y = m_Position.y + sinf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[3].pos.z = 0.0f;
	//���Z���̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[�̐ݒ�
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;
	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = m_aTexture[0];
	pVtx[1].tex = m_aTexture[1];
	pVtx[2].tex = m_aTexture[2];
	pVtx[3].tex = m_aTexture[3];
	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CScene2d::Draw(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�Ƀ����_���[�̃f�o�C�X����
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);
	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// ���_���W�ݒ�֐�
//=============================================================================
void CScene2d::SetVertexPosition(D3DXVECTOR3 VtxPos[NUM_VERTEX])
{
	//���_������
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		//�e�N�X�`����UV���W���蓖��
		m_aVtxPosition[nCount] = VtxPos[nCount];
	}
}

//=============================================================================
// �e�N�X�`����UV���W�ݒ�֐�
//=============================================================================
void CScene2d::SetTexture(D3DXVECTOR2 aTex[NUM_VERTEX])
{
	//���_������
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		//�e�N�X�`����UV���W�̊��蓖��
		m_aTexture[nCount] = aTex[nCount];
	}
}
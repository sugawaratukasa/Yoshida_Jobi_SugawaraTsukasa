//******************************************************************************
// 2D [scene2d.cpp]
// Author : �ǌ��i
//******************************************************************************

//******************************************************************************
//�C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define DEFAULLT_COL	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// �W���̐F
#define DEFAULT_SCALE	(1.0f)								// �W���̊g�嗦
//******************************************************************************
//�R���X�g���N�^
//******************************************************************************
CScene2D::CScene2D(int nPriority) :CScene(nPriority)
{
	m_pTexture	= NULL;
	m_pVtxBuff	= NULL;
	m_pos		= INIT_D3DXVECTOR3;
	m_size		= INIT_D3DXVECTOR3;
	m_rot		= INIT_D3DXVECTOR3;
	m_color		= INIT_COLOR;
	m_fAngle	= INIT_FLOAT;
	m_fLength	= INIT_FLOAT;
	m_fScale	= INIT_FLOAT;
}

//******************************************************************************
//�f�X�g���N�^
//******************************************************************************
CScene2D::~CScene2D()
{

}

//******************************************************************************
//����������
//******************************************************************************
HRESULT CScene2D::Init(void)
{
	// �g�嗦��1.0f��
	m_fScale = DEFAULT_SCALE;

	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX * MAX_POLYGON,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_pVtxBuff,				// ���_�o�b�t�@�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	// ���_����ݒ�
	VERTEX_2D *pVtx = NULL;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = m_pos.x - cosf(m_fAngle - m_rot.z) * m_fLength *m_fScale;
	pVtx[0].pos.y = m_pos.y - sinf(m_fAngle - m_rot.z) * m_fLength *m_fScale;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + cosf(m_fAngle + m_rot.z) * m_fLength *m_fScale;
	pVtx[1].pos.y = m_pos.y - sinf(m_fAngle + m_rot.z) * m_fLength *m_fScale;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x - cosf(m_fAngle + m_rot.z) * m_fLength *m_fScale;
	pVtx[2].pos.y = m_pos.y + sinf(m_fAngle + m_rot.z) * m_fLength *m_fScale;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + cosf(m_fAngle - m_rot.z) * m_fLength *m_fScale;
	pVtx[3].pos.y = m_pos.y + sinf(m_fAngle - m_rot.z) * m_fLength *m_fScale;
	pVtx[3].pos.z = 0.0f;

	//rhw
	pVtx[0].rhw = RHW_VALUE;
	pVtx[1].rhw = RHW_VALUE;
	pVtx[2].rhw = RHW_VALUE;
	pVtx[3].rhw = RHW_VALUE;
	//���_�J���[�̐ݒ� �������̂��

	pVtx[0].col = m_color;
	pVtx[1].col = m_color;
	pVtx[2].col = m_color;
	pVtx[3].col = m_color;

	//�e�N�X�`��
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//******************************************************************************
// �|���S���̏I������
//******************************************************************************
void CScene2D::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	// �j��
	Release();
}

//******************************************************************************
// �|���S���̍X�V����
//******************************************************************************
void CScene2D::Update(void)
{
	// ���_����ݒ�
	VERTEX_2D *pVtx;
	//�p�x�擾
	m_fAngle = atan2f((m_size.y / 2), (m_size.x / 2));

	//���a�擾
	m_fLength = sqrtf((float)(((m_size.x / 2) * (m_size.x / 2)) + ((m_size.y / 2) * (m_size.y / 2))));

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = m_pos.x - cosf(m_fAngle - m_rot.z) * m_fLength *m_fScale;
	pVtx[0].pos.y = m_pos.y - sinf(m_fAngle - m_rot.z) * m_fLength *m_fScale;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + cosf(m_fAngle + m_rot.z) * m_fLength *m_fScale;
	pVtx[1].pos.y = m_pos.y - sinf(m_fAngle + m_rot.z) * m_fLength *m_fScale;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x - cosf(m_fAngle + m_rot.z) * m_fLength *m_fScale;
	pVtx[2].pos.y = m_pos.y + sinf(m_fAngle + m_rot.z) * m_fLength *m_fScale;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + cosf(m_fAngle - m_rot.z) * m_fLength *m_fScale;
	pVtx[3].pos.y = m_pos.y + sinf(m_fAngle - m_rot.z) * m_fLength *m_fScale;
	pVtx[3].pos.z = 0.0f;

	//rhw
	pVtx[0].rhw = RHW_VALUE;
	pVtx[1].rhw = RHW_VALUE;
	pVtx[2].rhw = RHW_VALUE;
	pVtx[3].rhw = RHW_VALUE;

	//���_�J���[�̐ݒ� 
	pVtx[0].col = m_color;
	pVtx[1].col = m_color;
	pVtx[2].col = m_color;
	pVtx[3].col = m_color;

	//�e�N�X�`��
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
	//�ʒu���W�ݒ�
	SetPosition(m_pos);
}

//******************************************************************************
// �|���S���̕`�揈��
//******************************************************************************
void CScene2D::Draw(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//******************************************************************************
//�e�N�X�`���̐ݒ�
//******************************************************************************
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//******************************************************************************
//�A���t�@�l�̐ݒ�
//******************************************************************************
void CScene2D::SetColor(D3DXCOLOR color)
{
	m_color = color;
}

//******************************************************************************
//�����ݒ�
//******************************************************************************
void CScene2D::SetRotation(D3DXVECTOR3 rot)
{
	m_rot = rot;
}//******************************************************************************
// �g�嗦�ݒ�
//******************************************************************************
void CScene2D::SetScale(float fScale)
{
	m_fScale = fScale;
}
//******************************************************************************
// ���ݒ�
//******************************************************************************
void CScene2D::SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR color)
{
	m_pos = pos;
	m_rot = rot;
	m_size = size;
	m_color = color;
}
//******************************************************************************
// �ʒu���W�ݒ�
//******************************************************************************
void CScene2D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//******************************************************************************
// �T�C�Y�ݒ�
//******************************************************************************
void CScene2D::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}
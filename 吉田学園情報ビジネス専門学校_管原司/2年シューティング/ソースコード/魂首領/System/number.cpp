//******************************************************************************
// �i���o�[���� [number.cpp]
// Author : �ǌ��@�i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
#include "renderer.h"
#include "number.h"
#include "scene.h"
#include "scene2d.h"
#include "manager.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define TEXTURE_X		(0.10f)	// �e�N�X�`��X�l
#define TEXTURE_Y		(0.0f)	// �e�N�X�`��Y�l
#define TEXTURE_Y2		(1.0f)	// �e�N�X�`��Y�l
#define DEVIDE_VALUE	(2)		// ����l
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CNumber::CNumber()
{
	m_pVtxBuff	= NULL;
	m_pos		= INIT_D3DXVECTOR3;
	m_size		= INIT_D3DXVECTOR3;
	m_nNumber	= INIT_INT;
	m_col		= INIT_COLOR;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CNumber::~CNumber()
{

}
//******************************************************************************
// �e�N�X�`���ǂݍ���
//******************************************************************************
HRESULT CNumber::Load(void)
{
	//�����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/UI/number000.png", &m_pTexture);
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���j��
//******************************************************************************
void CNumber::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		//�e�N�X�`�������[�X
		m_pTexture->Release();
		//m_pTexture��NULL��
		m_pTexture = NULL;
	}
}
//******************************************************************************
// �����֐�
//******************************************************************************
CNumber * CNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col)
{
	// CNumber�̃|�C���^
	CNumber * pNumber;

	// �������m��
	pNumber = new CNumber;

	// �ʒu���W�ݒ�
	pNumber->SetPosition(pos);

	// �T�C�Y�ݒ�
	pNumber->SetSize(size);

	// �J���[�ݒ�
	pNumber->SetColor(col);

	//������
	pNumber->Init();

	// pNumber��Ԃ�
	return pNumber;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CNumber::Init(void)
{
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-m_size.x/ DEVIDE_VALUE), m_pos.y + (-m_size.y / DEVIDE_VALUE), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / DEVIDE_VALUE), m_pos.y + (-m_size.y / DEVIDE_VALUE), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-m_size.x / DEVIDE_VALUE), m_pos.y + (m_size.y / DEVIDE_VALUE), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / DEVIDE_VALUE), m_pos.y + (m_size.y / DEVIDE_VALUE), 0.0f);

	// rhw
	pVtx[0].rhw = RHW_VALUE;
	pVtx[1].rhw = RHW_VALUE;
	pVtx[2].rhw = RHW_VALUE;
	pVtx[3].rhw = RHW_VALUE;

	// ���_�J���[�̐ݒ� �������̂��
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// �e�N�X�`��
	pVtx[0].tex = D3DXVECTOR2(m_nNumber * TEXTURE_X, TEXTURE_Y);
	pVtx[1].tex = D3DXVECTOR2(m_nNumber * TEXTURE_X + TEXTURE_X, TEXTURE_Y);
	pVtx[2].tex = D3DXVECTOR2(m_nNumber * TEXTURE_X, TEXTURE_Y2);
	pVtx[3].tex = D3DXVECTOR2(m_nNumber * TEXTURE_X + TEXTURE_X, TEXTURE_Y2);

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
	return S_OK;
}
//******************************************************************************
//�I���֐�
//******************************************************************************
void CNumber::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		// m_pVtxBuff�����[�X
		m_pVtxBuff->Release();
		// m_pVtxBuff��NULL
		m_pVtxBuff = NULL;
	}
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CNumber::Update(void)
{
	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-m_size.x / DEVIDE_VALUE), m_pos.y + (-m_size.y / DEVIDE_VALUE), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / DEVIDE_VALUE), m_pos.y + (-m_size.y / DEVIDE_VALUE), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-m_size.x / DEVIDE_VALUE), m_pos.y + (m_size.y / DEVIDE_VALUE), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / DEVIDE_VALUE), m_pos.y + (m_size.y / DEVIDE_VALUE), 0.0f);

	// rhw
	pVtx[0].rhw = RHW_VALUE;
	pVtx[1].rhw = RHW_VALUE;
	pVtx[2].rhw = RHW_VALUE;
	pVtx[3].rhw = RHW_VALUE;

	// ���_�J���[�̐ݒ� �������̂��
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// �e�N�X�`��
	pVtx[0].tex = D3DXVECTOR2(m_nNumber * TEXTURE_X, TEXTURE_Y);
	pVtx[1].tex = D3DXVECTOR2(m_nNumber * TEXTURE_X + TEXTURE_X, TEXTURE_Y);
	pVtx[2].tex = D3DXVECTOR2(m_nNumber * TEXTURE_X, TEXTURE_Y2);
	pVtx[3].tex = D3DXVECTOR2(m_nNumber * TEXTURE_X + TEXTURE_X, TEXTURE_Y2);

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CNumber::Draw(void)
{
	//�����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);
}
//******************************************************************************
// �i���o�[�ݒ�
//******************************************************************************
void CNumber::SetNumber(int nNumber)
{
	// nNumber���
	m_nNumber = nNumber;

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`��
	pVtx[0].tex = D3DXVECTOR2(m_nNumber * TEXTURE_X, TEXTURE_Y);
	pVtx[1].tex = D3DXVECTOR2(m_nNumber * TEXTURE_X + TEXTURE_X, TEXTURE_Y);
	pVtx[2].tex = D3DXVECTOR2(m_nNumber * TEXTURE_X, TEXTURE_Y2);
	pVtx[3].tex = D3DXVECTOR2(m_nNumber * TEXTURE_X + TEXTURE_X, TEXTURE_Y2);

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}
//******************************************************************************
// �ʒu���W�ݒ�
//******************************************************************************
void CNumber::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//******************************************************************************
// �T�C�Y�ݒ�
//******************************************************************************
void CNumber::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}
//******************************************************************************
// �F�ݒ�
//******************************************************************************
void CNumber::SetColor(D3DXCOLOR col)
{
	m_col = col;
}
//******************************************************************************
// �Q�[�W [gage.cpp]
// Author : �ǌ��i
//******************************************************************************
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "manager.h"
#include "renderer.h"
#include "gage.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define DEFAULLT_COL	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// �W���̐F
#define TEX_VALUE		(1.0f)								// �e�N�X�`���l
#define DEVIDE_VALUE	(2)									// ����l
#define POS_Z			(0.0f)								// Z�̒l
#define SUB_GAGE		(1)									// �Q�[�W�̒l�������l
#define MUT_GAGE		(1.03f)								// �Q�[�W�Ɋ|����l
#define GAGE_MUT		(1.0f)								// �|����l
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CGage::CGage(int nPriority) : CScene(nPriority)
{
	m_pTexture		= NULL;
	m_pVtxBuff		= NULL;
	m_pos			= INIT_D3DXVECTOR3;
	m_size			= INIT_D3DXVECTOR3;
	m_color			= INIT_COLOR;
	m_nGageNum		= INIT_INT;
	m_fMaxGageNum	= INIT_FLOAT;
	m_fGageNum		= INIT_FLOAT;
	m_fTex_X		= INIT_FLOAT;
	m_fTex_X2		= INIT_FLOAT;
	m_fTex_Y		= INIT_FLOAT;
	m_fTex_Y2		= INIT_FLOAT;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CGage::~CGage()
{
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CGage::Init(void)
{
	// �e�N�X�`�����W��1.0f�ɐݒ�
	m_fTex_X2 = TEX_VALUE;
	m_fTex_Y2 = TEX_VALUE;

	// float�ɕϊ�
	m_fMaxGageNum = m_nGageNum * GAGE_MUT;

	// �Q�[�W�̒l�Z�o
	m_fGageNum = m_nGageNum / m_fMaxGageNum;

	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX * MAX_POLYGON,// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,																// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,																	// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,																// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_pVtxBuff,																	// ���_�o�b�t�@�ւ̃|�C���^
		NULL)))																			// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	// ���_����ݒ�
	VERTEX_2D *pVtx = NULL;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �ʒu�ƃT�C�Y
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-m_size.x / DEVIDE_VALUE), m_pos.y + (m_size.y / DEVIDE_VALUE), POS_Z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / DEVIDE_VALUE) - (m_size.x) * (SUB_GAGE - m_fGageNum), m_pos.y + (m_size.y / DEVIDE_VALUE), POS_Z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-m_size.x / DEVIDE_VALUE), m_pos.y + (-m_size.y / DEVIDE_VALUE), POS_Z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / DEVIDE_VALUE) - (m_size.x) * (SUB_GAGE - m_fGageNum), m_pos.y + (-m_size.y / DEVIDE_VALUE), POS_Z);

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

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(m_fTex_X, m_fTex_Y);
	pVtx[1].tex = D3DXVECTOR2(m_fTex_X2, m_fTex_Y);
	pVtx[2].tex = D3DXVECTOR2(m_fTex_X, m_fTex_Y2);
	pVtx[3].tex = D3DXVECTOR2(m_fTex_X2, m_fTex_Y2);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CGage::Uninit(void)
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
// �X�V�֐�
//******************************************************************************
void CGage::Update(void)
{
	// ���_����ݒ�
	VERTEX_2D *pVtx = NULL;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �ʒu�ƃT�C�Y
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-m_size.x / DEVIDE_VALUE), m_pos.y + (m_size.y / DEVIDE_VALUE), POS_Z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / DEVIDE_VALUE) - (m_size.x) * (SUB_GAGE - m_fGageNum), m_pos.y + (m_size.y / DEVIDE_VALUE), POS_Z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-m_size.x / DEVIDE_VALUE), m_pos.y + (-m_size.y / DEVIDE_VALUE), POS_Z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / DEVIDE_VALUE) - (m_size.x) * (SUB_GAGE - m_fGageNum), m_pos.y + (-m_size.y / DEVIDE_VALUE), POS_Z);

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

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(m_fTex_X, m_fTex_Y);
	pVtx[1].tex = D3DXVECTOR2(m_fTex_X2, m_fTex_Y);
	pVtx[2].tex = D3DXVECTOR2(m_fTex_X, m_fTex_Y2);
	pVtx[3].tex = D3DXVECTOR2(m_fTex_X2, m_fTex_Y2);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	// �Q�[�W�̒l�Z�o
	m_fGageNum = m_nGageNum / m_fMaxGageNum;

	//�ʒu���W�ݒ�
	SetPosition(m_pos);
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CGage::Draw(void)
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
// �e�N�X�`���󂯓n��
//******************************************************************************
void CGage::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
//******************************************************************************
// �e�N�X�`��UV���W�ݒ�
//******************************************************************************
void CGage::SetTexture(float tex_x, float tex_x2, float tex_y, float tex_y2)
{
	m_fTex_X	= tex_x;
	m_fTex_X2	= tex_x2;
	m_fTex_Y	= tex_y;
	m_fTex_Y2	= tex_y2;
}
//******************************************************************************
// �ʒu�ݒ�֐�
//******************************************************************************
void CGage::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//******************************************************************************
// �T�C�Y�ݒ�֐�
//******************************************************************************
void CGage::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}
//******************************************************************************
// �F�ݒ�֐�
//******************************************************************************
void CGage::SetColor(D3DXCOLOR color)
{
	m_color = color;
}
//******************************************************************************
// �Q�[�W�����ݒ�֐�
//******************************************************************************
void CGage::SetGageNum(int nGageNum)
{
	m_nGageNum = nGageNum;
}
//******************************************************************************
// ���ݒ�֐�
//******************************************************************************
void CGage::SetGage(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color, int nGageNum)
{
	// �ʒu
	m_pos = pos;

	// �T�C�Y
	m_size = size;

	// �F
	m_color = color;

	// �Q�[�W�̒l
	m_nGageNum = nGageNum;
}
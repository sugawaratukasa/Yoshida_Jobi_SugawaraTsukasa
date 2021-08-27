//******************************************************************************
// �r�[���̃x�[�X [beam_base.cpp]
// Author : �ǌ��@�i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "../System/main.h"
#include "../System/renderer.h"
#include "../System/scene.h"
#include "beam_base.h"
#include "../System/manager.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define SCALE_VALUE			(1.0f)		// �g�嗦�l
#define TEXTURE_ANIM_VALUE	(1.0f)		// �e�N�X�`���l
#define DEVIDE_VALUE		(2.0f)		// ���Z�l
#define ADD_SIZE_VALUE		(30.0f)		// �T�C�Y���Z��
#define ADD_TEX_VALUE		(0.1f)		// �e�N�X�`�����Z��
#define MAX_TEX_Y			(1.0f)		// Y�e�N�X�`���̍ő�l
#define MIN_TEX_Y			(0.0f)		// Y�e�N�X�`���̍ő�l
#define MAX_ANIM_TEX_Y		(2.0f)		// Y�e�N�X�`���̍ő�l
#define MIN_ANIM_TEX_Y		(1.0f)		// Y�e�N�X�`���̍ő�l
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CBeam_Base::CBeam_Base(int nPriority) : CScene(nPriority)
{
	m_pTexture		= NULL;
	m_pVtxBuff		= NULL;
	m_pos			= INIT_D3DXVECTOR3;
	m_rot			= INIT_D3DXVECTOR3;
	m_size			= INIT_D3DXVECTOR3;
	m_col			= INIT_COLOR;
	m_fAddSize		= INIT_FLOAT;
	m_fTexX			= INIT_FLOAT;
	m_fTexY			= INIT_FLOAT;
	m_fTexAnimX		= INIT_FLOAT;
	m_fTexAnimY		= INIT_FLOAT;
	m_bAddSize_Stop = false;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CBeam_Base::~CBeam_Base()
{
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CBeam_Base::Init()
{
	// �e�N�X�`���̒l���
	m_fTexAnimX = TEXTURE_ANIM_VALUE;
	m_fTexAnimY = TEXTURE_ANIM_VALUE;

	// �T�C�YY���
	m_fSizeY = m_size.y;

	//�����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//���_����ݒ�
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �ꏊ�̐ݒ�
	pVtx[0].pos = m_pos + D3DXVECTOR3((-m_size.x / DEVIDE_VALUE), (-m_fSizeY / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE)) ;
	pVtx[1].pos = m_pos + D3DXVECTOR3((m_size.x / DEVIDE_VALUE), (-m_fSizeY / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE)) ;
	pVtx[2].pos = m_pos + D3DXVECTOR3((-m_size.x / DEVIDE_VALUE), (m_size.y / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE));
	pVtx[3].pos = m_pos + D3DXVECTOR3((m_size.x / DEVIDE_VALUE), (m_size.y / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE));

	pVtx[0].rhw = RHW_VALUE;
	pVtx[1].rhw = RHW_VALUE;
	pVtx[2].rhw = RHW_VALUE;
	pVtx[3].rhw = RHW_VALUE;

	// ���_�J���[
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// �e�N�X�`��
	pVtx[0].tex = D3DXVECTOR2(m_fTexX, m_fTexY);
	pVtx[1].tex = D3DXVECTOR2(m_fTexX + m_fTexAnimX, m_fTexY);
	pVtx[2].tex = D3DXVECTOR2(m_fTexX, m_fTexAnimY);
	pVtx[3].tex = D3DXVECTOR2(m_fTexX + m_fTexAnimX, m_fTexAnimY);

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CBeam_Base::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		// �j��
		m_pVtxBuff->Release();

		// NULL��
		m_pVtxBuff = NULL;
	}
	// �j��
	Release();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CBeam_Base::Update(void)
{
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �ꏊ�̐ݒ�
	pVtx[0].pos = m_pos + D3DXVECTOR3((-m_size.x / DEVIDE_VALUE), (-m_fSizeY / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE));
	pVtx[1].pos = m_pos + D3DXVECTOR3((m_size.x / DEVIDE_VALUE), (-m_fSizeY / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE));
	pVtx[2].pos = m_pos + D3DXVECTOR3((-m_size.x / DEVIDE_VALUE), (m_size.y / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE));
	pVtx[3].pos = m_pos + D3DXVECTOR3((m_size.x / DEVIDE_VALUE), (m_size.y / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE));

	pVtx[0].rhw = RHW_VALUE;
	pVtx[1].rhw = RHW_VALUE;
	pVtx[2].rhw = RHW_VALUE;
	pVtx[3].rhw = RHW_VALUE;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// �e�N�X�`��
	pVtx[0].tex = D3DXVECTOR2(m_fTexX, m_fTexY);
	pVtx[1].tex = D3DXVECTOR2(m_fTexX + m_fTexAnimX, m_fTexY);
	pVtx[2].tex = D3DXVECTOR2(m_fTexX, m_fTexAnimY);
	pVtx[3].tex = D3DXVECTOR2(m_fTexX + m_fTexAnimX, m_fTexAnimY);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
	// ��ʊO�ɏo���ꍇ
	if (m_pos.y + -m_fSizeY / 2 >= WINDOW_POS_Y)
	{
		// ���Z�ʑ��
		m_fAddSize = ADD_SIZE_VALUE;

		// �T�C�Y���Z
		m_fSizeY += m_fAddSize;
	}

	// �e�N�X�`�����Z
	m_fTexY += ADD_TEX_VALUE;
	m_fTexAnimY += ADD_TEX_VALUE;

	// 1.0f�ȏ�̏ꍇ
	if (m_fTexY >= MAX_TEX_Y)
	{
		// 0.0f��
		m_fTexY = MIN_TEX_Y;
	}
	// 2.0f�ȏ�̏ꍇ
	if (m_fTexAnimY >= MAX_ANIM_TEX_Y)
	{
		// 1.0f��
		m_fTexAnimY = MIN_ANIM_TEX_Y;
	}
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CBeam_Base::Draw(void)
{
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	 
	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(NULL, m_pVtxBuff, NULL, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(NULL, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);
}
//******************************************************************************
// ���ݒ�
//******************************************************************************
void CBeam_Base::SetBeam(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col)
{
	m_pos = pos;
	m_size = size;
	m_col = col;
}
//******************************************************************************
// �ʒu���W�ݒ�֐�
//******************************************************************************
void CBeam_Base::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//******************************************************************************
// UV���W�ݒ�֐�
//******************************************************************************
void CBeam_Base::SetTexture(float fTexX, float fTexY, float fTexAnimX, float fTexAnimY)
{
	m_fTexX = fTexX;
	m_fTexY = fTexY;
	m_fTexAnimX = fTexAnimX;
	m_fTexAnimY = fTexAnimY;
}
//******************************************************************************
// �J���[�ݒ�֐�
//******************************************************************************
void CBeam_Base::SetRGBA(D3DXCOLOR col)
{
	m_col = col;
}
//******************************************************************************
// �����ݒ�֐�
//******************************************************************************
void CBeam_Base::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//******************************************************************************
// �T�C�Y�ݒ�
//******************************************************************************
void CBeam_Base::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}
//******************************************************************************
// �T�C�Y�ݒ�
//******************************************************************************
void CBeam_Base::SetSizeY(float sizeY)
{
	m_fSizeY = sizeY;
}
//******************************************************************************
// �e�N�X�`�����蓖�Ċ֐�
//******************************************************************************
void CBeam_Base::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

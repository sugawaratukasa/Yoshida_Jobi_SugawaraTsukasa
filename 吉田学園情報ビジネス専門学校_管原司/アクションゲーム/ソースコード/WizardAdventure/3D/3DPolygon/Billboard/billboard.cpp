//******************************************************************************
// �r���{�[�h[billboard.cpp]
// Author : �ǌ��@�i
//******************************************************************************
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "camera.h"
#include "billboard.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define NOR				(D3DXVECTOR3(1, 1, -1))	// �@��
#define SCALE_VALUE		(1.0f)					// �g�嗦
#define DEVIDE_VALUE	(2)						// ���鐔
#define DEFAULT_TEX		(1.0f)					// UV�l
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CBillboard::CBillboard(int nPriority) : CScene(nPriority)
{
	m_pTexture	= NULL;
	m_pVtxBuff	= NULL;
	m_pos		= INIT_D3DXVECTOR3;
	m_rot		= INIT_D3DXVECTOR3;
	m_size		= INIT_D3DXVECTOR3;
	m_col		= INIT_COLOR;
	m_fScale	= INIT_FLOAT;
	m_fTexX		= INIT_FLOAT;
	m_fTexX2	= INIT_FLOAT;
	m_fTexY		= INIT_FLOAT;
	m_fTexY2	= INIT_FLOAT;
	m_nAlpha	= INIT_INT;
	m_bDraw		= true;
	memset(m_mtxWorld, 0, sizeof(m_mtxWorld));
}
//******************************************************************************
//�@�f�X�g���N�^
//******************************************************************************
CBillboard::~CBillboard()
{
}
//******************************************************************************
//�@������
//******************************************************************************
HRESULT CBillboard::Init(void)
{
	// UV�l
	m_fTexX2 = DEFAULT_TEX;
	m_fTexY2 = DEFAULT_TEX;

	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,													// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,														// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,													// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_pVtxBuff,														// ���_�o�b�t�@�ւ̃|�C���^
		NULL)))																// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	// ���_����ݒ�
	VERTEX_3D *pVtx;

	// �X�P�[��1.0f
	m_fScale = SCALE_VALUE;

	// ���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �ꏊ�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3((-m_size.x / DEVIDE_VALUE), (m_size.y / DEVIDE_VALUE), (-m_size.z / DEVIDE_VALUE)) * m_fScale;
	pVtx[1].pos = D3DXVECTOR3((m_size.x / DEVIDE_VALUE), (m_size.y / DEVIDE_VALUE), (-m_size.z / DEVIDE_VALUE)) * m_fScale;
	pVtx[2].pos = D3DXVECTOR3((-m_size.x / DEVIDE_VALUE), (-m_size.y / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE)) * m_fScale;
	pVtx[3].pos = D3DXVECTOR3((m_size.x / DEVIDE_VALUE), (-m_size.y / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE)) * m_fScale;

	// �@���̐ݒ�
	pVtx[0].nor = NOR;
	pVtx[1].nor = NOR;
	pVtx[2].nor = NOR;
	pVtx[3].nor = NOR;

	// �J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(m_fTexX, m_fTexY);
	pVtx[1].tex = D3DXVECTOR2(m_fTexX2, m_fTexY);
	pVtx[2].tex = D3DXVECTOR2(m_fTexX, m_fTexY2);
	pVtx[3].tex = D3DXVECTOR2(m_fTexX2, m_fTexY2);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}
//******************************************************************************
//�@�I��
//******************************************************************************
void CBillboard::Uninit(void)
{
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
//�@�X�V
//******************************************************************************
void CBillboard::Update(void)
{
	// ���_����ݒ�
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �ꏊ�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3((-m_size.x / DEVIDE_VALUE), (m_size.y / DEVIDE_VALUE), (-m_size.z / DEVIDE_VALUE)) * m_fScale;
	pVtx[1].pos = D3DXVECTOR3((m_size.x / DEVIDE_VALUE), (m_size.y / DEVIDE_VALUE), (-m_size.z / DEVIDE_VALUE)) * m_fScale;
	pVtx[2].pos = D3DXVECTOR3((-m_size.x / DEVIDE_VALUE), (-m_size.y / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE)) * m_fScale;
	pVtx[3].pos = D3DXVECTOR3((m_size.x / DEVIDE_VALUE), (-m_size.y / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE)) * m_fScale;

	// �@���̐ݒ�
	pVtx[0].nor = NOR;
	pVtx[1].nor = NOR;
	pVtx[2].nor = NOR;
	pVtx[3].nor = NOR;

	// �J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(m_fTexX, m_fTexY);
	pVtx[1].tex = D3DXVECTOR2(m_fTexX2, m_fTexY);
	pVtx[2].tex = D3DXVECTOR2(m_fTexX, m_fTexY2);
	pVtx[3].tex = D3DXVECTOR2(m_fTexX2, m_fTexY2);

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

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
//�@�`��
//******************************************************************************
void CBillboard::Draw(void)
{
	// true�̏ꍇ
	if (m_bDraw == true)
	{
		// �����_���[�擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
		D3DXMATRIX mtxRot, mtxTrans; //�s��v�Z�p�̃}�g���N�X

		//���C�g����
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		// �A���t�@�e�X�g
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, m_nAlpha);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		// �Z�b�g�e�N�X�`��
		pDevice->SetTexture(0, m_pTexture);

		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// ���[���h�}�g���N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);

		// ��]�̋t�s��
		pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
		D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxRot);
		m_mtxWorld._41 = 0;
		m_mtxWorld._42 = 0;
		m_mtxWorld._43 = 0;

		// �������f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		// �|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		// �A���t�@�e�X�g������
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

		// ���C�g�L��
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}
//******************************************************************************
//�@�ʒu���W�ݒ�
//******************************************************************************
void CBillboard::SetPosition(D3DXVECTOR3 pos)
{
	//���
	m_pos = pos;
}
//******************************************************************************
//�@�����ݒ�
//******************************************************************************
void CBillboard::SetRotation(D3DXVECTOR3 rot)
{
	//���
	m_rot = rot;
}
//******************************************************************************
//�@�T�C�Y�ݒ�
//******************************************************************************
void CBillboard::SetSize(D3DXVECTOR3 size)
{
	//���
	m_size = size;
}
//******************************************************************************
//�@�J���[�ݒ�
//******************************************************************************
void CBillboard::SetColor(D3DXCOLOR col)
{
	//���
	m_col = col;
}
//******************************************************************************
//�@�e�N�X�`���ݒ�
//******************************************************************************
void CBillboard::SetTexture(float fTexX, float fTexY, float fTexX2, float fTexY2)
{
	m_fTexX = fTexX;
	m_fTexY = fTexY;
	m_fTexX2 = fTexX2;
	m_fTexY2 = fTexY2;
}
//******************************************************************************
//�@�g�嗦�ݒ�
//******************************************************************************
void CBillboard::SetScale(float fScale)
{
	//���
	m_fScale = fScale;
}
//******************************************************************************
//�@�e�N�X�`���󂯓n��
//******************************************************************************
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	//���
	m_pTexture = pTexture;
}
//******************************************************************************
// �A���t�@�e�X�g�̐��l�ݒ�
//******************************************************************************
void CBillboard::SetAlpha(int nAlpha)
{
	m_nAlpha = nAlpha;
}
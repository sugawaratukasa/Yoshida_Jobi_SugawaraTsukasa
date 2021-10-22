//******************************************************************************
// 3D�Q�[�W [3d_gage.cpp]
// Author : �ǌ��i
//******************************************************************************

//******************************************************************************
//�C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "3d_gage.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define NOR				(D3DXVECTOR3(0, 1, 0))	// �@��
#define DEVIDE_VALUE	(2.0f)					// ����l
#define TEX_VALUE		(1.0f)					// �e�N�X�`���l
#define ALPHA			(0)						// ���ߒl
#define SUB_GAGE		(1)						// �Q�[�W�̒l�������l
#define GAGE_MUT		(1.0f)					// �|����l
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
C3D_Gage::C3D_Gage(int nPriority) : CScene(nPriority)
{
	m_pTexture		= NULL;
	m_pVtxBuff		= NULL;
	m_pos			= INIT_D3DXVECTOR3;
	m_rot			= INIT_D3DXVECTOR3;
	m_size			= INIT_D3DXVECTOR3;
	m_col			= INIT_COLOR;
	m_nGageNum		= INIT_INT;
	m_fMaxGageNum	= INIT_FLOAT;
	m_fGageNum		= INIT_FLOAT;
	m_fTex_X		= INIT_FLOAT;
	m_fTex_X2		= INIT_FLOAT;
	m_fTex_Y		= INIT_FLOAT;
	m_fTex_Y2		= INIT_FLOAT;
	m_bDraw			= true;
	memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));
}

//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
C3D_Gage::~C3D_Gage()
{
}

//******************************************************************************
// ����������
//******************************************************************************
HRESULT C3D_Gage::Init(void)
{
	// �e�N�X�`�����W��1.0f�ɐݒ�
	m_fTex_X2 = TEX_VALUE;
	m_fTex_Y2 = TEX_VALUE;

	// float�ɕϊ�
	m_fMaxGageNum = m_nGageNum * GAGE_MUT;

	// �Q�[�W�̒l�Z�o
	m_fGageNum = m_nGageNum / m_fMaxGageNum;

	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_POLYGON,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,																	// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,																		// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,																	// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_pVtxBuff,																		// ���_�o�b�t�@�ւ̃|�C���^
		NULL)))																				// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	// ���_����ݒ�
	VERTEX_3D *pVtx = NULL;

	// ���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �ʒu�ƃT�C�Y
	pVtx[0].pos = D3DXVECTOR3((-m_size.x / DEVIDE_VALUE),(m_size.y / DEVIDE_VALUE), m_size.z);
	pVtx[1].pos = D3DXVECTOR3((m_size.x / DEVIDE_VALUE) - (m_size.x) * (SUB_GAGE - m_fGageNum),(m_size.y / DEVIDE_VALUE), m_size.z);
	pVtx[2].pos = D3DXVECTOR3((-m_size.x / DEVIDE_VALUE), (-m_size.y / DEVIDE_VALUE), m_size.z);
	pVtx[3].pos = D3DXVECTOR3((m_size.x / DEVIDE_VALUE) - (m_size.x) * (SUB_GAGE - m_fGageNum),(-m_size.y / DEVIDE_VALUE), m_size.z);

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
	pVtx[0].tex = D3DXVECTOR2(m_fTex_X, m_fTex_Y);
	pVtx[1].tex = D3DXVECTOR2(m_fTex_X2, m_fTex_Y);
	pVtx[2].tex = D3DXVECTOR2(m_fTex_X, m_fTex_Y2);
	pVtx[3].tex = D3DXVECTOR2(m_fTex_X2, m_fTex_Y2);

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//******************************************************************************
// �I������
//******************************************************************************
void C3D_Gage::Uninit(void)
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
// �X�V����
//******************************************************************************
void C3D_Gage::Update(void)
{
	// �J�����̈ʒu�擾
	D3DXVECTOR3 CameraPos = CManager::GetCamera()->GetPos();

	// ���_����ݒ�
	VERTEX_3D *pVtx = NULL;

	// ���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �ʒu�ƃT�C�Y
	pVtx[0].pos = D3DXVECTOR3((-m_size.x / DEVIDE_VALUE), (m_size.y / DEVIDE_VALUE), m_size.z);
	pVtx[1].pos = D3DXVECTOR3((m_size.x / DEVIDE_VALUE) - (m_size.x) * (SUB_GAGE - m_fGageNum), (m_size.y / DEVIDE_VALUE), m_size.z);
	pVtx[2].pos = D3DXVECTOR3((-m_size.x / DEVIDE_VALUE), (-m_size.y / DEVIDE_VALUE), m_size.z);
	pVtx[3].pos = D3DXVECTOR3((m_size.x / DEVIDE_VALUE) - (m_size.x) * (SUB_GAGE - m_fGageNum), (-m_size.y / DEVIDE_VALUE), m_size.z);

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
	pVtx[0].tex = D3DXVECTOR2(m_fTex_X, m_fTex_Y);
	pVtx[1].tex = D3DXVECTOR2(m_fTex_X2, m_fTex_Y);
	pVtx[2].tex = D3DXVECTOR2(m_fTex_X, m_fTex_Y2);
	pVtx[3].tex = D3DXVECTOR2(m_fTex_X2, m_fTex_Y2);

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	// �Q�[�W�̒l�Z�o
	m_fGageNum = m_nGageNum / m_fMaxGageNum;

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
void C3D_Gage::Draw(void)
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
		pDevice->SetRenderState(D3DRS_ALPHAREF, ALPHA);
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
// �ꏊ
//******************************************************************************
void C3D_Gage::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//******************************************************************************
// �p�x
//******************************************************************************
void C3D_Gage::SetRotation(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//******************************************************************************
// �T�C�Y
//******************************************************************************
void C3D_Gage::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}
//******************************************************************************
// �F�ݒ�
//******************************************************************************
void C3D_Gage::SetColor(D3DXCOLOR col)
{
	m_col = col;
}
//******************************************************************************
// �e�N�X�`��UV���W�ݒ�
//******************************************************************************
void C3D_Gage::SetTexture(float tex_x, float tex_x2, float tex_y, float tex_y2)
{
	m_fTex_X = tex_x;
	m_fTex_X2 = tex_x2;
	m_fTex_Y = tex_y;
	m_fTex_Y2 = tex_y2;
}
//******************************************************************************
// �e�N�X�`��
//******************************************************************************
void C3D_Gage::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
//******************************************************************************
// ���ݒ�
//******************************************************************************
void C3D_Gage::SetGage(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, int nGageNum)
{
	// �ʒu���W�ݒ�
	m_pos = pos;

	// �����ݒ�
	m_rot = rot;

	// �T�C�Y�ݒ�
	m_size = size;

	// �F�ݒ�
	m_col = col;

	// �Q�[�W�̒l�ݒ�
	m_nGageNum = nGageNum;
}
//******************************************************************************
// �Q�[�W�̒l�ݒ�
//******************************************************************************
void C3D_Gage::SetGageNum(int nGageNum)
{
	m_nGageNum = nGageNum;
}
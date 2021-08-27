//******************************************************************************
// Scene2d�̏��� [scene2d.cpp]
// Author : �ǌ��@�i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "manager.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define SCALE_VALUE			(1.0f)								// �g�嗦�l
#define TEXTURE_ANIM_VALUE	(1.0f)								// �e�N�X�`���l
#define DEVIDE_VALUE		(2)									// ���Z�l
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CScene2d::CScene2d(int nPriority) : CScene(nPriority)
{
	m_pTexture	= NULL;
	m_pVtxBuff	= NULL;
	m_pos		= INIT_D3DXVECTOR3;
	m_rot		= INIT_D3DXVECTOR3;
	m_size		= INIT_D3DXVECTOR3;
	m_col		= INIT_COLOR;
	m_fAngle	= INIT_FLOAT;
	m_fLength	= INIT_FLOAT;
	m_fTexX		= INIT_FLOAT;
	m_fTexY		= INIT_FLOAT;
	m_fTexAnimX = INIT_FLOAT;
	m_fTexAnimY = INIT_FLOAT;
	m_fScale	= INIT_FLOAT;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CScene2d::~CScene2d()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CScene2d * CScene2d::Create()
{
	// CScene2d�N���X�|�C���^
	CScene2d * pScene2D;

	// �������m��
	pScene2D = new CScene2d;

	// ������
	pScene2D->Init();

	// �|�C���^��Ԃ�
	return pScene2D;

}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CScene2d::Init()
{

	m_fTexAnimX = TEXTURE_ANIM_VALUE;
	m_fTexAnimY = TEXTURE_ANIM_VALUE;

	// �p�x�v�Z
	m_fAngle = atan2f((m_size.y / DEVIDE_VALUE), (m_size.x / DEVIDE_VALUE));

	// ���a�v�Z
	m_fLength = sqrtf((float)(((m_size.x / DEVIDE_VALUE) * (m_size.x / DEVIDE_VALUE)) + ((m_size.y / DEVIDE_VALUE) * (m_size.y / DEVIDE_VALUE))));

	// �g�嗦��1.0f�ɐݒ�
	m_fScale = SCALE_VALUE;

	//�����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//���_����ݒ�
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �ʒu���W
	pVtx[0].pos.x = m_pos.x - cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	pVtx[0].pos.y = m_pos.y - sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	pVtx[1].pos.y = m_pos.y - sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x - cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	pVtx[2].pos.y = m_pos.y + sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	pVtx[3].pos.y = m_pos.y + sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	pVtx[3].pos.z = 0.0f;

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
void CScene2d::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	// �����[�X
	Release();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CScene2d::Update(void)
{ 
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	// ���_����ݒ�
	VERTEX_2D *pVtx;
	// ���_�o�b�t�@�����b�N
 	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �ʒu���W
	pVtx[0].pos.x = m_pos.x - cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	pVtx[0].pos.y = m_pos.y - sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	pVtx[1].pos.y = m_pos.y - sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x - cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	pVtx[2].pos.y = m_pos.y + sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	pVtx[3].pos.y = m_pos.y + sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	pVtx[3].pos.z = 0.0f;

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
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CScene2d::Draw(void)
{
	// �����_���[�擾
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
// �ʒu���W�ݒ�֐�
//******************************************************************************
void CScene2d::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//******************************************************************************
// UV���W�ݒ�֐�
//******************************************************************************
void CScene2d::SetTexture(float fTexX, float fTexY, float fTexAnimX ,float fTexAnimY)
{
	m_fTexX = fTexX;
	m_fTexY = fTexY;
	m_fTexAnimX = fTexAnimX;
	m_fTexAnimY = fTexAnimY;
}
//******************************************************************************
// �J���[�ݒ�֐�
//******************************************************************************
void CScene2d::SetRGBA(D3DXCOLOR col)
{
	m_col = col;
}
//******************************************************************************
// �����ݒ�֐�
//******************************************************************************
void CScene2d::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//******************************************************************************
// �T�C�Y�ݒ�
//******************************************************************************
void CScene2d::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}
//******************************************************************************
// �g�嗦�ݒ�֐�
//******************************************************************************
void CScene2d::SetScale(float fScale)
{
	m_fScale = fScale;
}
//******************************************************************************
// �e�N�X�`�����蓖�Ċ֐�
//******************************************************************************
void CScene2d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

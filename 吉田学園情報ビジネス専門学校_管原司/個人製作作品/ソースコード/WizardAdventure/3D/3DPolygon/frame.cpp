//******************************************************************************
// �t���[��[frame.cpp]
// Author : �ǌ��i
//******************************************************************************
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "keyboard.h"
#include "scene.h"
#include "scene3d.h"
#include "../3D/Model/Block/block.h"
#include "frame.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define MOVE_VALUE	(D3DXVECTOR3(2.0f, 2.0f, 0.0f))
#define POS			(D3DXVECTOR3(pos.x,pos.y,pos.z - 15.0f))
#define FRAME_ROT1	(D3DXVECTOR3(0.0f,D3DXToRadian(0.0f),0.0f))
#define FRAME_ROT2	(D3DXVECTOR3(0.0f,D3DXToRadian(90.0f),0.0f))
#define FRAME_ROT3	(D3DXVECTOR3(0.0f,D3DXToRadian(270.0f),0.0f))
#define FRAME_ROT4	(D3DXVECTOR3(D3DXToRadian(90.0f),0.0f,0.0f))
#define MAX_FRAME	(2)
#define RADIUS		(15.0f)
//******************************************************************************
// �ÓI�����o�ϐ�������
//******************************************************************************
LPDIRECT3DTEXTURE9 CFrame::m_pTexture = NULL;
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CFrame::CFrame(int nPriority) : CScene3d(nPriority)
{
	m_pBlock = NULL;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CFrame::~CFrame()
{
}
//******************************************************************************
// �e�N�X�`���ǂݍ��݊֐�
//******************************************************************************
HRESULT CFrame::Load(void)
{
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/frame.png", &m_pTexture);
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���j���֐�
//******************************************************************************
void CFrame::Unload(void)
{
	// NULL�`�F�b�N
	if (m_pTexture != NULL)
	{
		// �j��
		m_pTexture->Release();

		// NULL
		m_pTexture = NULL;
	}
}
//******************************************************************************
// �����֐�
//******************************************************************************
CFrame * CFrame::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, CBlock *pBlock)
{
	// CPolygon�̃|�C���^
	CFrame *pFrame;

	// �������m��
	pFrame = new CFrame;

	// ���ݒ�
	pFrame->SetPolygon(pos, rot, size, col);

	// �u���b�N�̃|�C���^�ݒ�
	pFrame->m_pBlock = pBlock;

	// �e�N�X�`��
	pFrame->BindTexture(m_pTexture);

	// ������
	pFrame->Init();

	// �|�C���^��Ԃ�
	return pFrame;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CFrame::Init(void)
{
	// ������
	CScene3d::Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CFrame::Uninit(void)
{
	// �I��
	CScene3d::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CFrame::Update(void)
{
	// �X�V
	CScene3d::Update();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = m_pBlock->GetPos();

	// �ʒu���
	pos = POS;

	// �ʒu�X�V
	SetPosition(pos);
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CFrame::Draw(void)
{
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �`��
	CScene3d::Draw();

	// ���ɖ߂�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}
//******************************************************************************
// �I�𒆂̐F�ɐݒ�
//******************************************************************************
void CFrame::SetSelectingColor(D3DXCOLOR col)
{
	SetColor(col);
}
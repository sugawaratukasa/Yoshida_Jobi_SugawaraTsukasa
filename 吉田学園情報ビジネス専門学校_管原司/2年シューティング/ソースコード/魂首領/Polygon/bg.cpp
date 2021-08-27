//******************************************************************************
// �w�i [bg.cpp]
// Author : �ǌ��@�i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "../System/main.h"
#include "../System/manager.h"
#include "../System/renderer.h"
#include "../System/scene.h"
#include "../System/scene2d.h"
#include "bg.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define BG_TEXTURE_1	("data/Texture/BackGround/bg2.png")		// �e�N�X�`��1
#define BG_TEXTURE_2	("data/Texture/BackGround/bg101.png")	// �e�N�X�`��2
#define BG_TEXTURE_3	("data/Texture/BackGround/bg102.png")	// �e�N�X�`��3
#define COLOR_VALUE		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))		// �F
#define TEXTURE_MOVE	(0.005f)								// �ړ���
#define TEXTURE_MOVE2	(0.0005f)								// �ړ��ʂQ
#define MOVE_MAX		(1.0f)									// �ړ��ʍő�l
#define MOVE_MIN		(0.0f)									// �ړ��ʍŏ��l
#define TEX_1			(0.0f)									// �e�N�X�`��1
#define TEX_2			(0.0f)									// �e�N�X�`��2
#define TEX_3			(1.0f)									// �e�N�X�`��3
#define TEX_4			(1.0f)									// �e�N�X�`��4
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPDIRECT3DTEXTURE9 CBg::m_apTexture[TYPE_MAX] = {};
//******************************************************************************
// �e�N�X�`���ǂݍ���
//******************************************************************************
HRESULT CBg::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURE_1, &m_apTexture[TYPE_FARST_BG]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURE_2, &m_apTexture[TYPE_SECOUND_BG]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURE_3, &m_apTexture[TYPE_THIRD_BG]);
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���j��
//******************************************************************************
void CBg::Unload(void)
{
	for (int nCnt = INIT_INT; nCnt < TYPE_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}
//******************************************************************************
// �����֐�
//******************************************************************************
CBg * CBg::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �|�C���^
	CBg * pBg;

	// �������m��
	pBg = new CBg;

	// �ʒu���W���
	pBg->m_pos = pos;

	// �T�C�Y���
	pBg->m_size = size;

	// ������
	pBg->Init();

	// �|�C���^��Ԃ�
	return pBg;
}
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CBg::CBg(int nPriority) : CScene(nPriority)
{
	memset(m_apScene2D, 0, sizeof(m_apScene2D));
	m_type		= TYPE_NONE;
	m_pos		= INIT_D3DXVECTOR3;
	m_size		= INIT_D3DXVECTOR3;
	m_fSlowMove = INIT_FLOAT;
	m_fmove		= INIT_FLOAT;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CBg::~CBg()
{
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CBg::Init(void)
{
	// �������m��
	m_apScene2D[TYPE_FARST_BG] = new CScene2d(OBJTYPE_BG);
	m_apScene2D[TYPE_SECOUND_BG] = new CScene2d(OBJTYPE_BG);
	m_apScene2D[TYPE_THIRD_BG] = new CScene2d(OBJTYPE_BG);

	// �ʒu���W�ݒ�
	m_apScene2D[TYPE_FARST_BG]->SetPosition(m_pos);
	m_apScene2D[TYPE_SECOUND_BG]->SetPosition(m_pos);
	m_apScene2D[TYPE_THIRD_BG]->SetPosition(m_pos);

	// �ʒu���W�ݒ�
	m_apScene2D[TYPE_FARST_BG]->SetSize(m_size);
	m_apScene2D[TYPE_SECOUND_BG]->SetSize(m_size);
	m_apScene2D[TYPE_THIRD_BG]->SetSize(m_size);

	// �J���[�ݒ�
	m_apScene2D[TYPE_FARST_BG]->SetRGBA(COLOR_VALUE);
	m_apScene2D[TYPE_SECOUND_BG]->SetRGBA(COLOR_VALUE);
	m_apScene2D[TYPE_THIRD_BG]->SetRGBA(COLOR_VALUE);

	// �e�N�X�`���̎󂯓n��
	m_apScene2D[TYPE_FARST_BG]->BindTexture(m_apTexture[TYPE_FARST_BG]);
	m_apScene2D[TYPE_SECOUND_BG]->BindTexture(m_apTexture[TYPE_SECOUND_BG]);
	m_apScene2D[TYPE_THIRD_BG]->BindTexture(m_apTexture[TYPE_THIRD_BG]);

	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	m_apScene2D[TYPE_FARST_BG]->SetObjType(CScene::OBJTYPE_BG);
	m_apScene2D[TYPE_SECOUND_BG]->SetObjType(CScene::OBJTYPE_BG);
	m_apScene2D[TYPE_THIRD_BG]->SetObjType(CScene::OBJTYPE_BG);

	// ������
	m_apScene2D[TYPE_FARST_BG]->Init();
	m_apScene2D[TYPE_SECOUND_BG]->Init();
	m_apScene2D[TYPE_THIRD_BG]->Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CBg::Uninit(void)
{
	//�I��
	Release();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CBg::Update(void)
{
	// �X�V
	m_apScene2D[TYPE_FARST_BG]->Update();
	m_apScene2D[TYPE_SECOUND_BG]->Update();
	m_apScene2D[TYPE_THIRD_BG]->Update();

	// ����
	m_fmove += TEXTURE_MOVE;

	// �x��
	m_fSlowMove += TEXTURE_MOVE2;

	// �e�N�X�`���ړ�
	if (m_fmove >= MOVE_MAX)
	{
		m_fmove = MOVE_MIN;
	}
	// �e�N�X�`���ړ�
	if (m_fSlowMove >= MOVE_MAX)
	{
		m_fSlowMove = MOVE_MIN;
	}

	m_apScene2D[TYPE_SECOUND_BG]->SetTexture(TEX_1, TEX_2 + +m_fmove, TEX_3, TEX_4);
	m_apScene2D[TYPE_THIRD_BG]->SetTexture(TEX_1, TEX_2 + +m_fSlowMove, TEX_3, TEX_4);

}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CBg::Draw(void)
{
}
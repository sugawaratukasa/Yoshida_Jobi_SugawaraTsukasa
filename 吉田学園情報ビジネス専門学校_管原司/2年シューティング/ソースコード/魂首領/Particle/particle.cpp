//******************************************************************************
// �p�[�e�B�N������ [particle.cpp]
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
#include "particle.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define PARTICLE_TEXTURE_1	("data/Texture/Effect/particle001.png")	// �p�[�e�B�N���e�N�X�`��1
#define PARTICLE_TEXTURE_2	("data/Texture/Effect/fire002.png")		// �p�[�e�B�N���e�N�X�`��2
#define PARTICLE_TEXTURE_3	("data/Texture/Effect/particle008.png")		// �p�[�e�B�N���e�N�X�`��3
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPDIRECT3DTEXTURE9 CParticle::m_pTexture[TEX_TYPE_MAX] = {};
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CParticle::CParticle(int nPriority) : CScene2d(nPriority)
{
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CParticle::~CParticle()
{
}
//******************************************************************************
// �e�N�X�`���ǂݍ���
//******************************************************************************
HRESULT CParticle::Load(void)
{
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

	// �e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, PARTICLE_TEXTURE_1, &m_pTexture[TEX_TYPE_CIRCLE]);
	D3DXCreateTextureFromFile(pDevice, PARTICLE_TEXTURE_2, &m_pTexture[TEX_TYPE_EXPLOSION]);
	D3DXCreateTextureFromFile(pDevice, PARTICLE_TEXTURE_3, &m_pTexture[TEX_TYPE_FLASH]);
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���j��
//******************************************************************************
void CParticle::Unload(void)
{
	// 3��J��Ԃ�
	for (int nCnt = INIT_INT; nCnt < TEX_TYPE_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			// �e�N�X�`��Release
			m_pTexture[nCnt]->Release();

			// m_pTexture��NULL��
			m_pTexture[nCnt] = NULL;
		}
	}
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CParticle::Init(void)
{
	// ������
	CScene2d::Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CParticle::Uninit(void)
{
	// �I��
	CScene2d::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CParticle::Update(void)
{
	// �X�V
	CScene2d::Update();
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CParticle::Draw(void)
{
	// �`��
	CScene2d::Draw();
}
//******************************************************************************
// ���ݒ�֐�
//******************************************************************************
void CParticle::SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, TEX_TYPE TexType)
{
	// �ʒu���W�ݒ�
	SetPosition(pos);

	// �T�C�Y�ݒ�
	SetSize(size);

	// �����ݒ�
	SetRot(rot);

	// �J���[�ݒ�
	SetRGBA(col);

	// �e�N�X�`���^�C�v
	m_TexType = TexType;

	// �e�N�X�`���󂯓n��
	BindTexture(m_pTexture[m_TexType]);
}
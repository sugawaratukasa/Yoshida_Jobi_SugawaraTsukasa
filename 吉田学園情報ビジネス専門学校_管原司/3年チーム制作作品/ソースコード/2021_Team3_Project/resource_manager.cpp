//=============================================================================
//
// ���\�[�X�}�l�[�W���[���� [resource_manager.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "resource_manager.h"
#include "texture.h"
#include "xfile.h"
#include "sound.h"
#include "particle_texture.h"
//=============================================================================
// static�������錾
//=============================================================================
CResourceManager *CResourceManager::m_pResourceManager = nullptr;	// ���g�̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResourceManager::CResourceManager()
{
	m_pTexture = nullptr;	// �e�N�X�`���̃|�C���^
	m_pXFile = nullptr;		// X�t�@�C���̃|�C���^
	m_pSound = nullptr;		// �T�E���h�̃|�C���^
	m_pParticle_Texture = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResourceManager::~CResourceManager()
{
	// �A�����[�h����
	UnLoadAll();
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CResourceManager::Init(void)
{
	// nullcheck
	if (m_pTexture == nullptr)
	{
		// �e�N�X�`���̃C���X�^���X����
		m_pTexture = CTexture::Create();
	}

	// nullcheck
	if (m_pXFile == nullptr)
	{
		// X�t�@�C���̃C���X�^���X����
		m_pXFile = CXfile::Create();
	}

	// nullcheck
	if (m_pSound == nullptr)
	{
		// �T�E���h�̃C���X�^���X����
		m_pSound = CSound::Create();
	}

	// nullcheck
	if (m_pParticle_Texture == nullptr)
	{
		// �T�E���h�̃C���X�^���X����
		m_pParticle_Texture = new CParticle_Texture;
	}

	return S_OK;
}

//=============================================================================
// ���[�h����
//=============================================================================
void CResourceManager::LoadAll(void)
{
	// !nullcheck
	if (m_pTexture != nullptr)
	{
		// �e�N�X�`�����[�h
		m_pTexture->LoadAll();
	}

	// !nullcheck
	if (m_pXFile != nullptr)
	{
		// ���f�����[�h
		m_pXFile->LoadAll();
	}

	// !nullcheck
	if (m_pParticle_Texture != nullptr)
	{
		// ������
		m_pParticle_Texture->Init();
	}
}

//=============================================================================
// �A�����[�h����
//=============================================================================
void CResourceManager::UnLoadAll(void)
{
	// !nullcheck
	if (m_pTexture != nullptr)
	{
		// �e�N�X�`���̃A�����[�h
		m_pTexture->UnLoadAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	// !nullcheck
	if (m_pXFile != nullptr)
	{
		// �e�N�X�`���A�����[�h
		m_pXFile->UnLoadAll();
		delete m_pXFile;
		m_pXFile = nullptr;
	}

	// nullcheck
	if (m_pSound != nullptr)
	{
		// �I������
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}
	// !nullcheck
	if (m_pParticle_Texture != nullptr)
	{
		// �I������
		m_pParticle_Texture->Uninit();
		delete m_pParticle_Texture;
		m_pParticle_Texture = nullptr;
	}
}

//=============================================================================
// �C���X�^���X�擾�֐�
//=============================================================================
CResourceManager * CResourceManager::GetInstance(void)
{
	// nullcheck
	if (m_pResourceManager == nullptr)
	{
		// �������m��
		m_pResourceManager = new CResourceManager;

		// !nullcheck
		if (m_pResourceManager != nullptr)
		{
			// ����������
			m_pResourceManager->Init();
		}
	}

	return m_pResourceManager;
}
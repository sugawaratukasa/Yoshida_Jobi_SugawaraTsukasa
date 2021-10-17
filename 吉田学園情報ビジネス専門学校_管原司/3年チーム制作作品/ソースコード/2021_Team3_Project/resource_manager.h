#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_
//=============================================================================
//
// ���\�[�X�}�l�[�W���[���� [resource_manager.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �O���錾
//=============================================================================
class CTexture;
class CXfile;
class CSound;
class CParticle_Texture;

//=============================================================================
// ���\�[�X�}�l�[�W���[�N���X
//=============================================================================
class CResourceManager
{
public:
	~CResourceManager();									// �f�X�g���N�^

	HRESULT Init(void);										// ����������
	void LoadAll(void);										// �S�Ẵ��[�h����
	void UnLoadAll(void);									// �S�ẴA�����[�h

	static CResourceManager *GetInstance(void);				// �C���X�^���X�擾�֐�

	// Get�֐�
	CTexture *GetTextureClass(void) { return m_pTexture; }	// �e�N�X�`���̏��
	CXfile *GetXfileClass(void)		{ return m_pXFile; }	// �e�N�X�`���̏��
	CSound *GetSoundClass(void)		{ return m_pSound; }	// �T�E���h�̏��
	CParticle_Texture *GetParticle_Texture(void) { return m_pParticle_Texture; }	// �p�[�e�B�N���e�N�X�`���̏��
private:
	CResourceManager();								// �R���X�g���N�^
	static CResourceManager *m_pResourceManager;	// ���g�̃|�C���^
	CTexture *m_pTexture;							// �e�N�X�`���̃|�C���^
	CXfile *m_pXFile;								// X�t�@�C���̃|�C���^
	CSound *m_pSound;								// �T�E���h�̃|�C���^
	CParticle_Texture *m_pParticle_Texture;			// �p�[�e�B�N���e�N�X�`���̃|�C���^
};

#endif
//***********************************************************************************
//	UI�e�N�X�`��	[UI_texture.h]
//	Author : �ǌ� �i
//***********************************************************************************
#ifndef _UI_TEXTURE_H_
#define _UI_TEXTURE_H_
//***********************************************************************************
// �C���N���[�h�t�@�C��
//***********************************************************************************
//***********************************************************************************
// �}�N����`
//***********************************************************************************
#include "main.h"
//***********************************************************************************
// �N���X
//***********************************************************************************
class CUI_Texture
{
public:
	enum TEX_TYPE
	{
		TEX_TYPE_LIFE_GAGE = 0,
		TEX_TYPE_RESUME,
		TEX_TYPE_CONTROLS,
		TEX_TYPE_EXIT,
		TEX_TYPE_GAMESTART,
		TEX_TYPE_TITLE,
		TEX_TYPE_TITLE_BG,
		TEX_TYPE_PRESS_START,
		TEX_TYPE_RESULT,
		TEX_TYPE_MAGIC_UI,
		TEX_TYPE_CONTROLS_BG
	};
	CUI_Texture();
	~CUI_Texture();
	HRESULT Init(void);
	void Uninit(void);
	LPDIRECT3DTEXTURE9 GetTexture(int TexNum);
	int GetTexNum(void) { return m_nNumTex; }
private:
	void Load(void);
	LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`��
	LPDIRECT3DTEXTURE9 *m_pLoadTexture;	// �ǂݍ��ݗp�e�N�X�`��
	int m_nNumTex;						// �e�N�X�`����
};
#endif
//******************************************************************************
// �t�F�[�h [fade.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _FADE_H_
#define _FADE_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "polygon.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define FADE_POS	(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 ,0.0f))	// �t�F�[�h�ʒu���W
#define FADE_SIZE	(D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f))				// �T�C�Y
//******************************************************************************
// �O���錾
//******************************************************************************
class CSceneManager;
//******************************************************************************
// �N���X
//******************************************************************************
class CFade : public CPolygon 
{
public:
	// �t�F�[�h�񋓌^
	typedef enum
	{
		FADE_NONE = -1,
		FADE_IN,
		FADE_OUT,
		FADE_MAX
	}FADE;

	CFade(int nPriority = CScene::OBJTYPE_FADE);
	~CFade();
	static CFade * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CSceneManager::MODE mode);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	FADE m_fade;							// �t�F�[�h
	CSceneManager::MODE m_ModeNext;			// ���[�h
};
#endif
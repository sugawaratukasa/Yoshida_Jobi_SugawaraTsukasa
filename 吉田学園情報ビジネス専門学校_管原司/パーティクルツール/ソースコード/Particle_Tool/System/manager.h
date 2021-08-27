//******************************************************************************
//	�}�l�[�W���[[manager.h]
//	Author : �ǌ��i
//******************************************************************************
#ifndef _MANAGER_H_
#define _MANAGER_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
//******************************************************************************
//�O���錾
//******************************************************************************
class CRenderer;
class CCamera;
class CLight;
class CInputKeyboard;
class CDebugProc;
class CMode;
class CTexture;
//******************************************************************************
//�N���X
//******************************************************************************
class CManager
{
public:
	typedef enum
	{
		MODE_NONE = 0,
		MODE_TOOL,
		MODE_MAX
	}MODE;
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindouw);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void LoadAll(void);
	void UnloadAll(void);
	static void CreateCamera(void);
	void SetNumFPS(int nCountFPS) { m_nCountFPS = nCountFPS; }
	void SetMode(MODE mode);

	static CRenderer *GetRenderer(void) { return m_pRenderer; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CTexture *GetTexture(void) { return m_pTexture; }
private:
	static CRenderer *m_pRenderer;			//�����_���[
	static CCamera *m_pCamera;				//�J����
	static CMode *m_pMode;					// ���[�h
	static CTexture *m_pTexture;			// �e�N�X�`��
	int m_nCountFPS;						// FPS�̒l
	MODE m_Mode;							// ���[�h
};
#endif // !_MANAGER_H_

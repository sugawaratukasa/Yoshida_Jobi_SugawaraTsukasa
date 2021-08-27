//******************************************************************************
// manager [manager.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _MANAGER_H_
#define _MANAGER_H_
//******************************************************************************
// �O���錾
//******************************************************************************
class CRenderer;
class CInputKeyboard;
class CInputJoystick;
class CSound;
class CMode;
class CFade;
class CTutrial;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSceneManager
{
public:
	//���[�h�̗񋓌^
	typedef enum
	{
		MODE_NONE = -1,
		MODE_TITLE,
		MODE_TUTRIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_END
	}MODE;

	CSceneManager();
	~CSceneManager();
	HRESULT Init(HINSTANCE hInsitance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetMode(MODE mode);
	static MODE GetMode(void) { return m_mode; }
	static CRenderer * GetRenderer(void) { return m_pRenderer; }
	static CInputKeyboard * GetInputKeyboard(void) { return m_pInputKeyboard; }
	static CInputJoystick * GetInputJoystick(void) { return m_pInputJoystick; }
	static CSound * GetSound(void) { return m_pSound; }

	//static void CreateFade(MODE mode);
	void LoadAll(void);
	void UnloadAll(void);
private:
	static MODE m_mode;							// ���[�h 
	static CMode *m_pMode;						// ���[�h���
	static CRenderer * m_pRenderer;				// �����_���[���
	static CInputKeyboard * m_pInputKeyboard;	// �L�[�{�[�h���
	static CInputJoystick * m_pInputJoystick;	// �W���C�X�e�B�b�N�̏��
	static CSound * m_pSound;					// �T�E���h�̏��
};
#endif
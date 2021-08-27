//******************************************************************************
// �L�[�{�[�h���� [inputkeyboard.j]
// Author : �ǌ� �i
//******************************************************************************
#ifndef _INPUT_KEYBOARD_H_
#define _INPUT_KEYBOARD_H_

//******************************************************************************
// �N���X
//******************************************************************************
class CInputKeyboard :public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetKeyboardPress(int nKey);
	bool GetKeyboardTrigger(int nKey);
	bool GetKeyboardRelease(int nKey);
private:
	BYTE m_aKeyState[NUM_KEY_MAX];		  //�L�[�{�[�h�̓��͏�񃏁[�N
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX]; //�L�[�{�[�h�̃g���K�[���
	BYTE m_aKeyStateRelease[NUM_KEY_MAX]; //�L�[�{�[�h�̃����[�X���
};
#endif
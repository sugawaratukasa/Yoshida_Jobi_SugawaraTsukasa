//******************************************************************************
// �L�[�{�[�h����[keyboard.h]
// Author : �ǌ��i
//******************************************************************************
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
#include "input.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define NUM_KEY_MAX (256)//�L�[�{�[�h�̍ő吔
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
	bool GetKeyPress(int nKey);
	bool GetKeyTrigger(int nKey);
	bool GetKeyRelease(int nKey);
private:
	BYTE m_akeyState[NUM_KEY_MAX];			// �L�[�{�[�h�̓��͏�񃏁[�N
	BYTE m_akeyStateTrigger[NUM_KEY_MAX];	// �L�[�{�[�h�̓��͏�񃏁[�N
	BYTE m_akeyStateRelease[NUM_KEY_MAX];	// �L�[�{�[�h�̓��͏�񃏁[�N
};

#endif
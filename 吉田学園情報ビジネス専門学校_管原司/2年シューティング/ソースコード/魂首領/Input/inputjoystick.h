//******************************************************************************
// �R���g���[���[���� [inputjoystick.h]
// Author : �ǌ� �i
//******************************************************************************
#ifndef _INPUT_JOYSTICK_H_
#define _INPUT_JOYSTICK_H_
#define INITGUID
//******************************************************************************
// �}�N����`
//******************************************************************************
#define	NUM_JS_MAX (256)
//******************************************************************************
// �N���X
//******************************************************************************
class CInputJoystick : public CInput
{
public:
	// �{�^���̗�
	typedef enum
	{
		JS_NONE = -1,
		JS_X,
		JS_Y,
		JS_A,
		JS_B,
		JS_MAX
	}JS;

	CInputJoystick();
	~CInputJoystick();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetJoystickPress(int nKey);
	bool GetJoystickTrigger(int nKey);
	bool GetJoystickRelease(int nKey);
	static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext);
	static BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext);
	static LPDIRECTINPUTDEVICE8 GetDevice(void) { return m_pJDevice; }
private:
	static LPDIRECTINPUTDEVICE8 m_pJDevice;
	DIDEVCAPS	m_diDevCaps;					//Caps
	BYTE m_aJoyState[NUM_JS_MAX];				// �L�[�{�[�h�̓��͏�񃏁[�N
	BYTE m_aJoyStateTrigger[NUM_JS_MAX];		//�L�[�{�[�h�g���K�[���
	BYTE m_aJoyStateRelease[NUM_JS_MAX];		// �L�[�{�[�h�̃����[�X���
};
#endif
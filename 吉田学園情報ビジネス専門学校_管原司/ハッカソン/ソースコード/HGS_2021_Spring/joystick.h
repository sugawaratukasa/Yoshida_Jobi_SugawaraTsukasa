//=============================================================================
//
// �W���C�X�e�B�b�N���� [joystick.h]
// Author : ��K������
//
//=============================================================================
#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define JS_X	   (0)
#define JS_Y	   (1)
#define JS_A	   (2)
#define JS_B	   (3)
#define JS_LB	   (4)
#define JS_RB	   (5)
#define JS_LT	   (6)
#define JS_RT	   (7)
#define JS_LP	   (8)
#define JS_RP	   (9)
#define JS_BACK	   (10)
#define JS_START   (11)
#define JS_HOME    (12)
#define	NUM_JS_MAX (256)

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CJoystick : public CInput
{
public:
	CJoystick();
	~CJoystick();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetJoystickPress(int nKey);
	bool GetJoystickTrigger(int nKey);
	bool GetJoystickRelease(int nKey);
	BOOL CreateEffect(HWND);
	static BOOL CALLBACK EnumFFDevicesCallback(const DIDEVICEINSTANCE * pdidInstance, VOID * pContext);
	static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext);
	static BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext);
	static LPDIRECTINPUTDEVICE8 GetDevice(void) { return m_pJDevice; }
	static LPDIRECTINPUTEFFECT GetEffect(void) { return m_IpDIEffect; }
private:
	static LPDIRECTINPUTDEVICE8 m_pJDevice;		//�f�o�C�X
	static LPDIRECTINPUTEFFECT m_IpDIEffect;	//�G�t�F�N�g
	DIDEVCAPS	m_diDevCaps;					//Caps
	DWORD m_dwNumForceFeedbackAxis;				//�t�H�[�X�t�B�[�h�o�b�N
	DWORD m_rgdwAxes[2] = { DIJOFS_X , DIJOFS_Y };
	LONG  m_rglDirection[2] = { 1 , 1 };
	DICONSTANTFORCE cf;
	DIEFFECT        eff;
	BYTE m_aJoyState[NUM_JS_MAX];				// �W���C�X�e�B�b�N�̓��͏�񃏁[�N
	BYTE m_aJoyStateTrigger[NUM_JS_MAX];		//�W���C�X�e�B�b�N�g���K�[���
	BYTE m_aJoyStateRelease[NUM_JS_MAX];		// �W���C�X�e�B�b�N�����[�X���
};
#endif
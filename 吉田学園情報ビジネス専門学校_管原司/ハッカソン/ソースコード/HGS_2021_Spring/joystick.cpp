//=============================================================================
//
// �W���C�X�e�B�b�N���� [joystick.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "input.h"
#include "joystick.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECTINPUTDEVICE8 CJoystick::m_pJDevice = NULL;
LPDIRECTINPUTEFFECT CJoystick::m_IpDIEffect = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CJoystick::CJoystick()
{
	memset(m_aJoyState, 0, sizeof(m_aJoyState));
	memset(m_aJoyStateTrigger, 0, sizeof(m_aJoyStateTrigger));
	memset(m_aJoyStateRelease, 0, sizeof(m_aJoyStateRelease));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CJoystick::~CJoystick()
{
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CJoystick::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT  hr;

	hr = CInput::Init(hInstance, hWnd);

	hr = m_pDinput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL, DIEDFL_FORCEFEEDBACK | DIEDFL_ATTACHEDONLY);

	if (m_pJDevice != NULL)
	{
		if (FAILED(hr)) {
			MessageBox(hWnd, "Can't create Device.", "Error", MB_OK);
			return FALSE;
		}

		hr = m_pJDevice->SetDataFormat(&c_dfDIJoystick);
		if (FAILED(hr)) {
			MessageBox(hWnd, "Can't set data format.", "Error", MB_OK);
			return FALSE;
		}

		hr = m_pJDevice->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
		if (FAILED(hr)) {
			MessageBox(hWnd, "Can't set cooperative level.", "Error", MB_OK);
			return FALSE;
		}

		m_diDevCaps.dwSize = sizeof(DIDEVCAPS);
		hr = m_pJDevice->GetCapabilities(&m_diDevCaps);
		if (FAILED(hr)) {
			MessageBox(hWnd, "Can't create device capabilities.", "Error", MB_OK);
			return FALSE;
		}

		hr = m_pJDevice->EnumObjects(EnumAxesCallback, (VOID*)&m_dwNumForceFeedbackAxis, DIDFT_AXIS);
		if (FAILED(hr)) {
			MessageBox(hWnd, "Can't set property.", "Error", MB_OK);
			return FALSE;
		}

		if (m_dwNumForceFeedbackAxis > 2)
		{
			m_dwNumForceFeedbackAxis = 2;
		}

		if (!CreateEffect(hWnd)) {
			MessageBox(hWnd, "Can't create effect.", "Error", MB_OK);
			return FALSE;
		}

		hr = m_pJDevice->Poll();
		if (FAILED(hr)) {
			hr = m_pJDevice->Acquire();
			while (hr == DIERR_INPUTLOST) {
				hr = m_pJDevice->Acquire();
			}
		}
	}
	return TRUE;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CJoystick::Uninit(void)
{
	CInput::Uninit();
	if (m_pJDevice != NULL)
	{
		//�f�o�C�X����̒�~
		m_pJDevice->Unacquire();
		m_IpDIEffect->Release();
		m_pJDevice->Release();
		m_pJDevice = NULL;
	}
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CJoystick::Update(void)
{
	int nCntKey;
	DIJOYSTATE js;

	if (m_pJDevice != NULL)
	{
		m_pJDevice->Poll();
		m_pJDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
		//�f�o�C�X����f�[�^���擾
		if (SUCCEEDED(m_pJDevice->GetDeviceState(sizeof(DIJOYSTATE), &js)))
		{
			for (nCntKey = 0; nCntKey < NUM_JS_MAX; nCntKey++)
			{
				//�L�[�v���X����ۑ�
				m_aJoyState[nCntKey] = m_aJoyState[nCntKey];

				//�L�[�g���K�[
				m_aJoyStateTrigger[nCntKey] = (m_aJoyState[nCntKey] ^ js.rgbButtons[nCntKey]) &  js.rgbButtons[nCntKey];

				//�L�[�����[�X
				m_aJoyStateRelease[nCntKey] = (m_aJoyState[nCntKey] ^ js.rgbButtons[nCntKey]) & ~js.rgbButtons[nCntKey];

				//�L�[�v���X����ۑ�
				m_aJoyState[nCntKey] = js.rgbButtons[nCntKey];
			}
		}
		else
		{
			m_pJDevice->Acquire();
		}
	}
}

//=============================================================================
// PRESS
//=============================================================================
bool CJoystick::GetJoystickPress(int nKey)
{
	return m_aJoyState[nKey] & 0x80 ? true : false;
}

//=============================================================================
// TRIGGER
//=============================================================================
bool CJoystick::GetJoystickTrigger(int nKey)
{
	return m_aJoyStateTrigger[nKey] & 0x80 ? true : false;
}

//=============================================================================
//    Force Feedback Callback.
//=============================================================================
BOOL CJoystick::EnumFFDevicesCallback(const DIDEVICEINSTANCE * pdidInstance, VOID * pContext)
{
	HRESULT hr;

	hr = m_pDinput->CreateDevice(pdidInstance->guidInstance, &m_pJDevice, NULL);
	if (FAILED(hr)) return DIENUM_CONTINUE;

	return DIENUM_STOP;
}

//=============================================================================
//EnumJoysticksCallback
//=============================================================================
BOOL CALLBACK CJoystick::EnumJoysticksCallback(const DIDEVICEINSTANCE * pdidInstance, VOID * pContext)
{
	HRESULT hr;

	hr = m_pDinput->CreateDevice(pdidInstance->guidInstance, &m_pJDevice, NULL);

	if (FAILED(hr)) return DIENUM_CONTINUE;

	return DIENUM_STOP;
}

//=============================================================================
// RELEASE
//=============================================================================
bool CJoystick::GetJoystickRelease(int nKey)
{
	return m_aJoyStateRelease[nKey] & 0x80 ? true : false;
}

//=============================================================================
// EnumAxesCallback
//=============================================================================
BOOL CALLBACK CJoystick::EnumAxesCallback(const DIDEVICEOBJECTINSTANCE * pdidoi, VOID * pContext)
{
	HRESULT     hr;
	DIPROPRANGE diprg;

	diprg.diph.dwSize = sizeof(DIPROPRANGE);
	diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	diprg.diph.dwHow = DIPH_BYID;
	diprg.diph.dwObj = pdidoi->dwType;
	diprg.lMin = 0 - 1000;
	diprg.lMax = 0 + 1000;
	hr = m_pJDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

	if (FAILED(hr)) return DIENUM_STOP;

	DWORD *pdwNumForceFeedbackAxis = (DWORD*)pContext;
	if ((pdidoi->dwFlags & DIDOI_FFACTUATOR) != 0) (*pdwNumForceFeedbackAxis)++;

	return DIENUM_CONTINUE;
}

//=============================================================================
// Create Effect.
//=============================================================================
BOOL CJoystick::CreateEffect(HWND hWnd)
{
	DWORD           rgdwAxes[2] = { DIJOFS_X , DIJOFS_Y };
	LONG            rglDirection[2] = { 1 , 1 };
	DICONSTANTFORCE cf;
	DIEFFECT        eff;
	HRESULT         hr;

	ZeroMemory(&eff, sizeof(eff));
	eff.dwSize = sizeof(DIEFFECT);
	eff.dwFlags = DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS;
	eff.dwDuration = INFINITE;
	eff.dwSamplePeriod = 0;
	eff.dwGain = DI_FFNOMINALMAX;
	eff.dwTriggerButton = DIEB_NOTRIGGER;
	eff.dwTriggerRepeatInterval = 0;
	eff.cAxes = m_dwNumForceFeedbackAxis;
	eff.rgdwAxes = rgdwAxes;
	eff.rglDirection = rglDirection;
	eff.lpEnvelope = 0;
	eff.cbTypeSpecificParams = sizeof(DICONSTANTFORCE);
	eff.lpvTypeSpecificParams = &cf;
	eff.dwStartDelay = 0;

	hr = m_pJDevice->CreateEffect(GUID_ConstantForce, &eff,
		&m_IpDIEffect, NULL);

	if (FAILED(hr)) {
		MessageBox(hWnd, "Can't create effect.", "Error", MB_OK);
		return FALSE;
	}

	return TRUE;
}
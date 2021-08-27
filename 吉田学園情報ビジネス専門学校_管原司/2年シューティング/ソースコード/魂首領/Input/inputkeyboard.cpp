//******************************************************************************
// �L�[�{�[�h���� [inputkeyboard.cpp]
// Author : �ǌ� �i
//******************************************************************************

//******************************************************************************
// �t�@�C���̃C���N���[�h�t�@�C��
//******************************************************************************
#include "../System/main.h"
#include "input.h"
#include "inputkeyboard.h"

//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CInputKeyboard::CInputKeyboard()
{
	memset(m_aKeyState, 0, sizeof(m_aKeyState));
	memset(m_aKeyStateTrigger, 0, sizeof(m_aKeyStateTrigger));
	memset(m_aKeyStateRelease, 0, sizeof(m_aKeyStateRelease));
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CInputKeyboard::~CInputKeyboard()
{
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	if (FAILED(m_pDInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	m_pDevice->Acquire();
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CInputKeyboard::Uninit(void)
{
	// �I��
	CInput::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;

	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyState[nCntKey] = m_aKeyState[nCntKey]; //�L�[�v���X���ۑ�
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & ~aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}
//******************************************************************************
// ����������
//******************************************************************************
bool CInputKeyboard::GetKeyboardPress(int nKey)
{
	return m_aKeyState[nKey] & 0x80 ? true : false;
}
//******************************************************************************
// �g���K�[����
//******************************************************************************
bool CInputKeyboard::GetKeyboardTrigger(int nKey)
{
	return m_aKeyStateTrigger[nKey] & 0x80 ? true : false;
}
//******************************************************************************
// �����[�X����
//******************************************************************************
bool CInputKeyboard::GetKeyboardRelease(int nKey)
{
	return m_aKeyStateRelease[nKey] & 0x80 ? true : false;
}

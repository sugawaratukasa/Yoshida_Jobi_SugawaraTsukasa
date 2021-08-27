//=============================================================================
//
// �L�[�{�[�h���� [keyboard.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "keyboard.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CKeyboard::CKeyboard()
{
	memset(m_aKeyState, 0, sizeof(m_aKeyState));
	memset(m_aKeyStateRelease, 0, sizeof(m_aKeyStateRelease));
	memset(m_aKeyStateTrigger, 0, sizeof(m_aKeyStateTrigger));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CKeyboard::~CKeyboard()
{
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	if (FAILED(m_pDinput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
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

//=============================================================================
// �I�������֐�
//=============================================================================
void CKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];

	int nCntKey;

	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			//g_aKeyState[nCntKey] = aKeyState[nCntKey]; //�L�[�v���X���ۑ�
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}

bool CKeyboard::GetKeyboardPress(int nKey)
{
	return m_aKeyState[nKey] & 0x80 ? true : false;
}

bool CKeyboard::GetKeyboardTrigger(int nKey)
{
	return m_aKeyStateTrigger[nKey] & 0x80 ? true : false;
}

bool CKeyboard::GetKeyboardRelease(int nKey)
{
	return m_aKeyStateRelease[nKey] & 0x80 ? true : false;
}

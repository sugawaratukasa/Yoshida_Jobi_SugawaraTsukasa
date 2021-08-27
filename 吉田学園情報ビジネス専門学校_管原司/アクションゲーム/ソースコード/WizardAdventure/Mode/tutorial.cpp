//******************************************************************************
// �`���[�g���A�� [tutorial.cpp]
// Author : �ǌ��i
//******************************************************************************

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "scene.h"
#include "renderer.h"
#include "joystick.h"
#include "2d_polygon.h"
#include "fade.h"
#include "map.h"
#include "../3D/3DPolygon/Particle/Particle_Emitter/particle_emitter.h"
#include "../3D/3DPolygon/BG/bg.h"
#include "../3D/Model/player.h"
#include "sound.h"
#include "tutorial_pause.h"
#include "tutorial.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_POS			(D3DXVECTOR3(100.0f, -50.0f, -200.0f))						// �ʒu
#define PLAYER_ROT			(D3DXVECTOR3(0.0f,D3DXToRadian(90.0f),0.0f))				// ����
#define PLAYER_SIZE			(D3DXVECTOR3(30.0f,15.0f,30.0f))							// �T�C�Y
#define PRESS_START_POS		(D3DXVECTOR3(SCREEN_WIDTH / 2, 900.0f, 0.0f))				// �ʒu
#define PRESS_START_SIZE	(D3DXVECTOR3(750.0f, 300.0f, 0.0f))							// �T�C�Y
//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CTutorial::CTutorial()
{
	m_bPause = false;
}
//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CTutorial::~CTutorial()
{
}
//*****************************************************************************
//����������
//*****************************************************************************
HRESULT CTutorial::Init(void)
{
	//�T�E���h�擾
	CSound * pSound = CManager::GetSound();

	// �^�C�g��BGM�Đ�
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_TITLE);

	// �J����
	CManager::CreateCamera();

	// ���C�g
	CManager::CreateLight();

	// �}�b�v����
	CMap::Create(CMap::TYPE_TUTORIAL);

	// �v���C���[����
	CPlayer::Create(PLAYER_POS, PLAYER_ROT, PLAYER_SIZE);

	// �w�i����
	CBg::Create();
	
	// PRESS_START
	C2D_Polygon::Create(PRESS_START_POS, PRESS_START_SIZE, C2D_Polygon::TYPE_PRESS_START);
	return S_OK;
}

//*****************************************************************************
//�I������
//*****************************************************************************
void CTutorial::Uninit(void)
{
	//�T�E���h�̒�~
	CManager::GetSound()->StopSound();

	// �t�F�[�h�ȊO�j��
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}

//*****************************************************************************
//�X�V����
//*****************************************************************************
void CTutorial::Update(void)
{
	//�T�E���h�擾
	CSound * pSound = CManager::GetSound();

	// �R���g���[���[�擾
	DIJOYSTATE js;
	js.lY = INIT_INT;
	js.lX = INIT_INT;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();
	// NULL�łȂ��ꍇ
	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	// NULL�łȂ��ꍇ
	if (g_lpDIDevice != NULL)
	{
		// START�{�^�����������ꍇ
		if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_START) || pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_A))
		{
			// false�̏ꍇ
			if (m_bPause == false)
			{
				// START�{�^�����������ꍇ
				if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_START))
				{
					// ���艹�Đ�
					pSound->PlaySound(CSound::SOUND_LABEL_SE_DETERMINATION);

					// �|�[�Y����
					CTutorial_Pause::Create();

					// true��
					m_bPause = true;
				}
			}
		}
	}
}

//*****************************************************************************
//�`�揈��
//*****************************************************************************
void CTutorial::Draw(void)
{

}
//*****************************************************************************
// �|�[�Y�̎g�p�ݒ�
//*****************************************************************************
void CTutorial::SetPause(bool bPause)
{
	m_bPause = bPause;
}
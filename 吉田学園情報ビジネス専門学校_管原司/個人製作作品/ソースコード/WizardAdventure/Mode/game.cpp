//******************************************************************************
// �c�[�� [game.cpp]
// Author : �ǌ��@
//******************************************************************************

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "renderer.h"
#include "time.h"
#include "mode.h"
#include "camera.h"
#include "light.h"
#include "scene.h"
#include "game.h"
#include "debug_proc.h"
#include "../3D/Model/player.h"
#include "map.h"
#include "../3D/3DPolygon/Particle/Particle_Emitter/particle_emitter.h"
#include "../3D/3DPolygon/BG/bg.h"
#include "sound.h"
#include "pause.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_POS		(D3DXVECTOR3(100.0f, -50.0f, -200.0f))
#define PLAYER_ROT		(D3DXVECTOR3(0.0f,D3DXToRadian(90.0f),0.0f))
#define PLAYER_SIZE		(D3DXVECTOR3(30.0f,15.0f,30.0f))
#define ENEMY_POS		(D3DXVECTOR3(-100.0f,-45.0f,-200.0f))
#define ENEMY_POS2		(D3DXVECTOR3(0.0f,-45.0f,-200.0f))
#define TEST_POS		(D3DXVECTOR3(-150.0f, -70.0f, -200.0f))
#define TEST_ROT		(D3DXVECTOR3(0.0f,0.0,0.0))
#define TEST_SIZE		(D3DXVECTOR3(30.0f,30.0f, 30.0f))
#define TEST_COLOR		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
#define TEST_POS2		(D3DXVECTOR3(-50.0f, -50.0f, -200.0f))
#define TEST_ROT2		(D3DXVECTOR3(0.0f,0.0,0.0f))
#define TEST_SIZE2		(D3DXVECTOR3(30.0f, 30.0f, 30.0f))
#define TEST_POS3		(D3DXVECTOR3(-100.0f, -50.0f, -200.0f))
#define TEST_ROT3		(D3DXVECTOR3(0.0f,0.0,0.0f))
#define TEST_SIZE3		(D3DXVECTOR3(30.0f, 30.0f, 30.0f))
#define TEST_COLOR2		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
#define POS				(D3DXVECTOR3(-30.0f, 0.0f, -200.0f))
#define ROT				(D3DXVECTOR3(0.0f,90.0f,0.0f))
#define SIZE			(D3DXVECTOR3(30.0f, 30.0f, 30.0f))
#define COLOR			(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))
#define CREATE_COUNT	(60)
//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CGame::CGame()
{
	m_nCount = INIT_INT;
	m_bPause = false;
}
//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CGame::~CGame()
{
}
//*****************************************************************************
//����������
//*****************************************************************************
HRESULT CGame::Init(void)
{
	//�T�E���h�擾
	CSound * pSound = CManager::GetSound();

	// �Q�[��BGM�Đ�
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_GAME);

	// �J����
	CManager::CreateCamera();

	// ���C�g
	CManager::CreateLight();

	// �}�b�v����
	CMap::Create(CMap::TYPE_GAME);

	// �v���C���[����
	CPlayer::Create(PLAYER_POS, PLAYER_ROT, PLAYER_SIZE);

	// �G�t�F�N�g����
	CParticle_Emitter::Create(PLAYER_POS, CParticle_Emitter::TYPE_MAP);

	// �w�i����
	CBg::Create();

	return S_OK;
}

//*****************************************************************************
//�I������
//*****************************************************************************
void CGame::Uninit(void)
{
	//�T�E���h�̒�~
	CManager::GetSound()->StopSound();

	// �t�F�[�h�ȊO�j��
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}

//*****************************************************************************
//�X�V����
//*****************************************************************************
void CGame::Update(void)
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
		// false�̏ꍇ
		if (m_bPause == false)
		{
			// START�{�^�����������ꍇ
			if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_START))
			{
				// �^�C�g��BGM�Đ�
				pSound->PlaySound(CSound::SOUND_LABEL_SE_DETERMINATION);

				// �|�[�Y����
				CPause::Create();

				// true��
				m_bPause = true;
			}
		}
	}
}

//*****************************************************************************
//�`�揈��
//*****************************************************************************
void CGame::Draw(void)
{

}
//*****************************************************************************
// �|�[�Y�ݒ�
//*****************************************************************************
void CGame::SetPause(bool bPause)
{
	m_bPause = bPause;
}

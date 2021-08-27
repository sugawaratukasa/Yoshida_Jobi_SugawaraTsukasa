//******************************************************************************
// �^�C�g�� [title.cpp]
// Author : �ǌ��i
//******************************************************************************

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "joystick.h"
#include "2d_polygon.h"
#include "fade.h"
#include "../2D/2D_Particle/2d_particle_emitter.h"
#include "sound.h"
#include "title.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BG_POS				(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))	// �ʒu
#define BG_SIZE				(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f))			// �T�C�Y
#define TITLE_POS			(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3, 0.0f))	// �ʒu
#define TITLE_SIZE			(D3DXVECTOR3(1500.0f, 750.0f, 0.0f))						// �T�C�Y
#define PRESS_START_POS		(D3DXVECTOR3(SCREEN_WIDTH / 2, 700.0f, 0.0f))				// �ʒu
#define PRESS_START_SIZE	(D3DXVECTOR3(750.0f, 300.0f, 0.0f))							// �T�C�Y
#define EFFECT_POS			(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))	// �ʒu
//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CTitle::CTitle()
{
}
//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CTitle::~CTitle()
{
}
//*****************************************************************************
//����������
//*****************************************************************************
HRESULT CTitle::Init(void)
{
	//�T�E���h�擾
	CSound * pSound = CManager::GetSound();

	// �^�C�g��BGM�Đ�
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_TITLE);

	// �^�C�g���̔w�i
	C2D_Polygon::Create(BG_POS, BG_SIZE, C2D_Polygon::TYPE_TITLE_BG);

	// �^�C�g������
	C2D_Polygon::Create(TITLE_POS, TITLE_SIZE, C2D_Polygon::TYPE_TITLE);

	// PRESS_START
	C2D_Polygon::Create(PRESS_START_POS, PRESS_START_SIZE, C2D_Polygon::TYPE_PRESS_START);

	// �G�t�F�N�g����
	C2D_Particle_Emitter::Create(EFFECT_POS, C2D_Particle_Emitter::TYPE_GREEN);
	return S_OK;
}

//*****************************************************************************
//�I������
//*****************************************************************************
void CTitle::Uninit(void)
{
	//�T�E���h�̒�~
	CManager::GetSound()->StopSound();

	// �t�F�[�h�ȊO�j��
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}

//*****************************************************************************
//�X�V����
//*****************************************************************************
void CTitle::Update(void)
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
			// ���艹�Đ�
			pSound->PlaySound(CSound::SOUND_LABEL_SE_DETERMINATION);

			// �Q�[���ɑJ��
			CFade::Create(CManager::MODE_TUTORIAL);
		}
	}
}

//*****************************************************************************
//�`�揈��
//*****************************************************************************
void CTitle::Draw(void)
{

}
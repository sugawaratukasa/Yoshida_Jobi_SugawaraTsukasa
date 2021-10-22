//******************************************************************************
// ���U���g [result.cpp]
// Author : �ǌ��@
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
#include "../2D/2D_Particle/2d_particle_effect.h"
#include "sound.h"
#include "result.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BG_POS				(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))	// �ʒu
#define BG_SIZE				(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f))			// �T�C�Y
#define TITLE_POS			(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3, 0.0f))	// �ʒu
#define TITLE_SIZE			(D3DXVECTOR3(1500.0f, 750.0f, 0.0f))						// �T�C�Y
#define PRESS_START_POS		(D3DXVECTOR3(SCREEN_WIDTH / 2, 700.0f, 0.0f))				// �ʒu
#define PRESS_START_SIZE	(D3DXVECTOR3(750.0f, 300.0f, 0.0f))							// �T�C�Y
#define COUNT				(3)															// �J�E���g
#define REMAINDER			(0)															// �]��
#define RANDOM_POS_MUT		(10)														// 10�{
#define MUT					(2)															// �Q�{
#define SCREEN_X			(SCREEN_WIDTH - 800)										// X�̈ʒu
#define SCREEN_Y			(SCREEN_HEIGHT - 500)										// X�̈ʒu
//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CResult::CResult()
{
	m_nCount = INIT_INT;
}
//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CResult::~CResult()
{
}
//*****************************************************************************
//����������
//*****************************************************************************
HRESULT CResult::Init(void)
{
	// �T�E���h�擾
	CSound *pSound = CManager::GetSound();

	// BGM�Đ�
	pSound->PlaySoundA(CSound::SOUND_LABEL_BGM_RESULT);

	// �^�C�g������
	C2D_Polygon::Create(TITLE_POS, TITLE_SIZE, C2D_Polygon::TYPE_RESULT);
	return S_OK;
}

//*****************************************************************************
//�I������
//*****************************************************************************
void CResult::Uninit(void)
{
	// �T�E���h�̒�~
	CManager::GetSound()->StopSound();

	// �t�F�[�h�ȊO�j��
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}

//*****************************************************************************
//�X�V����
//*****************************************************************************
void CResult::Update(void)
{
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
			// �Q�[���ɑJ��
			CFade::Create(CManager::MODE_TITLE);
		}
	}
	// �C���N�������g
	m_nCount++;
	// 5���܂�0
	if (m_nCount % COUNT == REMAINDER)
	{
		// �ʒu
		D3DXVECTOR3 Random_pos = INIT_D3DXVECTOR3;

		// �ʒu�����_��
		Random_pos.x = float(rand() % (int)SCREEN_X *RANDOM_POS_MUT * MUT - (int)SCREEN_X *RANDOM_POS_MUT / MUT);

		// ���Z
		Random_pos.x = Random_pos.x / RANDOM_POS_MUT;

		// �ʒu�����_��
		Random_pos.y = float(rand() % (int)SCREEN_Y *RANDOM_POS_MUT * MUT - (int)SCREEN_Y *RANDOM_POS_MUT / MUT);

		// ���Z
		Random_pos.y = Random_pos.y / RANDOM_POS_MUT;

		// ����
		C2D_Particle_Effect::Create(Random_pos, C2D_Particle_Effect::TYPE_COLOR_BOM);
	}
}

//*****************************************************************************
//�`�揈��
//*****************************************************************************
void CResult::Draw(void)
{

}
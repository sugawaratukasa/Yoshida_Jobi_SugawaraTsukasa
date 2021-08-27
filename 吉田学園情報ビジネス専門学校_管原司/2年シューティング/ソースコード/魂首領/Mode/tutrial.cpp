//******************************************************************************
// �`���[�g���A�� [tutrial.cpp]
// Author : �ǌ� �i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "../System/main.h"
#include "../System/manager.h"
#include "../System/renderer.h"
#include "../System/scene.h"
#include "../System/scene2d.h"
#include "../Input/input.h"
#include "../Input/inputkeyboard.h"
#include "../Input/inputjoystick.h"
#include "../Polygon/fade.h"
#include "../UI/score.h"
#include "../Polygon/polygon.h"
#include "../System/ranking.h"
#include "../Polygon/ranking_polygon.h"
#include "../System/sound.h"
#include "../Polygon/black_polygon.h"
#include "../Polygon/tutrial_polygon.h"
#include "mode.h"
#include "tutrial.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define TUTRIAL_POS		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))// �ʒu
#define MODE_SIZE		(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT,0.0f))		// �T�C�Y
#define TUTRIAL_COLOR	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))						// �J���[
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************-
CTutrial::CTutrial()
{
	m_bfade = false;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CTutrial::~CTutrial()
{
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CTutrial::Init()
{
	// �`���[�g���A���摜����
	CTutrial_Polygon::Create(TUTRIAL_POS, MODE_SIZE, TUTRIAL_COLOR,CPolygon::TEX_TYPE_TUTRIAL);
	// ���|���S������
	CBlack_Polygon::Create(POLYGON_RIGHT_POS, POLYGON_SIZE, BLACK_POLYGON_COLOR, CPolygon::TEX_TYPE_MAX);
	CBlack_Polygon::Create(POLYGON_LEFT_POS, POLYGON_SIZE, BLACK_POLYGON_COLOR, CPolygon::TEX_TYPE_MAX);
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CTutrial::Uninit(void)
{
	// �t�F�[�h�ȊO�j��
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CTutrial::Update(void)
{
	//�T�E���h�擾
	CSound * pSound = CSceneManager::GetSound();
	CSound::SOUND_LABEL type;
	type = CSound::SOUND_LABEL_SE_SHOT;

	//�L�[�{�[�h�擾
	CInputKeyboard * pInputKeyboard = CSceneManager::GetInputKeyboard();

	//�R���g���[���[�擾
	DIJOYSTATE js;
	CInputJoystick * pInputJoystick = CSceneManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	// �R���g���[���[A�{�^���܂���ENTER
	if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_A) || pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
	{
		// �T�E���h�Đ�
		//pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);

		// �t�F�[�h����
		CFade::Create(FADE_POS, FADE_SIZE, CSceneManager::MODE_GAME);
	}
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CTutrial::Draw(void)
{
}
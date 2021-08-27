//******************************************************************************
// �^�C�g�� [title.cpp]
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
#include "../Polygon/title_polygon.h"
#include "../Polygon/press_enter_polygon.h"
#include "mode.h"
#include "title.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define TITLE_WAIT_COUNT	(10)													// �Q�[���֑J�ڂ���J�E���g
#define TITLE_POS			(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,0.0f))	// �^�C�g���ʒu���W
#define TITLE_SIZE			(D3DXVECTOR3(SCREEN_WIDTH /2, SCREEN_HEIGHT,0.0f))		// �^�C�g���T�C�Y
#define TITLE_COLOR			(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))						// �^�C�g���J���[
#define PRESS_ENTER_POS		(D3DXVECTOR3(SCREEN_WIDTH /2,600.0f,0.0f))				// PRESS_ENTER�ʒu���W
#define PRESS_ENTER_SIZE	(D3DXVECTOR3(200.0f,200.0f,0.0f))						// PRESS_ENTER�T�C�Y
#define PRESS_ENTER_COLOR	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))						// �^�C�g���J���[

//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CTitle::CTitle()
{
	m_bfade = false;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CTitle::~CTitle()
{
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CTitle::Init()
{
	// �^�C�g���摜����
	CTitle_Polygon::Create(TITLE_POS, TITLE_SIZE, TITLE_COLOR, CPolygon::TEX_TYPE_TITLE);
	CPress_Enter_Polygon::Create(PRESS_ENTER_POS,PRESS_ENTER_SIZE,PRESS_ENTER_COLOR,CPolygon::TEX_TYPE_PRESS_ENTER);

	// ���|���S������
	CBlack_Polygon::Create(POLYGON_RIGHT_POS, POLYGON_SIZE, BLACK_POLYGON_COLOR, CPolygon::TEX_TYPE_MAX);
	CBlack_Polygon::Create(POLYGON_LEFT_POS, POLYGON_SIZE, BLACK_POLYGON_COLOR, CPolygon::TEX_TYPE_MAX);
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CTitle::Uninit(void)
{
	// �t�F�[�h�ȊO�j��
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CTitle::Update(void)
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

	// A�{�^���܂���ENTER����������
	if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_A) || pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
	{
		// �T�E���h�Đ�
		//pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);

		// �t�F�[�h����
		CFade::Create(FADE_POS, FADE_SIZE,CSceneManager::MODE_TUTRIAL);
	}
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CTitle::Draw(void)
{
}
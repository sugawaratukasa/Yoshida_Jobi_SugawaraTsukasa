//******************************************************************************
// ���U���g [result.cpp]
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
#include "mode.h"
#include "result.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define RANKING_POLYGON_POS		(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f))	// �����L���O�|���S���ʒu
#define RANKING_POLYGON_SIZE	(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT,0.0f))		// �����L���O�|���S���T�C�Y
#define RANKING_POLYGON_COLOR	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))						// �����L���O�|���S���F
#define RANKING_POS				(D3DXVECTOR3(700.0f, 300.0f, 0.0f))						// �����L���O�ʒu
#define RANKING_SIZE			(D3DXVECTOR3(30.0f,30.0f,0.0f))							// �����L���O�T�C�Y
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
CPlayerdata *CResult::m_pPlayerData = NULL;

//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CResult::CResult()
{
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CResult::~CResult()
{
	m_bfade = false;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CResult::Init()
{
	// �����L���O�|���S������
	CRanking_Polygon::Create(RANKING_POLYGON_POS, RANKING_POLYGON_SIZE, RANKING_POLYGON_COLOR, CPolygon::TEX_TYPE_RANKING);
	//�����L���O����
	CRanking::Create(RANKING_POS, RANKING_SIZE);
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CResult::Uninit(void)
{
	// �t�F�[�h�ȊO�j��
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CResult::Update(void)
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

	// A�{�^���܂���ENTER���������ꍇ
	if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_A) || pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
	{
		// �T�E���h�Đ�
		pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);

		// �t�F�[�h����
		CFade::Create(FADE_POS, FADE_SIZE, CSceneManager::MODE_TITLE);
	}
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CResult::Draw(void)
{
}
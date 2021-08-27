//******************************************************************************
// �R���e�B�j���[ [continue.cpp]
// Author : �ǌ��@�i
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
#include "../Player/player.h"
#include "../System/sound.h"
#include "../System/number.h"
#include "../Mode/game.h"
#include "continue.h"
#include "../Polygon/fade.h"
#include "../Polygon/polygon.h"
#include "../Polygon/continue_polygon.h"
#include "../Polygon/press_enter_polygon.h"
//******************************************************************************
// �}�N����`
//******************************************************************************		
#define PRESS_ENTER_POS			(D3DXVECTOR3(SCREEN_WIDTH / 2,600,0.0f))						// �v���X�G���^�[�ʒu
#define PRESS_ENTER_SIZE		(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 4,0.0f))			// �v���X�G���^�[�T�C�Y
#define CONTINUE_POLYGON_POS	(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 - 200,0.0f))	// �R���e�B�j���[�|���S���̈ʒu
#define CONTINUE_POLYGON_SIZE	(D3DXVECTOR3(SCREEN_WIDTH / 2,300.0f,0.0f))						// �R���e�B�j���[�|���S���̃T�C�Y
#define CONTINUE_POLYGON_COLOR	(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))								// �R���e�B�j���[�|���S���̃T�C�Y
#define PRESS_ENTER_COLOR		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))								// �v���X�G���^�[�F
#define COLOR_VALUE				(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))								// �F�̒l
#define TIME_COUNT				(60)															// ����
#define CONTINUE_TIMW_MIN		(0)																// �R���e�B�j���[���Ԃ̍ŏ�
#define REMAINDER_VALUE			(0)																// �]��0�̒l
#define CONTINUE_TIME_MAX		(9)																// �R���e�B�j���[���Ԃ̍ő�
#define PLAYER_CONTINUE			(1)																// �v���C���[�̃R���e�B�j���[
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CContinue::CContinue(int nPriority) : CScene(nPriority)
{
	m_pNumber			= NULL;
	m_pContinue_Polygon = NULL;
	m_pPress_Enter		= NULL;
	m_pos				= INIT_D3DXVECTOR3;
	m_size				= INIT_D3DXVECTOR3;
	m_nContinueCount	= INIT_INT;
	m_nContinueNum		= INIT_INT;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CContinue::~CContinue()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CContinue * CContinue::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CContinue�N���X�̃|�C���^
	CContinue * pContinue;

	// �������m��
	pContinue = new CContinue;

	// �ʒu���W���
	pContinue->m_pos = pos;

	// �T�C�Y���
	pContinue->m_size = size;

	// ������
	pContinue->Init();

	// �|�C���^��Ԃ�
	return pContinue;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CContinue::Init(void)
{
	// ��������
	m_pNumber = CNumber::Create(m_pos, m_size, COLOR_VALUE);

	// �R���e�B�j���[����
	m_nContinueNum = CONTINUE_TIME_MAX;

	// �����ݒ�
	m_pNumber->SetNumber(m_nContinueNum);

	// UI����

	// �R���e�B�j���[�|���S������
	m_pContinue_Polygon = CContinue_Polygon::Create(CONTINUE_POLYGON_POS, CONTINUE_POLYGON_SIZE, CONTINUE_POLYGON_COLOR, CPolygon::TEX_TYPE_CONTINUE);

	// �v���X�G���^�[����
	m_pPress_Enter = CPress_Enter_Polygon::Create(PRESS_ENTER_POS, PRESS_ENTER_SIZE, PRESS_ENTER_COLOR,CPolygon::TEX_TYPE_PRESS_ENTER);

	return S_OK;								  
}												 
//******************************************************************************
// �I���֐�
//******************************************************************************
void CContinue::Uninit(void)
{
	// �I��
	if (m_pNumber != NULL)
	{
		m_pNumber->Uninit();
		delete m_pNumber;
		m_pNumber = NULL;
	}
	//�����[�X
	Release();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CContinue::Update(void)
{
	// �L�[�{�[�h�擾
	CInputKeyboard * pInputKeyboard = CSceneManager::GetInputKeyboard();

	// �W���C�X�e�B�b�N
	DIJOYSTATE js;

	// �C���v�b�g�W���C�X�e�B�b�N
	CInputJoystick * pInputJoystick = CSceneManager::GetInputJoystick();

	// �f�o�C�X�擾
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	// �v���C���[�̎擾
	CPlayer * pPlayer = CGame::GetPlayer();

	// �T�E���h�擾
	CSound * pSound = CSceneManager::GetSound();
	CSound::SOUND_LABEL type;
	type = CSound::SOUND_LABEL_SE_SHOT;

	// �R���e�B�j���[�^�C���̃C���N�������g
	m_nContinueCount++;
	// 1�b��������
	if (m_nContinueCount % TIME_COUNT == REMAINDER_VALUE)
	{
		// �i���o�[�̃f�N�������g
		m_nContinueNum--;
		// �i���o�[�̐ݒ�
		m_pNumber->SetNumber(m_nContinueNum);
	}
	// �i���o�[��0�̏ꍇ
	if (m_nContinueNum <= CONTINUE_TIMW_MIN)
	{
		// ���U���g�ɑJ��
		CFade::Create(FADE_POS, FADE_SIZE, CSceneManager::MODE_RESULT);
	}
	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	// START�{�^���܂���ENTER�������ꂽ�ꍇ
	if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(11) || pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
	{
		// ������
		pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);

		// �R���e�B�j���[�̔���
		pPlayer->SetContinue(PLAYER_CONTINUE);

		// �R���e�B�j���[�|���S���j��
		m_pContinue_Polygon->Uninit();

		// �v���X�G���^�[�j��
		m_pPress_Enter->Uninit();

		// �I��
		Uninit();
		return;
	}
	
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CContinue::Draw(void)
{
	// �`��
	m_pNumber->Draw();
}

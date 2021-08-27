//******************************************************************************
// manager [manager.cpp]
// Author : �ǌ��@�i
//******************************************************************************

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "../Input/input.h"
#include "../Input/inputkeyboard.h"
#include "../Input/inputjoystick.h"
#include "../Player/player.h"
#include "../Player/player_wepon.h"
#include "../Bullet/bullet.h"
#include "../Polygon/bg.h"
#include "sound.h"
#include "../Enemy/enemy.h"
#include "number.h"
#include "../UI/score.h"
#include "../UI/life.h"
#include "../Mode/mode.h"
#include "../Polygon/fade.h"
#include "../Polygon/item.h"
#include "../UI/bomui.h"
#include "../Polygon/polygon.h"
#include "../Boss/boss.h"
#include "../Boss/boss_left.h"
#include "../Boss/boss_right.h"
#include "../Mode/tutrial.h"
#include "../Enemy/ship.h"
#include "../Particle/particle.h"
#include "../Mode/title.h"
#include "../Mode/game.h"
#include "../Mode/result.h"
#include "../Beam/beam.h"
#include "../UI/warning.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODE_SIZE (D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT,0.0f))	// 
#define MAX_NUMBER (9)													// �i���o�[�ő吔
//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CRenderer * CSceneManager::m_pRenderer				= NULL;
CInputKeyboard * CSceneManager::m_pInputKeyboard	= NULL;
CInputJoystick * CSceneManager::m_pInputJoystick	= NULL;
CSound * CSceneManager::m_pSound					= NULL;
CMode *CSceneManager::m_pMode						= NULL;
CSceneManager::MODE CSceneManager::m_mode			= MODE_NONE;
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CSceneManager::CSceneManager()
{
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CSceneManager::~CSceneManager()
{
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CSceneManager::Init(HINSTANCE hInsitance, HWND hWnd, bool bWindow)
{
	// �����_���[�̐���
	if (m_pRenderer == NULL)
	{
		// �������m��
		m_pRenderer = new CRenderer;

		// NULL�łȂ��ꍇ
		if (m_pRenderer != NULL)
		{
			// �����_���[����������
			m_pRenderer->Init(hWnd, TRUE);
		}
		// NULL�̏ꍇ
		else
		{
			return 0;
		}
	}
	// �L�[�{�[�h����
	if (m_pInputKeyboard == NULL)
	{
		// �������m��
		m_pInputKeyboard = new CInputKeyboard;
		// NULL�łȂ��Ƃ�
		if (m_pInputKeyboard != NULL)
		{
			// �L�[�{�[�h����������
			m_pInputKeyboard->Init(hInsitance, hWnd);
		}
		// NULL�̏ꍇ
		else
		{
			return 0;
		}
	}
	// �R���g���[���[����
	if (m_pInputJoystick == NULL)
	{
		// �������m��
		m_pInputJoystick = new CInputJoystick;
		// NULL�łȂ��Ƃ�
		if (m_pInputJoystick != NULL)
		{
			// �R���g���[���[����������
			m_pInputJoystick->Init(hInsitance, hWnd);
		}
		// NULL�̏ꍇ
		else
		{
			return 0;
		}
	}
	//�T�E���h����
	if (m_pSound == NULL)
	{
		// ������m��
		m_pSound = new CSound;

		// NULL�łȂ��Ƃ�
		if (m_pSound != NULL)
		{
			// �T�E���h����������
			m_pSound->Init(hWnd);
		}
		// NULL�̏ꍇ
		else
		{
			return 0;
		}
	}

	// �e�N�X�`���S�ǂݍ���
	LoadAll();

	// �^�C�g���ɐݒ�
	SetMode(MODE_TITLE);

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CSceneManager::Uninit(void)
{
	//�S�ẴI�u�W�F�N�g��j��
	CScene::ReleaseAll();
	// �e�N�X�`���S�ǂݍ���
	UnloadAll();
	//�T�E���h�S��~
	m_pSound->StopSound();

	// NULL�łȂ��ꍇ
	if (m_pInputJoystick != NULL)
	{
		// �R���g���[���[�̏I������
		m_pInputJoystick->Uninit();
		delete m_pInputJoystick;
		m_pInputJoystick = NULL;
	}
	// NULL�łȂ��ꍇ
	if (m_pInputKeyboard != NULL)
	{
		// �L�[�{�[�h�̏I������
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}
	// NULL�łȂ��ꍇ
	if (m_pRenderer != NULL)
	{
		// �����_���[�̏I������
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	// NULL�łȂ��ꍇ
	if (m_pMode != NULL)
	{
		// ���[�h�I��
		m_pMode->Uninit();
	}

	// NULL�łȂ��ꍇ
	if (m_pSound != NULL)
	{
		// �T�E���h�̏I������
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}
}

//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CSceneManager::Update(void)
{
	// NULL�łȂ��ꍇ
	if (m_pRenderer != NULL)
	{
		// �����_���[�X�V
		m_pRenderer->Update();
	}
	// NULL�łȂ��ꍇ
	if (m_pInputKeyboard != NULL)
	{
		// �L�[�{�[�h�X�V
		m_pInputKeyboard->Update();
	}
	// NULL�łȂ��ꍇ
	if (m_pInputJoystick != NULL)
	{
		// �R���g���[���[�X�V
		m_pInputJoystick->Update();
	}
	// NULL�łȂ��ꍇ
	if (m_pMode != NULL)
	{
		// ���[�h�X�V
		m_pMode->Update();
	}
}

//******************************************************************************
// �`��֐�
//******************************************************************************
void CSceneManager::Draw(void)
{
	// NULL�łȂ��ꍇ
	if (m_pRenderer != NULL)
	{
		//�`�揈��
		m_pRenderer->Draw();
	}
	if (m_pMode != NULL)
	{
		// ���[�h�`�揈��
		m_pMode->Draw();
	}
}
//******************************************************************************
// ���[�h�ݒ�
//******************************************************************************
void CSceneManager::SetMode(MODE mode)
{
	// NULL�łȂ��ꍇ
	if (m_pMode != NULL)
	{
		// ���̎��̃��[�h�̏I������
		m_pMode->Uninit();
		// �������j��
		delete m_pMode;
		// NULL��
		m_pMode = NULL;
	}
	// NULL�̏ꍇ
	if (m_pMode == NULL)
	{
		m_mode = mode;

		switch (m_mode)
		{
		case MODE_TITLE:

			// �^�C�g���̐���
			m_pMode = new CTitle;

			// �^�C�g���̏���������
			m_pMode->Init();

			break;

		case MODE_GAME:
			// �Q�[���̐���
			m_pMode = new CGame;

			// �Q�[���̏���������
			m_pMode->Init();

			break;

		case MODE_TUTRIAL:

			// �`���[�g���A���̐���
			m_pMode = new CTutrial;

			// �`���[�g���A���̏���������
			m_pMode->Init();

			break;

		case MODE_RESULT:

			// �N���A��ʂ̐���
			m_pMode = new CResult;

			// �N���A��ʂ̏���������
			m_pMode->Init();

			break;
		}
	}
	// �L�[�{�[�h�X�V
	m_pInputJoystick->Update();
}
//******************************************************************************
// �e�N�X�`���S�ǂݍ��݊֐�
//******************************************************************************
void CSceneManager::LoadAll(void)
{
	// �w�i
	CBg::Load();
	// ���C�t
	CLife::Load();
	// ���@
	CPlayer::Load();
	// �v���C���[�̕���
	CPlayer_Wepon::Load();
	// �G
	CEnemy::Load();
	// �e
	CBullet::Load();
	// �i���o�[
	CNumber::Load();
	// �A�C�e��
	CItem::Load();
	// �{��
	CBomUI::Load();
	// Ship
	CShip::Load();
	// �{�X
	CBoss::Load();
	// �{�X�̍�
	CBoss_Left::Load();
	// �{�X�̉E
	CBoss_Right::Load();
	// warning
	CWarning::Load();
	// �p�[�e�B�N��
	CParticle::Load();
	// �|���S��
	CPolygon::Load();
	// �r�[��
	CBeam::Load();
}
//******************************************************************************
// �e�N�X�`���S�j���֐�
//******************************************************************************
void CSceneManager::UnloadAll(void)
{
	// �e�N�X�`���j��
	// �r�[��
	CBeam::Unload();
	// �|���S��
	CPolygon::Unload();
	// �p�[�e�B�N��
	CParticle::Unload();
	// warning
	CWarning::Unload();
	// �{�X
	CBoss::Unload();
	// �{�X�̍�
	CBoss_Left::Unload();
	// �{�X�̉E
	CBoss_Right::Unload();
	// Ship
	CShip::Unload();
	// �{��
	CBomUI::Unload();
	// �A�C�e��
	CItem::Unload();
	// �i���o�[
	CNumber::Unload();
	// �e
	CBullet::Unload();
	// �G
	CEnemy::Unload();
	// ���@
	CPlayer::Unload();
	// �v���C���[�̕���
	CPlayer_Wepon::Unload();
	// ���C�t
	CLife::Unload();
	// �w�i
	CBg::Unload();
}
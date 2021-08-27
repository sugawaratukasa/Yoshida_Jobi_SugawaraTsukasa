//******************************************************************************
// �|�[�Y [pause.cpp]
// Author : �ǌ��i
//******************************************************************************
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "joystick.h"
#include "2d_polygon.h"
#include "fade.h"
#include "mode.h"
#include "game.h"
#include "sound.h"
#include "pause.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define BLACK_POLYGON_POS	(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))				// �ʒu
#define BLACK_POLYGON_SIZE	(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f))						// �T�C�Y
#define SIZE				(D3DXVECTOR3(750.0f, 500.0f, 0.0f))										// �T�C�Y
#define RESUME_POS			(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - SIZE.y / 2, 0.0f))	// �ʒu
#define CONTROLS_POS		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))				// �ʒu
#define EXIT_POS			(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + SIZE.y / 2, 0.0f))	// �ʒu
#define DEAD_ZONE_MIN		(0)																		// �X�e�B�b�N�̃f�b�h�]�[���ŏ��l
#define COL					(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))										// �F
#define BLACK_COL			(D3DXCOLOR(0.5f,0.5f,0.5f,1.0f))										// �F
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CPause::CPause(int nPriority) : CScene(nPriority)
{
	memset(m_apPolygon, NULL, sizeof(m_apPolygon));
	m_nCount	= INIT_INT;
	m_bStick	= false;
	m_bControls = false;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CPause::~CPause()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CPause * CPause::Create(void)
{
	// CPause�̃|�C���^
	CPause *pPause = NULL;

	// NULL�̏ꍇ
	if (pPause == NULL)
	{
		// �������m��
		pPause = new CPause;

		// NULL�łȂ��ꍇ
		if (pPause != NULL)
		{
			// �I�u�W�F�N�g�^�C�v�ݒ�
			pPause->SetObjType(OBJTYPE_NOSTOP_UI);

			// ������
			pPause->Init();
		}
	}
	// �|�C���^��Ԃ�
	return pPause;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CPause::Init(void)
{
	// RESUME��
	m_nCount = TYPE_RESUME;

	// ���|������
	m_apPolygon[TYPE_BLACK] = C2D_Polygon::Create(BLACK_POLYGON_POS, BLACK_POLYGON_SIZE, C2D_Polygon::TYPE_NONE);

	// RESUME����
	m_apPolygon[TYPE_RESUME] = C2D_Polygon::Create(RESUME_POS, SIZE, C2D_Polygon::TYPE_RESUME);

	// RESUME����
	m_apPolygon[TYPE_CONTROLS] = C2D_Polygon::Create(CONTROLS_POS, SIZE, C2D_Polygon::TYPE_CONTROLS);

	// RESUME����
	m_apPolygon[TYPE_EXIT] = C2D_Polygon::Create(EXIT_POS, SIZE, C2D_Polygon::TYPE_EXIT);

	// �X�V��~
	SetUpdateStop(true);
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CPause::Uninit(void)
{
	// �j��
	CScene::Release();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CPause::Update(void)
{
	// �I��
	Select();
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CPause::Draw(void)
{
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CPause::Select(void)
{
	//�T�E���h�擾
	CSound * pSound = CManager::GetSound();

	// �R���g���[���[�擾
	DIJOYSTATE js;
	js.lY = INIT_INT;
	js.lX = INIT_INT;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();


	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	if (g_lpDIDevice != NULL)
	{
		// false�̏ꍇ
		if (m_bControls == false)
		{
			// false�̏ꍇ
			if (m_bStick == false)
			{
				// ���X�e�B�b�N����ɓ|���ꍇ
				if (js.lY >= STICK_REACTION)
				{
					// true��
					m_bStick = true;

					// EXIT�̏ꍇ
					if (m_nCount == TYPE_EXIT)
					{
						// EXIT��
						m_nCount = TYPE_EXIT;
					}
					// EXIT�łȂ��ꍇ
					if (m_nCount != TYPE_EXIT)
					{
						// ���艹�Đ�
						pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);

						// �C���N�������g
						m_nCount++;
					}
				}
				// ���X�e�B�b�N�����ɓ|���ꍇ
				if (js.lY <= -STICK_REACTION)
				{
					// RESUME�̏ꍇ
					if (m_nCount == TYPE_RESUME)
					{
						// EXIT��
						m_nCount = TYPE_RESUME;
					}
					// RESUME�łȂ��ꍇ
					if (m_nCount != TYPE_RESUME)
					{
						// ���艹�Đ�
						pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);

						// �f�N�������g
						m_nCount--;
					}
					// true��
					m_bStick = true;
				}
			}
			// true�̏ꍇ
			if (m_bStick == true)
			{
				// -500���傫��0��菬�����ꍇ
				if (js.lY > -STICK_REACTION && js.lY <= DEAD_ZONE_MIN)
				{
					m_bStick = false;
				}
				// 500��菬����0���傫���ꍇ
				if (js.lY < STICK_REACTION && js.lY >= DEAD_ZONE_MIN)
				{
					m_bStick = false;
				}
			}
			// RESUME�̏ꍇ
			if (m_nCount == TYPE_RESUME)
			{
				// �F�ݒ�
				m_apPolygon[m_nCount]->SetColor(COL);
				m_apPolygon[TYPE_CONTROLS]->SetColor(BLACK_COL);
				m_apPolygon[TYPE_EXIT]->SetColor(BLACK_COL);

				// A�{�^�����������ꍇ
				if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_A))
				{
					// ���艹�Đ�
					pSound->PlaySound(CSound::SOUND_LABEL_SE_DETERMINATION);

					// �X�V�J�n
					SetUpdateStop(false);

					// �j��
					CPause::Release();
				}
			}
			// RESUME�̏ꍇ
			if (m_nCount == TYPE_CONTROLS)
			{
				// �F�ݒ�
				m_apPolygon[m_nCount]->SetColor(COL);
				m_apPolygon[TYPE_RESUME]->SetColor(BLACK_COL);
				m_apPolygon[TYPE_EXIT]->SetColor(BLACK_COL);

				// A�{�^�����������ꍇ
				if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_A))
				{
					// ���艹�Đ�
					pSound->PlaySound(CSound::SOUND_LABEL_SE_DETERMINATION);

					// true��
					m_bControls = true;

					// ����
					C2D_Polygon::Create(BLACK_POLYGON_POS, BLACK_POLYGON_SIZE, C2D_Polygon::TYPE_CONTROLS_BG);
				}
			}
			// RESUME�̏ꍇ
			if (m_nCount == TYPE_EXIT)
			{
				// �F�ݒ�
				m_apPolygon[m_nCount]->SetColor(COL);
				m_apPolygon[TYPE_RESUME]->SetColor(BLACK_COL);
				m_apPolygon[TYPE_CONTROLS]->SetColor(BLACK_COL);

				// A�{�^�����������ꍇ
				if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_A))
				{
					// ���艹�Đ�
					pSound->PlaySound(CSound::SOUND_LABEL_SE_DETERMINATION);

					// �X�V�J�n
					SetUpdateStop(false);

					// �t�F�[�h����
					CFade::Create(CManager::MODE_TITLE);
				}
			}
			// B�������ꂽ�ꍇ
			if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_B))
			{
				// ���艹�Đ�
				pSound->PlaySound(CSound::SOUND_LABEL_SE_DETERMINATION);

				// �X�V�J�n
				SetUpdateStop(false);

				// �X�V
				pInputJoystick->Update();

				// �j��
				CPause::Release();
			}
		}
		// true�̏ꍇ
		if (m_bControls == true)
		{
			// B,START,A�{�^�����������ꍇ
			if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_B))
			{
				// ���艹�Đ�
				pSound->PlaySound(CSound::SOUND_LABEL_SE_DETERMINATION);

				// false��
				m_bControls = false;
			}
		}
		// START�������ꂽ�ꍇ
		if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_START))
		{
			// true�̏ꍇ
			if (m_bControls == true)
			{
				// false��
				m_bControls = false;
			}
			// false�̏ꍇ
			if (m_bControls == false)
			{
				// �X�V
				pInputJoystick->Update();
			}
			// ���艹�Đ�
			pSound->PlaySound(CSound::SOUND_LABEL_SE_DETERMINATION);

			// �X�V�J�n
			SetUpdateStop(false);

			// �j��
			CPause::Release();
		}
	}
}
//******************************************************************************
// �j���֐�
//******************************************************************************
void CPause::Release(void)
{
	// �Q�[���擾
	CMode *pMode = CManager::GetMode();

	// �Q�[���̎g�p����ݒ�
	((CGame*)pMode)->SetPause(false);

	// �j��
	m_apPolygon[TYPE_BLACK]->Uninit();
	m_apPolygon[TYPE_RESUME]->Uninit();
	m_apPolygon[TYPE_CONTROLS]->Uninit();
	m_apPolygon[TYPE_EXIT]->Uninit();

	// �I��
	Uninit();
	return;
}
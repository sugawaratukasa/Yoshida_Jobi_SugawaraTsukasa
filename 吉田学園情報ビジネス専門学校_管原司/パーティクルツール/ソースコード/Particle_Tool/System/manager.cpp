//***********************************************************************************
// �}�l�[�W���[���� [manager.cpp]
// Author : �ǌ��@�i
//***********************************************************************************

//***********************************************************************************
//�C���N���[�h�t�@�C��
//***********************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "camera.h"
#include "mode.h"
#include "tool.h"
#include "texture.h"
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include <d3d9.h>
#include <dinput.h>
#include <tchar.h>

//***********************************************************************************
//�X�^�e�B�b�N�ϐ�������
//***********************************************************************************
CRenderer *CManager::m_pRenderer = NULL;
CCamera *CManager::m_pCamera	 = NULL;
CMode *CManager::m_pMode		 = NULL;
CTexture *CManager::m_pTexture	 = NULL;
//***********************************************************************************
//�R���X�g���N�^
//***********************************************************************************
CManager::CManager()
{

}

//***********************************************************************************
//�f�X�g���N�^
//***********************************************************************************
CManager::~CManager()
{

}

//***********************************************************************************
//����������
//***********************************************************************************
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindouw)
{
	// NULL�̏ꍇ
	if (m_pRenderer == NULL)
	{
		// �������m��
		m_pRenderer = new CRenderer;

		// NULL�łȂ��ꍇ
		if (m_pRenderer != NULL)
		{
			// ������
			m_pRenderer->Init(hWnd, TRUE);
		}
	}
	// NULL�̏ꍇ
	if (m_pTexture == NULL)
	{
		// �������m��
		m_pTexture = new CTexture;

		// NULL�łȂ��ꍇ
		if (m_pTexture != NULL)
		{
			// ������
			m_pTexture->Init();
		}
	}

	// �o�[�W�����`�F�b�N
	IMGUI_CHECKVERSION();

	// �R���e�L�X�g����
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// �F�ݒ�
	ImGui::StyleColorsDark();

	// ������
	ImGui_ImplWin32_Init(hWnd);

	// ������
	ImGui_ImplDX9_Init(GetRenderer()->GetDevice());

	// �t�H���g�ݒ�
	ImFont* font = io.Fonts->AddFontFromFileTTF("C://Windows//Fonts//MEIRYO.TTC", 20.0f, NULL, io.Fonts->GetGlyphRangesJapanese());

	IM_ASSERT(font != NULL);

	// ���[�h�ݒ�
	SetMode(MODE_TOOL);
	return S_OK;
}

//***********************************************************************************
//�I������
//***********************************************************************************
void CManager::Uninit(void)
{
	CScene::ReleaseAll();

	// �e�N�X�`���̏I��
	if (m_pTexture != NULL)
	{
		// �I��
		m_pTexture->Uninit();

		// �������J��
		delete m_pTexture;

		// NULL��
		m_pTexture = NULL;
	}
	// ���[�h�̏I��
	if (m_pMode != NULL)
	{
		//���̎��̃��[�h�I��
		m_pMode->Uninit();

		// �������J��
		delete m_pMode;

		// NULL��
		m_pMode = NULL;
	}
	//�J�����̏I��
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}
	//�����_���[�̏I��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	// �I��
	ImGui_ImplDX9_Shutdown();

	// �I��
	ImGui_ImplWin32_Shutdown();

	// �R���e�L�X�g�j��
	ImGui::DestroyContext();
}

//***********************************************************************************
// �X�V����
//***********************************************************************************
void CManager::Update(void)
{
	// NULL�łȂ��ꍇ
	if (m_pRenderer != NULL)
	{
#ifdef _DEBUG
		// FPS�̃Z�b�g
		m_pRenderer->SetNumFPS(m_nCountFPS);
#endif
		//�����_���[�̍X�V����
		m_pRenderer->Update();
	}
	// NULL�łȂ��ꍇ
	if (m_pCamera != NULL)
	{
		//�J�����̂̍X�V����
		m_pCamera->Update();
	}
	// NULL�łȂ��ꍇ
	if (m_pMode != NULL)
	{
		// ���̎��̃��[�h�̕`�揈��
		m_pMode->Update();
	}
}

//***********************************************************************************
// �`�揈��
//***********************************************************************************
void CManager::Draw(void)
{
	// NULL�łȂ��ꍇ
	if (m_pRenderer != NULL)
	{
		//�`�揈��
		m_pRenderer->Draw();
	}
	// NULL�łȂ��ꍇ
	if (m_pMode != NULL)
	{
		// ���̎��̃��[�h�̕`�揈��
		m_pMode->Draw();
	}
}

//***********************************************************************************
//�e�N�X�`���̓ǂݍ��݂܂Ƃ�
//***********************************************************************************
void CManager::LoadAll(void)
{

}

//***********************************************************************************
//�e�N�X�`���̔j���܂Ƃ�
//***********************************************************************************
void CManager::UnloadAll(void)
{

}

//***********************************************************************************
//�J�����̐���
//***********************************************************************************
void CManager::CreateCamera(void)
{
	// NULL�̏ꍇ
	if (m_pCamera == NULL)
	{
		// �������m��
		m_pCamera = new CCamera;

		// NULL�łȂ��ꍇ
		if (m_pCamera != NULL)
		{
			// ������
			m_pCamera->Init();
		}
	}
}
//***********************************************************************************
// ���[�h�̐ݒ�
//***********************************************************************************
void CManager::SetMode(MODE mode)
{
	// NULL�łȂ��ꍇ
	if (m_pMode != NULL)
	{
		// ���̎��̃��[�h�̏I������
		m_pMode->Uninit();

		// �j��
		delete m_pMode;

		// NULL��
		m_pMode = NULL;
	}
	// NULL�̏ꍇ
	if (m_pMode == NULL)
	{
		// ���
		m_Mode = mode;

		switch (m_Mode)
		{
		case MODE_TOOL:
			// �c�[���̐���
			m_pMode = new CTool;

			// �c�[���̏���������
			m_pMode->Init();

			break;

		default:
			return;
			break;
		}
	}
}
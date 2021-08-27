//*****************************************************************************
// �c�[�� [tool.cpp]
// Author : �ǌ��@�i
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "manager.h"
#include "renderer.h"
#include "time.h"
#include "mode.h"
#include "camera.h"
#include "scene.h"
#include "tool.h"
#include "ui.h"
#include "particle.h"
#include "particle_2.h"
#include <tchar.h>
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ROT				(D3DXVECTOR3(0.0f,0.0f,0.0f))						// ����
#define SIZE			(D3DXVECTOR3(50.0f,50.0f,0.0f))						// �T�C�Y
#define COL				(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))					// �F
#define REMAINDER		(0)													// �]��
#define MIN_COLOR		(0.0f)												// �F�̍ŏ��l
#define RANDOM_POS_MUT	(10.0f)												// �|����l
#define MUT				(2.0f)												// �Q�{
//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CTool::CTool()
{
	m_pUi				= NULL;
	m_nCreateCount		= INIT_INT;
	m_nCreateCount_2	= INIT_INT;
}
//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CTool::~CTool()
{
}
//*****************************************************************************
//����������
//*****************************************************************************
HRESULT CTool::Init(void)
{
	//�J����
	CManager::CreateCamera();

	// UI����
	m_pUi = CUI::Create();

	return S_OK;
}
//*****************************************************************************
//�I������
//*****************************************************************************
void CTool::Uninit(void)
{
}
//*****************************************************************************
//�X�V����
//*****************************************************************************
void CTool::Update(void)
{
	// �p�[�e�B�N������
	Particle_Create();
}
//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CTool::Draw(void)
{
}
//*****************************************************************************
// �p�[�e�B�N����������
//*****************************************************************************
void CTool::Particle_Create(void)
{
	// �G�~�b�^�[��true�̏ꍇ
	if (m_pUi->GetbEmitter() == true)
	{
		// �C���N�������g
		m_nCreateCount++;

		// �����J�E���g
		int nDEVIDE = m_pUi->GetCreateCount();

		// ����
		if (m_nCreateCount % nDEVIDE == REMAINDER)
		{
			// �p�[�e�B�N������
			CParticle::Create(m_pUi);
		}
	}
	// �G�t�F�N�g��true�̏ꍇ
	if (m_pUi->GetbEffect() == true)
	{
		// �C���N�������g
		m_nCreateCount++;

		// �����J�E���g
		int nCreateCount = m_pUi->GetCreateCount();

		// �����̑���
		int nCreateTotalCount = m_pUi->GetCreateTotalCount();

		// ����
		if (m_nCreateCount == nCreateCount)
		{
			for (int nCnt = INIT_INT; nCnt < nCreateTotalCount; nCnt++)
			{
				// �p�[�e�B�N������
				CParticle::Create(m_pUi);
			}
			// ������
			m_nCreateCount = INIT_INT;
		}
		// m_nCreateCount��nCreateCount���傫���ꍇ
		if (m_nCreateCount > nCreateCount)
		{
			// ������
			m_nCreateCount = INIT_INT;
		}
	}
	// �G�~�b�^�[��true�̏ꍇ
	if (m_pUi->GetbEmitter_2() == true)
	{
		// �C���N�������g
		m_nCreateCount_2++;

		// �����J�E���g
		int nDEVIDE = m_pUi->GetCreateCount_2();

		// ����
		if (m_nCreateCount_2 % nDEVIDE == REMAINDER)
		{
			// �p�[�e�B�N������
			CParticle_2::Create(m_pUi);
		}
	}
	// �G�t�F�N�g��true�̏ꍇ
	if (m_pUi->GetbEffect_2() == true)
	{
		// �C���N�������g
		m_nCreateCount_2++;

		// �����J�E���g
		int nCreateCount = m_pUi->GetCreateCount_2();

		// �����̑���
		int nCreateTotalCount = m_pUi->GetCreateTotalCount_2();

		// ����
		if (m_nCreateCount_2 == nCreateCount)
		{
			// �������J��Ԃ�
			for (int nCnt = INIT_INT; nCnt < nCreateTotalCount; nCnt++)
			{
				// �p�[�e�B�N������
				CParticle_2::Create(m_pUi);
			}
			// ������
			m_nCreateCount_2 = INIT_INT;
		}
		// m_nCreateCount��nCreateCount���傫���ꍇ
		if (m_nCreateCount_2 > nCreateCount)
		{
			// ������
			m_nCreateCount_2 = INIT_INT;
		}
	}
}
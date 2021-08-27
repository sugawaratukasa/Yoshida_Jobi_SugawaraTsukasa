//******************************************************************************
// �{����UI [bomui.cpp]
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
#include "bomui.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define BOM_UI_TEXTURE				( "data/Texture/UI/bom3.png")		// �{��UI�e�N�X�`��
#define NOT_POSESSION_COLOR_VALUE	(D3DXCOLOR(0.3f,0.3f,0.3f,1.0f))	// �{�����������ĂȂ����̐F
#define POSESSION_COLOR_VALUE		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	//	�{�����������Ă���Ƃ��̐F
#define BOM_UI_SIZE					(D3DXVECTOR3(40.0f,40.0f,0.0f))		// �T�C�Y
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPDIRECT3DTEXTURE9 CBomUI::m_pTexture = NULL;
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CBomUI::CBomUI(int nPriority) : CScene(nPriority)
{
	memset(m_apScene2D, 0, sizeof(m_apScene2D));
	m_pos				= INIT_D3DXVECTOR3;
	m_size				= INIT_D3DXVECTOR3;
	m_nBom_Posession	= INIT_INT;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CBomUI::~CBomUI()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CBomUI * CBomUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CBomUI�N���X�̃|�C���^
	CBomUI * pBomUI;

	// �������m��
	pBomUI = new CBomUI;

	// �ʒu���W���
	pBomUI->m_pos = pos;

	// �T�C�Y���
	pBomUI->m_size = size;

	// ������
	pBomUI->Init();

	// �|�C���^��Ԃ�
	return pBomUI;
}
//******************************************************************************
// �e�N�X�`���ǂݍ���
//******************************************************************************
HRESULT CBomUI::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BOM_UI_TEXTURE, &m_pTexture);
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���j��
//******************************************************************************
void CBomUI::Unload(void)
{
	m_pTexture->Release();
	m_pTexture = NULL;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CBomUI::Init()
{
	// �ő吔���J��Ԃ�
	for (int nCnt = INIT_INT; nCnt < MAX_BOM; nCnt++)
	{
		// �������m��
		m_apScene2D[nCnt] = new CScene2d(OBJTYPE_UI);

		// �J���[�ݒ�
		m_apScene2D[nCnt]->SetRGBA(NOT_POSESSION_COLOR_VALUE);

		// �e�N�X�`���󂯓n��
		m_apScene2D[nCnt]->BindTexture(m_pTexture);

		// �ʒu�ݒ�
		m_apScene2D[nCnt]->SetPosition(D3DXVECTOR3((m_pos.x + BOM_UI_SIZE.x * nCnt), m_pos.y, m_pos.z));

		// �T�C�Y�ݒ�
		m_apScene2D[nCnt]->SetSize(m_size);

		// �I�u�W�F�N�g�^�C�v�̐ݒ�
		m_apScene2D[nCnt]->SetObjType(CScene::OBJTYPE_UI);

		// ������
		m_apScene2D[nCnt]->Init();
	}
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CBomUI::Uninit(void)
{
	// �I��
	Release();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CBomUI::Update(void)
{

}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CBomUI::Draw(void)
{
}
//******************************************************************************
// �{���̏������ݒ�
//******************************************************************************
void CBomUI::SetBomUI(int mBomPossesion)
{
	// �{���̏��������擾
	m_nBom_Posession = mBomPossesion;
	
	// ��������5�̏ꍇ
	if (m_nBom_Posession == POSESSION_MAX)
	{
		for (int nCount = INIT_INT; nCount < POSESSION_MAX; nCount++)
		{
			m_apScene2D[nCount]->SetRGBA(POSESSION_COLOR_VALUE);
		}
	}
	// ��������4�̏ꍇ
	if (m_nBom_Posession == POSESSION_4)
	{
		for (int nCount = INIT_INT; nCount < POSESSION_4; nCount++)
		{
			m_apScene2D[nCount]->SetRGBA(POSESSION_COLOR_VALUE);
		}
		m_apScene2D[4]->SetRGBA(NOT_POSESSION_COLOR_VALUE);
	}
	// ��������3�̏ꍇ
	if (m_nBom_Posession == POSESSION_3)
	{
		for (int nCount = INIT_INT; nCount < POSESSION_3; nCount++)
		{
			m_apScene2D[nCount]->SetRGBA(POSESSION_COLOR_VALUE);
		}
		m_apScene2D[3]->SetRGBA(NOT_POSESSION_COLOR_VALUE);
		m_apScene2D[4]->SetRGBA(NOT_POSESSION_COLOR_VALUE);
	}
	// ��������2�̏ꍇ
	if (m_nBom_Posession == POSESSION_2)
	{
		for (int nCount = INIT_INT; nCount < POSESSION_2; nCount++)
		{
			m_apScene2D[nCount]->SetRGBA(POSESSION_COLOR_VALUE);
		}
		m_apScene2D[2]->SetRGBA(NOT_POSESSION_COLOR_VALUE);
		m_apScene2D[3]->SetRGBA(NOT_POSESSION_COLOR_VALUE);
		m_apScene2D[4]->SetRGBA(NOT_POSESSION_COLOR_VALUE);
	}
	// ��������1�̏ꍇ
	if (m_nBom_Posession == POSESSION_1)
	{
			m_apScene2D[0]->SetRGBA(POSESSION_COLOR_VALUE);

			for (int nCount = POSESSION_1; nCount < MAX_BOM; nCount++)
			{
				m_apScene2D[nCount]->SetRGBA(NOT_POSESSION_COLOR_VALUE);
				m_apScene2D[nCount]->SetRGBA(NOT_POSESSION_COLOR_VALUE);
				m_apScene2D[nCount]->SetRGBA(NOT_POSESSION_COLOR_VALUE);
				m_apScene2D[nCount]->SetRGBA(NOT_POSESSION_COLOR_VALUE);
			}
	}
	// ��������0�̏ꍇ
	if (m_nBom_Posession == POSESSION_NONE)
	{
		for (int nCount = INIT_INT; nCount < MAX_BOM; nCount++)
		{
			m_apScene2D[nCount]->SetRGBA(NOT_POSESSION_COLOR_VALUE);
		}
	}
}
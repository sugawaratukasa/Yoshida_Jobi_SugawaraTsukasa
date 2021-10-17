//=============================================================================
//
// �^�C�g��Press_Enter [title_press_enter.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "game.h"
#include "light.h"
#include "title_press_enter.h"
#include "resource_manager.h"
#include "texture.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define POS		(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 1.3f,0.0f))	// �ʒu
#define SIZE	(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 4,0.0f))		// �T�C�Y
#define ADD_COL	(0.03f)														// �F�̉��Z�l
#define MAX_COL	(1.0f)														// �F�̍ő�l
#define MIN_COL	(0.0f)														// �F�̍ŏ��l

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTitlePress_Button::CTitlePress_Button(PRIORITY Priority) : CScene2D(Priority)
{
	m_bColor = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitlePress_Button::~CTitlePress_Button()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CTitlePress_Button * CTitlePress_Button::Create(void)
{
	// �������m��
	CTitlePress_Button *pPolygon = new CTitlePress_Button(PRIORITY_UI);

	// !nullcheck
	if (pPolygon != nullptr)
	{
		// ����������
		pPolygon->Init();

		return pPolygon;
	}

	return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTitlePress_Button::Init(void)
{
	// �e�N�X�`���̃|�C���擾
	CTexture *pTexture = GET_TEXTURE_PTR;

	// �e�N�X�`��
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_PRESS_BUTTON));

	// ����������
	CScene2D::Init(POS, SIZE);

	return S_OK;
}

//=============================================================================
// �X�V����l
//=============================================================================
void CTitlePress_Button::Update(void)
{
	// �`�揈��
	CScene2D::Update();
	// �F
	D3DXCOLOR col = GetColor();

	// false�̏ꍇ
	if (m_bColor == false)
	{
		// ���Z
		col.a -= ADD_COL;

		// �ŏ��ȉ��̏ꍇ
		if (col.a < MIN_COL)
		{
			// �ŏ��l��
			col.a = MIN_COL;

			// true��
			m_bColor = true;
		}
	}
	// true�̏ꍇ
	if (m_bColor == true)
	{
		// ���Z
		col.a += ADD_COL;

		// �ŏ��ȉ��̏ꍇ
		if (col.a > MAX_COL)
		{
			// �ŏ��l��
			col.a = MAX_COL;

			// true��
			m_bColor = false;
		}
	}

	// �F�ݒ�
	SetCol(col);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTitlePress_Button::Draw(void)
{
	// �`�揈��
	CScene2D::Draw();
}

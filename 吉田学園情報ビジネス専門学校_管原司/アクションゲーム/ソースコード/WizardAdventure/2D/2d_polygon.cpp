//******************************************************************************
// 2D_�|���S�� [2d_polygon.cpp]
// Author : �ǌ��i
//******************************************************************************
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "manager.h"
#include "joystick.h"
#include "ui_texture.h"
#include "2d_polygon.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define ROT			(D3DXVECTOR3(0.0f,0.0f,0.0f))		// ���� 
#define COL			(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// �F
#define BLACK_COL	(D3DXCOLOR(0.0f,0.0f,0.0f,0.5f))	// �F
#define ADD_ALPHA	(0.03f)								// ���Z
#define MIN_ALPHA	(0.1f)								// ���l�̍ŏ�
#define MAX_ALPHA	(1.0f)								// ���l�̍ő�
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
C2D_Polygon::C2D_Polygon(int nPriority) : CScene2D(nPriority)
{
	m_Type	 = TYPE_NONE;
	m_bColor = false;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
C2D_Polygon::~C2D_Polygon()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
C2D_Polygon * C2D_Polygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// C2D_Polygon�̃|�C���^
	C2D_Polygon *p2D_Polygon = NULL;

	// NULL�̏ꍇ
	if (p2D_Polygon == NULL)
	{
		// �������m��
		p2D_Polygon = new C2D_Polygon;

		// NULL�łȂ��ꍇ
		if (p2D_Polygon != NULL)
		{
			// ���ݒ�
			p2D_Polygon->SetPolygon(pos, ROT, size, COL);

			// ���
			p2D_Polygon->m_Type = type;

			switch (p2D_Polygon->m_Type)
			{
				// �e�N�X�`���Ȃ�
			case C2D_Polygon::TYPE_NONE:
				// �F�ݒ�
				p2D_Polygon->SetColor(BLACK_COL);
				break;

				// RESUME
			case C2D_Polygon::TYPE_RESUME:
				// �e�N�X�`���󂯓n��
				p2D_Polygon->BindTexture(CManager::GetUI_Texture()->GetTexture(CUI_Texture::TEX_TYPE_RESUME));
				// �F�ݒ�
				p2D_Polygon->SetColor(COL);
				break;

				// �R���g���[���[����
			case C2D_Polygon::TYPE_CONTROLS:
				// �e�N�X�`���󂯓n��
				p2D_Polygon->BindTexture(CManager::GetUI_Texture()->GetTexture(CUI_Texture::TEX_TYPE_CONTROLS));
				// �F�ݒ�
				p2D_Polygon->SetColor(COL);
				break;

				// EXIT
			case C2D_Polygon::TYPE_EXIT:
				// �e�N�X�`���󂯓n��
				p2D_Polygon->BindTexture(CManager::GetUI_Texture()->GetTexture(CUI_Texture::TEX_TYPE_EXIT));
				// �F�ݒ�
				p2D_Polygon->SetColor(COL);
				break;

				// GAMESTART
			case C2D_Polygon::TYPE_GAMESTART:
				// �e�N�X�`���󂯓n��
				p2D_Polygon->BindTexture(CManager::GetUI_Texture()->GetTexture(CUI_Texture::TEX_TYPE_GAMESTART));
				// �F�ݒ�
				p2D_Polygon->SetColor(COL);
				break;

				// TITLE
			case C2D_Polygon::TYPE_TITLE:
				// �e�N�X�`���󂯓n��
				p2D_Polygon->BindTexture(CManager::GetUI_Texture()->GetTexture(CUI_Texture::TEX_TYPE_TITLE));
				// �F�ݒ�
				p2D_Polygon->SetColor(COL);
				break;

				// �^�C�g���w�i
			case C2D_Polygon::TYPE_TITLE_BG:
				// �e�N�X�`���󂯓n��
				p2D_Polygon->BindTexture(CManager::GetUI_Texture()->GetTexture(CUI_Texture::TEX_TYPE_TITLE_BG));
				// �F�ݒ�
				p2D_Polygon->SetColor(COL);
				break;

				// PRESS_START
			case C2D_Polygon::TYPE_PRESS_START:
				// �e�N�X�`���󂯓n��
				p2D_Polygon->BindTexture(CManager::GetUI_Texture()->GetTexture(CUI_Texture::TEX_TYPE_PRESS_START));
				// �F�ݒ�
				p2D_Polygon->SetColor(COL);
				break;

				// RESULT
			case C2D_Polygon::TYPE_RESULT:
				// �e�N�X�`���󂯓n��
				p2D_Polygon->BindTexture(CManager::GetUI_Texture()->GetTexture(CUI_Texture::TEX_TYPE_RESULT));
				// �F�ݒ�
				p2D_Polygon->SetColor(COL);
				break;

				// MAGICUI
			case C2D_Polygon::TYPE_MAGIC_UI:
				// �e�N�X�`���󂯓n��
				p2D_Polygon->BindTexture(CManager::GetUI_Texture()->GetTexture(CUI_Texture::TEX_TYPE_MAGIC_UI));
				// �F�ݒ�
				p2D_Polygon->SetColor(COL);
				break;
			case C2D_Polygon::TYPE_CONTROLS_BG:
				// �e�N�X�`���󂯓n��
				p2D_Polygon->BindTexture(CManager::GetUI_Texture()->GetTexture(CUI_Texture::TEX_TYPE_CONTROLS_BG));
				// �F�ݒ�
				p2D_Polygon->SetColor(COL);
				break;
				// ��O
			default:
				break;
			}

			// �I�u�W�F�N�g�^�C�v�ݒ�
			p2D_Polygon->SetObjType(OBJTYPE_NOSTOP_UI);

			// ������
			p2D_Polygon->Init();
		}
	}
	// �|�C���^��Ԃ�
	return p2D_Polygon;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT C2D_Polygon::Init(void)
{
	// ������
	CScene2D::Init();
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void C2D_Polygon::Uninit(void)
{
	// �I��
	CScene2D::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void C2D_Polygon::Update(void)
{
	// �X�V
	CScene2D::Update();

	// �R���g���[���[�擾
	DIJOYSTATE js;
	js.lY = INIT_INT;
	js.lX = INIT_INT;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	// CONTROLS_BG�̏ꍇ
	if (m_Type == TYPE_CONTROLS_BG)
	{
		// NULL�łȂ��ꍇ	
		if (g_lpDIDevice != NULL)
		{
			// B,START,A�{�^�����������ꍇ
			if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_B) || 
				pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_START))
			{
				// �X�V
				pInputJoystick->Update();

				// �I��
				Uninit();
				return;
			}
		}
	}
	// PRESS_START�̏ꍇ
	if (m_Type == TYPE_PRESS_START)
	{
		// �F�擾
		D3DXCOLOR col = GetColor();

		// false�̏ꍇ
		if (m_bColor == false)
		{
			// ���l���Z
			col.a -= ADD_ALPHA;
			// 0.1�ȉ��̏ꍇ
			if (col.a <= MIN_ALPHA)
			{
				// 0.1f��
				col.a = MIN_ALPHA;

				// true�ɂ���
				m_bColor = true;
			}
		}
		else
		{
			// ���l���Z
			col.a += ADD_ALPHA;
			// 1.0f�ȏ�̏ꍇ
			if (col.a >= MAX_ALPHA)
			{
				// 1.0f��
				col.a = MAX_ALPHA;

				// false�ɂ���
				m_bColor = false;
			}
		}
		// �F�ݒ�
		SetColor(col);
	}
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void C2D_Polygon::Draw(void)
{
	// �`��֐�
	CScene2D::Draw();
}
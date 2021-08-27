//******************************************************************************
// ���[�j���O [warning.cpp]
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
#include "../Boss/boss.h"
#include "../Mode/game.h"
#include "warning.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define TEXTURE				( "data/Texture/UI/warning.png")				// �e�N�X�`��
#define BOSS_RESPAWN_COUNT	(50)											// �{�X�����J�E���g
#define COLOR_ADD_VALUE		(0.05f)											// �F���Z�l
#define COLOR_MAX_VALUE		(1.0f)											// �F�̍ő�l
#define COLOR_MIN_VALUE		(0.1f)											// �F�̍ŏ��l
#define COLOR				(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))				// �F�̒l
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPDIRECT3DTEXTURE9 CWarning::m_pTexture = NULL;
//******************************************************************************
// �e�N�X�`���ǂݍ���
//******************************************************************************
HRESULT CWarning::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE, &m_pTexture);
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���j��
//******************************************************************************
void CWarning::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CWarning::CWarning(int nPriority) : CScene2d(nPriority)
{
	m_bColor		= false;
	m_nWarnigCount	= INIT_INT;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CWarning::~CWarning()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CWarning * CWarning::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CWarning�N���X�̃|�C���^
	CWarning * pWarning;

	// �������m��
	pWarning = new CWarning;

	// �ʒu���W�ݒ�
	pWarning->SetPosition(pos);

	// �ʒu���W�ݒ�
	pWarning->SetSize(size);

	// ������
	pWarning->Init();

	// �|�C���^��Ԃ�
	return nullptr;
}

//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CWarning::Init(void)
{
	// �J���[�ݒ�
	SetRGBA(COLOR);

	// �e�N�X�`���󂯓n��
	BindTexture(m_pTexture);

	// ������
	CScene2d::Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CWarning::Uninit(void)
{
	//�I��
	CScene2d::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CWarning::Update(void)
{
	// �X�V
	CScene2d::Update();

	// �J���[�擾
	D3DXCOLOR col = GetRGBA();

	// false�̏ꍇ
	if (m_bColor == false)
	{
		// ���l���Z
		col.a -= COLOR_ADD_VALUE;
		// 0.1�ȉ��ɂȂ����ꍇ
		if (col.a <= COLOR_MIN_VALUE)
		{
			// true�ɂ���
			m_bColor = true;
		}
	}
	// true�̏ꍇ
	else
	{
		// ���l���Z
		col.a += COLOR_ADD_VALUE;
		// 1.0f�ȏ�̏ꍇ
		if (col.a >= COLOR_MAX_VALUE)
		{
			// false�ɂ���
			m_bColor = false;
		}
		// �C���N�������g
		m_nWarnigCount++;
	}
	// 50�̏ꍇ
	if (m_nWarnigCount == BOSS_RESPAWN_COUNT)
	{
		// �{�X����
		CGame::CreateBoss();

		// �I��
		Uninit();
		// ���̏�����ʂ�Ȃ��悤��
		return;
	}

	// �J���[�ݒ�
	SetRGBA(col);
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CWarning::Draw(void)
{
	// �`��
	CScene2d::Draw();
}
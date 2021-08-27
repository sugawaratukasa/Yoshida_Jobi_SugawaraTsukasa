//******************************************************************************
// ���C�t���� [life.cpp]
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
#include "../Player/player.h"
#include "life.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define LIFE_TEXTURE		("data/Texture/UI/PlayerLife.png")	// �e�N�X�`��
#define COLOR_VALUE			(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// �F�̒l
#define DAMAGE_COLOR_VALUE	(D3DXCOLOR(0.3f,0.3f,0.3f,1.0f))	// ���C�t�������Ă��鎞�̐F�̒l
#define INTERVAL_VALUE		(50.0f)								// ���C�t�̊Ԋu�̒l
#define LIFE_VALUE_MAX		(3)									// ���C�t�̍ő�l
#define LIFE_VALUE_2		(2)									// ���C�t�̐��l2
#define LIFE_VALUE_1		(1)									// ���C�t�̐��l1
#define LIFE_VALUE_MIN		(0)									// ���C�t�̍ŏ��l
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPDIRECT3DTEXTURE9 CLife::m_pTexture = NULL;
//******************************************************************************
// �e�N�X�`���ǂݍ���
//******************************************************************************
HRESULT CLife::Load(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	// �e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, LIFE_TEXTURE, &m_pTexture);
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���j��
//******************************************************************************
void CLife::Unload(void)
{
	// �e�N�X�`���j��
	m_pTexture->Release();
	m_pTexture = NULL;
}
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CLife::CLife(int nPriority) : CScene(nPriority)
{
	memset(m_apScene2D, 0, sizeof(m_apScene2D));
	m_pos		= INIT_D3DXVECTOR3;
	m_size		= INIT_D3DXVECTOR3;
	m_nNumLife	= INIT_INT;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CLife::~CLife()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CLife * CLife::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CLife�N���X�̃|�C���^
	CLife * pLife;

	// �������m��
	pLife = new CLife;

	// �ʒu���W���
	pLife->m_pos = pos;

	// �T�C�Y���
	pLife->m_size = size;

	// ������
	pLife->Init();

	// �|�C���^��Ԃ�
	return pLife;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CLife::Init()
{
	// ���C�t����3��
	m_nNumLife = LIFE_VALUE_MAX;

	// �ő吔���J��Ԃ�

	for (int nCnt = INIT_INT; nCnt < MAX_LIFE; nCnt++)
	{
		//�@�������m��
		m_apScene2D[nCnt] = new CScene2d(OBJTYPE_UI);

		// �ʒu���W�ݒ�
		m_apScene2D[nCnt]->SetPosition(D3DXVECTOR3((m_pos.x + INTERVAL_VALUE * nCnt), m_pos.y, m_pos.z));

		// �T�C�Y�ݒ�
		m_apScene2D[nCnt]->SetSize(D3DXVECTOR3(m_size));

		// �J���[�ݒ�
		m_apScene2D[nCnt]->SetRGBA(COLOR_VALUE);

		// �e�N�X�`���󂯓n��
		m_apScene2D[nCnt]->BindTexture(m_pTexture);

		//�I�u�W�F�N�g�^�C�v�̐ݒ�
		m_apScene2D[nCnt]->SetObjType(CScene::OBJTYPE_UI);

		// ������
		m_apScene2D[nCnt]->Init();
	}
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CLife::Uninit(void)
{
	// �I��
	Release();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CLife::Update(void)
{

}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CLife::Draw(void)
{
}
//******************************************************************************
// ���C�t���Z�֐�
//******************************************************************************
void CLife::AddLife(int nLife)
{
	m_nNumLife = nLife;
	// ���C�t�ݒ�
	SetLife();
}
//******************************************************************************
// ���C�t���Z�֐�
//******************************************************************************
void CLife::HitDamage(int Damage)
{
	m_nNumLife -= Damage;
	// ���C�t�ݒ�
	SetLife();
}
//******************************************************************************
// ���C�t�ݒ�֐�
//******************************************************************************
void CLife::SetLife(void)
{
	// ���C�t��3�̏ꍇ
	if (m_nNumLife == LIFE_VALUE_MAX)
	{
		m_apScene2D[0]->SetRGBA(COLOR_VALUE);
		m_apScene2D[1]->SetRGBA(COLOR_VALUE);
		m_apScene2D[2]->SetRGBA(COLOR_VALUE);
	}
	// ���C�t��2�̏ꍇ
	if (m_nNumLife == LIFE_VALUE_2)
	{
		m_apScene2D[2]->SetRGBA(DAMAGE_COLOR_VALUE);
	}
	// ���C�t��1�̏ꍇ
	if (m_nNumLife == LIFE_VALUE_1)
	{
		m_apScene2D[1]->SetRGBA(DAMAGE_COLOR_VALUE);
	}
	// ���C�t��0�̏ꍇ
	if (m_nNumLife == LIFE_VALUE_MIN)
	{
		m_apScene2D[0]->SetRGBA(DAMAGE_COLOR_VALUE);
	}
}

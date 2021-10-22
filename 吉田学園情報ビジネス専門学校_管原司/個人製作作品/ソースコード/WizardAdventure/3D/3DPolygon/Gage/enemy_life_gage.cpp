//******************************************************************************
// �G�̃��C�t�Q�[�W [enemy_life_gage.cpp]
// Author : �ǌ��i
//******************************************************************************
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "manager.h"
#include "ui_texture.h"
#include "../3D/Model/Enemy/enemy.h"
#include "3d_gage_back.h"
#include "enemy_life_gage.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define POS			(D3DXVECTOR3(EnemyPos.x,EnemyPos.y + 40.0f, EnemyPos.z - 10.0f))	// �ʒu
#define SIZE		(D3DXVECTOR3(30.0f,2.5f,0.0f))										// �T�C�Y
#define SIZE_BACK	(D3DXVECTOR3(SIZE.x * 1.01f, SIZE.y * 1.15f, SIZE.z))				// �Q�[�W�̔w�i�T�C�Y
#define ROT			(D3DXVECTOR3(0.0f,0.0f,0.0f))										// ����
#define COL			(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))									// �F
#define MIN_LIFE	(0)																	// ���C�t�̍ŏ��l
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CEnemy_Life_Gage::CEnemy_Life_Gage(int nPriority) : C3D_Gage(nPriority)
{
	m_pEnemy		= NULL;
	m_p3D_Gage_Back = NULL;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CEnemy_Life_Gage::~CEnemy_Life_Gage()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CEnemy_Life_Gage * CEnemy_Life_Gage::Create(D3DXVECTOR3 pos, CEnemy *pEnemy)
{
	// CLife_Gage�̃|�C���^
	CEnemy_Life_Gage *pEnemy_Life_Gage = NULL;

	// NULL�̏ꍇ
	if (pEnemy_Life_Gage == NULL)
	{
		// �������m��
		pEnemy_Life_Gage = new CEnemy_Life_Gage;

		// NULL�łȂ��ꍇ
		if (pEnemy_Life_Gage != NULL)
		{
			// ���
			pEnemy_Life_Gage->m_pEnemy = pEnemy;

			// ���C�t
			int nLife = pEnemy_Life_Gage->m_pEnemy->GetLife();

			// ���ݒ�
			pEnemy_Life_Gage->SetGage(pos, ROT, SIZE, COL, nLife);

			// ������
			pEnemy_Life_Gage->Init();
		}
	}
	// �|�C���^��Ԃ�
	return pEnemy_Life_Gage;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CEnemy_Life_Gage::Init(void)
{
	// ������
	C3D_Gage::Init();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	// �Q�[�W�w�i����
	m_p3D_Gage_Back = C3D_Gage_Back::Create(pos, SIZE_BACK);
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CEnemy_Life_Gage::Uninit(void)
{
	// �I��
	C3D_Gage::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CEnemy_Life_Gage::Update(void)
{
	// �X�V
	C3D_Gage::Update();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	// �G�̈ʒu�擾
	D3DXVECTOR3 EnemyPos = m_pEnemy->GetPos();

	// ���C�t�擾
	int nLife = m_pEnemy->GetLife();

	// ���C�t�ݒ�
	SetGageNum(nLife);

	// �ʒu���
	pos = POS;

	// �ʒu
	m_p3D_Gage_Back->SetPosition(pos);

	// �ʒu�ݒ�
	SetPosition(pos);

	// ���C�t��0�ȉ��ɂȂ����ꍇ
	if (nLife <= MIN_LIFE)
	{
		// �j��
		m_p3D_Gage_Back->Uninit();

		// �I��
		Uninit();
		return;
	}
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CEnemy_Life_Gage::Draw(void)
{
	// �`��
	C3D_Gage::Draw();
}
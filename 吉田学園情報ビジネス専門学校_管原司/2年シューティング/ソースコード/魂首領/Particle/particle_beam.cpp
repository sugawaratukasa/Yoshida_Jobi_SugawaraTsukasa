//******************************************************************************
// �r�[���������������̃p�[�e�B�N�� [particle_beam.cpp]
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
#include "particle.h"
#include "particle_beam.h"
#include "particle_circle.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define LIFE_VALUE			(5)																							// ���C�t�l
#define MIN_LIFE			(0)																							// ���C�t�̍ŏ��l
#define EFFECT_SIZE			(D3DXVECTOR3(30.0f,30.0f,0.0f))																// �T�C�Y
#define EFFECT_ROT			(D3DXVECTOR3(0.0f,0.0f,0.0f))																// ����
#define EFFECT_COL			(D3DXCOLOR(0.0f,0.5f,1.0f,1.0f))															// �F
#define SPEED_DIVIDE		(100)																						// �ړ�
#define EFFECT_RANDUM_COUNT	(10)																						// �G�t�F�N�g�J�E���g�����_��
#define EFFECT_COUNT		(2)																							// �G�t�F�N�g�J�E���g
#define RANDUM_ANGLE		(270 - 90)																					// �p�x�����_��
#define RANDUM_SPEED		(1000 - 500)																				// �ړ��ʃ����_��
#define EFFECT_MOVE			(D3DXVECTOR3(cosf(D3DXToRadian(fAngle))*fSpeed, sinf(D3DXToRadian(fAngle))*fSpeed, 0.0f))	// �ړ���
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CParticle_Beam::CParticle_Beam(int nPrirority) : CParticle(nPrirority)
{
	m_nLife = INIT_INT;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CParticle_Beam::~CParticle_Beam()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CParticle_Beam * CParticle_Beam::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType)
{
	// CParticle_Beam�N���X�̃|�C���^
	CParticle_Beam *pParticle_Beam;

	// �������m��
	pParticle_Beam = new CParticle_Beam;

	// �p�[�e�B�N�����ݒ�
	pParticle_Beam->SetParticle(pos, size, rot, col, TexType);

	// ������
	pParticle_Beam->Init();

	// �|�C���^��Ԃ�
	return pParticle_Beam;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CParticle_Beam::Init(void)
{
	// ������
	CParticle::Init();

	// ���C�t�ݒ�
	m_nLife = LIFE_VALUE;

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CParticle_Beam::Uninit(void)
{
	// �I��
	CParticle::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CParticle_Beam::Update(void)
{
	// �X�V
	CParticle::Update();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();
	int nNum = rand() % EFFECT_RANDUM_COUNT;

	if (nNum == EFFECT_COUNT)
	{
		// �p�x��360�x�����_����
		float fAngle = float(rand() % RANDUM_ANGLE);

		// �X�s�[�h��10����-10�Ń����_����
		float fSpeed = float(rand() % RANDUM_SPEED);
		fSpeed = fSpeed / SPEED_DIVIDE;

		CParticle_Circle::Create(pos, EFFECT_SIZE, EFFECT_ROT, EFFECT_COL, EFFECT_MOVE, CParticle::TEX_TYPE_CIRCLE);
	}
	// �f�N�������g
	m_nLife--;

	// 0�ȉ��̏ꍇ
	if (m_nLife <= MIN_LIFE)
	{
		// �I��
		Uninit();
		return;
	}
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CParticle_Beam::Draw(void)
{
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

	// ���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �`��
	CParticle::Draw();

	// ���ɖ߂�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//******************************************************************************
// �p�[�e�B�N������ [particle_circle.cpp]
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
#include "particle_circle.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define EFFECT_ROT				(D3DXVECTOR3(0.0f,0.0f,sinf(fAngle)))							// ����
#define EFFECT_MOVE				(D3DXVECTOR3(cosf(D3DXToRadian(fAngle))*fSpeed, sinf(D3DXToRadian(fAngle))*fSpeed, 0.0f))	// �ړ���
#define SCALE_MIN_VALUE			(0.0f)															// �g�嗦�ŏ��l
#define RANDUM_ANGLE_MAX		(360)															// �ʓx�ő�l
#define RANDUM_ANGLE_MIN		(180)															// �ʓx�ŏ��l
#define RANDUM_SPEED_MAX		(1500)															// �ړ��ʂ̍ő�l
#define RANDUM_SPEED_MIN		(1000)															// �ړ��ʂ̍ŏ��l
#define SPEED_DIVIDE			(100)															// �ړ��ʏ��Z�l
#define RANDUM_COLOR			(255)															// �F�����_��
#define A_COLOR					(255)															// ���l
#define SUB_SCALE_VALUE			(0.03f)															// �g�嗦���Z��
#define SUBTRACT_COLOR_VALUE	(0.01f)															// �J���[���Z��
#define COLOR_MIN_VALUE			(0.0f)															// �J���[�ŏ��l
#define MAX_PARTICLE			(3)																// �����ő吔

#define RANDUM_ANGLE	(RANDUM_ANGLE_MAX - RANDUM_ANGLE_MIN)									// �ʓx�����_��
#define RANDUM_SPEED	(RANDUM_SPEED_MAX - RANDUM_SPEED_MIN)									// �ړ��ʃ����_��
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CParticle_Circle::CParticle_Circle(int nPrirority) : CParticle(nPrirority)
{
	m_move = INIT_D3DXVECTOR3;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CParticle_Circle::~CParticle_Circle()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CParticle_Circle * CParticle_Circle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 move, CParticle::TEX_TYPE TexType)
{
	// CParticle_Explosion�N���X�̃|�C���^
	CParticle_Circle *pParticle_Explosion;

	// �������m��
	pParticle_Explosion = new CParticle_Circle;

	// �p�[�e�B�N�����ݒ�
	pParticle_Explosion->SetParticle(pos, size, rot, col, TexType);

	// �ړ��ʑ��
	pParticle_Explosion->m_move = move;

	// ������
	pParticle_Explosion->Init();

	// �|�C���^��Ԃ�
	return pParticle_Explosion;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CParticle_Circle::Init(void)
{
	// ������
	CParticle::Init();

	return S_OK;

}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CParticle_Circle::Uninit(void)
{
	// �I��
	CParticle::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CParticle_Circle::Update(void)
{
	// �X�V
	CParticle::Update();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �F�擾
	D3DXCOLOR col = GetRGBA();

	// �g�嗦�擾
	float fScale = GetScale();

	// �g�嗦���Z�l
	float fSubScale = SUB_SCALE_VALUE;

	// �J���[���Z�l
	float fMinColor = SUBTRACT_COLOR_VALUE;

	// �T�C�Y���Z
	fScale -= fSubScale;

	// �J���[�l���Z
	col.a -= fMinColor;
	col.r -= fMinColor;
	col.g -= fMinColor;

	// �T�C�Y�ݒ�
	SetScale(fScale);

	// �F�ݒ�
	SetRGBA(col);

	// �ʒu�X�V
	pos += m_move;

	// �ʒu���W�ݒ�
	SetPosition(pos);

	// �g�嗦��0.0f�ȉ��̏ꍇ
	if (fScale <= SCALE_MIN_VALUE)
	{
		// �I��
		Uninit();
		return;
	}
	// �J���[��0.0f�ȉ��̏ꍇ
	if (col.a <= COLOR_MIN_VALUE)
	{
		Uninit();
		return;
	}
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CParticle_Circle::Draw(void)
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
//******************************************************************************
// ���������֐�
//******************************************************************************
void CParticle_Circle::CreateParticleEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nCreateCount)
{
		// 5��J��Ԃ�
		for (int nCount = INIT_INT; nCount < nCreateCount; nCount++)
		{
			// �p�x��360�x�����_����
			float fAngle = float(rand() % RANDUM_ANGLE_MAX);

			// �X�s�[�h��10����-10�Ń����_����
			float fSpeed = float(rand() % RANDUM_SPEED);
			fSpeed = fSpeed / SPEED_DIVIDE;

			// �F�������_��
			int fColorRed = int(rand() % RANDUM_COLOR);
			int fColorGreen = int(rand() % RANDUM_COLOR);
			int fColorBlue = int(rand() % RANDUM_COLOR);
			int fColorA	= A_COLOR;

			// �F
			D3DXCOLOR color = D3DCOLOR_RGBA(fColorRed, fColorGreen, fColorBlue, fColorA);

			// ����
			Create(pos,
				size,
				EFFECT_ROT,
				color,
				EFFECT_MOVE,
				CParticle::TEX_TYPE_CIRCLE);
		}
}
//******************************************************************************
// ���������֐�
//******************************************************************************
void CParticle_Circle::PlayerDeathEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nCreateCount)
{
	// 5��J��Ԃ�
	for (int nCount = INIT_INT; nCount < nCreateCount; nCount++)
	{
		// �p�x��360�x�����_����
		float fAngle = float(rand() % RANDUM_ANGLE);

		// �X�s�[�h��10����-10�Ń����_����
		float fSpeed = float(rand() % RANDUM_SPEED);
		fSpeed = fSpeed / SPEED_DIVIDE;

		// �F
		D3DXCOLOR col = D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f);
		// ����
		Create(pos,
			size,
			EFFECT_ROT,
			col,
			EFFECT_MOVE,
			CParticle::TEX_TYPE_CIRCLE);
	}
}
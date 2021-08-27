//******************************************************************************
// �������� [particle_explosion.cpp]
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
#include "particle_explosion.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define EFFECT_ROT				(D3DXVECTOR3(0.0f,0.0f,sinf(fAngle)))							// ����
#define EFFECT_MOVE				(D3DXVECTOR3(fSpeed, sinf(D3DXToRadian(fAngle))*fSpeed, 0.0f))	// �ړ���
#define ENEMY_EXPLOSION_COLOR	(D3DCOLOR_RGBA(255, 150, 0, 255))								// �J���[(��)
#define PLAYER_EXPLOSION_COLOR	(D3DCOLOR_RGBA(0, 200, 255, 255))								// �J���[(��)
#define RANDUM_ANGLE_MAX		(360)															// �ʓx�ő�l
#define RANDUM_ANGLE_MIN		(180)															// �ʓx�ŏ��l
#define RANDUM_SPEED_MAX		(200)															// �ړ��ʂ̍ő�l
#define RANDUM_SPEED_MIN		(100)															// �ړ��ʂ̍ŏ��l
#define SPEED_DIVIDE			(100)															// �ړ��ʏ��Z�l
#define SCALE_MIN_VALUE			(0.0f)															// �g�嗦�ŏ��l
#define ADD_SCALE_VALUE			(1.5f)															// �g�嗦���Z��
#define SUBTRACT_COLOR_VALUE	(0.04f)															// �J���[���Z��
#define COLOR_MIN_VALUE			(0.0f)															// �J���[�ŏ��l
#define MAX_EXPLOSION			(10)															// �����ő吔
#define SIZE_MUT				(1.5f)															// �����̃T�C�Y�̔{��
#define RANDUM_ANGLE	(RANDUM_ANGLE_MAX - RANDUM_ANGLE_MIN)									// �ʓx�����_��
#define RANDUM_SPEED	(RANDUM_SPEED_MAX - RANDUM_SPEED_MIN)									// �ړ��ʃ����_��
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CParticle_Explosion::CParticle_Explosion(int nPrirority) : CParticle(nPrirority)
{
	m_move = INIT_D3DXVECTOR3;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CParticle_Explosion::~CParticle_Explosion()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CParticle_Explosion * CParticle_Explosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 move, CParticle::TEX_TYPE TexType)
{
	// CParticle_Explosion�N���X�̃|�C���^
	CParticle_Explosion *pParticle_Explosion;

	// �������m��
	pParticle_Explosion = new CParticle_Explosion;

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
HRESULT CParticle_Explosion::Init(void)
{
	// ������
	CParticle::Init();

	return S_OK;

}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CParticle_Explosion::Uninit(void)
{
	// �I��
	CParticle::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CParticle_Explosion::Update(void)
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
	float fAddScale = ADD_SCALE_VALUE;

	// �J���[���Z�l
	float fMinColor = SUBTRACT_COLOR_VALUE;

	// �T�C�Y���Z
	fScale += fAddScale;

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
void CParticle_Explosion::Draw(void)
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
// �������������֐�
//******************************************************************************
void CParticle_Explosion::CreateExplosionEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	TYPE Type = type;
	switch (Type)
	{
	case TYPE_ENEMY:
		// 15��J��Ԃ�
		for (int nCount = INIT_INT; nCount < MAX_EXPLOSION; nCount++)
		{
			// �p�x��360�x�����_����
			float fAngle = float(rand() % RANDUM_ANGLE);
			// �X�s�[�h��10����-10�Ń����_����
			float fSpeed = float(rand() % RANDUM_SPEED);
			fSpeed = fSpeed / SPEED_DIVIDE;

			// ����
			Create(pos,
				size * SIZE_MUT,
				EFFECT_ROT,
				ENEMY_EXPLOSION_COLOR,
				EFFECT_MOVE,
				CParticle::TEX_TYPE_EXPLOSION);
		}
		break;

	case TYPE_PLAYER:
		// 15��J��Ԃ�
		for (int nCount = INIT_INT; nCount < MAX_EXPLOSION; nCount++)
		{
			// �p�x��360�x�����_����
			float fAngle = float(rand() % RANDUM_ANGLE);
			// �X�s�[�h��10����-10�Ń����_����
			float fSpeed = float(rand() % RANDUM_SPEED);
			fSpeed = fSpeed / SPEED_DIVIDE;
			
			// ����
			Create(pos,
				size * SIZE_MUT,
				EFFECT_ROT,
				PLAYER_EXPLOSION_COLOR,
				EFFECT_MOVE,
				CParticle::TEX_TYPE_EXPLOSION);
		}
		break;
	}
}
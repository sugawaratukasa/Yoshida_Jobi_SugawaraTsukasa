//******************************************************************************
// �{�� [bom.h]
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
#include "../Mode/game.h"
#include "bullet.h"
#include "../Enemy/enemy.h"
#include "bom.h"
#include "../UI/score.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define ANIM_COUNT				(4)		// �A�j���[�V�����J�E���g
#define INIT_ANIM_COUNT			(0)		// �A�j���[�V�����J�E���g������
#define PATTERN_COUNT			(4)		// �p�^�[���J�E���g
#define PATTERN_COUNT2			(5)		// �p�^�[���J�E���g2
#define PATTERN_COUNT_MAX		(10)	// �p�^�[���J�E���g�ő�l
#define INIT_TEX				(0.0f)	// �e�N�X�`������
#define TEX_X					(0.2f)	// �e�N�X�`��X
#define TEX_X2					(0.5f)	// �e�N�X�`��X2
#define TEX_Y					(0.5f)	// �e�N�X�`��Y
#define TEX_Y2					(1.0f)	// �e�N�X�`��Y2
#define ENEMY_DAMAGE			(100)	// �G�ɗ^����_���[�W
#define ADD_SCORE				(100)	// ���Z�X�R�A
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CBom::CBom(int nPriority) : CBullet(nPriority)
{
	m_nPatternCount = INIT_INT;
	m_nAnimCount	= INIT_INT;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CBom::~CBom()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CBom * CBom::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, CBullet::TEX_TYPE textype)
{
	// CNormal_Bullet�|�C���^
	CBom * pBom;

	// �������m��
	pBom = new CBom;

	// �e�̏��ݒ�
	pBom->SetBullet(pos, rot, size, D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), textype, CScene::OBJTYPE_PLAYER_BULLET);

	// �e�N�X�`���ݒ�
	pBom->SetTexture(0.0f, 0.5f, 0.2f, 1.0f);

	// ������
	pBom->Init();

	// �|�C���^��Ԃ�
	return pBom;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CBom::Init(void)
{
	// ������
	CBullet::Init();

	// �e�N�X�`���ݒ�
	SetTexture(m_nPatternCount * TEX_X, INIT_TEX, TEX_X, TEX_Y);

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CBom::Uninit(void)
{
	// �I��
	CBullet::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CBom::Update(void)
{
	// �X�V
	CBullet::Update();

	// �q�b�g����
	HitEnemy();

	// �J�E���g�C���N�������g
	m_nAnimCount++;

	//�J�E���g��4�ȏ�ɂȂ�����
	if (m_nAnimCount > ANIM_COUNT)
	{
		// �J�E���g��0��
		m_nAnimCount = INIT_ANIM_COUNT;

		// �p�^�[����4�ȉ��̏ꍇ
		if (m_nPatternCount <= PATTERN_COUNT)
		{
			// �e�N�X�`���ݒ�
			SetTexture(m_nPatternCount * TEX_X, INIT_TEX, TEX_X, TEX_Y);
		}
		// �p�^�[����5�ȏ�̏ꍇ
		if (m_nPatternCount >= PATTERN_COUNT2)
		{
			// �e�N�X�`���̐ݒ�
			SetTexture(m_nPatternCount * TEX_X, TEX_X2, TEX_X, TEX_Y2);

		}
		// �p�^�[���̃C���N�������g
		m_nPatternCount++;
	}
	// �p�^�[����10�ȏ�ɂȂ�����
	if (m_nPatternCount >= PATTERN_COUNT_MAX)
	{
		// �I������
		Uninit();
		return;
	}
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CBom::Draw(void)
{
	// �`��
	CBullet::Draw();
}
//******************************************************************************
// �q�b�g����
//******************************************************************************
void CBom::HitEnemy(void)
{
	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// �X�R�A�̎擾
	CScore * pScore = CGame::GetScore();

	// CScene�^�̃|�C���^
	CScene *pScene = NULL;

	// �G�̔���
	do
	{
		// �I�u�W�F�^�C�v���G�̏ꍇ
		pScene = GetScene(OBJTYPE_ENEMY);

		// NULL�`�F�b�N
		if (pScene != NULL)
		{
			// �I�u�W�F�^�C�v�擾
			OBJTYPE objType = pScene->GetObjType();
			// �I�u�W�F�N�g�^�C�v���G
			if (objType == OBJTYPE_ENEMY)
			{
				// ���W�ƃT�C�Y�擾
				D3DXVECTOR3 EnemyPos = ((CEnemy*)pScene)->GetPosition();
				D3DXVECTOR3 EnemySize = ((CEnemy*)pScene)->GetSize();

				// �����蔻��
				if (Collision(pos, EnemyPos, size, EnemySize) == true)
				{
					// �G�Ƀ_���[�W��^����
					((CEnemy*)pScene)->HitEnemy(ENEMY_DAMAGE);
					// �X�R�A���Z
					pScore->AddScore(ADD_SCORE);
				}
			}
		}
	} while (pScene != NULL);


	// �G�̒e�̔���
	do
	{
		// �I�u�W�F�^�C�v���G�̏ꍇ
		pScene = GetScene(OBJTYPE_ENEMY_BULLET);

		// NULL�`�F�b�N
		if (pScene != NULL)
		{
			// �I�u�W�F�^�C�v�擾
			OBJTYPE objType = pScene->GetObjType();
			// �I�u�W�F�N�g�^�C�v���G
			if (objType == OBJTYPE_ENEMY_BULLET)
			{
				// ���W�ƃT�C�Y�擾
				D3DXVECTOR3 Enemy_Bullet_Pos = ((CBullet*)pScene)->GetPosition();
				D3DXVECTOR3 Enemy_Bullet_Size = ((CBullet*)pScene)->GetSize();

				// �����蔻��
				if (Collision(pos, Enemy_Bullet_Pos, size, Enemy_Bullet_Size) == true)
				{
					// �G�Ƀ_���[�W��^����
					((CBullet*)pScene)->Uninit();
					// �X�R�A���Z
					pScore->AddScore(ADD_SCORE);
				}
			}
		}
	} while (pScene != NULL);
}
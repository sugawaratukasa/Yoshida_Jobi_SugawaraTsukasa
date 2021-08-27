//******************************************************************************
// �G�H��[ghost.cpp]
// Author : �ǌ� �i
//******************************************************************************

//******************************************************************************
//�C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "../3D/3DPolygon/scene3d.h"
#include "../3D/Model/model.h"
#include "../3D/Model/player.h"
#include "../3D/3DPolygon/Particle/Particle_Emitter/particle_emitter.h"
#include "../3D/3DPolygon/Particle/magic.h"
#include "../3D/3DPolygon/Gage/enemy_life_gage.h"
#include "ghost.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define POS			(D3DXVECTOR3(pos.x,pos.y + 15.0f,pos.z - 8.0f))						// �ʒu
#define ATTACK_POS	(D3DXVECTOR3(pos.x,pos.y + 15.0f,pos.z))							// �ʒu
#define ROT			(D3DXVECTOR3(0.0f,0.0f,0.0f))										// ����
#define RIGHT_ROT	(D3DXVECTOR3(0.0f,D3DXToRadian(0.0f),0.0f))							// �E����
#define LEFT_ROT	(D3DXVECTOR3(0.0f,D3DXToRadian(180.0f),0.0f))						// ������
#define MAGIC_MOVE	(D3DXVECTOR3(cosf(fAngle) * 2.0f, sinf(fAngle) * 2.0f, 0.0f))		// ���@�̈ړ�
#define ATTACKCOUNT	(300)																// �U���J�E���g
#define REMAINDER	(0)																	// �]��
#define MAX_LIFE	(100)																// ���C�t�̍ő吔
#define ADD_ROT		(0.2f)																// ����
//******************************************************************************
//�ÓI�����o�ϐ�
//******************************************************************************

//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CGhost::CGhost(int nPriority) : CEnemy(nPriority)
{
	m_pParticleEmitter	= NULL;
	m_Type				= TYPE_NONE;
	m_nAttackCount		= INIT_INT;
	m_Rot				= ROT_RIGHT;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CGhost::~CGhost()
{

}
//******************************************************************************
// �����֐�
//******************************************************************************
CGhost * CGhost::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// CGhost�̃|�C���^
	CGhost *pGhost = NULL;

	// NULL�̏ꍇ
	if (pGhost == NULL)
	{
		// �������m��
		pGhost = new CGhost;

		// NULL�łȂ��ꍇ
		if (pGhost != NULL)
		{
			// ���ݒ�
			pGhost->SetEnemy(pos, ROT, size, MAX_LIFE);

			// ��ޑ��
			pGhost->m_Type = type;

			// �I�u�W�F�N�g�^�C�v�ݒ�
			pGhost->SetObjType(OBJTYPE_ENEMY);

			// ������
			pGhost->Init();

			// ����
			CEnemy_Life_Gage::Create(pos, pGhost);
		}
	}
	// �|�C���^��Ԃ�
	return pGhost;
}
//******************************************************************************
// ����������
//******************************************************************************
HRESULT CGhost::Init(void)
{
	// ������
	CEnemy::Init();

	// �ʒu
	D3DXVECTOR3 pos = GetPos();

	// FIRE�̏ꍇ
	if (m_Type == TYPE_FIRE)
	{
		// ���ˑ̐���
		CParticle_Emitter::Create(POS, CParticle_Emitter::TYPE_FIRE_CREATE);

		// ���ˑ̐���
		m_pParticleEmitter = CParticle_Emitter::Create(POS, CParticle_Emitter::TYPE_FIRE_GHOST);
	}
	// ICE�̏ꍇ
	if (m_Type == TYPE_ICE)
	{
		// ���ˑ̐���
		CParticle_Emitter::Create(POS, CParticle_Emitter::TYPE_ICE_CREATE);

		// ���ˑ̐���
		m_pParticleEmitter = CParticle_Emitter::Create(POS, CParticle_Emitter::TYPE_ICE_GHOST);
	}

	return S_OK;
}
//******************************************************************************
// �I������
//******************************************************************************
void CGhost::Uninit(void)
{
	// �I��
	CEnemy::Uninit();
}
//******************************************************************************
// �X�V����
//******************************************************************************
void CGhost::Update(void)
{
	// �X�V
	CEnemy::Update();

	// ��Ԏ擾
	int nState = CEnemy::GetState();

	// ���S��Ԃ̏ꍇ
	if (nState == STATE_DEAD)
	{
		// �j��
		m_pParticleEmitter->Uninit();
	}

	// �C���N�������g
	m_nAttackCount++;

	// 200�J�E���g����
	if (m_nAttackCount % ATTACKCOUNT == REMAINDER)
	{
		// �U��
		Attack();
	}

	// ����
	Rot();

	// �ʒu�퓗
	D3DXVECTOR3 pos = GetPos();

	// �ʒu�ݒ�
	m_pParticleEmitter->SetPos(POS);

	// �ʒu�ݒ�
	SetPos(pos);
}

//******************************************************************************
// �`�揈��
//******************************************************************************
void CGhost::Draw(void)
{
	// �`��
	CEnemy::Draw();
}
//******************************************************************************
// �U������
//******************************************************************************
void CGhost::Attack(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// CScene�̃|�C���^
	CScene *pScene = NULL;

	// �v���C���[�̈ʒu
	D3DXVECTOR3 PlayerPos;
	// �v���C���[�擾
	do
	{
		// �v���C���[�̃|�C���^�擾
		pScene = GetScene(OBJTYPE_PLAYER);

		// NULL�łȂ��ꍇ
		if (pScene != NULL)
		{
			// �I�u�W�F�N�g�^�C�v�擾
			OBJTYPE objtype = pScene->GetObjType();

			// �I�u�W�F�N�g�^�C�v�v���C���[�̏ꍇ
			if (objtype == OBJTYPE_PLAYER)
			{
				// �ʒu�擾
				PlayerPos.x = ((CPlayer*)pScene)->GetMtxWorld(CPlayer::PARTS_UNDER_BODY)._41;
				PlayerPos.y = ((CPlayer*)pScene)->GetMtxWorld(CPlayer::PARTS_UNDER_BODY)._42;
				PlayerPos.z = ((CPlayer*)pScene)->GetMtxWorld(CPlayer::PARTS_UNDER_BODY)._43;
			}
		}
		// NULL�ɂȂ�܂ŌJ��Ԃ�
	} while (pScene != NULL);

	// �p�x�Z�o
	float fAngle = atan2f(PlayerPos.y - pos.y, PlayerPos.x - pos.x);

	// FIRE�̏ꍇ
	if (m_Type == TYPE_FIRE)
	{
		// �U������
		CMagic::Create(ATTACK_POS, MAGIC_MOVE, CMagic::TYPE_ENEMY_FIRE_BALL);
	}
	// ICE�̏ꍇ
	if (m_Type == TYPE_ICE)
	{
		// �U������
		CMagic::Create(ATTACK_POS, MAGIC_MOVE, CMagic::TYPE_ENEMY_ICE_BALL);
	}
}
//******************************************************************************
// ����
//******************************************************************************
void CGhost::Rot(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// �����擾
	D3DXVECTOR3 rot = GetRot();

	// �ړI�̌���
	D3DXVECTOR3 RotDest = rot;

	// CScene�̃|�C���^
	CScene *pScene = NULL;

	do
	{
		// �V�[���擾
		pScene = GetScene(OBJTYPE_PLAYER);

		// NULL�łȂ��ꍇ
		if (pScene != NULL)
		{
			// �I�u�W�F�N�g�^�C�v�擾
			OBJTYPE objtype = pScene->GetObjType();

			// OBJECT_TYPE��OBJTYPE_PLAYER�̏ꍇ
			if (objtype == OBJTYPE_PLAYER)
			{
				// �ʒu�擾
				D3DXVECTOR3 PlayerPos = ((CPlayer*)pScene)->GetPos();

				// �v���C���[��荶�ɂ���ꍇ
				if (pos.x < PlayerPos.x)
				{
					// RIGHT��
					m_Rot = ROT_RIGHT;
				}
				// �v���C���[���E�ɂ���ꍇ
				if (pos.x > PlayerPos.x)
				{
					// LEFT��
					m_Rot = ROT_LEFT;
				}

			}
		}
		// NULL�ɂȂ�܂ŌJ��Ԃ�
	} while (pScene != NULL);

	// �E�������Ă�ꍇ
	if (m_Rot == ROT_RIGHT)
	{
		// ����
		RotDest.y = RIGHT_ROT.y;
	}
	// ���������Ă�ꍇ
	if (m_Rot == ROT_LEFT)
	{
		// ����
		RotDest.y = LEFT_ROT.y;
	}

	// ����
	rot += (RotDest - rot) * ADD_ROT;

	// �����ݒ�
	SetRot(rot);
}
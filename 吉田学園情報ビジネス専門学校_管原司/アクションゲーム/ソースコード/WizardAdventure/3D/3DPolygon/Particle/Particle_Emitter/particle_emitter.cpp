//******************************************************************************
// �p�[�e�B�N���G�~�b�^�[ [particle_emitter.cpp]
// Author : �ǌ��@�i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "scene.h"
#include "../3D/Model/player.h"
#include "../3D/3DPolygon/Particle/particle.h"
#include "../3D/Model/Enemy/ghost.h"
#include "particle_emitter.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define STAR_EMITTER_TEXT	("data/Effect/StarEmitter01_Data.txt")								// �e�L�X�g�̃p�X
#define FIRE_EMITTER_TEXT	("data/Effect/FireEmitter_Data.txt")								// �e�L�X�g�̃p�X
#define ICE_EMITTER_TEXT	("data/Effect/IceEmitter_Data.txt")									// �e�L�X�g�̃p�X
#define FIREGHOST_TEXT		("data/Effect/FireGhostEmitter_Data.txt")							// �e�L�X�g�̃p�X
#define ICEGHOST_TEXT		("data/Effect/IceGhostEmitter_Data.txt")							// �e�L�X�g�̃p�X
#define FIRE_ENEMY_CREATE	("data/Effect/Fire_Create_Data.txt")								// �e�L�X�g�̃p�X
#define ICE_ENEMY_CREATE	("data/Effect/Ice_Create_Data.txt")									// �e�L�X�g�̃p�X
#define MAP_EMITTER			("data/Effect/MapEffect_Data.txt")									// �e�L�X�g�̃p�X
#define STAR_EMITTER2_TEXT	("data/Effect/StarEmitter02_Data.txt")								// �e�L�X�g�̃p�X
#define MAP_POS				(D3DXVECTOR3(PlayerPos.x - 300.0f, 0.0f, -150.0f))					// �ʒu
#define MAP_POS2			(D3DXVECTOR3(PlayerPos.x + 300.0f, 0.0f, -150.0f))					// �ʒu
#define REMAINDER			(0)																	// �]��0
#define RELEASE_COUNT		(60)																// �j���J�E���g
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CParticle_Emitter::CParticle_Emitter()
{
	m_pos				= INIT_D3DXVECTOR3;
	m_nCount			= INIT_INT;
	m_nCreateCount		= INIT_INT;
	memset(m_cText, NULL, sizeof(m_cText));
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CParticle_Emitter::~CParticle_Emitter()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CParticle_Emitter * CParticle_Emitter::Create(D3DXVECTOR3 pos, TYPE type)
{
	// CParticle_Emitter�̃|�C���^
	CParticle_Emitter *pParticle_Emitter = NULL;

	// NULL�̏ꍇ
	if (pParticle_Emitter == NULL)
	{
		// �������m��
		pParticle_Emitter = new CParticle_Emitter;

		// NULL�łȂ��ꍇ
		if (pParticle_Emitter != NULL)
		{
			// �ʒu���
			pParticle_Emitter->m_pos = pos;

			// �ʒu���
			pParticle_Emitter->m_Type = type;

			// ������
			pParticle_Emitter->Init();
		}
	}
	// �|�C���^��Ԃ�
	return pParticle_Emitter;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CParticle_Emitter::Init(void)
{
	// �^�C�v
	switch (m_Type)
	{
	case TYPE_STAR_RIGHT:
		// �e�L�X�g�t�@�C���ǂݍ���
		sprintf(m_cText, STAR_EMITTER_TEXT);
		break;
	case TYPE_STAR_LEFT:
		// �e�L�X�g�t�@�C���ǂݍ���
		sprintf(m_cText, STAR_EMITTER_TEXT);
		break;
	case TYPE_FIRE_RIGHT:
		// �e�L�X�g�t�@�C���ǂݍ���
		sprintf(m_cText, FIRE_EMITTER_TEXT);
		break;
	case TYPE_FIRE_LEFT:
		// �e�L�X�g�t�@�C���ǂݍ���
		sprintf(m_cText, FIRE_EMITTER_TEXT);
		break;
	case TYPE_ICE_RIGHT:
		// �e�L�X�g�t�@�C���ǂݍ���
		sprintf(m_cText, ICE_EMITTER_TEXT);
		break;
	case TYPE_ICE_LEFT:
		// �e�L�X�g�t�@�C���ǂݍ���
		sprintf(m_cText, ICE_EMITTER_TEXT);
		break;
	case TYPE_FIRE_GHOST:
		// �e�L�X�g�t�@�C���ǂݍ���
		sprintf(m_cText, FIREGHOST_TEXT);
		break;
	case TYPE_ICE_GHOST:
		// �e�L�X�g�t�@�C���ǂݍ���
		sprintf(m_cText, ICEGHOST_TEXT);
		break;
	case TYPE_FIRE_CREATE:
		// �t�@�C���ǂݍ���
		sprintf(m_cText, FIRE_ENEMY_CREATE);
		break;
	case TYPE_ICE_CREATE:
		// �t�@�C���ǂݍ���
		sprintf(m_cText, ICE_ENEMY_CREATE);
		break;
	case TYPE_MAP:
		// �t�@�C���ǂݍ���
		sprintf(m_cText, MAP_EMITTER);
		break;
	case TYPE_STAR:
		// �t�@�C���ǂݍ���
		sprintf(m_cText, STAR_EMITTER2_TEXT);
		break;
	}

	// �ǂݍ���
	Load(m_cText);
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CParticle_Emitter::Uninit(void)
{
	// �j��
	CScene::Release();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CParticle_Emitter::Update(void)
{
	// ��������
	CreateParticle();

	// �^�C�v���E�̏ꍇ
	if (m_Type == TYPE_STAR_RIGHT || m_Type == TYPE_FIRE_RIGHT || m_Type == TYPE_ICE_RIGHT)
	{
		// ���̏���
		Right_Arm();
	}
	// �^�C�v�����̏ꍇ
	if (m_Type == TYPE_STAR_LEFT || m_Type == TYPE_FIRE_LEFT || m_Type == TYPE_ICE_LEFT)
	{
		// ���̏���
		Left_Arm();
	}
	// �^�C�v��MAP�̏ꍇ
	if (m_Type == TYPE_MAP)
	{
		// CScene�̃|�C���^
		CScene *pScene = NULL;

		do
		{
			// CScene�擾
			pScene = GetScene(OBJTYPE_PLAYER);

			// NULL�łȂ��ꍇ
			if (pScene != NULL)
			{
				// �I�u�W�F�N�g�^�C�v�擾
				OBJTYPE objtype = pScene->GetObjType();

				// OBJTYPE_PLAYER�̏ꍇ
				if (objtype == OBJTYPE_PLAYER)
				{
					// �����擾
					int nRot = ((CPlayer*)pScene)->GetRotState();

					// �v���C���[�̈ʒu�擾
					D3DXVECTOR3 PlayerPos = ((CPlayer*)pScene)->GetPos();

					// RIGHT�̏ꍇ
					if (nRot == CPlayer::ROT_STATE_RIGHT)
					{
						// �ʒu�ݒ�
						m_pos = MAP_POS;
					}
					// LEFT�̏ꍇ
					if (nRot == CPlayer::ROT_STATE_LEFT)
					{
						// �ʒu�ݒ�
						m_pos = MAP_POS2;
					}
				}
			}
			// NULL�ɂȂ�܂ŌJ��Ԃ�
		} while (pScene != NULL);
	}
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CParticle_Emitter::Draw(void)
{
}
//******************************************************************************
// �j���֐�
//******************************************************************************
void CParticle_Emitter::Release(void)
{
	// �I��
	Uninit();
	return;
}
//******************************************************************************
// �ʒu�ݒ�֐�
//******************************************************************************
void CParticle_Emitter::SetPos(D3DXVECTOR3 pos)
{
	// �ʒu���
	m_pos = pos;
}
//******************************************************************************
// �p�[�e�B�N�����������֐�
//******************************************************************************
void CParticle_Emitter::CreateParticle(void)
{
	// �C���N�������g
	m_nCount++;

	// �]�肪0�̏ꍇ
	if (m_nCount % m_nCreateCount == REMAINDER)
	{
		CParticle::Create(m_pos, m_cText);
	}

	// TYPE_FIRE_CREATE�܂���TYPE_ICE_CREATE�̏ꍇ
	if (m_Type == TYPE_FIRE_CREATE || m_Type == TYPE_ICE_CREATE)
	{
		// 100�ɂȂ�����
		if (m_nCount == RELEASE_COUNT)
		{
			// �I��
			Uninit();
			return;
		}
	}
}
//******************************************************************************
// �ǂݍ��݊֐�
//******************************************************************************
void CParticle_Emitter::Load(const char * cText)
{
	// �ǂݍ��ݗp
	char cReedText[MAX_TEXT];

	// �����̔��ʗp
	char cHeadText[MAX_TEXT];

	// �g��Ȃ�����
	char cDie[MAX_TEXT];

	// �t�@�C���|�C���^
	FILE *pFile = NULL;

	// NULL�̏ꍇ
	if (pFile == NULL)
	{
		//�t�@�C�����J��
		pFile = fopen(cText, "r");

		// NULL�łȂ��ꍇ
		if (pFile != NULL)
		{
			// SCRIPT�̕�����������܂�
			while (strcmp(cHeadText, "SCRIPT") != INIT_INT)
			{
				// �e�L�X�g����cReedText��������ǂݍ���
				fgets(cReedText, sizeof(cReedText), pFile);

				// �ǂݍ��񂾕�������cHeadText�Ɋi�[
				sscanf(cReedText, "%s", &cHeadText);
			}
			// cHeadText��SCRIPT��������
			if (strcmp(cHeadText, "SCRIPT") == INIT_INT)
			{
				// END_SCRIPT�̕�����������܂�
				while (strcmp(cHeadText, "END_SCRIPT") != INIT_INT)
				{
					// �e�L�X�g����cReedText��������ǂݍ���
					fgets(cReedText, sizeof(cReedText), pFile);

					// �ǂݍ��񂾕�������cHeadText�Ɋi�[
					sscanf(cReedText, "%s", &cHeadText);

					// cHeadText��MOTIONSET��������
					if (strcmp(cHeadText, "SETTINGS") == INIT_INT)
					{
						// END_MOTIONSET�̕�����������܂�
						while (strcmp(cHeadText, "END_SETTINGS") != INIT_INT)
						{
							// �e�L�X�g����cReedText��������ǂݍ���
							fgets(cReedText, sizeof(cReedText), pFile);

							// �ǂݍ��񂾕�������cHeadText�Ɋi�[
							sscanf(cReedText, "%s", &cHeadText);

							// cHeadText��ALPHA_BLEND�̏ꍇ
							if (strcmp(cHeadText, "CREATE_COUNT") == INIT_INT)
							{
								// ����m_bAlpha_Blend�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nCreateCount);
							}
						}
					}
				}
				// �t�@�C�������
				fclose(pFile);
			}
			// �J���Ȃ�������
			else
			{
				printf("�t�@�C�����J�������o���܂���ł����B\n");
			}
		}
	}
}
//******************************************************************************
// �E��̏����֐�
//******************************************************************************
void CParticle_Emitter::Right_Arm(void)
{
	// �ʒu
	D3DXVECTOR3 pos;

	// CScene�̃|�C���^
	CScene *pScene = NULL;

	// �v���C���[�擾
	do
	{
		// �V�[���擾
		pScene = GetScene(OBJTYPE_PLAYER);

		// NULL�łȂ��ꍇ
		if (pScene != NULL)
		{
			// �I�u�W�F�N�g�^�C�v�擾
			OBJTYPE objtype = pScene->GetObjType();

			// �I�u�W�F�N�g�^�C�v�v���C���[
			if (objtype == OBJTYPE_PLAYER)
			{
				// �ʒu�擾
				pos.x = ((CPlayer*)pScene)->GetMtxWorld(CPlayer::PARTS_DOWN_ARM_R)._41;
				pos.y = ((CPlayer*)pScene)->GetMtxWorld(CPlayer::PARTS_DOWN_ARM_R)._42;
				pos.z = ((CPlayer*)pScene)->GetMtxWorld(CPlayer::PARTS_DOWN_ARM_R)._43;

				// �ʒu���
				m_pos = pos;
			}
		}
		// NULL�ɂȂ�܂ŌJ��Ԃ�
	} while (pScene != NULL);
}
//******************************************************************************
// ����̏����֐�
//******************************************************************************
void CParticle_Emitter::Left_Arm(void)
{
	// �ʒu
	D3DXVECTOR3 pos;

	// CScene�̃|�C���^
	CScene *pScene = NULL;

	// �v���C���[�擾
	do
	{
		// �V�[���擾
		pScene = GetScene(OBJTYPE_PLAYER);

		// NULL�łȂ��ꍇ
		if (pScene != NULL)
		{
			// �I�u�W�F�N�g�^�C�v�擾
			OBJTYPE objtype = pScene->GetObjType();

			// �I�u�W�F�N�g�^�C�v�v���C���[
			if (objtype == OBJTYPE_PLAYER)
			{
				// �ʒu�擾
				pos.x = ((CPlayer*)pScene)->GetMtxWorld(CPlayer::PARTS_DOWN_ARM_L)._41;
				pos.y = ((CPlayer*)pScene)->GetMtxWorld(CPlayer::PARTS_DOWN_ARM_L)._42;
				pos.z = ((CPlayer*)pScene)->GetMtxWorld(CPlayer::PARTS_DOWN_ARM_L)._43;

				// �ʒu���
				m_pos = pos;
			}
		}
		// NULL�ɂȂ�܂ŌJ��Ԃ�
	} while (pScene != NULL);
}
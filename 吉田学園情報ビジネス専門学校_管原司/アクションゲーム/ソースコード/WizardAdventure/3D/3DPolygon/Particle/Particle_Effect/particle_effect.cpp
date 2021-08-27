//******************************************************************************
// �p�[�e�B�N���G�~�b�^�[ [particle_emitter.cpp]
// Author : �ǌ��@�i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "../3D/3DPolygon/Particle/particle.h"
#include "particle_effect.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define FIRE_EXPLOSION			("data/Effect/Fire_Explosion_Data.txt")			// �΂̔����p�X
#define ICE_EXPLOSION			("data/Effect/Ice_Explosion_Data.txt")			// �X�̔����p�X
#define FIRE_EXPLOSION_2		("data/Effect/Fire_Explosion2_Data.txt")		// �΂̔����p�X
#define ICE_EXPLOSION_2			("data/Effect/Ice_Explosion2_Data.txt")			// �X�̔����p�X
#define ENEMY_FIRE_EXPLOSION	("data/Effect/Enemy_Fire_Explosion_Data.txt")	// �G�΂̔����p�X
#define ENEMY_FIRE_EXPLOSION_2	("data/Effect/Enemy_Fire_Explosion2_Data.txt")	// �G�΂̔����p�X
#define WOOD_EFFECT				("data/Effect/wood_effect_Data.txt")			// �؂̃G�t�F�N�g
#define WOOD_EFFECT_2			("data/Effect/wood_effect_2_Data.txt")			// �؂̃G�t�F�N�g
#define BLOCK_EFFECT			("data/Effect/Block_effect_Data.txt")			// �u���b�N�G�t�F�N�g
#define STAR_EFFECT				("data/Effect/StarEffect_Data.txt")				// ���G�t�F�N�g
#define STAR_EFFECT2			("data/Effect/StarEffect2_Data.txt")			// ���G�t�F�N�g
#define REMAINDER				(0)												// �]��0
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CParticle_Effect::CParticle_Effect()
{
	m_pos				 = INIT_D3DXVECTOR3;
	m_nCreate_TotalCount = INIT_INT;
	memset(m_cText, NULL, sizeof(m_cText));
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CParticle_Effect::~CParticle_Effect()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CParticle_Effect * CParticle_Effect::Create(D3DXVECTOR3 pos, TYPE type)
{
	// CParticle_Effect�̃|�C���^
	CParticle_Effect *pParticle_Effect = NULL;

	// NULL�̏ꍇ
	if (pParticle_Effect == NULL)
	{
		// �������m��
		pParticle_Effect = new CParticle_Effect;

		// NULL�łȂ��ꍇ
		if (pParticle_Effect != NULL)
		{
			// �ʒu���
			pParticle_Effect->m_pos = pos;

			// �^�C�v���
			pParticle_Effect->m_Type = type;

			// ������
			pParticle_Effect->Init();
		}
	}
	// �|�C���^��Ԃ�
	return pParticle_Effect;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CParticle_Effect::Init(void)
{
	// ���
	switch (m_Type)
	{
	case TYPE_FIRE_EXPLOSION:
		// �e�L�X�g�ǂݍ���
		sprintf(m_cText, FIRE_EXPLOSION);
		break;
	case TYPE_ICE_EXPLOSION:
		// �e�L�X�g�ǂݍ���
		sprintf(m_cText, ICE_EXPLOSION);
		break;
	case TYPE_FIRE_EXPLOSION_2:
		// �e�L�X�g�ǂݍ���
		sprintf(m_cText, FIRE_EXPLOSION_2);
		break;
	case TYPE_ICE_EXPLOSION_2:
		// �e�L�X�g�ǂݍ���
		sprintf(m_cText, ICE_EXPLOSION_2);
		break;
	case TYPE_ENEMY_FIRE_EXPLOSION:
		// �e�L�X�g�ǂݍ���
		sprintf(m_cText,ENEMY_FIRE_EXPLOSION);
		break;
	case TYPE_ENEMY_FIRE_EXPLOSION_2:
		// �e�L�X�g�ǂݍ���
		sprintf(m_cText, ENEMY_FIRE_EXPLOSION_2);
		break;
	case TYPE_WOOD_EFFECT:
		// �e�L�X�g�ǂݍ���
		sprintf(m_cText, WOOD_EFFECT);
		break;
	case TYPE_WOOD_EFFECT_2:
		// �e�L�X�g�ǂݍ���
		sprintf(m_cText, WOOD_EFFECT_2);
		break;
	case TYPE_BLOCK_EFFECT:
		// �e�L�X�g�ǂݍ���
		sprintf(m_cText, BLOCK_EFFECT);
		break;
	case TYPE_STAR_EFFECT:
		// �e�L�X�g�ǂݍ���
		sprintf(m_cText, STAR_EFFECT);
		break;
	case TYPE_STAR_EFFECT2:
		// �e�L�X�g�ǂݍ���
		sprintf(m_cText, STAR_EFFECT2);
		break;
		// ��O
	default:
		break;
	}
	// �ǂݍ���
	Load(m_cText);

	// ����
	CParticle::CreateEffect(m_pos, m_nCreate_TotalCount, m_cText);

	// �j��
	Uninit();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CParticle_Effect::Uninit(void)
{
	// �j��
	Release();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CParticle_Effect::Update(void)
{
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CParticle_Effect::Draw(void)
{
}
//******************************************************************************
// �ǂݍ��݊֐�
//******************************************************************************
void CParticle_Effect::Load(const char * cText)
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
							if (strcmp(cHeadText, "CREATE_TOTAL_COUNT") == INIT_INT)
							{
								// ����m_bAlpha_Blend�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nCreate_TotalCount);
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
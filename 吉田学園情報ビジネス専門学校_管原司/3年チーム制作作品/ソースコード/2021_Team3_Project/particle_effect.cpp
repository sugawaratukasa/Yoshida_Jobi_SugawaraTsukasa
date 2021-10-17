//******************************************************************************
// �p�[�e�B�N���G�~�b�^�[ [particle_emitter.cpp]
// Author : �ǌ��@�i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "particle.h"
#include "particle_effect.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define SPLASH		("data/Text/Effect/Splash.txt")		// �e�L�X�g�p�X
#define WAVE		("data/Text/Effect/Wave.txt")		// �e�L�X�g�p�X
#define SMOKE		("data/Text/Effect/Smoke.txt")		// �e�L�X�g�p�X
#define EXPLOSION	("data/Text/Effect/Explosion.txt")	// �e�L�X�g�p�X
#define WOOD		("data/Text/Effect/Wood_Effect.txt")// �e�L�X�g�p�X
#define REMAINDER	(0)									// �]��0
#define MAX_TEXT	(1024)								// �e�L�X�g�̍ő吔
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CParticle_Effect::CParticle_Effect()
{
	m_pos = ZeroVector3;
	m_nCreate_TotalCount = ZERO_INT;
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
			pParticle_Effect->Init(pos, ZeroVector3);
		}
	}
	// �|�C���^��Ԃ�
	return pParticle_Effect;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CParticle_Effect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �ǂݍ��ݗp
	char cText[MAX_TEXT];
	// ���
	switch (m_Type)
	{
	case TYPE_SPLASH:
		// �e�L�X�g�ǂݍ���
		sprintf(cText, SPLASH);
		break;
	case TYPE_WAVE:
		// �e�L�X�g�ǂݍ���
		sprintf(cText, WAVE);
		break;
	case TYPE_SMOKE:
		// �e�L�X�g�ǂݍ���
		sprintf(cText, SMOKE);
		break;
	case TYPE_EXPLOSION:
		// �e�L�X�g�ǂݍ���
		sprintf(cText, EXPLOSION);
		break;
	case TYPE_WOOD:
		// �e�L�X�g�ǂݍ���
		sprintf(cText, WOOD);
		break;
		// ��O
	default:
		break;
	}
	// �ǂݍ���
	Load(cText);

	// ����
	CParticle::CreateEffect(m_pos, m_nCreate_TotalCount, cText);

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
	FILE *pFile = nullptr;

	// NULL�̏ꍇ
	if (pFile == nullptr)
	{
		//�t�@�C�����J��
		pFile = fopen(cText, "r");

		// NULL�łȂ��ꍇ
		if (pFile != nullptr)
		{
			// SCRIPT�̕�����������܂�
			while (strcmp(cHeadText, "SCRIPT") != ZERO_INT)
			{
				// �e�L�X�g����cReedText��������ǂݍ���
				fgets(cReedText, sizeof(cReedText), pFile);

				// �ǂݍ��񂾕�������cHeadText�Ɋi�[
				sscanf(cReedText, "%s", &cHeadText);
			}
			// cHeadText��SCRIPT��������
			if (strcmp(cHeadText, "SCRIPT") == ZERO_INT)
			{
				// END_SCRIPT�̕�����������܂�
				while (strcmp(cHeadText, "END_SCRIPT") != ZERO_INT)
				{
					// �e�L�X�g����cReedText��������ǂݍ���
					fgets(cReedText, sizeof(cReedText), pFile);

					// �ǂݍ��񂾕�������cHeadText�Ɋi�[
					sscanf(cReedText, "%s", &cHeadText);

					// cHeadText��MOTIONSET��������
					if (strcmp(cHeadText, "SETTINGS") == ZERO_INT)
					{
						// END_MOTIONSET�̕�����������܂�
						while (strcmp(cHeadText, "END_SETTINGS") != ZERO_INT)
						{
							// �e�L�X�g����cReedText��������ǂݍ���
							fgets(cReedText, sizeof(cReedText), pFile);

							// �ǂݍ��񂾕�������cHeadText�Ɋi�[
							sscanf(cReedText, "%s", &cHeadText);

							// cHeadText��ALPHA_BLEND�̏ꍇ
							if (strcmp(cHeadText, "CREATE_TOTAL_COUNT") == ZERO_INT)
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
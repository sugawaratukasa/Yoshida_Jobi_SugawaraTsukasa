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
#define MAX_TEXT	(1024)								// �e�L�X�g�̍ő吔
#define DATA_TEXT	("data/Effect/Explosion_Data.txt")	// �e�L�X�g
#define REMAINDER	(0)									// �]��0
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CParticle_Effect::CParticle_Effect()
{
	m_pos = INITIAL_D3DXVECTOR3;
	m_nCreate_TotalCount = INIT_INT;
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
CParticle_Effect * CParticle_Effect::Create(D3DXVECTOR3 pos)
{
	// CParticle_Effect�̃|�C���^
	CParticle_Effect *pParticle_Effect;

	// �������m��
	pParticle_Effect = new CParticle_Effect;

	// �ʒu���
	pParticle_Effect->m_pos = pos;

	// �e�L�X�g�t�@�C���ǂݍ���
	pParticle_Effect->Load(DATA_TEXT);

	// ������
	pParticle_Effect->Init();

	// �|�C���^��Ԃ�
	return pParticle_Effect;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CParticle_Effect::Init(void)
{
	// ����
	CParticle::CreateEffect(m_pos, m_nCreate_TotalCount, DATA_TEXT);

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
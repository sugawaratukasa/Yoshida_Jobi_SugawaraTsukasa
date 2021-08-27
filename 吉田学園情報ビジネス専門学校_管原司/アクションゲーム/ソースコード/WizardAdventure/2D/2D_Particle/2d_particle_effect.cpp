//******************************************************************************
// 2D�p�[�e�B�N���G�~�b�^�[ [2d_particle_emitter.cpp]
// Author : �ǌ��@�i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "2d_particle.h"
#include "2d_particle_effect.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define COLOR_BOM	("data/Effect/ColorBom_Data.txt")		// �p�X
#define REMAINDER	(0)									// �]��0
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
C2D_Particle_Effect::C2D_Particle_Effect()
{
	m_pos					= INIT_D3DXVECTOR3;
	m_nCreate_TotalCount	= INIT_INT;
	memset(m_cText, NULL, sizeof(m_cText));
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
C2D_Particle_Effect::~C2D_Particle_Effect()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
C2D_Particle_Effect *C2D_Particle_Effect::Create(D3DXVECTOR3 pos, TYPE type)
{
	// C2D_Particle_Effect�̃|�C���^
	C2D_Particle_Effect *p2D_Particle_Effect = NULL;

	// NULL�̏ꍇ
	if (p2D_Particle_Effect == NULL)
	{
		// �������m��
		p2D_Particle_Effect = new C2D_Particle_Effect;

		// NULL�łȂ��ꍇ
		if (p2D_Particle_Effect != NULL)
		{
			// �ʒu���
			p2D_Particle_Effect->m_pos = pos;

			// �^�C�v���
			p2D_Particle_Effect->m_Type = type;

			// ������
			p2D_Particle_Effect->Init();
		}
	}
	// �|�C���^��Ԃ�
	return p2D_Particle_Effect;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT C2D_Particle_Effect::Init(void)
{
	// ���
	switch (m_Type)
	{
		// �J���[�{��
	case TYPE_COLOR_BOM:
		// ����
		// �e�L�X�g�ǂݍ���
		sprintf(m_cText, COLOR_BOM);
		break;
		// ��O
	default:
		break;
	}
	// �ǂݍ���
	Load(m_cText);

	// ����
	C2D_Particle::CreateEffect(m_pos, m_nCreate_TotalCount, m_cText);

	// �j��
	Uninit();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void C2D_Particle_Effect::Uninit(void)
{
	// �j��
	Release();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void C2D_Particle_Effect::Update(void)
{
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void C2D_Particle_Effect::Draw(void)
{
}
//******************************************************************************
// �ǂݍ��݊֐�
//******************************************************************************
void C2D_Particle_Effect::Load(const char * cText)
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
//******************************************************************************
// 2d�p�[�e�B�N���G�~�b�^�[ [2d_particle_emitter.cpp]
// Author : �ǌ��@�i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "scene.h"
#include "2d_particle.h"
#include "2d_particle_emitter.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define FIRE_EMITTER_TEXT	("data/Effect/2dFireEmitter_Data.txt")	 // �e�L�X�g�̃p�X
#define ICE_EMITTER_TEXT	("data/Effect/2dIceEmitter_Data.txt")	 // �e�L�X�g�̃p�X
#define GREEN_EMITTER		("data/Effect/2D_GreenEffect_Data.txt")	 // �e�L�X�g�̃p�X
#define REMAINDER			(0)										 // �]��0
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
C2D_Particle_Emitter::C2D_Particle_Emitter()
{
	m_pos			= INIT_D3DXVECTOR3;
	m_nCount		= INIT_INT;
	m_nCreateCount	= INIT_INT;
	memset(m_cText, NULL, sizeof(m_cText));
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
C2D_Particle_Emitter::~C2D_Particle_Emitter()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
C2D_Particle_Emitter * C2D_Particle_Emitter::Create(D3DXVECTOR3 pos, TYPE type)
{
	// C2D_Particle_Emitter�̃|�C���^
	C2D_Particle_Emitter *p2D_Particle_Emitter = NULL;

	// NULL�̏ꍇ
	if (p2D_Particle_Emitter == NULL)
	{
		// �������m��
		p2D_Particle_Emitter = new C2D_Particle_Emitter;

		// NULL�łȂ��ꍇ
		if (p2D_Particle_Emitter != NULL)
		{
			// �ʒu���
			p2D_Particle_Emitter->m_pos = pos;

			// �ʒu���
			p2D_Particle_Emitter->m_Type = type;

			// ������
			p2D_Particle_Emitter->Init();
		}
	}
	// �|�C���^��Ԃ�
	return p2D_Particle_Emitter;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT C2D_Particle_Emitter::Init(void)
{
	// �^�C�v
	switch (m_Type)
	{
		// ��
	case TYPE_GREEN:
		// �ǂݍ��ރt�@�C���w��
		sprintf(m_cText, GREEN_EMITTER);
		break;
		// ��
	case TYPE_FIRE:
		// �ǂݍ��ރt�@�C���w��
		sprintf(m_cText, FIRE_EMITTER_TEXT);
		break;
		// �X
	case TYPE_ICE:
		// �ǂݍ��ރt�@�C���w��
		sprintf(m_cText, ICE_EMITTER_TEXT);
		break;
		// ��O
	default:
		break;
	}

	// �ǂݍ���
	Load(m_cText);
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void C2D_Particle_Emitter::Uninit(void)
{
	// �j��
	CScene::Release();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void C2D_Particle_Emitter::Update(void)
{
	// ��������
	CreateParticle();
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void C2D_Particle_Emitter::Draw(void)
{
}
//******************************************************************************
// �j���֐�
//******************************************************************************
void C2D_Particle_Emitter::Release(void)
{
	// �I��
	Uninit();
	return;
}
//******************************************************************************
// �ʒu�ݒ�֐�
//******************************************************************************
void C2D_Particle_Emitter::SetPos(D3DXVECTOR3 pos)
{
	// �ʒu���
	m_pos = pos;
}
//******************************************************************************
// �p�[�e�B�N�����������֐�
//******************************************************************************
void C2D_Particle_Emitter::CreateParticle(void)
{
	// �C���N�������g
	m_nCount++;

	// �]�肪0�̏ꍇ
	if (m_nCount % m_nCreateCount == REMAINDER)
	{
		C2D_Particle::Create(m_pos, m_cText);
	}
}
//******************************************************************************
// �ǂݍ��݊֐�
//******************************************************************************
void C2D_Particle_Emitter::Load(const char * cText)
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
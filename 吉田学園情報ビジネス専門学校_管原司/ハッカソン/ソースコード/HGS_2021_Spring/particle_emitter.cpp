//******************************************************************************
// �p�[�e�B�N���G�~�b�^�[ [particle_emitter.cpp]
// Author : �ǌ��@�i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "particle.h"
#include "particle_emitter.h"
#include "mode_game.h"
#include "player_3d.h"

//******************************************************************************
// �}�N����`
//******************************************************************************
#define MAX_TEXT	(1024)							// �e�L�X�g�̍ő吔
#define BOAD_EFFECT_TEXT	("data/Effect/BoadEffect_Data.txt")	// �e�L�X�g
#define REMAINDER	(0)								// �]��0
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CParticle_Emitter::CParticle_Emitter()
{
	m_pos = INITIAL_D3DXVECTOR3;
	m_nCount = INIT_INT;
	m_nCreateCount = INIT_INT;
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
	CParticle_Emitter *pParticle_Emitter;

	// �������m��
	pParticle_Emitter = new CParticle_Emitter;

	// �ʒu���
	pParticle_Emitter->m_pos = pos;

	// �ʒu���
	pParticle_Emitter->m_Type = type;

	// ������
	pParticle_Emitter->Init();

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
	case TYPE_BOAD:
		// �e�L�X�g�t�@�C���ǂݍ���
		sprintf(m_cText, BOAD_EFFECT_TEXT);
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
	Release();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CParticle_Emitter::Update(void)
{
	CPlayer3d * pPlayer = CGameMode::GetPlayer3d();
	// �C���N�������g
	m_nCount++;
	if (pPlayer != NULL)
	{
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
		m_pos = PlayerPosition;
		// �]�肪0�̏ꍇ
		//if (m_nCount % m_nCreateCount == REMAINDER)
		//{
		CParticle::Create(PlayerPosition, m_cText);
		//}
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
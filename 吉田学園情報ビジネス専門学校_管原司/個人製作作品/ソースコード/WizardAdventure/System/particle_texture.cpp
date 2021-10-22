//***********************************************************************************
//	�e�N�X�`��	[texture.cpp]
//	Author : �ǌ� �i
//***********************************************************************************
//***********************************************************************************
// �C���N���[�h�t�@�C��
//***********************************************************************************
#include "manager.h"
#include "renderer.h"
#include "particle_texture.h"
//***********************************************************************************
// �}�N����`
//***********************************************************************************
#define TEXTURE_TEXT	("data/Particle/Texture/texture.txt")	// �e�N�X�`���e�L�X�g
#define MAX_TEXT		(1024)									// �����̍ő吔
//***********************************************************************************
//�ÓI�����o�ϐ��錾
//***********************************************************************************
//***********************************************************************************
// �R���X�g���N�^
//***********************************************************************************
CParticle_Texture::CParticle_Texture()
{
	m_pTexture		= NULL;
	m_pLoadTexture	= NULL;
	m_nNumTex		= INIT_INT;
}
//***********************************************************************************
// �f�X�g���N�^
//***********************************************************************************
CParticle_Texture::~CParticle_Texture()
{
}
//***********************************************************************************
// �������֐�
//***********************************************************************************
HRESULT CParticle_Texture::Init(void)
{
	// �e�N�X�`���ǂݍ���
	Load();

	return S_OK;
}
//***********************************************************************************
// �I���֐�
//***********************************************************************************
void CParticle_Texture::Uninit(void)
{
	// �e�N�X�`���j��
	if (m_pTexture != NULL)
	{
		// �j��
		m_pTexture->Release();

		// NULL��
		m_pTexture = NULL;
	}
	// �ǂݍ��ݗp�e�N�X�`���̔j��
	if (m_pLoadTexture != NULL)
	{
		// �e�N�X�`��������
		for (int nCnt = INIT_INT; nCnt < m_nNumTex; nCnt++)
		{
			// �e�N�X�`���j��
			m_pLoadTexture[nCnt]->Release();
		}

		// �������j��
		delete[] m_pLoadTexture;

		// m_pParticle_Texture��NULL��
		m_pLoadTexture = NULL;
	}
}
//***********************************************************************************
// �e�N�X�`���ǂݍ���
//***********************************************************************************
void CParticle_Texture::Load(void)
{
	// �ǂݍ��ݗp
	char cReedText[MAX_TEXT];

	// �����̔��ʗp
	char cHeadText[MAX_TEXT];

	// �g��Ȃ�����
	char cDie[MAX_TEXT];

	// �e�N�X�`���̃e�L�X�g
	char **cTexText = NULL;

	// �e�N�X�`���J�E���g
	int nTexCnt = INIT_INT;

	// �t�@�C���|�C���^
	FILE *pFile = NULL;

	// NULL�̏ꍇ
	if (pFile == NULL)
	{
		//�t�@�C�����J��
		pFile = fopen(TEXTURE_TEXT, "r");

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

					// cHeadText��TEXTURE_NUM�̏ꍇ 
					if (strcmp(cHeadText, "TEXTURE_NUM") == INIT_INT)
					{
						// �e�N�X�`���̐���m_nNumTex�Ɋi�[
						sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nNumTex);

						// NULL�̏ꍇ
						if (cTexText == NULL)
						{
							// �������m��
							cTexText = new char *[m_nNumTex];

							// NULL�łȂ��ꍇ
							if (cTexText != NULL)
							{
								// �e�N�X�`��������
								for (int nCnt = INIT_INT; nCnt < m_nNumTex; nCnt++)
								{
									// �������m��
									cTexText[nCnt] = new char[MAX_TEXT];
								}
							}
						}
					}
					// cHeadText��TEXTURE_FILENAME�̏ꍇ
					if (strcmp(cHeadText, "TEXTURE_FILENAME") == INIT_INT)
					{
						// �e�N�X�`���̃p�X��cTexText�Ɋi�[
						sscanf(cReedText, "%s %s %s", &cDie, &cDie, cTexText[nTexCnt]);

						// �C���N�������g
						nTexCnt++;
					}
				}
			}
			// �����_���[�擾
			LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

			// �������m��
			m_pLoadTexture = new LPDIRECT3DTEXTURE9[m_nNumTex];

			// �e�N�X�`��������
			for (int nCnt = INIT_INT; nCnt < m_nNumTex; nCnt++)
			{
				// �e�N�X�`���ǂݍ���
				D3DXCreateTextureFromFile(pDevice, cTexText[nCnt], &m_pLoadTexture[nCnt]);
			}
			// NULL�łȂ��ꍇ
			if (cTexText != NULL)
			{
				// �e�N�X�`��������
				for (int nCnt = INIT_INT; nCnt < m_nNumTex; nCnt++)
				{
					// �������j��
					delete[] cTexText[nCnt];
				}
				// �������j��
				delete[] cTexText;

				// NULL��
				cTexText = NULL;
			}
			// �t�@�C�������
			fclose(pFile);
		}
	}
}
//***********************************************************************************
// �e�N�X�`���擾
//***********************************************************************************
LPDIRECT3DTEXTURE9 CParticle_Texture::GetTexture(int TexNum)
{
	// ���
	m_pTexture = m_pLoadTexture[TexNum];

	// �e�N�X�`����Ԃ�
	return m_pTexture;
}
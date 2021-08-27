//******************************************************************************
// 2D�p�[�e�B�N��[2d_particle.cpp]
// Author : �ǌ��@�i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "particle_texture.h"
#include "2d_particle.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define MAX_TEXT		(1024)							// �e�L�X�g�̍ő吔
#define RANDOM_POS_MUT	(10)							// 10�{
#define MUT				(2)								// �Q�{
#define ROT				(D3DXVECTOR3(0.0f,0.0f,0.0f))	// ����
#define MIN_COL			(0.0f)							// �F�̍ŏ��l
#define MIN_LIFE		(0)								// ���C�t�̍ŏ��l
#define MIN_SCALE		(0.0f)							// �g�嗦�̍ŏ��l
#define DEVIDE_SIZE		(10)							// �T�C�Y���Z
#define ROT_RANDOM		(360)							// �����̃����_���l
#define COLOR_A			(255)							// ���l	
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
C2D_Particle::C2D_Particle(int nPriority) : CScene2D(nPriority)
{
	m_bAlpha_Blend		= false;
	m_bLife				= false;
	m_bRandomPos		= false;
	m_bRandomSize		= false;
	m_bAddScale			= false;
	m_bSubColor			= false;
	m_bRotRandom		= false;
	m_bTexRandom		= false;
	m_bColorRandom		= false;
	m_Random_pos		= INIT_D3DXVECTOR3;
	m_size				= INIT_D3DXVECTOR3;
	m_move				= INIT_D3DXVECTOR3;
	m_AddAngle			= INIT_D3DXVECTOR3;
	m_color				= INIT_COLOR;
	m_SubColor			= INIT_COLOR;
	m_nAlpha			= INIT_INT;
	m_nLife				= INIT_INT;
	m_nTexNum			= INIT_INT;
	m_nMinTex_RandomNum = INIT_INT;
	m_nMaxTex_RandomNum = INIT_INT;
	m_nColorR			= INIT_INT;
	m_nColorG			= INIT_INT;
	m_nColorB			= INIT_INT;
	m_fAngle			= INIT_FLOAT;
	m_fAddAngle			= INIT_FLOAT;
	m_fRandom_Min_Size	= INIT_FLOAT;
	m_fRandom_Max_Size	= INIT_FLOAT;
	m_fAddScale			= INIT_FLOAT;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
C2D_Particle::~C2D_Particle()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
C2D_Particle *C2D_Particle::Create(D3DXVECTOR3 pos, const char *cText)
{
	// CParticle�̃|�C���^
	C2D_Particle *pParticle = NULL;

	// NULL�̏ꍇ
	if (pParticle == NULL)
	{
		// �������m��
		pParticle = new C2D_Particle;

		// NULL�łȂ��ꍇ
		if (pParticle != NULL)
		{
			//�ʒu�ݒ�
			pParticle->SetPosition(pos);

			// �e�L�X�g�ǂݍ���
			pParticle->LoadParticle(cText);

			// ������
			pParticle->Init();
		}
	}
	// �|�C���^��Ԃ�
	return pParticle;
}

//******************************************************************************
// ������
//******************************************************************************
HRESULT C2D_Particle::Init(void)
{
	// ������
	CScene2D::Init();

	// �T�C�Y�ݒ�
	SetSize(m_size);

	// �T�C�Y�ݒ�
	SetRotation(ROT);

	// �F�ݒ�
	SetColor(m_color);

	if (m_bTexRandom == false)
	{
		// �e�N�X�`���󂯓n��
		BindTexture(CManager::GetParticle_Texture()->GetTexture(m_nTexNum));
	}

	if (m_bTexRandom == true)
	{
		// �e�N�X�`�������_��
		int nTexNum = (rand() % m_nMaxTex_RandomNum + m_nMinTex_RandomNum);

		// �e�N�X�`���󂯓n��
		BindTexture(CManager::GetParticle_Texture()->GetTexture(nTexNum));
	}

	// true�̏ꍇ
	if (m_bRotRandom == true)
	{
		D3DXVECTOR3 rot = INIT_D3DXVECTOR3;

		// ���������_��
		rot.z = float(rand() % ROT_RANDOM);

		// ���W�A���ϊ�
		rot = D3DXToRadian(rot);

		// �����ݒ�
		SetRotation(rot);
	}
	// true�̏ꍇ
	if (m_bRandomSize == true)
	{
		// �T�C�Y
		D3DXVECTOR3 size = INIT_D3DXVECTOR3;

		// �T�C�Y�������_��
		float fRandomSize = float(rand() % (int)m_fRandom_Max_Size + (int)m_fRandom_Min_Size);

		// �T�C�Y��ݒ�
		size.x = fRandomSize;

		// �T�C�Y��ݒ�
		size.y = fRandomSize;

		// �T�C�Y�ݒ�
		SetSize(size);
	}

	// true�̏ꍇ
	if (m_bRandomPos == true)
	{
		// �ʒu�擾
		D3DXVECTOR3 pos = GetPosition();

		// �ʒu
		D3DXVECTOR3 Random_pos = INIT_D3DXVECTOR3;

		// �ʒu�����_��
		Random_pos.x = float(rand() % (int)m_Random_pos.x *RANDOM_POS_MUT * MUT - (int)m_Random_pos.x *RANDOM_POS_MUT / MUT);

		// ���Z
		Random_pos.x = Random_pos.x / RANDOM_POS_MUT;

		// �ʒu�����_��
		Random_pos.y = float(rand() % (int)m_Random_pos.y *RANDOM_POS_MUT * MUT - (int)m_Random_pos.y *RANDOM_POS_MUT / MUT);

		// ���Z
		Random_pos.y = Random_pos.y / RANDOM_POS_MUT;

		// �ʒu�����_��
		pos += Random_pos;

		// �ʒu�ݒ�
		SetPosition(pos);
	}
	// true�̏ꍇ
	if (m_bColorRandom == true)
	{
		// �F
		D3DXCOLOR col = INIT_COLOR;

		// �F�����_��
		m_nColorR = (rand() % m_nColorR);
		m_nColorG = (rand() % m_nColorG);
		m_nColorB = (rand() % m_nColorB);

		col = D3DCOLOR_RGBA(m_nColorR, m_nColorG, m_nColorB, COLOR_A);

		// �F�ݒ�
		SetColor(col);
	}
	// �p�x�����_��
	m_fAngle = float(rand() % (int)m_fAngle);

	// �p�x�擾
	m_Angle.x = m_fAngle;
	m_Angle.y = m_fAngle;
	m_Angle.z = m_fAngle;

	return S_OK;
}

//******************************************************************************
// �I��
//******************************************************************************
void C2D_Particle::Uninit(void)
{
	// �I��
	CScene2D::Uninit();
}

//******************************************************************************
// �X�V
//******************************************************************************
void C2D_Particle::Update(void)
{
	// �X�V
	CScene2D::Update();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// �F�擾
	D3DXCOLOR col = GetColor();

	// �g�嗦�擾
	float fScale = GetScale();

	// �p�x���Z
	m_Angle.x += m_AddAngle.x;
	m_Angle.y += m_AddAngle.y;
	m_Angle.z += m_AddAngle.z;

	// ���C�t���g�p����ꍇ
	if (m_bLife == true)
	{
		// �f�N�������g
		m_nLife--;

		// ���C�t��0�ȉ��̏ꍇ
		if (m_nLife <= MIN_LIFE)
		{
			// �I��
			Uninit();
			return;
		}
	}
	// �g�嗦���Z���g�p��ԂȂ�
	if (m_bAddScale == true)
	{
		// �g�嗦���Z
		fScale += m_fAddScale;

		// �g�嗦��0.0f�ȉ��̏ꍇ
		if (fScale <= MIN_SCALE)
		{
			// �I��
			Uninit();
			return;
		}
	}
	// �F���Z���g�p����ꍇ
	if (m_bSubColor == true)
	{
		// ���Z
		col -= m_SubColor;

		// ���l��0.0f�ȉ��̏ꍇ
		if (col.a <= MIN_COL)
		{
			// �I��
			Uninit();
			return;
		}
	}

	// �g�嗦�ݒ�
	SetScale(fScale);

	// �T�C�Y�ݒ�
	SetSize(size);

	// �F�ݒ�
	SetColor(col);

	// �ʒu�X�V
	pos.x += cosf(D3DXToRadian(m_Angle.x))*m_move.x;
	pos.y += sinf(D3DXToRadian(m_Angle.y))*m_move.y;
	pos.z += sinf(D3DXToRadian(m_Angle.z))*m_move.z;

	// �ʒu�ݒ�
	SetPosition(pos);
}

//******************************************************************************
// �`��
//******************************************************************************
void C2D_Particle::Draw(void)
{
	// ���Z�������s��Ȃ��ꍇ
	if (m_bAlpha_Blend == false)
	{
		// �`��
		CScene2D::Draw();
	}
	// ���Z�������s���ꍇ
	if (m_bAlpha_Blend == true)
	{
		// �����_���[�擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// ���Z�����̐ݒ�
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		// �`��
		CScene2D::Draw();

		// ���ɖ߂�
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}
//******************************************************************************
// ���ݒ�
//******************************************************************************
void C2D_Particle::LoadParticle(const char * cText)
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
							if (strcmp(cHeadText, "ALPHA_BLEND") == INIT_INT)
							{
								// ����m_bAlpha_Blend�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bAlpha_Blend);
							}
							// cHeadText��LIFE�̏ꍇ
							if (strcmp(cHeadText, "LIFE") == INIT_INT)
							{
								// ����m_bLife�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bLife);
							}
							// cHeadText��RANDOM_POS�̏ꍇ
							if (strcmp(cHeadText, "RANDOM_POS") == INIT_INT)
							{
								// ����m_bRandomPos�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bRandomPos);
							}
							// cHeadText��RANDOM_SIZE�̏ꍇ
							if (strcmp(cHeadText, "RANDOM_SIZE") == INIT_INT)
							{
								// ����m_bRandomSize�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bRandomSize);
							}
							// cHeadText��ADD_SCALE�̏ꍇ
							if (strcmp(cHeadText, "ADD_SCALE") == INIT_INT)
							{
								// ����m_bAddScale�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bAddScale);
							}
							// cHeadText��COLOR_SUBTRACT�̏ꍇ
							if (strcmp(cHeadText, "COLOR_SUBTRACT") == INIT_INT)
							{
								// ����m_bSubColor�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bSubColor);
							}
							// cHeadText��ROT_RANDOM�̏ꍇ
							if (strcmp(cHeadText, "ROT_RANDOM") == INIT_INT)
							{
								// ����m_bRotRandom�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bRotRandom);
							}
							// cHeadText��TEX_RANDOM�̏ꍇ
							if (strcmp(cHeadText, "TEX_RANDOM") == INIT_INT)
							{
								// ����m_bTexRandom�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bTexRandom);
							}
							// cHeadText��TEX_RANDOM�̏ꍇ
							if (strcmp(cHeadText, "COLOR_RANDOM") == INIT_INT)
							{
								// ����m_bTexRandom�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bColorRandom);
							}
							// cHeadText��TEXTURE_NUM�̏ꍇ
							if (strcmp(cHeadText, "TEXTURE_NUM") == INIT_INT)
							{
								// ����m_nTexNum�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nTexNum);
							}
							// cHeadText��MIN_TEXTURE_RANDOM_NUM�̏ꍇ
							if (strcmp(cHeadText, "MIN_TEXTURE_RANDOM_NUM") == INIT_INT)
							{
								// ����m_nMinTex_RandomNum�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nMinTex_RandomNum);
							}
							// cHeadText��MAX_TEXTURE_RANDOM_NUM�̏ꍇ
							if (strcmp(cHeadText, "MAX_TEXTURE_RANDOM_NUM") == INIT_INT)
							{
								// ����m_nMaxTex_RandomNum�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nMaxTex_RandomNum);
							}
							// cHeadText��ALPHA_NUM�̏ꍇ
							if (strcmp(cHeadText, "ALPHA_NUM") == INIT_INT)
							{
								// ����m_nAlpha�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nAlpha);
							}
							// cHeadText��SIZE�̏ꍇ
							if (strcmp(cHeadText, "SIZE") == INIT_INT)
							{
								// ����m_bRandomPos�Ɋi�[
								sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &m_size.x, &m_size.y, &m_size.z);
							}
							// cHeadText��MOVE�̏ꍇ
							if (strcmp(cHeadText, "MOVE") == INIT_INT)
							{
								// ����m_move�Ɋi�[
								sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &m_move.x, &m_move.y, &m_move.z);
							}
							// cHeadText��ANGLE�̏ꍇ
							if (strcmp(cHeadText, "ANGLE") == INIT_INT)
							{
								// ����m_fAngle�Ɋi�[
								sscanf(cReedText, "%s %s %f", &cDie, &cDie, &m_fAngle);
							}
							// cHeadText��ANGLE�̏ꍇ
							if (strcmp(cHeadText, "ADD_ANGLE") == INIT_INT)
							{
								// ����m_fAngle�Ɋi�[
								sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &m_AddAngle.x, &m_AddAngle.y, &m_AddAngle.z);
							}
							// cHeadText��COLOR�̏ꍇ
							if (strcmp(cHeadText, "COLOR") == INIT_INT)
							{
								// ����m_color�Ɋi�[
								sscanf(cReedText, "%s %s %f %f %f %f", &cDie, &cDie, &m_color.r, &m_color.g, &m_color.b, &m_color.a);
							}
							// cHeadText��LIFE_VALUE�̏ꍇ
							if (strcmp(cHeadText, "LIFE_VALUE") == INIT_INT)
							{
								// ����m_nLife�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nLife);
							}
							// cHeadText��ADD_SCALE_VALUE�̏ꍇ
							if (strcmp(cHeadText, "ADD_SCALE_VALUE") == INIT_INT)
							{
								/// ����m_fAddScale�Ɋi�[
								sscanf(cReedText, "%s %s %f", &cDie, &cDie, &m_fAddScale);
							}
							// cHeadText��COLOR_SUB_VALUE�̏ꍇ
							if (strcmp(cHeadText, "COLOR_R_VALUE") == INIT_INT)
							{
								// ����m_SubColor�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nColorR);
							}
							// cHeadText��COLOR_SUB_VALUE�̏ꍇ
							if (strcmp(cHeadText, "COLOR_G_VALUE") == INIT_INT)
							{
								// ����m_SubColor�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nColorG);
							}
							// cHeadText��COLOR_SUB_VALUE�̏ꍇ
							if (strcmp(cHeadText, "COLOR_B_VALUE") == INIT_INT)
							{
								// ����m_SubColor�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nColorB);
							}
							// cHeadText��COLOR_SUB_VALUE�̏ꍇ
							if (strcmp(cHeadText, "COLOR_SUB_VALUE") == INIT_INT)
							{
								// ����m_SubColor�Ɋi�[
								sscanf(cReedText, "%s %s %f %f %f %f", &cDie, &cDie, &m_SubColor.r, &m_SubColor.g, &m_SubColor.b, &m_SubColor.a);
							}
							// cHeadText��MIN_SIZE_VALUE�̏ꍇ
							if (strcmp(cHeadText, "MIN_SIZE_VALUE") == INIT_INT)
							{
								// ����m_fRandom_Min_Size�Ɋi�[
								sscanf(cReedText, "%s %s %f", &cDie, &cDie, &m_fRandom_Min_Size);
							}
							// cHeadText��MAX_SIZE_VALUE�̏ꍇ
							if (strcmp(cHeadText, "MAX_SIZE_VALUE") == INIT_INT)
							{
								// ����m_fRandom_Max_Size�Ɋi�[
								sscanf(cReedText, "%s %s %f", &cDie, &cDie, &m_fRandom_Max_Size);
							}
							// cHeadText��RANDOM_POS_VALUE�̏ꍇ
							if (strcmp(cHeadText, "RANDOM_POS_VALUE") == INIT_INT)
							{
								// ����m_fRandomPos�Ɋi�[
								sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &m_Random_pos.x, &m_Random_pos.y, &m_Random_pos.z);
							}
							// cHeadText��RANDOM_POS_VALUE�̏ꍇ
							if (strcmp(cHeadText, "RANDOM_POS_VALUE") == INIT_INT)
							{
								// ����m_fRandomPos�Ɋi�[
								sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &m_Random_pos.x, &m_Random_pos.y, &m_Random_pos.z);
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
// �e�N�X�`���ԍ��ݒ�
//******************************************************************************
void C2D_Particle::SetTexNum(int nTexNum)
{
	m_nTexNum = nTexNum;
}
//******************************************************************************
// �G�t�F�N�g����
//******************************************************************************
void C2D_Particle::CreateEffect(D3DXVECTOR3 pos, int nCreateNum, const char *cText)
{
	// ��������
	for (int nCnt = INIT_INT; nCnt < nCreateNum; nCnt++)
	{
		// ����
		Create(pos, cText);
	}
}
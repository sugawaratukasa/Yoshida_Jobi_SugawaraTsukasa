//******************************************************************************
// �p�[�e�B�N��[particle.cpp]
// Author : �ǌ��@�i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "pbillboard.h"
#include "resource_manager.h"
#include "particle_texture.h"
#include "particle.h"
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
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CParticle::CParticle(PRIORITY Priority) : CpBillboard(Priority)
{
	m_bAlpha_Blend		= false;
	m_bLife				= false;
	m_bRandomPos		= false;
	m_bRandomSize		= false;
	m_bAddScale			= false;
	m_bSubColor			= false;
	m_bRotRandom		= false;
	m_bTexRandom		= false;
	m_Random_pos		= ZeroVector3;
	m_size				= ZeroVector3;
	m_move				= ZeroVector3;
	m_AddAngle			= ZeroVector3;
	m_color				= WhiteColor;
	m_SubColor			= WhiteColor;
	m_nAlpha			= ZERO_INT;
	m_nLife				= ZERO_INT;
	m_nTexNum			= ZERO_INT;
	m_nMinTex_RandomNum = ZERO_INT;
	m_nMaxTex_RandomNum = ZERO_INT;
	m_fAngle			= ZERO_FLOAT;
	m_fAddAngle			= ZERO_FLOAT;
	m_fRandom_Min_Size	= ZERO_FLOAT;
	m_fRandom_Max_Size	= ZERO_FLOAT;
	m_fAddScale			= ZERO_FLOAT;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CParticle::~CParticle()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CParticle *CParticle::Create(D3DXVECTOR3 pos, const char *cText)
{
	// CParticle�̃|�C���^
	CParticle *pParticle = nullptr;

	// nullptr�̏ꍇ
	if (pParticle == nullptr)
	{
		// �������m��
		pParticle = new CParticle;

		// NULL�łȂ��ꍇ
		if (pParticle != nullptr)
		{
			// ������
			pParticle->Init(pos, cText);
		}
	}
	// �|�C���^��Ԃ�
	return pParticle;
}

//******************************************************************************
// ������
//******************************************************************************
HRESULT CParticle::Init(D3DXVECTOR3 pos, const char *cText)
{
	// �e�L�X�g�ǂݍ���
	LoadParticle(cText);

	// ������
	CpBillboard::Init(pos, m_size);

	// �T�C�Y�ݒ�
	SetSize(m_size);

	// �T�C�Y�ݒ�
	SetRotation(ROT);

	// �F�ݒ�
	SetColor(m_color);

	// �Z�b�g�A���t�@
	SetAlpha(m_nAlpha);

	// �e�N�X�`���̃|�C���^�擾
	CParticle_Texture *pParticle_Texture = CManager::GetResourceManager()->GetParticle_Texture();

	// !nullcheck
	if (pParticle_Texture != nullptr)
	{
		// false�̏ꍇ
		if (m_bTexRandom == false)
		{
			// �e�N�X�`���󂯓n��
			BindTexture(pParticle_Texture->GetTexture(m_nTexNum));
		}
		// true�̏ꍇ
		if (m_bTexRandom == true)
		{
			// �e�N�X�`�������_��
			int nTexNum = m_nMinTex_RandomNum + (int)(rand() * (m_nMaxTex_RandomNum - m_nMinTex_RandomNum + 1.0f) / (1.0f + RAND_MAX));

			// �e�N�X�`���󂯓n��
			BindTexture(pParticle_Texture->GetTexture(nTexNum));
		}
	}
	// true�̏ꍇ
	if (m_bRotRandom == true)
	{
		D3DXVECTOR3 rot = ZeroVector3;

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
		D3DXVECTOR3 size = ZeroVector3;

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
		D3DXVECTOR3 Random_pos = ZeroVector3;

		// �ʒu�����_��
		Random_pos.x = float(rand() % (int)m_Random_pos.x *RANDOM_POS_MUT * MUT - (int)m_Random_pos.x *RANDOM_POS_MUT / MUT);

		// ���Z
		Random_pos.x = Random_pos.x / RANDOM_POS_MUT;

		// y��0���傫���ꍇ
		if (m_Random_pos.y > ZERO_FLOAT)
		{
			// �ʒu�����_��
			Random_pos.y = float(rand() % (int)m_Random_pos.y * RANDOM_POS_MUT);

			// ���Z
			Random_pos.y = Random_pos.y / RANDOM_POS_MUT;
		}
		// �ʒu�����_��
		pos += Random_pos;

		// �ʒu�ݒ�
		SetPosition(pos);
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
void CParticle::Uninit(void)
{
	// �I��
	CpBillboard::Uninit();
}

//******************************************************************************
// �X�V
//******************************************************************************
void CParticle::Update(void)
{
	// �X�V
	CpBillboard::Update();

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

	SetPosition(pos);
}

//******************************************************************************
// �`��
//******************************************************************************
void CParticle::Draw(void)
{
	// ���Z�������s��Ȃ��ꍇ
	if (m_bAlpha_Blend == false)
	{
		// �`��
		CpBillboard::Draw();
	}
	// ���Z�������s���ꍇ
	if (m_bAlpha_Blend == true)
	{
		// �����_���[�擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// ���Z�����̐ݒ�
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		// �`��
		CpBillboard::Draw();

		// ���ɖ߂�
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}
//******************************************************************************
// ���ݒ�
//******************************************************************************
void CParticle::LoadParticle(const char * cText)
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
							if (strcmp(cHeadText, "ALPHA_BLEND") == ZERO_INT)
							{
								// ����m_bAlpha_Blend�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bAlpha_Blend);
							}
							// cHeadText��LIFE�̏ꍇ
							if (strcmp(cHeadText, "LIFE") == ZERO_INT)
							{
								// ����m_bLife�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bLife);
							}
							// cHeadText��RANDOM_POS�̏ꍇ
							if (strcmp(cHeadText, "RANDOM_POS") == ZERO_INT)
							{
								// ����m_bRandomPos�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bRandomPos);
							}
							// cHeadText��RANDOM_SIZE�̏ꍇ
							if (strcmp(cHeadText, "RANDOM_SIZE") == ZERO_INT)
							{
								// ����m_bRandomSize�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bRandomSize);
							}
							// cHeadText��ADD_SCALE�̏ꍇ
							if (strcmp(cHeadText, "ADD_SCALE") == ZERO_INT)
							{
								// ����m_bAddScale�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bAddScale);
							}
							// cHeadText��COLOR_SUBTRACT�̏ꍇ
							if (strcmp(cHeadText, "COLOR_SUBTRACT") == ZERO_INT)
							{
								// ����m_bSubColor�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bSubColor);
							}
							// cHeadText��ROT_RANDOM�̏ꍇ
							if (strcmp(cHeadText, "ROT_RANDOM") == ZERO_INT)
							{
								// ����m_bRotRandom�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bRotRandom);
							}
							// cHeadText��TEX_RANDOM�̏ꍇ
							if (strcmp(cHeadText, "TEX_RANDOM") == ZERO_INT)
							{
								// ����m_bTexRandom�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bTexRandom);
							}
							// cHeadText��TEXTURE_NUM�̏ꍇ
							if (strcmp(cHeadText, "TEXTURE_NUM") == ZERO_INT)
							{
								// ����m_nTexNum�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nTexNum);
							}
							// cHeadText��MIN_TEXTURE_RANDOM_NUM�̏ꍇ
							if (strcmp(cHeadText, "MIN_TEXTURE_RANDOM_NUM") == ZERO_INT)
							{
								// ����m_nMinTex_RandomNum�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nMinTex_RandomNum);
							}
							// cHeadText��MAX_TEXTURE_RANDOM_NUM�̏ꍇ
							if (strcmp(cHeadText, "MAX_TEXTURE_RANDOM_NUM") == ZERO_INT)
							{
								// ����m_nMaxTex_RandomNum�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nMaxTex_RandomNum);
							}
							// cHeadText��ALPHA_NUM�̏ꍇ
							if (strcmp(cHeadText, "ALPHA_NUM") == ZERO_INT)
							{
								// ����m_nAlpha�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nAlpha);
							}
							// cHeadText��SIZE�̏ꍇ
							if (strcmp(cHeadText, "SIZE") == ZERO_INT)
							{
								// ����m_bRandomPos�Ɋi�[
								sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &m_size.x, &m_size.y, &m_size.z);
							}
							// cHeadText��MOVE�̏ꍇ
							if (strcmp(cHeadText, "MOVE") == ZERO_INT)
							{
								// ����m_move�Ɋi�[
								sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &m_move.x, &m_move.y, &m_move.z);
							}
							// cHeadText��ANGLE�̏ꍇ
							if (strcmp(cHeadText, "ANGLE") == ZERO_INT)
							{
								// ����m_fAngle�Ɋi�[
								sscanf(cReedText, "%s %s %f", &cDie, &cDie, &m_fAngle);
							}
							// cHeadText��ANGLE�̏ꍇ
							if (strcmp(cHeadText, "ADD_ANGLE") == ZERO_INT)
							{
								// ����m_fAngle�Ɋi�[
								sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &m_AddAngle.x, &m_AddAngle.y, &m_AddAngle.z);
							}
							// cHeadText��COLOR�̏ꍇ
							if (strcmp(cHeadText, "COLOR") == ZERO_INT)
							{
								// ����m_color�Ɋi�[
								sscanf(cReedText, "%s %s %f %f %f %f", &cDie, &cDie, &m_color.r, &m_color.g, &m_color.b, &m_color.a);
							}
							// cHeadText��LIFE_VALUE�̏ꍇ
							if (strcmp(cHeadText, "LIFE_VALUE") == ZERO_INT)
							{
								// ����m_nLife�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nLife);
							}
							// cHeadText��ADD_SCALE_VALUE�̏ꍇ
							if (strcmp(cHeadText, "ADD_SCALE_VALUE") == ZERO_INT)
							{
								/// ����m_fAddScale�Ɋi�[
								sscanf(cReedText, "%s %s %f", &cDie, &cDie, &m_fAddScale);
							}
							// cHeadText��COLOR_SUB_VALUE�̏ꍇ
							if (strcmp(cHeadText, "COLOR_SUB_VALUE") == ZERO_INT)
							{
								// ����m_SubColor�Ɋi�[
								sscanf(cReedText, "%s %s %f %f %f %f", &cDie, &cDie, &m_SubColor.r, &m_SubColor.g, &m_SubColor.b, &m_SubColor.a);
							}
							// cHeadText��MIN_SIZE_VALUE�̏ꍇ
							if (strcmp(cHeadText, "MIN_SIZE_VALUE") == ZERO_INT)
							{
								// ����m_fRandom_Min_Size�Ɋi�[
								sscanf(cReedText, "%s %s %f", &cDie, &cDie, &m_fRandom_Min_Size);
							}
							// cHeadText��MAX_SIZE_VALUE�̏ꍇ
							if (strcmp(cHeadText, "MAX_SIZE_VALUE") == ZERO_INT)
							{
								// ����m_fRandom_Max_Size�Ɋi�[
								sscanf(cReedText, "%s %s %f", &cDie, &cDie, &m_fRandom_Max_Size);
							}
							// cHeadText��RANDOM_POS_VALUE�̏ꍇ
							if (strcmp(cHeadText, "RANDOM_POS_VALUE") == ZERO_INT)
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
void CParticle::SetTexNum(int nTexNum)
{
	m_nTexNum = nTexNum;
}
//******************************************************************************
// �G�t�F�N�g����
//******************************************************************************
void CParticle::CreateEffect(D3DXVECTOR3 pos, int nCreateNum, const char *cText)
{
	// ��������
	for (int nCnt = ZERO_INT; nCnt < nCreateNum; nCnt++)
	{
		// ����
		Create(pos, cText);
	}
}
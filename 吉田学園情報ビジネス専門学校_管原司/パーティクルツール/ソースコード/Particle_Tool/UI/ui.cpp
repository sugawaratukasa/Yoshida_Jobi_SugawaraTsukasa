//***********************************************************************************
//	UI	[ui.cpp]
//	Author : �ǌ� �i
//***********************************************************************************
//***********************************************************************************
// �C���N���[�h�t�@�C��
//***********************************************************************************
#include "main.h"
#include "manager.h"
#include "texture.h"
#include "ui.h"
#include <tchar.h>
//***********************************************************************************
// �}�N����`
//***********************************************************************************
#define MAX_SIZE				(100.0f)									// �T�C�Y�̍ő�l
#define MIN_SIZE				(0.0f)										// �T�C�Y�̍ŏ��l
#define MAX_MOVE				(10.0f)										// �ړ��ʂ̍ő�l
#define MIN_MOVE				(-10.0f)									// �ړ��ʂ̍ŏ��l
#define MAX_SCALE				(5.0f)										// �g�嗦�̍ő�l
#define MIN_SCALE				(-5.0f)										// �g�嗦�̍ŏ��l
#define MAX_ANGLE				(360.0f)									// �p�x�̍ő�l
#define MIN_ANGLE				(1.0f)										// �p�x�̍ŏ��l
#define MAX_COUNT				(500)										// �J�E���g�̍ő�l
#define MIN_COUNT				(1)											// �J�E���g�̍ŏ��l
#define SLIDER_VALUE			(1.0f)										// �X���C�_�[�̉��Z��
#define SLIDER_VALUE2			(0.01f)										// �X���C�_�[�̉��Z��
#define SLIDER_VALUE3			(1)											// �X���C�_�[�̉��Z��
#define DEFAULT_SIZE			(30.0f)										// �T�C�Y�̊�l
#define DEFAULT_COUNT			(10)										// �J�E���g�̊�l
#define DEFAULT_ANGLE			(360.0f)									// �p�x�̊�l
#define SIZE					(D3DXVECTOR3(m_fSize, m_fSize, 0.0f))		// �T�C�Y
#define SIZE_2					(D3DXVECTOR3(m_fSize_2, m_fSize_2, 0.0f))	// �T�C�Y
#define COLOR					(D3DXCOLOR(1.0f,1.0f, 1.0f, 1.0f))			// �F
#define NAME_NUM				(16)										// ���O
#define MIN_TEX					(0)											// �e�N�X�`���̍ŏ���
#define SUB_TEXTURENUM			(1)											// �e�N�X�`���̔ԍ���-1
#define MIN_ALPHA				(0)											// �A���t�@�̍ŏ��l
#define MAX_ALPHA				(255)										// �A���t�@�̍ő�l
#define SUBCOLOR_SLIDE			(0.01f)										// �F���Z�X���C�_�[
#define MIN_SUBCOLOR			(0.0f)										// �F���Z�ŏ��l
#define MAX_SUBCOLOR			(1.0f)										// �F���Z
#define MAX_LIFE				(50)										// �J�E���g�̍ő�l
#define MIN_LIFE				(1)											// �J�E���g�̍ŏ��l
#define RANDOM_MIN_SIZE			(1.0f)										// �����_���T�C�Y�̍ŏ��l
#define RANDOM_SIZE_INIT		(30.0f)										// �����_���T�C�Y�̏����l
#define RANDOM_MIN_POS			(1.0f)										// �����_���ʒu�̍ŏ�
#define RANDOM_MAX_POS			(100.0f)									// �����_���ʒu�̍ŏ�
#define INIT_LIFE				(30)										// ���C�t�����l
#define RANDOM_POS_INIT			(50.0f)										// �����_���ʒu�̏����l
#define CREATE_TOTALCOUNT_INIT	(30)										// �����̑����̏����l
#define MAX_TEXT				(1024)										// �e�L�X�g�̍ő吔
#define MIN_ADDANGLE			(-30.0f)									// �p�x���Z�ŏ��l
#define MAX_ADDANGLE			(30.0f)										// �p�x���Z�ő�l
#define MIN_ROT					(0.0f)										// �p�x���Z�ŏ��l
#define MAX_ROT					(360.0f)									// �p�x���Z�ő�l
#define INIT_COLORRANDOM		(255)										// �F�̃����_���l
#define MIN_RANDOMCOL			(1)											// �����_���J���[�ŏ��l
#define MAX_RANDOMCOL			(255)										// �����_���J���[�ő�l
//***********************************************************************************
//�ÓI�����o�ϐ�
//***********************************************************************************
//***********************************************************************************
// �R���X�g���N�^
//***********************************************************************************
CUI::CUI(int nPriority)
{
	m_bSetting_window	= true;
	m_bSettingNoad_1	= false;
	m_bSettingNoad_2	= false;
	m_bEmitter			= false;
	m_bEffect			= false;
	m_bAlpha_Blend		= false;
	m_bLife				= true;
	m_bRandomPos		= false;
	m_bRandomSize		= false;
	m_bAddScale			= false;
	m_bSubColor			= false;
	m_bSave				= false;
	m_bLoad				= false;
	m_bSameSize			= false;
	m_bRotRandom		= false;
	m_bTex_Random		= false;
	m_bColorRandom		= false;
	m_fSize				= INIT_FLOAT;
	m_pos				= INIT_D3DXVECTOR3;
	m_rot				= INIT_D3DXVECTOR3;
	m_size				= INIT_D3DXVECTOR3;
	m_move				= INIT_D3DXVECTOR3;
	m_AddAngle			= INIT_D3DXVECTOR3;
	m_color				= INIT_COLOR;
	m_SubColor			= INIT_COLOR;
	m_fAddScale			= INIT_FLOAT;
	m_fAngle			= INIT_FLOAT;
	m_fRandom_Max_Size	= INIT_FLOAT;
	m_fRandom_Min_Size	= INIT_FLOAT;
	m_nCreateCount		= INIT_INT;
	m_nCreateTotalCount = INIT_INT;
	m_nTexNum			= INIT_INT;
	m_nAlpha			= INIT_INT;
	m_nLife				= INIT_INT;
	m_nMinTexRamdomNum	= INIT_INT;
	m_nMaxTexRamdomNum	= INIT_INT;
	m_nColor_R			= INIT_INT;
	m_nColor_G			= INIT_INT;
	m_nColor_B			= INIT_INT;
	memset(m_cSave, NULL, sizeof(m_cSave));
	memset(m_cLoad, NULL, sizeof(m_cLoad));
	//**********************************************
	// ���
	//**********************************************
	m_bEmitter_2			= false;
	m_bEffect_2				= false;
	m_bAlpha_Blend_2		= false;
	m_bLife_2				= true;
	m_bRandomPos_2			= false;
	m_bRandomSize_2			= false;
	m_bAddScale_2			= false;
	m_bSubColor_2			= false;
	m_bSave_2				= false;
	m_bLoad_2				= false;
	m_bSameSize_2			= false;
	m_bRotRandom_2			= false;
	m_bTex_Random_2			= false;
	m_bColorRandom_2		= false;
	m_fSize_2				= INIT_FLOAT;
	m_pos_2					= INIT_D3DXVECTOR3;
	m_rot_2					= INIT_D3DXVECTOR3;
	m_size_2				= INIT_D3DXVECTOR3;
	m_move_2				= INIT_D3DXVECTOR3;
	m_AddAngle_2			= INIT_D3DXVECTOR3;
	m_color_2				= INIT_COLOR;
	m_SubColor_2			= INIT_COLOR;
	m_fAddScale_2			= INIT_FLOAT;
	m_fAngle_2				= INIT_FLOAT;
	m_fRandom_Max_Size_2	= INIT_FLOAT;
	m_fRandom_Min_Size_2	= INIT_FLOAT;
	m_nCreateCount_2		= INIT_INT;
	m_nCreateTotalCount_2	= INIT_INT;
	m_nTexNum_2				= INIT_INT;
	m_nAlpha_2				= INIT_INT;
	m_nLife_2				= INIT_INT;
	m_nMinTexRamdomNum_2	= INIT_INT;
	m_nMaxTexRamdomNum_2	= INIT_INT;
	m_nColor_R_2			= INIT_INT;
	m_nColor_G_2			= INIT_INT;
	m_nColor_B_2			= INIT_INT;
	memset(m_cSave_2, NULL, sizeof(m_cSave_2));
	memset(m_cLoad_2, NULL, sizeof(m_cSave_2));
}
//***********************************************************************************
// �f�X�g���N�^
//***********************************************************************************
CUI::~CUI()
{
}
//***********************************************************************************
// �����֐�
//***********************************************************************************
CUI * CUI::Create(void)
{
	// CUI�̃|�C���^
	CUI *pUi = NULL;

	// NULL�̏ꍇ
	if (pUi == NULL)
	{
		// �������m��
		pUi = new CUI;

		// NULL�łȂ��ꍇ
		if (pUi != NULL)
		{
			// ������
			pUi->Init();
		}
	}
	// �|�C���^��Ԃ�
	return pUi;
}
//***********************************************************************************
// �������֐�
//***********************************************************************************
HRESULT CUI::Init(void)
{
	// �F
	m_color = COLOR;

	// �T�C�Yx
	m_size.x = DEFAULT_SIZE;

	// �T�C�Yx
	m_size.y = DEFAULT_SIZE;

	// �T�C�Y
	m_fSize = DEFAULT_SIZE;

	// �����_���T�C�Y
	m_fRandom_Min_Size = RANDOM_SIZE_INIT;

	// �����_���T�C�Y
	m_fRandom_Max_Size = RANDOM_SIZE_INIT;

	// �p�x
	m_fAngle = DEFAULT_ANGLE;

	// �J�E���g
	m_nCreateCount = DEFAULT_COUNT;

	// �����̑���
	m_nCreateTotalCount = CREATE_TOTALCOUNT_INIT;

	// ���C�t
	m_nLife = INIT_LIFE;

	// �����_���ʒu
	m_pos.x = RANDOM_POS_INIT;

	// �����_���ʒu
	m_pos.y = RANDOM_POS_INIT;

	// �e�N�X�`�����擾
	int nTexNum = CManager::GetTexture()->GetTexNum();

	// �����_���e�N�X�`���̍ő�
	m_nMaxTexRamdomNum = nTexNum - SUB_TEXTURENUM;

	// �����_���F�̏����l
	m_nColor_R = INIT_COLORRANDOM;
	m_nColor_G = INIT_COLORRANDOM;
	m_nColor_B = INIT_COLORRANDOM;

	//**********************************************************
	// 2�Ԗڂ̃m�[�h
	//**********************************************************

	// �F
	m_color_2 = COLOR;

	// �T�C�Yx
	m_size_2.x = DEFAULT_SIZE;

	// �T�C�Yx
	m_size_2.y = DEFAULT_SIZE;

	// �T�C�Y
	m_fSize_2 = DEFAULT_SIZE;

	// �����_���T�C�Y
	m_fRandom_Min_Size_2 = RANDOM_SIZE_INIT;

	// �����_���T�C�Y
	m_fRandom_Max_Size_2 = RANDOM_SIZE_INIT;

	// �p�x
	m_fAngle_2 = DEFAULT_ANGLE;

	// �J�E���g
	m_nCreateCount_2 = DEFAULT_COUNT;

	// �����̑���
	m_nCreateTotalCount_2 = CREATE_TOTALCOUNT_INIT;

	// ���C�t
	m_nLife_2 = INIT_LIFE;

	// �����_���ʒu
	m_pos_2.x = RANDOM_POS_INIT;

	// �����_���ʒu
	m_pos_2.y = RANDOM_POS_INIT;

	// �����_���e�N�X�`���̍ő�
	m_nMaxTexRamdomNum_2 = nTexNum - SUB_TEXTURENUM;

	// �����_���F�̏����l
	m_nColor_R_2 = INIT_COLORRANDOM;
	m_nColor_G_2 = INIT_COLORRANDOM;
	m_nColor_B_2 = INIT_COLORRANDOM;
	return S_OK;
}
//***********************************************************************************
// �I���֐�
//***********************************************************************************
void CUI::Uninit(void)
{
	// �j��
	Release();
}
//***********************************************************************************
// �X�V�֐�
//***********************************************************************************
void CUI::Update(void)
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// �E�B���h�E
	if (m_bSetting_window)
	{
		// �E�B���h�E����
		ImGui::Begin("SettingWindows");

		// ��Ԗڂ̃m�[�h�̐ݒ�
		SettingNoad_1();

		// 2�Ԗڂ̃m�[�h�̐ݒ�
		SettingNoad_2();

		ImGui::End();
	}
	// �X�V�����̏I����
	ImGui::EndFrame();
}
//***********************************************************************************
// �`��֐�
//***********************************************************************************
void CUI::Draw(void)
{
}
//***********************************************************************************
// ���ۑ��֐�
//***********************************************************************************
void CUI::Save(const char *cText)
{
	FILE * pFile = NULL;

	// �e�L�X�g
	char cSaveText[MAX_TEXT] = {};

	// �ǂݍ���
	sprintf(cSaveText, "%s.txt", cText);

	// NULL�̏ꍇ
	if (pFile == NULL)
	{
		// �t�@�C���̏����o��
		pFile = fopen(cSaveText, "w");

		// �t�@�C�����󂶂�Ȃ���
		if (pFile != NULL)
		{
			// ��������
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �p�[�e�B�N���f�[�^�ۑ��e�L�X�g\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "SCRIPT\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �e��ݒ�\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "SETTINGS\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �����J�E���g\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "CREATE_COUNT = %d\n", m_nCreateCount);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �����̑���\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "CREATE_TOTAL_COUNT = %d\n", m_nCreateTotalCount);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# Effect��Emitter���g�p����[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "EMITTER = %d\n", (int)m_bEmitter);
			fprintf(pFile, "EFFECT = %d\n", (int)m_bEffect);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# ���Z�����g�p����[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "ALPHA_BLEND = %d\n", (int)m_bAlpha_Blend);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# ���C�t�̎g�p����[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "LIFE = %d\n", (int)m_bLife);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �ʒu�������_���g�p����[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "RANDOM_POS = %d\n", (int)m_bRandomPos);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �����_���T�C�Y�g�p����[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "RANDOM_SIZE = %d\n", (int)m_bRandomSize);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �g��g�p����[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "ADD_SCALE = %d\n", (int)m_bAddScale);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �F���Z�̎g�p����[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "COLOR_SUBTRACT = %d\n", (int)m_bSubColor);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# ���������_���̎g�p����[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "ROT_RANDOM = %d\n", (int)m_bRotRandom);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �e�N�X�`�������_���̎g�p����[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "TEX_RANDOM = %d\n", (int)m_bTex_Random);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �F�����_���̎g�p����[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "COLOR_RANDOM = %d\n", (int)m_bColorRandom);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �e�N�X�`���i���o�[\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "TEXTURE_NUM = %d\n", m_nTexNum);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �����_���e�N�X�`���i���o�[\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "MIN_TEXTURE_RANDOM_NUM = %d\n", m_nMinTexRamdomNum);
			fprintf(pFile, "MAX_TEXTURE_RANDOM_NUM = %d\n", m_nMaxTexRamdomNum);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# ���ߒl\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "ALPHA_NUM = %d\n", m_nAlpha);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �T�C�Y\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "SIZE = %.1f %.1f %.1f\n", m_size.x, m_size.y, m_size.z);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �ړ���\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "MOVE = %.1f %.1f %.1f\n", m_move.x, m_move.y, m_move.z);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �p�x\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "ANGLE = %.1f\n", m_fAngle);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �p�x���Z\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "ADD_ANGLE = %.1f %.1f %.1f\n", m_AddAngle.x, m_AddAngle.y, m_AddAngle.z);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �F\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "COLOR = %.1f %.1f %.1f %.1f \n", m_color.r, m_color.g, m_color.b, m_color.a);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# ���C�t�̒l\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "LIFE_VALUE = %d\n", m_nLife);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �g�嗦���Z�̒l\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "ADD_SCALE_VALUE = %.3f\n", m_fAddScale);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �F�����_���̒l\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "COLOR_R_VALUE = %d\n", m_nColor_R);
			fprintf(pFile, "COLOR_G_VALUE = %d\n", m_nColor_G);
			fprintf(pFile, "COLOR_B_VALUE = %d\n", m_nColor_B);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �F���Z�l�̒l\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "COLOR_SUB_VALUE = %.3f %.3f %.3f %.3f \n", m_SubColor.r, m_SubColor.g, m_SubColor.b, m_SubColor.a);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �����_���T�C�Y�̒l[�ŏ�/�ő�]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "MIN_SIZE_VALUE = %.1f\n", m_fRandom_Min_Size);
			fprintf(pFile, "MAX_SIZE_VALUE = %.1f\n", m_fRandom_Max_Size);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �ʒu�����_���̒l\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "RANDOM_POS_VALUE = %.1f %.1f %.1f\n", m_pos.x, m_pos.y, m_pos.z);
			fprintf(pFile, "END_SETTINGS\n");
			fprintf(pFile, "\n");
			fprintf(pFile, "END_SCRIPT");

			// �t�@�C�������
			fclose(pFile);
		}
	}
}
//***********************************************************************************
// ���ۑ��֐�
//***********************************************************************************
void CUI::Save2(const char * cText)
{
	FILE * pFile = NULL;

	// �e�L�X�g
	char cSaveText[MAX_TEXT] = {};

	// �ǂݍ���
	sprintf(cSaveText, "%s.txt", cText);

	// NULL�̏ꍇ
	if (pFile == NULL)
	{
		// �t�@�C���̏����o��
		pFile = fopen(cSaveText, "w");

		// �t�@�C�����󂶂�Ȃ���
		if (pFile != NULL)
		{
			// ��������
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �p�[�e�B�N���f�[�^�ۑ��e�L�X�g\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "SCRIPT\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �e��ݒ�\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "SETTINGS\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# Effect��Emitter���g�p����[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "EMITTER = %d\n", (int)m_bEmitter_2);
			fprintf(pFile, "EFFECT = %d\n", (int)m_bEffect_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# ���Z�����g�p����[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "ALPHA_BLEND = %d\n", (int)m_bAlpha_Blend_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# ���C�t�̎g�p����[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "LIFE = %d\n", (int)m_bLife_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �ʒu�������_���g�p����[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "RANDOM_POS = %d\n", (int)m_bRandomPos_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �����_���T�C�Y�g�p����[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "RANDOM_SIZE = %d\n", (int)m_bRandomSize_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "ADD_SCALE = %d\n", (int)m_bAddScale_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �F���Z�̎g�p����[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "COLOR_SUBTRACT = %d\n", (int)m_bSubColor_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# ���������_���̎g�p����[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "ROT_RANDOM = %d\n", (int)m_bRotRandom_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �e�N�X�`�������_���̎g�p����[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "TEX_RANDOM = %d\n", (int)m_bTex_Random_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �F�����_���̎g�p����[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "COLOR_RANDOM = %d\n", (int)m_bColorRandom);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �e�N�X�`���i���o�[\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "TEXTURE_NUM = %d\n", m_nTexNum_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �����_���e�N�X�`���i���o�[\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "MIN_TEXTURE_RANDOM_NUM = %d\n", m_nMinTexRamdomNum_2);
			fprintf(pFile, "MAX_TEXTURE_RANDOM_NUM = %d\n", m_nMaxTexRamdomNum_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# ���ߒl\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "ALPHA_NUM = %d\n", m_nAlpha_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �T�C�Y\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "SIZE = %.1f %.1f %.1f\n", m_size_2.x, m_size_2.y, m_size_2.z);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �ړ���\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "MOVE = %.1f %.1f %.1f\n", m_move_2.x, m_move_2.y, m_move_2.z);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �g��g�p����[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �p�x\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "ANGLE = %.1f\n", m_fAngle_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �p�x���Z\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "ADD_ANGLE = %.1f %.1f %.1f\n", m_AddAngle.x, m_AddAngle.y, m_AddAngle.z);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �F\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "COLOR = %.1f %.1f %.1f %.1f \n", m_color_2.r, m_color_2.g, m_color_2.b, m_color_2.a);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �����J�E���g\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "CREATE_COUNT = %d\n", m_nCreateCount_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# ��������\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "CREATE_COUNT = %d\n", m_nCreateTotalCount_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# ���C�t�̒l\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "LIFE_VALUE = %d\n", m_nLife_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �g�嗦���Z�̒l\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "ADD_SCALE_VALUE = %.3f\n", m_fAddScale_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �F�����_���̒l\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "COLOR_R_VALUE = %d\n", m_nColor_R);
			fprintf(pFile, "COLOR_G_VALUE = %d\n", m_nColor_G);
			fprintf(pFile, "COLOR_B_VALUE = %d\n", m_nColor_B);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �F���Z�l�̒l\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "COLOR_SUB_VALUE = %.3f %.3f %.3f %.3f \n", m_SubColor_2.r, m_SubColor_2.g, m_SubColor_2.b, m_SubColor_2.a);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �����_���T�C�Y�̒l[�ŏ�/�ő�]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "MIN_SIZE_VALUE = %.1f\n", m_fRandom_Min_Size_2);
			fprintf(pFile, "MAX_SIZE_VALUE = %.1f\n", m_fRandom_Max_Size_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# �ʒu�����_���̒l\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "RANDOM_POS_VALUE = %.1f %.1f %.1f\n", m_pos_2.x, m_pos_2.y, m_pos_2.z);
			fprintf(pFile, "END_SETTINGS\n");
			fprintf(pFile, "\n");
			fprintf(pFile, "END_SCRIPT");

			// �t�@�C�������
			fclose(pFile);
		}
	}
}
//***********************************************************************************
// ���ǂݍ��݊֐�
//***********************************************************************************
void CUI::Load(const char * cText)
{
	// �ǂݍ��ݗp
	char cReedText[MAX_TEXT];

	// �����̔��ʗp
	char cHeadText[MAX_TEXT];

	// �g��Ȃ�����
	char cDie[MAX_TEXT];

	// �e�L�X�g
	char cSaveText[MAX_TEXT];

	// �ǂݍ���
	sprintf(cSaveText, "%s.txt", cText);

	// �t�@�C���|�C���^
	FILE *pFile = NULL;

	// NULL�̏ꍇ
	if (pFile == NULL)
	{
		//�t�@�C�����J��
		pFile = fopen(cSaveText, "r");

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

							// cHeadText��EMITTER�̏ꍇ
							if (strcmp(cHeadText, "EMITTER") == INIT_INT)
							{
								// ����m_bEmitter�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bEmitter);
							}
							// cHeadText��EFFECT�̏ꍇ
							if (strcmp(cHeadText, "EFFECT") == INIT_INT)
							{
								// ����m_bEffect�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bEffect);
							}
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
							// cHeadText��COLOR_SUBTRACT�̏ꍇ
							if (strcmp(cHeadText, "ROT_RANDOM") == INIT_INT)
							{
								// ����m_bSubColor�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bRotRandom);
							}
							// cHeadText��TEXTURE_NUM�̏ꍇ 
							if (strcmp(cHeadText, "TEXTURE_NUM") == INIT_INT)
							{
								// ����m_nTexNum�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nTexNum);
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
							// cHeadText��CREATE_COUNT�̏ꍇ
							if (strcmp(cHeadText, "CREATE_COUNT") == INIT_INT)
							{
								// ����m_nCreateCount�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nCreateCount);
							}
							// cHeadText��CREATE_TOTAL_COUNT�̏ꍇ
							if (strcmp(cHeadText, "CREATE_TOTAL_COUNT") == INIT_INT)
							{
								// ����m_nCreateTotalCount�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nCreateTotalCount);
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
								sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &m_pos.x, &m_pos.y, &m_pos.z);
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
//***********************************************************************************
// �m�[�h2�ɏ��ǂݍ��݊֐�
//***********************************************************************************
void CUI::Load2(const char * cText)
{
	// �ǂݍ��ݗp
	char cReedText[MAX_TEXT];

	// �����̔��ʗp
	char cHeadText[MAX_TEXT];

	// �g��Ȃ�����
	char cDie[MAX_TEXT];

	// �e�L�X�g
	char cSaveText[MAX_TEXT];

	// �ǂݍ���
	sprintf(cSaveText, "%s.txt", cText);

	// �t�@�C���|�C���^
	FILE *pFile = NULL;

	// NULL�̏ꍇ
	if (pFile == NULL)
	{
		//�t�@�C�����J��
		pFile = fopen(cSaveText, "r");

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

							// cHeadText��EMITTER�̏ꍇ
							if (strcmp(cHeadText, "EMITTER") == INIT_INT)
							{
								// ����m_bEmitter�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bEmitter_2);
							}
							// cHeadText��EFFECT�̏ꍇ
							if (strcmp(cHeadText, "EFFECT") == INIT_INT)
							{
								// ����m_bEffect�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bEffect_2);
							}
							// cHeadText��ALPHA_BLEND�̏ꍇ
							if (strcmp(cHeadText, "ALPHA_BLEND") == INIT_INT)
							{
								// ����m_bAlpha_Blend�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bAlpha_Blend_2);
							}
							// cHeadText��LIFE�̏ꍇ
							if (strcmp(cHeadText, "LIFE") == INIT_INT)
							{
								// ����m_bLife�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bLife_2);
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
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bRandomSize_2);
							}
							// cHeadText��ADD_SCALE�̏ꍇ
							if (strcmp(cHeadText, "ADD_SCALE") == INIT_INT)
							{
								// ����m_bAddScale�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bAddScale_2);
							}
							// cHeadText��COLOR_SUBTRACT�̏ꍇ
							if (strcmp(cHeadText, "COLOR_SUBTRACT") == INIT_INT)
							{
								// ����m_bSubColor�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bSubColor_2);
							}
							// cHeadText��COLOR_SUBTRACT�̏ꍇ
							if (strcmp(cHeadText, "ROT_RANDOM") == INIT_INT)
							{
								// ����m_bSubColor�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bRotRandom_2);
							}
							// cHeadText��TEXTURE_NUM�̏ꍇ 
							if (strcmp(cHeadText, "TEXTURE_NUM") == INIT_INT)
							{
								// ����m_nTexNum�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nTexNum_2);
							}
							// cHeadText��ALPHA_NUM�̏ꍇ
							if (strcmp(cHeadText, "ALPHA_NUM") == INIT_INT)
							{
								// ����m_nAlpha�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nAlpha_2);
							}
							// cHeadText��SIZE�̏ꍇ
							if (strcmp(cHeadText, "SIZE") == INIT_INT)
							{
								// ����m_bRandomPos�Ɋi�[
								sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &m_size_2.x, &m_size_2.y, &m_size_2.z);
							}
							// cHeadText��MOVE�̏ꍇ
							if (strcmp(cHeadText, "MOVE") == INIT_INT)
							{
								// ����m_move�Ɋi�[
								sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &m_move_2.x, &m_move_2.y, &m_move_2.z);
							}
							// cHeadText��ANGLE�̏ꍇ
							if (strcmp(cHeadText, "ANGLE") == INIT_INT)
							{
								// ����m_fAngle�Ɋi�[
								sscanf(cReedText, "%s %s %f", &cDie, &cDie, &m_fAngle_2);
							}
							// cHeadText��ANGLE�̏ꍇ
							if (strcmp(cHeadText, "ADD_ANGLE") == INIT_INT)
							{
								// ����m_fAngle�Ɋi�[
								sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &m_AddAngle_2.x, &m_AddAngle_2.y, &m_AddAngle_2.z);
							}
							// cHeadText��COLOR�̏ꍇ
							if (strcmp(cHeadText, "COLOR") == INIT_INT)
							{
								// ����m_color�Ɋi�[
								sscanf(cReedText, "%s %s %f %f %f %f", &cDie, &cDie, &m_color_2.r, &m_color_2.g, &m_color_2.b, &m_color_2.a);
							}
							// cHeadText��CREATE_COUNT�̏ꍇ
							if (strcmp(cHeadText, "CREATE_COUNT") == INIT_INT)
							{
								// ����m_nCreateCount�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nCreateCount_2);
							}
							// cHeadText��CREATE_TOTAL_COUNT�̏ꍇ
							if (strcmp(cHeadText, "CREATE_TOTAL_COUNT") == INIT_INT)
							{
								// ����m_nCreateTotalCount�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nCreateTotalCount_2);
							}
							// cHeadText��LIFE_VALUE�̏ꍇ
							if (strcmp(cHeadText, "LIFE_VALUE") == INIT_INT)
							{
								// ����m_nLife�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nLife_2);
							}
							// cHeadText��ADD_SCALE_VALUE�̏ꍇ
							if (strcmp(cHeadText, "ADD_SCALE_VALUE") == INIT_INT)
							{
								/// ����m_fAddScale�Ɋi�[
								sscanf(cReedText, "%s %s %f", &cDie, &cDie, &m_fAddScale_2);
							}
							// cHeadText��COLOR_SUB_VALUE�̏ꍇ
							if (strcmp(cHeadText, "COLOR_SUB_VALUE") == INIT_INT)
							{
								// ����m_SubColor�Ɋi�[
								sscanf(cReedText, "%s %s %f %f %f %f", &cDie, &cDie, &m_SubColor_2.r, &m_SubColor_2.g, &m_SubColor_2.b, &m_SubColor_2.a);
							}
							// cHeadText��MIN_SIZE_VALUE�̏ꍇ
							if (strcmp(cHeadText, "MIN_SIZE_VALUE") == INIT_INT)
							{
								// ����m_fRandom_Min_Size�Ɋi�[
								sscanf(cReedText, "%s %s %f", &cDie, &cDie, &m_fRandom_Min_Size_2);
							}
							// cHeadText��MAX_SIZE_VALUE�̏ꍇ
							if (strcmp(cHeadText, "MAX_SIZE_VALUE") == INIT_INT)
							{
								// ����m_fRandom_Max_Size�Ɋi�[
								sscanf(cReedText, "%s %s %f", &cDie, &cDie, &m_fRandom_Max_Size_2);
							}
							// cHeadText��RANDOM_POS_VALUE�̏ꍇ
							if (strcmp(cHeadText, "RANDOM_POS_VALUE") == INIT_INT)
							{
								// ����m_fRandomPos�Ɋi�[
								sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &m_pos_2.x, &m_pos_2.y, &m_pos_2.z);
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
//***********************************************************************************
// �m�[�h1�̏��ݒ�
//***********************************************************************************
void CUI::SettingNoad_1(void)
{
	// �c���[�m�[�h����
	ImGui::SetNextTreeNodeOpen(m_bSettingNoad_1, ImGuiCond_Once);

	if (ImGui::TreeNode("SettingNoad_1"))
	{
		// Emitter�`�F�b�N�{�b�N�X
		ImGui::Checkbox("Emitter", &m_bEmitter);

		// �G�~�b�^�[��true�̏ꍇ
		if (m_bEmitter)
		{
			// true�̏ꍇ
			if (m_bEffect == true)
			{
				m_bEffect = false;
			}

			// �J�E���g�ݒ�p							
			ImGui::DragInt("Create Count", (int*)&m_nCreateCount, SLIDER_VALUE3, MIN_COUNT, MAX_COUNT);
		}

		// Effect�`�F�b�N�{�b�N�X
		ImGui::Checkbox("Effect", &m_bEffect);

		// �G�~�b�^�[��true�̏ꍇ
		if (m_bEffect)
		{
			// true�̏ꍇ
			if (m_bEmitter == true)
			{
				m_bEmitter = false;
			}
			// �J�E���g�ݒ�p							
			ImGui::DragInt("Create Count", (int*)&m_nCreateCount, SLIDER_VALUE3, MIN_COUNT, MAX_COUNT);

			// �J�E���g�ݒ�p							
			ImGui::DragInt("Create TotalCount", (int*)&m_nCreateTotalCount, SLIDER_VALUE3, MIN_COUNT, MAX_COUNT);
		}

		// ���݂̃e�N�X�`���i���o�[
		ImGui::Text("TextureNumber = %d", m_nTexNum);

		// �e�N�X�`�����擾
		int nTexNum = CManager::GetTexture()->GetTexNum();

		// �`�F�b�N�{�b�N�X
		ImGui::Checkbox("Texture_Radom", &m_bTex_Random);

		// false�̏ꍇ
		if (m_bTex_Random == true)
		{
			// �e�N�X�`���̍ŏ��X���C�_�[
			ImGui::SliderInt("MinTextureNumber", (int*)&m_nMinTexRamdomNum, MIN_TEX, nTexNum - SUB_TEXTURENUM);

			// �e�N�X�`���̍ő�X���C�_�[
			ImGui::SliderInt("MaxTextureNumber", (int*)&m_nMaxTexRamdomNum, MIN_TEX, nTexNum - SUB_TEXTURENUM);
		}

		// false�̏ꍇ
		if (m_bTex_Random == false)
		{
			// �e�N�X�`���̃X���C�_�[
			ImGui::SliderInt("TextureNumber", (int*)&m_nTexNum, MIN_TEX, nTexNum - SUB_TEXTURENUM);
		}

		// ���ߒl�̃X���C�_�[
		ImGui::SliderInt("AlphaNum", (int*)&m_nAlpha, MIN_ALPHA, MAX_ALPHA);

		// �`�F�b�N�{�b�N�X
		ImGui::Checkbox("AlphaBlend", &m_bAlpha_Blend);

		// ���C�t�̃`�F�b�N�{�b�N�X
		ImGui::Checkbox("Life", &m_bLife);

		// ���C�t
		if (m_bLife)
		{
			// �J�E���g�ݒ�p							
			ImGui::DragInt("Life", (int*)&m_nLife, SLIDER_VALUE3, MIN_LIFE, MAX_LIFE);
		}

		// �����_���ʒu�̃`�F�b�N�{�b�N�X
		ImGui::Checkbox("RandomPos", &m_bRandomPos);

		// �ʒu�����_��
		if (m_bRandomPos)
		{
			// �ʒu�����_���T�C�Y�ݒ�							
			ImGui::DragFloat3("RandomPosValue", (float*)&m_pos, SLIDER_VALUE, RANDOM_MIN_POS, RANDOM_MAX_POS);
		}

		// �`�F�b�N�{�b�N�X
		ImGui::Checkbox("Rot_Random", &m_bRotRandom);

		// false�̏ꍇ
		if (m_bRotRandom == false)
		{
			// �ړ��ʐݒ�p
			ImGui::DragFloat3("rot", (float*)&m_rot, SLIDER_VALUE, MIN_ROT, MAX_ROT);
		}

		// �`�F�b�N�{�b�N�X
		ImGui::Checkbox("Same_Size", &m_bSameSize);

		// false�̏ꍇ
		if (m_bSameSize == false)
		{
			// �T�C�Y�ݒ�p
			ImGui::DragFloat2("size", (float*)&m_size, SLIDER_VALUE, MIN_SIZE, MAX_SIZE);
		}
		// true�̏ꍇ
		if (m_bSameSize == true)
		{
			// �T�C�Y�ݒ�p
			ImGui::DragFloat("size", (float*)&m_fSize, SLIDER_VALUE, MIN_SIZE, MAX_SIZE);

			// �T�C�Y�ݒ�
			m_size = SIZE;
		}

		// �`�F�b�N�{�b�N�X
		ImGui::Checkbox("SizeRandom", &m_bRandomSize);

		// �����_���T�C�Y
		if (m_bRandomSize == true)
		{
			// �T�C�Y�����_���T�C�Y�ݒ�							
			ImGui::DragFloat("MinSizeValue", (float*)&m_fRandom_Min_Size, SLIDER_VALUE, RANDOM_MIN_SIZE, MAX_SIZE);

			// �T�C�Y�����_���T�C�Y�ݒ�							
			ImGui::DragFloat("MaxSizeValue", (float*)&m_fRandom_Max_Size, SLIDER_VALUE, RANDOM_MIN_SIZE, MAX_SIZE);
		}

		// �ړ��ʐݒ�p
		ImGui::DragFloat3("move", (float*)&m_move, SLIDER_VALUE, MIN_MOVE, MAX_MOVE);

		// �`�F�b�N�{�b�N�X
		ImGui::Checkbox("AddScale", &m_bAddScale);

		// �g�嗦���Z
		if (m_bAddScale)
		{
			// �J�E���g�ݒ�p							
			ImGui::DragFloat("AddScale_Value", (float*)&m_fAddScale, SLIDER_VALUE2, MIN_SCALE, MAX_SCALE);
		}

		// �p�x�ݒ�p
		ImGui::DragFloat("Angle", &m_fAngle, SLIDER_VALUE, MIN_ANGLE, MAX_ANGLE);

		// �p�x���Z�ݒ�p
		ImGui::DragFloat3("AddAngle", (float*)&m_AddAngle, SLIDER_VALUE, MIN_ADDANGLE, MAX_ADDANGLE);

		// �`�F�b�N�{�b�N�X
		ImGui::Checkbox("ColorRandom", &m_bColorRandom);

		// false�̏ꍇ
		if (m_bColorRandom == false)
		{
			// �J���[�G�f�B�b�g
			ImGui::ColorEdit4("color", (float*)&m_color);
		}
		// true�̏ꍇ
		if (m_bColorRandom == true)
		{
			// �J���[�G�f�B�b�g
			ImGui::DragInt("R", &m_nColor_R, SLIDER_VALUE3, MIN_RANDOMCOL, MAX_RANDOMCOL);

			// �J���[�G�f�B�b�g
			ImGui::DragInt("G", &m_nColor_G, SLIDER_VALUE3, MIN_RANDOMCOL, MAX_RANDOMCOL);

			// �J���[�G�f�B�b�g
			ImGui::DragInt("B", &m_nColor_B, SLIDER_VALUE3, MIN_RANDOMCOL, MAX_RANDOMCOL);
		}

		// �`�F�b�N�{�b�N�X
		ImGui::Checkbox("ColorSubtract", &m_bSubColor);

		// �J���[���Z
		if (m_bSubColor)
		{
			// �F���Z�l�ݒ�							
			ImGui::DragFloat4("SubColor Value", (float*)m_SubColor, SUBCOLOR_SLIDE, MIN_SUBCOLOR, MAX_SUBCOLOR);

			// �`�F�b�N�{�b�N�X
			ImGui::Checkbox("SubColor Close", &m_bSubColor);
		}

		// �c���[�m�[�h����
		ImGui::SetNextTreeNodeOpen(m_bSave, ImGuiCond_Once);

		if (ImGui::TreeNode("Save"))
		{
			// �e�L�X�g������
			ImGui::InputTextWithHint("Save Text", "Save Text Name", m_cSave, sizeof(m_cSave));

			// �Z�[�u
			if (ImGui::Button("Save"))
			{
				// NULL�łȂ��ꍇ
				if (m_cSave != NULL)
				{
					// �ۑ�
					Save(m_cSave);
				}
			}
			ImGui::TreePop();
		}

		// �c���[�m�[�h����
		ImGui::SetNextTreeNodeOpen(m_bLoad, ImGuiCond_Once);

		if (ImGui::TreeNode("Load"))
		{
			// �e�L�X�g������
			ImGui::InputTextWithHint("Load Text", "Load Text Name", m_cLoad, sizeof(m_cLoad));

			// �Z�[�u
			if (ImGui::Button("Load"))
			{
				// NULL�łȂ��ꍇ
				if (m_cSave != NULL)
				{
					// �ۑ�
					Load(m_cLoad);
				}
			}
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
}
//***********************************************************************************
// �m�[�h2�̏��ݒ�
//***********************************************************************************
void CUI::SettingNoad_2(void)
{
	ImGui::SetNextTreeNodeOpen(m_bSettingNoad_2, ImGuiCond_Once);

	if (ImGui::TreeNode("SettingNoad_2"))
	{
		// Emitter�`�F�b�N�{�b�N�X
		ImGui::Checkbox("Emitter", &m_bEmitter_2);

		// �G�~�b�^�[��true�̏ꍇ
		if (m_bEmitter_2)
		{
			// true�̏ꍇ
			if (m_bEffect_2 == true)
			{
				m_bEffect_2 = false;
			}
			// �J�E���g�ݒ�p							
			ImGui::DragInt("Create Count", (int*)&m_nCreateCount_2, SLIDER_VALUE3, MIN_COUNT, MAX_COUNT);
		}

		// Effect�`�F�b�N�{�b�N�X
		ImGui::Checkbox("Effect", &m_bEffect_2);

		// �G�~�b�^�[��true�̏ꍇ
		if (m_bEffect_2)
		{
			// true�̏ꍇ
			if (m_bEmitter_2 == true)
			{
				m_bEmitter_2 = false;
			}
			// �J�E���g�ݒ�p							
			ImGui::DragInt("Create Count2", (int*)&m_nCreateCount_2, SLIDER_VALUE3, MIN_COUNT, MAX_COUNT);

			// �J�E���g�ݒ�p							
			ImGui::DragInt("Create TotalCount2", (int*)&m_nCreateTotalCount_2, SLIDER_VALUE3, MIN_COUNT, MAX_COUNT);
		}

		// �e�N�X�`�����擾
		int nTexNum = CManager::GetTexture()->GetTexNum();

		// �`�F�b�N�{�b�N�X
		ImGui::Checkbox("Texture_Radnom", &m_bTex_Random_2);

		// true�̏ꍇ
		if (m_bTex_Random_2 == true)
		{
			// �e�N�X�`���̍ŏ��X���C�_�[
			ImGui::SliderInt("MinTextureNumber", (int*)&m_nMinTexRamdomNum_2, MIN_TEX, nTexNum - SUB_TEXTURENUM);

			// �e�N�X�`���̍ő�X���C�_�[
			ImGui::SliderInt("MaxTextureNumber", (int*)&m_nMaxTexRamdomNum_2, MIN_TEX, nTexNum - SUB_TEXTURENUM);
		}

		// false�̏ꍇ
		if (m_bTex_Random_2 == false)
		{
			// �e�N�X�`���̃X���C�_�[
			ImGui::SliderInt("TextureNumber", (int*)&m_nTexNum_2, MIN_TEX, nTexNum - SUB_TEXTURENUM);
		}

		// ���ߒl�̃X���C�_�[
		ImGui::SliderInt("AlphaNum", (int*)&m_nAlpha_2, MIN_ALPHA, MAX_ALPHA);

		// �`�F�b�N�{�b�N�X
		ImGui::Checkbox("AlphaBlend", &m_bAlpha_Blend_2);

		// ���C�t�̃`�F�b�N�{�b�N�X
		ImGui::Checkbox("Life", &m_bLife_2);

		// ���C�t
		if (m_bLife_2)
		{
			// �J�E���g�ݒ�p							
			ImGui::DragInt("Life", (int*)&m_nLife_2, SLIDER_VALUE3, MIN_LIFE, MAX_LIFE);
		}

		// �����_���ʒu�̃`�F�b�N�{�b�N�X
		ImGui::Checkbox("RandomPos", &m_bRandomPos_2);

		// �ʒu�����_��
		if (m_bRandomPos_2)
		{
			// �ʒu�����_���T�C�Y�ݒ�							
			ImGui::DragFloat3("RandomPosValue2", (float*)&m_pos_2, SLIDER_VALUE, RANDOM_MIN_POS, RANDOM_MAX_POS);
		}

		// �`�F�b�N�{�b�N�X
		ImGui::Checkbox("Rot_Random", &m_bRotRandom_2);

		// false�̏ꍇ
		if (m_bRotRandom_2 == false)
		{
			// �ړ��ʐݒ�p
			ImGui::DragFloat3("rot", (float*)&m_rot_2, SLIDER_VALUE, MIN_ROT, MAX_ROT);
		}
		// �����_���ʒu�̃`�F�b�N�{�b�N�X
		ImGui::Checkbox("Same_Size", &m_bSameSize_2);

		// false�̏ꍇ
		if (m_bSameSize_2 == false)
		{
			// �T�C�Y�ݒ�p
			ImGui::DragFloat2("size", (float*)&m_size_2, SLIDER_VALUE, MIN_SIZE, MAX_SIZE);
		}
		// true�̏ꍇ
		if (m_bSameSize_2 == true)
		{
			// �T�C�Y�ݒ�p
			ImGui::DragFloat("size", (float*)&m_fSize_2, SLIDER_VALUE, MIN_SIZE, MAX_SIZE);

			// �T�C�Y�ݒ�
			m_size_2 = SIZE_2;
		}

		// �`�F�b�N�{�b�N�X
		ImGui::Checkbox("SizeRandom", &m_bRandomSize_2);

		// �����_���T�C�Y
		if (m_bRandomSize_2 == true)
		{
			// �T�C�Y�����_���T�C�Y�ݒ�							
			ImGui::DragFloat("MinSizeValue2", (float*)&m_fRandom_Min_Size_2, SLIDER_VALUE, RANDOM_MIN_SIZE, MAX_SIZE);

			// �T�C�Y�����_���T�C�Y�ݒ�							
			ImGui::DragFloat("MaxSizeValue2", (float*)&m_fRandom_Max_Size_2, SLIDER_VALUE, RANDOM_MIN_SIZE, MAX_SIZE);
		}

		// �ړ��ʐݒ�p
		ImGui::DragFloat3("move", (float*)&m_move_2, SLIDER_VALUE, MIN_MOVE, MAX_MOVE);

		// �`�F�b�N�{�b�N�X
		ImGui::Checkbox("AddScale", &m_bAddScale_2);

		// �g�嗦���Z
		if (m_bAddScale_2)
		{
			// �J�E���g�ݒ�p							
			ImGui::DragFloat("AddScale_Value2", (float*)&m_fAddScale_2, SLIDER_VALUE2, MIN_SCALE, MAX_SCALE);
		}

		// �p�x�ݒ�p
		ImGui::DragFloat("Angle", &m_fAngle_2, SLIDER_VALUE, MIN_ANGLE, MAX_ANGLE);

		// �p�x���Z�ݒ�p
		ImGui::DragFloat3("AddAngle", (float*)&m_AddAngle_2, SLIDER_VALUE, MIN_ADDANGLE, MAX_ADDANGLE);

		// �`�F�b�N�{�b�N�X
		ImGui::Checkbox("ColorRandom", &m_bColorRandom_2);

		// false�̏ꍇ
		if (m_bColorRandom_2 == false)
		{
			// �J���[�G�f�B�b�g
			ImGui::ColorEdit4("color", (float*)&m_color_2);
		}
		// true�̏ꍇ
		if (m_bColorRandom == true)
		{
			// �J���[�G�f�B�b�g
			ImGui::DragInt("R", &m_nColor_R_2, SLIDER_VALUE3, MIN_RANDOMCOL, MAX_RANDOMCOL);

			// �J���[�G�f�B�b�g
			ImGui::DragInt("G", &m_nColor_G_2, SLIDER_VALUE3, MIN_RANDOMCOL, MAX_RANDOMCOL);

			// �J���[�G�f�B�b�g
			ImGui::DragInt("B", &m_nColor_B_2, SLIDER_VALUE3, MIN_RANDOMCOL, MAX_RANDOMCOL);
		}

		// �`�F�b�N�{�b�N�X
		ImGui::Checkbox("ColorSubtract", &m_bSubColor_2);

		// �J���[���Z
		if (m_bSubColor_2)
		{
			// �F���Z�l�ݒ�							
			ImGui::DragFloat4("SubColor Value2", (float*)m_SubColor_2, SUBCOLOR_SLIDE, MIN_SUBCOLOR, MAX_SUBCOLOR);
		}

		ImGui::SetNextTreeNodeOpen(m_bSave_2, ImGuiCond_Once);

		if (ImGui::TreeNode("Save"))
		{
			// �e�L�X�g������
			ImGui::InputTextWithHint("Save Text", "Save Text Name", m_cSave_2, sizeof(m_cSave_2));

			// �Z�[�u
			if (ImGui::Button("Save"))
			{
				// NULL�łȂ��ꍇ
				if (m_cSave != NULL)
				{
					// �ۑ�
					Save2(m_cSave_2);
				}
			}
			ImGui::TreePop();
		}

		ImGui::SetNextTreeNodeOpen(m_bLoad_2, ImGuiCond_Once);

		if (ImGui::TreeNode("Load"))
		{
			// �e�L�X�g������
			ImGui::InputTextWithHint("Load Text", "Load Text Name", m_cLoad_2, sizeof(m_cLoad_2));

			// �Z�[�u
			if (ImGui::Button("Load"))
			{
				// NULL�łȂ��ꍇ
				if (m_cSave != NULL)
				{
					// �ۑ�
					Load2(m_cLoad_2);
				}
			}
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
}

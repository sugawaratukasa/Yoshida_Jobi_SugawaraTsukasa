//***********************************************************************************
//	UI	[ui.h]
//	Author : �ǌ� �i
//***********************************************************************************
#ifndef _UI_H_
#define _UI_H_
//***********************************************************************************
// �C���N���[�h�t�@�C��
//***********************************************************************************
#include "scene.h"
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
//***********************************************************************************
// �}�N����`
//***********************************************************************************
#define MAX_SAVE_CHAR	(16)		// �Z�[�u�p�e�L�X�g���̍ő吔
#define MAX_LOAD_CHAR	(16)		// ���[�h�p�e�L�X�g���̍ő吔
//***********************************************************************************
// �N���X
//***********************************************************************************
class CUI : public CScene
{
public:
	CUI(int nPriority = 0);
	~CUI();
	static CUI *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//*********************************************************
	// 1�Ԗڂ̃m�[�h�̐ݒ�
	//*********************************************************
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	D3DXVECTOR3 GetRandom_Pos(void) { return m_pos; }
	D3DXCOLOR GetColor(void) { return m_color; }
	D3DXCOLOR GetSubColor(void) { return m_SubColor; }
	float GetScale(void) { return m_fAddScale; }
	float GetAngle(void) { return m_fAngle; }
	D3DXVECTOR3 GetAddAngle(void) { return m_AddAngle; }
	float GetRandom_Min_Size(void) { return m_fRandom_Min_Size; }
	float GetRandom_Max_Size(void) { return m_fRandom_Max_Size; }
	bool GetUseAlpha_Blend(void) { return m_bAlpha_Blend; }
	bool GetbEmitter(void) { return m_bEmitter; }
	bool GetbEffect(void) { return m_bEffect; }
	bool GetbLife(void) { return m_bLife; }
	bool GetbRandomPos(void) { return m_bRandomPos; }
	bool GetRandomSize(void) { return m_bRandomSize; }
	bool GetbAddScale(void) { return m_bAddScale; }
	bool GetbSubColor(void) { return m_bSubColor; }
	bool GetbRotRandom(void) { return m_bRotRandom; }
	bool GetbTexRandom(void) { return m_bTex_Random; }
	bool GetColorRandom(void) { return m_bColorRandom; }
	int GetCreateCount(void) { return m_nCreateCount; }
	int GetCreateTotalCount(void) { return m_nCreateTotalCount; }
	int GetTexNum(void) { return m_nTexNum; }
	int GetAlpha(void) { return m_nAlpha; }
	int GetLife(void) { return m_nLife; }
	int GetMinTexRandomNum(void) { return m_nMinTexRamdomNum; }
	int GetMaxTexRandomNum(void) { return m_nMaxTexRamdomNum; }
	int GetColorRandom_R(void) { return m_nColor_R; }
	int GetColorRandom_G(void) { return m_nColor_G; }
	int GetColorRandom_B(void) { return m_nColor_B; }
	//*********************************************************
	// 2�Ԗڂ̃m�[�h�̃Q�b�^�[
	//*********************************************************
	D3DXVECTOR3 GetPos_2(void) { return m_pos_2; }
	D3DXVECTOR3 GetRot_2(void) { return m_rot_2; }
	D3DXVECTOR3 GetSize_2(void) { return m_size_2; }
	D3DXVECTOR3 GetMove_2(void) { return m_move_2; }
	D3DXVECTOR3 GetRandom_Pos_2(void) { return m_pos_2; }
	D3DXCOLOR GetColor_2(void) { return m_color_2; }
	D3DXCOLOR GetSubColor_2(void) { return m_SubColor_2; }
	float GetScale_2(void) { return m_fAddScale_2; }
	float GetAngle_2(void) { return m_fAngle_2; }
	D3DXVECTOR3 GetAddAngle_2(void) { return m_AddAngle_2; }
	float GetRandom_Min_Size_2(void) { return m_fRandom_Min_Size_2; }
	float GetRandom_Max_Size_2(void) { return m_fRandom_Max_Size_2; }
	bool GetUseAlpha_Blend_2(void) { return m_bAlpha_Blend_2; }
	bool GetbEmitter_2(void) { return m_bEmitter_2; }
	bool GetbEffect_2(void) { return m_bEffect_2; }
	bool GetbLife_2(void) { return m_bLife_2; }
	bool GetbRandomPos_2(void) { return m_bRandomPos_2; }
	bool GetRandomSize_2(void) { return m_bRandomSize_2; }
	bool GetbAddScale_2(void) { return m_bAddScale_2; }
	bool GetbSubColor_2(void) { return m_bSubColor_2; }
	bool GetbRotRandom_2(void) { return m_bRotRandom_2; }
	bool GetbTexRandom_2(void) { return m_bTex_Random_2; }
	bool GetColorRandom_2(void) { return m_bColorRandom_2; }
	int GetCreateCount_2(void) { return m_nCreateCount_2; }
	int GetCreateTotalCount_2(void) { return m_nCreateTotalCount_2; }
	int GetTexNum_2(void) { return m_nTexNum_2; }
	int GetAlpha_2(void) { return m_nAlpha_2; }
	int GetLife_2(void) { return m_nLife_2; }
	int GetMinTexRandomNum_2(void) { return m_nMinTexRamdomNum_2; }
	int GetMaxTexRandomNum_2(void) { return m_nMaxTexRamdomNum_2; }
	int GetColorRandom_R_2(void) { return m_nColor_R; }
	int GetColorRandom_G_2(void) { return m_nColor_G; }
	int GetColorRandom_B_2(void) { return m_nColor_B; }
private:
	void Save(const char *cText);
	void Save2(const char *cText);
	void Load(const char *cText);
	void Load2(const char *cText);
	void SettingNoad_1(void);
	void SettingNoad_2(void);
	bool m_bSetting_window;				// �e��ݒ�window
	bool m_bSettingNoad_1;				// ��ڂ̃m�[�h
	bool m_bSettingNoad_2;				// ��ڂ̃m�[�h
//************************************************************
// 1�Ԗڂ̃m�[�h
//************************************************************
	bool m_bEmitter;					// �G�~�b�^�[��bool
	bool m_bEffect;						// �G�t�F�N�g��bool
	bool m_bAlpha_Blend;				// �A���t�@�u�����h�̎g�p����
	bool m_bLife;						// ���C�t
	bool m_bRandomPos;					// �ʒu�����_��
	bool m_bRandomSize;					// �����_���T�C�Y
	bool m_bAddScale;					// �X�P�[��
	bool m_bSubColor;					// �J���[���Z�p��bool
	bool m_bSave;						// �Z�[�u
	bool m_bLoad;						// ���[�h
	bool m_bSameSize;					// �T�C�YXY�𓯂��ɂ��邩
	bool m_bRotRandom;					// ���������_��
	bool m_bTex_Random;					// �e�N�X�`�������_��
	bool m_bColorRandom;				// �J���[�����_��
	D3DXCOLOR m_color;					// �F
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_rot;					// ����
	D3DXVECTOR3 m_size;					// �T�C�Y
	D3DXVECTOR3 m_move;					// �ړ�
	D3DXVECTOR3 m_AddAngle;				// �p�x���Z
	D3DXCOLOR m_SubColor;				// �F���Z
	float m_fSize;						// �T�C�Y
	float m_fRandom_Max_Size;			// �����_���T�C�Y
	float m_fRandom_Min_Size;			// �����_���T�C�Y
	float m_fAddScale;					// �g�嗦���Z��
	float m_fAngle;						// �p�x
	int m_nCreateCount;					// �����J�E���g
	int m_nCreateTotalCount;			// �����̑���
	int m_nTexNum;						// �e�N�X�`���ԍ�
	int m_nAlpha;						// ���ߒl
	int m_nLife;						// ���C�t
	int m_nMinTexRamdomNum;				// �����_���̍ŏ��l
	int m_nMaxTexRamdomNum;				// �����_���̍ő�l
	int m_nColor_R;						// �Ԃ̗�
	int m_nColor_G;						// �Ԃ̗�
	int m_nColor_B;						// �Ԃ̗�
	char m_cSave[MAX_SAVE_CHAR];		// �Z�[�u�p
	char m_cLoad[MAX_LOAD_CHAR];		// ���[�h�p
//********************************************
// 2�Ԗڂ̃m�[�h
//********************************************
	bool m_bEmitter_2;					// �G�~�b�^�[��bool
	bool m_bEffect_2;					// �G�t�F�N�g��bool
	bool m_bAlpha_Blend_2;				// �A���t�@�u�����h�̎g�p����
	bool m_bLife_2;						// ���C�t
	bool m_bRandomPos_2;				// �ʒu�����_��
	bool m_bRandomSize_2;				// �����_���T�C�Y
	bool m_bAddScale_2;					// �X�P�[��
	bool m_bSubColor_2;					// �J���[���Z�p��bool
	bool m_bSave_2;						// �Z�[�u
	bool m_bLoad_2;						// ���[�h
	bool m_bSameSize_2;					// �T�C�YXY�𓯂��ɂ��邩
	bool m_bRotRandom_2;				// ���������_��
	bool m_bTex_Random_2;				// �e�N�X�`�������_��
	bool m_bColorRandom_2;				// �F�����_��
	D3DXCOLOR m_color_2;				// �F
	D3DXVECTOR3 m_pos_2;				// �ʒu
	D3DXVECTOR3 m_rot_2;				// ����
	D3DXVECTOR3 m_size_2;				// �T�C�Y
	D3DXVECTOR3 m_move_2;				// �ړ�
	D3DXVECTOR3 m_AddAngle_2;			// �p�x���Z
	D3DXCOLOR m_SubColor_2;				// �F���Z
	float m_fSize_2;					// �T�C�Y
	float m_fRandom_Max_Size_2;			// �����_���T�C�Y
	float m_fRandom_Min_Size_2;			// �����_���T�C�Y
	float m_fAddScale_2;				// �g�嗦���Z��
	float m_fAngle_2;					// �p�x
	int m_nCreateCount_2;				// �����J�E���g
	int m_nCreateTotalCount_2;			// �����̑���
	int m_nTexNum_2;					// �e�N�X�`���ԍ�
	int m_nAlpha_2;						// ���ߒl
	int m_nLife_2;						// ���C�t
	int m_nMinTexRamdomNum_2;			// �����_���̍ŏ��l
	int m_nMaxTexRamdomNum_2;			// �����_���̍ő�l
	int m_nColor_R_2;					// �Ԃ̗�
	int m_nColor_G_2;					// �΂̗�
	int m_nColor_B_2;					// �̗�
	char m_cSave_2[MAX_SAVE_CHAR];		// �Z�[�u�p
	char m_cLoad_2[MAX_LOAD_CHAR];		// ���[�h�p
};
#endif
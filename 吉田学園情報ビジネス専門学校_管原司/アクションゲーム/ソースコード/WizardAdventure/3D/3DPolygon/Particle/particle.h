//******************************************************************************
// �p�[�e�B�N�� [ particle.h]
// Author : �ǌ� �i
//******************************************************************************
#ifndef _PARTICLE_H_
#define _PARTICLE_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "../3D/3DPolygon/Billboard/billboard.h"
//******************************************************************************
// �N���X
//******************************************************************************
class CParticle : public CBillboard
{
public:
	CParticle(int nPriority = OBJTYPE_PARTICLE);
	~CParticle();
	static CParticle *Create(D3DXVECTOR3 pos, const char *cText);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void LoadParticle(const char *cText);
	void SetTexNum(int nTexNum);
	static void CreateEffect(D3DXVECTOR3 pos, int nCreateNum, const char *cText);
private:
	bool m_bAlpha_Blend;		// ���Z�������s����
	bool m_bLife;				// ���C�t���g�p���邩
	bool m_bRandomPos;			// �ʒu�������_���ɂ��邩
	bool m_bRandomSize;			// �����_���T�C�Y
	bool m_bAddScale;			// �g�嗦�����Z���邩
	bool m_bSubColor;			// �F���Z���s����
	bool m_bRotRandom;			// ���������_��
	bool m_bTexRandom;			// �e�N�X�`�������_��
	D3DXVECTOR3 m_Random_pos;	// �ʒu�����_��
	D3DXVECTOR3 m_size;			// �T�C�Y
	D3DXVECTOR3 m_move;			// �ړ���
	D3DXVECTOR3 m_Angle;		// �p�x
	D3DXVECTOR3 m_AddAngle;		// xyz�̊p�x���Z
	D3DXCOLOR m_color;			// �F
	D3DXCOLOR m_SubColor;		// �F���Z��
	int m_nAlpha;				// �`�悷�铧���x
	int m_nLife;				// ���C�t��
	int m_nTexNum;				// �e�N�X�`���i���o�[
	int m_nMinTex_RandomNum;	// �e�N�X�`���i���o�[
	int m_nMaxTex_RandomNum;	// �e�N�X�`���i���o�[
	float m_fAngle;				// �p�x
	float m_fAddAngle;			// �p�x�̉��Z��
	float m_fRandom_Min_Size;	// �����_���T�C�Y�̍ŏ��l
	float m_fRandom_Max_Size;	// �����_���T�C�Y�̍ő�l
	float m_fAddScale;			// �g�嗦�̉��Z��
};
#endif
//******************************************************************************
// 2D_�p�[�e�B�N���G�t�F�N�g [2d_particle_effect.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _2D_PARTICLE_EFFECT_H_
#define _2D_PARTICLE_EFFECT_H_

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "scene.h"
//******************************************************************************
// �N���X
//******************************************************************************
class C2D_Particle_Effect : public CScene
{
public:
	enum TYPE
	{
		TYPE_COLOR_BOM = 0,
	};
	C2D_Particle_Effect();
	~C2D_Particle_Effect();
	static C2D_Particle_Effect *Create(D3DXVECTOR3 pos, TYPE type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Load(const char *cText);
	D3DXVECTOR3 m_pos;				// �ʒu���W
	int m_nCreate_TotalCount;		// �����̑���
	char m_cText[MAX_TEXT];			// �e�L�X�g
	TYPE m_Type;					// ���
};
#endif
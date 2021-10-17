//******************************************************************************
// �p�[�e�B�N���G�t�F�N�g [particle_effect.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _PARTICLE_EFFECT_H_
#define _PARTICLE_EFFECT_H_

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "scene.h"
//******************************************************************************
// �N���X
//******************************************************************************
class CParticle_Effect : public CScene
{
public:
	enum TYPE
	{
		TYPE_SPLASH = 0,
		TYPE_WAVE,
		TYPE_SMOKE,
		TYPE_EXPLOSION,
		TYPE_WOOD,
		TYPE_MAX
	};
	CParticle_Effect();
	~CParticle_Effect();
	static CParticle_Effect *Create(D3DXVECTOR3 pos, TYPE type);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Load(const char *cText);
	D3DXVECTOR3 m_pos;				// �ʒu���W
	int m_nCreate_TotalCount;		// �����̑���
	TYPE m_Type;					// ���
};
#endif
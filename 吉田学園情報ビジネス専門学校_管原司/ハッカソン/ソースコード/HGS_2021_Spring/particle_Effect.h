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
	CParticle_Effect();
	~CParticle_Effect();
	static CParticle_Effect *Create(D3DXVECTOR3 pos);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Load(const char *cText);
	D3DXVECTOR3 m_pos;				// �ʒu���W
	int m_nCreate_TotalCount;		// �����̑���
};
#endif
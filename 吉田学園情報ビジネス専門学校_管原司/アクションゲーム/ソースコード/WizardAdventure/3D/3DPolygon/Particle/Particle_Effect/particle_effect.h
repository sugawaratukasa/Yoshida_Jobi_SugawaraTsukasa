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
		TYPE_FIRE_EXPLOSION = 0,
		TYPE_ICE_EXPLOSION,
		TYPE_FIRE_EXPLOSION_2,
		TYPE_ICE_EXPLOSION_2,
		TYPE_ENEMY_FIRE_EXPLOSION,
		TYPE_ENEMY_FIRE_EXPLOSION_2,
		TYPE_WOOD_EFFECT,
		TYPE_WOOD_EFFECT_2,
		TYPE_BLOCK_EFFECT,
		TYPE_STAR_EFFECT,
		TYPE_STAR_EFFECT2
	};
	CParticle_Effect();
	~CParticle_Effect();
	static CParticle_Effect *Create(D3DXVECTOR3 pos, TYPE type);
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
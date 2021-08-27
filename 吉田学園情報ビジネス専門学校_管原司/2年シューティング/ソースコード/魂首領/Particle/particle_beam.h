//******************************************************************************
// �r�[���������������̃p�[�e�B�N�� [particle_beam.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _PARTICLE_BEAM_H_
#define _PARTICLE_BEAM_H_
//******************************************************************************
// �N���X
//******************************************************************************
class CParticle_Beam : public CParticle
{
public:
	// ���
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_ENEMY,
		TYPE_PLAYER,
		TYPE_MAX
	}TYPE;

	CParticle_Beam(int nPrirority = OBJTYPE_PARTICLE);
	~CParticle_Beam();
	static CParticle_Beam *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	int m_nLife;	// ���C�t
};
#endif

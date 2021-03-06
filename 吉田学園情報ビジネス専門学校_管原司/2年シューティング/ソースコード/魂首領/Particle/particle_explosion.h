//******************************************************************************
// 爆発処理 [particle_explosion.h]
// Author : 管原　司
//******************************************************************************
#ifndef _PARTICLE_EXPLOSION_H_
#define _PARTICLE_EXPLOSION_H_
//******************************************************************************
// クラス
//******************************************************************************
class CParticle_Explosion : public CParticle
{
public:
	// 種類
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_ENEMY,
		TYPE_PLAYER,
		TYPE_MAX
	}TYPE;

	CParticle_Explosion(int nPrirority = OBJTYPE_EXPLOSION);
	~CParticle_Explosion();
	static CParticle_Explosion *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 move, CParticle::TEX_TYPE TexType);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void CreateExplosionEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);
private:
	D3DXVECTOR3	m_move;		// 移動量
};
#endif
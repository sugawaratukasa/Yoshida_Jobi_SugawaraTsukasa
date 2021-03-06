//***********************************************************************************
//	particle [particle.h]
//	Author : 管原 司
//***********************************************************************************
#ifndef _PARTICLE_H_
#define _PARTICLE_H_
//***********************************************************************************
// インクルードファイル
//***********************************************************************************
#include "billboard.h"
#include "ui.h"
//***********************************************************************************
// マクロ定義
//***********************************************************************************
//***********************************************************************************
// 前方宣言
//***********************************************************************************
class CUI;
//***********************************************************************************
// クラス
//***********************************************************************************
class CParticle : public CBillboard
{
public:
	CParticle();
	~CParticle();
	static CParticle *Create(CUI *pUi);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	CUI *m_pUi;				// ポインタ
	bool m_bAlpha_Blend;	// 加算合成を行うか
	int m_nLife;			// 体力
	D3DXVECTOR3 m_Angle;	// 角度
};
#endif
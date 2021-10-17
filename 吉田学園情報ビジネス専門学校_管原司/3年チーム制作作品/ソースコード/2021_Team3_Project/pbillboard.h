//******************************************************************************
// ビルボード [billboard.h]
// Author : SugawaraTsukasa
//******************************************************************************
#ifndef _PBILLBOARD_H_
#define _PBILLBOARD_H_
//******************************************************************************
// インクルードファイル
// Author : SugawaraTsukasa
//******************************************************************************
#include "scene.h"
//******************************************************************************
// クラス
// Author : SugawaraTsukasa
//******************************************************************************
class CpBillboard : public CScene
{
public:
	CpBillboard(PRIORITY Priority = PRIORITY_3D_UI);
	~CpBillboard();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//*********************************************
	// セッター
	//*********************************************
	void SetPosition(D3DXVECTOR3 pos);
	void SetRotation(D3DXVECTOR3 rot);
	void SetSize(D3DXVECTOR3 size);
	void SetColor(D3DXCOLOR col);
	void SetTexture(float fTexX, float fTexY, float fTexX2, float fTexY2);
	void SetScale(float fScale);
	void SetAlpha(int nAlpha);
	//*********************************************
	// ゲッター
	//*********************************************
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXCOLOR GetColor(void) { return m_col; }
	float GetScale(void) { return m_fScale; }

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

private:
	LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;						// 位置座標
	D3DXVECTOR3 m_size;						// サイズ
	D3DXVECTOR3 m_rot;						// 向き
	D3DXCOLOR m_col;						// カラー
	float  m_fTexX;							// テクスチャX座標
	float  m_fTexX2;						// テクスチャX2座標
	float  m_fTexY;							// テクスチャY座標
	float  m_fTexY2;						// テクスチャY座標
	D3DXMATRIX m_mtxWorld;					// マトリックス
	float m_fScale;							// 拡大
	int m_nAlpha;							// 透過値
	bool m_bDraw;							// 描画判定
};
#endif
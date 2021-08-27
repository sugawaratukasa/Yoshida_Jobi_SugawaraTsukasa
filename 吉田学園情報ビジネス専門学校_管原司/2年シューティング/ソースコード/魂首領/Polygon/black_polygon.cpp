//******************************************************************************
// 黒ポリゴン [black_polygon.cpp]
// Author : 管原　司
//******************************************************************************
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "../System/main.h"
#include "../System/manager.h"
#include "../System/renderer.h"
#include "../System/scene.h"
#include "../System/scene2d.h"
#include "polygon.h"
#include "black_polygon.h"
//******************************************************************************
// コンストラクタ
//******************************************************************************
CBlack_Polygon::CBlack_Polygon(int nPriority) : CPolygon(nPriority)
{
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CBlack_Polygon::~CBlack_Polygon()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CBlack_Polygon * CBlack_Polygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TEX_TYPE textype)
{
	//　CBlack_Polygonクラスのポインタ
	CBlack_Polygon *pBlack_Polygon;

	// メモリ確保
	pBlack_Polygon = new CBlack_Polygon;

	// 情報設定
	pBlack_Polygon->SetPolygon(pos, size, col, textype);

	// 初期化
	pBlack_Polygon->Init();

	// ポインタを返す
	return pBlack_Polygon;

}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CBlack_Polygon::Init()
{
	//　初期化
	CPolygon::Init();

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CBlack_Polygon::Uninit(void)
{
	//　終了
	CPolygon::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CBlack_Polygon::Update(void)
{
	//　更新
	CPolygon::Update();
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CBlack_Polygon::Draw(void)
{
	//　描画
	CPolygon::Draw();
}
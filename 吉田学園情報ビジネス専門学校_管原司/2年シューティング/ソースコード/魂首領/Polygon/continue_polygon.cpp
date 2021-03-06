//******************************************************************************
// コンティニューポリゴン [continue_polygon.cpp]
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
#include "continue_polygon.h"
//******************************************************************************
// コンストラクタ
//******************************************************************************
CContinue_Polygon::CContinue_Polygon(int nPriority) : CPolygon(nPriority)
{
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CContinue_Polygon::~CContinue_Polygon()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CContinue_Polygon * CContinue_Polygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TEX_TYPE textype)
{
	//　CContinue_Polygonクラスのポインタ
	CContinue_Polygon *pContinue_Polygon;

	// メモリ確保
	pContinue_Polygon = new CContinue_Polygon;

	// 情報設定
	pContinue_Polygon->SetPolygon(pos, size, col, textype);

	// 初期化
	pContinue_Polygon->Init();

	// ポインタを返す
	return pContinue_Polygon;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CContinue_Polygon::Init()
{
	//　初期化
	CPolygon::Init();

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CContinue_Polygon::Uninit(void)
{
	//　終了
	CPolygon::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CContinue_Polygon::Update(void)
{
	//　更新
	CPolygon::Update();
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CContinue_Polygon::Draw(void)
{
	//　描画
	CPolygon::Draw();
}
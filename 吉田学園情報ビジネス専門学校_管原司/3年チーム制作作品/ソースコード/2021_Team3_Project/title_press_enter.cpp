//=============================================================================
//
// タイトルPress_Enter [title_press_enter.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "game.h"
#include "light.h"
#include "title_press_enter.h"
#include "resource_manager.h"
#include "texture.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define POS		(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 1.3f,0.0f))	// 位置
#define SIZE	(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 4,0.0f))		// サイズ
#define ADD_COL	(0.03f)														// 色の加算値
#define MAX_COL	(1.0f)														// 色の最大値
#define MIN_COL	(0.0f)														// 色の最小値

//=============================================================================
// コンストラクタ
//=============================================================================
CTitlePress_Button::CTitlePress_Button(PRIORITY Priority) : CScene2D(Priority)
{
	m_bColor = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CTitlePress_Button::~CTitlePress_Button()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CTitlePress_Button * CTitlePress_Button::Create(void)
{
	// メモリ確保
	CTitlePress_Button *pPolygon = new CTitlePress_Button(PRIORITY_UI);

	// !nullcheck
	if (pPolygon != nullptr)
	{
		// 初期化処理
		pPolygon->Init();

		return pPolygon;
	}

	return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTitlePress_Button::Init(void)
{
	// テクスチャのポイン取得
	CTexture *pTexture = GET_TEXTURE_PTR;

	// テクスチャ
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_PRESS_BUTTON));

	// 初期化処理
	CScene2D::Init(POS, SIZE);

	return S_OK;
}

//=============================================================================
// 更新処理l
//=============================================================================
void CTitlePress_Button::Update(void)
{
	// 描画処理
	CScene2D::Update();
	// 色
	D3DXCOLOR col = GetColor();

	// falseの場合
	if (m_bColor == false)
	{
		// 減算
		col.a -= ADD_COL;

		// 最小以下の場合
		if (col.a < MIN_COL)
		{
			// 最小値に
			col.a = MIN_COL;

			// trueに
			m_bColor = true;
		}
	}
	// trueの場合
	if (m_bColor == true)
	{
		// 増算
		col.a += ADD_COL;

		// 最小以下の場合
		if (col.a > MAX_COL)
		{
			// 最小値に
			col.a = MAX_COL;

			// trueに
			m_bColor = false;
		}
	}

	// 色設定
	SetCol(col);
}

//=============================================================================
// 描画処理
//=============================================================================
void CTitlePress_Button::Draw(void)
{
	// 描画処理
	CScene2D::Draw();
}

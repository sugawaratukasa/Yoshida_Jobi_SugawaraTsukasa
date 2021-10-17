//=============================================================================
// 弾 [bullet.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "character.h"
#include "collision.h"
#include "bullet.h"
#include "sound.h"
#include "particle_effect.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define GRAVITY		(0.1f)								// 重力
#define SIZE		(D3DXVECTOR3(80.0f,80.0f,80.0f))	// サイズ
#define POS_Y_MIN	(0.0f)								// Y座標最小値
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CBullet::CBullet(PRIORITY Priority) : CModel(Priority)
{
	m_XfileNum = CXfile::XFILE_NUM_BULLET;
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CBullet::~CBullet()
{
}

//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CBulletのポインタ
	CBullet *pBullet = nullptr;

	// nullcheck
	if (pBullet == nullptr)
	{
		// メモリ確保
		pBullet = new CBullet;

		// !nullcheck
		if (pBullet != nullptr)
		{
			// 初期化処理
			pBullet->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pBullet;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// モデル情報取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデル情報取得
		CXfile::MODEL model = pXfile->GetXfile(m_XfileNum);

		// モデルの情報を渡す
		BindModel(model);
	}

	// サイズ設定
	SetSize(SIZE);

	// 初期化処理
	CModel::Init(pos, rot);

	CSound *pSound = GET_SOUND_PTR;
	pSound->Play(CSound::SOUND_SE_SHOT);

	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBullet::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBullet::Update(void)
{
	// 更新処理
	CModel::Update();

	// 移動量取得
	D3DXVECTOR3 move = GetMove();

	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// 移動
	move.y -= GRAVITY;

	// 移動量設定
	SetMove(move);

	// yが0以下の場合
	if (pos.y <= POS_Y_MIN)
	{
		//水しぶき
		CreateSplash();

		// 破棄
		Death();
	}
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBullet::Draw(void)
{
	// 描画処理
	CModel::Draw();
}
//=======================================================================================
// 水しぶき生成関数
// Author : Oguma Akira
//=======================================================================================
void CBullet::CreateSplash(void)
{
	// 水しぶき生成
	CParticle_Effect::Create(GetPos(), CParticle_Effect::TYPE_SPLASH);
}
//=============================================================================
// 煙生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBullet::Smoke(void)
{
	// 煙生成
	CParticle_Effect::Create(GetPos(), CParticle_Effect::TYPE_SMOKE);
}
//=============================================================================
// 爆発生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBullet::Explosion(void)
{
	// 爆発生成
	CParticle_Effect::Create(GetPos(), CParticle_Effect::TYPE_EXPLOSION);

	// 煙生成
	CParticle_Effect::Create(GetPos(), CParticle_Effect::TYPE_SMOKE);
}
//=============================================================================
// 木片生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBullet::Wood(void)
{
	// 生成
	CParticle_Effect::Create(GetPos(), CParticle_Effect::TYPE_WOOD);
}
//=============================================================================
// 死亡処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBullet::Death(void)
{
	// 死亡状態に
	SetState(STATE_DEAD);

	// 終了処理
	Uninit();

	return;
}

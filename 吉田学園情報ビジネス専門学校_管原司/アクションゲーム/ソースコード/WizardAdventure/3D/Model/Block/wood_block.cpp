//******************************************************************************
// 木箱 [wood_block.cpp]
// Author : 管原　司
//******************************************************************************
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "wood_block.h"
//******************************************************************************
// コンストラクタ
//******************************************************************************
CWood_Block::CWood_Block(int nPriority) :CBlock(nPriority)
{
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CWood_Block::~CWood_Block()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CWood_Block * CWood_Block::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// ポインタ
	CWood_Block *pWoodBlock = NULL;
	// NULLの場合
	if (pWoodBlock == NULL)
	{
		// メモリ確保
		pWoodBlock = new CWood_Block;

		// NULLでない場合
		if (pWoodBlock != NULL)
		{
			// 情報設定
			pWoodBlock->SetBlock(pos, rot, size, C3D_Obj::TYPE_WOOD_BLOCK, pWoodBlock);

			// 初期化
			pWoodBlock->Init();
		}
	}
	// ポインタを返す
	return pWoodBlock;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CWood_Block::Init(void)
{
	// 初期化
	CBlock::Init();
	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CWood_Block::Uninit(void)
{
	// 終了
	CBlock::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CWood_Block::Update(void)
{
	// 更新
	CBlock::Update();
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CWood_Block::Draw(void)
{
	// 描画
	CBlock::Draw();
}

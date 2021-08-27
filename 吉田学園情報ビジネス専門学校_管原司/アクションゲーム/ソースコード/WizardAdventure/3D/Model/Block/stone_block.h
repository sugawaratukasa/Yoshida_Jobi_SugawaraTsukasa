//******************************************************************************
// 石の箱 [stone_block.h]
// Author : 管原　司
//******************************************************************************
#ifndef _STONE_BLOCK_H_
#define _STONE_BLOCK_H_

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "block.h"
//******************************************************************************
// 前方宣言
//******************************************************************************

//******************************************************************************
// プレイヤークラス
//******************************************************************************
class CStone_Block :public CBlock
{
public:
	CStone_Block(int nPriority = OBJTYPE_BLOCK);
	~CStone_Block();
	static CStone_Block *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
};

#endif
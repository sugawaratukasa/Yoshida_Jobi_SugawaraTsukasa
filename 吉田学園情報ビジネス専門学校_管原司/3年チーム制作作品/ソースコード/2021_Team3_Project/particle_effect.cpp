//******************************************************************************
// パーティクルエミッター [particle_emitter.cpp]
// Author : 管原　司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "particle.h"
#include "particle_effect.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define SPLASH		("data/Text/Effect/Splash.txt")		// テキストパス
#define WAVE		("data/Text/Effect/Wave.txt")		// テキストパス
#define SMOKE		("data/Text/Effect/Smoke.txt")		// テキストパス
#define EXPLOSION	("data/Text/Effect/Explosion.txt")	// テキストパス
#define WOOD		("data/Text/Effect/Wood_Effect.txt")// テキストパス
#define REMAINDER	(0)									// 余り0
#define MAX_TEXT	(1024)								// テキストの最大数
//******************************************************************************
// コンストラクタ
//******************************************************************************
CParticle_Effect::CParticle_Effect()
{
	m_pos = ZeroVector3;
	m_nCreate_TotalCount = ZERO_INT;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CParticle_Effect::~CParticle_Effect()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CParticle_Effect * CParticle_Effect::Create(D3DXVECTOR3 pos, TYPE type)
{
	// CParticle_Effectのポインタ
	CParticle_Effect *pParticle_Effect = NULL;

	// NULLの場合
	if (pParticle_Effect == NULL)
	{
		// メモリ確保
		pParticle_Effect = new CParticle_Effect;

		// NULLでない場合
		if (pParticle_Effect != NULL)
		{
			// 位置代入
			pParticle_Effect->m_pos = pos;

			// タイプ代入
			pParticle_Effect->m_Type = type;

			// 初期化
			pParticle_Effect->Init(pos, ZeroVector3);
		}
	}
	// ポインタを返す
	return pParticle_Effect;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CParticle_Effect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 読み込み用
	char cText[MAX_TEXT];
	// 種類
	switch (m_Type)
	{
	case TYPE_SPLASH:
		// テキスト読み込み
		sprintf(cText, SPLASH);
		break;
	case TYPE_WAVE:
		// テキスト読み込み
		sprintf(cText, WAVE);
		break;
	case TYPE_SMOKE:
		// テキスト読み込み
		sprintf(cText, SMOKE);
		break;
	case TYPE_EXPLOSION:
		// テキスト読み込み
		sprintf(cText, EXPLOSION);
		break;
	case TYPE_WOOD:
		// テキスト読み込み
		sprintf(cText, WOOD);
		break;
		// 例外
	default:
		break;
	}
	// 読み込み
	Load(cText);

	// 生成
	CParticle::CreateEffect(m_pos, m_nCreate_TotalCount, cText);

	// 破棄
	Uninit();

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CParticle_Effect::Uninit(void)
{
	// 破棄
	Release();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CParticle_Effect::Update(void)
{
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CParticle_Effect::Draw(void)
{
}
//******************************************************************************
// 読み込み関数
//******************************************************************************
void CParticle_Effect::Load(const char * cText)
{
	// 読み込み用
	char cReedText[MAX_TEXT];

	// 文字の判別用
	char cHeadText[MAX_TEXT];

	// 使わない文字
	char cDie[MAX_TEXT];

	// ファイルポインタ
	FILE *pFile = nullptr;

	// NULLの場合
	if (pFile == nullptr)
	{
		//ファイルを開く
		pFile = fopen(cText, "r");

		// NULLでない場合
		if (pFile != nullptr)
		{
			// SCRIPTの文字が見つかるまで
			while (strcmp(cHeadText, "SCRIPT") != ZERO_INT)
			{
				// テキストからcReedText分文字を読み込む
				fgets(cReedText, sizeof(cReedText), pFile);

				// 読み込んだ文字ををcHeadTextに格納
				sscanf(cReedText, "%s", &cHeadText);
			}
			// cHeadTextがSCRIPTだったら
			if (strcmp(cHeadText, "SCRIPT") == ZERO_INT)
			{
				// END_SCRIPTの文字が見つかるまで
				while (strcmp(cHeadText, "END_SCRIPT") != ZERO_INT)
				{
					// テキストからcReedText分文字を読み込む
					fgets(cReedText, sizeof(cReedText), pFile);

					// 読み込んだ文字ををcHeadTextに格納
					sscanf(cReedText, "%s", &cHeadText);

					// cHeadTextがMOTIONSETだったら
					if (strcmp(cHeadText, "SETTINGS") == ZERO_INT)
					{
						// END_MOTIONSETの文字が見つかるまで
						while (strcmp(cHeadText, "END_SETTINGS") != ZERO_INT)
						{
							// テキストからcReedText分文字を読み込む
							fgets(cReedText, sizeof(cReedText), pFile);

							// 読み込んだ文字ををcHeadTextに格納
							sscanf(cReedText, "%s", &cHeadText);

							// cHeadTextがALPHA_BLENDの場合
							if (strcmp(cHeadText, "CREATE_TOTAL_COUNT") == ZERO_INT)
							{
								// 情報をm_bAlpha_Blendに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nCreate_TotalCount);
							}
						}
					}
				}
				// ファイルを閉じる
				fclose(pFile);
			}
			// 開けなかったら
			else
			{
				printf("ファイルを開く事が出来ませんでした。\n");
			}
		}
	}
}
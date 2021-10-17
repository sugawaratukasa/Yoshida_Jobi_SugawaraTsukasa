//******************************************************************************
// パーティクル[particle.cpp]
// Author : 管原　司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "pbillboard.h"
#include "resource_manager.h"
#include "particle_texture.h"
#include "particle.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define MAX_TEXT		(1024)							// テキストの最大数
#define RANDOM_POS_MUT	(10)							// 10倍
#define MUT				(2)								// ２倍
#define ROT				(D3DXVECTOR3(0.0f,0.0f,0.0f))	// 向き
#define MIN_COL			(0.0f)							// 色の最小値
#define MIN_LIFE		(0)								// ライフの最小値
#define MIN_SCALE		(0.0f)							// 拡大率の最小値
#define DEVIDE_SIZE		(10)							// サイズ除算
#define ROT_RANDOM		(360)							// 向きのランダム値
//******************************************************************************
// コンストラクタ
//******************************************************************************
CParticle::CParticle(PRIORITY Priority) : CpBillboard(Priority)
{
	m_bAlpha_Blend		= false;
	m_bLife				= false;
	m_bRandomPos		= false;
	m_bRandomSize		= false;
	m_bAddScale			= false;
	m_bSubColor			= false;
	m_bRotRandom		= false;
	m_bTexRandom		= false;
	m_Random_pos		= ZeroVector3;
	m_size				= ZeroVector3;
	m_move				= ZeroVector3;
	m_AddAngle			= ZeroVector3;
	m_color				= WhiteColor;
	m_SubColor			= WhiteColor;
	m_nAlpha			= ZERO_INT;
	m_nLife				= ZERO_INT;
	m_nTexNum			= ZERO_INT;
	m_nMinTex_RandomNum = ZERO_INT;
	m_nMaxTex_RandomNum = ZERO_INT;
	m_fAngle			= ZERO_FLOAT;
	m_fAddAngle			= ZERO_FLOAT;
	m_fRandom_Min_Size	= ZERO_FLOAT;
	m_fRandom_Max_Size	= ZERO_FLOAT;
	m_fAddScale			= ZERO_FLOAT;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CParticle::~CParticle()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CParticle *CParticle::Create(D3DXVECTOR3 pos, const char *cText)
{
	// CParticleのポインタ
	CParticle *pParticle = nullptr;

	// nullptrの場合
	if (pParticle == nullptr)
	{
		// メモリ確保
		pParticle = new CParticle;

		// NULLでない場合
		if (pParticle != nullptr)
		{
			// 初期化
			pParticle->Init(pos, cText);
		}
	}
	// ポインタを返す
	return pParticle;
}

//******************************************************************************
// 初期化
//******************************************************************************
HRESULT CParticle::Init(D3DXVECTOR3 pos, const char *cText)
{
	// テキスト読み込み
	LoadParticle(cText);

	// 初期化
	CpBillboard::Init(pos, m_size);

	// サイズ設定
	SetSize(m_size);

	// サイズ設定
	SetRotation(ROT);

	// 色設定
	SetColor(m_color);

	// セットアルファ
	SetAlpha(m_nAlpha);

	// テクスチャのポインタ取得
	CParticle_Texture *pParticle_Texture = CManager::GetResourceManager()->GetParticle_Texture();

	// !nullcheck
	if (pParticle_Texture != nullptr)
	{
		// falseの場合
		if (m_bTexRandom == false)
		{
			// テクスチャ受け渡し
			BindTexture(pParticle_Texture->GetTexture(m_nTexNum));
		}
		// trueの場合
		if (m_bTexRandom == true)
		{
			// テクスチャランダム
			int nTexNum = m_nMinTex_RandomNum + (int)(rand() * (m_nMaxTex_RandomNum - m_nMinTex_RandomNum + 1.0f) / (1.0f + RAND_MAX));

			// テクスチャ受け渡し
			BindTexture(pParticle_Texture->GetTexture(nTexNum));
		}
	}
	// trueの場合
	if (m_bRotRandom == true)
	{
		D3DXVECTOR3 rot = ZeroVector3;

		// 向きランダム
		rot.z = float(rand() % ROT_RANDOM);

		// ラジアン変換
		rot = D3DXToRadian(rot);

		// 向き設定
		SetRotation(rot);
	}
	// trueの場合
	if (m_bRandomSize == true)
	{
		// サイズ
		D3DXVECTOR3 size = ZeroVector3;

		// サイズをランダム
		float fRandomSize = float(rand() % (int)m_fRandom_Max_Size + (int)m_fRandom_Min_Size);

		// サイズを設定
		size.x = fRandomSize;

		// サイズを設定
		size.y = fRandomSize;

		// サイズ設定
		SetSize(size);
	}

	// trueの場合
	if (m_bRandomPos == true)
	{
		// 位置取得
		D3DXVECTOR3 pos = GetPosition();

		// 位置
		D3DXVECTOR3 Random_pos = ZeroVector3;

		// 位置ランダム
		Random_pos.x = float(rand() % (int)m_Random_pos.x *RANDOM_POS_MUT * MUT - (int)m_Random_pos.x *RANDOM_POS_MUT / MUT);

		// 除算
		Random_pos.x = Random_pos.x / RANDOM_POS_MUT;

		// yが0より大きい場合
		if (m_Random_pos.y > ZERO_FLOAT)
		{
			// 位置ランダム
			Random_pos.y = float(rand() % (int)m_Random_pos.y * RANDOM_POS_MUT);

			// 除算
			Random_pos.y = Random_pos.y / RANDOM_POS_MUT;
		}
		// 位置ランダム
		pos += Random_pos;

		// 位置設定
		SetPosition(pos);
	}

	// 角度ランダム
	m_fAngle = float(rand() % (int)m_fAngle);

	// 角度取得
	m_Angle.x = m_fAngle;
	m_Angle.y = m_fAngle;
	m_Angle.z = m_fAngle;

	return S_OK;
}

//******************************************************************************
// 終了
//******************************************************************************
void CParticle::Uninit(void)
{
	// 終了
	CpBillboard::Uninit();
}

//******************************************************************************
// 更新
//******************************************************************************
void CParticle::Update(void)
{
	// 更新
	CpBillboard::Update();

	// 位置取得
	D3DXVECTOR3 pos = GetPosition();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// 色取得
	D3DXCOLOR col = GetColor();

	// 拡大率取得
	float fScale = GetScale();

	// 角度加算
	m_Angle.x += m_AddAngle.x;
	m_Angle.y += m_AddAngle.y;
	m_Angle.z += m_AddAngle.z;

	// ライフを使用する場合
	if (m_bLife == true)
	{
		// デクリメント
		m_nLife--;

		// ライフが0以下の場合
		if (m_nLife <= MIN_LIFE)
		{
			// 終了
			Uninit();
			return;
		}
	}
	// 拡大率加算が使用状態なら
	if (m_bAddScale == true)
	{
		// 拡大率加算
		fScale += m_fAddScale;

		// 拡大率が0.0f以下の場合
		if (fScale <= MIN_SCALE)
		{
			// 終了
			Uninit();
			return;
		}
	}
	// 色減算を使用する場合
	if (m_bSubColor == true)
	{
		// 減算
		col -= m_SubColor;

		// α値が0.0f以下の場合
		if (col.a <= MIN_COL)
		{
			// 終了
			Uninit();
			return;
		}
	}

	// 拡大率設定
	SetScale(fScale);

	// サイズ設定
	SetSize(size);

	// 色設定
	SetColor(col);

	// 位置更新
	pos.x += cosf(D3DXToRadian(m_Angle.x))*m_move.x;
	pos.y += sinf(D3DXToRadian(m_Angle.y))*m_move.y;
	pos.z += sinf(D3DXToRadian(m_Angle.z))*m_move.z;

	SetPosition(pos);
}

//******************************************************************************
// 描画
//******************************************************************************
void CParticle::Draw(void)
{
	// 加算合成を行わない場合
	if (m_bAlpha_Blend == false)
	{
		// 描画
		CpBillboard::Draw();
	}
	// 加算合成を行う場合
	if (m_bAlpha_Blend == true)
	{
		// レンダラー取得
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// 加算合成の設定
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		// 描画
		CpBillboard::Draw();

		// 元に戻す
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}
//******************************************************************************
// 情報設定
//******************************************************************************
void CParticle::LoadParticle(const char * cText)
{
	// 読み込み用
	char cReedText[MAX_TEXT];

	// 文字の判別用
	char cHeadText[MAX_TEXT];

	// 使わない文字
	char cDie[MAX_TEXT];

	// ファイルポインタ
	FILE *pFile = NULL;

	// NULLの場合
	if (pFile == NULL)
	{
		//ファイルを開く
		pFile = fopen(cText, "r");

		// NULLでない場合
		if (pFile != NULL)
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
							if (strcmp(cHeadText, "ALPHA_BLEND") == ZERO_INT)
							{
								// 情報をm_bAlpha_Blendに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bAlpha_Blend);
							}
							// cHeadTextがLIFEの場合
							if (strcmp(cHeadText, "LIFE") == ZERO_INT)
							{
								// 情報をm_bLifeに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bLife);
							}
							// cHeadTextがRANDOM_POSの場合
							if (strcmp(cHeadText, "RANDOM_POS") == ZERO_INT)
							{
								// 情報をm_bRandomPosに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bRandomPos);
							}
							// cHeadTextがRANDOM_SIZEの場合
							if (strcmp(cHeadText, "RANDOM_SIZE") == ZERO_INT)
							{
								// 情報をm_bRandomSizeに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bRandomSize);
							}
							// cHeadTextがADD_SCALEの場合
							if (strcmp(cHeadText, "ADD_SCALE") == ZERO_INT)
							{
								// 情報をm_bAddScaleに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bAddScale);
							}
							// cHeadTextがCOLOR_SUBTRACTの場合
							if (strcmp(cHeadText, "COLOR_SUBTRACT") == ZERO_INT)
							{
								// 情報をm_bSubColorに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bSubColor);
							}
							// cHeadTextがROT_RANDOMの場合
							if (strcmp(cHeadText, "ROT_RANDOM") == ZERO_INT)
							{
								// 情報をm_bRotRandomに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bRotRandom);
							}
							// cHeadTextがTEX_RANDOMの場合
							if (strcmp(cHeadText, "TEX_RANDOM") == ZERO_INT)
							{
								// 情報をm_bTexRandomに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bTexRandom);
							}
							// cHeadTextがTEXTURE_NUMの場合
							if (strcmp(cHeadText, "TEXTURE_NUM") == ZERO_INT)
							{
								// 情報をm_nTexNumに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nTexNum);
							}
							// cHeadTextがMIN_TEXTURE_RANDOM_NUMの場合
							if (strcmp(cHeadText, "MIN_TEXTURE_RANDOM_NUM") == ZERO_INT)
							{
								// 情報をm_nMinTex_RandomNumに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nMinTex_RandomNum);
							}
							// cHeadTextがMAX_TEXTURE_RANDOM_NUMの場合
							if (strcmp(cHeadText, "MAX_TEXTURE_RANDOM_NUM") == ZERO_INT)
							{
								// 情報をm_nMaxTex_RandomNumに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nMaxTex_RandomNum);
							}
							// cHeadTextがALPHA_NUMの場合
							if (strcmp(cHeadText, "ALPHA_NUM") == ZERO_INT)
							{
								// 情報をm_nAlphaに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nAlpha);
							}
							// cHeadTextがSIZEの場合
							if (strcmp(cHeadText, "SIZE") == ZERO_INT)
							{
								// 情報をm_bRandomPosに格納
								sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &m_size.x, &m_size.y, &m_size.z);
							}
							// cHeadTextがMOVEの場合
							if (strcmp(cHeadText, "MOVE") == ZERO_INT)
							{
								// 情報をm_moveに格納
								sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &m_move.x, &m_move.y, &m_move.z);
							}
							// cHeadTextがANGLEの場合
							if (strcmp(cHeadText, "ANGLE") == ZERO_INT)
							{
								// 情報をm_fAngleに格納
								sscanf(cReedText, "%s %s %f", &cDie, &cDie, &m_fAngle);
							}
							// cHeadTextがANGLEの場合
							if (strcmp(cHeadText, "ADD_ANGLE") == ZERO_INT)
							{
								// 情報をm_fAngleに格納
								sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &m_AddAngle.x, &m_AddAngle.y, &m_AddAngle.z);
							}
							// cHeadTextがCOLORの場合
							if (strcmp(cHeadText, "COLOR") == ZERO_INT)
							{
								// 情報をm_colorに格納
								sscanf(cReedText, "%s %s %f %f %f %f", &cDie, &cDie, &m_color.r, &m_color.g, &m_color.b, &m_color.a);
							}
							// cHeadTextがLIFE_VALUEの場合
							if (strcmp(cHeadText, "LIFE_VALUE") == ZERO_INT)
							{
								// 情報をm_nLifeに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nLife);
							}
							// cHeadTextがADD_SCALE_VALUEの場合
							if (strcmp(cHeadText, "ADD_SCALE_VALUE") == ZERO_INT)
							{
								/// 情報をm_fAddScaleに格納
								sscanf(cReedText, "%s %s %f", &cDie, &cDie, &m_fAddScale);
							}
							// cHeadTextがCOLOR_SUB_VALUEの場合
							if (strcmp(cHeadText, "COLOR_SUB_VALUE") == ZERO_INT)
							{
								// 情報をm_SubColorに格納
								sscanf(cReedText, "%s %s %f %f %f %f", &cDie, &cDie, &m_SubColor.r, &m_SubColor.g, &m_SubColor.b, &m_SubColor.a);
							}
							// cHeadTextがMIN_SIZE_VALUEの場合
							if (strcmp(cHeadText, "MIN_SIZE_VALUE") == ZERO_INT)
							{
								// 情報をm_fRandom_Min_Sizeに格納
								sscanf(cReedText, "%s %s %f", &cDie, &cDie, &m_fRandom_Min_Size);
							}
							// cHeadTextがMAX_SIZE_VALUEの場合
							if (strcmp(cHeadText, "MAX_SIZE_VALUE") == ZERO_INT)
							{
								// 情報をm_fRandom_Max_Sizeに格納
								sscanf(cReedText, "%s %s %f", &cDie, &cDie, &m_fRandom_Max_Size);
							}
							// cHeadTextがRANDOM_POS_VALUEの場合
							if (strcmp(cHeadText, "RANDOM_POS_VALUE") == ZERO_INT)
							{
								// 情報をm_fRandomPosに格納
								sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &m_Random_pos.x, &m_Random_pos.y, &m_Random_pos.z);
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
//******************************************************************************
// テクスチャ番号設定
//******************************************************************************
void CParticle::SetTexNum(int nTexNum)
{
	m_nTexNum = nTexNum;
}
//******************************************************************************
// エフェクト生成
//******************************************************************************
void CParticle::CreateEffect(D3DXVECTOR3 pos, int nCreateNum, const char *cText)
{
	// 数分生成
	for (int nCnt = ZERO_INT; nCnt < nCreateNum; nCnt++)
	{
		// 生成
		Create(pos, cText);
	}
}
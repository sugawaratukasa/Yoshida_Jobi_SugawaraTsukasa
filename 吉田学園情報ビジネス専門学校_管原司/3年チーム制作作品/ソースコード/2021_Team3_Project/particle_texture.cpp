//***********************************************************************************
//	テクスチャ	[texture.cpp]
//	Author : 管原 司
//***********************************************************************************
//***********************************************************************************
// インクルードファイル
//***********************************************************************************
#include "manager.h"
#include "renderer.h"
#include "particle_texture.h"
//***********************************************************************************
// マクロ定義
//***********************************************************************************
#define TEXTURE_TEXT	("data/Texture/Effect_Texture/texture.txt")	// テクスチャテキスト
#define MAX_TEXT		(1024)									// 文字の最大数
//***********************************************************************************
//静的メンバ変数宣言
//***********************************************************************************
//***********************************************************************************
// コンストラクタ
//***********************************************************************************
CParticle_Texture::CParticle_Texture()
{
	m_pTexture		= nullptr;
	m_pLoadTexture	= nullptr;
	m_nNumTex		= ZERO_INT;
}
//***********************************************************************************
// デストラクタ
//***********************************************************************************
CParticle_Texture::~CParticle_Texture()
{
}
//***********************************************************************************
// 初期化関数
//***********************************************************************************
HRESULT CParticle_Texture::Init(void)
{
	// テクスチャ読み込み
	Load();

	return S_OK;
}
//***********************************************************************************
// 終了関数
//***********************************************************************************
void CParticle_Texture::Uninit(void)
{
	// テクスチャ破棄
	if (m_pTexture != nullptr)
	{
		// 破棄
		m_pTexture->Release();

		// NULLに
		m_pTexture = nullptr;
	}
	// 読み込み用テクスチャの破棄
	if (m_pLoadTexture != NULL)
	{
		// テクスチャ数分回す
		for (int nCnt = ZERO_INT; nCnt < m_nNumTex; nCnt++)
		{
			// テクスチャ破棄
			m_pLoadTexture[nCnt]->Release();
		}

		// メモリ破棄
		delete[] m_pLoadTexture;

		// m_pParticle_TextureをNULLに
		m_pLoadTexture = nullptr;
	}
}
//***********************************************************************************
// テクスチャ読み込み
//***********************************************************************************
void CParticle_Texture::Load(void)
{
	// 読み込み用
	char cReedText[MAX_TEXT];

	// 文字の判別用
	char cHeadText[MAX_TEXT];

	// 使わない文字
	char cDie[MAX_TEXT];

	// テクスチャのテキスト
	char **cTexText = nullptr;

	// テクスチャカウント
	int nTexCnt = ZERO_INT;

	// ファイルポインタ
	FILE *pFile = nullptr;

	// NULLの場合
	if (pFile == nullptr)
	{
		//ファイルを開く
		pFile = fopen(TEXTURE_TEXT, "r");

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

					// cHeadTextがTEXTURE_NUMの場合 
					if (strcmp(cHeadText, "TEXTURE_NUM") == ZERO_INT)
					{
						// テクスチャの数をm_nNumTexに格納
						sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nNumTex);

						// NULLの場合
						if (cTexText == nullptr)
						{
							// メモリ確保
							cTexText = new char *[m_nNumTex];

							// NULLでない場合
							if (cTexText != NULL)
							{
								// テクスチャ数分回す
								for (int nCnt = ZERO_INT; nCnt < m_nNumTex; nCnt++)
								{
									// メモリ確保
									cTexText[nCnt] = new char[MAX_TEXT];
								}
							}
						}
					}
					// cHeadTextがTEXTURE_FILENAMEの場合
					if (strcmp(cHeadText, "TEXTURE_FILENAME") == ZERO_INT)
					{
						// テクスチャのパスをcTexTextに格納
						sscanf(cReedText, "%s %s %s", &cDie, &cDie, cTexText[nTexCnt]);

						// インクリメント
						nTexCnt++;
					}
				}
			}
			// レンダラー取得
			LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

			// メモリ確保
			m_pLoadTexture = new LPDIRECT3DTEXTURE9[m_nNumTex];

			// テクスチャ数分回す
			for (int nCnt = ZERO_INT; nCnt < m_nNumTex; nCnt++)
			{
				// テクスチャ読み込み
				D3DXCreateTextureFromFile(pDevice, cTexText[nCnt], &m_pLoadTexture[nCnt]);
			}
			// NULLでない場合
			if (cTexText != nullptr)
			{
				// テクスチャ数分回す
				for (int nCnt = ZERO_INT; nCnt < m_nNumTex; nCnt++)
				{
					// メモリ破棄
					delete[] cTexText[nCnt];
				}
				// メモリ破棄
				delete[] cTexText;

				// NULLに
				cTexText = nullptr;
			}
			// ファイルを閉じる
			fclose(pFile);
		}
	}
}
//***********************************************************************************
// テクスチャ取得
//***********************************************************************************
LPDIRECT3DTEXTURE9 CParticle_Texture::GetTexture(int TexNum)
{
	// 代入
	m_pTexture = m_pLoadTexture[TexNum];

	// テクスチャを返す
	return m_pTexture;
}
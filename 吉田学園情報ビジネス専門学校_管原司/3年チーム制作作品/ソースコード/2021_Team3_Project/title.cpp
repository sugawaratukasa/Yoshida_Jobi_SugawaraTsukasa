//=============================================================================
//
// タイトル処理 [title.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "title.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "scene2d.h"
#include "fade.h"
#include "keyboard.h"
#include "texture.h"
#include "sound.h"
#include "joypad.h"
#include "resource_manager.h"
#include "camera.h"
#include "camera_title.h"
#include "light.h"
#include "player.h"
#include "water.h"
#include "title_map.h"
#include "title_sky.h"
#include "title_press_enter.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define LOGO_POS			(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 150.0f, 0.0f))
#define LOGO_SIZE			(D3DXVECTOR3(950.0f, 220.0f, 0.0f))
#define TITLE_PLAYER_POS	(D3DXVECTOR3(5000.0f, 0.0f, -20000.0f))
#define SHIP_PADDLE_ROTATE	(D3DXToRadian(1.0f))
#define KEYBORAD_MAX		(256)
// LightInfo
#define TITLE_LIGHT_VECDIR	(D3DXVECTOR3(-0.8f, -1.0f, 1.0f))

//=============================================================================
// コンストラクタ
//=============================================================================
CTitle::CTitle()
{
	m_pShip = nullptr;
	m_pObject2D.clear();
	m_pCamera = nullptr;
	m_pLight = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CTitle::~CTitle()
{
	// 終了処理
	Uninit();
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTitle::Init(void)
{
	// 3Dオブジェクト生成
	Create3DObject();

	// 2Dオブジェクト生成
	Create2DObject();

	// 音の設定
	CSound *pSound = GET_SOUND_PTR;
	pSound->Play(CSound::SOUND_BGM_TITLE);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	for (auto &object : m_pObject2D)
	{
		// 終了処理
		object->Uninit();
	}

	// オブジェクト削除
	m_pObject2D.clear();

	// カメラ終了処理
	if (m_pCamera)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	// ライト終了処理
	if (m_pLight)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	// 船終了処理
	if (m_pShip)
	{
		m_pShip->Uninit();
		m_pShip = nullptr;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CTitle::Update(void)
{
	// カメラ更新処理
	if (m_pCamera)
	{
		m_pCamera->Update();
	}

	// 船のパドルの回転
	if (m_pShip)
	{
		m_pShip->PaddleRotateR(-SHIP_PADDLE_ROTATE);
		m_pShip->PaddleRotateL(-SHIP_PADDLE_ROTATE);
	}

	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();
	// キーが押されたかつモード遷移中でない場合
	if (pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
	{
		// 画面遷移
		ModeTransition();
	}
	//// どこのキーでも反応する様に
	//for (int nCnt = ZERO_INT; nCnt <= KEYBORAD_MAX; nCnt++)
	//{
	//	// キーが押されたかつモード遷移中でない場合
	//	if (pKey->GetTrigger(nCnt) && mode == CFade::FADE_MODE_NONE)
	//	{
	//		// 画面遷移
	//		ModeTransition();
	//	}
	//}
	// コントローラのボタンを押した場合
	for (int nCnt = ZERO_INT; nCnt < CInputJoypad::JOY_BUTTON_MAX; nCnt++)
	{
		// キーが押されたかつモード遷移中でない場合
		if (CManager::GetJoypad()->GetJoystickTrigger(nCnt, 0) && mode == CFade::FADE_MODE_NONE)
		{
			// 画面遷移
			ModeTransition();
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CTitle::Draw(void)
{

}

//=============================================================================
// 2Dオブジェクト生成
//=============================================================================
void CTitle::Create2DObject(void)
{
	// テクスチャのポイン取得
	CTexture *pTexture = GET_TEXTURE_PTR;

	// メモリ確保
	CScene2D *pTitleLogo = CScene2D::Create(LOGO_POS, LOGO_SIZE);
	pTitleLogo->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_TITLE_LOGO));

	// ボタン生成
	CScene2D *pPressButton = CTitlePress_Button::Create();

	// オブジェクト追加
	m_pObject2D.push_back(pTitleLogo);

	// オブジェクト追加
	m_pObject2D.push_back(pPressButton);
}

//=============================================================================
// 3Dオブジェクト生成
//=============================================================================
void CTitle::Create3DObject(void)
{
	// タイトルカメラの生成
	if (!m_pCamera)
	{
		m_pCamera = CCameraTitle::Create();
	}

	// ライトの生成
	if (!m_pLight)
	{
		m_pLight = CLight::Create();
		m_pLight->SetVecDir(TITLE_LIGHT_VECDIR);
	}

	// プレイヤーの生成
	if (!m_pShip)
	{
		m_pShip = CPlayer::Create(TITLE_PLAYER_POS, ZeroVector3);
	}

	CWater::Create();		// 海
	CTitleMap::Create();	// タイトルマップ
	CTitleSky::Create();	// 空
}
//=============================================================================
// モード遷移
//=============================================================================
void CTitle::ModeTransition(void)
{
	// 音の設定
	CSound *pSound = GET_SOUND_PTR;
	pSound->Play(CSound::SOUND_SE_BUTTON);

	CFade *pFade = CManager::GetFade();
	pFade->SetFade(CManager::MODE_TYPE_GAME);
}
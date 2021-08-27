//******************************************************************************
// メイン処理 [main.h]
// Author : 管原　司
//******************************************************************************
#ifndef _MAIN_H_
#define _MAIN_H_
#define DIRECTINPUT_VERSION 0x800
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <Windows.h>
#include <dinput.h>
#include "d3dx9.h"
//*****************************************************************************
// ライブラリファイルのリンク
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
int GetFPS(void);
#endif
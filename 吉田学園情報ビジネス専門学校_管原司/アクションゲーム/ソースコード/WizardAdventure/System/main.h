//******************************************************************************
// ���C������ [main.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _MAIN_H_
#define _MAIN_H_
#define DIRECTINPUT_VERSION 0x800
#define _CRT_SECURE_NO_WARNINGS 
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <Windows.h>
#include <dinput.h>
#include "d3dx9.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
//*****************************************************************************
// ���C�u�����t�@�C���̃����N
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define INIT_INT			(0)														// int�^������
#define INIT_FLOAT			(0.0f)													// float�^������
#define INIT_D3DXVECTOR3	(D3DXVECTOR3(0.0f,0.0f,0.0f))							// D3DXVECTOR3������
#define INIT_COLOR			(D3DXCOLOR(0.0f,0.0f,0.0f,0.0f))						// D3DXCOLOR������
#define MAX_TEXT			(1024)													// �e�L�X�g�̍ő�
int GetFPS(void);
#endif
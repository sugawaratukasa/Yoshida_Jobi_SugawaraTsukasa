//=============================================================================
//
// ���C�� [main.h]
// Author : ��K������
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_
#define DIRECTINPUT_VERSION (0x0800)
#define _CRT_SECURE_NO_WARNINGS 
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "windows.h"
#include "d3dx9.h"
#include <dinput.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(1920)
#define SCREEN_HEIGHT	(1080)
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define MAX_TEXT		(1024)
#define MAX_PASS_LETTER (128)
#define MAX_POLYGON		(256)
#define NUM_POLYGON		(2)
#define NUM_VERTEX		(4)
#define REMAINDER		(0)
#define INIT_INT (0)
#define INIT_FLOAT (0.0f)
#define INITIAL_D3DXVECTOR3 (D3DXVECTOR3(0.0f,0.0f,0.0f))
#define INITIAL_ROTATION (D3DXVECTOR3(D3DXToRadian(0.0f),D3DXToRadian(0.0f),D3DXToRadian(0.0f)))
#define INITIAL_D3DXCOLOR (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))

//*****************************************************************************
// ���C�u�����t�@�C���̃����N
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"ws2_32.lib")
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float		rhw;	//���W�ϊ��p���W��
	D3DCOLOR	col;	//���_�J���[
	D3DXVECTOR2	tex;	//�e�N�X�`��
}VERTEX_2D;

typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR	col;	//���_�J���[
	D3DXVECTOR2	tex;	//�e�N�X�`��
}VERTEX_3D;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
#ifdef _DEBUG
int GetFPS(void);
#endif
#endif
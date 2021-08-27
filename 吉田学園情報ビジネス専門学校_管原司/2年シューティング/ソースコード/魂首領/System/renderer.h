//******************************************************************************
// �`�� [renderer.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _RENERER_H_
#define _RENDERER_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <dinput.h>
#include "d3dx9.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define WINDOW_POS_X	(0)		// �T�C�Y
#define WINDOW_POS_Y	(0)		// �T�C�Y
#define SCREEN_WIDTH	(1280)	// �T�C�Y
#define SCREEN_HEIGHT	(720)	// �T�C�Y
//#undef _DEBUG
//******************************************************************************
// �N���X
//******************************************************************************
class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3Decvice; }
private:
	void DrawFPS(void);
	LPDIRECT3D9 m_pD3D;				//LPDIRECT3D9
	LPDIRECT3DDEVICE9 m_pD3Decvice;	//�f�o�C�X
	LPD3DXFONT m_pFont;				//�t�H���g
};
#endif
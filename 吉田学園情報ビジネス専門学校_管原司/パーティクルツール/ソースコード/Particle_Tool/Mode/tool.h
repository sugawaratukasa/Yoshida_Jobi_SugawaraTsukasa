//******************************************************************************
// �c�[�� [tool.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _TOOL_H_
#define _TOOL_H_
//******************************************************************************
// �}�N����`
//******************************************************************************
#define FLOOR_POLYGON_POS D3DXVECTOR3(0.0f,0.0f,0.0f)
#define FLOOR_POLYGON_SIZE D3DXVECTOR3(100.0f,0.0f,100.0f)
#define RIGTT_WALL_POS D3DXVECTOR3(100.0f,0.0f,0.0f)
#define LEFT_WALL_POS D3DXVECTOR3(-100.0f,0.0f,0.0f)
#define RIGHT_WALL_SIZE D3DXVECTOR3(100.0f,100.0f,0.0f)
#define LEFT_WALL_SIZE D3DXVECTOR3(100.0f,100.0f,0.0f)
#define RIGHT_WALL_ROT D3DXVECTOR3(0.0,D3DXToRadian(90.0f),0.0f)
#define LEFT_WALL_ROT D3DXVECTOR3(0.0,D3DXToRadian(-90.0f),0.0f)

//*****************************************************************************
//�w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "mode.h"
#include "ui.h"
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
//*****************************************************************************
//�O���錾
//*****************************************************************************
class CUI;
//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CTool :public CMode
{
public:
	CTool();
	~CTool();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Particle_Create(void);
	CUI *m_pUi;				// CUI�̃|�C���^
	int m_nCreateCount;		// �����J�E���g
	int m_nCreateCount_2;	// �����J�E���g2
};
#endif
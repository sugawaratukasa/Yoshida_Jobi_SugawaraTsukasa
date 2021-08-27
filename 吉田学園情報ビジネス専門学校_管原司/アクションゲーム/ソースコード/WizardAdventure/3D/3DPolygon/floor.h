//******************************************************************************
// ��[floor.h]
// Author : �ǌ��i
//******************************************************************************
#ifndef _FLOOR_H_
#define _FLOOR_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "scene3d.h"
//******************************************************************************
// �O���錾
//******************************************************************************

//******************************************************************************
// �N���X
//******************************************************************************
class CFloor : public CScene3d
{
public:
	CFloor(int nPriority = OBJTYPE_FLOOR);
	~CFloor();
	static HRESULT Load(void);
	static void Unload(void);
	static CFloor *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���ւ̃|�C���^
};
#endif
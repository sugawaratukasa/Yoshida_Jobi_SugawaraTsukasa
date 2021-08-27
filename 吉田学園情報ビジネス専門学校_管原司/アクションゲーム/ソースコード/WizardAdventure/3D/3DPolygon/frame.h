//******************************************************************************
// �t���[��[frame.h]
// Author : �ǌ��i
//******************************************************************************
#ifndef _FRAME_H_
#define _FRAME_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "scene3d.h"
//******************************************************************************
// �O���錾
//******************************************************************************
class CBlock;
//******************************************************************************
// �N���X
//******************************************************************************
class CFrame : public CScene3d
{
public:
	CFrame(int nPriority = OBJTYPE_FRAME);
	~CFrame();
	static HRESULT Load(void);
	static void Unload(void);
	static CFrame *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, CBlock *pBlock);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetSelectingColor(D3DXCOLOR col);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	CBlock *m_pBlock;						// ��
};
#endif
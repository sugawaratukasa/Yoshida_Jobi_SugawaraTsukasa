//******************************************************************************
// �r���{�[�h [billboard.h]
// Author : SugawaraTsukasa
//******************************************************************************
#ifndef _PBILLBOARD_H_
#define _PBILLBOARD_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
// Author : SugawaraTsukasa
//******************************************************************************
#include "scene.h"
//******************************************************************************
// �N���X
// Author : SugawaraTsukasa
//******************************************************************************
class CpBillboard : public CScene
{
public:
	CpBillboard(PRIORITY Priority = PRIORITY_3D_UI);
	~CpBillboard();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//*********************************************
	// �Z�b�^�[
	//*********************************************
	void SetPosition(D3DXVECTOR3 pos);
	void SetRotation(D3DXVECTOR3 rot);
	void SetSize(D3DXVECTOR3 size);
	void SetColor(D3DXCOLOR col);
	void SetTexture(float fTexX, float fTexY, float fTexX2, float fTexY2);
	void SetScale(float fScale);
	void SetAlpha(int nAlpha);
	//*********************************************
	// �Q�b�^�[
	//*********************************************
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXCOLOR GetColor(void) { return m_col; }
	float GetScale(void) { return m_fScale; }

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

private:
	LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;						// �ʒu���W
	D3DXVECTOR3 m_size;						// �T�C�Y
	D3DXVECTOR3 m_rot;						// ����
	D3DXCOLOR m_col;						// �J���[
	float  m_fTexX;							// �e�N�X�`��X���W
	float  m_fTexX2;						// �e�N�X�`��X2���W
	float  m_fTexY;							// �e�N�X�`��Y���W
	float  m_fTexY2;						// �e�N�X�`��Y���W
	D3DXMATRIX m_mtxWorld;					// �}�g���b�N�X
	float m_fScale;							// �g��
	int m_nAlpha;							// ���ߒl
	bool m_bDraw;							// �`�攻��
};
#endif
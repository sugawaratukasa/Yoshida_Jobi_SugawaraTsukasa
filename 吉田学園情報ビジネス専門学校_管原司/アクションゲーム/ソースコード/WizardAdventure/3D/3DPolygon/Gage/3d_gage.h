//******************************************************************************
// 3D_�Q�[�W[3d_gage.h]
// Author : �ǌ��i
//******************************************************************************
#ifndef _3D_GAGE_H_
#define _3D_GAGE_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "scene.h"
//******************************************************************************
// �N���X
//******************************************************************************
class C3D_Gage :public CScene
{
public:
	C3D_Gage(int nPriority = OBJTYPE_BILLBOARD_UI);
	~C3D_Gage();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	void SetRotation(D3DXVECTOR3 rot);
	void SetSize(D3DXVECTOR3 size);
	void SetColor(D3DXCOLOR col);
	void SetTexture(float tex_x, float tex_x2, float tex_y, float tex_y2);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetGage(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, int nGageNum);
	void SetGageNum(int nGageNum);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXCOLOR GetColor(void) { return m_col; }
private:
	LPDIRECT3DTEXTURE9		m_pTexture;	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;					// �ʒu���W
	D3DXVECTOR3 m_size;					// �T�C�Y
	D3DXVECTOR3 m_rot;					// ����
	D3DXCOLOR m_col;					// �F
	D3DXMATRIX m_mtxWorld;				// ���[���h���W
	int m_nGageNum;						// �Q�[�W�̒l
	float m_fMaxGageNum;				// �Q�[�W�̍ő�
	float m_fGageNum;					// �Q�[�W�̒l
	float m_fTex_X;						// �e�N�X�`��X
	float m_fTex_X2;					// �e�N�X�`��X2
	float m_fTex_Y;						// �e�N�X�`��Y
	float m_fTex_Y2;					// �e�N�X�`��Y2
	bool m_bDraw;						// �`�攻��
};
#endif
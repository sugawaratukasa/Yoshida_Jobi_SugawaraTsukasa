//******************************************************************************
// �Q�[�W [gage.h]
// Author : �ǌ��i
//******************************************************************************
#ifndef _GAGE_H_
#define _GAGE_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "scene.h"
//******************************************************************************
// �N���X
//******************************************************************************
class CGage :public CScene
{
public:
	CGage(int nPriority = OBJTYPE_UI);
	~CGage();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetTexture(float tex_x, float tex_x2, float tex_y, float tex_y2);
	void SetPosition(D3DXVECTOR3 pos);
	void SetSize(D3DXVECTOR3 size);
	void SetColor(D3DXCOLOR color);
	void SetGageNum(int nGageNum);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXCOLOR GetColor(void) { return m_color; }
	void SetGage(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color, int nGageNum);
private:
	LPDIRECT3DTEXTURE9		m_pTexture;	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3	m_pos;					// �|���S���̈ʒu
	D3DXVECTOR3	m_size;					// �T�C�Y
	D3DXCOLOR m_color;					// �J���[
	int m_nGageNum;						// �Q�[�W�̒l
	float m_fMaxGageNum;				// �Q�[�W�̍ő�
	float m_fGageNum;					// �Q�[�W�̒l
	float m_fTex_X;						// �e�N�X�`��X
	float m_fTex_X2;					// �e�N�X�`��X2
	float m_fTex_Y;						// �e�N�X�`��Y
	float m_fTex_Y2;					// �e�N�X�`��Y2
};

#endif

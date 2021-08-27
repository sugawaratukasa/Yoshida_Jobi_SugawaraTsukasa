//******************************************************************************
// scene2d [scene2d.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _SCENE2D_H_
#define _SCENE2D_H_
//******************************************************************************
// �N���X
//******************************************************************************
class CScene2d : public CScene
{
public:

	CScene2d(int nPriority = OBJTYPE_DEFAULT);
	~CScene2d();
	static CScene2d*Create();

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	void SetTexture(float fTexX, float fTexY, float fTexAnimX , float fTexAnimY);
	void SetRGBA(D3DXCOLOR col);
	void SetRot(D3DXVECTOR3 rot);
	void SetSize(D3DXVECTOR3 size);
	void SetScale(float fScale);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXCOLOR GetRGBA(void) { return m_col; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	float GetScale(void) { return m_fScale; }
private:
	LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// �o�b�t�@
	D3DXVECTOR3 m_pos;					// �ʒu���W
	D3DXVECTOR3 m_rot;					// ����
	D3DXVECTOR3 m_size;					// �T�C�Y
	D3DXCOLOR m_col;					// �J���[
	float m_fAngle;						// �p�x
	float m_fLength;					// �Ίp��
	float m_fTexX;						// �e�N�X�`��X
	float m_fTexY;						// �e�N�X�`��Y
	float m_fTexAnimX;					// �e�N�X�`���A�j���[�V����
	float m_fTexAnimY;					// �e�N�X�`���A�j���[�V����
	float m_fScale;						// �g��
};
#endif
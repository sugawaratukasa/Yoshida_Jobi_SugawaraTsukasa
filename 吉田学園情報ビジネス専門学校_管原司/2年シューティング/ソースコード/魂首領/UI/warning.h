//******************************************************************************
// ���[�j���O [warning.h]
// Author : �ǌ� �i
//******************************************************************************
#ifndef _WARNING_H_
#define _WARNING_H_
//******************************************************************************
// �N���X
//******************************************************************************
class CWarning : public CScene2d
{
public:
	CWarning(int nPriority = OBJTYPE_UI);
	~CWarning();
	static CWarning * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//texture
	bool m_bColor;							//�J���[���
	int m_nWarnigCount;						//�J�E���g
};
#endif
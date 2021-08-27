//******************************************************************************
// �e [bullet.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _BULLET_H_
#define _BULLET_H_
//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �N���X
//******************************************************************************
class CBullet : public CScene2d
{
public:

	//�e�N�X�`���^�C�v
	typedef enum
	{
		TEX_TYPE_NONE = -1,
		TEX_TYPE_NORMAL,
		TEX_TYPE_BEAM,
		TEX_TYPE_BOM,
		TEX_TYPE_ENEMY_NORMAL,
		TEX_TYPE_MAX
	}TEX_TYPE;
	CBullet(int nPriority = 10);
	~CBullet();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, TEX_TYPE textype, OBJTYPE objtype);
	bool Collision(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2);
	static void AllReleaseBullet(void);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TEX_TYPE_MAX];	// texture�̏��
	D3DXVECTOR3 m_rot;										// ����
	TEX_TYPE m_Textype;										// �e�N�X�`���̃^�C�v
	static bool m_bUseBullet;								// �e�̎g�p����
};
#endif
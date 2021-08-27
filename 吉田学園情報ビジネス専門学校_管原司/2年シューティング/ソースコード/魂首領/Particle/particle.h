//******************************************************************************
// �p�[�e�B�N������ [particle.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _PARTICLE_H_
#define _PARTICLE_H_
//******************************************************************************
// �N���X
//******************************************************************************
class CParticle : public CScene2d
{
public:
	// �e�N�X�`���^�C�v
	typedef enum
	{
		TEX_TYPE_NONE = -1,
		TEX_TYPE_CIRCLE,
		TEX_TYPE_EXPLOSION,
		TEX_TYPE_FLASH,
		TEX_TYPE_MAX,
	}TEX_TYPE;

	CParticle(int nPriority = OBJTYPE_PARTICLE);
	~CParticle();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, TEX_TYPE TexType);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TEX_TYPE_MAX];	// �e�N�X�`�����
	TEX_TYPE m_TexType;									// �e�N�X�`���^�C�v
};
#endif
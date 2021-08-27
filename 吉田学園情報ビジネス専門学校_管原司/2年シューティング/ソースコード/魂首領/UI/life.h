//******************************************************************************
// ���C�t���� [life.h]
// Author : �ǌ� �i
//******************************************************************************
#ifndef _LIFE_H_
#define _LIFE_H_
//******************************************************************************
// �}�N����`
//******************************************************************************
#define MAX_LIFE	(3)								// ���C�t�ő吔
//******************************************************************************
// �O���錾
//******************************************************************************
class CScene2d;
//******************************************************************************
// �N���X
//******************************************************************************
class CLife : public CScene
{
public:
	CLife(int nPriority = OBJTYPE_UI);
	~CLife();
	static HRESULT Load(void);
	static void Unload(void);
	static CLife * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddLife(int nLife);
	void HitDamage(int Damage);
	void SetLife(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// �e�N�X�`�����
	CScene2d * m_apScene2D[MAX_LIFE];		// ���C�t�̏��
	D3DXVECTOR3 m_pos;						// �ʒu���W
	D3DXVECTOR3 m_size;						// �T�C�Y
	int m_nNumLife;							// ���C�t��
};
#endif
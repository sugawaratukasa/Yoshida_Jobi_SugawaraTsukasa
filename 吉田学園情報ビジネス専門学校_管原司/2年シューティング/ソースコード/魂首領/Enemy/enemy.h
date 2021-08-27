//******************************************************************************
// �G [enemy.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _ENEMY_H_
#define _ENEMY_H_
//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �N���X
//******************************************************************************
class CEnemy : public CScene2d
{
public:
	// �e�N�X�`���̗񋓌^
	typedef enum
	{
		TEX_TYPE_NONE = -1,
		TEX_TYPE_NORMAL,
		TEX_TYPE_BLUE,
		TEX_TYPE_RED,
		TEX_TYPE_SHIP_BATTERY,
		TEX_TYPE_MAX
	}TEX_TYPE;
	// ��Ԃ̗񋓌^
	typedef enum
	{
		STATE_NONE = -1,
		STATE_NORMAL,
		STATE_DAMAGE,
		STATE_DEATH,
		STATE_MAX
	}STATE;
	CEnemy(int nPriority = OBJTYPE_ENEMY);
	~CEnemy();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void HitEnemy(int nDamage);
	void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife, TEX_TYPE tex_type, CScene::OBJTYPE objtype);

	STATE GetState(void) { return m_state; }
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TEX_TYPE_MAX];	//�@�e�N�X�`�����
	TEX_TYPE m_TexType;										//�@�e�N�X�`���^�C�v
	STATE m_state;											//�@state
	int m_nLife;											//�@�̗�
	int m_nDamageCount;										//�@�_���[�W�J�E���g
};
#endif
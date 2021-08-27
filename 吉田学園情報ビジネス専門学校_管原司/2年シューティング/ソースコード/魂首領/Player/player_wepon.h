//******************************************************************************
// ���@�̕��� [player_wepon.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _PLAYER_WEPON_H_
#define _PLAYER_WEPON_H_
//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �N���X
//******************************************************************************
class CPlayer_Wepon : public CScene2d
{
public:
	// �^�C�v�̗񋓌^
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_RIGHT,
		TYPE_LEFT,
		TYPE_MAX
	}TYPE;

	CPlayer_Wepon(int nPriority = OBJTYPE_PLAYER_WEPON);
	~CPlayer_Wepon();
	static HRESULT Load(void);
	static void Unload(void);
	static CPlayer_Wepon * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void Move(void);
	void Shot(void);

	static LPDIRECT3DTEXTURE9 m_pTexture;	// �e�N�X�`�����
	TYPE m_Type;								// �^�C�v
	int m_nCountAnim;						// �J�E���^�[
	int m_nPatternAnim;						// �p�^�[��

};
#endif
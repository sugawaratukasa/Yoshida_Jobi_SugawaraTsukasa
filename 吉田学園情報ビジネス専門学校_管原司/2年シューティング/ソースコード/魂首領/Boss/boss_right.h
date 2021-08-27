//******************************************************************************
// �{�X�E [boss_right.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _BOSS_RIGHT_H_
#define _BOSS_RIGHT_H_
//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �N���X
//******************************************************************************
class CBoss_Right : public CScene2d
{
public:

	// ���
	typedef enum
	{
		STATE_NONE = -1,
		STATE_NORMAL,
		STATE_DAMAGE,
		STATE_MAX
	}STATE;

	CBoss_Right(int nPriority = OBJTYPE_BOSS_RIGHT);
	~CBoss_Right();
	static HRESULT Load(void);
	static void Unload(void);
	static CBoss_Right * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(int nDamage);

private:
	void State(void);
	void Attack(void);

	static LPDIRECT3DTEXTURE9 m_pTexture;	// �e�N�X�`�����
	STATE m_State;							// ��ԕϐ�
	int m_nAttackCount;						// �U���J�E���g
	int m_nDamageCount;						// �_���[�W�J�E���g
	int m_nHalfLife_AttackCount;			// ���C�t�������̎��̍U���J�E���g
};
#endif
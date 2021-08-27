//******************************************************************************
// �{�X [boss.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _BOSS_H_
#define _BOSS_H_
//******************************************************************************
// �N���X
//******************************************************************************
class CBoss : public CScene2d
{
public:
	typedef enum
	{
		STATE_NONE = -1,
		STATE_MOVE,
		STATE_NORMAL,
		STATE_DAMAGE,
		STATE_DEATH_EFFECT,
		STATE_DEATH,
		STATE_MAX
	}STATE;
	CBoss(int nPriority = OBJTYPE_BOSS);
	~CBoss();
	static HRESULT Load(void);
	static void Unload(void);
	static CBoss * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void HitBoss(int nDamage);

	D3DXVECTOR3 GetCollisionSize(void) { return m_CollisionSize; }
	int GetState(void) { return m_State; }
	int GetLife(void) { return m_nLife; }
	bool GetHalfLife(void) { return m_bLifeHalf; }

private:
	void Attack(void);
	void State(void);
	void Move(void);
	void Death(void);

	static LPDIRECT3DTEXTURE9 m_pTexture;					// �e�N�X�`�����
	D3DXVECTOR3 m_CollisionSize;							// �����蔻��T�C�Y
	D3DXVECTOR3 m_move;										// �ړ�
	int m_nLife;											// �̗�
	int m_nAttackCount;										// �U��
	int m_nDamageCount;										// �_���[�W
	int m_nSetCount;										// �{�X�Z�b�g�J�E���g
	int m_nDeathCount;										// ���S���������p�J�E���g
	STATE m_State;											// State
	bool m_bMove;											// move
	bool m_bLifeHalf;										// ���C�t�������ȉ��ɂȂ�����
};
#endif
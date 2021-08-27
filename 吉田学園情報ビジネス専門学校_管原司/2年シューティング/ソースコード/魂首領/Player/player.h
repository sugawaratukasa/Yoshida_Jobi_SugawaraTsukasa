//******************************************************************************
// ���@ [player.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _PLAYER_H_
#define _PLAYER_H_
//******************************************************************************
// �O���錾
//******************************************************************************
class CPlayer_Beam;
class CBom_Beam;
//******************************************************************************
// �N���X
//******************************************************************************
class CPlayer : public CScene2d
{
public:
	// �^�C�v�̗񋓌^
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_MAIN,
		TYPE_RIGHT,
		TYPE_LEFT,
		TYPE_MAX
	}TYPE;
	// ��ԗp�̗񋓌^
	typedef enum
	{
		STATE_NONE = -1,
		STATE_NORMAL,
		STATE_RESPAWN,
		STATE_DAMAGE,
		STATE_DEAD,
		STATE_MAX
	}STATE;
	// Level�p�̗񋓌^
	typedef enum
	{
		LEVEL_NONE = -1,
		LEVEL_1,
		LEVEL_2,
		LEVEL_3,
		LEVEL_MAX
	}LEVEL;

	CPlayer(int nPriority = OBJTYPE_PLAYER);
	~CPlayer();
	static HRESULT Load(void);
	static void Unload(void);
	static CPlayer * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void HitPlayer(void);
	void GetBom(int nBom);
	void GetPowerUp(void);
	void SetContinue(int Continue);
	void SavePlayer(void);
	void SetBossBom(bool bBoss);

	D3DXVECTOR3 GetCollisionSize(void) { return m_Collision_Size; }
	int GetLevel(void) { return m_nPower; }
	int GetPlayerState(void) { return m_nPlayerState; }
	bool GetUseShot(void) { return m_bUseShot; }
	bool GetUseBeam(void) { return m_bUseBeam; }
	bool GetUseBossBom(void) { return m_bBossBom; }
private:
	void Move(void);
	void Shot(void);
	void PlayerState(void);

	static LPDIRECT3DTEXTURE9 m_pTexture;	// �e�N�X�`�����
	D3DXVECTOR3 m_Collision_Size;			// �����蔻��T�C�Y
	CPlayer_Beam *m_pBeam;					// �r�[���̃|�C���^
	CBom_Beam *m_pBomBeam;					// �{���r�[��
	int m_nContinue;						// �R���e�B�j���[�J�E���g
	int m_nLife;							// �̗�
	int m_nCountAnim;						// �J�E���^�[
	int m_nPatternAnim;						// �p�^�[��
	int m_AttackCount;						// �e���˂̃J�E���g
	int m_nBeamCount;						// �r�[���̗��ߎ���
	int m_nDamageCount;						// �_���[�W�J�E���g
	int m_nRespawnCount;					// ���X�|�[���J�E���g
	int m_nBomCount;						// �{���̔��˃J�E���g
	int m_nBom_possession_count;			// �{���̏�����
	int m_nScore;							// �X�R�A
	int m_nPlayerState;						// �v���C���[��state
	int m_nPower;							// �v���C���[�̃p���[
	bool m_bMove;							// �ړ��̏��
	bool m_bUseShot;						// �ʏ�e�𔭎˂����� 
	bool m_bUseBeam;						// �r�[���̎g�p���
	bool m_bUseBom;							// �{���̎g�p���
	bool m_bBossBom;						// �{�X��p�̃{���̎g�p���	
	bool m_bBoss;							// �{�X
	bool m_bBossDeath;						// �{�X�����S������
	bool m_bContinue;						// �R���e�B�j���[
};
#endif
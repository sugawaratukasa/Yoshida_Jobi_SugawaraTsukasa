//******************************************************************************
// �Q�[�� [game.h]
// Author : �ǌ� �i
//******************************************************************************
#ifndef _GAME_H_
#define _GAME_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "mode.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define MAX_GAME_WIDTH (960)
#define MIN_GAME_WIDTH (320)
//******************************************************************************
// �O���錾
//******************************************************************************
class CPlayer;
class CScore;
class CLife;
class CEnemy;
class CBomUI;
class CShip;
class CBoss;

///******************************************************************************
// �N���X
//******************************************************************************
class CGame : public CMode
{
public:
	CGame();
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void CreateBoss(void);
	static CScore * GetScore(void) { return m_pScore; }
	static CLife * GetLife(void) { return m_pLife; }
	static CPlayer * GetPlayer(void) { return m_pPlayer; }
	static CBomUI * GetBomUI(void) { return m_pBom; }
	static CShip * GetShip(void) { return m_pShip; }
	static CBoss * GetBoss(void) { return m_pBoss; }
private:
	void Enemy_Respawn(void);

	static CScore * m_pScore;	// �X�R�A���
	static CLife * m_pLife;		// ���C�t���
	static CPlayer * m_pPlayer;	// �v���C���[���
	static CBomUI * m_pBom;		// �{��
	static CShip * m_pShip;		// �D
	static CBoss * m_pBoss;		// �{�X

	bool m_bfade;				// �t�F�[�h
	int m_nCount;				// �J�E���g
	int m_nRespawn_Count;		// Respawn�J�E���g
	int m_nShipSpawnCount;		// �D�̐���
	bool m_bUseBoss;			// �{�X�킩
};
#endif
//******************************************************************************
// �H��[ghost.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _GHOST_H_
#define _GHOST_H_

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "enemy.h"
//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �O���錾
//******************************************************************************
class CModel;
class CParticle_Emitter;
//******************************************************************************
// �v���C���[�N���X
//******************************************************************************
class CGhost :public CEnemy
{
public:
	enum TYPE
	{
		TYPE_NONE = -1,
		TYPE_FIRE,
		TYPE_ICE,
		TYPE_MAX
	};
	enum ROT
	{
		ROT_RIGHT = 0,
		ROT_LEFT
	};
	CGhost(int nPriority = OBJTYPE_ENEMY);
	~CGhost();
	static CGhost *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	TYPE GetType(void) { return m_Type; }
private:
	void Attack(void);
	void Rot(void);

	CParticle_Emitter *m_pParticleEmitter;	// CParticle_Emitter1�̃|�C���^
	TYPE m_Type;							// ���
	int m_nAttackCount;						// �U���J�E���g
	ROT m_Rot;								// �����̗�
};
#endif
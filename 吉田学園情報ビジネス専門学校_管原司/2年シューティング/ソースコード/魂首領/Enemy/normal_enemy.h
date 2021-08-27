//******************************************************************************
// �ʏ�̓G [normal_enemy.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _NORMAL_ENEMY_H_
#define _NORMAL_ENEMY_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "enemy.h"
//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �N���X
//******************************************************************************
class CNormal_Enemy : public CEnemy
{
public:

	CNormal_Enemy(int nPriority = OBJTYPE_ENEMY);
	~CNormal_Enemy();
	static CNormal_Enemy * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife, TEX_TYPE tex_type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Attack(void);
	int m_nAttackCount;	// �U���J�E���g
};
#endif
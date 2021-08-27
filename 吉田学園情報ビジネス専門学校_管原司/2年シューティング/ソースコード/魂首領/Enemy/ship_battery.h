//******************************************************************************
// �D�̖C�� [ship_battery_enemy.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _SHIP_BATTERY_H_
#define _SHIP_BATTERY_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************
#include "enemy.h"
//******************************************************************************
// �N���X
//******************************************************************************
class CShip_Battery : public CEnemy
{
public:

	CShip_Battery(int nPriority = OBJTYPE_ENEMY);
	~CShip_Battery();
	static CShip_Battery * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife, TEX_TYPE tex_type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Attack(void);
	D3DXVECTOR3 m_pos;	// �ʒu���W
	int m_nAttackCount;	// �U���J�E���g
};
#endif
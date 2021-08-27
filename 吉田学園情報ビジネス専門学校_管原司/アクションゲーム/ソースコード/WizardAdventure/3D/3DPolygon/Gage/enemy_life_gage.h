//******************************************************************************
// �G�̃��C�t�Q�[�W [enemy_life_gage.h]
// Author : �ǌ��i
//******************************************************************************
#ifndef _ENEMY_LIFE_GAGE_H_
#define _ENEMY_LIFE_GAGE_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "3d_gage.h"
//******************************************************************************
// �O���錾
//******************************************************************************
class CEnemy;
class C3D_Gage_Back;
//******************************************************************************
// �N���X
//******************************************************************************
class CEnemy_Life_Gage : public C3D_Gage
{
public:
	CEnemy_Life_Gage(int nPriority = OBJTYPE_BILLBOARD_UI);
	~CEnemy_Life_Gage();
	static CEnemy_Life_Gage *Create(D3DXVECTOR3 pos, CEnemy *pEnemy);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	CEnemy *m_pEnemy;				// CEnemy�̃|�C���^
	C3D_Gage_Back *m_p3D_Gage_Back;	// C3D_Gage_Back�̃|�C���^
};
#endif
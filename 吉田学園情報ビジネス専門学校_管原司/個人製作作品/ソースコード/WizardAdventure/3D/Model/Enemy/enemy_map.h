//******************************************************************************
// �G�}�b�v[enemy_map.h]
// Author : �ǌ��i
//******************************************************************************
#ifndef _ENEMY_MAP_H_
#define _ENEMY_MAP_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "scene.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define MAX_ENEMY	(3)	// �G�̍ő吔
//******************************************************************************
// �O���錾
//******************************************************************************
class CEnemy;
//******************************************************************************
// �N���X
//******************************************************************************
class CEnemy_Map : public CScene
{
public:

	// ���
	enum OBJ_TYPE
	{
		OBJ_TYPE_NONE = 0,		// ����
		OBJ_TYPE_BLOCK,			// �u���b�N
		OBJ_TYPE_ENEMY_FIRE,	// �΂̓G
		OBJ_TYPE_ENEMY_ICE,		// �X�̓G
		OBJ_TYPE_MAX			// �ő�
	};

	CEnemy_Map(int nPriority = OBJTYPE_ENEMY_MAP);
	~CEnemy_Map();
	static CEnemy_Map *Create(D3DXVECTOR3 pos);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool GetbEnd(void) { return m_bEnd; }
private:
	void ObjCreate(void);
	void ObjLoad(void);
	void SetRowCol(void);

	OBJ_TYPE **m_apObjIndex;			// �s��
	int m_nRow;							// �s
	int m_nCol;							// ��
	D3DXVECTOR3 m_pos;					// �ʒu
	CEnemy* m_apEnemy[MAX_ENEMY];		// CEnemy�̃|�C���^
	bool m_bEnd;						// �I������
};
#endif
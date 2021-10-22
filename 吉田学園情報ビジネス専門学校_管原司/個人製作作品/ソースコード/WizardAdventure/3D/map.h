//******************************************************************************
// �}�b�v[map.h]
// Author : �ǌ��i
//******************************************************************************
#ifndef _MAP_H_
#define _MAP_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "scene.h"
//******************************************************************************
// �O���錾
//******************************************************************************

//******************************************************************************
// �N���X
//******************************************************************************
class CMap : public CScene
{
public:
	enum TYPE
	{
		TYPE_TUTORIAL = 0,
		TYPE_GAME
	};
	//�ǂݍ��ގ��
	typedef enum
	{
		LOAD_TYPE_FLOOR = -1,
		LOAD_TYPE_BLOCK,
		LOAD_TYPE_BACK_OBJ,
		LOAD_TYPE_MAX
	}LOAD_TYPE;
	// ���
	typedef enum
	{
		FLOOR_TYPE_NONE = -1,	// �ŏ�
		FLOOR_TYPE_GLASS,		// ���u���b�N
		FLOOR_TYPE_MAX			// �ő�
	}FLOOR_TYPE;

	// ���
	typedef enum
	{
		OBJ_TYPE_NONE = 0,		// ����
		OBJ_TYPE_NORMAL_BLOCK,	// ���u���b�N
		OBJ_TYPE_NEEDLE,		// �j�u���b�N
		OBJ_TYPE_BUTTON,		// �{�^��
		OBJ_TYPE_GATE,			// ��
		OBJ_TYPE_CHECK_POINT,	// �`�F�b�N�|�C���g
		OBJ_TYPE_END,			// �N���A
		OBJ_TYPE_WOOD_BOX,		// �ؔ�
		OBJ_TYPE_WOOD,			// ��
		OBJ_TYPE_ENEMY_CREATE,	// �G����
		OBJ_TYPE_MAX			// �ő�
	}OBJ_TYPE;

	// �w�i�I�u�W�F�N�g�̎��
	enum BACK_OBJ_TYPE
	{
		BACK_OBJ_NONE = 0,	// �ŏ�
		BACK_OBJ_TREE,		// ��
		BACK_OBJ_STONE_0,	// �Α�
		BACK_OBJ_STONE_1,	// �Β�
		BACK_OBJ_STONE_2,	// �Ώ�
		BACK_OBJ_MAX		// �ő�
	};
	CMap();
	~CMap();
	static CMap *Create(TYPE type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void MapCreate(void);
	void FloorCreate(void);
	void FloorLoad(void);
	void BlockCreate(void);
	void BlockLoad(void);
	void BackObjCreate(void);
	void BackObjLoad(void);
	void SetRowCol(LOAD_TYPE load_type);

	FLOOR_TYPE **m_apFloorIndex;		// �s��
	OBJ_TYPE **m_apObjIndex;			// �s��
	BACK_OBJ_TYPE **m_apBackObjIndex;	// �s��
	int m_nRow;							// �s
	int m_nCol;							// ��
	TYPE m_Type;						// ���
};
#endif
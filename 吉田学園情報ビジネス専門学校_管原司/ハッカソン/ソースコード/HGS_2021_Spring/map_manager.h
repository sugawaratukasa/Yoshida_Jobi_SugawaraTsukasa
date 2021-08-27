//=============================================================================
//
// �}�b�v���� [map.h]
// Author : �ѐ�ї���
//
//=============================================================================
#ifndef _MAP_H_
#define _MAP_H_

#define MAX_ROW (10)
#define MAX_COL (800)

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CBlock;

//2D�I�u�W�F�N�g�N���X
class CMap : public CScene
{
public:
	CMap(int nPriority = 3);
	~CMap();

	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_AIR,//��C
		TYPE_BLOCK,//�u���b�N
		TYPE_MAX
	}TYPE;
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMap * Create(void);
private:
	typedef struct
	{
		int x, y;
	}CUBE_ID;
	void MapLoad(void);
	TYPE m_aMapIndex[MAX_ROW][MAX_COL];
	CBlock * m_apBlock[MAX_ROW][MAX_COL];

};
#endif // !_SCORE_H_

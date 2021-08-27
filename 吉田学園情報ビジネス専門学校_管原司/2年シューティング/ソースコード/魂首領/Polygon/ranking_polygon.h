//******************************************************************************
// �����L���O�|���S�� [ranking_polygon.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _RANKING_POLYGON_H_
#define _RANKING_POLYGON_H_
//******************************************************************************
// �N���X
//******************************************************************************
class CRanking_Polygon : public CPolygon
{
public:
	CRanking_Polygon(int nPriority = OBJTYPE::OBJTYPE_UI);
	~CRanking_Polygon();
	static CRanking_Polygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TEX_TYPE textype);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:

};
#endif
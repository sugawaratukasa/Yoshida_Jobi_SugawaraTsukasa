//******************************************************************************
// PressEnter�|���S�� [press_enter_polygon.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _PRESS_ENTER_POLYGON_H_
#define _PRESS_ENTER_POLYGON_H_
//******************************************************************************
// �N���X
//******************************************************************************
class CPress_Enter_Polygon : public CPolygon
{
public:
	CPress_Enter_Polygon(int nPriority = OBJTYPE::OBJTYPE_UI);
	~CPress_Enter_Polygon();
	static CPress_Enter_Polygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TEX_TYPE textype);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	bool m_bColor;
};
#endif
//******************************************************************************
// �R���e�B�j���[�|���S�� [continue_polygon.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _CONTINUE_POLYGON_H_
#define _CONTINUE_POLYGON_H_
//******************************************************************************
// �N���X
//******************************************************************************
class CContinue_Polygon : public CPolygon
{
public:
	CContinue_Polygon(int nPriority = OBJTYPE::OBJTYPE_UI);
	~CContinue_Polygon();
	static CContinue_Polygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TEX_TYPE textype);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:

};
#endif
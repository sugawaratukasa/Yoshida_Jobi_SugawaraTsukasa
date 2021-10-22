//******************************************************************************
// 3D�|���S��[3d_polygon.h]
// Author : �ǌ��i
//******************************************************************************
#ifndef _3D_POLYGON_H_
#define _3D_POLYGON_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "scene3d.h"
//******************************************************************************
// �O���錾
//******************************************************************************

//******************************************************************************
// �N���X
//******************************************************************************
class C3D_Polygon : public CScene3d
{
public:
	// �e�N�X�`���^�C�v�̗񋓌^
	enum TEX_TYPE
	{
		TEX_TYPE_NONE = -1,
		TEX_TYPE_SKY,
		TEX_TYPE_CLOUD,
		TEX_TYPE_MAX
	};

	C3D_Polygon(int nPriority = OBJTYPE_BG);
	~C3D_Polygon();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 size, TEX_TYPE textype);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TEX_TYPE_MAX];		// �e�N�X�`���ւ̃|�C���^
	TEX_TYPE m_Textype;										// �e�N�X�`���̎��
	bool m_bDraw;
};
#endif

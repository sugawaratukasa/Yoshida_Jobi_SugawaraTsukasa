//******************************************************************************
// �D [ship.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _SHIP_H_
#define _SHIP_H_
//******************************************************************************
// �N���X
//******************************************************************************
class CShip : public CScene2d
{
public:
	CShip(int nPriority = OBJTYPE_SHIP);
	~CShip();
	static HRESULT Load(void);
	static void Unload(void);
	static CShip * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void BatteryCreate(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�@�e�N�X�`�����
};
#endif
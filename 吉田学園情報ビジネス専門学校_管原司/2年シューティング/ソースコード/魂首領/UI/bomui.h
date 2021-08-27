//******************************************************************************
// �{����UI [bomui.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _BOM_UI_H_
#define _BOM_UI_H_
//******************************************************************************
// �}�N����`
//******************************************************************************
#define MAX_BOM		(5)								// �{���̍ő吔
//******************************************************************************
// �O���錾
//******************************************************************************
class CScene2d;
//******************************************************************************
// �N���X
//******************************************************************************
class CBomUI : public CScene
{
public:
	CBomUI(int nPriority = OBJTYPE_UI);
	~CBomUI();
	static CBomUI * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetBomUI(int mBomPossesion);
private:
	// �������̗񋓌^
	typedef enum
	{
		POSESSION_NONE = 0,
		POSESSION_1,
		POSESSION_2,
		POSESSION_3,
		POSESSION_4,
		POSESSION_MAX
	}POSESSION;

	static LPDIRECT3DTEXTURE9 m_pTexture;	// �e�N�X�`�����
	CScene2d * m_apScene2D[MAX_BOM];		// ���C�t�̏��
	D3DXVECTOR3 m_pos;						// �ʒu���W
	D3DXVECTOR3 m_size;
	int m_nBom_Posession;					// �{���̏�����
};
#endif
//******************************************************************************
// �w�i [bg.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _BG_H_
#define _BG_H_
//******************************************************************************
// �N���X
//******************************************************************************
class CBg : public CScene
{
public:
	// �^�C�v�̗񋓌^
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_FARST_BG,
		TYPE_SECOUND_BG,
		TYPE_THIRD_BG,
		TYPE_MAX
	}TYPE;
	CBg(int nPriority = OBJTYPE_BG);
	~CBg();
	static HRESULT Load(void);
	static void Unload(void);
	static CBg * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];	// �e�N�X�`�����
	CScene2d * m_apScene2D[TYPE_MAX];					// BG�̏��
	TYPE m_type;										// �^�C�v
	D3DXVECTOR3 m_pos;									// �ʒu
	D3DXVECTOR3 m_size;									// �T�C�Y
	float m_fSlowMove;									// �x��
	float m_fmove;										// �ړ�
};													   
#endif

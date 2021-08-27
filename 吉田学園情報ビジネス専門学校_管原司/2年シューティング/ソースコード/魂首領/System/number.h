//******************************************************************************
// �i���o�[���� [number.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef NUMBER_H_
#define NUMBER_H_
//******************************************************************************
// �N���X
//******************************************************************************
class CNumber
{
public:
	CNumber();
	~CNumber();
	static HRESULT Load(void);
	static void Unload(void);
	static CNumber * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNumber(int nNumber);
	void SetPosition(D3DXVECTOR3 pos);
	void SetSize(D3DXVECTOR3 size);
	void SetColor(D3DXCOLOR col);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXCOLOR GetColor(void) { return m_col; }
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// �o�b�t�@
	D3DXVECTOR3 m_pos;							// �ʒu���W
	D3DXVECTOR3 m_size;							// �T�C�Y
	D3DXCOLOR m_col;							// �F
	int m_nNumber;								// �i���o�[
};
#endif
//******************************************************************************
// beam [beam.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _BEAM_BASE_H_
#define _BEAM_BASE_H_
//******************************************************************************
// �N���X
//******************************************************************************
class CBeam_Base : public CScene
{
public:

	CBeam_Base(int nPriority = OBJTYPE_PLAYER_BULLET);
	~CBeam_Base();

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetBeam(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col);
	void SetPosition(D3DXVECTOR3 pos);
	void SetTexture(float fTexX, float fTexY, float fTexAnimX, float fTexAnimY);
	void SetRGBA(D3DXCOLOR col);
	void SetRot(D3DXVECTOR3 rot);
	void SetSize(D3DXVECTOR3 size);
	void SetSizeY(float sizeY);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXCOLOR GetRGBA(void) { return m_col; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	float GetSizeY(void) { return m_fSizeY; }
private:
	LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// �o�b�t�@
	D3DXVECTOR3 m_pos;					// �ʒu���W
	D3DXVECTOR3 m_rot;					// ����
	D3DXVECTOR3 m_size;					// �T�C�Y
	D3DXCOLOR m_col;					// �J���[
	float m_fSizeY;						// �T�C�Y
	float m_fAddSize;					// �T�C�Y���Z
	float m_fTexX;						// �e�N�X�`��X
	float m_fTexY;						// �e�N�X�`��Y
	float m_fTexAnimX;					// �e�N�X�`���A�j���[�V����
	float m_fTexAnimY;					// �e�N�X�`���A�j���[�V����
	bool m_bAddSize_Stop;				// �T�C�Y���Z��~
};
#endif
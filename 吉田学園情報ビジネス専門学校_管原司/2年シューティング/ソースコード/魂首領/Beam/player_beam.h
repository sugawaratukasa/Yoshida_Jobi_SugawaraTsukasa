//******************************************************************************
// �v���C���[�r�[�� [player_beam.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _PLAYER_BEAM_H_
#define _PLAYER_BEAM_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************
#define BEAM_MAX_NUM	(2)	// ��
//******************************************************************************
// �O���錾
//******************************************************************************
class CBeam;
//******************************************************************************
// �N���X
//******************************************************************************
class CPlayer_Beam : public CScene
{
public:
	CPlayer_Beam(int nPriority = OBJTYPE_PLAYER_BULLET);
	~CPlayer_Beam();

	static CPlayer_Beam *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void BeamCreate(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void ReleaseAllBeam(void);
private:
	void Collision(void);
	D3DXVECTOR3 m_pos;						// �ʒu
	D3DXVECTOR3 m_size;						// �T�C�Y
	CBeam *m_apBeam[BEAM_MAX_NUM];			// CBeam�N���X�̃|�C���^
};
#endif
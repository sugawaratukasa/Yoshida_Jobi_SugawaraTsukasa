//******************************************************************************
// �{�� [bom.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _BOM_H_
#define _BOM_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************

//******************************************************************************
// �N���X
//******************************************************************************
class CBom : public CBullet
{
public:

	CBom(int nPriority = OBJTYPE_PLAYER_BULLET);
	~CBom();
	static CBom * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, CBullet::TEX_TYPE textype);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void HitEnemy(void);
	int m_nPatternCount;	// �p�^�[���J�E���g
	int m_nAnimCount;		// �A�j���[�V�����J�E���g

};
#endif
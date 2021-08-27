//******************************************************************************
// �p�[�e�B�N���G�~�b�^�[ [particle_emitter.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _PARTICLE_EMITTER_H_
#define _PARTICLE_EMITTER_H_

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "scene.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
//******************************************************************************
// �O���錾
//******************************************************************************

//******************************************************************************
// �N���X
//******************************************************************************
class CParticle_Emitter : public CScene
{
public:
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_STAR_RIGHT,
		TYPE_STAR_LEFT,
		TYPE_FIRE_RIGHT,
		TYPE_FIRE_LEFT,
		TYPE_ICE_RIGHT,
		TYPE_ICE_LEFT,
		TYPE_FIRE_GHOST,
		TYPE_ICE_GHOST,
		TYPE_FIRE_CREATE,
		TYPE_ICE_CREATE,
		TYPE_MAP,
		TYPE_STAR,
		TYPE_MAX
	}TYPE;
	CParticle_Emitter();
	~CParticle_Emitter();
	static CParticle_Emitter *Create(D3DXVECTOR3 pos, TYPE type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Release(void);
	void SetPos(D3DXVECTOR3 pos);
private:
	void CreateParticle(void);
	void Load(const char *cText);
	void Right_Arm(void);
	void Left_Arm(void);
	D3DXVECTOR3 m_pos;		// �ʒu���W
	int m_nCount;			// �Ԋu
	int m_nCreateCount;		// �����J�E���g
	char m_cText[MAX_TEXT];	// �e�L�X�g
	TYPE m_Type;			// �^�C�v
};
#endif
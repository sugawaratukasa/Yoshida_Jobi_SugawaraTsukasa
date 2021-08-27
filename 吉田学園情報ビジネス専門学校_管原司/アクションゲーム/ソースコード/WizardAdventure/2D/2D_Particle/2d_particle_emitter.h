//******************************************************************************
// 2d�p�[�e�B�N���G�~�b�^�[ [2d_particle_emitter.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _2D_PARTICLE_EMITTER_H_
#define _2D_PARTICLE_EMITTER_H_

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
class C2D_Particle_Emitter : public CScene
{
public:
	typedef enum
	{
		TYPE_GREEN,
		TYPE_FIRE,
		TYPE_ICE
	}TYPE;
	C2D_Particle_Emitter();
	~C2D_Particle_Emitter();
	static C2D_Particle_Emitter *Create(D3DXVECTOR3 pos, TYPE type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Release(void);
	void SetPos(D3DXVECTOR3 pos);
private:
	void CreateParticle(void);
	void Load(const char *cText);
	D3DXVECTOR3 m_pos;		// �ʒu���W
	int m_nCount;			// �Ԋu
	int m_nCreateCount;		// �����J�E���g
	char m_cText[MAX_TEXT];	// �e�L�X�g
	TYPE m_Type;			// �^�C�v
};
#endif
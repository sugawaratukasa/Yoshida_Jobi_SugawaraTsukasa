//******************************************************************************
// �p�[�e�B�N���G�~�b�^�[ [particle_emitter.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _PARTICLE_EMITTER_H_
#define _PARTICLE_EMITTER_H_

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "../System/scene.h"
//******************************************************************************
// �N���X
//******************************************************************************
class CParticle_Emitter : public CScene
{
public:
	CParticle_Emitter();
	virtual ~CParticle_Emitter();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void);
	virtual void Draw(void) = 0;

	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	int GetCount(void) { return m_nCount; }
private:
	D3DXVECTOR3 m_pos;	// �ʒu���W
	int m_nCount;		// �J�E���g
};
#endif
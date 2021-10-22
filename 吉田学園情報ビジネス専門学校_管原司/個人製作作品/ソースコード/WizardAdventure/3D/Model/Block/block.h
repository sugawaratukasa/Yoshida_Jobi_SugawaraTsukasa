//******************************************************************************
// �u���b�N [block.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _BLOCK_H_
#define _BLOCK_H_

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "scene.h"
#include "../3D/Model/Object/3d_obj.h"
#include "../3D/Model/model.h"
//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �O���錾
//******************************************************************************
class CFrame;
class CParticle_Emitter;
//******************************************************************************
// �v���C���[�N���X
//******************************************************************************
class CBlock :public C3D_Obj
{
public:
	CBlock(int nPriority = OBJTYPE_BLOCK);
	~CBlock();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Move(void);
	void Create_Move(void);
	void ReleaseBlock(void);
	void SetFrame(void);
	void Selecting(void);
	void UnSelected(void);
	void PlayerSelection(void);
	void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, TYPE type, CBlock *pBlock);
	void SetbMove(bool bMove);
	void SetbEmitter(bool bEmitter);
private:
	void Collision(D3DXVECTOR3 posOld, D3DXVECTOR3 size);
	D3DXVECTOR3 m_posOld;					// �Â��ʒu
	D3DXVECTOR3 m_move;						// �ړ�
	CBlock *m_pBlock;						// �|�C���^
	CFrame *m_pFrame;						// �g�̃|�C���^
	CParticle_Emitter *m_pParticleEmitter;	// CParticle_Emitter�̃|�C���^
	bool m_bMove;							// �ړ��̔���
	bool m_bParticleEmitter;					// ���ˑ̂̔���
};

#endif
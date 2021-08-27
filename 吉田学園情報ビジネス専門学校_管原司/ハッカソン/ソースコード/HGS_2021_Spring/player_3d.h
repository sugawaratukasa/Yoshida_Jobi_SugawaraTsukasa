//=============================================================================
//
// �v���C���[ [player.h]
// Author : ��K������
//
//=============================================================================
#ifndef _PLAYER_3D_H_
#define _PLAYER_3D_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "polygon_3d.h"
#include "block.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPlayer3d :public CPolygon3d
{
public:
	typedef enum
	{
		STATE_NONE = -1,
		STATE_DEATH,		//���S
		STATE_INVINCIBLE,	//���G
		STATE_MAX
	}STATE;		//���
	CPlayer3d(int nPriority = OBJTYPE_PLAYER);
	~CPlayer3d();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CPlayer3d * Create(D3DXVECTOR3 Position);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	float GetCameraDistance(void) { return m_fCameraDistance; }
	D3DXVECTOR3 GetPositionOld(void) { return m_PositionOld; }
	D3DXVECTOR3 GetCollisionSize(void) { return m_CollisionSize; }
	D3DXVECTOR3 GetMove(void) { return m_Move; };
	void SetMove(D3DXVECTOR3 Move);
	void SetCollisionSize(D3DXVECTOR3 CollisionSize);
	void SetState(STATE state);
	STATE GetState(void) { return m_State; };
	void Death(D3DXVECTOR3 HitPos);
	CBlock::IS_COLLISION GetIsCollision(void) { return m_bIsCollision; };

	void SetIsCollision(CBlock::IS_COLLISION isCollision);
private:
	void Input(void);
	void Move(void);
	D3DXVECTOR3 MovableRange(void);
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_PositionOld;				//�ߋ��̈ʒu
	D3DXVECTOR3 m_Move;						//�ړ���
	D3DXVECTOR3 m_CollisionSize;			//�Փ˔���p�T�C�Y
	int m_nSurvivalTime;					//��������
	float m_fSpeed;							//����
	float m_fCameraDistance;				//�J�����Ƃ̋���
	bool m_bJump;							//�W�����v�������ǂ���
	STATE m_State;							//���
	CBlock::IS_COLLISION m_bIsCollision;	//�ǂ̖ʂɓ������Ă邩
	int m_nPattarnAnim;						//�A�j���[�V�����J�E���^
	int m_nCounterAnim;						//�t���[���J�E���^
	int m_nCreateCount;
	float m_fAddSpeed;
	bool m_bSyagami;
};
#endif
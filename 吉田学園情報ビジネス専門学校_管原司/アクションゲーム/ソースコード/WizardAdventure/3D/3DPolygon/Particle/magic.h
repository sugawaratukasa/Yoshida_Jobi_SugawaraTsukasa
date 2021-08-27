//******************************************************************************
// ���@ [magic.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _MAGIC_H_
#define _MAGIC_H_

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "scene.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define MAX_TEXT	(1024)
//******************************************************************************
// �N���X
//******************************************************************************
class CMagic : public CScene
{
public:
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_FIRE_BALL,
		TYPE_ICE_BALL,
		TYPE_ENEMY_FIRE_BALL,
		TYPE_ENEMY_ICE_BALL,
		TYPE_MAX
	}TYPE;
	CMagic();
	~CMagic();
	static CMagic *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Collision(void);
	void Load(const char *cText);
	D3DXVECTOR3 m_pos;				// �ʒu���W
	D3DXVECTOR3 m_move;				// �ړ���
	int m_nCount;					// �Ԋu
	int m_nCreateCount;				// �����J�E���g
	int m_nLife;					// ���C�t
	char m_cText[MAX_TEXT];			// �e�L�X�g
	TYPE m_Type;					// �^�C�v
};
#endif
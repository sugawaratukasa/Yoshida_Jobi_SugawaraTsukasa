//=============================================================================
//
// �Q�[�����[�h [mode_game.h]
// Author : ��K������
//
//=============================================================================
#ifndef _MODE_GAME_H_
#define _MODE_GAME_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CLight;
class CCamera;
class CPlayer2d;
class CPlayer3d;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CGameMode : CScene
{
public:
	CGameMode();
	~CGameMode();
	static CGameMode * Create();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CCamera * GetCamera(void) { return m_pCamera; }
	static CPlayer2d * GetPlayer2d(void) { return m_pPlayer2d; }
	static CPlayer3d * GetPlayer3d(void) { return m_pPlayer3d; }
private:
	void InitCreateAll(void);
	void UpdateCreateAll(void);
	static CCamera * m_pCamera;			//�J�����̃|�C���^
	static CPlayer2d * m_pPlayer2d;		//�v���C���[2D�̃|�C���^
	static CPlayer3d * m_pPlayer3d;		//�v���C���[3D�̃|�C���^
	CLight * m_pLight;				//���C�g�̃|�C���^
};
#endif

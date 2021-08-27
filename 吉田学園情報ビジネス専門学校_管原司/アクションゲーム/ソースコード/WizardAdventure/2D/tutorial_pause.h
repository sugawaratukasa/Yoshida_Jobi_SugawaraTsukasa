//******************************************************************************
// �`���[�g���A���|�[�Y [tutorial_pause.h]
// Author : �ǌ��i
//******************************************************************************
#ifndef _TUTORIAL_PAUSE_H_
#define _TUTORIAL_PAUSE_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "scene.h"
//******************************************************************************
// �O���錾
//******************************************************************************
class C2D_Polygon;
//******************************************************************************
// �N���X
//******************************************************************************
class CTutorial_Pause :public CScene
{
public:
	enum TYPE
	{
		TYPE_BLACK = 0,
		TYPE_RESUME,
		TYPE_CONTROLS,
		TYPE_GAMESTART,
		TYPE_EXIT,
		TYPE_MAX
	};
	CTutorial_Pause(int nPriority = OBJTYPE_NOSTOP_UI);
	~CTutorial_Pause();
	static CTutorial_Pause *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Select(void);
	void Release(void);
	C2D_Polygon *m_apPolygon[TYPE_MAX];	// C2D_Polygon�̃|�C���^
	int m_nCount;						// �J�E���g
	bool m_bStick;						// �X�e�B�b�N�̔���
	bool m_bControls;					// �����̔���
};
#endif
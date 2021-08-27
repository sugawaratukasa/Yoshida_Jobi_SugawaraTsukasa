//*******************************************************************
// �I�u�W�F�N�g���� [scene.h]
// Author : �ǌ��i
//*******************************************************************
#ifndef _SCENE_H_
#define _SCENE_H_
//*******************************************************************
// �C���N���[�h�t�@�C��
//*******************************************************************
#include "main.h"
//*******************************************************************
// �}�N����`
//*******************************************************************
#define DEFAULT_PRIORITY (4)

//*******************************************************************
// �I�u�W�F�N�g�N���X
//*******************************************************************
class CScene
{
public:
	// �I�u�W�F�N�g�^�C�v
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_DEFAULT,
		OBJTYPE_FADE,
		OBJTYPE_TUTORIAL,
		OBJTYPE_PLAYER,
		OBJTYPE_MAX
	}OBJTYPE;

	CScene(int nPriority = OBJTYPE_DEFAULT);
	virtual ~CScene();

	void SetObjType(OBJTYPE objType);
	OBJTYPE GetObjType(void) { return m_objType; }
	static CScene *GetScene(int nPriority);

	//�������z�֐�
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);
	static void DesignationReleaseAll(OBJTYPE type);
	static void SetUpdateStop(bool bUpdateStop);

	static bool GetUpdateStop(void) { return m_bUpdateStop; }

protected:
	void Release(void);

private:
	OBJTYPE m_objType;					// �I�u�W�F�N�g�̎��
	static CScene *m_pTop[OBJTYPE_MAX];	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CScene *m_pCur[OBJTYPE_MAX];	// ���݂̃I�u�W�F�N�g�ւ̃|�C���^
	CScene *m_pPrev;					// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene *m_pNext;					// ���̃I�u�W�F�N�g�ւ̃|�C���^
	int m_nPriority;					// �`�揇
	static int m_nNext;					// ��
	static bool m_bRelease;				// �j��h����
	bool m_bDeath;						// ���S�t���O
	static bool m_bUpdateStop;			// �X�V��~����
};
#endif
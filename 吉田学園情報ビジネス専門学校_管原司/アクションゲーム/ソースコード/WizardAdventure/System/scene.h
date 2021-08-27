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
#define NUM_VERTEX			(4)
#define NUM_POLYGON			(2)
#define MAX_POLYGON			(2048)
#define	FVF_VERTEX_2D		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D		(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define RHW_VALUE			(1.0f)													// rhw�l
//********************************************************************
// �\���̒�`
//*******************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// ���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_2D;

typedef struct {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
}VERTEX_3D;
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
		OBJTYPE_BG,
		OBJTYPE_ENEMY,
		OBJTYPE_PLAYER,
		OBJTYPE_ITEM,
		OBJTYPE_DEFAULT,
		OBJTYPE_BLOCK,
		OBJTYPE_FRAME,
		OBJTYPE_FLOOR,
		OBJTYPE_MAP_OBJ,
		OBJTYPE_BACK_OBJ,
		OBJTYPE_BUTTON,
		OBJTYPE_GATE_ROOF,
		OBJTYPE_PARTICLE,
		OBJTYPE_MAGIC,
		OBJTYPE_ENEMY_MAGIC,
		OBJTYPE_ENEMY_MAP,
		OBJTYPE_GAGE_BACK,
		OBJTYPE_BILLBOARD_UI,
		OBJTYPE_UI,
		OBJTYPE_NOSTOP_UI,
		OBJTYPE_FADE,
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
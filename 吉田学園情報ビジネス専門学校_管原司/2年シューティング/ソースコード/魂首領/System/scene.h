//******************************************************************************
// ���X�g�\�� [scene.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _SCENE_H_
#define _SCENE_H_
//******************************************************************************
// �}�N����`
//******************************************************************************
#define INIT_INT			(0)									// int�^������
#define INIT_FLOAT			(0.0f)								// float�^������
#define INIT_D3DXVECTOR3	(D3DXVECTOR3(0.0f,0.0f,0.0f))		// D3DXVECTOR3������
#define INIT_COLOR			(D3DXCOLOR(0.0f,0.0f,0.0f,0.0f))	// D3DXCOLOR������
#define RHW_VALUE			(1.0f)								// rhw�l
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE| D3DFVF_TEX1)
#define NUM_VERTEX		(4)
#define NUM_POLYGON		(2)
//******************************************************************************
// �\���̐錾
//******************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// ���W�ϊ��p���W��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`��
}VERTEX_2D;
//******************************************************************************
// �N���X
//******************************************************************************
class CScene
{
public:
	// �I�u�W�F�N�g�^�C�v�̗񋓌^
	typedef enum
	{
		OBJTYPE_NONE = -1,
		OBJTYPE_BG,
		OBJTYPE_SHIP,
		OBJTYPE_ENEMY,
		OBJTYPE_DEFAULT,
		OBJTYPE_PLAYER,
		OBJTYPE_PLAYER_BULLET,
		OBJTYPE_PLAYER_WEPON,
		OBJTYPE_ENEMY_BULLET,
		OBJTYPE_BOSS,
		OBJTYPE_BOSS_RIGHT,
		OBJTYPE_BOSS_LEFT,
		OBJTYPE_PARTICLE,
		OBJTYPE_EXPLOSION,
		OBJTYPE_ITEM,
		OBJTYPE_UI,
		OBJTYPE_FADE,
		OBJTYPE_MAX
	}OBJTYPE;

	CScene(int nPriority = OBJTYPE_DEFAULT);
	virtual ~CScene();

	void SetObjType(OBJTYPE objType);
	OBJTYPE GetObjType(void) { return m_objType; }
	static CScene *GetScene(int nPriority);

	// �������z�֐�
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
	static int m_nNext;					// ���̃J�E���g	
	static bool m_bRelease;				// �j�����邩�𔻒f����ϐ�
	bool m_bDeath;						// ���S�t���O
	static bool m_bUpdateStop;			// �X�V��~���邩���f����ϐ�
};
#endif // !_RENDERER_H_
//******************************************************************************
// �u���b�N [block.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _OBJ_H_
#define _OBJ_H_

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "scene.h"
#include "../3D/Model/model.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define MAX_MATERIAL	(50)
//******************************************************************************
// �O���錾
//******************************************************************************
class CModel;
//******************************************************************************
// �v���C���[�N���X
//******************************************************************************
class C3D_Obj :public CScene
{
public:
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_FLOOR_01,
		TYPE_NEEDLE,
		TYPE_WOOD_BLOCK,
		TYPE_STONE_BLOCK,
		TYPE_BUTTON,
		TYPE_GATE,
		TYPE_GATE_ROOF,
		TYPE_TREE,
		TYPE_STONE_0,
		TYPE_STONE_1,
		TYPE_STONE_2,
		TYPE_WOOD,
		TYPE_MAX
	}TYPE;

	C3D_Obj(int nPriority = OBJTYPE_MAP_OBJ);
	~C3D_Obj();

	static HRESULT Load(void);
	static void Unload(void);
	static HRESULT LoadTexture(void);
	static void UnloadTexture(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	//***************************************
	// �Z�b�^�[
	//***************************************
	void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, TYPE type);
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetSize(D3DXVECTOR3 size);

	//***************************************
	// �Q�b�^�[
	//***************************************
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	TYPE GetType(void) { return m_Type; }
private:
	static LPD3DXMESH m_pMesh[TYPE_MAX];									// ���b�V�����̃|�C���^
	static LPD3DXBUFFER m_pBuffMat[TYPE_MAX];								// �}�e���A�����̃|�C���^
	static DWORD m_nNumMat[TYPE_MAX];										// �}�e���A�����̐�
	D3DXMATRIX m_mtxWorld;													// �s��v�Z�p
	static char* m_apFileName[TYPE_MAX];									// �t�@�C���̖��O
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];						// �}�e���A���̍ő吔
	D3DXVECTOR3 m_pos;														// �ʒu
	D3DXVECTOR3 m_rot;														// �p�x
	D3DXVECTOR3 m_size;														// �傫��
	CModel *m_pModel;														// ���f���N���X�̃|�C���^
	TYPE m_Type;															// ���
	bool m_bDraw;															// �`�攻��
};

#endif
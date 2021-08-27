//******************************************************************************
// �G [enemy.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _ENEMY_H_
#define _ENEMY_H_

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
class CEnemy :public CScene
{
public:
	// ���
	enum STATE
	{
		STATE_NORMAL = 0,
		STATE_DEAD,
	};

	CEnemy(int nPriority = OBJTYPE_ENEMY);
	~CEnemy();

	static HRESULT Load(void);
	static void Unload(void);
	static HRESULT LoadTexture(void);
	static void UnloadTexture(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(int nDamage);

	//***************************************
	// �Z�b�^�[
	//***************************************
	void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife);
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetSize(D3DXVECTOR3 size);
	void SetLife(int nLife);

	//***************************************
	// �Q�b�^�[
	//***************************************
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	int GetLife(void) { return m_nLife; }
	STATE GetState(void) { return m_State; }
private:
	static LPD3DXMESH m_pMesh;									// ���b�V�����̃|�C���^
	static LPD3DXBUFFER m_pBuffMat;								// �}�e���A�����̃|�C���^
	static DWORD m_nNumMat;										// �}�e���A�����̐�
	D3DXMATRIX m_mtxWorld;										// �s��v�Z�p
	static char* m_apFileName;									// �t�@�C���̖��O
	static LPDIRECT3DTEXTURE9 m_apTexture;						// �}�e���A���̍ő吔
	D3DXVECTOR3 m_pos;											// �ʒu
	D3DXVECTOR3 m_rot;											// �p�x
	D3DXVECTOR3 m_size;											// �傫��
	CModel *m_pModel;											// ���f���N���X�̃|�C���^
	STATE m_State;												// STATE
	int m_nLife;												// �̗�
	bool m_bDraw;												// �`�攻��
};

#endif
//=============================================================================
//
// 3D�V�[���Ǘ� [scene3d.h]
// Author : ��K������
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CScene3d :public CScene
{
public:
	CScene3d(int nPriority = DEFAULT_PRIORITY);
	virtual ~CScene3d();
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	void SetPosition(D3DXVECTOR3 Position) { m_Position = Position; }
	void SetRotation(D3DXVECTOR3 Rotation) { m_Rotation = Rotation; }
	void SetSize(D3DXVECTOR3 Size) { m_Size = Size; }
	D3DXVECTOR3 GetPosition(void) { return m_Position; }
	D3DXVECTOR3 GetRotation(void) { return m_Rotation; }
	D3DXVECTOR3 GetSize(void) { return m_Size; }
private:
	D3DXVECTOR3 m_Position;	//�ʒu
	D3DXVECTOR3 m_Rotation;	//��]�l
	D3DXVECTOR3 m_Size;		//�T�C�Y
};
#endif
//=============================================================================
//
// 2D�V�[���Ǘ� [scene2d.h]
// Author : ��K������
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

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
class CScene2d :public CScene
{
public:
	CScene2d(int nPriority = DEFAULT_PRIORITY);
	~CScene2d();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 Position) { m_Position = Position; }
	void SetRotation(D3DXVECTOR3 Rotation) { m_Rotation = Rotation; }
	void SetSize(D3DXVECTOR3 Size) { m_Size = Size; }
	void SetScale(float fScale) { m_fScale = fScale; }
	void SetColor(D3DXCOLOR Color) { m_Color = Color; }
	void SetVertexPosition(D3DXVECTOR3 aVertexPosition[NUM_VERTEX]);
	void SetTexture(D3DXVECTOR2 aTexture[NUM_VERTEX]);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }
	D3DXVECTOR3 GetPosition(void) { return m_Position; }
	D3DXVECTOR3 GetRotation(void) { return m_Rotation; }
	D3DXVECTOR3 GetSize(void) { return m_Size; }
	D3DXCOLOR GetColor(void) { return m_Color; }
	float GetScale(void) { return m_fScale; }
private:
	LPDIRECT3DTEXTURE9		m_pTexture;					//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_Position;					//���W
	D3DXVECTOR3				m_Size;						//�T�C�Y
	D3DXVECTOR3				m_Rotation;					//��]
	D3DXVECTOR3				m_aVtxPosition[NUM_VERTEX];	//���_���W
	D3DXVECTOR2				m_aTexture[NUM_VERTEX];		//�e�N�X�`����UV���W
	D3DXCOLOR	 			m_Color;					//�J���[
	float					m_fScale;					//�g�k
	float					m_fAngle;					//�p�x
	float					m_fLength;					//����
};
#endif
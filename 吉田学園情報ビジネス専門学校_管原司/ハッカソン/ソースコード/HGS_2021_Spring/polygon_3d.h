//=============================================================================
//
// 3D�|���S���Ǘ� [polygon3d.h]
// Author : ��K������
//
//=============================================================================
#ifndef _POLYGON3D_H_
#define _POLYGON3D_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene3d.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPolygon3d :public CScene3d
{
public:
	CPolygon3d(int nPriority = DEFAULT_PRIORITY);
	~CPolygon3d();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTexture(D3DXVECTOR2 aTexture[NUM_VERTEX]);
	void SetColor(D3DXCOLOR Color) { m_Color = Color; }
	void SetScale(float fScale) { m_fScale = fScale; }
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }
	D3DXCOLOR GetColor(void) { return m_Color; };
	float GetScale(void) { return m_fScale; };
private:
	D3DXMATRIX m_mtxWorld;							//���[���h�}�g���N�X
	LPDIRECT3DTEXTURE9		m_pTexture;				//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR2				m_aTex[NUM_VERTEX];		//�e�N�X�`����UV���W
	D3DXCOLOR	 			m_Color;				//���_�J���[
	float					m_fScale;				//�k��
	float					m_fAngle;				//�p�x
	float					m_fLength;				//����
};
#endif
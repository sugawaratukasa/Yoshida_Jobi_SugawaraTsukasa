//******************************************************************************
// 2D [scene2d.h]
// Author : �ǌ��i
//******************************************************************************
#ifndef _SCENE2D_H_
#define _SCENE2D_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "scene.h"
//******************************************************************************
// �N���X
//******************************************************************************
class CScene2D :public CScene
{
public:
	CScene2D(int nPriority = OBJTYPE_DEFAULT);
	~CScene2D();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetPosition(D3DXVECTOR3 pos);
	void SetSize(D3DXVECTOR3 size);
	void SetColor(D3DXCOLOR color);
	void SetRotation(D3DXVECTOR3 rot);
	void SetScale(float fScale);
	void SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR color);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXCOLOR GetColor(void) { return m_color; }
	float GetScale(void) { return m_fScale; }
private:
	LPDIRECT3DTEXTURE9		m_pTexture;				// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;					// �|���S���̈ʒu
	D3DXVECTOR3				m_size;					// �T�C�Y
	D3DXVECTOR3				m_rot;					// ����
	D3DXCOLOR				m_color;				// �J���[
	float					m_fAngle;				// �p�x
	float					m_fLength;				// ���a
	float					m_fScale;				// �g�嗦
};

#endif // !_SCENE2D_H_

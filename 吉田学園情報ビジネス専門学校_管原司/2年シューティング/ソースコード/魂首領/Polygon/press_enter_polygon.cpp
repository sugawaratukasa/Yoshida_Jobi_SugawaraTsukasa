//******************************************************************************
// Press_Enter�|���S�� [press_enter_polygon.cpp]
// Author : �ǌ��@�i
//******************************************************************************
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "../System/main.h"
#include "../System/manager.h"
#include "../System/renderer.h"
#include "../System/scene.h"
#include "../System/scene2d.h"
#include "polygon.h"
#include "press_enter_polygon.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define COLOR_RATE	(0.05f)								// a���Z���Z�l
#define COLOR_MIN	(D3DXCOLOR(1.0f,1.0f,1.0f,0.1f))	// �F�̍ŏ��l
#define	COLOR_MAX	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// �F�̍ő�l
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CPress_Enter_Polygon::CPress_Enter_Polygon(int nPriority) : CPolygon(nPriority)
{
	m_bColor = false;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CPress_Enter_Polygon::~CPress_Enter_Polygon()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CPress_Enter_Polygon * CPress_Enter_Polygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TEX_TYPE textype)
{
	//�@CPress_Enter_Polygon�N���X�̃|�C���^
	CPress_Enter_Polygon *pTitle_Polygonn;

	// �������m��
	pTitle_Polygonn = new CPress_Enter_Polygon;

	// ���ݒ�
	pTitle_Polygonn->SetPolygon(pos, size, col, textype);

	// ������
	pTitle_Polygonn->Init();

	// �|�C���^��Ԃ�
	return pTitle_Polygonn;

}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CPress_Enter_Polygon::Init()
{
	//�@������
	CPolygon::Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CPress_Enter_Polygon::Uninit(void)
{
	//�@�I��
	CPolygon::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CPress_Enter_Polygon::Update(void)
{
	//�@�X�V
	CPolygon::Update();

	// �J���[�擾
	D3DXCOLOR col = GetRGBA();

	// false�̏ꍇ
	if (m_bColor == false)
	{
		// ���l���Z
		col.a -= COLOR_RATE;
		// 0.1�ȉ��̏ꍇ
		if (col.a <= COLOR_MIN.a)
		{
			// 0.1f��
			col.a = COLOR_MIN.a;

			// true�ɂ���
			m_bColor = true;
		}
	}
	else
	{
		// ���l���Z
		col.a += COLOR_RATE;
		// 1.0f�ȏ�̏ꍇ
		if (col.a >= COLOR_MAX.a)
		{
			// 1.0f��
			col.a = COLOR_MAX.a;

			// false�ɂ���
			m_bColor = false;
		}
	}
	// �J���[�ݒ�
	SetRGBA(col);
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CPress_Enter_Polygon::Draw(void)
{
	//�@�`��
	CPolygon::Draw();
}
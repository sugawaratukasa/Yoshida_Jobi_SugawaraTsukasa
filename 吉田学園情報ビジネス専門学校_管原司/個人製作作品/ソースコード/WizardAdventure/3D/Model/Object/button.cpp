//******************************************************************************
// �{�^��[button.cpp]
// Author : �ǌ� �i
//******************************************************************************

//******************************************************************************
//�C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "../3D/3DPolygon/scene3d.h"
#include "../3D/Model/model.h"
#include "3d_obj.h"
#include "../3D/Model/player.h"
#include "collision.h"
#include "../3D/Model/Block/block.h"
#include "sound.h"
#include "button.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define MOVE		(D3DXVECTOR3(0.0f,2.0f,0.0f))	// �ړ���
#define SIZE_DEVIDE	(3.0f)							// �T�C�Y������
//******************************************************************************
//�ÓI�����o�ϐ�
//******************************************************************************

//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CButton::CButton(int nPriority) : C3D_Obj(nPriority)
{
	m_SavePos	= INIT_D3DXVECTOR3;
	m_bPush		= false;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CButton::~CButton()
{

}
//******************************************************************************
// �����֐�
//******************************************************************************
CButton * CButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// CButton�̃|�C���^
	CButton *pButton = NULL;

	// NULL�̏ꍇ
	if (pButton == NULL)
	{
		// �������m��
		pButton = new CButton;

		// NULL�łȂ��ꍇ
		if (pButton != NULL)
		{
			// ���ݒ�
			pButton->SetModel(pos, rot, size, C3D_Obj::TYPE_BUTTON);

			// �ʒu�ۑ�
			pButton->m_SavePos = pos;

			// �I�u�W�F�N�g�^�C�v�ݒ�
			pButton->SetObjType(OBJTYPE_BUTTON);

			// ������
			pButton->Init();
		}
	}
	// �|�C���^��Ԃ�
	return pButton;
}
//******************************************************************************
// ����������
//******************************************************************************
HRESULT CButton::Init(void)
{
	// ������
	C3D_Obj::Init();

	return S_OK;
}
//******************************************************************************
// �I������
//******************************************************************************
void CButton::Uninit(void)
{
	// �I��
	C3D_Obj::Uninit();
}
//******************************************************************************
// �X�V����
//******************************************************************************
void CButton::Update(void)
{
	// �X�V
	C3D_Obj::Update();

	// true�̏ꍇ
	if (m_bPush == true) 
	{
		// �ړ�����
		UnderMove();
	}
	// false�̏ꍇ
	if (m_bPush == false)
	{
		// �ړ�����
		UpMove();
	}

	// �����蔻��
	Collision();
}

//******************************************************************************
// �`�揈��
//******************************************************************************
void CButton::Draw(void)
{
	// �`��
	C3D_Obj::Draw();
}
//******************************************************************************
// �����蔻��
//******************************************************************************
void CButton::Collision(void)
{
	// �T�E���h�擾
	CSound *pSound = CManager::GetSound();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// �V�[���̃|�C���^
	CScene *pScene = NULL;

	// �u���b�N�Ƃ̓����蔻��
	do
	{
		// ���X�g�\���̐擪�擾
		pScene = GetScene(OBJTYPE_BLOCK);

		// NULL�łȂ��ꍇ
		if (pScene != NULL)
		{
			// �I�u�W�F�N�g�^�C�v�擾
			OBJTYPE Objtype = pScene->GetObjType();

			// �I�u�W�F�N�g�^�C�v���u���b�N�̏ꍇ
			if (Objtype == OBJTYPE_BLOCK)
			{
				// �ʒu�擾
				D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

				// �T�C�Y�擾
				D3DXVECTOR3 BlockSize = ((CBlock*)pScene)->GetSize();

				// �����蔻��
				if (CCollision::RectangleCollision(pos, size, BlockPos, BlockSize) == true)
				{
					// false�̏ꍇ
					if (m_bPush == false)
					{
						// ���������Đ�
						pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON_PUSH);

						// true��
						m_bPush = true;
					}
				}
				else
				{
					if (m_bPush == true)
					{
						// ���������Đ�
						pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON_PUSH);

						// false��
						m_bPush = false;
					}
				}
			}
		}
		// NULL�ɂȂ�܂�
	} while (pScene != NULL);
}
//******************************************************************************
// ��ړ�����
//******************************************************************************
void CButton::UpMove(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// �{�^���������肫������
	if (pos.y <= m_SavePos.y - size.y / SIZE_DEVIDE)
	{
		// �ړ�
		pos.y += MOVE.y;
	}

	// �ʒu�ݒ�
	SetPos(pos);
}
//******************************************************************************
// ���ړ�����
//******************************************************************************
void CButton::UnderMove(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// �{�^���������肫������
	if (pos.y >= m_SavePos.y - size.y / SIZE_DEVIDE)
	{
		// �ړ�
		pos.y += -MOVE.y;
	}

	// �ʒu�ݒ�
	SetPos(pos);
}
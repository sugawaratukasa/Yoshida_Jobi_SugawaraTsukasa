//******************************************************************************
// �|�[�Y [pause.cpp]
// Author : �ǌ��i
//******************************************************************************
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "joystick.h"
#include "2d_polygon.h"
#include "fade.h"
#include "mode.h"
#include "game.h"
#include "../3D/Model/player.h"
#include "../2D/2D_Particle/2d_particle_emitter.h"
#include "magic_ui.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define POS			(D3DXVECTOR3(100.0f,50.0f,0.0f))	// �ʒu
#define EFFECT_POS	(D3DXVECTOR3(100.0f,60.0f,0.0f))	// �ʒu
#define SIZE		(D3DXVECTOR3(100.0f,100.0f,0.0f))	// �T�C�Y
#define SIZE2		(D3DXVECTOR3(0.0f,0.0f,0.0f))		// �T�C�Y2
#define COL			(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// �F
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CMagic_UI::CMagic_UI(int nPriority) : CScene(nPriority)
{
	m_p2D_Particle_Emitter	= NULL;
	m_nMagicType			= INIT_INT;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CMagic_UI::~CMagic_UI()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CMagic_UI * CMagic_UI::Create(void)
{
	// CMagic_UI�̃|�C���^
	CMagic_UI *pMagic_UI = NULL;

	// NULL�̏ꍇ
	if (pMagic_UI == NULL)
	{
		// �������m��
		pMagic_UI = new CMagic_UI;

		// NULL�łȂ��ꍇ
		if (pMagic_UI != NULL)
		{
			// �I�u�W�F�N�g�^�C�v�ݒ�
			pMagic_UI->SetObjType(OBJTYPE_NOSTOP_UI);

			// ������
			pMagic_UI->Init();
		}
	}
	// �|�C���^��Ԃ�
	return pMagic_UI;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CMagic_UI::Init(void)
{
	// ����
	C2D_Polygon::Create(POS, SIZE, C2D_Polygon::TYPE_MAGIC_UI);

	// ���ˑ̐���
	m_p2D_Particle_Emitter = C2D_Particle_Emitter::Create(EFFECT_POS, C2D_Particle_Emitter::TYPE_FIRE);
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CMagic_UI::Uninit(void)
{
	// �j��
	CScene::Release();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CMagic_UI::Update(void)
{
	// CScene�̃|�C���^
	CScene *pScene = NULL;

	// �v���C���[�擾
	do 
	{
		// �|�C���^�擾
		pScene = GetScene(OBJTYPE_PLAYER);

		// NULL�łȂ��ꍇ
		if (pScene != NULL)
		{
			// �I�u�W�F�N�g�^�C�v�擾
			OBJTYPE objtype = pScene->GetObjType();

			// OBJTYPE_PLAYER�̏ꍇ
			if (objtype == OBJTYPE_PLAYER)
			{
				// �^�C�v�擾
				int nMagicType = ((CPlayer*)pScene)->GetMagicType();

				// ���݂̎�ނƈႤ�ꍇ
				if (m_nMagicType != nMagicType)
				{
					// FIRE_BALL�̏ꍇ
					if (nMagicType == CPlayer::MAGIC_TYPE_FIREBALL)
					{
						// NULL�̏ꍇ
						if (m_p2D_Particle_Emitter != NULL)
						{
							// �j��
							m_p2D_Particle_Emitter->Uninit();

							// NULL��
							m_p2D_Particle_Emitter = NULL;
						}
						// NULL�̏ꍇ
						if (m_p2D_Particle_Emitter == NULL)
						{
							// ����
							m_p2D_Particle_Emitter = C2D_Particle_Emitter::Create(EFFECT_POS, C2D_Particle_Emitter::TYPE_FIRE);
						}
					}
					// ICE_BALL�̏ꍇ
					if (nMagicType == CPlayer::MAGIC_TYPE_ICEBALL)
					{
						// NULL�̏ꍇ
						if (m_p2D_Particle_Emitter != NULL)
						{
							// �j��
							m_p2D_Particle_Emitter->Uninit();

							// NULL��
							m_p2D_Particle_Emitter = NULL;
						}
						// NULL�̏ꍇ
						if (m_p2D_Particle_Emitter == NULL)
						{
							// ����
							m_p2D_Particle_Emitter = C2D_Particle_Emitter::Create(EFFECT_POS, C2D_Particle_Emitter::TYPE_ICE);
						}
					}

					// ���
					m_nMagicType = nMagicType;
				}
			}
		}
		// NULL�ɂȂ�܂ŌJ��Ԃ�
	} while (pScene != NULL);
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CMagic_UI::Draw(void)
{
}
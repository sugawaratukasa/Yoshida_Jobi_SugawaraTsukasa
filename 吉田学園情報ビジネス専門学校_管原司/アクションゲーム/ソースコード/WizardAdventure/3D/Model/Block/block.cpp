//******************************************************************************
// �u���b�N[block.cpp]
// Author : �ǌ� �i
//******************************************************************************

//******************************************************************************
//�C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "joystick.h"
#include "../3D/Model/Block/block.h"
#include "../3D/3DPolygon/frame.h"
#include "collision.h"
#include "../3D/Model/Object/3d_obj.h"
#include "../3D/Model/player.h"
#include "../3D/3DPolygon/Particle/Particle_Emitter/particle_emitter.h"
#include "block.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define POS				(D3DXVECTOR3(pos.x,pos.y,pos.z - 15.0f))			// �ʒu
#define MOVE_VALUE		(D3DXVECTOR3(2.0f,2.0f,0.0f))						// �ړ���
#define FRAME_POS		(D3DXVECTOR3(pos.x,pos.y,pos.z - 15.0f))			// �g�̃T�C�Y
#define FRAME_SIZE		(D3DXVECTOR3(GetSize().x,GetSize().y,0.0f))			// �g�̃T�C�Y
#define FRAME_COLOR1	(D3DXCOLOR(1.0f,1.0f,1.0f,0.0f))					// �g�̐F
#define FRAME_COLOR2	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))					// �g�̐F
#define FRAME_COLOR3	(D3DXCOLOR(0.0f,0.8f,1.0f,1.0f))					// �g�̐F
#define FRAME_ROT1		(D3DXVECTOR3(0.0f,D3DXToRadian(180.0f),0.0f))		// �g�̌���
#define MIN_MOVE_VALUE	(0)													// �ړ��ʂ̍ŏ��l
#define DEVIDE_VALUE	(2.0f)												// ���鐔
#define GRAVITY_VALUE	(-0.3f)												// �d��
#define CREATE_MOVE_POS	(PlayerPos.y + 80.0f)								// �u���b�N�̐������ʒu
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CBlock::CBlock(int nPriority) :C3D_Obj(nPriority)
{
	m_posOld			= INIT_D3DXVECTOR3;
	m_move				= INIT_D3DXVECTOR3;
	m_pBlock			= NULL;
	m_pFrame			= NULL;
	m_pParticleEmitter	= NULL;
	m_bMove				= false;
	m_bParticleEmitter	= false;
}

//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CBlock::~CBlock()
{

}

//******************************************************************************
// ����������
//******************************************************************************
HRESULT CBlock::Init(void)
{
	// ������
	C3D_Obj::Init();

	// �g�𐶐�
	SetFrame();

	return S_OK;
}

//******************************************************************************
// �I������
//******************************************************************************
void CBlock::Uninit(void)
{
	// �I��
	C3D_Obj::Uninit();
}

//******************************************************************************
// �X�V����
//******************************************************************************
void CBlock::Update(void)
{
	// 1�t���[���O�̈ʒu�擾
	D3DXVECTOR3 posOld = GetPos();

	// �X�V
	C3D_Obj::Update();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// CScene�̃|�C���^
	CScene *pScene = NULL;

	// ��Ԃ̕ϐ�
	int nPlayerState;

	// true�̏ꍇ
	if (m_bParticleEmitter == true)
	{
		// NULL�̏ꍇ
		if (m_pParticleEmitter == NULL)
		{
			m_pParticleEmitter = CParticle_Emitter::Create(POS, CParticle_Emitter::TYPE_STAR);
		}
		// NULL�łȂ��ꍇ
		if (m_pParticleEmitter != NULL)
		{
			// �ʒu
			m_pParticleEmitter->SetPos(POS);
		}
	}
	// false�̏ꍇ
	if (m_bParticleEmitter == false)
	{
		// NULL�łȂ��ꍇ
		if (m_pParticleEmitter != NULL)
		{
			// �I��
			m_pParticleEmitter->Uninit();

			// NULL��
			m_pParticleEmitter = NULL;
		}
	}
	// �v���C���[�̏�Ԏ擾
	do
	{
		// �v���C���[�擾
		pScene = GetScene(OBJTYPE_PLAYER);

		// NULL�łȂ��ꍇ
		if (pScene != NULL)
		{
			// �I�u�W�F�N�g�^�C�v�擾
			OBJTYPE objtype = pScene->GetObjType();

			// �I�u�W�F�^�C�v���v���C���[�̏ꍇ
			if (objtype == OBJTYPE_PLAYER)
			{
				// �u���b�N�̎g�p��Ԏ擾
				nPlayerState = ((CPlayer*)pScene)->GetBlockActive();

				// �u���b�N�������̏ꍇ
				if (nPlayerState == CPlayer::BLOCK_ACTIVE_CREATE)
				{
					// true�̏ꍇ
					m_bMove = true;
				}
			}
		}
	} while (pScene != NULL);

	// false�̏ꍇ
	if (m_bMove == false)
	{
		// �d��
		m_move.y += GRAVITY_VALUE;

		// �ʒu�X�V
		pos.y += m_move.y;

		// �ʒu�ݒ�
		SetPos(pos);
	}

	// �����蔻��
	Collision(posOld, size);
}

//******************************************************************************
// �`�揈��
//******************************************************************************
void CBlock::Draw(void)
{
	// �`��
	C3D_Obj::Draw();
}
//******************************************************************************
// �ړ������֐�
//******************************************************************************
void CBlock::Move(void)
{
	// false�̏ꍇ
	if (m_bParticleEmitter == false)
	{
		// true��
		m_bParticleEmitter = true;
	}
	// �R���g���[���[�擾
	DIJOYSTATE js;
	js.lZ = NULL;
	js.lRz = NULL;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	// �ʒu
	D3DXVECTOR3 pos = GetPos();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	if (g_lpDIDevice != NULL)
	{
		// �X�e�B�b�N�͈̔͊O�̏ꍇ
		if (js.lZ > -STICK_REACTION && js.lZ < STICK_REACTION)
		{
			// �ړ���0
			m_move.y = MIN_MOVE_VALUE;
		}
		if (js.lRz > -STICK_REACTION && js.lRz < STICK_REACTION)
		{
			// �ړ���0
			m_move.x = MIN_MOVE_VALUE;
		}
		// �E�X�e�B�b�N�����ɓ|��
		if (js.lZ <= -STICK_REACTION)
		{
			m_move.x = -MOVE_VALUE.x;
		}
		// �E�X�e�B�b�N���E�ɓ|��
		if (js.lZ >= STICK_REACTION)
		{
			m_move.x = MOVE_VALUE.x;
		}
		// �E�X�e�B�b�N����ɓ|��
		if (js.lRz <= -STICK_REACTION)
		{
			m_move.y = MOVE_VALUE.y;
		}
		// �E�X�e�B�b�N�����ɓ|��
		if (js.lRz >= STICK_REACTION)
		{
			m_move.y = -MOVE_VALUE.y;
		}
	}

	// �ړ�
	pos.x += m_move.x;
	pos.y += m_move.y;

	// �ʒu�ݒ�
	SetPos(pos);
}
//******************************************************************************
// �������ɓ�����
//******************************************************************************
void CBlock::Create_Move(void)
{
	DIJOYSTATE js;
	js.lX = NULL;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	// �ʒu
	D3DXVECTOR3 pos = GetPos();

	// CScene�̃|�C���^
	CScene *pScene = NULL;

	// �v���C���[�̈ʒu
	D3DXVECTOR3 PlayerPos;

	// �v���C���[�̈ʒu�擾
	do
	{
		// �v���C���[�擾
		pScene = GetScene(OBJTYPE_PLAYER);

		// NULL�łȂ��ꍇ
		if (pScene != NULL)
		{
			// �I�u�W�F�N�g�^�C�v�擾
			OBJTYPE objtype = pScene->GetObjType();

			// �I�u�W�F�^�C�v���v���C���[�̏ꍇ
			if (objtype == OBJTYPE_PLAYER)
			{
				// // �v���C���[�̈ʒu�擾
				PlayerPos = ((CPlayer*)pScene)->GetPos();

			}
		}
	} while (pScene != NULL);

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	if (g_lpDIDevice != NULL)
	{
		if (js.lX > -STICK_REACTION && js.lRz < STICK_REACTION)
		{
			// �ړ���0
			m_move.x = MIN_MOVE_VALUE;
		}
		// �E�X�e�B�b�N�����ɂ�����
		if (js.lX <= -STICK_REACTION)
		{
			// �ړ���
			m_move.x = -MOVE_VALUE.x;
		}
		// �E�X�e�B�b�N���E�ɂ�����
		if (js.lX >= STICK_REACTION)
		{
			// �ړ���
			m_move.x = MOVE_VALUE.x ;
		}
	}

	// �ړ�
	pos.x += m_move.x;
	pos.y += m_move.y;

	// y���W���
	pos.y = CREATE_MOVE_POS;

	// �ʒu�ݒ�
	SetPos(pos);
}
//******************************************************************************
// �j���֐�
//******************************************************************************
void CBlock::ReleaseBlock(void)
{
	// �I��
	m_pFrame->Uninit();

	// �j��
	Uninit();

	return;
}
//******************************************************************************
// �t���[������
//******************************************************************************
void CBlock::SetFrame(void)
{
	// �ʒu
	D3DXVECTOR3 pos	= GetPos();

	// �t���[������
	m_pFrame = CFrame::Create(FRAME_POS, FRAME_ROT1, FRAME_SIZE, FRAME_COLOR1, m_pBlock);
}
//******************************************************************************
// �I������Ă���ꍇ
//******************************************************************************
void CBlock::Selecting(void)
{
	m_pFrame->SetSelectingColor(FRAME_COLOR3);
}
//******************************************************************************
// ���I���̏ꍇ
//******************************************************************************
void CBlock::UnSelected(void)
{
	m_pFrame->SetSelectingColor(FRAME_COLOR1);
}
//******************************************************************************
// �v���C���[���I�𒆂̏ꍇ
//******************************************************************************
void CBlock::PlayerSelection(void)
{
	m_pFrame->SetSelectingColor(FRAME_COLOR2);
}
//******************************************************************************
// ���ݒ�
//******************************************************************************
void CBlock::SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, TYPE type, CBlock *pBlock)
{
	// ���f���ݒ�
	SetModel(pos, rot, size, type);

	// ���
	m_pBlock = pBlock;

	// �I�u�W�F�^�C�v���u���b�N�ɐݒ�
	SetObjType(OBJTYPE_BLOCK);
}
//******************************************************************************
// �ړ�����ݒ�
//******************************************************************************
void CBlock::SetbMove(bool bMove)
{
	// ���
	m_bMove = bMove;
}
//******************************************************************************
// �G�t�F�N�g����ݒ�
//******************************************************************************
void CBlock::SetbEmitter(bool bEmitter)
{
	m_bParticleEmitter = bEmitter;
}
//******************************************************************************
// �����蔻��
//******************************************************************************
void CBlock::Collision(D3DXVECTOR3 posOld, D3DXVECTOR3 size)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// �u���b�N�Ƃ̓����蔻��
	CScene *pScene = NULL;

	// �u���b�N�Ƃ̓����蔻��
	do
	{
		// �I�u�W�F�^�C�v���u���b�N�̏ꍇ
		pScene = GetScene(OBJTYPE_BLOCK);

		// NULL�`�F�b�N
		if (pScene != NULL)
		{
			// �I�u�W�F�^�C�v�擾
			OBJTYPE objType = pScene->GetObjType();

			// �I�u�W�F�N�g�^�C�v���G
			if (objType == OBJTYPE_BLOCK)
			{
				// ���W�ƃT�C�Y�擾
				D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();
				D3DXVECTOR3 BlockSize = ((CBlock*)pScene)->GetSize();

				// �ǂ��̖ʂɓ���������
				//��
				if (CCollision::RectangleCollisionMove(pos, posOld, size, BlockPos, BlockSize) == CCollision::SURFACE_DOWN)
				{
					// �ړ���0
					m_move.y = MIN_MOVE_VALUE;

					// �ʒu
					pos.y = (-BlockSize.y / DEVIDE_VALUE + BlockPos.y) - (size.y / DEVIDE_VALUE);
				}
				// ��
				else if (CCollision::RectangleCollisionMove(pos, posOld, size, BlockPos, BlockSize) == CCollision::SURFACE_UP)
				{
					// �ړ���0
					m_move.y = MIN_MOVE_VALUE;

					// �ʒu
					pos.y = (BlockSize.y / DEVIDE_VALUE + BlockPos.y) + (size.y / DEVIDE_VALUE);
				}
				// ��
				else if (CCollision::RectangleCollisionMove(pos, posOld, size, BlockPos, BlockSize) == CCollision::SURFACE_LEFT)
				{
					// �ړ���0
					m_move.x = MIN_MOVE_VALUE;

					// �ʒu
					pos.x = (-BlockSize.x / DEVIDE_VALUE + BlockPos.x) - (size.x / DEVIDE_VALUE);
				}
				// �E
				else if (CCollision::RectangleCollisionMove(pos, posOld, size, BlockPos, BlockSize) == CCollision::SURFACE_RIGHT)
				{
					// �ړ���0
					m_move.x = MIN_MOVE_VALUE;

					// �ʒu
					pos.x = (BlockSize.x / DEVIDE_VALUE + BlockPos.x) + (size.x / DEVIDE_VALUE);
				}
			}
		}
	} while (pScene != NULL);

	// �}�b�v�I�u�W�F�N�g�̓����蔻��
	do
	{
		// �I�u�W�F�^�C�v���u���b�N�̏ꍇ
		pScene = GetScene(OBJTYPE_MAP_OBJ);

		// NULL�`�F�b�N
		if (pScene != NULL)
		{
			// �I�u�W�F�^�C�v�擾
			OBJTYPE objType = pScene->GetObjType();

			// �I�u�W�F�N�g�^�C�v���G
			if (objType == OBJTYPE_MAP_OBJ)
			{
				// ���W�ƃT�C�Y�擾
				D3DXVECTOR3 ObjPos = ((C3D_Obj*)pScene)->GetPos();
				D3DXVECTOR3 ObjSize = ((C3D_Obj*)pScene)->GetSize();

				// �ǂ��̖ʂɓ���������
				//��
				if (CCollision::RectangleCollisionMove(pos, posOld, size, ObjPos, ObjSize) == CCollision::SURFACE_DOWN)
				{
					// �ړ���0
					m_move.y = MIN_MOVE_VALUE;
					
					// �ʒu
					pos.y = (-ObjSize.y / DEVIDE_VALUE + ObjPos.y) - (size.y / DEVIDE_VALUE);
				}
				// ��
				else if (CCollision::RectangleCollisionMove(pos, posOld, size, ObjPos, ObjSize) == CCollision::SURFACE_UP)
				{
					// �ړ���0
					m_move.y = MIN_MOVE_VALUE;

					// �ʒu
					pos.y = (ObjSize.y / DEVIDE_VALUE + ObjPos.y) + (size.y / DEVIDE_VALUE);
				}
				// ��
				else if (CCollision::RectangleCollisionMove(pos, posOld, size, ObjPos, ObjSize) == CCollision::SURFACE_LEFT)
				{
					// �ړ���0
					m_move.x = MIN_MOVE_VALUE;

					// �ʒu
					pos.x = (-ObjSize.x / DEVIDE_VALUE + ObjPos.x) - (size.x / DEVIDE_VALUE);
				}
				// �E
				else if (CCollision::RectangleCollisionMove(pos, posOld, size, ObjPos, ObjSize) == CCollision::SURFACE_RIGHT)
				{
					// �ړ���0
					m_move.x = MIN_MOVE_VALUE;

					// �ʒu
					pos.x = (ObjSize.x / DEVIDE_VALUE + ObjPos.x) + (size.x / DEVIDE_VALUE);
				}
			}
		}
	} while (pScene != NULL);

	// �ʒu�ݒ�
	SetPos(pos);
}
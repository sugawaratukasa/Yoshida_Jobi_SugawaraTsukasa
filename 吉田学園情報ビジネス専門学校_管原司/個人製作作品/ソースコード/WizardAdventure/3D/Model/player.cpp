//******************************************************************************
// �v���C���[�̏��� [player.h]
// Author : �ǌ��@�i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "manager.h"
#include "renderer.h"
#include "motion.h"
#include "model.h"
#include "joystick.h"
#include "../3D/Model/Block/block.h"
#include "../3D/Model/Block/stone_block.h"
#include "../3D/3DPolygon/frame.h"
#include "collision.h"
#include "../3D/Model/Object/3d_obj.h"
#include "game.h"
#include "camera.h"
#include "../3D/3DPolygon/Particle/magic.h"
#include "../3D/3DPolygon/Particle/Particle_Emitter/particle_emitter.h"
#include "../2D/Gage/life_gage.h"
#include "../3D/Model/Block/floor_block.h"
#include "../3D/Model/Enemy/enemy_map.h"
#include "map.h"
#include "../3D/3DPolygon/Particle/Particle_Effect/particle_effect.h"
#include "magic_ui.h"
#include "sound.h"
#include "fade.h"
#include "player.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define UNDER_BODY				("data/MODEL/PLAYER/00_UnderBody.x")						// �����g
#define BODY					("data/MODEL/PLAYER/01_Body.x")								// �㔼�g
#define HEAD					("data/MODEL/PLAYER/02_Head.x")								// ��
#define SHOULDER_R				("data/MODEL/PLAYER/03_shoulder_R.x")						// �E��
#define UP_ARM_R				("data/MODEL/PLAYER/04_up_arm_R.x")							// �E��r
#define DOWN_ARM_R				("data/MODEL/PLAYER/05_down_arm_R.x")						// �E�O�r	
#define SHOULDER_L				("data/MODEL/PLAYER/06_shoulder_L.x")						// ����
#define UP_ARM_L				("data/MODEL/PLAYER/07_up_arm_L.x")							// ����r
#define DOWN_ARM_L				("data/MODEL/PLAYER/08_down_arm_L.x")						// ���O�r
#define THIGTS_R				("data/MODEL/PLAYER/09_Thigts_R.x")							// �E������
#define KNEE_R					("data/MODEL/PLAYER/10_Knee_R.x")							// �E�G
#define FOOT_R					("data/MODEL/PLAYER/11_foot_R.x")							// �E��
#define THIGTS_L				("data/MODEL/PLAYER/12_Thigts_L.x")							// ��������
#define KNEE_L					("data/MODEL/PLAYER/13_Knee_L.x")							// ���G
#define FOOT_L					("data/MODEL/PLAYER/14_foot_L.x")							// ����
#define MOTION_PLAYER_TEXT		("data/MODEL/PLAYER/Motion/motion.txt")						// ���[�V�����̃e�L�X�g
#define LOAD_PLAYER_TEXT		("data/MODEL/PLAYER/Motion/player.txt")						// �e���f���p�[�c�̏����l
#define BLOCK_CREATE_RIGHTPOS	(D3DXVECTOR3(m_pos.x + 20.0f,m_pos.y + 80,m_pos.z))			// �������ʒu
#define BLOCK_CREATE_LEFTPOS	(D3DXVECTOR3(m_pos.x - 20.0f,m_pos.y + 80,m_pos.z))			// �������ʒu
#define EFFECT_RIGHTPOS			(D3DXVECTOR3(m_pos.x + 20.0f,m_pos.y + 80,m_pos.z - 15.0f))	// �������ʒu
#define EFFECT_LEFTPOS			(D3DXVECTOR3(m_pos.x - 20.0f,m_pos.y + 80,m_pos.z - 15.0f))	// �������ʒu
#define RELAESE_POS				(D3DXVECTOR3(BlockPos.x,BlockPos.y,BlockPos.z - 15.0f))		// �j������u���b�N�̈ʒu
#define DEAD_POS				(D3DXVECTOR3(ObjPos.x,ObjPos.y + 15.0f,ObjPos.z - 15.0f))	// �G�t�F�N�g�ʒu
#define RESPOWN_POS				(D3DXVECTOR3(m_pos.x,m_pos.y + 30.0f,m_pos.z - 15.0f))		// �G�t�F�N�g�ʒu
#define BLOCK_ROT				(D3DXVECTOR3(0.0f,0.0f,0.0f))								// ���̌���
#define BLOCK_SIZE				(D3DXVECTOR3(30.0f,30.0f,30.0f))							// ���̃T�C�Y
#define MOVE_VALUE				(D3DXVECTOR3(2.0f,2.0f,2.0f))								// �ړ���
#define RIGHT_ROT				(D3DXVECTOR3(0.0f,D3DXToRadian(270.0f),0.0f))				// ����
#define LEFT_ROT				(D3DXVECTOR3(0.0f,D3DXToRadian(90.0f),0.0f))				// ����
#define GAGE_POS				(D3DXVECTOR3(400.0f,50.0f,0.0f))							// �Q�[�W�̈ʒu
#define MIN_BLOCK_NUM			(0)															// �u���b�N�̍ŏ���
#define ARRAY_FIRST_NUM			(0)															// �z��̐擪
#define ARRAY_MOVE_NUMBER		(1)															// �z��̈ړ�
#define ARRAY_SUB_VALUE			(1)															// �z��ɍ��킹�邽�߂̒l
#define DEVIDE_VALUE			(2.0f)														// ���鐔
#define MOVE_DEVIDE				(1.5f)														// �ړ��̊��鐔
#define PARENT_NUMBER			(-1)														// �e�̐��l
#define ROT_MOVE				(0.2f)														// �����̈ړ�
#define POW_VALUE				(2.0f)														// ���
#define MIN_MOVE_VALUE			(0.0f)														// �ړ��ʂ̍ŏ��l
#define GRAVITY_VALUE			(-1.3f)														// �d��
#define JUMP_VALUE				(17.0f)														// �W�����v��
#define JUMP_VALUE_2			(0.01f)														// �W�����v��
#define DEAD_ZONE_MIN			(0)															// �X�e�B�b�N�̃f�b�h�]�[���ŏ��l
#define MAGIC_MOTION_COUNT		(30)														// ���@�̃��[�V�����J�E���g
#define MAX_LIFE				(100)														// ���C�t�̍ő�l
#define MIN_LIFE				(0)															// ���C�t�̍ŏ��l
// ���@�̈ʒu
#define MAGIC_POS				(D3DXVECTOR3(m_pModel[PARTS_DOWN_ARM_L]->GetMtxWorld()._41,m_pModel[PARTS_DOWN_ARM_L]->GetMtxWorld()._42,m_pModel[PARTS_DOWN_ARM_L]->GetMtxWorld()._43))
#define MAGIC_MOVE_RIGHT		(D3DXVECTOR3(2.5f,0.0f,0.0f))						// ���@�̈ړ���
#define MAGIC_MOVE_LEFT			(D3DXVECTOR3(-2.5f,0.0f,0.0f))						// ���@�̈ړ���
// �p�[�e�B�N���G�~�b�^�[�ʒu
#define EMITTER_POS_RIGHT		(D3DXVECTOR3(m_pModel[PARTS_DOWN_ARM_R]->GetMtxWorld()._41,m_pModel[PARTS_DOWN_ARM_R]->GetMtxWorld()._42,m_pModel[PARTS_DOWN_ARM_R]->GetMtxWorld()._43))
#define EMITTER_POS_LEFT		(D3DXVECTOR3(m_pModel[PARTS_DOWN_ARM_R]->GetMtxWorld()._41,m_pModel[PARTS_DOWN_ARM_R]->GetMtxWorld()._42,m_pModel[PARTS_DOWN_ARM_R]->GetMtxWorld()._43))
// ���̈ʒu
#define POS						(D3DXVECTOR3(m_pModel[PARTS_UNDER_BODY]->GetMtxWorld()._41,m_pModel[PARTS_UNDER_BODY]->GetMtxWorld()._42,m_pModel[PARTS_UNDER_BODY]->GetMtxWorld()._43))
#define MAGIC_UI_POS			(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z - 20.0f))	// ���@UI�̈ʒu
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPD3DXMESH CPlayer::m_pMesh[PARTS_MAX] = {};
LPD3DXBUFFER CPlayer::m_pBuffMat[PARTS_MAX] = {};
DWORD CPlayer::m_nNumMat[PARTS_MAX] = {};
D3DXMATRIX CPlayer::m_mtxWorld[PARTS_MAX] = {};
int CPlayer::m_nldxModelParent[PARTS_MAX] = {};
char* CPlayer::m_apFileName[PARTS_MAX] = {
	UNDER_BODY,
	BODY,
	HEAD,
	SHOULDER_R,
	UP_ARM_R,
	DOWN_ARM_R,
	SHOULDER_L,
	UP_ARM_L,
	DOWN_ARM_L,
	THIGTS_R,
	KNEE_R,
	FOOT_R,
	THIGTS_L,
	KNEE_L,
	FOOT_L,
};
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CPlayer::CPlayer(int nPriority) : CScene(nPriority)
{
	m_pos					= INIT_D3DXVECTOR3;		
	m_posOld				= INIT_D3DXVECTOR3;
	m_RespawnPos			= INIT_D3DXVECTOR3;
	m_rot					= INIT_D3DXVECTOR3;		
	m_size					= INIT_D3DXVECTOR3;		
	m_move					= INIT_D3DXVECTOR3;		
	m_bAllMotion			= false;				
	m_pMotion				= NULL;					
	m_pBlock				= NULL;	
	m_pStoneBlock			= NULL;
	m_Blcok_Active			= BLOCK_ACTIVE_NONE;	
	m_nBlockNum				= INIT_INT;				
	m_nBlock_Select_Num		= INIT_INT;	
	m_nMotion_Count			= INIT_INT;
	m_nLife					= INIT_INT;
	m_bStick				= false;				
	m_Rot_State				= ROT_STATE_RIGHT;	
	m_MagicType				= MAGIC_TYPE_FIREBALL;
	m_Emitter_Type			= EMITTER_TYPE_NONE;
	m_bJump					= false;				
	m_bJumpValue			= false;
	m_bBlock_Move			= false;
	m_bMagic				= false;
	m_bParticle_Emitter		= false;
	m_bCollision			= false;
	m_bChange_MagicType		= false;
	m_bEnemyCreate			= false;
	m_bDash					= false;
	m_bEnd					= false;
	memset(m_pModel, NULL, sizeof(m_pModel));
	memset(m_apParticle_Emitter, NULL, sizeof(m_apParticle_Emitter));
}

//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CPlayer::~CPlayer()
{

}

//******************************************************************************
// �����֐�
//******************************************************************************
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// CPlayer�̃|�C���^
	CPlayer *pPlayer = NULL;

	// NULL�̏ꍇ
	if (pPlayer == NULL)
	{
		// �������m��
		pPlayer = new CPlayer;

		// NULL�łȂ��ꍇ
		if (pPlayer != NULL)
		{
			// ���ݒ�
			pPlayer->SetPlayer(pos, rot, size);

			// ������
			pPlayer->Init();

			// ���C�t�Q�[�W����
			CLife_Gage::Create(GAGE_POS, pPlayer);
		}
	}
	// �|�C���^��Ԃ�
	return pPlayer;
}

//******************************************************************************
// �ǂݍ��݊֐�
//******************************************************************************
HRESULT CPlayer::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �p�[�c�����J��Ԃ�
	for (int nCount = INIT_INT; nCount < PARTS_MAX; nCount++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(m_apFileName[nCount],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat[nCount],
			NULL,
			&m_nNumMat[nCount],
			&m_pMesh[nCount]
		);
	}
	
	return S_OK;
}

//******************************************************************************
// �ǂݍ��ݔj���֐�
//******************************************************************************
void CPlayer::Unload(void)
{
	for (int nCount = INIT_INT; nCount < PARTS_MAX; nCount++)
	{
		// ���b�V���̔j��
		if (m_pMesh[nCount] != NULL)
		{
			m_pMesh[nCount]->Release();
			m_pMesh[nCount] = NULL;
		}

		// �}�e���A���̔j��
		if (m_pBuffMat[nCount] != NULL)
		{
			m_pBuffMat[nCount]->Release();
			m_pBuffMat[nCount] = NULL;
		}

		if (m_nNumMat[nCount] != NULL)
		{
			m_nNumMat[nCount] = NULL;
		}
	}
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CPlayer::Init(void)
{
	// Magic_UI����
	CMagic_UI::Create();

	// ���C�t���
	m_nLife = MAX_LIFE;

	// ���[�V�����̐���
	m_pMotion = CMotion::Create();

	// ���[�V�����̓ǂݍ���
	m_pMotion->Load(LOAD_PLAYER_TEXT);
	m_pMotion->LoadMotion(MOTION_PLAYER_TEXT);

	// ���[�V�����̏����ݒ�
	m_pMotion->SetMotion(CMotion::MOTION_IDLE);

	// �p�[�c�����J��Ԃ�
	for (int nCount = INIT_INT; nCount < PARTS_MAX; nCount++)
	{
		// ���f���̐���
		m_pModel[nCount] = CModel::Create();

		// �y�A�����g�̎󂯎��
		m_nldxModelParent[nCount] = m_pMotion->GetParents(nCount);

		// ���f���̃o�C���h
		m_pModel[nCount]->BindModel(m_pMesh[nCount], m_pBuffMat[nCount], m_nNumMat[nCount], m_nldxModelParent[nCount]);

		// ���f���̃p�[�c���Ƃ̍��W�Ɖ�]���󂯎��
		m_pModel[nCount]->SetModel(m_pMotion->GetPos(nCount), m_pMotion->GetRot(nCount) + m_pModel[nCount]->GetRot(), m_size);
	}

	// ���W�A��]�A�T�C�Y�̃Z�b�g
	m_pModel[PARTS_UNDER_BODY]->SetModel(m_pMotion->GetPos(PARTS_UNDER_BODY) + m_pos, m_pMotion->GetRot(PARTS_UNDER_BODY) + m_rot, m_size);

	return S_OK;
}

//******************************************************************************
// �I���֐�
//******************************************************************************
void CPlayer::Uninit(void)
{
	// �p�[�c�����J��Ԃ�
	for (int nCount = INIT_INT; nCount < PARTS_MAX; nCount++)
	{
		if (m_pModel[nCount] != NULL)
		{
			// ���f���N���X�̏I������
			m_pModel[nCount]->Uninit();
			m_pModel[nCount] = NULL;
		}
	}
	// NULL�`�F�b�N
	if (m_pMotion != NULL)
	{
		// ���[�V�����N���X�̏I������
		m_pMotion->Uninit();
		m_pMotion = NULL;
	}

	// �����[�X
	Release();
}

//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CPlayer::Update(void)
{
	//�T�E���h�擾
	CSound * pSound = CManager::GetSound();

	// �ʒu���
	m_posOld = m_pModel[PARTS_UNDER_BODY]->GetPos();

	// �R���g���[���[�擾
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
	}

	// ���[�V�����̍X�V����
	m_pMotion->UpdateMotion();

	// �E�����̏ꍇ
	if (m_Rot_State == ROT_STATE_RIGHT)
	{
		// �u���b�N�ŉ������Ă��Ȃ����
		if (m_Blcok_Active == BLOCK_ACTIVE_NONE)
		{
			// �E�����̎��u���b�N���ł��߂��u���b�N��I�𒆂ɂ��鏈��
			RightSelectBlock();
		}
		// NULL�łȂ��ꍇ
		if (m_pBlock != NULL)
		{
			// false�̏ꍇ
			if (m_bMagic == false)
			{
				// LT���������ꍇ
				if (g_lpDIDevice != NULL && pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_LT))
				{
					// 0��
					m_nBlock_Select_Num = MIN_BLOCK_NUM;

					// �I�𒆂̏�Ԃ�
					m_Blcok_Active = BLOCK_ACTIVE_SELECT;
				}
				// �I�𒆂̏�Ԃ̏ꍇ
				if (m_Blcok_Active == BLOCK_ACTIVE_SELECT)
				{
					// ���̑I������
					RightSelectionBlock();
				}

				// ���̏���
				RightBlock();
			}
		}
	}
	// �������̏ꍇ
	if (m_Rot_State == ROT_STATE_LEFT)
	{
		// �u���b�N�ŉ������Ă��Ȃ����
		if (m_Blcok_Active == BLOCK_ACTIVE_NONE)
		{
			// �������̎��u���b�N���ł��߂��u���b�N��I�𒆂ɂ��鏈��
			LeftSelectBlock();
		}
		// NULL�łȂ��ꍇ
		if (m_pBlock != NULL)
		{
			// false�̏ꍇ
			if (m_bMagic == false)
			{
				// LT���������ꍇ
				if (g_lpDIDevice != NULL && pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_LT))
				{
					// 0��
					m_nBlock_Select_Num = MIN_BLOCK_NUM;

					// �I�𒆂̏�Ԃ�
					m_Blcok_Active = BLOCK_ACTIVE_SELECT;
				}
				// �I�𒆂̏�Ԃ̏ꍇ
				if (m_Blcok_Active == BLOCK_ACTIVE_SELECT)
				{
					// ���̑I������
					LeftSelectionBlock();
				}

				// ���̏���
				LeftBlock();
			}
		}
	}
	// X�{�^���������ꂽ�ꍇ
	if (g_lpDIDevice != NULL && pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_X))
	{
		// �������Đ�
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BLOCK_CREATE);
		// �u���b�N����
		Block_Create();
	}
	// �u���b�N�I�𒆂łȂ��ꍇ
	if (m_Blcok_Active != BLOCK_ACTIVE_SELECT)
	{
		// ���@
		Magic();
	}

	// �ړ�����
	Move();

	// �p�[�c������
	for (int nCount = INIT_INT; nCount < PARTS_MAX; nCount++)
	{
		// ���f���̃p�[�c���Ƃ̍��W�Ɖ�]���󂯎��
		m_pModel[nCount]->SetModel(m_pMotion->GetPos(nCount), m_pMotion->GetRot(nCount), m_size);
	}

	// ���W�A��]�A�T�C�Y�̃Z�b�g
	m_pModel[PARTS_UNDER_BODY]->SetModel(m_pMotion->GetPos(PARTS_UNDER_BODY) + m_pos, m_pMotion->GetRot(PARTS_UNDER_BODY) + m_rot, m_size);

	// �����蔻��
	Collision();
}

//******************************************************************************
// �`��֐�
//******************************************************************************
void CPlayer::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;

	// �p�[�c�����J��Ԃ�
	for (int nCount = INIT_INT; nCount < PARTS_MAX; nCount++)
	{
		//���[���h�}�g���N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld[nCount]);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld[nCount], &m_mtxWorld[nCount], &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld[nCount], &m_mtxWorld[nCount], &mtxTrans);

		// �e�̃��f���p�[�c�ȊO�̃y�A�����g���Z�b�g
		if (m_nldxModelParent[nCount] != PARENT_NUMBER)
		{
			m_pModel[nCount]->SetParent(m_pModel[m_nldxModelParent[nCount]]);
		}

		// ���f���N���X�̕`�揈��
		m_pModel[nCount]->Draw();
	}
}
//******************************************************************************
// �q�b�g
//******************************************************************************
void CPlayer::Hit(int nLife)
{
	// ���C�t���Z
	m_nLife -= nLife;

	// 0�ȉ��ɂȂ����ꍇ
	if (m_nLife <= MIN_LIFE)
	{
		//�T�E���h�擾
		CSound * pSound = CManager::GetSound();

		// �̗͂��ŏ��l��
		m_nLife = MIN_LIFE;

		// ���X�|�[�����Đ�
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE_RESPAWN);

		// ���X�|�[���ʒu��
		m_pos = m_RespawnPos;

		// �G�t�F�N�g����
		CParticle_Effect::Create(RESPOWN_POS, CParticle_Effect::TYPE_STAR_EFFECT2);
	}
}
//******************************************************************************
// ���ݒ�
//******************************************************************************
void CPlayer::SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot ,D3DXVECTOR3 size)
{
	m_pos			= pos;
	m_RespawnPos	= pos;
	m_rot			= rot;
	m_size			= size;

	// �I�u�W�F�N�g�^�C�v�ݒ�
	SetObjType(OBJTYPE_PLAYER);
}
//******************************************************************************
// �p�[�c�̈ʒu�擾
//******************************************************************************
D3DXMATRIX CPlayer::GetMtxWorld(PLAYER_PARTS Parts)
{
	return m_pModel[Parts]->GetMtxWorld();
}
//******************************************************************************
// ���̑I��
//******************************************************************************
void CPlayer::RightSelectBlock(void)
{
	// �J�����̈ʒu�擾
	D3DXVECTOR3 CameraPos = CManager::GetCamera()->GetPos();

	// CScene�̃|�C���^
	CScene *pScene = NULL;

	// ��
	do
	{
		// �I�u�W�F�^�C�v���G�̏ꍇ
		pScene = GetScene(OBJTYPE_BLOCK);

		// NULL�̏ꍇ
		if (pScene != NULL)
		{
			// �I�u�W�F�N�g�^�C�v�擾
			OBJTYPE objType = pScene->GetObjType();
			// �I�u�W�F�N�g�^�C�v��BLOCK�̏ꍇ
			if (objType == OBJTYPE_BLOCK)
			{
				// ���W�ƃT�C�Y�擾
				D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

				// �͈͓��̏ꍇ
				if (BlockPos.x < CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE3 && BlockPos.x > CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE3)
				{
					// �v���C���[�����ʂ������Ă��Ĕ��̈ʒu���O�ɂ���ꍇ
					if (m_pos.x < BlockPos.x)
					{
						// �C���N�������g
						m_nBlockNum++;
					}
					// �v���C���[�����ʂ������Ă��Ĕ��̈ʒu���O���ɂ���ꍇ
					if (m_pos.x > BlockPos.x)
					{
						((CBlock*)pScene)->UnSelected();
					}
				}
			}
		}
	} while (pScene != NULL);

	// �u���b�N����0��葽���ꍇ
	if (m_nBlockNum > MIN_BLOCK_NUM)
	{
		// NULL��
		CBlock **apBlock = NULL;

		// NULL�̏ꍇ
		if (apBlock == NULL)
		{
			// �������m��
			apBlock = new CBlock*[m_nBlockNum];

			// �ŏ�����
			m_nBlockNum = MIN_BLOCK_NUM;

			// NULL�łȂ��ꍇ
			if (apBlock != NULL)
			{
				do
				{
					// �I�u�W�F�^�C�v���G�̏ꍇ
					pScene = GetScene(OBJTYPE_BLOCK);
					// NULL�łȂ��ꍇ
					if (pScene != NULL)
					{
						// �I�u�W�F�N�g�^�C�v�擾
						OBJTYPE objType = pScene->GetObjType();

						// �I�u�W�F�N�g�^�C�v��BLOCK�̏ꍇ
						if (objType == OBJTYPE_BLOCK)
						{
							// ���W�ƃT�C�Y�擾
							D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

							// �͈͓��̏ꍇ
							if (BlockPos.x < CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE3 && BlockPos.x > CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE3)
							{
								// �v���C���[���E�������Ă��Ĕ��̈ʒu���O�ɂ���ꍇ
								if (m_pos.x < BlockPos.x)
								{
									// �|�C���^���
									apBlock[m_nBlockNum] = (CBlock*)pScene;

									// �C���N�������g
									m_nBlockNum++;
								}
							}
						}
					}
				} while (pScene != NULL);

				// float�̃|�C���^
				float *anLength = NULL;

				// NULL�̏ꍇ
				if (anLength == NULL)
				{
					// �������m��
					anLength = new float[m_nBlockNum];
					// NULL�łȂ��ꍇ
					if (anLength != NULL)
					{
						// �u���b�N������
						for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
						{
							// �ʒu���W
							D3DXVECTOR3 BlockPos = apBlock[nCnt]->GetPos();
							// �v���C���[�Ƃ̋���
							anLength[nCnt] = sqrtf(powf(m_pos.x - BlockPos.x, POW_VALUE) + powf(m_pos.y - BlockPos.y, POW_VALUE));
						}

						// �z��̐擪
						int nFirst_Array;

						// �ŏ��l
						int nMin_Length;

						// �ꎞ�ۑ�
						float fArray_Move;

						// �ꎞ�ۑ�
						CBlock *pBlock_Save;

						// �u���b�N������
						for (nFirst_Array = INIT_INT; nFirst_Array < m_nBlockNum - ARRAY_MOVE_NUMBER; nFirst_Array++)
						{
							// �z��̐擪���ŏ��l��
							nMin_Length = nFirst_Array;

							// ��r
							for (int nCnt = nFirst_Array + ARRAY_MOVE_NUMBER; nCnt < m_nBlockNum; nCnt++)
							{
								// �������ŏ��l���߂��ꍇ
								if (anLength[nCnt] < anLength[nMin_Length])
								{
									// ���
									nMin_Length = nCnt;
								}
							}
							// �擪�̔z��̒l����ۑ�
							fArray_Move = anLength[nFirst_Array];
							pBlock_Save = apBlock[nFirst_Array];

							// �擪�̔z��ɍŏ��l���
							anLength[nFirst_Array] = anLength[nMin_Length];
							apBlock[nFirst_Array] = apBlock[nMin_Length];

							// �ŏ��l�Ɍ��̐擪�̒l����
							anLength[nMin_Length] = fArray_Move;
							apBlock[nMin_Length] = pBlock_Save;
						}
					}
					// �������j��
					delete[]anLength;

					// NULL��
					anLength = NULL;
				}
				// 0�ԖڈȊO���I����Ԃ�
				for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
				{
					// ���I����Ԃ�
					apBlock[nCnt]->UnSelected();
				}

				// �z��̐擪����
				m_pBlock = apBlock[ARRAY_FIRST_NUM];

			}
			// �������j��
			delete[]apBlock;

			// NULL��
			apBlock = NULL;
		}
	}
	// �ŏ�����
	m_nBlockNum = MIN_BLOCK_NUM;
}
//******************************************************************************
// �u���b�N�����֐�
//******************************************************************************
void CPlayer::RightBlock(void)
{
	// �J�����̈ʒu�擾
	D3DXVECTOR3 CameraPos = CManager::GetCamera()->GetPos();

	// �R���g���[���[�擾
	DIJOYSTATE js;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	// NULL�łȂ��ꍇ
	if (m_pBlock != NULL)
	{
		// ���̈ʒu�擾
		D3DXVECTOR3 BlockPos = m_pBlock->GetPos();

		// �͈͓��̏ꍇ
		if (BlockPos.x < CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE3 && BlockPos.x > CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE3)
		{
			// �v���C���[���E�������Ă��Ĕ��̈ʒu���O�ɂ���ꍇ
			if (m_pos.x < BlockPos.x)
			{
				// �I�𒆂̏ꍇ
				m_pBlock->Selecting();

				// �������̏ꍇ
				if (m_Blcok_Active == BLOCK_ACTIVE_CREATE)
				{
					// true��
					m_pBlock->SetbMove(true);

					// �ړ����鏈��
					m_pBlock->Create_Move();

					// ���ˑ̐���
					Emitter_Create(EMITTER_TYPE_STAR);
				}
			}
			// RT���������ꍇ
			if (pInputJoystick->GetJoystickPress(CInputJoystick::JS_RT))
			{
				// �I����ԈȊO�̏ꍇ
				if (m_Blcok_Active != BLOCK_ACTIVE_SELECT)
				{
					// �ړ��̔���ݒ�
					m_pBlock->SetbMove(true);

					// �ړ���Ԃ�
					m_Blcok_Active = BLOCK_ACTIVE_MOVE;

					// �u���b�N�̈ړ�
					m_pBlock->Move();
				}
				// false�̏ꍇ
				if (m_bBlock_Move == false)
				{
					// �v���C���[��荶�ɂ���ꍇ
					if (m_pos.x > BlockPos.x)
					{
						m_Rot_State = ROT_STATE_LEFT;
					}
				}
				// true�̏ꍇ
				if (m_bBlock_Move == true)
				{
					// �v���C���[��荶�ɂ���ꍇ
					if (m_pos.x > BlockPos.x)
					{
						// �ړ��̔���ݒ�
						m_pBlock->SetbMove(false);

						// �u���b�N�ōs�����ĂȂ���Ԃ�
						m_Blcok_Active = BLOCK_ACTIVE_NONE;

						// NULL��
						m_pBlock = NULL;
					}
				}
			}
			else
			{
				// �ړ��̔���ݒ�
				m_pBlock->SetbEmitter(false);

				// �ړ��̔���ݒ�
				m_pBlock->SetbMove(false);

				// �v���C���[���E�������Ă��Ĕ��̈ʒu�����ɂ���ꍇ
				if (m_pos.x > BlockPos.x)
				{
					// �I���O��
					m_pBlock->UnSelected();

					// �u���b�N��ʏ��Ԃ�
					m_Blcok_Active = BLOCK_ACTIVE_NONE;
				}
			}
		}
		// �͈͊O�̏ꍇ
		if (BlockPos.x > CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE3 || BlockPos.x < CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE3)
		{
			// ���ˑ̂̔���ݒ�
			m_pBlock->SetbEmitter(false);

			// �ړ��̔���ݒ�
			m_pBlock->SetbMove(false);

			// �I���O��
			m_pBlock->UnSelected();

			// �u���b�N��ʏ��Ԃ�
			m_Blcok_Active = BLOCK_ACTIVE_NONE;

			// NULL��
			m_pBlock = NULL;
		}
	}
}
//******************************************************************************
// �������u���b�N��I��
//******************************************************************************
void CPlayer::RightSelectionBlock(void)
{
	//�T�E���h�擾
	CSound * pSound = CManager::GetSound();

	// �J�����̈ʒu�擾
	D3DXVECTOR3 CameraPos = CManager::GetCamera()->GetPos();

	// �R���g���[���[�擾
	DIJOYSTATE js;
	js.lY = INIT_INT;
	js.lX = INIT_INT;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	// CScene�̃|�C���^
	CScene *pScene = NULL;

	// ��
	do
	{
		// �I�u�W�F�^�C�v���G�̏ꍇ
		pScene = GetScene(OBJTYPE_BLOCK);

		// NULL�̏ꍇ
		if (pScene != NULL)
		{
			// �I�u�W�F�N�g�^�C�v�擾
			OBJTYPE objType = pScene->GetObjType();

			// �I�u�W�F�N�g�^�C�v��BLOCK�̏ꍇ
			if (objType == OBJTYPE_BLOCK)
			{
				// ���W�ƃT�C�Y�擾
				D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

				// �͈͓��̏ꍇ
				if (BlockPos.x < CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE3 && BlockPos.x > CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE3)
				{
					// �v���C���[�����ʂ������Ă��Ĕ��̈ʒu���O�ɂ���ꍇ
					if (m_pos.x < BlockPos.x)
					{
						// �C���N�������g
						m_nBlockNum++;
					}
					// �v���C���[�����ʂ������Ă��Ĕ��̈ʒu���O���ɂ���ꍇ
					if (m_pos.x > BlockPos.x)
					{
						((CBlock*)pScene)->UnSelected();
					}
				}
			}
		}
	} while (pScene != NULL);

	// 0��葽���ꍇ
	if (m_nBlockNum > MIN_BLOCK_NUM)
	{
		// NULL��
		CBlock **apBlock = NULL;

		// NULL�̏ꍇ
		if (apBlock == NULL)
		{
			// �������m��
			apBlock = new CBlock*[m_nBlockNum];

			// �ŏ�����
			m_nBlockNum = MIN_BLOCK_NUM;

			// NULL�łȂ��ꍇ
			if (apBlock != NULL)
			{
				do
				{
					// �I�u�W�F�^�C�v���G�̏ꍇ
					pScene = GetScene(OBJTYPE_BLOCK);

					// NULL�łȂ��ꍇ
					if (pScene != NULL)
					{
						// �I�u�W�F�N�g�^�C�v�擾
						OBJTYPE objType = pScene->GetObjType();

						// �I�u�W�F�N�g�^�C�v��BLOCK�̏ꍇ
						if (objType == OBJTYPE_BLOCK)
						{
							// ���W�ƃT�C�Y�擾
							D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

							// �͈͓��̏ꍇ
							if (BlockPos.x < CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE3 && BlockPos.x > CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE3)
							{
								// �v���C���[���E�������Ă��Ĕ��̈ʒu���O�ɂ���ꍇ
								if (m_pos.x < BlockPos.x)
								{
									// �|�C���^���
									apBlock[m_nBlockNum] = (CBlock*)pScene;

									// �C���N�������g
									m_nBlockNum++;
								}
							}
						}
					}
				} while (pScene != NULL);

				// float�̃|�C���^
				float *anLength = NULL;

				// NULL�̏ꍇ
				if (anLength == NULL)
				{
					// �������m��
					anLength = new float[m_nBlockNum];

					// NULL�łȂ��ꍇ
					if (anLength != NULL)
					{
						// �u���b�N������
						for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
						{
							// �ʒu���W
							D3DXVECTOR3 BlockPos = apBlock[nCnt]->GetPos();

							// �v���C���[�Ƃ̋���
							anLength[nCnt] = sqrtf(powf(m_pos.x - BlockPos.x, POW_VALUE));
						}

						// �z��̐擪
						int nFirst_Array;

						// �ŏ��l
						int nMin_Length;

						// �ꎞ�ۑ�
						float fArray_Move;

						// �ꎞ�ۑ�
						CBlock *pBlock_Save;

						// �u���b�N������
						for (nFirst_Array = INIT_INT; nFirst_Array < m_nBlockNum - ARRAY_MOVE_NUMBER; nFirst_Array++)
						{
							// �z��̐擪���ŏ��l��
							nMin_Length = nFirst_Array;

							// ��r
							for (int nCnt = nFirst_Array + ARRAY_MOVE_NUMBER; nCnt < m_nBlockNum; nCnt++)
							{
								// �������ŏ��l���߂��ꍇ
								if (anLength[nCnt] > anLength[nMin_Length])
								{
									// ���
									nMin_Length = nCnt;
								}
							}
							// �擪�̔z��̒l����ۑ�
							fArray_Move = anLength[nFirst_Array];
							pBlock_Save = apBlock[nFirst_Array];

							// �擪�̔z��ɍŏ��l���
							anLength[nFirst_Array] = anLength[nMin_Length];
							apBlock[nFirst_Array] = apBlock[nMin_Length];

							// �ŏ��l�Ɍ��̐擪�̒l����
							anLength[nMin_Length] = fArray_Move;
							apBlock[nFirst_Array] = pBlock_Save;
						}
					}
					// �������j��
					delete[]anLength;

					// NULL��
					anLength = NULL;
				}
				// 0�ԖڈȊO���I����Ԃ�
				for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
				{
					// ���I����Ԃ�
					apBlock[nCnt]->PlayerSelection();
				}
				// �I���I����ԂłȂ��ꍇ
				if (g_lpDIDevice != NULL && pInputJoystick->GetJoystickRelease(CInputJoystick::JS_LT))
				{
					// 0�ԖڈȊO���I����Ԃ�
					for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
					{
						// �I���I���̐F��
						apBlock[nCnt]->UnSelected();
					}

					// �I���������
					m_Blcok_Active = BLOCK_ACTIVE_SELECTED;
				}
				// �F�I�𒆂̐F��
				apBlock[m_nBlock_Select_Num]->Selecting();

				// �I�����Ă���u���b�N�̔z�����
				m_pBlock = apBlock[m_nBlock_Select_Num];
			}
			// �������j��
			delete[]apBlock;

			// NULL��
			apBlock = NULL;
		}
	}

	// ���ۑ�
	m_nSelect_Save_Num = m_nBlockNum;

	// �ŏ�����
	m_nBlockNum = MIN_BLOCK_NUM;

	if (g_lpDIDevice != NULL)
	{
		// false�̏ꍇ
		if (m_bStick == false)
		{
			// �E�X�e�B�b�N�����ɓ|��
			
			if (js.lZ <= -STICK_REACTION)
			{
				// 0�Ԗڂ̏ꍇ
				if (m_nBlock_Select_Num > MIN_BLOCK_NUM)
				{
					// �I�����Đ�
					pSound->PlaySoundA(CSound::SOUND_LABEL_SE_SELECT);

					// �f�N�������g
					m_nBlock_Select_Num--;
				}
				// 0�Ԗڂ̏ꍇ
				if (m_nBlock_Select_Num == MIN_BLOCK_NUM)
				{
					// �u���b�N�̍ő�l�ɂ���
					m_nBlock_Select_Num = MIN_BLOCK_NUM;
				}

				// true��
				m_bStick = true;
			}
			// �E�X�e�B�b�N���E�ɓ|��
			if (js.lZ >= STICK_REACTION)
			{
				// �ő�l�̏ꍇ
				if (m_nBlock_Select_Num < m_nSelect_Save_Num - ARRAY_SUB_VALUE)
				{
					// �I�����Đ�
					pSound->PlaySoundA(CSound::SOUND_LABEL_SE_SELECT);

					// �C���N�������g
					m_nBlock_Select_Num++;
				}
				// �ő�l�̏ꍇ
				if (m_nBlock_Select_Num >= m_nSelect_Save_Num - ARRAY_SUB_VALUE)
				{
					// 0�Ԗڂɐݒ�
					m_nBlock_Select_Num = m_nSelect_Save_Num - ARRAY_SUB_VALUE;
				}

				// true��
				m_bStick = true;
			}
		}
		// true�̏ꍇ
		if (m_bStick == true)
		{
			// -500���傫��0��菬�����ꍇ
			if (js.lZ > -STICK_REACTION && js.lZ <= DEAD_ZONE_MIN)
			{
				m_bStick = false;
			}
			// 500��菬����0���傫���ꍇ
			if (js.lZ < STICK_REACTION && js.lZ >= DEAD_ZONE_MIN)
			{
				m_bStick = false;
			}
		}
		// 0���Ⴂ�ꍇ
		if (m_nBlock_Select_Num < MIN_BLOCK_NUM)
		{
			// 0�ɐݒ�
			m_nBlock_Select_Num = MIN_BLOCK_NUM;
		}
		// ���̐����傫���ꍇ
		if (m_nBlock_Select_Num > m_nSelect_Save_Num)
		{
			// ���̐��Ɠ����ɂ���
			m_nBlock_Select_Num = m_nSelect_Save_Num;
		}
	}
}
//******************************************************************************
// �����̑I��
//******************************************************************************
void CPlayer::LeftSelectBlock(void)
{
	// �J�����̈ʒu�擾
	D3DXVECTOR3 CameraPos = CManager::GetCamera()->GetPos();

	// CScene�̃|�C���^
	CScene *pScene = NULL;

	// ��
	do
	{
		// �I�u�W�F�^�C�v���G�̏ꍇ
		pScene = GetScene(OBJTYPE_BLOCK);

		// NULL�̏ꍇ
		if (pScene != NULL)
		{
			// �I�u�W�F�N�g�^�C�v�擾
			OBJTYPE objType = pScene->GetObjType();

			// �I�u�W�F�N�g�^�C�v��BLOCK�̏ꍇ
			if (objType == OBJTYPE_BLOCK)
			{
				// ���W�ƃT�C�Y�擾
				D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

				// �͈͓��̏ꍇ
				if (BlockPos.x < CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE3 && BlockPos.x > CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE3)
				{
					// �v���C���[�����������Ă��Ĕ��̈ʒu���O�ɂ���ꍇ
					if (m_pos.x > BlockPos.x)
					{
						// �C���N�������g
						m_nBlockNum++;
					}
					// �v���C���[�����������Ă��Ĕ��̈ʒu���O���ɂ���ꍇ
					if (m_pos.x < BlockPos.x)
					{
						((CBlock*)pScene)->UnSelected();
					}
				}
			}
		}
		// NULL�ɂȂ�܂ŌJ��Ԃ�
	} while (pScene != NULL);

	// �u���b�N����0��葽���ꍇ
	if (m_nBlockNum > MIN_BLOCK_NUM)
	{
		// NULL��
		CBlock **apBlock = NULL;

		// NULL�̏ꍇ
		if (apBlock == NULL)
		{
			// �������m��
			apBlock = new CBlock*[m_nBlockNum];

			// �ŏ�����
			m_nBlockNum = MIN_BLOCK_NUM;

			// NULL�łȂ��ꍇ
			if (apBlock != NULL)
			{
				do
				{
					// �I�u�W�F�^�C�v���G�̏ꍇ
					pScene = GetScene(OBJTYPE_BLOCK);

					// NULL�łȂ��ꍇ
					if (pScene != NULL)
					{
						// �I�u�W�F�N�g�^�C�v�擾
						OBJTYPE objType = pScene->GetObjType();

						// �I�u�W�F�N�g�^�C�v��BLOCK�̏ꍇ
						if (objType == OBJTYPE_BLOCK)
						{
							// ���W�ƃT�C�Y�擾
							D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

							// �͈͓��̏ꍇ
							if (BlockPos.x < CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE3 && BlockPos.x > CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE3)
							{
								// �v���C���[�����������Ă��Ĕ��̈ʒu���O�ɂ���ꍇ
								if (m_pos.x > BlockPos.x)
								{
									// �|�C���^���
									apBlock[m_nBlockNum] = (CBlock*)pScene;

									// �C���N�������g
									m_nBlockNum++;
								}
							}
						}
					}
				} while (pScene != NULL);

				// float�̃|�C���^
				float *anLength = NULL;

				// NULL�̏ꍇ
				if (anLength == NULL)
				{
					// �������m��
					anLength = new float[m_nBlockNum];
					// NULL�łȂ��ꍇ
					if (anLength != NULL)
					{
						// �u���b�N������
						for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
						{
							// �ʒu���W
							D3DXVECTOR3 BlockPos = apBlock[nCnt]->GetPos();

							// �v���C���[�Ƃ̋���
							anLength[nCnt] = sqrtf(powf(m_pos.x - BlockPos.x, POW_VALUE));
						}

						// �z��̐擪
						int nFirst_Array;

						// �ŏ��l
						int nMin_Length;

						// �ꎞ�ۑ�
						float fArray_Move;

						// �ꎞ�ۑ�
						CBlock *pBlock_Save;

						// �u���b�N������
						for (nFirst_Array = INIT_INT; nFirst_Array < m_nBlockNum - ARRAY_MOVE_NUMBER; nFirst_Array++)
						{
							// �z��̐擪���ŏ��l��
							nMin_Length = nFirst_Array;

							// ��r
							for (int nCnt = nFirst_Array + ARRAY_MOVE_NUMBER; nCnt < m_nBlockNum; nCnt++)
							{
								// �������ŏ��l���߂��ꍇ
								if (anLength[nCnt] < anLength[nMin_Length])
								{
									// ���
									nMin_Length = nCnt;
								}
							}
							// �擪�̔z��̒l����ۑ�
							fArray_Move = anLength[nFirst_Array];
							pBlock_Save = apBlock[nFirst_Array];

							// �擪�̔z��ɍŏ��l���
							anLength[nFirst_Array] = anLength[nMin_Length];
							apBlock[nFirst_Array] = apBlock[nMin_Length];

							// �ŏ��l�Ɍ��̐擪�̒l����
							anLength[nMin_Length] = fArray_Move;
							apBlock[nMin_Length] = pBlock_Save;
						}
					}
					// �������j��
					delete[]anLength;

					// NULL��
					anLength = NULL;
				}
				// 0�ԖڈȊO���I����Ԃ�
				for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
				{
					// ���I����Ԃ�
					apBlock[nCnt]->UnSelected();
				}

				// �z��̐擪����
				m_pBlock = apBlock[ARRAY_FIRST_NUM];

			}
			// �������j��
			delete[]apBlock;

			// NULL��
			apBlock = NULL;
		}
	}
	// �ŏ�����
	m_nBlockNum = MIN_BLOCK_NUM;
}
//******************************************************************************
// �u���b�N�����֐�
//******************************************************************************
void CPlayer::LeftBlock(void)
{
	// �J�����̈ʒu�擾
	D3DXVECTOR3 CameraPos = CManager::GetCamera()->GetPos();

	// �R���g���[���[�擾
	DIJOYSTATE js;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	// NULL�łȂ��ꍇ
	if (m_pBlock != NULL)
	{
		// ���̈ʒu�擾
		D3DXVECTOR3 BlockPos = m_pBlock->GetPos();

		// �͈͓��̏ꍇ
		if (BlockPos.x < CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE3 && BlockPos.x > CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE3)
		{
			// �v���C���[�����������Ă��Ĕ��̈ʒu���O�ɂ���ꍇ
			if (m_pos.x > BlockPos.x)
			{
				// �I�𒆂̏ꍇ
				m_pBlock->Selecting();

				// �������̏ꍇ
				if (m_Blcok_Active == BLOCK_ACTIVE_CREATE)
				{
					// true��
					m_pBlock->SetbMove(true);

					// �ړ����鏈��
					m_pBlock->Create_Move();

					// ���ˑ̐���
					Emitter_Create(EMITTER_TYPE_STAR);
				}
			}
			// RT���������ꍇ
			if (pInputJoystick->GetJoystickPress(CInputJoystick::JS_RT))
			{
				// �I����ԈȊO�̏ꍇ
				if (m_Blcok_Active != BLOCK_ACTIVE_SELECT)
				{
					// �ړ��̔���ݒ�
					m_pBlock->SetbMove(true);

					// �ړ���Ԃ�
					m_Blcok_Active = BLOCK_ACTIVE_MOVE;

					// �u���b�N�̈ړ�
					m_pBlock->Move();
				}
				// false�̏ꍇ
				if (m_bBlock_Move == false)
				{
					// �v���C���[���E�ɂ���ꍇ
					if (m_pos.x < BlockPos.x)
					{
						m_Rot_State = ROT_STATE_RIGHT;
					}
				}
				// true�̏ꍇ
				if (m_bBlock_Move == true)
				{
					// �v���C���[��荶�ɂ���ꍇ
					if (m_pos.x < BlockPos.x)
					{
						// �ړ��̔���ݒ�
						m_pBlock->SetbMove(false);

						// �u���b�N�ōs�����ĂȂ���Ԃ�
						m_Blcok_Active = BLOCK_ACTIVE_NONE;

						// NULL��
						m_pBlock = NULL;
					}
				}
			}
			else
			{
				// ���ˑ̂̔���ݒ�
				m_pBlock->SetbEmitter(false);

				// �ړ��̔���ݒ�
				m_pBlock->SetbMove(false);

				// �v���C���[�����������Ă��Ĕ��̈ʒu�����ɂ���ꍇ
				if (m_pos.x < BlockPos.x)
				{
					// �I���O��
					m_pBlock->UnSelected();

					// �u���b�N���ړ���Ԃ�
					m_Blcok_Active = BLOCK_ACTIVE_NONE;
				}
			}
		}
		// �͈͊O�̏ꍇ
		if (BlockPos.x > CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE3 || BlockPos.x < CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE3)
		{
			// ���ˑ̂̔���ݒ�
			m_pBlock->SetbEmitter(false);

			// �ړ��̔���ݒ�
			m_pBlock->SetbMove(false);

			// �I���O��
			m_pBlock->UnSelected();

			// �u���b�N��ʏ��Ԃ�
			m_Blcok_Active = BLOCK_ACTIVE_NONE;

			// NULL��
			m_pBlock = NULL;
		}
	}
}
//******************************************************************************
// �������u���b�N��I��
//******************************************************************************
void CPlayer::LeftSelectionBlock(void)
{
	//�T�E���h�擾
	CSound * pSound = CManager::GetSound();

	// �R���g���[���[�擾
	DIJOYSTATE js;
	// ������
	js.lY = DEAD_ZONE_MIN;
	js.lX = DEAD_ZONE_MIN;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	// �J�����̈ʒu�擾
	D3DXVECTOR3 CameraPos = CManager::GetCamera()->GetPos();

	// CScene�̃|�C���^
	CScene *pScene = NULL;

	// �u���b�N
	do
	{
		// �I�u�W�F�^�C�v���G�̏ꍇ
		pScene = GetScene(OBJTYPE_BLOCK);

		// NULL�̏ꍇ
		if (pScene != NULL)
		{
			// �I�u�W�F�N�g�^�C�v�擾
			OBJTYPE objType = pScene->GetObjType();

			// �I�u�W�F�N�g�^�C�v��BLOCK�̏ꍇ
			if (objType == OBJTYPE_BLOCK)
			{
				// ���W�ƃT�C�Y�擾
				D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

				// �͈͓��̏ꍇ
				if (BlockPos.x < CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE3 && BlockPos.x > CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE3)
				{
					// �v���C���[�����ʂ������Ă��Ĕ��̈ʒu���O�ɂ���ꍇ
					if (m_pos.x > BlockPos.x)
					{
						// �C���N�������g
						m_nBlockNum++;
					}
					// �v���C���[�����ʂ������Ă��Ĕ��̈ʒu���O���ɂ���ꍇ
					if (m_pos.x < BlockPos.x)
					{
						((CBlock*)pScene)->UnSelected();
					}
				}
			}
		}
		// NULL�ɂȂ�܂ŌJ��Ԃ�
	} while (pScene != NULL);

	// 0��葽���ꍇ
	if (m_nBlockNum > MIN_BLOCK_NUM)
	{
		// NULL��
		CBlock **apBlock = NULL;

		// NULL�̏ꍇ
		if (apBlock == NULL)
		{
			// �������m��
			apBlock = new CBlock*[m_nBlockNum];

			// �ŏ�����
			m_nBlockNum = MIN_BLOCK_NUM;

			// NULL�łȂ��ꍇ
			if (apBlock != NULL)
			{
				do
				{
					// �I�u�W�F�^�C�v���G�̏ꍇ
					pScene = GetScene(OBJTYPE_BLOCK);

					// NULL�łȂ��ꍇ
					if (pScene != NULL)
					{
						// �I�u�W�F�N�g�^�C�v�擾
						OBJTYPE objType = pScene->GetObjType();

						// �I�u�W�F�N�g�^�C�v��BLOCK�̏ꍇ
						if (objType == OBJTYPE_BLOCK)
						{
							// ���W�ƃT�C�Y�擾
							D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

							// �͈͓��̏ꍇ
							if (BlockPos.x < CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE3 && BlockPos.x > CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE3)
							{
								// �v���C���[�����������Ă��Ĕ��̈ʒu���O�ɂ���ꍇ
								if (m_pos.x > BlockPos.x)
								{
									// �|�C���^���
									apBlock[m_nBlockNum] = (CBlock*)pScene;

									// �C���N�������g
									m_nBlockNum++;
								}
							}
						}
					}
					// NULL�ɂȂ�܂ŌJ��Ԃ�
				} while (pScene != NULL);

				// float�̃|�C���^
				float *afLength = NULL;

				// NULL�̏ꍇ
				if (afLength == NULL)
				{
					// �������m��
					afLength = new float[m_nBlockNum];

					// NULL�łȂ��ꍇ
					if (afLength != NULL)
					{
						// �u���b�N������
						for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
						{
							// �ʒu���W
							D3DXVECTOR3 BlockPos = apBlock[nCnt]->GetPos();

							// �v���C���[�Ƃ̋���
							afLength[nCnt] = sqrtf(powf(m_pos.x - BlockPos.x, POW_VALUE) + powf(m_pos.y - BlockPos.y, POW_VALUE));
						}

						// �z��̐擪
						int nFirst_Array;

						// �ŏ��l
						int nMin_Length;

						// �ꎞ�ۑ�
						float fArray_Move;

						// �ꎞ�ۑ�
						CBlock *pBlock_Save;

						// �u���b�N������
						for (nFirst_Array = INIT_INT; nFirst_Array < m_nBlockNum; nFirst_Array++)
						{
							// �z��̐擪���ŏ��l��
							nMin_Length = nFirst_Array;

							// ��r
							for (int nCnt = nFirst_Array + ARRAY_MOVE_NUMBER; nCnt < m_nBlockNum; nCnt++)
							{
								// �������ŏ��l���߂��ꍇ
								if (afLength[nCnt] > afLength[nMin_Length])
								{
									// ���
									nMin_Length = nCnt;
								}
							}
							// �擪�̔z��̒l����ۑ�
							fArray_Move = afLength[nFirst_Array];
							pBlock_Save = apBlock[nFirst_Array];

							// �擪�̔z��ɍŏ��l���
							afLength[nFirst_Array] = afLength[nMin_Length];
							apBlock[nFirst_Array] = apBlock[nMin_Length];

							// �ŏ��l�Ɍ��̐擪�̒l����
							afLength[nMin_Length] = fArray_Move;
							apBlock[nFirst_Array] = pBlock_Save;
						}
					}
					// �������j��
					delete[]afLength;

					// NULL��
					afLength = NULL;
				}
				// 0�ԖڈȊO���I����Ԃ�
				for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
				{
					// ���I����Ԃ�
					apBlock[nCnt]->PlayerSelection();
				}
				// �I���I����ԂłȂ��ꍇ
				if (g_lpDIDevice != NULL && pInputJoystick->GetJoystickRelease(CInputJoystick::JS_LT))
				{
					// 0�ԖڈȊO���I����Ԃ�
					for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
					{
						// �I���I���̐F��
						apBlock[nCnt]->UnSelected();
					}

					// �I���������
					m_Blcok_Active = BLOCK_ACTIVE_SELECTED;
				}
				// �F�I�𒆂̐F��
				apBlock[m_nBlockNum - ARRAY_SUB_VALUE - m_nBlock_Select_Num]->Selecting();

				// �I�����Ă���u���b�N�̔z�����
				m_pBlock = apBlock[m_nBlockNum - ARRAY_SUB_VALUE - m_nBlock_Select_Num];
			}
			// �������j��
			delete[]apBlock;

			// NULL��
			apBlock = NULL;
		}
	}

	// ���ۑ�
	m_nSelect_Save_Num = m_nBlockNum;

	// �ŏ�����
	m_nBlockNum = MIN_BLOCK_NUM;

	if (g_lpDIDevice != NULL)
	{
		// false�̏ꍇ
		if (m_bStick == false)
		{
			// �E�X�e�B�b�N�����ɓ|��
			if (js.lZ <= -STICK_REACTION)
			{
				// �ő�l�̏ꍇ
				if (m_nBlock_Select_Num < m_nSelect_Save_Num - ARRAY_SUB_VALUE)
				{
					// �I�����Đ�
					pSound->PlaySoundA(CSound::SOUND_LABEL_SE_SELECT);

					// �C���N�������g
					m_nBlock_Select_Num++;
				}
				// �ő�l�̏ꍇ
				if (m_nBlock_Select_Num >= m_nSelect_Save_Num - ARRAY_SUB_VALUE)
				{
					// 0�Ԗڂɐݒ�
					m_nBlock_Select_Num = m_nSelect_Save_Num - ARRAY_SUB_VALUE;
				}
				// true��
				m_bStick = true;
			}
		// �E�X�e�B�b�N���E�ɓ|��
		if (js.lZ >= STICK_REACTION)
		{
				// 0�Ԗڂ̏ꍇ
				if (m_nBlock_Select_Num > MIN_BLOCK_NUM)
				{
					// �I�����Đ�
					pSound->PlaySoundA(CSound::SOUND_LABEL_SE_SELECT);

					// �f�N�������g
					m_nBlock_Select_Num--;
				}
				// 0�Ԗڂ̏ꍇ
				if (m_nBlock_Select_Num == MIN_BLOCK_NUM)
				{
					// �u���b�N�̍ő�l�ɂ���
					m_nBlock_Select_Num = MIN_BLOCK_NUM;
				}
				// true��
				m_bStick = true;
			}
		}
		// true�̏ꍇ
		if (m_bStick == true)
		{
			// -500���傫��0��菬�����ꍇ
			if (js.lZ > -STICK_REACTION && js.lZ <= DEAD_ZONE_MIN)
			{
				m_bStick = false;
			}
			// 500��菬����0���傫���ꍇ
			if (js.lZ < STICK_REACTION && js.lZ >= DEAD_ZONE_MIN)
			{
				m_bStick = false;
			}
		}
		// 0�������ꍇ
		if (m_nBlock_Select_Num < MIN_BLOCK_NUM)
		{
			// 0�ɐݒ�
			m_nBlock_Select_Num = MIN_BLOCK_NUM;
		}
		// ���̐����傫���ꍇ
		if (m_nBlock_Select_Num > m_nSelect_Save_Num)
		{
			// ���̐��Ɠ����ɂ���
			m_nBlock_Select_Num = m_nSelect_Save_Num;
		}
	}
}
//******************************************************************************
// �u���b�N�����֐�
//******************************************************************************
void CPlayer::Block_Create(void)
{
	// ������Ԃ�
	m_Blcok_Active = BLOCK_ACTIVE_CREATE;

	// NULL�̏ꍇ
	if (m_pStoneBlock == NULL)
	{
		// �E�����̏ꍇ
		if (m_Rot_State == ROT_STATE_RIGHT)
		{
			// �G�t�F�N�g��
			CParticle_Effect::Create(EFFECT_RIGHTPOS, CParticle_Effect::TYPE_STAR_EFFECT);

			// ����
			m_pStoneBlock = CStone_Block::Create(BLOCK_CREATE_RIGHTPOS, BLOCK_ROT, BLOCK_SIZE);
		}
		// �������̏ꍇ
		if (m_Rot_State == ROT_STATE_LEFT)
		{
			// �G�t�F�N�g��
			CParticle_Effect::Create(EFFECT_LEFTPOS, CParticle_Effect::TYPE_STAR_EFFECT);

			// ����
			m_pStoneBlock = CStone_Block::Create(BLOCK_CREATE_LEFTPOS, BLOCK_ROT, BLOCK_SIZE);
		}
		// ���
		m_pBlock = m_pStoneBlock;
	}
	// NULL�łȂ��ꍇ
	if (m_pStoneBlock != NULL)
	{
		// �ʒu�擾
		D3DXVECTOR3 BlockPos = m_pStoneBlock->GetPos();

		// �G�t�F�N�g��
		CParticle_Effect::Create(RELAESE_POS, CParticle_Effect::TYPE_STAR_EFFECT);

		// �j��
		m_pStoneBlock->ReleaseBlock();

		// �E�����̏ꍇ
		if (m_Rot_State == ROT_STATE_RIGHT)
		{
			// �G�t�F�N�g��
			CParticle_Effect::Create(EFFECT_RIGHTPOS, CParticle_Effect::TYPE_STAR_EFFECT);

			// ����
			m_pStoneBlock = CStone_Block::Create(BLOCK_CREATE_RIGHTPOS, BLOCK_ROT, BLOCK_SIZE);
		}
		// �������̏ꍇ
		if (m_Rot_State == ROT_STATE_LEFT)
		{
			// �G�t�F�N�g��
			CParticle_Effect::Create(EFFECT_LEFTPOS, CParticle_Effect::TYPE_STAR_EFFECT);

			// ����
			m_pStoneBlock = CStone_Block::Create(BLOCK_CREATE_LEFTPOS, BLOCK_ROT, BLOCK_SIZE);
		}
		// ���
		m_pBlock = m_pStoneBlock;
	}
}												   
//******************************************************************************
// �����蔻�菈���֐�
//******************************************************************************
void CPlayer::Collision(void)
{
	//�T�E���h�擾
	CSound * pSound = CManager::GetSound();

	// �ʒu
	D3DXVECTOR3 pos = m_pModel[PARTS_UNDER_BODY]->GetPos();

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

				 //�ǂ��̖ʂɓ����������擾
				 //��
				if (CCollision::RectangleCollisionMove(pos, m_posOld, m_size, BlockPos, BlockSize) == CCollision::SURFACE_DOWN)
				{
					// �ړ���0
					m_move.y = MIN_MOVE_VALUE;

					// �ʒu
					m_pos.y = (-BlockSize.y / DEVIDE_VALUE + BlockPos.y) - (m_size.y / DEVIDE_VALUE);

				}
				// ��
				else if (CCollision::RectangleCollisionMove(m_pos, m_posOld, m_size, BlockPos, BlockSize) == CCollision::SURFACE_UP)
				{
					// �ړ���0
					m_move.y = MIN_MOVE_VALUE;

					// �ʒu
					m_pos.y = (BlockSize.y / DEVIDE_VALUE + BlockPos.y) - (m_size.y / DEVIDE_VALUE);

					// true�̏ꍇ
					if (m_bJump == true)
					{
						// false��
						m_bJump = false;

						// false��
						m_bJumpValue = false;
					}
				}
				// ��
				else if (CCollision::RectangleCollisionMove(pos, m_posOld, m_size, BlockPos, BlockSize) == CCollision::SURFACE_LEFT)
				{
					// �ړ���0
					m_move.x = MIN_MOVE_VALUE;

					// �ʒu
					m_pos.x = (-BlockSize.x / DEVIDE_VALUE + BlockPos.x) - (m_size.x / DEVIDE_VALUE);

					// false�̏ꍇ
					if (m_bCollision == false)
					{
						// true��
						m_bCollision = true;
					}
				}
				// �E
				else if (CCollision::RectangleCollisionMove(pos, m_posOld, m_size, BlockPos, BlockSize) == CCollision::SURFACE_RIGHT)
				{
					// �ړ���0
					m_move.x = MIN_MOVE_VALUE;

					// �ʒu
					m_pos.x = (BlockSize.x / DEVIDE_VALUE + BlockPos.x) + (m_size.x / DEVIDE_VALUE);

					// false�̏ꍇ
					if (m_bCollision == false)
					{
						// true��
						m_bCollision = true;
					}
				}
				// ���E�̖ʂɓ������ĂȂ��ꍇ
				if (CCollision::RectangleCollisionMove(pos, m_posOld, m_size, BlockPos, BlockSize) != CCollision::SURFACE_LEFT ||
					CCollision::RectangleCollisionMove(pos, m_posOld, m_size, BlockPos, BlockSize) != CCollision::SURFACE_RIGHT)
				{
					// true�̏ꍇ
					if (m_bCollision == true)
					{
						// false��
						m_bCollision = false;
					}
				}
			}
		}
	} while (pScene != NULL);

	// 3D�I�u�W�F�N�g�Ƃ̓����蔻��
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
				// �ʒu���W�擾
				D3DXVECTOR3 ObjPos = ((C3D_Obj*)pScene)->GetPos();
				// �T�C�Y�擾
				D3DXVECTOR3 ObjSize = ((C3D_Obj*)pScene)->GetSize();

				//�ǂ��̖ʂɓ����������擾
				//��
				if (CCollision::RectangleCollisionMove(pos, m_posOld, m_size, ObjPos, ObjSize) == CCollision::SURFACE_DOWN)
				{
					// �ړ���0
					m_move.y = MIN_MOVE_VALUE;

					// �ʒu
					m_pos.y = (m_size.y / DEVIDE_VALUE) -  (ObjPos.y + ObjSize.y / DEVIDE_VALUE);
				}
				// ��
				else if (CCollision::RectangleCollisionMove(m_pos, m_posOld, m_size, ObjPos, ObjSize) == CCollision::SURFACE_UP)
				{
					// �^�C�v�擾
					int n3D_ObjType = ((C3D_Obj*)pScene)->GetType();

					// �^�C�v�����u���b�N�̏ꍇ
					if (n3D_ObjType == C3D_Obj::TYPE_FLOOR_01)
					{
						// ���u���b�N�̃^�C�v�擾
						int nType = ((CFloor_Block*)pScene)->GetType();

						// �`�F�b�N�|�C���g�̏ꍇ
						if (nType == CFloor_Block::TYPE_CHECK_POINT)
						{
							// �ʒu�ۑ�
							m_RespawnPos.x = ((CFloor_Block*)pScene)->GetPos().x;
						}
						// �G�����̏ꍇ
						if (nType == CFloor_Block::TYPE_ENEMY_CREATE)
						{
							// �ʒu�ۑ�
							m_RespawnPos.x = ((CFloor_Block*)pScene)->GetPos().x;

							// false�̏ꍇ
							if (m_bEnemyCreate == false)
							{
								// �G����
								CEnemy_Map::Create(ObjPos);

								// true��
								m_bEnemyCreate = true;
							}
						}
						// �I���̏ꍇ
						if (nType == CFloor_Block::TYPE_END)
						{
							// false�̏ꍇ
							if (m_bEnd == false)
							{
								// �J��
								CFade::Create(CManager::MODE_RESULT);

								// true��
								m_bEnd = true;
							}
						}
					}
					// �^�C�v���j�̏ꍇ
					if (n3D_ObjType == C3D_Obj::TYPE_NEEDLE)
					{
						// �G�t�F�N�g����
						CParticle_Effect::Create(DEAD_POS, CParticle_Effect::TYPE_STAR_EFFECT2);

						// ���X�|�[�����Đ�
						pSound->PlaySoundA(CSound::SOUND_LABEL_SE_RESPAWN);

						// ���X�|�[���ʒu�Ɉړ�
						m_pos = m_RespawnPos;

						// �G�t�F�N�g����
						CParticle_Effect::Create(RESPOWN_POS, CParticle_Effect::TYPE_STAR_EFFECT2);
					}
					// �ړ���0
					m_move.y = MIN_MOVE_VALUE;

					// �ʒu
					m_pos.y = (-m_size.y / DEVIDE_VALUE) + (ObjPos.y + ObjSize.y / DEVIDE_VALUE);

					// true�̏ꍇ
					if (m_bJump == true)
					{
						// false��
						m_bJump = false;

						// false��
						m_bJumpValue = false;
					}
				}
				// ��
				else if (CCollision::RectangleCollisionMove(pos, m_posOld, m_size, ObjPos, ObjSize) == CCollision::SURFACE_LEFT)
				{
					// �ړ���0
					m_move.x = MIN_MOVE_VALUE;

					// �ʒu
					m_pos.x = (-m_size.x / DEVIDE_VALUE) + (ObjPos.x - ObjSize.x / DEVIDE_VALUE);

					// false�̏ꍇ
					if (m_bCollision == false)
					{
						// true��
						m_bCollision = true;
					}
				}
				// �E
				else if (CCollision::RectangleCollisionMove(pos, m_posOld, m_size, ObjPos, ObjSize) == CCollision::SURFACE_RIGHT)
				{
					// �ړ���0
					m_move.x = MIN_MOVE_VALUE;

					// �ʒu
					m_pos.x = (m_size.x / DEVIDE_VALUE) + (ObjPos.x + ObjSize.x / DEVIDE_VALUE);

					// false�̏ꍇ
					if (m_bCollision == false)
					{
						// true��
						m_bCollision = true;
					}
				}
				// ���E�̖ʂɓ������ĂȂ��ꍇ
				if (CCollision::RectangleCollisionMove(pos, m_posOld, m_size, ObjPos, ObjSize) != CCollision::SURFACE_LEFT ||
					CCollision::RectangleCollisionMove(pos, m_posOld, m_size, ObjPos, ObjSize) != CCollision::SURFACE_RIGHT)
				{
					// true�̏ꍇ
					if (m_bCollision == true)
					{
						// false��
						m_bCollision = false;
					}
				}
			}
		}
		// pScene��NULL�̏ꍇ
	} while (pScene != NULL);
}
//******************************************************************************
// �ړ������֐�
//******************************************************************************
void CPlayer::Move(void)
{
	//�T�E���h�擾
	CSound * pSound = CManager::GetSound();

	// �R���g���[���[�擾
	DIJOYSTATE js;
	js.lY = INIT_INT;
	js.lX = INIT_INT;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	// �ړI�̌���
	D3DXVECTOR3 RotDest = m_rot;

	// �J�����擾
	CCamera *pCamera = CManager::GetCamera();

	// �J�����̈ʒu�擾
	D3DXVECTOR3 CameraPos = pCamera->GetPos();

	if (g_lpDIDevice != NULL)
	{
		// �u���b�N�I�𒆂łȂ��ꍇ
		if (m_Blcok_Active != BLOCK_ACTIVE_SELECT)
		{
			// false�̏ꍇ
			if (m_bMagic == false)
			{
				// ��
				if (js.lX <= -STICK_REACTION)
				{
					// false�̏ꍇ
					if (m_bDash == false)
					{
						// ���s���Đ�
						pSound->PlaySoundA(CSound::SOUND_LABEL_SE_WALK);

						// true��
						m_bDash = true;
					}

					// true��
					m_bBlock_Move = true;

					// false�̏ꍇ
					if (m_bCollision == false)
					{
						// �J�����̈ʒu���Ⴂ�ꍇ
						if (m_pos.x < CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE)
						{
							pCamera->Move(-MOVE_VALUE.x);
						}
					}
					// NULL�łȂ��ꍇ
					if (m_pBlock != NULL)
					{
						// R�g���K�[��������Ă���ꍇ
						if (pInputJoystick->GetJoystickPress(CInputJoystick::JS_RT))
						{
							// �E�����̏ꍇ
							if (m_Rot_State == ROT_STATE_LEFT)
							{
								// �ړ����[�V����
								m_pMotion->SetMotion(CMotion::MOTION_BLOCK_RUN);

								// ���
								m_move.x = -MOVE_VALUE.x;
							}
							// �������̏ꍇ
							if (m_Rot_State == ROT_STATE_RIGHT)
							{
								// �ړ����[�V����
								m_pMotion->SetMotion(CMotion::MOTION_BACKRUN);

								// ���
								m_move.x = -MOVE_VALUE.x / MOVE_DEVIDE;
							}
						}
					}
					// NULL�̏ꍇ
					if (m_pBlock == NULL)
					{
						// R�g���K�[��������Ă���ꍇ
						if (pInputJoystick->GetJoystickPress(CInputJoystick::JS_RT))
						{
							// �������̏��
							m_Rot_State = ROT_STATE_LEFT;

							// �������łȂ��ꍇ
							if (m_Blcok_Active != BLOCK_ACTIVE_CREATE)
							{
								// �ړ����[�V����
								m_pMotion->SetMotion(CMotion::MOTION_RUN);
							}

							// ���
							m_move.x = -MOVE_VALUE.x;
						}
					}
					// RT��������Ă��Ȃ��ꍇ
					if (!pInputJoystick->GetJoystickPress(CInputJoystick::JS_RT))
					{
						// �������̏��
						m_Rot_State = ROT_STATE_LEFT;

						// �������̏ꍇ
						if (m_Blcok_Active == BLOCK_ACTIVE_CREATE)
						{
							// �u���b�N�ړ����[�V����
							m_pMotion->SetMotion(CMotion::MOTION_BLOCK_RUN);
						}
						// �������łȂ��ꍇ
						if (m_Blcok_Active != BLOCK_ACTIVE_CREATE)
						{
							// �ړ����[�V����
							m_pMotion->SetMotion(CMotion::MOTION_RUN);
						}

						// ���
						m_move.x = -MOVE_VALUE.x;
					}
				}
				// �E
				if (js.lX >= STICK_REACTION)
				{
					// false�̏ꍇ
					if (m_bDash == false)
					{
						// ���s���Đ�
						pSound->PlaySoundA(CSound::SOUND_LABEL_SE_WALK);

						// true��
						m_bDash = true;
					}

					// true��
					m_bBlock_Move = true;

					// false�̏ꍇ
					if (m_bCollision == false)
					{
						// �J�����̈ʒu�������ꍇ
						if (m_pos.x > CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE)
						{
							pCamera->Move(MOVE_VALUE.x);
						}
					}
					// NULL�łȂ��ꍇ
					if (m_pBlock != NULL)
					{
						// R�g���K�[��������Ă���ꍇ
						if (pInputJoystick->GetJoystickPress(CInputJoystick::JS_RT))
						{
							// �������̏ꍇ
							if (m_Rot_State == ROT_STATE_RIGHT)
							{
								// �ړ����[�V����
								m_pMotion->SetMotion(CMotion::MOTION_BLOCK_RUN);

								// ���
								m_move.x = MOVE_VALUE.x;
							}
							// �E�����̏ꍇ
							if (m_Rot_State == ROT_STATE_LEFT)
							{
								// �ړ����[�V����
								m_pMotion->SetMotion(CMotion::MOTION_BACKRUN);

								// ���
								m_move.x = MOVE_VALUE.x / MOVE_DEVIDE;
							}
						}
					}
					// NULL�̏ꍇ
					if (m_pBlock == NULL)
					{
						// R�g���K�[��������Ă���ꍇ
						if (pInputJoystick->GetJoystickPress(CInputJoystick::JS_RT))
						{
							// �������̏��
							m_Rot_State = ROT_STATE_RIGHT;

							// �������łȂ��ꍇ
							if (m_Blcok_Active != BLOCK_ACTIVE_CREATE)
							{
								// �ړ����[�V����
								m_pMotion->SetMotion(CMotion::MOTION_RUN);
							}

							// ���
							m_move.x = MOVE_VALUE.x;
						}
					}
					// RT��������Ă��Ȃ��ꍇ
					if (!pInputJoystick->GetJoystickPress(CInputJoystick::JS_RT))
					{
						// �E�����̏��
						m_Rot_State = ROT_STATE_RIGHT;

						// �������̏ꍇ
						if (m_Blcok_Active == BLOCK_ACTIVE_CREATE)
						{
							// �u���b�N�ړ����[�V����
							m_pMotion->SetMotion(CMotion::MOTION_BLOCK_RUN);
						}
						// �������łȂ��ꍇ
						if (m_Blcok_Active != BLOCK_ACTIVE_CREATE)
						{
							// �ړ����[�V����
							m_pMotion->SetMotion(CMotion::MOTION_RUN);
						}

						// �O�ɐi��
						m_move.x = MOVE_VALUE.x;
					}
				}
				// �X�e�B�b�N�͈̔͊O�̏ꍇ
				if (js.lX > -STICK_REACTION && js.lX < STICK_REACTION)
				{
					// false�̏ꍇ
					if (m_bDash == true)
					{
						// ���s���Đ�
						pSound->StopSound(CSound::SOUND_LABEL_SE_WALK);

						// false��
						m_bDash = false;
					}

					// true��
					m_bBlock_Move = false;

					// �ړ���0
					m_move.x = MIN_MOVE_VALUE;

					// NULL�łȂ��ꍇ
					if (m_pBlock != NULL)
					{
						// R�g���K�[��������Ă���ꍇ
						if (pInputJoystick->GetJoystickPress(CInputJoystick::JS_RT))
						{

							// �u���b�N�̃j���[�g�������[�V����
							m_pMotion->SetMotion(CMotion::MOTION_BLOCK_IDLE);
						}
					}
					// NULL�̏ꍇ
					if (m_pBlock == NULL)
					{
						// R�g���K�[��������Ă���ꍇ
						if (pInputJoystick->GetJoystickPress(CInputJoystick::JS_RT))
						{

							// �u���b�N�̃j���[�g�������[�V����
							m_pMotion->SetMotion(CMotion::MOTION_IDLE);
						}
					}
					// RT��������Ă��Ȃ��ꍇ
					if (!pInputJoystick->GetJoystickPress(CInputJoystick::JS_RT))
					{
						// �������̏ꍇ
						if (m_Blcok_Active == BLOCK_ACTIVE_CREATE)
						{
							// �u���b�N�ړ����[�V����
							m_pMotion->SetMotion(CMotion::MOTION_BLOCK_IDLE);
						}
						// �������łȂ��ꍇ
						if (m_Blcok_Active != BLOCK_ACTIVE_CREATE)
						{
							// �j���[�g�������[�V����
							m_pMotion->SetMotion(CMotion::MOTION_IDLE);
						}
					}
				}
				// �W�����v
				if (m_bJump == false)
				{
					// A�{�^�����������ꍇ
					if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_A))
					{
						// true��
						m_bJump = true;
						// false�̏ꍇ
						if (m_bJumpValue == false)
						{
							// �ړ�
							m_move.y += JUMP_VALUE;

							m_bJumpValue = true;
						}
						// true�̏ꍇ
						if (m_bJumpValue == true)
						{
							// �ړ�
							m_move.y += JUMP_VALUE_2;
						}
					}
				}
			}
			// true�̏ꍇ
			if (m_bMagic == true)
			{
				// �ړ��ʂ�0.0f��
				m_move.x = MIN_MOVE_VALUE;
			}
		}
	}
	// �E�������Ă�ꍇ
	if (m_Rot_State == ROT_STATE_RIGHT)
	{
		// ����
		RotDest.y = RIGHT_ROT.y;
	}
	// ���������Ă�ꍇ
	if (m_Rot_State == ROT_STATE_LEFT)
	{
		// ����
		RotDest.y = LEFT_ROT.y;
	}

	// ����
	m_rot += (RotDest - m_rot) * ROT_MOVE;

	// �d��
	m_move.y += GRAVITY_VALUE;

	// �ړ�
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
}
//******************************************************************************
// ���@�����֐�
//******************************************************************************
void CPlayer::Magic(void)
{
	//�T�E���h�擾
	CSound * pSound = CManager::GetSound();

	// �R���g���[���[�擾
	DIJOYSTATE js;
	js.lY = INIT_INT;
	js.lX = INIT_INT;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	// false�̏ꍇ
	if (m_bMagic == false)
	{
		// B���������ꍇ�{�^�����������ꍇ
		if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_B))
		{
			// true��
			m_bMagic = true;

			// ���@�U�����[�V����
			m_pMotion->SetMotion(CMotion::MOTION_MAGIC_ACTION);
		}
		// �t�@�C�A�[�{�[���̏ꍇ
		if (m_MagicType == MAGIC_TYPE_FIREBALL)
		{
			// false�̏ꍇ
			if (m_bChange_MagicType == false)
			{
				// RB�܂���LB�������ꂽ�ꍇ
				if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_RB) || pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_LB))
				{
					// true��
					m_bChange_MagicType = true;

					// �A�C�X�{�[����
					m_MagicType = MAGIC_TYPE_ICEBALL;

					// ���ˑ̐���
					Emitter_Create(EMITTER_TYPE_ICE);
				}
			}
			// true�̏ꍇ
			if (m_bChange_MagicType == true)
			{
				// RB�܂���LB�������ꂽ�ꍇ
				if (pInputJoystick->GetJoystickRelease(CInputJoystick::JS_RB) || pInputJoystick->GetJoystickRelease(CInputJoystick::JS_LB))
				{
					// false��
					m_bChange_MagicType = false;
				}
			}
		}
		// �A�C�X�{�[���̏ꍇ
		if (m_MagicType == MAGIC_TYPE_ICEBALL)
		{
			// false�̏ꍇ
			if (m_bChange_MagicType == false)
			{
				// RB�܂���LB�������ꂽ�ꍇ
				if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_RB) || pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_LB))
				{
					// true��
					m_bChange_MagicType = true;

					// �t�@�C�A�[�{�[����
					m_MagicType = MAGIC_TYPE_FIREBALL;

					// ���ˑ̐���
					Emitter_Create(EMITTER_TYPE_FIRE);
				}
			}
			// true�̏ꍇ
			if (m_bChange_MagicType == true)
			{
				// RB�܂���LB�������ꂽ�ꍇ
				if (pInputJoystick->GetJoystickRelease(CInputJoystick::JS_RB) || pInputJoystick->GetJoystickRelease(CInputJoystick::JS_LB))
				{
					// false��
					m_bChange_MagicType = false;
				}
			}
		}
	}
	// true�̏ꍇ
	if (m_bMagic == true)
	{
		// �C���N�������g
		m_nMotion_Count++;

		// 30�J�E���g�ɂȂ����ꍇ
		if (m_nMotion_Count == MAGIC_MOTION_COUNT)
		{
			// false��
			m_bMagic = false;

			// �E�����̏ꍇ
			if (m_Rot_State == ROT_STATE_RIGHT)
			{
				// �t�@�C�A�{�[���̏ꍇ
				if (m_MagicType == MAGIC_TYPE_FIREBALL)
				{
					// �΂̋����Đ�
					pSound->PlaySoundA(CSound::SOUND_LABEL_SE_FIRE_BALL);

					// �t�@�C�A�[�{�[������
					CMagic::Create(MAGIC_POS, MAGIC_MOVE_RIGHT, CMagic::TYPE_FIRE_BALL);
				}
				// �A�C�X�{�[���̏ꍇ
				if (m_MagicType == MAGIC_TYPE_ICEBALL)
				{
					// �΂̋����Đ�
					pSound->PlaySoundA(CSound::SOUND_LABEL_SE_FIRE_BALL);

					// �A�C�X�{�[���̐���
					CMagic::Create(MAGIC_POS, MAGIC_MOVE_RIGHT, CMagic::TYPE_ICE_BALL);
				}
			}
			// �������̏ꍇ
			if (m_Rot_State == ROT_STATE_LEFT)
			{
				// �t�@�C�A�{�[���̏ꍇ
				if (m_MagicType == MAGIC_TYPE_FIREBALL)
				{
					// �΂̋����Đ�
					pSound->PlaySoundA(CSound::SOUND_LABEL_SE_FIRE_BALL);

					// �t�@�C�A�[�{�[������
					CMagic::Create(MAGIC_POS, MAGIC_MOVE_LEFT, CMagic::TYPE_FIRE_BALL);
				}
				// �A�C�X�{�[���̏ꍇ
				if (m_MagicType == MAGIC_TYPE_ICEBALL)
				{
					// �΂̋����Đ�
					pSound->PlaySoundA(CSound::SOUND_LABEL_SE_FIRE_BALL);

					// �A�C�X�{�[���̐���
					CMagic::Create(MAGIC_POS, MAGIC_MOVE_LEFT, CMagic::TYPE_ICE_BALL);
				}
			}
			// ������
			m_nMotion_Count = INIT_INT;
		}
	}
}
//******************************************************************************
// ���ˑ̐����֐�
//******************************************************************************
void CPlayer::Emitter_Create(EMITTER_TYPE EmitterType)
{
	// NULL�̏ꍇ
	if (m_apParticle_Emitter[PARTICLE_EMITTER_RIGHT] == NULL && m_apParticle_Emitter[PARTICLE_EMITTER_LEFT] == NULL)
	{
		// ���
		m_Emitter_Type = EmitterType;

		// ���̏ꍇ
		if (m_Emitter_Type == EMITTER_TYPE_STAR)
		{
			// �E��
			m_apParticle_Emitter[PARTICLE_EMITTER_RIGHT] = CParticle_Emitter::Create(EMITTER_POS_RIGHT, CParticle_Emitter::TYPE_STAR_RIGHT);

			// ����
			m_apParticle_Emitter[PARTICLE_EMITTER_LEFT] = CParticle_Emitter::Create(EMITTER_POS_LEFT, CParticle_Emitter::TYPE_STAR_LEFT);
		}
		// �΂̏ꍇ
		if (m_Emitter_Type == EMITTER_TYPE_FIRE)
		{
			// �E��
			m_apParticle_Emitter[PARTICLE_EMITTER_RIGHT] = CParticle_Emitter::Create(EMITTER_POS_RIGHT, CParticle_Emitter::TYPE_FIRE_RIGHT);

			// ����
			m_apParticle_Emitter[PARTICLE_EMITTER_LEFT] = CParticle_Emitter::Create(EMITTER_POS_LEFT, CParticle_Emitter::TYPE_FIRE_LEFT);
		}
		// �X�̏ꍇ
		if (m_Emitter_Type == EMITTER_TYPE_ICE)
		{
			// �E��
			m_apParticle_Emitter[PARTICLE_EMITTER_RIGHT] = CParticle_Emitter::Create(EMITTER_POS_RIGHT, CParticle_Emitter::TYPE_ICE_RIGHT);

			// ����
			m_apParticle_Emitter[PARTICLE_EMITTER_LEFT] = CParticle_Emitter::Create(EMITTER_POS_LEFT, CParticle_Emitter::TYPE_ICE_LEFT);
		}
	}
	// NULL�łȂ��ꍇ
	if (m_apParticle_Emitter[PARTICLE_EMITTER_RIGHT] != NULL && m_apParticle_Emitter[PARTICLE_EMITTER_LEFT] != NULL)
	{
		// ������ނłȂ��ꍇ
		if (m_Emitter_Type != EmitterType)
		{
			// ���
			m_Emitter_Type = EmitterType;

			// 2��J��Ԃ�
			for (int nCnt = INIT_INT; nCnt < PARTICLE_EMITTER_MAX; nCnt++)
			{
				// �j��
				m_apParticle_Emitter[nCnt]->Release();

				// NULL��
				m_apParticle_Emitter[nCnt] = NULL;
			}

			// NULL�̏ꍇ
			if (m_apParticle_Emitter[PARTICLE_EMITTER_RIGHT] == NULL && m_apParticle_Emitter[PARTICLE_EMITTER_LEFT] == NULL)
			{
				// ���̏ꍇ
				if (m_Emitter_Type == EMITTER_TYPE_STAR)
				{
					// �E��
					m_apParticle_Emitter[PARTICLE_EMITTER_RIGHT] = CParticle_Emitter::Create(EMITTER_POS_RIGHT, CParticle_Emitter::TYPE_STAR_RIGHT);

					// ����
					m_apParticle_Emitter[PARTICLE_EMITTER_LEFT] = CParticle_Emitter::Create(EMITTER_POS_LEFT, CParticle_Emitter::TYPE_STAR_LEFT);
				}
				// �΂̏ꍇ
				if (m_Emitter_Type == EMITTER_TYPE_FIRE)
				{
					// �E��
					m_apParticle_Emitter[PARTICLE_EMITTER_RIGHT] = CParticle_Emitter::Create(EMITTER_POS_RIGHT, CParticle_Emitter::TYPE_FIRE_RIGHT);

					// ����
					m_apParticle_Emitter[PARTICLE_EMITTER_LEFT] = CParticle_Emitter::Create(EMITTER_POS_LEFT, CParticle_Emitter::TYPE_FIRE_LEFT);
				}
				// �X�̏ꍇ
				if (m_Emitter_Type == EMITTER_TYPE_ICE)
				{
					// �E��
					m_apParticle_Emitter[PARTICLE_EMITTER_RIGHT] = CParticle_Emitter::Create(EMITTER_POS_RIGHT, CParticle_Emitter::TYPE_ICE_RIGHT);

					// ����
					m_apParticle_Emitter[PARTICLE_EMITTER_LEFT] = CParticle_Emitter::Create(EMITTER_POS_LEFT, CParticle_Emitter::TYPE_ICE_LEFT);
				}
			}
		}
	}
}
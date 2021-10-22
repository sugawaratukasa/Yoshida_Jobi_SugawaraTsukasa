//******************************************************************************
// �v���C���[�̏��� [player.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _PLAYER_H_
#define _PLAYER_H_

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "scene.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define MAX_PLAYER_PARTS	(15)							// �v���C���[�̃��f���̃p�[�c�̍ő吔
#define MAX_MATERIAL		(50)							// �}�e���A���̍ő�
#define MAX_BLOCK			(3)								// �u���b�N���̍ő吔
//******************************************************************************
// �O���錾
//******************************************************************************
class CMotion;
class CModel;
class CBlock;
class CStone_Block;
class CParticle_Emitter;
//******************************************************************************
// �v���C���[�N���X
//******************************************************************************
class CPlayer :public CScene
{
public:
	// �v���C���[�p�[�c
	typedef enum
	{
		PARTS_UNDER_BODY = 0,	// ��
		PARTS_BODY,				// ���
		PARTS_HEAD,				// ��
		PARTS_SHOULDER_R,		// �E��
		PARTS_UP_ARM_R,			// �E��r
		PARTS_DOWN_ARM_R,		// �E�O�r
		PARTS_SHOULDER_L,		// ����
		PARTS_UP_ARM_L,			// ����r
		PARTS_DOWN_ARM_L,		// ���O�r
		PARTS_THIGTS_R,			// �E������
		PARTS_KNEE_R,			// �E�G
		PARTS_FOOT_R,			// �E��
		PARTS_THIGTS_L,			// ��������
		PARTS_KNEE_L,			// ���G
		PARTS_FOOT_L,			// ����
		PARTS_MAX				// �ő吔
	}PLAYER_PARTS;

	// ���[�V����
	typedef enum {
		MOTION_IDLE = 0,// �ҋ@���[�V����
		MOTION_RUN,		// �������[�V����
		MOTION_JUMP,	// �W�����v���[�V����
		MOTION_LANDING,	// ���n���[�V����
		MOTION_MAX		// �ő吔
	}MOTIONSTATE;

	// �u���b�N��p���Ă̍s���̎��
	typedef enum
	{
		BLOCK_ACTIVE_NONE = 0,	// �u���b�N��p���čs�������Ă��Ȃ����
		BLOCK_ACTIVE_CREATE,	// �u���b�N������
		BLOCK_ACTIVE_MOVE,		// �u���b�N���ړ������Ă�����
		BLOCK_ACTIVE_SELECT,	// �u���b�N��I�����Ă�����
		BLOCK_ACTIVE_SELECTED,	// �u���b�N��I���������
		BLOCK_ACTIVE_MAX		// �ő吔
	}BLOCK_ACTIVE;

	// �v���C���[�̌���
	typedef enum
	{
		ROT_STATE_RIGHT = 0,// �E�������Ă�����
		ROT_STATE_LEFT,		// ���������Ă�����
		ROT_STATE_MAX		// �ő吔
	}ROT_STATE;

	// �p�[�e�B�N���G�~�b�^�[
	enum PARTICLE_EMITTER
	{
		PARTICLE_EMITTER_NONE = -1,		// �ŏ�
		PARTICLE_EMITTER_RIGHT,			// �E
		PARTICLE_EMITTER_LEFT,			// ��
		PARTICLE_EMITTER_MAX			// �ő�
	};

	// ���ˑ̂̎��
	enum EMITTER_TYPE
	{
		EMITTER_TYPE_NONE = -1,
		EMITTER_TYPE_STAR,
		EMITTER_TYPE_FIRE,
		EMITTER_TYPE_ICE,
		EMITTER_TYPE_MAX
	};

	// ���@�̎��
	enum MAGIC_TYPE
	{
		MAGIC_TYPE_FIREBALL = 0,
		MAGIC_TYPE_ICEBALL,
		MAGIC_TYPE_MAX
	};

	CPlayer(int nPriority = CScene::OBJTYPE_PLAYER);
	~CPlayer();
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(int nLife);
	void SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	BLOCK_ACTIVE GetBlockActive(void) { return m_Blcok_Active; }
	D3DXMATRIX GetMtxWorld(PLAYER_PARTS Parts);
	int GetLife(void) { return m_nLife; }
	ROT_STATE GetRotState(void) { return m_Rot_State; }
	MAGIC_TYPE GetMagicType(void) { return m_MagicType; }
private:
	void RightSelectBlock(void);
	void RightBlock(void);
	void RightSelectionBlock(void);

	void LeftSelectBlock(void);
	void LeftBlock(void);
	void LeftSelectionBlock(void);

	void Block_Create(void);
	void Collision(void);
	void Move(void);
	void Magic(void);
	void Emitter_Create(EMITTER_TYPE EmitterType);

	static LPD3DXMESH m_pMesh[PARTS_MAX];							// ���b�V�����̃|�C���^
	static LPD3DXBUFFER m_pBuffMat[PARTS_MAX];						// �}�e���A�����̃|�C���^
	static DWORD m_nNumMat[PARTS_MAX];								// �}�e���A�����̐�
	static D3DXMATRIX m_mtxWorld[PARTS_MAX];						// �s��v�Z�p
	static int m_nldxModelParent[PARTS_MAX];						// �e���f���̃C���f�b�N�X
	static char* m_apFileName[PARTS_MAX];							// �t�@�C���̖��O
	static char* m_apTextureFileName[PARTS_MAX];					// �e�N�X�`���̃t�@�C���̖��O
	D3DXVECTOR3 m_pos;												// �ʒu
	D3DXVECTOR3 m_posOld;											// �Â��ʒu
	D3DXVECTOR3 m_RespawnPos;										// ���X�|�[���ʒu
	D3DXVECTOR3 m_rot;												// �p�x
	D3DXVECTOR3 m_size;												// �傫��
	D3DXVECTOR3 m_move;												// �ړ���
	bool m_bAllMotion;												// �S���[�V�����̔���
	CMotion *m_pMotion;												// ���[�V�����N���X�̃|�C���^
	CModel *m_pModel[PARTS_MAX];									// ���f���N���X�̃|�C���^
	CBlock *m_pBlock;												// ���̃|�C���^
	CStone_Block *m_pStoneBlock;									// �΂̔��̃|�C���^
	CParticle_Emitter *m_apParticle_Emitter[PARTICLE_EMITTER_MAX];	// �p�[�e�B�N���G�~�b�^�[�̃|�C���^
	BLOCK_ACTIVE m_Blcok_Active;									// ����p���Ă̈ړ�
	ROT_STATE m_Rot_State;											// �����̏��
	MAGIC_TYPE m_MagicType;											// ���@�̎��
	EMITTER_TYPE m_Emitter_Type;									// ���ˑ̂̎��
	int m_nBlockNum;												// ���̐�
	int m_nBlock_Select_Num;										// ���̑I������
	int m_nSelect_Save_Num;											// ���̐���ۑ�����
	int m_nMotion_Count;											// ���[�V�����J�E���g
	int m_nLife;													// �̗�
	bool m_bStick;													// �X�e�B�b�N����
	bool m_bRot;													// ����
	bool m_bJump;													// �W�����v����
	bool m_bJumpValue;												// �W�����v�ʔ���
	bool m_bBlock_Move;												// �u���b�N�̈ړ�����
	bool m_bMagic;													// ���[�V��������
	bool m_bParticle_Emitter;										// �G�~�b�^�[�̎g�p����
	bool m_bCollision;												// �I�u�W�F�^�C�v�ɓ������Ă��邩
	bool m_bChange_MagicType;										// ���@�̃^�C�v�ύX����
	bool m_bEnemyCreate;											// �G��������
	bool m_bDash;													// �_�b�V��
	bool m_bEnd;													// �I������
};
#endif
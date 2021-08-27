//******************************************************************************
// ���@ [player.cpp]
// Author : �ǌ��@�i
//******************************************************************************
#define	_CRT_SECURE_NO_WARNINGS	//scanf�G���[
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "../System/main.h"
#include "../System/manager.h"
#include "../System/renderer.h"
#include "../System/scene.h"
#include "../System/scene2d.h"
#include "../Input/input.h"
#include "../Input/inputkeyboard.h"
#include "../Input/inputjoystick.h"
#include "player.h"
#include "player_wepon.h"
#include "../Bullet/bullet.h"
#include "../Bullet/normal_bullet.h"
#include "../Beam/player_beam.h"
#include "../System/sound.h"
#include "../UI/life.h"
#include "../Mode/game.h"
#include "../UI/bomui.h"
#include "../UI/continue.h"
#include "../Bullet/bom.h"
#include "../UI/score.h"
#include "../Particle/particle.h"
#include "../Particle/particle_explosion.h"
#include "../Boss/boss.h"
#include "../Beam/beam.h"
#include "../Particle/particle_circle.h"
#include "../Beam/bom_beam.h"
#include <stdio.h>
//******************************************************************************
// �}�N����`
//******************************************************************************
#define PLAYER_TEXTURE					("data/Texture/Player/Player003.png")					// �e�N�X�`��
#define BULLET_NORMAL_MOVE_VALUE		(D3DXVECTOR3(0.0f,15.0f,0.0f))							// �ʏ�e�ړ���
#define BEAM_BULLET_MOVE_VALUE			(D3DXVECTOR3(0.0f,15.0f,0.0f))							// �r�[���ړ���
#define EXPLOSION_SIZE					(D3DXVECTOR3(3.0f,3.0f,0.0f))							// �����T�C�Y
#define PLAYER_SIZE						(D3DXVECTOR3(50.0f,50.0f,0.0f))							// �v���C���[�T�C�Y
#define PLAYER_COLLISION_SIZE			(D3DXVECTOR3(5.0f,5.0f,0.0f))							// �v���C���[����T�C�Y
#define PLAYER_MOVE						(D3DXVECTOR3(8.0f,8.0f,0.0f))							// �v���C���[�T�C�Y
#define PLAYER_BEAM_MOVE				(D3DXVECTOR3(5.0f,5.0f,0.0f))							// �v���C���[�r�[���T�C�Y
#define PLAYER_COLLISION_SIZE			(D3DXVECTOR3(5.0f,5.0f,0.0f))							// �v���C���[����T�C�Y
#define PLAYER_DEATH_POS				(D3DXVECTOR3(-100.0f, -100.0f, 0.0f))					// ���S���̈ʒu
#define PLAYER_RESPAWN_POS				(D3DXVECTOR3(SCREEN_WIDTH / 2, 600.0f, 0.0f))			// ���X�|���ʒu
#define BEAM_POS						(D3DXVECTOR3(0.0f,-45.0f,0.0f))							// �r�[�������ʒu
#define BULLET_ROT						(D3DXVECTOR3(0.0f,0.0f,0.0f))							// �e�̌���
#define CONTINUE_POS					(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))// �R���e�B�j���[�ʒu
#define CONTINUE_SIZE					(D3DXVECTOR3(250.0f,250.0f,0.0f))						// �T�C�Y
#define PLAYER_WEPON_POS				(D3DXVECTOR3(40.0f,40.0f,0.0f))							// �v���C���[����̈ʒu
#define PLAYER_BEAM_WEPON_POS			(D3DXVECTOR3(15.0f,40.0f,0.0f))							// �v���C���[����̈ʒu
#define PLAYER_WEPON_SIZE				(D3DXVECTOR3(25.0f,25.0f,0.0f))							// �v���C���[����T�C�Y
#define BULLET_LEVEL1_BEAM_SIZE			(D3DXVECTOR3(40.0f,40.0f,0.0f))							//�r�[���̃T�C�Y
#define BULLET_LEVEL2_BEAM_SIZE			(D3DXVECTOR3(50.0f,50.0f,0.0f))							//�r�[���̃T�C�Y
#define BULLET_LEVEL3_BEAM_SIZE			(D3DXVECTOR3(60.0f,60.0f,0.0f))							//�r�[���̃T�C�Y
#define BULLET_LEVEL1_SIZE				(D3DXVECTOR3(40.0f,40.0f,0.0f))							// ���x��1�̒e�̃T�C�Y
#define BULLET_LEVEL2_SIZE				(D3DXVECTOR3(50.0f,50.0f,0.0f))							// ���x��2�̒e�̃T�C�Y
#define BULLET_LEVEL3_SIZE				(D3DXVECTOR3(50.0f,50.0f,0.0f))							// ���x��3�̒e�̃T�C�Y
#define BOSS_BOM_SIZE					(D3DXVECTOR3(100.0f,100.0f,0.0f))						// �T�C�Y
#define BOSS_BOM_ROT					(D3DXVECTOR3(0.0f,0.0f,0.0f))							// �{���̌���
#define BOM_POS							(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f))	// �{���̈ʒu
#define BOM_SIZE						(D3DXVECTOR3(800.0f,800.0f,0.0f))						// �{���̃T�C�Y
#define BOM_ROT							(D3DXVECTOR3(0.0f,0.0f,0.0f))							// �{���̌���
#define COLOR							(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))						// �J���[
#define BULLET_COLOR					(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))						// �e�̐F
#define DAMAGE_COLOR					(D3DXCOLOR(1.0f,1.0f,1.0f,0.0f))						// �_���[�W��Ԃ̎��̐F
#define GET_BOM_ADD_SCORE				(5000)													// �{���擾���̉��Z�X�R�A�l
#define GET_POWERUP_ADD_SCORE			(3000)													// �p���[�A�b�v�A�C�e���擾���̉��Z�X�R�A�l
#define CONTINUE_SUB_SCORE				(-3000)													// �R���e�B�j���[���̃X�R�A���Z�l
#define JOYSTICK_DICISION				(500)													// �W���C�X�e�B�b�N����l
#define DAMAGE_COUNT					(300)													// �_���[�W�J�E���g
#define BOM_LAUNCH_TIME					(200)													// �{���̑ҋ@����
#define DAMAGE_RESPAWN_COUNT			(30)													// �_���[�W���X�|���J�E���g
#define NODAMAGE_COUNT					(50)													// ���G����
#define BEAM_COUNT						(20)													// �r�[���J�E���g
#define BEAM_SHOT_COUNT					(2)														// �r�[���̒e�����J�E���g
#define INIT_BEAM_COUNT					(0)														// �r�[���J�E���g������
#define INIT_BOM_COUNT					(0)														// �{���̃J�E���g������
#define NORMAL_ANIM_PATTERN_COUNT		(2)														// �ʏ펞�̃A�j���[�V�����p�^�[��
#define LEFT_MOVE_ANIM_PATTERN_COUNT	(0)														// ���ړ����̃A�j���[�V�����J�E���g
#define RIGHT_MOVE_ANIM_PATTERN_COUNT	(4)														// �E�ړ����̃A�j���[�V�����J�E���g
#define MAX_BOM_POSSESION				(5)														// �{���̍ő及����
#define MIN_BOM_POSSESION				(0)														// �{���̍ő及����
#define HIT_DAMAGE_VALUE				(1)														// �_���[�W��
#define PLAYER_LIFE						(3)														// �v���C���[���C�t
#define PLAYER_CONTINUE					(1)														// �v���C���[�̃R���e�B�j���[
#define DEVIDE_VALUE					(2)														// ���Z�l
#define REMAINDER_VALUE					(0)														// �]��l
#define INIT_PLAYER_RESPAWN_COUNT		(0)														// ���X�|�[���J�E���g������
#define DAMAGE_COUNT_VEVIDE1			(5)														// �_���[�W�J�E���g�̏��Z�l
#define DAMAGE_COUNT_VEVIDE2			(6)														// �_���[�W�J�E���g�̏��Z�l
#define INIT_DAMAGE_COUNT				(0)														// �_���[�W�J�E���g������
#define INIT_CONTINUE_COUNT				(0)														// �R���e�B�j���[�J�E���g������
#define MIN_LIFE_VALUE					(0)														// ���C�t�̍ŏ��l
#define CONTINUE_BOM_POSSETION			(3)														// �R���e�B�j���[���̃{���̏�����
#define SHOT_BOM						(-1)													// �{���̏����
#define RATE_MOVE_BASE					(0.0f)													// �����̈�����鐔��
#define RATE_MOVE						(0.4f)													// �����̈ړ���
#define TEX_1							(0.2f)													// �e�N�X�`��UV�l1
#define TEX_2							(0.0f)													// �e�N�X�`��UV�l2
#define TEX_3							(0.2f)													// �e�N�X�`��UV�l3
#define TEX_4							(1.0f)													// �e�N�X�`��UV�l4
#define CIRCLE_SIZE						(D3DXVECTOR3(30.0f,30.0f,0.0f))							// �~�`�p�[�e�B�N���T�C�Y
#define CIRCLE_CREATE_NUM				(30)													// �~�`�p�[�e�B�N��������
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;
//******************************************************************************
// �e�N�X�`���ǂݍ��݊֐�
//******************************************************************************
HRESULT CPlayer::Load(void)
{
	//�����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, PLAYER_TEXTURE, &m_pTexture);
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���j���֐�
//******************************************************************************
void CPlayer::Unload(void)
{
		// �e�N�X�`���̔j��
		if (m_pTexture != NULL)
		{
			// �e�N�X�`���̂�Release
			m_pTexture->Release();
			// �e�N�X�`���̂�NULL
			m_pTexture= NULL;
		}
}
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CPlayer::CPlayer(int nPriority) : CScene2d(nPriority)
{
	m_pBeam					= NULL;	
	m_pBomBeam				= NULL;
	m_nContinue				= INIT_INT;
	m_nLife					= INIT_INT;
	m_nCountAnim			= INIT_INT;
	m_nPatternAnim			= INIT_INT;
	m_AttackCount			= INIT_INT;
	m_nBeamCount			= INIT_INT;
	m_nDamageCount			= INIT_INT;
	m_nRespawnCount			= INIT_INT;
	m_nBomCount				= INIT_INT;
	m_nBom_possession_count = INIT_INT;
	m_nPlayerState			= STATE_NONE;
	m_nPower					= LEVEL_NONE;
	m_bMove					= false;
	m_bUseShot				= false;
	m_bUseBeam				= false;
	m_bUseBom				= false;
	m_bBossBom				= false;
	m_bBoss					= false;
	m_bBossDeath			= false;
	m_bContinue				= false;
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
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CPlayer�N���X�̃|�C���^
	CPlayer * pPlayer;																			

	// �������m��
	pPlayer = new CPlayer;

	// pos���
	pPlayer->SetPosition(pos);

	// �T�C�Y���
	pPlayer->SetSize(size);

	// �J���[�ݒ�
	pPlayer->SetRGBA(COLOR);

	// �e�N�X�`���ݒ�
	pPlayer->BindTexture(m_pTexture);

	// �I�u�W�F�N�g�^�C�v�ݒ�
	pPlayer->SetObjType(OBJTYPE_PLAYER);

	// ������
	pPlayer->Init();

	// pPlayer��Ԃ�
	return pPlayer;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CPlayer::Init(void)
{
	// �v���C���[�̃X�e�[�g�m�[�}��
	m_nPlayerState = STATE_NORMAL;

	// �����蔻��T�C�Y
	m_Collision_Size = PLAYER_COLLISION_SIZE;

	// ���x��1
	m_nPower = LEVEL_1;

	// �̗�
	m_nLife = PLAYER_LIFE;

	// ���퐶��
	// ��
	CPlayer_Wepon::Create(D3DXVECTOR3(-PLAYER_WEPON_POS.x, PLAYER_WEPON_POS.y, PLAYER_WEPON_POS.z), PLAYER_WEPON_SIZE, CPlayer_Wepon::TYPE_LEFT);

	// �E
	CPlayer_Wepon::Create(D3DXVECTOR3(PLAYER_WEPON_POS.x, PLAYER_WEPON_POS.y, PLAYER_WEPON_POS.z), PLAYER_WEPON_SIZE, CPlayer_Wepon::TYPE_RIGHT);

	// ������
	CScene2d::Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CPlayer::Uninit(void)
{
	// �I��
	CScene2d::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CPlayer::Update(void)
{
	// State���֌W���Ă��鏈��
	PlayerState();
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CPlayer::Draw(void)
{
	// �`��
	CScene2d::Draw();
}
//******************************************************************************
// �q�b�g�����֐�
//******************************************************************************
void CPlayer::HitPlayer(void)
{
	// ��Ԃ��m�[�}���̏ꍇ
	if (m_nPlayerState == STATE_NORMAL)
	{
		// �ʒu���W�擾
		D3DXVECTOR3 pos = GetPosition();

		// �T�E���h�擾
		CSound * pSound = CSceneManager::GetSound();
		CSound::SOUND_LABEL type;
		type = CSound::SOUND_LABEL_SE_SHOT;

		// ����������
		pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);

		// ���C�t�̎擾
		CLife * pLife = CGame::GetLife();

		// ���C�t���Z
		m_nLife--;

		// ���C�tUI�̌��Z
		pLife->HitDamage(HIT_DAMAGE_VALUE);

		// �����̐���
		CParticle_Explosion::CreateExplosionEffect(pos, EXPLOSION_SIZE, CParticle_Explosion::TYPE_PLAYER);

		// �p�[�e�B�N������
		CParticle_Circle::PlayerDeathEffect(pos, CIRCLE_SIZE, CIRCLE_CREATE_NUM);

		// �_���[�W���󂯂��ꍇ��ʊO��
		SetPosition(PLAYER_DEATH_POS);

		// State��Respawn��
		m_nPlayerState = STATE_RESPAWN;
	}
}
//******************************************************************************
// �{�����菈���֐�
//******************************************************************************
void CPlayer::GetBom(int nBom)
{
	// �{���擾
	CBomUI * pBom = CGame::GetBomUI();
	// �X�R�A�擾
	CScore * pScore = CGame::GetScore();

	// �{���̏������̉��Z���Z
	if (m_nBom_possession_count >= MIN_BOM_POSSESION && m_nBom_possession_count <= MAX_BOM_POSSESION)
	{
		// �{���̏��������Z
		m_nBom_possession_count += nBom;

		// �{���̏������ݒ�
		pBom->SetBomUI(m_nBom_possession_count);

	}
	// �{���̐���5��葽���Ȃ����ꍇ
	if (m_nBom_possession_count > MAX_BOM_POSSESION)
	{
		// �{���̐���5�ɐݒ�
		m_nBom_possession_count = MAX_BOM_POSSESION;

		// �{���̏������ݒ�
		pBom->SetBomUI(m_nBom_possession_count);
	}

	// �{���̏�������MAX�̏ꍇ
	if (m_nBom_possession_count >= MAX_BOM_POSSESION)
	{
		// �X�R�A���Z
		pScore->AddScore(GET_BOM_ADD_SCORE);
	}
}
//******************************************************************************
// �p���[�A�b�v�����֐�
//******************************************************************************
void CPlayer::GetPowerUp(void)
{
	CScore * pScore = CGame::GetScore();
	// ���x����3���Ⴂ�ꍇ
	if (m_nPower < LEVEL_3)
	{
		// ���x���A�b�v
		m_nPower++;
	}
	// ���x����3�̏ꍇ
	if (m_nPower == LEVEL_3)
	{
		// �X�R�A���Z
		pScore->AddScore(GET_POWERUP_ADD_SCORE);
	}
}
//******************************************************************************
// �R���e�B�j���[�����֐�
//******************************************************************************
void CPlayer::SetContinue(int Continue)
{
	// ���
	m_nContinue = Continue;
}
//******************************************************************************
// �v���C���[��񏑂����݊֐�
//******************************************************************************
void CPlayer::SavePlayer(void)
{
	// �t�@�C��
	FILE * pFile;

	// �t�@�C���̏����o��
	pFile = fopen("player.txt", "w");

	// �t�@�C�����󂶂�Ȃ���
	if (pFile != NULL)
	{
		// �X�R�A��������
		fprintf(pFile, "%d\n", m_nScore);

		// �t�@�C�������
		fclose(pFile);
	}
}
//******************************************************************************
// �{�X��p�{�������֐�
//******************************************************************************
void CPlayer::SetBossBom(bool bBoss)
{
	m_bBoss = bBoss;
}
//******************************************************************************
// �ړ������֐�
//******************************************************************************
void CPlayer::Move(void)
{
	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �ړ�
	D3DXVECTOR3 move = INIT_D3DXVECTOR3;

	// �L�[�{�[�h�擾
	CInputKeyboard * pInputKeyboard = CSceneManager::GetInputKeyboard();

	// �R���g���[���[�擾
	DIJOYSTATE js;
	CInputJoystick * pInputJoystick = CSceneManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	//���E�ړ����ĂȂ���
	if (m_bMove == false)
	{
		//�A�j���[�V�����p�^�[����2�ɂ���
		m_nPatternAnim = NORMAL_ANIM_PATTERN_COUNT;
	}
	// ��
	if (g_lpDIDevice != NULL &&js.lY <= -JOYSTICK_DICISION || pInputKeyboard->GetKeyboardPress(DIK_W))
	{
		//false��
		m_bMove = false;

		// �r�[���𔭎˂��Ă鎞
		if (m_bUseBeam == true)
		{
			// �ړ�
			move.y = -PLAYER_BEAM_MOVE.y;
		}
		// �r�[���𔭎˂��ĂȂ���
		else
		{
			// �ړ�
			move.y = -PLAYER_MOVE.y;
		}
	}
	// ��
	if (g_lpDIDevice != NULL &&js.lY >= JOYSTICK_DICISION || pInputKeyboard->GetKeyboardPress(DIK_S))
	{
		// false��
		m_bMove = false;

		// �r�[���𔭎˂��Ă鎞
		if (m_bUseBeam == true)
		{
			// �ړ�
			move.y = PLAYER_BEAM_MOVE.y;
		}
		// �r�[���𔭎˂��ĂȂ���
		else
		{
			// �ړ�
			move.y = PLAYER_MOVE.y;
		}
	}
	// ��
	if (g_lpDIDevice != NULL &&js.lX <= -JOYSTICK_DICISION || pInputKeyboard->GetKeyboardPress(DIK_A))
	{
		// true��
		m_bMove = true;

		// �r�[���𔭎˂��Ă���ꍇ
		if (m_bUseBeam == true)
		{
			// �ړ�
			move.x = -PLAYER_BEAM_MOVE.x;
		}
		// �r�[���𔭎˂��ĂȂ��ꍇ
		else
		{
			// �ړ�
			move.x = -PLAYER_MOVE.x;
		}

		// �A�j���[�V������0��
		m_nPatternAnim = LEFT_MOVE_ANIM_PATTERN_COUNT;
	}
	// ���Ɉړ����ĂȂ���
	else
	{
		m_bMove = false;
	}
	//�E
	if (g_lpDIDevice != NULL &&js.lX >= JOYSTICK_DICISION || pInputKeyboard->GetKeyboardPress(DIK_D))
	{
		// m_bMove��true��
		m_bMove = true;

		// �r�[���𔭎˂��Ă���ꍇ
		if (m_bUseBeam == true)
		{
			move.x = PLAYER_BEAM_MOVE.x;
		}
		// �r�[���𔭎˂��Ă��Ȃ��ꍇ
		else
		{
			move.x = PLAYER_MOVE.x;
		}

		// �A�j���[�V����
		m_nPatternAnim = RIGHT_MOVE_ANIM_PATTERN_COUNT;
	}
	// �E�Ɉړ����ĂȂ���
	else
	{
		m_bMove = false;
	}

	// �ʒu�X�V
	pos.x += move.x;
	pos.y += move.y;

	// ����
	move.x += (RATE_MOVE_BASE - move.x) * RATE_MOVE;
	move.y += (RATE_MOVE_BASE - move.y) * RATE_MOVE;

	// state��Normal�܂���Damage�̎�
	if (m_nPlayerState == STATE_NORMAL || m_nPlayerState == STATE_DAMAGE)
	{
		// ���ʊO�ɏo���Ƃ�
		if (pos.y - PLAYER_SIZE.y < WINDOW_POS_Y)
		{
			// �v���C���[�̃T�C�Y�����炷
			pos.y = PLAYER_SIZE.y;
		}
		// �����v���C���[������ʊO�ɍs������
		if (pos.y + PLAYER_SIZE.y > SCREEN_HEIGHT)
		{
			// �v���C���[�̃T�C�Y�����炷
			pos.y = SCREEN_HEIGHT - PLAYER_SIZE.y;
		}
		// �����v���C���[������ʊO�ɍs������
		if (pos.x - PLAYER_SIZE.x - PLAYER_WEPON_SIZE.x / DEVIDE_VALUE < MIN_GAME_WIDTH)
		{
			// �v���C���[�ƕ���̃T�C�Y�����炷
			pos.x = MIN_GAME_WIDTH + PLAYER_SIZE.x + PLAYER_WEPON_SIZE.x / DEVIDE_VALUE;
		}
		// �����v���C���[���E��ʊO�ɍs������
		if (pos.x + PLAYER_SIZE.x + PLAYER_WEPON_SIZE.x / DEVIDE_VALUE > MAX_GAME_WIDTH)
		{
			// �v���C���[�ƕ���̃T�C�Y�����炷
			pos.x = MAX_GAME_WIDTH - PLAYER_SIZE.x - PLAYER_WEPON_SIZE.x / DEVIDE_VALUE;
		}
	}
	// �ʒu�ݒ�
	SetPosition(pos);
}
//******************************************************************************
// �e���ˏ����֐�
//******************************************************************************
void CPlayer::Shot(void)
{
	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �L�[�{�[�h�擾
	CInputKeyboard * pInputKeyboard = CSceneManager::GetInputKeyboard();

	// �R���g���[���[�擾
	CInputJoystick * pInputJoystick = CSceneManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	// �T�E���h�擾
	CSound * pSound = CSceneManager::GetSound();
	CSound::SOUND_LABEL type;
	type = CSound::SOUND_LABEL_SE_SHOT;


	//*****************************************************************
	// �m�[�}���e�̏���
	//*****************************************************************
	// �{�����g�p���ĂȂ��ꍇ
	if (m_bUseBom == false)
	{
		// �r�[�����g�p���ĂȂ��ꍇ
		if (m_bUseBeam == false)
		{
			// �r�[��
			// SPACE�܂��̓R���g���[���[A�{�^��
			if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_A) || pInputKeyboard->GetKeyboardTrigger(DIK_SPACE))
			{
				// �V���b�g���g�p��Ԃ�
				m_bUseShot = true;

				// �V���b�g��
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);

				// �v���C���[���x����1�̏ꍇ
				if (m_nPower == LEVEL_1)
				{
					// �e�̐���
					CNormal_Bullet::Create(D3DXVECTOR3(pos),
						BULLET_ROT,
						BULLET_LEVEL1_SIZE,
						D3DXVECTOR3(BULLET_NORMAL_MOVE_VALUE.x, -BULLET_NORMAL_MOVE_VALUE.y, BULLET_NORMAL_MOVE_VALUE.z),
						BULLET_COLOR
						, CBullet::TEX_TYPE_NORMAL);
				}
				// �v���C���[���x����2�̏ꍇ
				if (m_nPower == LEVEL_2)
				{
					// �e�̐���
					CNormal_Bullet::Create(D3DXVECTOR3(pos),
						BULLET_ROT,
						BULLET_LEVEL2_SIZE,
						D3DXVECTOR3(BULLET_NORMAL_MOVE_VALUE.x, -BULLET_NORMAL_MOVE_VALUE.y, BULLET_NORMAL_MOVE_VALUE.z),
						BULLET_COLOR,
						CBullet::TEX_TYPE_NORMAL);
				}
				// �v���C���[���x����3�̏ꍇ
				if (m_nPower == LEVEL_3)
				{
					// �e�̐���
					CNormal_Bullet::Create(D3DXVECTOR3(pos),
						BULLET_ROT,
						BULLET_LEVEL3_SIZE,
						D3DXVECTOR3(BULLET_NORMAL_MOVE_VALUE.x, -BULLET_NORMAL_MOVE_VALUE.y, BULLET_NORMAL_MOVE_VALUE.z),
						BULLET_COLOR,
						CBullet::TEX_TYPE_NORMAL);
				}

			}
			// �R���g���[���[A�{�^���܂��̓L�[�{�[�hSPACE�𗣂����ꍇ
			if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickRelease(CInputJoystick::JS_A) || pInputKeyboard->GetKeyboardRelease(DIK_SPACE))
			{
				// �ʏ�e�̕s�g�p��Ԃ�
				m_bUseShot = false;
			}
		}

		//*****************************************************************
		// �r�[�����˂̏���
		//*****************************************************************

		//�r�[��
		//SPACE�������܂��̓R���g���[���[A�{�^��
		if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickPress(CInputJoystick::JS_A) || pInputKeyboard->GetKeyboardPress(DIK_SPACE))
		{
			// false�̏ꍇ
			if (m_bUseBeam == false)
			{
				//�r�[���J�E���g�C���N�������g
				m_nBeamCount++;
				//�J�E���g��20�ȏ�̎�
				if (m_nBeamCount == BEAM_COUNT)
				{
					// �r�[����
					pSound->PlaySound(CSound::SOUND_LABEL_SE_BEAM);

					//�r�[����bool��true��
					m_bUseBeam = true;
				}
			}
		}
		// �r�[����bool��true�̎�
		if (m_bUseBeam == true)
		{
			// NULL�̏ꍇ
			if (m_pBeam == NULL)
			{
				// ���x��1�̏ꍇ
				if (m_nPower == LEVEL_1)
				{
					// �r�[������
					m_pBeam = CPlayer_Beam::Create(D3DXVECTOR3(pos.x, pos.y + BEAM_POS.y, pos.z),
						BULLET_LEVEL1_BEAM_SIZE);
				}
				// ���x��2�̏ꍇ
				if (m_nPower == LEVEL_2)
				{
					// �r�[������
					m_pBeam = CPlayer_Beam::Create(D3DXVECTOR3(pos.x, pos.y + BEAM_POS.y, pos.z),
						BULLET_LEVEL2_BEAM_SIZE);
				}
				// ���x��3�̏ꍇ
				if (m_nPower == LEVEL_3)
				{
					// �r�[������
					m_pBeam = CPlayer_Beam::Create(D3DXVECTOR3(pos.x, pos.y + BEAM_POS.y, pos.z),
						BULLET_LEVEL3_BEAM_SIZE);
				}
			}
		}
		// SPACE�܂��̓R���g���[��A�{�^���𗣂����Ƃ�
		if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickRelease(CInputJoystick::JS_A) || pInputKeyboard->GetKeyboardRelease(DIK_SPACE))
		{
			// true�̏ꍇ
			if (m_bUseBeam == true)
			{
				// NULL�̏ꍇ
				if (m_pBeam != NULL)
				{
					// �r�[���j��
					m_pBeam->ReleaseAllBeam();

					// NULL��
					m_pBeam = NULL;
				}

				// �J�E���g��0��
				m_nBeamCount = INIT_BEAM_COUNT;

				// �r�[������~
				pSound->StopSound(CSound::SOUND_LABEL_SE_BEAM);

				// �r�[��bool��false��
				m_bUseBeam = false;
			}
		}
		// �L�[�{�[�h��B�܂��̓R���g���[����B�{�^�����������ꍇ
		if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_B) || pInputKeyboard->GetKeyboardTrigger(DIK_B))
		{
			// �{����������0��葽���ꍇ
			if (m_nBom_possession_count > MIN_BOM_POSSESION)
			{
				// �{��bool��true��
				m_bUseBom = true;

				// �{���̏��������Z
				GetBom(SHOT_BOM);
			}
		}
	}
	// �{�����g�p���̏ꍇ
	if (m_bUseBom == true)
	{
		// �{�X��łȂ���
		if (m_bBoss == false)
		{
			// ����������
			pSound->PlaySound(CSound::SOUND_LABEL_SE_BOM);

			// �{������
			CBom::Create(BOM_POS, BOM_ROT, BOM_SIZE, CBullet::TEX_TYPE_BOM);

			// false��
			m_bUseBom = false;
		}
		// �{�X��̎�
		else
		{
			// NULL�̏ꍇ
			if (m_pBeam != NULL)
			{
				// �r�[���j��
				m_pBeam->ReleaseAllBeam();

				// NULL��
				m_pBeam = NULL;
			}
			// false�̏ꍇ
			if (m_bBossBom == false)
			{
				// NULL�łȂ��ꍇ
				if (m_pBomBeam == NULL)
				{
					// �e�̐���
					m_pBomBeam = CBom_Beam::Create(D3DXVECTOR3(pos.x, pos.y + BEAM_POS.y, pos.z), BOSS_BOM_SIZE);
				}
				// �{�X��p�̃{�����g�p��Ԃ�
				m_bBossBom = true;
			}
			// true�̏ꍇ
			if (m_bBossBom == true)
			{
				// �{���̃J�E���g���C���N�������g
				m_nBomCount++;

				// �J�E���g��200�ȏ�ɂȂ�����
				if (m_nBomCount >= BOM_LAUNCH_TIME)
				{
					// �{���̎g�p��Ԃ�false��
					m_bUseBom = false;

					// false��
					m_bBossBom = false;

					// �{���̃J�E���g��0��
					m_nBomCount = INIT_BOM_COUNT;

					// NULL�łȂ��ꍇ
					if (m_pBomBeam != NULL)
					{
						// �r�[���j��
						m_pBomBeam->ReleaseAllBeam();

						// NULL��
						m_pBomBeam = NULL;
					}
				}
			}
		}
	}
}

//******************************************************************************
// �v���C���[�̏�ԏ����֐�
//******************************************************************************
void CPlayer::PlayerState(void)
{
	//���S��ԂłȂ���
	if (m_nPlayerState != STATE_DEAD)
	{
		// �X�V
		CScene2d::Update();

		//���@�̒��S
		D3DXVECTOR3 pos = GetPosition();

		//�e�N�X�`���X�V
		SetTexture(m_nPatternAnim * TEX_1, TEX_2, TEX_3, TEX_4);
	
		//�X�R�A�擾
		CScore * pScore = CGame::GetScore();
		m_nScore = pScore->GetScore();

		// �v���C���[�̏����O���t�@�C���ɏ�������
		SavePlayer();

		// �ړ�����
		Move();

		// �e���ˏ���
		Shot();

		//�ʏ���
		if (m_nPlayerState == STATE_NORMAL)
		{
			//�J���[�ݒ�
			SetRGBA(COLOR);
		}
		//���X�|�[�����
		if (m_nPlayerState == STATE_RESPAWN)
		{
			//�J�E���g�C���N�������g
			m_nRespawnCount++;

			//�J�E���g��30�ɂȂ����Ƃ�
			if (m_nRespawnCount == DAMAGE_RESPAWN_COUNT)
			{
				// �_���[�W��Ԃ�
				m_nPlayerState = STATE_DAMAGE;

				// ���X�|���ʒu�ݒ�
				SetPosition(PLAYER_RESPAWN_POS);

				// �J�E���g��0��
				m_nRespawnCount = INIT_PLAYER_RESPAWN_COUNT;
			}
		}
		// �_���[�W���
		if (m_nPlayerState == STATE_DAMAGE)
		{
			// �J�E���g�C���N�������g
			m_nDamageCount++;
			// �_���[�W�̃J�E���g��5���܂�0�ɂȂ�����
			if (m_nDamageCount % DAMAGE_COUNT_VEVIDE1 == REMAINDER_VALUE)
			{
				// �J���[�ݒ�
				SetRGBA(COLOR);
			}
			// �_���[�W�̃J�E���g��6���܂�0�ɂȂ�����
			if (m_nDamageCount % DAMAGE_COUNT_VEVIDE2 == REMAINDER_VALUE)
			{
				// �J���[�ݒ�
				SetRGBA(DAMAGE_COLOR);

			}
			// ���G���Ԃ��I��������
			if (m_nDamageCount == DAMAGE_COUNT)
			{
				// �J���[�ݒ�
				SetRGBA(COLOR);

				// state��Normal��
				m_nPlayerState = STATE_NORMAL;

				// �J�E���g��0��
				m_nDamageCount = INIT_DAMAGE_COUNT;
			}
		}
		// �R���e�B�j���[��Ԃ�false�̎�
		if (m_bContinue == false)
		{
			// ���C�t��0�ȉ��̎�
			if (m_nLife <= MIN_LIFE_VALUE)
			{
				// �R���e�B�j���[��Ԃ�true��
				m_bContinue = true;
			}
		}
		// �R���e�B�j���[��Ԃ�true��
		if (m_bContinue == true)
		{
			// �R���e�B�j���[���� 
			CContinue::Create(CONTINUE_POS, CONTINUE_SIZE);

			// ���S��Ԃ�
			m_nPlayerState = STATE_DEAD;
		}
		// �{�X������ꍇ
		if (m_bBoss == true)
		{
			// �v���C���[�̎擾
			CBoss * pBoss = CGame::GetBoss();

			// NULL�`�F�b�N
			if (pBoss != NULL)
			{
				// ��Ԏ擾
				int BossState = pBoss->GetState();

				// �{�X�����S��Ԃ̏ꍇ
				if (BossState == CBoss::STATE_DEATH_EFFECT || BossState == CBoss::STATE_DEATH)
				{
					// true��
					m_bBossDeath = true;
				}
			}
		}
	}
	// ���S��Ԃ̏ꍇ
	if (m_nPlayerState == STATE_DEAD)
	{
		// ��ʊO�Ɉړ�������
		SetPosition(PLAYER_DEATH_POS);

		// �R���e�B�j���[�����ꍇ
		if (m_nContinue == PLAYER_CONTINUE)
		{
			// �X�R�A�擾
			CScore * pScore = CGame::GetScore();

			// �X�R�A���Z
			pScore->AddScore(CONTINUE_SUB_SCORE);

			// ���C�t�̎擾
			CLife * pLife = CGame::GetLife();

			// ���C�t��3��
			m_nLife = PLAYER_LIFE;

			// ���C�t��ݒ�
			pLife->AddLife(m_nLife);

			// �{���̏�������3��
			GetBom(CONTINUE_BOM_POSSETION);

			// �R���e�B�j���[��Ԃ�false��
			m_bContinue = false;

			// �R���e�B�j���[�̃J�E���g��0��
			m_nContinue = INIT_CONTINUE_COUNT;

			// ���X�|�[����Ԃ�
			m_nPlayerState = STATE_RESPAWN;
		}
	}
}
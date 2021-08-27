//******************************************************************************
// �Q�[�� [game.cpp]
// Author : �ǌ� �i
//******************************************************************************

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
#include "../Player/player.h"
#include "../Bullet/bullet.h"
#include "../Polygon/bg.h"
#include "../System/sound.h"
#include "../Enemy/enemy.h"
#include "../Enemy/normal_enemy.h"
#include "../Enemy/circle_bullet_enemy.h"
#include "../System/number.h"
#include "../UI/score.h"
#include "../UI/life.h"
#include "game.h"
#include "../Polygon/fade.h"
#include "../Polygon/item.h"
#include "../UI/bomui.h"
#include "../Polygon/polygon.h"
#include "../Enemy/ship.h"
#include "../Boss/boss.h"
#include "warning.h"
#include "../Enemy/ship_battery.h"
#include "../Particle/particle.h"
#include "../Particle/particle_explosion.h"
#include "../Polygon/black_polygon.h"
#include "mode.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define PLAYER_POS					(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 + 200, 0.0))	// �v���C���[�̈ʒu
#define PLAYER_SIZE					(D3DXVECTOR3(50.0f,50.0f,0.0f))									// �v���C���[�T�C�Y
#define BOSS_POS					(D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f))					// �{�X�̈ʒu
#define BOSS_MAIN_SIZE				(D3DXVECTOR3(150.0f,150.0f,0.0f))								// �{�X�̒����̃T�C�Y
#define BG_POS						(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))		// �w�i�ʒu
#define SCORE_POS					(D3DXVECTOR3(940.0f, 50.0f, 0.0f))								// �X�R�A�ʒu
#define LIFE_POS					(D3DXVECTOR3(350.0f, 50.0f, 0.0f))								// ���C�t�ʒu
#define BOM_UI_POS					(D3DXVECTOR3(340.0f, 700.0f, 0.0f))								// �{����UI�ʒu
#define ENEMY_ROT					(D3DXVECTOR3(0.0f,0.0f,0.0f))									// �G�̌���
#define ENEMY_RESPWAN_POS_1			(D3DXVECTOR3(900.0f, -300.0f, 0.0f))							// �G�̐����ʒu1
#define ENEMY_RESPWAN_POS_2			(D3DXVECTOR3(540.0f, -150.0f, 0.0f))							// �G�̐����ʒu2
#define ENEMY_RESPAWN_POS_3			(D3DXVECTOR3(480.0f, -100.0f, 0.0f))							// �G�̐����ʒu3
#define ENEMY_RESPWAN_POS_4			(D3DXVECTOR3(840.0f, -100.0f, 0.0f))							// �G�̐����ʒu4
#define ENEMY_RESPWAN_POS_5			(D3DXVECTOR3(740.0f, -50.0f, 0.0f))								// �G�̐����ʒu5
#define ENEMY_RESPWAN_POS_6			(D3DXVECTOR3(600.0f, -100.0f, 0.0f))							// �G�̐����ʒu6
#define SHIP_RESPAWN_POS			(D3DXVECTOR3(SCREEN_WIDTH / 2, -1000.0f, 0.0f))					// �D�����ʒu
#define SHIP_SIZE					(D3DXVECTOR3(1000.0f,1800.0f,0.0f))								// �D�̃T�C�Y
#define BG_SIZE						(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT,0.0f))				// �w�i�T�C�Y
#define SCORE_SIZE					(D3DXVECTOR3 (30.0f,30.0f,0.0f))								// �X�R�A�T�C�Y
#define LIFE_SIZE					(D3DXVECTOR3(30.0f,30.0f,0.0f))									// ���C�t�T�C�Y
#define BOM_UI_SIZE					(D3DXVECTOR3(40.0f,40.0f,0.0f))									// �T�C�Y
#define NORMAL_ENEMY_SIZE			(D3DXVECTOR3(50.0f,50.0f,0.0f))									// �ʏ�̓G�T�C�Y
#define CIRCLE_BULLET_ENEMY_SIZE	(D3DXVECTOR3(50.0f,50.0f,0.0f))									// �T�C�Y
#define RESPAWN_COUNT_DEVIDE		(150)															// �G�����J�E���g
#define RESPAWN_COUNT_DEVIDE2		(300)															// �G�����J�E���g2
#define RESPAWN_COUNT_DEVIDE3		(400)															// �G�����J�E���g3
#define RESPAWN_COUNT_DEVIDE4		(500)															// �G�����J�E���g4
#define SHIP_RESPAWN				(1000)															// �D�����J�E���g
#define ENEMY_NO_RESPAWN_COUNT		(3300)															// �G�̐������~�߂�J�E���g
#define NORMAL_ENEMY_LIFE			(20)															// �ʏ�̓G�̃��C�t
#define CIRCLE_BULLET_ENEMY_LIFE	(50)															// ���C�t
#define RESPAWN_COUNT_REMAINDER		(0)																// �]��
#define INIT_SCORE					(0)																// �����X�R�A
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
CScore * CGame::m_pScore	= NULL;
CLife * CGame::m_pLife		= NULL;
CPlayer * CGame::m_pPlayer	= NULL;
CBomUI * CGame::m_pBom		= NULL;
CShip * CGame::m_pShip		= NULL;
CBoss * CGame::m_pBoss		= NULL;
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CGame::CGame()
{
	m_nCount			= INIT_INT;
	m_nRespawn_Count	= INIT_INT;
	m_bfade				= false;
	m_bUseBoss			= false;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CGame::~CGame()
{
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CGame::Init(void)
{
	//�T�E���h�擾
	CSound * pSound = CSceneManager::GetSound();

	// �T�E���h�Đ�
	pSound->PlaySound(CSound::SOUND_LABEL_BGM000);

	// ���|���S������
	CBlack_Polygon::Create(POLYGON_RIGHT_POS, POLYGON_SIZE, BLACK_POLYGON_COLOR,CPolygon::TEX_TYPE_MAX);
	CBlack_Polygon::Create(POLYGON_LEFT_POS, POLYGON_SIZE, BLACK_POLYGON_COLOR, CPolygon::TEX_TYPE_MAX);

	//�w�i
	CBg::Create(BG_POS, BG_SIZE);

	//���@
	m_pPlayer = CPlayer::Create(PLAYER_POS, PLAYER_SIZE);

	//�X�R�A
	m_pScore = CScore::Create(SCORE_POS, SCORE_SIZE);

	// �X�R�A�ݒ�
	m_pScore->SetScore(INIT_SCORE);

	//���C�t
	m_pLife = CLife::Create(LIFE_POS, LIFE_SIZE);

	//�{��UI
	m_pBom = CBomUI::Create(BOM_UI_POS, BOM_UI_SIZE);

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CGame::Uninit(void)
{
	//�T�E���h�̒�~
	CSceneManager::GetSound()->StopSound();

	// �t�F�[�h�ȊO�j��
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CGame::Update(void)
{
	// �v���C���[�擾
	CPlayer * pPlayer = GetPlayer();

	// State
	int nPlayerState = INIT_INT;

	// State�擾
	nPlayerState = pPlayer->GetPlayerState();

	// �v���C���[�����S��ԂłȂ��ꍇ
	if (nPlayerState != CPlayer::STATE_DEAD)
	{
		// false�̏ꍇ
		if (m_bUseBoss == false)
		{
			// �G�����֐�
			Enemy_Respawn();
		}
	}
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CGame::Draw(void)
{
}
//******************************************************************************
// �{�X����
//******************************************************************************
void CGame::CreateBoss(void)
{
	// �{�X����
	m_pBoss = CBoss::Create(BOSS_POS, BOSS_MAIN_SIZE);
}
//******************************************************************************
// �G���������֐�
//******************************************************************************
void CGame::Enemy_Respawn(void)
{
	// �C���N�������g
	m_nRespawn_Count++;

	// 150���܂�0�̂Ƃ�
	if (m_nRespawn_Count % RESPAWN_COUNT_DEVIDE == RESPAWN_COUNT_REMAINDER)
	{
		// �G����
		CNormal_Enemy::Create(ENEMY_RESPWAN_POS_1,
			ENEMY_ROT,
			NORMAL_ENEMY_SIZE,
			NORMAL_ENEMY_LIFE,
			CEnemy::TEX_TYPE_NORMAL);

		CNormal_Enemy::Create(ENEMY_RESPWAN_POS_2,
			ENEMY_ROT,
			NORMAL_ENEMY_SIZE,
			NORMAL_ENEMY_LIFE,
			CEnemy::TEX_TYPE_NORMAL);
	}
	// 300���܂�0�̂Ƃ�
	if (m_nRespawn_Count % RESPAWN_COUNT_DEVIDE2 == RESPAWN_COUNT_REMAINDER)
	{
		// �G����
		CCirecle_Bullet_Enemy::Create(ENEMY_RESPAWN_POS_3,
			ENEMY_ROT,
			CIRCLE_BULLET_ENEMY_SIZE,
			CIRCLE_BULLET_ENEMY_LIFE,
			CEnemy::TEX_TYPE_BLUE,
			CCirecle_Bullet_Enemy::DROP_ITEM_BOM);
	}
	// 400���܂�0�̂Ƃ�
	if (m_nRespawn_Count % RESPAWN_COUNT_DEVIDE3 == RESPAWN_COUNT_REMAINDER)
	{
		// �G����
		CNormal_Enemy::Create(ENEMY_RESPWAN_POS_4,
			ENEMY_ROT,
			NORMAL_ENEMY_SIZE,
			NORMAL_ENEMY_LIFE,
			CEnemy::TEX_TYPE_NORMAL);

		CNormal_Enemy::Create(ENEMY_RESPWAN_POS_5,
			ENEMY_ROT,
			NORMAL_ENEMY_SIZE,
			NORMAL_ENEMY_LIFE,
			CEnemy::TEX_TYPE_NORMAL);

	}
	// 500���܂�0�̂Ƃ�
	if (m_nRespawn_Count % RESPAWN_COUNT_DEVIDE4 == RESPAWN_COUNT_REMAINDER)
	{
		// �G����
		CCirecle_Bullet_Enemy::Create(ENEMY_RESPWAN_POS_6,
			ENEMY_ROT,
			CIRCLE_BULLET_ENEMY_SIZE,
			CIRCLE_BULLET_ENEMY_LIFE,
			CEnemy::TEX_TYPE_RED,
			CCirecle_Bullet_Enemy::DROP_ITEM_POWERUP);
	}
	// 1500�J�E���g
	if (m_nRespawn_Count == SHIP_RESPAWN)
	{
		// �D����
		m_pShip = CShip::Create(SHIP_RESPAWN_POS, SHIP_SIZE);
	}
	// 3300�ɂȂ����ꍇ
	if (m_nRespawn_Count == ENEMY_NO_RESPAWN_COUNT)
	{
		// true��
		m_bUseBoss = true;
	}
}
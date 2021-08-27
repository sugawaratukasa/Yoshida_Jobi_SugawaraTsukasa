//******************************************************************************
// �A�C�e������ [item.cpp]
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
#include "../Player/player.h"
#include "../System/sound.h"
#include "../UI/score.h"
#include "../UI/life.h"
#include "../Mode/game.h"
#include "item.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define BOM_TEXTURE		( "data/Texture/UI/bom3.png")		// �{���e�N�X�`��
#define POWERUP_TEXTURE	( "data/Texture/UI/Powerup.png")	// �p���[�A�b�v�e�N�X�`��
#define ITEM_SIZE		(D3DXVECTOR3(40.0f,40.0f,0.0f))		// �A�C�e���T�C�Y
#define COLOR			(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// �F
#define MOVE_VALUE		(3.0f)								// �ړ���
#define DEVIDE_VALUE	(2)									// ���Z�l
#define GET_BOM_VALUE	(1)									// �{���擾��
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPDIRECT3DTEXTURE9 CItem::m_apTexture[TYPE_MAX] = {};
//******************************************************************************
// �e�N�X�`���ǂݍ���
//******************************************************************************
HRESULT CItem::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BOM_TEXTURE, &m_apTexture[TYPE_BOM]);
	D3DXCreateTextureFromFile(pDevice, POWERUP_TEXTURE, &m_apTexture[TYPE_POWERUP]);
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���j��
//******************************************************************************
void CItem::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCnt = INIT_INT; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}
//******************************************************************************
// �����֐�
//******************************************************************************
CItem * CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// pItem�N���X�̃|�C���^
	CItem * pItem;

	// �������m��
	pItem = new CItem;

	// �ʒu���W�ݒ�
	pItem->SetPosition(pos);

	// �T�C�Y�ݒ�
	pItem->SetSize(size);

	// �^�C�v�ݒ�
	pItem->m_type = type;

	// �e�̏����ݒ�
	pItem->SetRGBA(COLOR);

	// �e�N�X�`���󂯓n��
	pItem->BindTexture(m_apTexture[pItem->m_type]);

	// �I�u�W�F�N�g�^�C�v�ݒ�
	pItem->SetObjType(CScene::OBJTYPE_ITEM);

	// ������
	pItem->Init();

	// pItem�|�C���^��Ԃ�
	return pItem;
}
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CItem::CItem(int nPriority) : CScene2d(nPriority)
{
	m_move	= INIT_D3DXVECTOR3;
	m_bMove = false;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CItem::~CItem()
{
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CItem::Init(void)
{
	// ������
	CScene2d::Init();

	return S_OK;
}
///******************************************************************************
// �I���֐�
//******************************************************************************
void CItem::Uninit(void)
{
	// �I��
	CScene2d::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CItem::Update(void)
{
	//�X�V
	CScene2d::Update();

	//�T�E���h�̎擾
	CSound * pSound = CSceneManager::GetSound();

	//���W�̎擾
	D3DXVECTOR3 pos;
	pos = GetPosition();

	// �����蔻��
	HitPlayer();

	// false�̏ꍇ
	if (m_bMove == false)
	{
		m_move.y = MOVE_VALUE;
	}
	// ��ʂ̉E�ɓ���������
	if (pos.x + ITEM_SIZE.x / DEVIDE_VALUE > MAX_GAME_WIDTH)
	{
		m_bMove = true;
		// �^�񒆂��Ⴉ������
		if (pos.y + ITEM_SIZE.y/ DEVIDE_VALUE < SCREEN_HEIGHT / DEVIDE_VALUE)
		{
			m_move.x = -MOVE_VALUE;
			m_move.y = MOVE_VALUE;
		}
		// �^�񒆂�荂��������
		if (pos.y - ITEM_SIZE.y / DEVIDE_VALUE > SCREEN_HEIGHT / DEVIDE_VALUE)
		{
			m_move.x = -MOVE_VALUE;
			m_move.y = MOVE_VALUE;
		}
	}
	// ��ʍ��ɓ���������
	if (pos.x - ITEM_SIZE.x / DEVIDE_VALUE < MIN_GAME_WIDTH)
	{
		// true�ɂ���
		m_bMove = true;
		// �^�񒆂��Ⴉ������
		if (pos.y + ITEM_SIZE.y / DEVIDE_VALUE < SCREEN_HEIGHT / DEVIDE_VALUE)
		{
			m_move.x = MOVE_VALUE;
			m_move.y = MOVE_VALUE;
		}
		// �^�񒆂�荂��������
		if (pos.y - ITEM_SIZE.y / DEVIDE_VALUE > SCREEN_HEIGHT / DEVIDE_VALUE)
		{
			m_move.x = MOVE_VALUE;
			m_move.y = -MOVE_VALUE;
		}
	}
	//��ʉ��ɓ���������
	if (pos.y - ITEM_SIZE.y / DEVIDE_VALUE <= WINDOW_POS_Y)
	{
		// true��
		m_bMove = true;
		// �^�񒆂��E
		if (pos.x + ITEM_SIZE.x / DEVIDE_VALUE > SCREEN_WIDTH / DEVIDE_VALUE)
		{
			m_move.x = MOVE_VALUE;
			m_move.y = MOVE_VALUE;
		}
		// �^�񒆂�荶
		if (pos.x + ITEM_SIZE.x / DEVIDE_VALUE < SCREEN_WIDTH / DEVIDE_VALUE)
		{
			m_move.x = -MOVE_VALUE;
			m_move.y = MOVE_VALUE;
		}
	}
	//��ʏ�ɓ���������
	if (pos.y + ITEM_SIZE.y / DEVIDE_VALUE > SCREEN_HEIGHT)
	{
		// true�ɂ���
		m_bMove = true;
		m_move.y = -MOVE_VALUE;
	}
	
	// �ړ�
	pos.x += m_move.x;
	pos.y += m_move.y;

	// �ʒu�X�V
	SetPosition(pos);
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CItem::Draw(void)
{
	// �`��
	CScene2d::Draw();
}
//******************************************************************************
// �����蔻��֐�
//******************************************************************************
bool CItem::Collision(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2)
{
	bool bHit = false;  //�����������ǂ���

	D3DXVECTOR3 box1Max = D3DXVECTOR3(size1.x / 2, size1.y, size1.z / 2) + pos1;          //�Ԃ��鑤�̍ő�l
	D3DXVECTOR3 box1Min = D3DXVECTOR3(-size1.x / 2, -size1.y, -size1.z / 2) + pos1;       //�Ԃ��鑤�̍ŏ��l
	D3DXVECTOR3 box2Max = D3DXVECTOR3(size2.x / 2, size2.y / 2, size2.z / 2) + pos2;      //�Ԃ����鑤�̍ő�l
	D3DXVECTOR3 box2Min = D3DXVECTOR3(-size2.x / 2, -size2.y / 2, -size2.z / 2) + pos2;   //�Ԃ����鑤�̍ŏ��l

	if (box1Max.y > box2Min.y&&
		box1Min.y < box2Max.y&&
		box1Max.x > box2Min.x&&
		box1Min.x < box2Max.x)
	{
		bHit = true;
	}

	return bHit;    //�����������ǂ�����Ԃ�
}
//******************************************************************************
// �v���C���[�Ɠ��������Ƃ�
//******************************************************************************
void CItem::HitPlayer(void)
{
	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	CPlayer * pPlayer = CGame::GetPlayer();

	// ���W�ƃT�C�Y�擾
	D3DXVECTOR3 PlayerPos = pPlayer->GetPosition();
	D3DXVECTOR3 PlayerSize = pPlayer->GetSize();

	// �����蔻��
	if (Collision(pos, PlayerPos, size, PlayerSize) == true)
	{
		// �^�C�v���{���̏ꍇ
		if (m_type == TYPE_BOM)
		{
			// �{���̏������̉��Z
			pPlayer->GetBom(GET_BOM_VALUE);
		}
		// �^�C�v���p���[�A�b�v�̏ꍇ
		if (m_type == TYPE_POWERUP)
		{
			// �p���[�A�b�v
			pPlayer->GetPowerUp();
		}

		// �e������
		Uninit();
		return;
	}
}
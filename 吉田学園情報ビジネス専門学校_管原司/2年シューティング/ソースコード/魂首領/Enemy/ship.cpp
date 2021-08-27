//******************************************************************************
// �D [ship.cpp]
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
#include "ship.h"
#include "ship_battery.h"
#include "../UI/warning.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define SHIP_TEXTURE		("data/Texture/Enemy/Ship.png")							// �D�̃e�N�X�`��
#define COLOR_VALUE			(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))						// �F�̒l
#define ROT_VALUE			(D3DXVECTOR3(0.0f,0.0f, D3DXToRadian(180.0f)))			// �����̒l
#define MOVE_VALUE			(D3DXVECTOR3(0.0f,1.0f,0.0f))							// �ړ���
#define SHIP_SIZE			(D3DXVECTOR3(1000.0f,1800.0f,0.0f))						// �D�̃T�C�Y
#define SHIP_BATTERY_POS1	(D3DXVECTOR3(150.0f,400.0f,0.0f))						// �C��̈ʒu1
#define SHIP_BATTERY_POS2	(D3DXVECTOR3(-150.0f,400.0f,0.0f))						// �C��̈ʒu2
#define SHIP_BATTERY_POS3	(D3DXVECTOR3(280.0f,-20.0f,0.0f))						// �C��̈ʒu3
#define SHIP_BATTERY_POS4	(D3DXVECTOR3(-280.0f,-20.0f,0.0f))						// �C��̈ʒu4
#define SHIP_BATTERY_POS5	(D3DXVECTOR3(-280.0f,-550.0f,0.0f))						// �C��̈ʒu5
#define SHIP_BATTERY_POS6	(D3DXVECTOR3(280.0f,-550.0f,0.0f))						// �C��̈ʒu6
#define SHIP_BATTERY_SIZE	(D3DXVECTOR3(100.0f,200.0f,0.0f))						// �D�̖C��̃T�C�Y
#define SHIP_BATTERY_ROT	(D3DXVECTOR3(0.0f,0.0f,0.0f))							// �D�̖C��̌���
#define WARNING_POS			(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2, 0.0f))	// �ʒu���W
#define WARNING_SIZE		(D3DXVECTOR3(500.0f,300.0f,0.0f))						// �T�C�Y
#define SHIP_BATTERY_LIFE	(100)													// �D�̖C��̃��C�t
#define DEVIDE_VAlUE		(2)														// ���Z�l
#define TEX_X				(0.0f)													// �e�N�X�`��X
#define TEX_Y				(0.0f)													// �e�N�X�`��Y
#define TEX_ANIM_X			(1.0f)													// �e�N�X�`��X
#define TEX_ANIM_Y			(1.0f)													// �e�N�X�`��Y
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPDIRECT3DTEXTURE9 CShip::m_pTexture = NULL;
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CShip::CShip(int nPriority) : CScene2d(nPriority)
{
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CShip::~CShip()
{
}
//******************************************************************************
// �e�N�X�`���ǂݍ���
//******************************************************************************
HRESULT CShip::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, SHIP_TEXTURE, &m_pTexture);
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���j��
//******************************************************************************
void CShip::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//******************************************************************************
// �����֐�
//******************************************************************************
CShip * CShip::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CShip�N���X�̃|�C���^
	CShip * pShip;

	// �������m��
	pShip = new CShip;

	// �ʒu���W�ݒ�
	pShip->SetPosition(pos);

	// �ʒu���W�ݒ�
	pShip->SetSize(size);

	// �����ݒ�
	pShip->SetRot(ROT_VALUE);

	// �J���[�ݒ�
	pShip->SetRGBA(COLOR_VALUE);

	// �e�N�X�`���󂯓n��
	pShip->BindTexture(m_pTexture);

	// �I�u�W�F�N�g�^�C�v�ݒ�
	pShip->SetObjType(OBJTYPE_SHIP);

	// ������
	pShip->Init();

	// �C�䐶��
	pShip->BatteryCreate();

	// �|�C���^��Ԃ�
	return pShip;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CShip::Init(void)
{
	// ������
	CScene2d::Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CShip::Uninit(void)
{
	// �I��
	CScene2d::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CShip::Update(void)
{
	// �X�V
	CScene2d::Update();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �ړ��p�ϐ�
	D3DXVECTOR3 move = MOVE_VALUE;

	// ��ʊO�ɂł���
	if (pos.y - SHIP_SIZE.y / DEVIDE_VAlUE >= SCREEN_HEIGHT)
	{
		// Warning����
		CWarning::Create(WARNING_POS, WARNING_SIZE);

		// �I��
		Uninit();
		return;
	}

	// �ړ�
	pos.y += move.y;

	// �e�N�X�`��
	SetTexture(TEX_X, TEX_Y, TEX_ANIM_X, TEX_ANIM_Y);

	// �ʒu���W�ݒ�
	SetPosition(pos);
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CShip::Draw(void)
{
	// �`��
	CScene2d::Draw();
}
//******************************************************************************
// �C�䐶��
//******************************************************************************
void CShip::BatteryCreate(void)
{
	// �C�䐶��
	CShip_Battery::Create(SHIP_BATTERY_POS1, SHIP_BATTERY_ROT, SHIP_BATTERY_SIZE, SHIP_BATTERY_LIFE, CEnemy::TEX_TYPE_SHIP_BATTERY);
	CShip_Battery::Create(SHIP_BATTERY_POS2, SHIP_BATTERY_ROT, SHIP_BATTERY_SIZE, SHIP_BATTERY_LIFE, CEnemy::TEX_TYPE_SHIP_BATTERY);
	CShip_Battery::Create(SHIP_BATTERY_POS3, SHIP_BATTERY_ROT, SHIP_BATTERY_SIZE, SHIP_BATTERY_LIFE, CEnemy::TEX_TYPE_SHIP_BATTERY);
	CShip_Battery::Create(SHIP_BATTERY_POS4, SHIP_BATTERY_ROT, SHIP_BATTERY_SIZE, SHIP_BATTERY_LIFE, CEnemy::TEX_TYPE_SHIP_BATTERY);
	CShip_Battery::Create(SHIP_BATTERY_POS5, SHIP_BATTERY_ROT, SHIP_BATTERY_SIZE, SHIP_BATTERY_LIFE, CEnemy::TEX_TYPE_SHIP_BATTERY);
	CShip_Battery::Create(SHIP_BATTERY_POS6, SHIP_BATTERY_ROT, SHIP_BATTERY_SIZE, SHIP_BATTERY_LIFE, CEnemy::TEX_TYPE_SHIP_BATTERY);

}
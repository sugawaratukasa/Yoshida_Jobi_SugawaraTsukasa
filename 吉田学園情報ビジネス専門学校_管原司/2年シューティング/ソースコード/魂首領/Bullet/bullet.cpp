//******************************************************************************
// �e [bullet.cpp]
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
#include "../Mode/game.h"
#include "bullet.h"
#include "../Particle/particle.h"
#include "../Particle/particle_circle.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define PLAYER_BULLET_TEXTURE	("data/Texture/Bullet/Playerbullet001.png")		// ���@�̒e�̃e�N�X�`��	
#define PLAYER_BEAM_TEXTURE		("data/Texture/Bullet/PlayerBeam001.png")		// ���@�̃r�[���̃e�N�X�`��
#define BOM_TEXTURE				("data/Texture/Bullet/bom.png")					// �{���̃e�N�X�`��
#define ENEMY_BULLET_TEXTURE	("data/Texture/Bullet/EnemyBullet.png")			// �G�̒e�̃e�N�X�`��
#define PARTICLE_SIZE			(D3DXVECTOR3(150.0f,150.0f,0.0f))				// �T�C�Y
#define PARTICLE_CREATE_NUM		(3)												// �p�[�e�B�N��������
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPDIRECT3DTEXTURE9 CBullet::m_apTexture[TEX_TYPE_MAX] = {};
bool CBullet::m_bUseBullet = true;
//******************************************************************************
// �e�N�X�`���ǂݍ��݊֐�
//******************************************************************************
HRESULT CBullet::Load(void)
{
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

	// �e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, PLAYER_BULLET_TEXTURE, &m_apTexture[TEX_TYPE_NORMAL]);
	D3DXCreateTextureFromFile(pDevice, PLAYER_BEAM_TEXTURE, &m_apTexture[TEX_TYPE_BEAM]);
	D3DXCreateTextureFromFile(pDevice, BOM_TEXTURE, &m_apTexture[TEX_TYPE_BOM]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_BULLET_TEXTURE, &m_apTexture[TEX_TYPE_ENEMY_NORMAL]);
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���j���֐�
//******************************************************************************
void CBullet::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCnt = INIT_INT; nCnt < TEX_TYPE_MAX; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CBullet::CBullet(int nPriority) : CScene2d(nPriority)
{
	m_rot			= INIT_D3DXVECTOR3;
	m_Textype		= TEX_TYPE_NONE;
	m_bUseBullet	= true;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CBullet::~CBullet()
{
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CBullet::Init()
{
	// ������
	CScene2d::Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CBullet::Uninit(void)
{
	// �I��
	CScene2d::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CBullet::Update(void)
{
	// �X�V
	CScene2d::Update();

	// �ʒu���W�̎擾
	D3DXVECTOR3 pos;
	pos = GetPosition();
	
	// �ʒu�X�V
	SetPosition(pos);

	// ��ʊO
	if (pos.x > MAX_GAME_WIDTH || pos.x < MIN_GAME_WIDTH || pos.y > SCREEN_HEIGHT || pos.y < 0)
	{
		//�I��
		Uninit();
		return;
	}

	// �I�u�W�F�N�g�^�C�v�擾
	OBJTYPE objtype = GetObjType();

	if (objtype == OBJTYPE_ENEMY_BULLET)
	{
		// false�̏ꍇ
		if (m_bUseBullet == false)
		{
			// �p�[�e�B�N���G�t�F�N�g
			CParticle_Circle::CreateParticleEffect(pos, PARTICLE_SIZE, PARTICLE_CREATE_NUM);

			// �I��
			Uninit();
			return;
		}
	}
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CBullet::Draw(void)
{
	// �`��
	CScene2d::Draw();
}
//******************************************************************************
// �e�̏��ݒ�
//******************************************************************************
void CBullet::SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, TEX_TYPE textype, OBJTYPE objtype)
{
	// �ʒu���W�ݒ�
	SetPosition(pos);

	// �����ݒ�
	SetRot(rot);

	// �T�C�Y�ݒ�
	SetSize(size);

	// �J���[�ݒ�
	SetRGBA(col);

	// �e�N�X�`���^�C�v�ݒ�
	m_Textype = textype;

	// �e�N�X�`���ݒ�
	BindTexture(m_apTexture[m_Textype]);

	// �I�u�W�F�N�g�^�C�v�ݒ�
	SetObjType(objtype);
}
//******************************************************************************
// �����蔻��
//******************************************************************************
bool CBullet::Collision(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2)
{
	//�����������ǂ���
	bool bHit = false;  

	D3DXVECTOR3 box1Max = D3DXVECTOR3(size1.x / 2, size1.y / 2, size1.z / 2) + pos1;          //�Ԃ��鑤�̍ő�l
	D3DXVECTOR3 box1Min = D3DXVECTOR3(-size1.x / 2, -size1.y / 2, -size1.z / 2) + pos1;       //�Ԃ��鑤�̍ŏ��l
	D3DXVECTOR3 box2Max = D3DXVECTOR3(size2.x / 2, size2.y / 2, size2.z / 2) + pos2;      //�Ԃ����鑤�̍ő�l
	D3DXVECTOR3 box2Min = D3DXVECTOR3(-size2.x / 2, -size2.y / 2, -size2.z / 2) + pos2;   //�Ԃ����鑤�̍ŏ��l

	// ��`�̔���
	if (box1Max.y > box2Min.y&&
		box1Min.y < box2Max.y&&
		box1Max.x > box2Min.x&&
		box1Min.x < box2Max.x)
	{
		bHit = true;
	}

	//�����������ǂ�����Ԃ�
	return bHit;    
}
//******************************************************************************
// ��������Ă���e��S�Ĕj��
//******************************************************************************
void CBullet::AllReleaseBullet(void)
{
	// false��
	m_bUseBullet = false;
}
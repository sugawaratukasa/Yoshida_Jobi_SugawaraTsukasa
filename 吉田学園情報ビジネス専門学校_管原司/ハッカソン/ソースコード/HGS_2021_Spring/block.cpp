//=============================================================================
//
// �u���b�N�̏��� [block.cpp]
// Author : �ѐ�ї���
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "block.h"
#include "player_3d.h"
#include "mode_game.h"

//*****************************************************************************
// �ÓI�����o�ϐ�������
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBlock::m_apTexture[1] = {};
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBlock::CBlock(int nPriority)
{
	m_nPatternAnim = 2;
	m_nCountAnim = 0;
	m_nBreakIces = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBlock::~CBlock()
{

}
//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CBlock::Load(void)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BLOCK, &m_apTexture[0]);
	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CBlock::Unload(void)
{
	for (int nCnt = 0; nCnt < 1; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CBlock::Init(void)
{
	SetObjType(CScene::OBJTYPE_NONE);

	CPolygon3d::Init();

	//�e�N�X�`���Z�b�g
	D3DXVECTOR2 Tex[NUM_VERTEX];
	Tex[0] = D3DXVECTOR2(0.0f, 0.0f);
	Tex[1] = D3DXVECTOR2(1.0f, 0.0f);
	Tex[2] = D3DXVECTOR2(0.0f, 1.0f);
	Tex[3] = D3DXVECTOR2(1.0f, 1.0f);
	SetTexture(Tex);

	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//������ݒ�
	SetRotation(D3DXVECTOR3(D3DXToRadian(0.0f), D3DXToRadian(0.0f), D3DXToRadian(0.0f)));

	BindTexture(m_apTexture[0]);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBlock::Uninit(void)
{
	CPolygon3d::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBlock::Update(void)
{
	CPolygon3d::Update();
	//�e�N�X�`���Z�b�g
	D3DXVECTOR2 Tex[NUM_VERTEX];
	Tex[0] = D3DXVECTOR2(0.0f, 0.0f);
	Tex[1] = D3DXVECTOR2(1.0f, 0.0f);
	Tex[2] = D3DXVECTOR2(0.0f, 1.0f);
	Tex[3] = D3DXVECTOR2(1.0f, 1.0f);
	SetTexture(Tex);
	Collision();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBlock::Draw(void)
{
	CPolygon3d::Draw();
}

void CBlock::Collision(void)
{

	D3DXVECTOR3 Move;
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Size;
	D3DXVECTOR3 PosOld;
	CPlayer3d * pPlayer = CGameMode::GetPlayer3d();

	if (pPlayer != nullptr)
	{
		Pos = pPlayer->GetPosition();
		Size = pPlayer->GetCollisionSize();
		PosOld = pPlayer->GetPositionOld();
		Move = pPlayer->GetMove();

		D3DXVECTOR3 box1Max = D3DXVECTOR3(Size.x / 2, Size.y / 2, Size.z / 2) + Pos;
		D3DXVECTOR3 box1Min = D3DXVECTOR3(-Size.x / 2, -Size.y / 2, -Size.z / 2) + Pos;
		D3DXVECTOR3 box2Max = D3DXVECTOR3((GetSize().x / 2), (GetSize().y / 2), (GetSize().z / 2)) + GetPosition();
		D3DXVECTOR3 box2Min = D3DXVECTOR3((-GetSize().x / 2), (-GetSize().y / 2), (-GetSize().z / 2)) + GetPosition();

		if (
			box1Max.y > box2Min.y && //�c��
			box1Min.y < box2Max.y && //�c��
			box1Max.x > box2Min.x && //����
			box1Min.x < box2Max.x //���E
			)
		{
			if (pPlayer->GetState() != CPlayer3d::STATE_DEATH)
			{
				pPlayer->Death(GetPosition());//���������玀�S
			}
		}
	}
}
//******************************************************************************
// �r�[���̏��� [beam.cpp]
// Author : �ǌ��@�i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "../System/main.h"
#include "../System/renderer.h"
#include "../System/scene.h"
#include "../System/manager.h"
#include "../System/scene.h"
#include "../System/scene2d.h"
#include "../Player/player.h"
#include "../Beam/beam.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define TEXTURE_01				("data/Texture/Bullet/beam.png")				// �e�N�X�`��
#define TEXTURE_02				("data/Texture/Effect/particle008.png")			// �e�N�X�`��
#define POS						(D3DXVECTOR3(0.0f,-35.0f,0.0f))					// �ʒu
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPDIRECT3DTEXTURE9 CBeam::m_apTexture[TEX_TYPE_MAX] = {};
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CBeam::CBeam(int nPriority) : CBeam_Base(nPriority)
{
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CBeam::~CBeam()
{
}
//******************************************************************************
// �e�N�X�`���ǂݍ���
//******************************************************************************
HRESULT CBeam::Load(void)
{
	//�����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_01, &m_apTexture[TEX_TYPE_01]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_02, &m_apTexture[TEX_TYPE_02]);
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���j��
//******************************************************************************
void CBeam::Unload(void)
{
	// �ő吔����
	for (int nCnt = INIT_INT; nCnt < TEX_TYPE_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[TEX_TYPE_MAX] != NULL)
		{
			// �e�N�X�`���̂�Release
			m_apTexture[TEX_TYPE_MAX]->Release();
			// �e�N�X�`���̂�NULL
			m_apTexture[TEX_TYPE_MAX] = NULL;
		}
	}
}
//******************************************************************************
// �����֐�
//******************************************************************************
CBeam * CBeam::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DCOLOR col, TEX_TYPE tex_type)
{
	// CBeam�N���X�̃|�C���^
	CBeam *pBeam;

	// �������m��
	pBeam = new CBeam;

	// ���ݒ�
	pBeam->SetBeam(pos, size, col);

	// �e�N�X�`���󂯓n��
	pBeam->BindTexture(m_apTexture[tex_type]);

	// ������
	pBeam->Init();

	// �|�C���^��Ԃ�
	return pBeam;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CBeam::Init(void)
{
	// ������
	CBeam_Base::Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CBeam::Uninit(void)
{
	// �I��
	CBeam_Base::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CBeam::Update(void)
{
	// �X�V
	CBeam_Base::Update();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	// CScene�^�̃|�C���^
	CScene *pScene = NULL;

	// �v���C���[�̎擾
	do
	{
		// �I�u�W�F�^�C�v���G�̏ꍇ
		pScene = GetScene(OBJTYPE_PLAYER);

		// NULL�`�F�b�N
		if (pScene != NULL)
		{
			// �I�u�W�F�^�C�v�擾
			OBJTYPE objType = pScene->GetObjType();

			// �I�u�W�F�N�g�^�C�v���v���C���[
			if (objType == OBJTYPE_PLAYER)
			{
				// �v���C���[�ʒu�擾
				D3DXVECTOR3 PlayerPos = ((CPlayer*)pScene)->GetPosition();

				// �ʒu�ݒ�
				SetPosition(D3DXVECTOR3(PlayerPos.x, PlayerPos.y + POS.y, pos.z));
			}
		}
	} while (pScene != NULL);
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CBeam::Draw(void)
{
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

	// ���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �`��
	CBeam_Base::Draw();

	// ���ɖ߂�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//******************************************************************************
// �j���֐�
//******************************************************************************
void CBeam::Release(void)
{
	// �I��
	Uninit();
	return;
}

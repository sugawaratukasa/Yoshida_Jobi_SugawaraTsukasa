//***********************************************************************************
//	particle [particle.cpp]
//	Author : �ǌ� �i
//***********************************************************************************
//***********************************************************************************
// �C���N���[�h�t�@�C��
//***********************************************************************************
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "particle.h"
//***********************************************************************************
// �}�N����`
//***********************************************************************************
#define MIN_SCALE		(0.0f)					// �g�嗦�̍ŏ��l
#define MIN_COL			(0.0f)					// �F�̍ŏ��l
#define MIN_LIFE		(0)						// ���C�t�ŏ��l
#define RANDOM_POS_MUT	(10.0f)					// �|����l
#define MUT				(2.0f)					// �Q�{
#define ROT_MAX			(360)					// �p�x�ő�
#define COLOR_A			(255)					// ���l
#define ADD_RAND		(1.0f)					// �^�������p
//***********************************************************************************
// �R���X�g���N�^
//***********************************************************************************
CParticle::CParticle()
{
	m_pUi			= NULL;
	m_nLife			= INIT_INT;
	m_bAlpha_Blend	= false;
	m_Angle			= INIT_D3DXVECTOR3;
}
//***********************************************************************************
// �f�X�g���N�^
//***********************************************************************************
CParticle::~CParticle()
{
}
//***********************************************************************************
// �����֐�
//***********************************************************************************
CParticle * CParticle::Create(CUI *pUi)
{
	// CParticle�̃|�C���^
	CParticle *pParticle = NULL;

	// NULL�̏ꍇ
	if (pParticle == NULL)
	{
		// �������m��
		pParticle = new CParticle;

		// NULL�łȂ��ꍇ
		if (pParticle != NULL)
		{
			// ���
			pParticle->m_pUi = pUi;

			// �ʒu�ݒ�
			pParticle->SetPosition(pParticle->m_pUi->GetPos());

			// �T�C�Y�ݒ�
			pParticle->SetSize(pParticle->m_pUi->GetSize());

			// ���ߒl�擾
			int nAlpha = pParticle->m_pUi->GetAlpha();

			// ���ߒl�ݒ�
			pParticle->SetAlpha(nAlpha);

			// ������
			pParticle->Init();
		}
	}
	// �|�C���^��Ԃ�
	return pParticle;
}
//***********************************************************************************
// �������֐�
//***********************************************************************************
HRESULT CParticle::Init(void)
{
	// ������
	CBillboard::Init();

	// �����������_���ɂ��邩�擾
	bool bRotRandom = m_pUi->GetbRotRandom();

	// false�̏ꍇ
	if (bRotRandom == false)
	{
		// �����擾
		D3DXVECTOR3 rot = m_pUi->GetRot();

		// ���W�A���ϊ�
		rot = (D3DXToRadian(rot));

		// �����ݒ�
		SetRotation(rot);
	}
	// true�̏ꍇ
	if (bRotRandom == true)
	{
		// �����擾
		D3DXVECTOR3 rot = INIT_D3DXVECTOR3;

		// ���������_��
		rot.z = float(rand() % (int)ROT_MAX);

		// ���W�A���ϊ�
		rot = (D3DXToRadian(rot));

		// �����ݒ�
		SetRotation(rot);
	}

	// �T�C�Y�����_��
	bool bRandomSize = m_pUi->GetRandomSize();

	// true�̏ꍇ
	if (bRandomSize == true)
	{
		// �T�C�Y
		D3DXVECTOR3 size = INIT_D3DXVECTOR3;

		// �����_���T�C�Y�̍ŏ��l
		float fRandom_Min_Size = m_pUi->GetRandom_Min_Size();

		// �����_���T�C�Y�̍ő�l
		float fRandom_Max_Size = m_pUi->GetRandom_Max_Size();

		// �T�C�Y�������_��
		float fRandomSize = float(rand() % (int)fRandom_Max_Size + (int)fRandom_Min_Size);

		// �T�C�Y��ݒ�
		size.x = fRandomSize;

		// �T�C�Y��ݒ�
		size.y = fRandomSize;

		// �T�C�Y�ݒ�
		SetSize(size);
	}

	// �T�C�Y�����_��
	bool bRandomPos = m_pUi->GetbRandomPos();

	// true�̏ꍇ
	if (bRandomPos == true)
	{
		// �����擾
		D3DXVECTOR3 pos = INIT_D3DXVECTOR3;

		// �擾
		D3DXVECTOR3 RandomPos = m_pUi->GetRandom_Pos();

		// �ʒu�����_��
		pos.x = float(rand() % (int)RandomPos.x *RANDOM_POS_MUT * MUT - (int)RandomPos.x *RANDOM_POS_MUT / MUT);

		// ���Z
		pos.x = pos.x / RANDOM_POS_MUT;

		// �ʒu�����_��
		pos.y = float(rand() % (int)RandomPos.y * RANDOM_POS_MUT);

		// ���Z
		pos.y = pos.y / RANDOM_POS_MUT;

		// �ʒu�ݒ�
		SetPosition(pos);
	}
	// �J���[�����_����
	bool bColorRandom = m_pUi->GetColorRandom();

	// false�̏ꍇ
	if (bColorRandom == false)
	{
		// �F�ݒ�
		SetColor(m_pUi->GetColor());
	}
	// true�̏ꍇ
	if (bColorRandom == true)
	{
		// �F
		D3DXCOLOR col = INIT_COLOR;

		// �F�擾
		int nColor_R = m_pUi->GetColorRandom_R();
		int nColor_G = m_pUi->GetColorRandom_G();
		int nColor_B = m_pUi->GetColorRandom_B();

		// �F�����_��
		nColor_R = (rand() % nColor_R);
		nColor_G = (rand() % nColor_G);
		nColor_B = (rand() % nColor_B);

		col = D3DCOLOR_RGBA(nColor_R, nColor_G, nColor_B, COLOR_A);

		// �F�ݒ�
		SetColor(col);
	}
	// ���C�t
	bool bLife = m_pUi->GetbLife();

	// �p�x�������_����
	float fAngle = m_pUi->GetAngle();

	// �p�x�����_��
	fAngle = float(rand() % (int)fAngle);

	// �p�x�擾
	m_Angle.x = fAngle;
	m_Angle.y = fAngle;
	m_Angle.z = fAngle;

	// true�̏ꍇ
	if (bLife == true)
	{
		// ���C�t�擾
		m_nLife = m_pUi->GetLife();
	}
	bool bTexRandom = m_pUi->GetbTexRandom();

	if (bTexRandom == true)
	{
		// �e�N�X�`���ŏ��ԍ��擾
		int nMinTex = m_pUi->GetMinTexRandomNum();

		// �e�N�X�`���ő�ԍ��擾
		int nMaxTex = m_pUi->GetMaxTexRandomNum();

		int nTexNum = nMinTex + (int)(rand() * (nMaxTex - nMinTex + ADD_RAND) / (ADD_RAND + RAND_MAX));

		// �e�N�X�`���󂯓n��
		BindTexture(CManager::GetTexture()->GetTexture(nTexNum));
	}

	if (bTexRandom == false)
	{
		// �e�N�X�`���ԍ��擾
		int nNumTex = m_pUi->GetTexNum();

		// �e�N�X�`���󂯓n��
		BindTexture(CManager::GetTexture()->GetTexture(nNumTex));
	}

	return S_OK;
}
//***********************************************************************************
// �I���֐�
//***********************************************************************************
void CParticle::Uninit(void)
{
	// �I��
	CBillboard::Uninit();
}
//***********************************************************************************
// �X�V�֐�
//***********************************************************************************
void CParticle::Update(void)
{
	// �X�V
	CBillboard::Update();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// �F�擾
	D3DXCOLOR col = GetColor();

	// �ړ��ʎ擾
	D3DXVECTOR3 move = m_pUi->GetMove();

	// �g�嗦�擾
	float fScale = GetScale();

	// �p�x���Z�l�擾
	D3DXVECTOR3 AddAngle = m_pUi->GetAddAngle();

	// �p�x���Z
	m_Angle.x += AddAngle.x;
	m_Angle.y += AddAngle.y;
	m_Angle.z += AddAngle.z;

	// �A���t�@�u�����h���g�p���邩�擾
	m_bAlpha_Blend = m_pUi->GetUseAlpha_Blend();

	// ���C�t
	bool bLife = m_pUi->GetbLife();

	// ���C�t���g�p����ꍇ
	if (bLife == true)
	{
		// �f�N�������g
		m_nLife--;

		// ���C�t��0�ȉ��̏ꍇ
		if (m_nLife <= MIN_LIFE)
		{
			// �I��
			Uninit();
			return;
		}
	}

	// �g�嗦�����Z���邩�擾
	bool bAddScale = m_pUi->GetbAddScale();

	// �g�嗦���Z���g�p��ԂȂ�
	if (bAddScale == true)
	{
		// �g�嗦
		float AddScale = m_pUi->GetScale();

		// �g�嗦���Z
		fScale += AddScale;

		// �g�嗦��0.0f�ȉ��̏ꍇ
		if (fScale <= MIN_SCALE)
		{
			// �I��
			Uninit();
			return;
		}
	}
	// �F���Z
	bool bSubColor = m_pUi->GetbSubColor();

	// �F���Z���g�p����ꍇ
	if (bSubColor == true)
	{
		// �F���Z�l�擾
		D3DXCOLOR SubColor = m_pUi->GetSubColor();

		// ���Z
		col -= SubColor;

		// ���l��0.0f�ȉ��̏ꍇ
		if (col.a <= MIN_COL)
		{
			// �I��
			Uninit();
			return;
		}
	}

	// �g�嗦�ݒ�
	SetScale(fScale);

	// �T�C�Y�ݒ�
	SetSize(size);

	// �F�ݒ�
	SetColor(col);

	// �ʒu�X�V
	pos.x += cosf(D3DXToRadian(m_Angle.x))*move.x;
	pos.y += sinf(D3DXToRadian(m_Angle.y))*move.y;
	pos.z += sinf(D3DXToRadian(m_Angle.z))*move.z;

	// �ʒu�ݒ�
	SetPosition(pos);
}
//***********************************************************************************
// �`��֐�
//***********************************************************************************
void CParticle::Draw(void)
{
	// false�̏ꍇ
	if (m_bAlpha_Blend == false)
	{
		// �`��
		CBillboard::Draw();
	}

	// true�̏ꍇ
	if (m_bAlpha_Blend == true)
	{
		// �����_���[�擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// ���Z�����̐ݒ�
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		// �`��
		CBillboard::Draw();

		// ���ɖ߂�
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

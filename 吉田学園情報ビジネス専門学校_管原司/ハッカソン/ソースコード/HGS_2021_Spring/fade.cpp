//=============================================================================
//
// �t�F�[�h [fade.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "mode_game.h"
#include "fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f))		//�ʒu
#define SIZE (D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f))					//�T�C�Y
#define COLOR (D3DXCOLOR(0.0f,0.0f,0.0f,0.0f))								//�F

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFade::CFade()
{
	m_pVtxBuff = NULL;					//���_�o�b�t�@
	m_Position = INITIAL_D3DXVECTOR3;	//�ʒu
	m_Size = INITIAL_D3DXVECTOR3;		//�T�C�Y
	m_fade = FADE_NONE;					//�t�F�[�h
	m_ModeNext = CManager::MODE_NONE;	//���̃��[�h
	m_Color = COLOR;			//�t�F�[�h�̐F
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFade::~CFade()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CFade * CFade::Create(CManager::MODE mode)
{
	//�t�F�[�h�̃|�C���^
	CFade * pFade = NULL;
	//�����t�F�[�h�̃|�C���^��NULL�̏ꍇ
	if (pFade == NULL)
	{
		//�t�F�[�h�̃������m��
		pFade = new CFade;
		//�����t�F�[�h�̃|�C���^��NULL����Ȃ��ꍇ
		if (pFade != NULL)
		{
			//�����������֐��Ăяo��
			pFade->Init(mode);
		}
	}
	//�t�F�[�h�̃|�C���^��Ԃ�
	return pFade;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CFade::Init(CManager::MODE mode)
{
	//�����_���[�̎擾
	CRenderer * pRenderer = CManager::GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	VERTEX_2D *pVtx;
	//�ʒu�̏����ݒ�
	m_Position = POSITION;
	//�T�C�Y�̏����ݒ�
	m_Size = SIZE;
	//���̃��[�h
	m_ModeNext = mode;
	m_fade = FADE_IN;
	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_Position.x + (-m_Size.x / 2), m_Position.y + (-m_Size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Position.x + (m_Size.x / 2), m_Position.y + (-m_Size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Position.x + (-m_Size.x / 2), m_Position.y + (m_Size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Position.x + (m_Size.x / 2), m_Position.y + (m_Size.y / 2), 0.0f);
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[�̐ݒ� 
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;
	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CFade::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CFade::Update(void)
{
	//���_����ݒ�
	VERTEX_2D *pVtx;
	//���[�h
	m_ModeNext = CManager::GetMode();
	//�X�V
	if (m_fade != FADE_NONE)
	{
		//�t�F�[�h�C��
		if (m_fade == FADE_IN)
		{
			//a�l�����Z
			m_Color.a += FADE_RATE;
			//��ʂ������Ȃ�����
			if (m_Color.a >= 1.0f)
			{
				//�^�C�g���ɑJ��
				CManager::SetMode(m_ModeNext);
				//�t�F�[�h�I������
				m_Color.a = 1.0f;
				m_fade = FADE_OUT;
			}
		}
		//�t�F�[�h�A�E�g
		if (m_fade == FADE_OUT)
		{
			//���l�����Z
			m_Color.a -= FADE_RATE;
			//��ʂ̓���
			if (m_Color.a <= 0.0f)
			{
				//�t�F�[�h�����؂�ւ�
				m_Color.a = 0.0f;
				//���[�h�ݒ�
				m_fade = FADE_IN;
				CManager::StopFade();
			}
		}
		//���_�o�b�t�@�����b�N
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		//���_�J���[�̐ݒ� 
		pVtx[0].col = m_Color;
		pVtx[1].col = m_Color;
		pVtx[2].col = m_Color;
		pVtx[3].col = m_Color;
		//���_�o�b�t�@�̃A�����b�N
		m_pVtxBuff->Unlock();
	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CFade::Draw(void)
{
	//�`��
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);
	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);
}

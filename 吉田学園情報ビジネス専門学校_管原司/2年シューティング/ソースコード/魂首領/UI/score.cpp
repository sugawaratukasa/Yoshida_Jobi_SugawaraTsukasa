//******************************************************************************
// �X�R�A���� [score.cpp]
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
#include "../Input/input.h"
#include "../Input/inputkeyboard.h"
#include "../System/number.h"
#include "score.h"
#include <cmath>
//******************************************************************************
// �}�N����`
//******************************************************************************
#define COLOR_VALUE		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// �F�̒l
#define DIVIDE_VALUE	(10.0f)								// ���Z�l
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CScore::CScore(int nPriority) : CScene(nPriority)
{
	memset(m_apNumber, 0, sizeof(m_apNumber));
	m_pos		= INIT_D3DXVECTOR3;
	m_size		= INIT_D3DXVECTOR3;
	m_nScore	= INIT_INT;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CScore::~CScore()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************-
CScore * CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CScore�N���X�̃|�C���^
	CScore * pScore;

	// �������m��
	pScore = new CScore;

	// �ʒu���W���
	pScore->m_pos = pos;

	// �T�C�Y���
	pScore->m_size = size;

	// ������
	pScore->Init();

	// �|�C���^��Ԃ�
	return pScore;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CScore::Init()
{
	// �ő吔���J��Ԃ�
	for (int nCnt = INIT_INT; nCnt < MAX_SCORE; nCnt++)
	{
		// ������
		m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(m_pos.x - (m_size.x * nCnt), m_pos.y, m_pos.z), m_size, COLOR_VALUE);
	}
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CScore::Uninit(void)
{
	// �ő吔���J��Ԃ�
	for (int nCnt = INIT_INT; nCnt < MAX_SCORE; nCnt++)
	{
		// �I��
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->Uninit();
			delete m_apNumber[nCnt];
			m_apNumber[nCnt] = NULL;
		}
	}
	//�����[�X
	Release();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CScore::Update(void)
{
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CScore::Draw(void)
{
	// �ő吔���J��Ԃ�
	for (int nCnt = INIT_INT; nCnt < MAX_SCORE; nCnt++)
	{
		// �`��
		m_apNumber[nCnt]->Draw();
	}
}
//******************************************************************************
// �X�R�A�ݒ�
//******************************************************************************
void CScore::SetScore(int nScore)
{
	// �X�R�A���
	m_nScore = nScore;

	// �v�Z�p�ϐ�
	int integer = INIT_INT;

	// �J�E���g
	int nCntNumber = INIT_INT;

	// �ő吔���J��Ԃ�
	for (int nCntDigit = 1; nCntDigit <= MAX_SCORE; nCntDigit++, nCntNumber++)
	{
		// 1�̈ʈȉ���؂�̂Ă�
		integer = int(m_nScore / std::pow(DIVIDE_VALUE, nCntDigit));
		integer = int(integer * std::pow(DIVIDE_VALUE, nCntDigit));
		// �X�R�A��ݒ�
		m_apNumber[nCntNumber]->SetNumber(int((m_nScore - integer) / std::pow(DIVIDE_VALUE, nCntDigit - 1)));
	}
}
//******************************************************************************
// �X�R�A���Z
//******************************************************************************
void CScore::AddScore(int nValue)
{
	// �X�R�A���Z
	m_nScore += nValue;
	// �X�R�A�ݒ�
	SetScore(m_nScore);
}

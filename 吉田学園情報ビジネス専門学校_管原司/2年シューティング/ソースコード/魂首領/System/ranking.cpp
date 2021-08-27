//******************************************************************************
// �����L���O [ranking.cpp]
// Author : �ǌ��@�i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#define	_CRT_SECURE_NO_WARNINGS	//scanf�G���[
#include "sound.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "../Input/input.h"
#include "../Input/inputkeyboard.h"
#include "../Player/player.h"
#include "../Bullet/bullet.h"
#include "number.h"
#include "../UI/score.h"
#include "ranking.h"
#include "../Mode/result.h"
#include <stdio.h>
//******************************************************************************
// �}�N����`
//******************************************************************************
#define RANKING_SCORE_SIZE	(D3DXVECTOR3(30.0f,30.0f,0.0f))		// �X�R�A�̃T�C�Y
#define RANKING_POS			(D3DXVECTOR3(50.0f,100.0f,0.0f))	// �����L���O�̈ʒu
#define RANKING_SCORE_POS1	(D3DXVECTOR3(0.0f,200.0f,0.0f))		// �X�R�A�ʒu
#define RANKING_SCORE_POS2	(D3DXVECTOR3(0.0f,280.0f,0.0f))		// �X�R�A�ʒu
#define RANKING_SCORE_POS3	(D3DXVECTOR3(0.0f,350.0f,0.0f))		// �X�R�A�ʒu
#define RANKING_SCORE_POS4	(D3DXVECTOR3(0.0f,440.0f,0.0f))		// �X�R�A�ʒu
#define RANKING_SCORE_POS5	(D3DXVECTOR3(0.0f,530.0f,0.0f))		// �X�R�A�ʒu
#define RANKING_MOVE_VALUE	(-1)								// �����L���O����ւ�
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CRanking::CRanking(int nPriority) : CScene(nPriority)
{
	memset(m_apScore, 0, sizeof(m_apScore));
	memset(m_anScore, 0, sizeof(m_anScore));
	m_nPlayerScore = INIT_INT;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CRanking::~CRanking()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CRanking * CRanking::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CRanking�N���X�̃|�C���^
	CRanking * pRanking;

	// �������m��
	pRanking = new CRanking;

	// �ʒu���W
	pRanking->m_pos = pos;

	// �T�C�Y���
	pRanking->m_size = size;

	// ������
	pRanking->Init();

	// �|�C���^��Ԃ�
	return pRanking;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CRanking::Init()
{
	// �v���C���[�e�L�X�g�ǂݍ���
	ReadPlayerFile();

	// �v���C���[�̃X�R�A����
	m_pPlayerScore = CScore::Create(D3DXVECTOR3(m_pos.x + RANKING_POS.x, RANKING_POS.y, m_pos.z), RANKING_SCORE_SIZE);

	// �X�R�A�ݒ�
	m_pPlayerScore->SetScore(m_nPlayerScore);

	// �����L���O�e�L�X�g�ǂݍ���
	ReadFile();

	// �����L���O�ݒ�
	SetRanking(m_nPlayerScore);

	// �����L���O�ǂݍ���
	ReadFile();

	// �X�R�A����
	m_apScore[SCORE_1Th] = CScore::Create(D3DXVECTOR3(m_pos.x, RANKING_SCORE_POS1.y, m_pos.z), RANKING_SCORE_SIZE);
	m_apScore[SCORE_1Th]->SetScore(m_anScore[SCORE_1Th]);
	m_apScore[SCORE_2Th] = CScore::Create(D3DXVECTOR3(m_pos.x, RANKING_SCORE_POS2.y, m_pos.z), RANKING_SCORE_SIZE);
	m_apScore[SCORE_2Th]->SetScore(m_anScore[SCORE_2Th]);
	m_apScore[SCORE_3Th] = CScore::Create(D3DXVECTOR3(m_pos.x, RANKING_SCORE_POS3.y, m_pos.z), RANKING_SCORE_SIZE);
	m_apScore[SCORE_3Th]->SetScore(m_anScore[SCORE_3Th]);
	m_apScore[SCORE_4Th] = CScore::Create(D3DXVECTOR3(m_pos.x, RANKING_SCORE_POS4.y, m_pos.z), RANKING_SCORE_SIZE);
	m_apScore[SCORE_4Th]->SetScore(m_anScore[SCORE_4Th]);
	m_apScore[SCORE_5Th] = CScore::Create(D3DXVECTOR3(m_pos.x, RANKING_SCORE_POS5.y, m_pos.z), RANKING_SCORE_SIZE);
	m_apScore[SCORE_5Th]->SetScore(m_anScore[SCORE_5Th]);
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CRanking::Uninit(void)
{
	// �I��
	Release();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CRanking::Update(void)
{
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CRanking::Draw(void)
{
}
//******************************************************************************
// �����L���O�e�L�X�g�ǂݍ��݊֐�
//******************************************************************************
void CRanking::ReadFile(void)
{
	FILE * pFile;
	// �t�@�C���̓ǂݍ���
	pFile = fopen("ranking.txt", "r");
	// �t�@�C�����󂶂�Ȃ���
	if (pFile != NULL)
	{
		// �ǂݍ���
		for (int nCnt = INIT_INT; nCnt < SCORE_MAX; nCnt++)
		{
			fscanf(pFile, "%d\n", &m_anScore[nCnt]);
		}
		// �t�@�C�������
		fclose(pFile);
	}
}
//******************************************************************************
// �v���C���[�̃e�L�X�g�ǂݍ��݊֐�
//******************************************************************************
void CRanking::ReadPlayerFile(void)
{
	FILE * pFile;
	// �t�@�C���̓ǂݍ���
	pFile = fopen("player.txt", "r");

	// �t�@�C�����󂶂�Ȃ���
	if (pFile != NULL)
	{
		// �ǂݍ���
		fscanf(pFile, "%d\n", &m_nPlayerScore);
		// �t�@�C�������
		fclose(pFile);
	}
}
//******************************************************************************
// �����L���O�e�L�X�g�������݊֐�
//******************************************************************************
void CRanking::WriteFile(void)
{
	FILE * pFile;
	// �t�@�C���̏����o��
	pFile = fopen("ranking.txt", "w");
	// �t�@�C�����󂶂�Ȃ���
	if (pFile != NULL)
	{
		// ��������
		for (int nCnt = INIT_INT; nCnt < SCORE_MAX; nCnt++)
		{
			fprintf(pFile, "%d\n", m_anScore[nCnt]);
		}
		// �t�@�C�������
		fclose(pFile);
	}
}
//******************************************************************************
// �����L���O�ݒ�
//******************************************************************************
void CRanking::SetRanking(int nScore)
{
	for (int nCount = INIT_INT; nCount < SCORE_MAX; nCount++)
	{
		// �����L���O���X�V����ꏊ����
		if (m_anScore[nCount] == INIT_INT || nScore > m_anScore[nCount])
		{
			// �ȍ~�̃����L���O�f�[�^�����Ɉړ�
			for (int nCntMove = SCORE_MAX + RANKING_MOVE_VALUE; nCntMove > nCount; nCntMove--)
			{
				m_anScore[nCntMove] = m_anScore[nCntMove + RANKING_MOVE_VALUE];
			}
			m_anScore[nCount] = nScore;
			break;
		}
	}
	// �t�@�C����������
	WriteFile();
}

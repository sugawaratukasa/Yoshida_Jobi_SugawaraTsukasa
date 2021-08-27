//******************************************************************************
// �����L���O [ranking.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _RANKING_H_
#define _RANKING_H_
//******************************************************************************
// �O���錾
//******************************************************************************
class CScore;
//******************************************************************************
// �N���X
//******************************************************************************
class CRanking : public CScene
{
public:
	typedef enum
	{
		SCORE_NONE = -1,
		SCORE_1Th,
		SCORE_2Th,
		SCORE_3Th,
		SCORE_4Th,
		SCORE_5Th,
		SCORE_MAX,
	}SCORE;
	CRanking(int nPriority = OBJTYPE::OBJTYPE_UI);
	~CRanking();
	static CRanking * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void ReadFile(void);
	void ReadPlayerFile(void);
	void WriteFile(void);
	void SetRanking(int nScore);
private:
	CScore * m_apScore[SCORE_MAX];		// �����L���O
	CScore * m_pPlayerScore;			// �v���C���[�X�R�A
	D3DXVECTOR3 m_pos;					// �ʒu���W
	D3DXVECTOR3 m_size;					// �T�C�Y
	int m_anScore[SCORE_MAX];			// �X�R�A
	int m_nPlayerScore;					// �v���C���[�X�R�A
};
#endif
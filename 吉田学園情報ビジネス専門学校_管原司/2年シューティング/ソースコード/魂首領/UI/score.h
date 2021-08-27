//******************************************************************************
// �X�R�A���� [score.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef SCORE_H_
#define SCORE_H_
//******************************************************************************
// �}�N����`
//******************************************************************************
#define MAX_SCORE	(8)									// �X�R�A�ő吔
//******************************************************************************
// �O���錾
//******************************************************************************
class CNumber;
//******************************************************************************
// �N���X
//******************************************************************************
class CScore : public CScene
{
public:
	CScore(int nPriority = OBJTYPE_UI);
	~CScore();
	static CScore * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetScore(int nScore);
	void AddScore(int nValue);
	int GetScore(void) { return m_nScore; }
private:
	CNumber * m_apNumber[MAX_SCORE];	// Score�̏��
	D3DXVECTOR3 m_pos;					// �ʒu���W
	D3DXVECTOR3 m_size;					// �T�C�Y
	int m_nScore;						// �X�R�A
};
#endif
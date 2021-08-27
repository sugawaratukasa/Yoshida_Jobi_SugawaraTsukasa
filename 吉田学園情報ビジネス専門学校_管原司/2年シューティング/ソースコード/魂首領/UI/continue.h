//******************************************************************************
// �R���e�B�j���[ [continue.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _CONTINUE_H_
#define _CONTINUE_H_
//******************************************************************************
// �O���錾
//******************************************************************************
class CNumber;
class CContinue_Polygon;
class CPress_Enter_Polygon;
//******************************************************************************
// �N���X
//******************************************************************************
class CContinue : public CScene
{
public:
	CContinue(int nPriority = OBJTYPE_UI);
	~CContinue();
	static CContinue * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	CNumber * m_pNumber;						// �i���o�[�̏��
	CContinue_Polygon *m_pContinue_Polygon;		// �R���e�B�j���[�|���S���̏��
	CPress_Enter_Polygon *m_pPress_Enter;		// �v���X�G���^�[�̏��
	D3DXVECTOR3 m_pos;							// �ʒu���W
	D3DXVECTOR3 m_size;							// �T�C�Y
	int m_nContinueCount;						// �J�E���g
	int m_nContinueNum;							// �R���e�B�j���[�i���o�[
};
#endif
//=============================================================================
// bg���� [bg.h]
// Author : �ѐ�ї���
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "polygon_3d.h"
#define TEXTURE_BLOCK "Data/Texture/block.png"
#define BLOCK_SIZE (100.0f)
#define ICE_LIFE 3
#define HARD_ICE_LIFE 6

class CBlock : public CPolygon3d
{
public:
	CBlock(int nPriority = 3);
	~CBlock();

	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_BLOCK_001,
		TYPE_MAX,
	}TYPE;
	typedef struct
	{
		bool bIsTop;
		bool bIsBottom;
		bool bIsRight;
		bool bIsLeft;
		bool bIsFront;
		bool bIsBack;
	}IS_COLLISION;
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Collision(void);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[1];//�e�N�X�`���̃|�C���^
	int                     m_nPatternAnim; //�A�j���[�V�����p�^�[��
	int                     m_nCountAnim; //�A�j���[�V�����p�^�[��
	int m_nBreakIces;

};
#endif // !_BLOCK_H_
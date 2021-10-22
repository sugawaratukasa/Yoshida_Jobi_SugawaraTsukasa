//******************************************************************************
// �����蔻�� [collision.cpp]
// Author : �ǌ��@�i
//******************************************************************************
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "collision.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define DEVIDE_VALUE	(2)		// ���鐔
#define SQUARE			(2.0f)	// 2��
//******************************************************************************
// �����̂̓����蔻��
//******************************************************************************
bool CCollision::RectangleCollision(D3DXVECTOR3 pPos1, D3DXVECTOR3 size1, D3DXVECTOR3 pPos2, D3DXVECTOR3 size2)
{
	bool bHit = false;

	D3DXVECTOR3 box1Max = D3DXVECTOR3(size1.x / DEVIDE_VALUE, size1.y / DEVIDE_VALUE, size1.z / DEVIDE_VALUE) + pPos1;          //�Ԃ��鑤�̍ő�l
	D3DXVECTOR3 box1Min = D3DXVECTOR3(-size1.x / DEVIDE_VALUE, -size1.y / DEVIDE_VALUE, -size1.z / DEVIDE_VALUE) + pPos1;       //�Ԃ��鑤�̍ŏ��l
	D3DXVECTOR3 box2Max = D3DXVECTOR3(size2.x / DEVIDE_VALUE, size2.y / DEVIDE_VALUE, size2.z / DEVIDE_VALUE) + pPos2;      //�Ԃ����鑤�̍ő�l
	D3DXVECTOR3 box2Min = D3DXVECTOR3(-size2.x / DEVIDE_VALUE, -size2.y / DEVIDE_VALUE, -size2.z / DEVIDE_VALUE) + pPos2;   //�Ԃ����鑤�̍ŏ��l

	if (box1Max.y > box2Min.y&&
		box1Min.y < box2Max.y&&
		box1Max.x > box2Min.x&&
		box1Min.x < box2Max.x&&
		box1Max.z > box2Min.z&&
		box1Min.z < box2Max.z)
	{
		bHit = true;
	}

	// �����������ǂ�����Ԃ�
	return bHit;
}
//******************************************************************************
// �~�`�̓����蔻��
//******************************************************************************
bool CCollision::SphereCollision(D3DXVECTOR3 pos1, float size1, D3DXVECTOR3 pos2, float size2)
{
	// �ʒu
	float distance = powf(pos1.x - pos2.x, SQUARE) + powf(pos1.y - pos2.y, SQUARE) + powf(pos1.z - pos2.z, SQUARE);

	// ���a
	float radius = powf(size1 + size2, SQUARE);

	// �߂荞��ł��邩
	return (distance < radius);
}
//******************************************************************************
// �����̂̓����蔻��
//******************************************************************************
int CCollision::RectangleCollisionMove(D3DXVECTOR3 pPos1, D3DXVECTOR3 pPosOld, D3DXVECTOR3 size1, D3DXVECTOR3 pPos2, D3DXVECTOR3 size2)
{
	int nSurFace = INIT_INT;

	D3DXVECTOR3 box1Max = D3DXVECTOR3(size1.x / DEVIDE_VALUE, size1.y / DEVIDE_VALUE, size1.z / DEVIDE_VALUE) + pPos1;
	D3DXVECTOR3 box1Min = D3DXVECTOR3(-size1.x / DEVIDE_VALUE, -size1.y / DEVIDE_VALUE, -size1.z / DEVIDE_VALUE) + pPos1;
	D3DXVECTOR3 box2Max = D3DXVECTOR3(size2.x / DEVIDE_VALUE, size2.y / DEVIDE_VALUE, size2.z / DEVIDE_VALUE) + pPos2;
	D3DXVECTOR3 box2Min = D3DXVECTOR3(-size2.x / DEVIDE_VALUE, -size2.y / DEVIDE_VALUE, -size2.z / DEVIDE_VALUE) + pPos2;

	if (box1Max.y > box2Min.y &&	// ��
		box1Min.y < box2Max.y &&	// ��
		box1Max.x > box2Min.x &&	// �E����
		box1Min.x < box2Max.x &&	// ������
		box1Max.z > box2Min.z &&	// ������
		box1Min.z < box2Max.z)		// ��O
	{
		
		// ��
		if (box1Max.y > box2Min.y && pPosOld.y <= box2Min.y)
		{
			// ��
			nSurFace = SURFACE_DOWN;
		}
		// ��
		if (box1Min.y < box2Max.y && pPosOld.y >= box2Max.y)
		{
			// ��
			nSurFace = SURFACE_UP;
		}
		// ��
		if (box1Max.x > box2Min.x && pPosOld.x <= box2Min.x)
		{
			// ��
			nSurFace = SURFACE_LEFT;
		}
		// �E
		if (box1Min.x < box2Max.x && pPosOld.x >= box2Max.x)
		{
			// �E
			nSurFace = SURFACE_RIGHT;
		}
	}
	// ���������ʂ�Ԃ�
	return nSurFace;
}

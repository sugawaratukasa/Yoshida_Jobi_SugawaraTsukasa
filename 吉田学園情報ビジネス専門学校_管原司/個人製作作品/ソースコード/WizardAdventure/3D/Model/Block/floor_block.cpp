//******************************************************************************
// �u���b�N[block.cpp]
// Author : �ǌ� �i
//******************************************************************************

//******************************************************************************
//�C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "../3D/Model/model.h"
#include "../3D/Model/Object/3d_obj.h"
#include "../3D/Model/Enemy/enemy_map.h"
#include "../3D/3DPolygon/Particle/Particle_Effect/particle_effect.h"
#include "floor_block.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define POS	(D3DXVECTOR3(pos.x,pos.y,pos.z - 15.0f))
//******************************************************************************
//�ÓI�����o�ϐ�
//******************************************************************************

//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CFloor_Block::CFloor_Block(int nPriority) : C3D_Obj(nPriority)
{
	m_Type = TYPE_NORMAL;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CFloor_Block::~CFloor_Block()
{

}
//******************************************************************************
// �����֐�
//******************************************************************************
CFloor_Block * CFloor_Block::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, TYPE type)
{
	// CObj_Floor�̃|�C���^
	CFloor_Block *pFloor = NULL;

	// NULL�̏ꍇ
	if (pFloor == NULL)
	{
		// �������m��
		pFloor = new CFloor_Block;

		// NULL�łȂ��ꍇ
		if (pFloor != NULL)
		{
			// ���ݒ�
			pFloor->SetModel(pos, rot, size, C3D_Obj::TYPE_FLOOR_01);

			// ��ޑ��
			pFloor->m_Type = type;

			// ������
			pFloor->Init();
		}
	}
	// �|�C���^��Ԃ�
	return pFloor;
}
//******************************************************************************
// ����������
//******************************************************************************
HRESULT CFloor_Block::Init(void)
{
	// ������
	C3D_Obj::Init();

	// �ʒu
	D3DXVECTOR3 pos = GetPos();

	// ENEMY�̏ꍇ
	if (m_Type == TYPE_ENEMY)
	{
		// �G�t�F�N�g����
		CParticle_Effect::Create(POS, CParticle_Effect::TYPE_BLOCK_EFFECT);
	}
	return S_OK;
}
//******************************************************************************
// �I������
//******************************************************************************
void CFloor_Block::Uninit(void)
{
	// �I��
	C3D_Obj::Uninit();
}
//******************************************************************************
// �X�V����
//******************************************************************************
void CFloor_Block::Update(void)
{
	// �X�V
	C3D_Obj::Update();

	// �ʒu
	D3DXVECTOR3 pos = GetPos();

	// ENEMY�̏ꍇ
	if (m_Type == TYPE_ENEMY)
	{
		// CScene�̃|�C���^
		CScene *pScene = NULL;
		do 
		{
			// �V�[���擾
			pScene = GetScene(OBJTYPE_ENEMY_MAP);

			// NULL�łȂ��ꍇ
			if (pScene != NULL)
			{
				// �I�u�W�F�N�g�^�C�v�擾
				OBJTYPE objtype = pScene->GetObjType();

				// ENEMY_MAP�̏ꍇ
				if (objtype == OBJTYPE_ENEMY_MAP)
				{
					// ����擾
					bool bEnd = ((CEnemy_Map*)pScene)->GetbEnd();

					// true�̏ꍇ
					if (bEnd == true)
					{
						// �G�t�F�N�g����
						CParticle_Effect::Create(POS, CParticle_Effect::TYPE_BLOCK_EFFECT);

						// �I��
						Uninit();
						return;
					}
				}

			}
			// NULL�ɂȂ�܂ŌJ��Ԃ�
		} while (pScene != NULL);
	}
}

//******************************************************************************
// �`�揈��
//******************************************************************************
void CFloor_Block::Draw(void)
{
	// �`��
	C3D_Obj::Draw();
}
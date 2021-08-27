//******************************************************************************
// ���X�g�\�� [scene.cpp]
// Author : �ǌ��@�i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "scene.h"
#include "scene2d.h"

//******************************************************************************
// �ÓI�����o�ϐ��錾
//******************************************************************************
CScene *CScene::m_pTop[OBJTYPE_MAX] = {};
CScene *CScene::m_pCur[OBJTYPE_MAX] = {};
int CScene::m_nNext = INIT_INT;
bool CScene::m_bUpdateStop = false;

//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CScene::CScene(int nPriority)
{
	// m_pNext��NULL
	m_pNext = NULL;

	// m_pPrev��NULL
	m_pPrev = NULL;

	//�g�b�v��NULL�̎�
	if (m_pTop[nPriority] == NULL)
	{
		m_pTop[nPriority] = this;
	}
	//�g�b�v��NULL����Ȃ��Ƃ�
	else
	{
		m_pPrev = m_pCur[nPriority];
		m_pCur[nPriority]->m_pNext = this;
	}

	// m_pNext��NULL
	m_pNext = NULL;

	// m_pCur�ɑ��
	m_pCur[nPriority] = this;

	// �I�u�W�F�N�g�^�C�v������
	m_objType = OBJTYPE_NONE;

	// Priority���
	m_nPriority = nPriority;

	// ���S�t���O��false��
	m_bDeath = false;
}

//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CScene::~CScene()
{

}

//******************************************************************************
// �I�u�W�F�N�g�^�C�v�ݒ�
//******************************************************************************
void CScene::SetObjType(OBJTYPE objType)
{
	// �I�u�W�F�N�g�^�C�v���
	m_objType = objType;
}

//******************************************************************************
// �V�[���̎擾
//******************************************************************************
CScene * CScene::GetScene(int nPriority)
{
	// pScene��m_pTop���
	CScene *pScene = m_pTop[nPriority];

	// m_nNext�̕�������
	for (int nCount = INIT_INT; nCount < m_nNext; nCount++)
	{
		// NULL�`�F�b�N
		if (pScene != NULL)
		{
			// Next�̏��̕ێ�
			CScene *pSceneNext = pScene->m_pNext;

			// Next�̏���pScene�ɓ����
			pScene = pSceneNext;
		}
	}

	// m_nNext�̉��Z
	m_nNext++;

	// pScene��NULL�̎�
	if (pScene == NULL)
	{
		m_nNext = INIT_INT;
	}
	// �|�C���^��Ԃ�
	return pScene;
}

//******************************************************************************
// �S�j�������֐�
//******************************************************************************
void CScene::ReleaseAll(void)
{
	// �I�u�W�F�N�g�^�C�v�̍ő吔���J��Ԃ�
	for (int nCount = INIT_INT; nCount < OBJTYPE_MAX; nCount++)
	{
		// pScene��m_pTop����
		CScene *pScene = m_pTop[nCount];

		// pScene��NULL�łȂ��ꍇ
		while (pScene != NULL)
		{
			// pSave��pScene��m_pNext��ۑ�
			CScene *pSave = pScene->m_pNext;
			// �I��
			pScene->Release();
			// pScene��pSave����
			pScene = pSave;
		}
	}
	// �I�u�W�F�N�g�^�C�v�̍ő吔���J��Ԃ�
	for (int nCount = INIT_INT; nCount < OBJTYPE_MAX; nCount++)
	{
		// pScene��m_pTop����
		CScene *pScene = m_pTop[nCount];

		// pScene��NULL�łȂ��ꍇ
		while (pScene != NULL)
		{
			// pSave��pScene��m_pNext����
			CScene *pSave = pScene->m_pNext;

			// pScene�̎��Sm_bDeathtrue�̏ꍇ
			if (pScene->m_bDeath == true)
			{
				// pScene��m_pPrev��NULL�łȂ��ꍇ
				if (pScene->m_pPrev != NULL)
				{
					// pScene��m_pPrev��m_pNext��pScene��m_pNext�ɂ���
					pScene->m_pPrev->m_pNext = pScene->m_pNext;
				}
				// pScene��m_pNext��NULL�łȂ��ꍇ
				if (pScene->m_pNext != NULL)
				{
					// pScene��m_pNext��m_pPrev��pScene��m_pPrev�ɂ��� 
					pScene->m_pNext->m_pPrev = pScene->m_pPrev;
				}
				// m_pTop��pScene�̏ꍇ
				if (m_pTop[nCount] == pScene)
				{
					// m_pTop��pScene��m_pNext�ɂ���
					m_pTop[nCount] = pScene->m_pNext;
				}
				// m_pCur��pScene�̏ꍇ
				if (m_pCur[nCount] == pScene)
				{
					// m_pCur��pScene��m_pPrev�ɂ���
					m_pCur[nCount] = pScene->m_pPrev;
				}

				// �I�u�W�F�N�g��j��
				delete pScene;
			}

			// pScene�ɕۑ����Ă����|�C���^����
			pScene = pSave;
		}
	}
}
//******************************************************************************
// �w��j���֐�
//******************************************************************************
void CScene::DesignationReleaseAll(OBJTYPE type)
{
	// �I�u�W�F�N�g�^�C�v�ő吔���J��Ԃ�
	for (int nCount = INIT_INT; nCount < OBJTYPE_MAX; nCount++)
	{
		// �w�肵���^�C�v�o�Ȃ��ꍇ
		if (nCount != type)
		{
			// pScene��m_pTop����
			CScene *pScene = m_pTop[nCount];

			// pScene��NULL�ɂȂ�܂ŌJ��Ԃ�
			while (pScene != NULL)
			{
				//�I������
				CScene *pSave = pScene->m_pNext;
				pScene->Release();
				pScene = pSave;
			}
		}
	}

	// �I�u�W�F�N�g�^�C�v�ő吔���J��Ԃ�
	for (int nCount = INIT_INT; nCount < OBJTYPE_MAX; nCount++)
	{
		// pScene��m_pTop����
		CScene *pScene = m_pTop[nCount];

		// pScene��NULL�ɂȂ�܂ŌJ��Ԃ�
		while (pScene != NULL)
		{
			// pScene��m_pNext��ۑ�
			CScene *pSave = pScene->m_pNext;

			// ���S�t���O��true�̏ꍇ
			if (pScene->m_bDeath == true)
			{
				// pScene��m_pPrev��NULL�łȂ��ꍇ
				if (pScene->m_pPrev != NULL)
				{
					// pScene��m_pPrev��m_pNext��pScene��m_pNext�ɂ���
					pScene->m_pPrev->m_pNext = pScene->m_pNext;
				}
				// pScene��m_pNext��NULL�łȂ��ꍇ
				if (pScene->m_pNext != NULL)
				{
					// pScene��m_pNext��m_pPrev��pScene��m_pPrev�ɂ���
					pScene->m_pNext->m_pPrev = pScene->m_pPrev;
				}
				// pScene��m_pTop�������ꍇ
				if (m_pTop[nCount] == pScene)
				{
					// m_pTop��pScene��m_pNext�ɂ���
					m_pTop[nCount] = pScene->m_pNext;
				}
				// pScene��m_pCur�Ƃ������ꍇ
				if (m_pCur[nCount] == pScene)
				{
					// m_pCur��pScene��m_pPrev�ɂ���
					m_pCur[nCount] = pScene->m_pPrev;
				}

				//�I�u�W�F�N�g��j��
				delete pScene;
			}
			// pScene�ɕۑ����Ă����̂�������
			pScene = pSave;
		}
	}
}
//******************************************************************************
// �X�V��~�֐�
//******************************************************************************
void CScene::SetUpdateStop(bool bUpdateStop)
{
	m_bUpdateStop = bUpdateStop;
}

//******************************************************************************
// �S�X�V����
//******************************************************************************
void CScene::UpdateAll(void)
{
	// �X�V��~�ϐ���false�̏ꍇ
	if (m_bUpdateStop == false)
	{
		// �I�u�W�F�N�g�^�C�v�̍ő吔���J��Ԃ�
		for (int nCount = INIT_INT; nCount < OBJTYPE_MAX; nCount++)
		{
			// pScene��m_pTop����
			CScene *pScene = m_pTop[nCount];

			// pScene��NULL�ɂȂ�܂ŌJ��Ԃ�
			while (pScene != NULL)
			{
				// pScene��m_pNext��ۑ�
				CScene *pSave = pScene->m_pNext;

				// ���S�t���O��false�̏ꍇ
				if (pScene->m_bDeath == false)
				{
					//�X�V����
					pScene->Update();
				}
				// �ۑ����Ă������̂���
				pScene = pSave;
			}
		}
	}
	else
	{
		// pScene��m_pTop����
		CScene *pScene = m_pTop[OBJTYPE_TUTORIAL];

		// pScene��NULL�ɂȂ�܂ŌJ��Ԃ�
		while (pScene != NULL)
		{
			// pScene��m_pNext��ۑ�
			CScene *pSave = pScene->m_pNext;

			// ���S�t���O��false�̏ꍇ
			if (pScene->m_bDeath == false)
			{
				//�X�V����
				pScene->Update();
			}
			// �ۑ����Ă������̂���
			pScene = pSave;
		}
	}
	// �I�u�W�F�N�g�^�C�v�̍ő吔���J��Ԃ�
	for (int nCount = INIT_INT; nCount < OBJTYPE_MAX; nCount++)
	{
		// pScene��m_pTop����
		CScene *pScene = m_pTop[nCount];

		// pScene��NULL�ɂȂ�܂ŌJ��Ԃ�
		while (pScene != NULL)
		{
			// pScene��m_pNext��ۑ�
			CScene *pSave = pScene->m_pNext;

			// ���S�t���O��true�̏ꍇ
			if (pScene->m_bDeath == true)
			{
				// pScene��m_pPrev��NULL�łȂ��ꍇ
				if (pScene->m_pPrev != NULL)
				{
					// pScene��m_pPrev��m_pNext��pScene��m_pNext�ɂ���
					pScene->m_pPrev->m_pNext = pScene->m_pNext;
				}
				// pScene��m_pNext��NULL�łȂ��ꍇ
				if (pScene->m_pNext != NULL)
				{
					// pScene��m_pNext��m_pPrev��pScene��m_pPrev�ɂ���
					pScene->m_pNext->m_pPrev = pScene->m_pPrev;
				}
				// pScene��m_pTop�������ꍇ
				if (m_pTop[nCount] == pScene)
				{
					// m_pTop��pScene��m_pNext�ɂ���
					m_pTop[nCount] = pScene->m_pNext;
				}
				// pScene��m_pCur�Ƃ������ꍇ
				if (m_pCur[nCount] == pScene)
				{
					// m_pCur��pScene��m_pPrev�ɂ���
					m_pCur[nCount] = pScene->m_pPrev;
				}

				//�I�u�W�F�N�g��j��
				delete pScene;
			}
			// �ۑ������Ă������̂���
			pScene = pSave;
		}
	}
}

//******************************************************************************
// �S�`��֐�
//******************************************************************************
void CScene::DrawAll(void)
{
	// �I�u�W�F�N�g�^�C�v�̍ő吔���J��Ԃ�
	for (int nCountpriority = INIT_INT; nCountpriority < OBJTYPE_MAX; nCountpriority++)
	{
		// pScene��m_pTop����
		CScene*pScene = m_pTop[nCountpriority];
		CScene*pSceneNext = NULL;

		// pScene��NULL�ɂȂ�܂ŌJ��Ԃ�
		while (pScene != NULL)
		{
			// pSceneNext��pScene��m_pNext����
			pSceneNext = pScene->m_pNext;

			// �`��
			pScene->Draw();

			// pScene��pSceneNext����
			pScene = pSceneNext;
		}
	}
}

//******************************************************************************
// ���S�t���O�𗧂Ă�֐�
//******************************************************************************
void CScene::Release(void)
{
	//���S�t���O�𗧂Ă�
	m_bDeath = true;
}
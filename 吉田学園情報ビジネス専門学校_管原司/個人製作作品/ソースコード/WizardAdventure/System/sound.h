//******************************************************************************
// �T�E���h���� [sound.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _SOUND_H_
#define _SOUND_H_
//******************************************************************************
// �t�@�C���C���N���[�h
//******************************************************************************
#include <xaudio2.h>
//******************************************************************************
// �}�N����`
//******************************************************************************
class CSound
{
public:
	typedef enum
	{
		SOUND_LABEL_BGM_TITLE = 0,		// BGM�^�C�g��
		SOUND_LABEL_BGM_GAME,			// BGM�Q�[��
		SOUND_LABEL_BGM_RESULT,			// BGM���U���g
		SOUND_LABEL_SE_WALK,			// �ړ���
		SOUND_LABEL_SE_BLOCK_CREATE,	// ������
		SOUND_LABEL_SE_SELECT,			// �I����
		SOUND_LABEL_SE_DETERMINATION,	// ���艹
		SOUND_LABEL_SE_FIRE_BALL,		// �΂̋�
		SOUND_LABEL_SE_FIRE_EXPLOSION,	// ������
		SOUND_LABEL_SE_ICE_EXPLOSION,	// ������
		SOUND_LABEL_SE_BUTTON_PUSH,		// �{�^������������
		SOUND_LABEL_SE_GATE_OPEN,		// �����J������
		SOUND_LABEL_SE_RESPAWN,			// ���X�|�[����
		SOUND_LABEL_MAX					// �ő�
	} SOUND_LABEL;
	typedef enum
	{
		TYPE_LOOP = -1,
		TYPE_SE,
		TYPE_MAX
	}TYPE;
	CSound();
	~CSound();
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

private:
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	}PARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	IXAudio2 *m_pXAudio2;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;				// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
	static PARAM m_aParam[SOUND_LABEL_MAX];					// �e���f�ނ̃p�����[�^
};
#endif
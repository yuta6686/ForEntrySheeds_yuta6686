#pragma once
//-------------------------------
//	[Tutorial.h]	
//-------------------------------
//	create -> ���V�D��
//	
//-------------------------------
#include "main.h"
#include "sound.h"


struct TUTORIAL_INFO {
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;

	bool use;
};

//	�y�[�W�Ǘ�
enum TUTORIAL {
	TUTORIAL_NONE,
	TUTORIAL_001,
	TUTORIAL_002,
	TUTORIAL_003,
	TUTORIAL_004,
	TUTORIAL_005,
	TUTORIAL_MAX,
};

class Tutorial
{

private:	//	�w�b�_�[���Œl���`����ϐ��͂����ɏ���

	//�y�[�W�Ǘ��ϐ�
	int m_nowPage = TUTORIAL_001;

	char m_TexName_001[128] = "data/TEXTURE/Tutorial_001.png";
	char m_TexName_002[128] = "data/TEXTURE/Tutorial_002.png";
	char m_TexName_003[128] = "data/TEXTURE/Tutorial_003.png";
	char m_TexName_004[128] = "data/TEXTURE/Tutorial_005.png";
	char m_TexName_005[128] = "data/TEXTURE/Tutorial_004.png";

	int m_Music;
	char m_MusName[128] = "data/BGM/nohohonkissa.wav";


private:

private:
	//	�����V��������
//	�����o�ϐ�	

	//	���_�f�[�^
	TUTORIAL_INFO m_Obj[TUTORIAL_MAX];

	//	�e�N�X�`���[�̕ۑ��p�ϐ�
	int m_TexIndex_001;
	//int m_TexIndex_001_hoge;
	int m_TexIndex_002;
	int m_TexIndex_003;
	int m_TexIndex_004;
	int m_TexIndex_005;

	//	�����o�֐�

		//	�e�N�X�`�����[�h
	void TutorialTextureLoad();

	//-------------------------------
	//	Init
	//-------------------------------
	void TutorialInit_001();
	void TutorialInit_002();
	void TutorialInit_003();
	void TutorialInit_004();
	void TutorialInit_005();

	//-------------------------------
	//	Update
	//-------------------------------
	void TutorialUpdate_001();
	void TutorialUpdate_002();
	void TutorialUpdate_003();
	void TutorialUpdate_004();
	void TutorialUpdate_005();
	void TutorialUpdate_Max();

	void ObjUseManag();
	//-------------------------------
	//	Draw
	//-------------------------------
	void TutorialDraw_001();
	void TutorialDraw_002();
	void TutorialDraw_003();
	void TutorialDraw_004();
	void TutorialDraw_005();


	//	�p�u���b�N�͊�{�����Ȃ��I
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};



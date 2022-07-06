#pragma once
//#include "StageObject.h"

// �o�^�V�[���ꗗ
enum SCENE
{
	SCENE_NONE,			//�V�[�������Ȃ�
	SCENE_TITLE,		//�^�C�g��
	SCENE_CREDIT,		//�N���W�b�g
	SCENE_SELECT_STAGE,	//�X�e�[�W�I��
	SCENE_TUTORIAL,		//�`���[�g���A��
	SCENE_GAME,			//�Q�[��
	SCENE_RESULT,		//���U���g
	SCENE_GAMEOVER,		//�Q�[���I�[�o�[

	SCENE_MAX			//�Ōゾ�Ƃ킩��z�������
};

void InitScene(SCENE index);
void UninitScene(void);
void UpdateScene(void);
void DrawScene(void);

void SetScene(SCENE index);
void CheckScene(void);

void SetStageNum(int sn);
int GetStageNum(void);
void AddStageNum(void);
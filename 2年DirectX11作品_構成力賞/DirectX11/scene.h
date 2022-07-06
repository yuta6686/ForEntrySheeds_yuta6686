/*==============================================================================

   �V�[���Ǘ� [scene.cpp]
														 Author :Yanagisawa Yuta
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include <vector>

#include "SelectSkill.h"

#define A_STAGE_NUM_MAX 10

// �o�^�V�[���ꗗ
enum SCENE
{
	SCENE_NONE,		//�V�[�������Ȃ�
	SCENE_TITLE,	//�^�C�g��
	SCENE_TUTORIAL,	//�`���[�g���A��
	SCENE_GAME,		//�Q�[��
	SCENE_RESULT,	//���U���g

	SCENE_MAX		//�Ōゾ�Ƃ킩��z�������
};

void InitScene(SCENE index);
void UninitScene(void);
void UpdateScene(void);
void DrawScene(void);

void SetScene(SCENE index);
void CheckScene(void);

bool GetOnceTutorial();
void SetOnceTutorial(bool flag);



SkillManager* GetSkillManager_Scene(void);

int* GetStageNum(void);
void AddStageNum(int value);
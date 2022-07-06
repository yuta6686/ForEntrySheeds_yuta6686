/*==============================================================================

   �V�[���Ǘ� [scene.cpp]
														 Author :Yanagisawa Yuta
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/

#include "scene.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "Tutorial.h"



/*------------------------------------------------------------------------------
   �萔��`
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   �\���̐錾
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   �v���g�^�C�v�錾
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   �O���[�o���ϐ��̒�`
------------------------------------------------------------------------------*/
static SCENE g_SceneIndex = SCENE_NONE;
static SCENE g_SceneNextIndex = g_SceneIndex;

static Tutorial g_Tutorial;

static bool g_OnceTutorial;



//	�S�X�L���Ǘ���
static SkillManager g_SkillManager;

//	�X�e�[�W�ԍ�
static int g_StageNum;
/*------------------------------------------------------------------------------
   �Q�b�^�[�Z�b�^�[
------------------------------------------------------------------------------*/
int* GetStageNum(void) { return &g_StageNum; }
void AddStageNum(int value) { g_StageNum += value; }

SkillManager* GetSkillManager_Scene(void) { return &g_SkillManager; }



bool GetOnceTutorial() { return g_OnceTutorial; }
void SetOnceTutorial(bool flag) { g_OnceTutorial = flag; }

/*------------------------------------------------------------------------------
   �������֐�
------------------------------------------------------------------------------*/
void InitScene(SCENE index)
{
	

	g_SceneIndex = g_SceneNextIndex = index;

	switch (g_SceneIndex)
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		InitTitle();
		break;

	case SCENE_TUTORIAL:
		g_Tutorial.Init();
		break;

	case SCENE_GAME:
		InitGame();
		break;


	case SCENE_RESULT:
		InitResult();
		break;
	}
}

/*------------------------------------------------------------------------------
   �I������������֐�
------------------------------------------------------------------------------*/
void UninitScene(void)
{
	switch (g_SceneIndex)
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		UninitTitle();
		break;

	case SCENE_TUTORIAL:
		g_Tutorial.Uninit();
		break;

	case SCENE_GAME:
		UninitGame();
		break;


	case SCENE_RESULT:
		UninitResult();
		break;
	}
}

/*------------------------------------------------------------------------------
   �X�V����������֐�
------------------------------------------------------------------------------*/
void UpdateScene(void)
{
	switch( g_SceneIndex ) 
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		UpdateTitle();
		break;

	case SCENE_TUTORIAL:
		g_Tutorial.Update();
		break;

	case SCENE_GAME:
		UpdateGame();
		break;

	case SCENE_RESULT:
		UpdateResult();
		break;
	}

	UpdateFade();
}

/*------------------------------------------------------------------------------
   �`�揈��������֐�
------------------------------------------------------------------------------*/
void DrawScene(void)
{
	switch( g_SceneIndex )
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		DrawTitle();
		break;

	case SCENE_TUTORIAL:
		g_Tutorial.Draw();
		break;

	case SCENE_GAME:
		DrawGame();
		break;		

	case SCENE_RESULT:
		DrawResult();
		break;
	}

	DrawFade();
}

/*------------------------------------------------------------------------------
   �V�[���J�ڂ�v������֐�
------------------------------------------------------------------------------*/
void SetScene(SCENE index)
{
	//�J�ڐ�V�[����ݒ肷��
	g_SceneNextIndex = index;
}

/*------------------------------------------------------------------------------
   �J�ڂ�v��������ꍇ�ɃV�[����؂�ւ���֐�
------------------------------------------------------------------------------*/
void CheckScene(void)
{
	//���݂̃V�[���ƑJ�ڐ�V�[��������Ă�����
	if( g_SceneIndex != g_SceneNextIndex )
	{
		//���݂̃V�[�����I��������
		UninitScene();
		
		//�J�ڐ�V�[���̏������������s��
		InitScene(g_SceneNextIndex);
	}
}

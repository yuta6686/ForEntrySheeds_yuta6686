/*==============================================================================

   �Q�[������ [game.cpp]
														 Author :Yanagisawa Yuta
														 Date   :~~~~~~~~~~~~~~~
--------------------------------------------------------------------------------

==============================================================================*/

#include "game.h"
#include "main.h"
#include "input.h"
#include "fade.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "meshfield.h"
#include "collision.h"
#include "sound.h"
#include "score.h"
#include "camera.h"
#include "light.h"
#include "shadow.h"
#include "GameFramework.h"



/*------------------------------------------------------------------------------
   �O���[�o���ϐ��̒�`
------------------------------------------------------------------------------*/
static int g_BGMNo = 0;
static GameFramework g_GameFramework;

static SelectSkill g_SelectSkill;

static Eff_Clear g_ClearEffect;

static UInew_Manager g_UImanager;

UInew_Manager* GetUIManager() { return &g_UImanager; }

Eff_Clear* GetClearEffect() { return &g_ClearEffect; }

//	true  = �X�L���I����Ԓ�
//	false = �Q�[����
bool g_SelectSkillState = false;

/*------------------------------------------------------------------------------
   �֐��錾�E��`
------------------------------------------------------------------------------*/

/*
//	true  = �X�L���I����Ԓ�
//	false = �Q�[����
bool g_SelectSkillState;
*/
bool GetSelectSkillState(void) { return g_SelectSkillState; }
void ChangeSelectSkillState(bool flag) { g_SelectSkillState = flag; }

/*------------------------------------------------------------------------------
   �������֐�
------------------------------------------------------------------------------*/
void InitGame(void)
{
	// �J�����̏�����
	InitCamera();

	// ���C�g�̏�����
	InitLight();

	// �e�̏�����
	InitShadow();

	g_GameFramework.Init();

	// �n�ʂ̏�����
	InitMeshField(D3DXVECTOR3(0.0f, -1001.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, 10, 100.0f, 100.0f);


	// �e�̏�����
	InitBullet();

	// �X�R�A�̏�����
	InitScore();

	//	�Q�[���N���A���̃G�t�F�N�g������
	g_ClearEffect.Init();

	SetLightEnable(true);

	//  �X�L���I������������
	g_SelectSkill.Init();

	//	UI�Ǘ�������
	g_UImanager.Init();

	g_BGMNo = LoadSound((char*)"data/BGM/kanatanouchuu.wav");

	SetVolume(g_BGMNo, 0.25f);
	PlaySound(g_BGMNo, -1);
}

/*------------------------------------------------------------------------------
   �I������������֐�
------------------------------------------------------------------------------*/
void UninitGame()
{
	//�������Ƃ͋t���ɏI���������s��
	g_GameFramework.Uninit();

	//	�X�R�A�I������
	UninitScore();

	//	�Q�[���N���A�G�t�F�N�g�I������
	g_ClearEffect.Uninit();

	//	�e�I������
	UninitShadow();

	//	�o���b�g�I������
	UninitBullet();

	//	���b�V���t�B�[���h�I������
	UninitMeshField();

	//	�X�L���I���I������
	g_SelectSkill.Uninit();

	//	UI�I������
	g_UImanager.Uninit();

	//	�X�e�[�W�ԍ����Z�b�g
	*GetStageNum() = 0;
}

/*------------------------------------------------------------------------------
   �X�V����������֐�
------------------------------------------------------------------------------*/
void UpdateGame(void)
{
	
	// �J�����X�V
	UpdateCamera();

	// �n�ʂ̍X�V����
	UpdateMeshField();

	g_GameFramework.Update();

	// �e�̍X�V����
	UpdateShadow();

	// �e�̍X�V����
	UpdateBullet();

	//	�X�L���I��
	if (g_SelectSkillState) {
		g_SelectSkill.Update();
	}

	// �X�R�A�̍X�V����
	UpdateScore();

	//	�N���A�G�t�F�N�g�X�V����
	g_ClearEffect.Update();

	//	UI�X�V����
	g_UImanager.Update();

	// �����蔻��̍X�V����
	UpdateCollision();
}

/*------------------------------------------------------------------------------
   �`�揈��������֐�
------------------------------------------------------------------------------*/
void DrawGame(void)
{
	// �v���C���[���_
	//D3DXVECTOR3 pos = GetPlayer()->pos;
	//pos.y = 0.0f;			// �J����������h�����߂ɃN���A���Ă���
	//SetCameraAT(pos);
	//SetCamera();

	// �[�x�e�X�g�L��
	SetDepthEnable(true);

	// ���C�e�B���O�L��
	SetLightEnable(true);

	// �n�ʂ̕`�揈��
	DrawMeshField();

	// �e�̕`�揈��
	DrawShadow();

	g_GameFramework.Draw();

	// �e�̕`�揈��
	DrawBullet();

	// �}�g���N�X�ݒ�
	SetWorldViewProjection2D();//���W��2D�ϊ�

	// 2D�`��Ȃ̂Ő[�x����
	SetDepthEnable(false);

	// �X�R�A�̕`�揈��
	//DrawScore();

	//	�N���A�G�t�F�N�g�`�揈��
	g_ClearEffect.Draw();

	//	UI�X�V�`�揈��
	g_UImanager.Draw();

	//	�X�L���I����ԂȂ�`��
	if (g_SelectSkillState) {
		g_SelectSkill.Draw();
	}
	
}


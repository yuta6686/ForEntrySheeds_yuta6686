//---------------------------------------------
//	[GameFramework.cpp]
// --------------------------------------------
//	Haruyakakoubou
//---------------------------------------------

//�C���N���[�h
#include "GameFramework.h"
#include "GameObject.h"
#include "GO_Player.h"
#include "GO_Scramble.h"
#include "GO_ScrambleRotation.h"
#include "GO_Throw.h"
#include "GO_Timer.h"
#include "GO_Fall.h"
#include "GO_Bungee.h"
#include "GO_SS_Manager.h"
/*---------------------------------------------
				�R���X�g���N�^
---------------------------------------------*/
GameFramework::GameFramework()
{
	for (int i = 0; i < GAME_OBJECT_MAX; i++) {
		m_pGameObjects[i] = nullptr;
	}

	Create();
}

/*---------------------------------------------
				�N���G�C�g
-----------------------------------------------
	�|�C���^�������A�����A���W�X�^�[
---------------------------------------------*/
void GameFramework::Create()
{
	//null
	{
		mp_player = nullptr;
		mp_vortex = nullptr;
		mp_VoRot = nullptr;

		/*�����ŐV�����Q�[���I�u�W�F�N�g�̃|�C���^������������*/

		mp_Throw = nullptr;
		mp_Timer = nullptr;
		mp_Fall = nullptr;
		mp_Bungee = nullptr;
		mp_ssManager = nullptr;
	}


	//new
	{
		mp_player = new GO_Player;
		mp_vortex = new GO_Scramble;
		mp_VoRot = new GO_ScrambleRotation;

		/*�Q�[���I�u�W�F�N�g���I����*/

		mp_Throw = new GO_Throw;
		mp_Timer = new GO_Timer;
		mp_Fall = new GO_Fall;
		mp_Bungee = new GO_Bungee;
		mp_ssManager = new GO_SS_Manager;
	}

	//Register
	{
		Register(mp_vortex);
		Register(mp_player);
		Register(mp_VoRot);

		/*GameObject�N���X���p�����Ă�΁A�o�^�ł��܂��B*/

		Register(mp_Throw);
		Register(mp_Timer);
		Register(mp_Fall);
		Register(mp_Bungee);
		Register(mp_ssManager);
	}

}

/*---------------------------------------------
	SetGameObject()	
-----------------------------------------------
	�Q�[���I�u�W�F�N�g���ő��̃I�u�W�F�N�g���g�p�������ꍇ

	���g�̃w�b�_�[�t�@�C����Set�֐�������Ďg�p����

	*���̊֐��͏����������̍Ō�Ɏg�p
---------------------------------------------*/
void GameFramework::SetGameObject()
{
	mp_VoRot->SetPlayer(mp_player);
	mp_VoRot->SetVortex(mp_vortex);
}

/*---------------------------------------------
			�V�[���J�ڏ���
---------------------------------------------*/
/*---------------------------------------------
ex)	case GAMESCENE_SCRANBLE

	mp_Timer��use

	�ŏ���			true
	�������I����	false
	�V�[����ς���	true
---------------------------------------------*/
void GameFramework::TransitionScene()
{
	switch (m_GameScene)
	{
	case GAMESCENE_SCRAMBLE:
		//Timer��10�b�o�߂�����t���O��false�ɂȂ�
		if (!mp_Timer->GetTimerUse()) {

			//���������ɓ���Ȃ��悤�ɁAtrue��Ԃɂ��Ă���
			mp_Timer->SetTimerUse(true);

			//�V�[�����ς���Timer��Update���������Ȃ�
			m_GameScene = GAMESCENE_FALL;
		}
		break;

	case GAMESCENE_FALL:
		if (!mp_Fall->GetIsTransition()) {

			mp_Fall->SetIsTransition(true);

			m_GameScene = GAMESCENE_BUNGEE_JUMP;
		}
		break;

	case GAMESCENE_BUNGEE_JUMP:
		if (mp_Bungee->GetPosY() >= SCREEN_HEIGHT) {

			m_GameScene = GAMESCENE_GAME_TEST;
		}
		break;

	case GAMESCENE_GAME_TEST:

		break;
	default:
		break;
	}

	
}

/*---------------------------------------------
*				�f�X�g���N�^
---------------------------------------------*/
GameFramework::~GameFramework()
{
	for (int i = 0; i < GAME_OBJECT_MAX; i++) {
		// nullptr��delete���Ă����v
		delete m_pGameObjects[i];
	}
}

/*---------------------------------------------
*				����������
---------------------------------------------*/
void GameFramework::Initialize(void)
{

	for (int i = 0; i < GAME_OBJECT_MAX; i++) {
		if (m_pGameObjects[i]) {
			m_pGameObjects[i]->Initialize();
		}
	}

	SetGameObject();
	
}

/*---------------------------------------------
*				�I������
---------------------------------------------*/
void GameFramework::Finalize(void)
{
	for (int i = 0; i < GAME_OBJECT_MAX; i++) {
		if (m_pGameObjects[i]) {
			m_pGameObjects[i]->Finalize();
		}
	}
}

/*---------------------------------------------
*				�X�V����
---------------------------------------------*/
void GameFramework::Update(void)
{
	TransitionScene();

	//GameScene.h�Q�Ƃ��Ă�������
	for (int i = 0; i < GAME_OBJECT_MAX; i++) {
		if (!m_pGameObjects[i])continue;
		if (m_pGameObjects[i]->GetGameScene() != m_GameScene)continue;
		
		m_pGameObjects[i]->Update();
		
	}
}
/*---------------------------------------------
*				�`�揈��
---------------------------------------------*/
void GameFramework::Draw(void)
{
	//GameScene.h�Q�Ƃ��Ă�������
	for (int i = 0; i < GAME_OBJECT_MAX; i++) {
		if (!m_pGameObjects[i])continue;
		if (m_pGameObjects[i]->GetGameScene() != m_GameScene)continue;
			m_pGameObjects[i]->Draw();
		
	}
}

/*---------------------------------------------
*				�o�^����
---------------------------------------------*/
void GameFramework::Register(GameObject* pGameObject)
{
	for (int i = 0; i < GAME_OBJECT_MAX; i++) {
		if (!m_pGameObjects[i]) {
			m_pGameObjects[i] = pGameObject;
			break;
		}
	}
}


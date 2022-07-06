#pragma once
//---------------------------
//	[GameFramework.h]
//	Yuta Yanagisawa 
//---------------------------
#include "GameScene.h"

//------�O���錾
class GameObject;
class Enemy;
class GO_Player;
class Collision;
class GO_Scramble;
class GO_ScrambleRotation;
class GO_Throw;
class GO_Timer;
class GO_Fall;
class GO_Bungee;
class GO_SS_Manager;

//�N���X�@�Q�[���t���[�����[�N
class GameFramework {
public:
	GameFramework();
	~GameFramework();

	void Initialize(void);
	void Finalize(void);
	void Update(void);
	void Draw(void);

	//m_pGameObjects[]��GameObject���l�ߍ���
	void Register(GameObject* pGameObject);

private:
	static const int GAME_OBJECT_MAX = 100;

	//GameObject�̃|�C���^
	GameObject* m_pGameObjects[GAME_OBJECT_MAX];

	GO_Player* mp_player;
	GO_Scramble* mp_vortex;
	GO_ScrambleRotation* mp_VoRot;
	GO_Throw* mp_Throw;
	GO_Timer* mp_Timer;
	GO_Fall* mp_Fall;
	GO_Bungee* mp_Bungee;
	GO_SS_Manager* mp_ssManager;

	//GameScene
	int m_GameScene = GAMESCENE_GAME_TEST;

	/*
	* GAMESCENE_SCRAMBLE
	* GAMESCENE_FALL
	* GAMESCENE_BUNGEE_JUMP
	* GAMESCENE_GAME_TEST
	*/

	//nullptr����[��new�œ��I�����[��Register�o�^���܂Ƃ߂Ă��ꏊ�B
	//�R���X�g���N�^�Ŏg�p
	void Create();

	//���̃Q�[���t���[�����[�N�Ɋ��������ꍇ�g�p
	void SetGameObject();


	void SetGameScene(int GameScene) { m_GameScene = GameScene; }

	void TransitionScene();
};

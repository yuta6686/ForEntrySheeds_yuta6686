#pragma once
//---------------------------
//	[GameScene.h]
//	Yuta Yanagisawa 
//---------------------------

//�Q�[�����ł̃V�[���J�ڂ��Ǘ����܂��B


enum GAMESCENE{
    GAMESCENE_NONE,
    GAMESCENE_SCRAMBLE,         //�[��������V�[��
    GAMESCENE_FALL,             //������V�[��
    GAMESCENE_BUNGEE_JUMP,      //�o���W�[�W�����v�̃V�[��
    GAMESCENE_GAME_TEST,
    GAMESCENE_MAX
};

class GameScene
{
public:
    int m_GameScene = GAMESCENE_BUNGEE_JUMP;
};


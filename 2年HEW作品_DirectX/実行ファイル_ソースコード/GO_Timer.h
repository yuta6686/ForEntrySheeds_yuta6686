//---------------------------------------------
//	�^�C�}�[�v��	[GO_Timer.h]	Author: Yanagisawa
//---------------------------------------------
// 1���ځ`�����_���ʂ܂ł̕\��
//  
//---------------------------------------------
#pragma once

#include"GameObject.h"

class GO_Timer:
	public GameObject
{
public:
	// GameObject ����Čp������܂���
	virtual void Initialize(void) override;
	virtual void Finalize(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;
	virtual int GetGameScene(void) override { return GAME_SCENE;};


	//	GameScene�p�̂��
	bool GetTimerUse(void) { return Timer_Vertex.use; }
	void SetTimerUse(bool flag) { Timer_Vertex.use = flag; }

private:
//--------------------------------------------------------
//	�����o�ϐ�
//--------------------------------------------------------

	//	Texture�p�ϐ�
	char TEX_NAME[128] = "data/TEXTURE/number2.png";
	int Number_Texture;

	//	GameScene�p�ϐ�
	const int GAME_SCENE = GAMESCENE_GAME_TEST;

	//	UV�p�̕ϐ�
	const int NUMBER_X = 4;
	const int NUMBER_Y = 4;
	const float NUMBER_WIDTH = 1.0f / (float)NUMBER_X;
	const float NUMBER_HEIGHT = 1.0f / (float)NUMBER_Y;

	//���_�f�[�^
	VERTEX_ALPHA_ANIMATION_USE Timer_Vertex;	//1����
	VERTEX_UV Timer_Second;						//�����_����
	VERTEX_UV Timer_Third;						//�����_����

//--------------------------------------------------------
//	�����o�֐�
//--------------------------------------------------------
//	What --> �ꌅ�ځ@�`�@�����_���ʂ܂ł̍X�V����
//	Why	 --> �����̂���
//--------------------------------------------------------
	void FirstNum(void);
	void SecondNum(void);
	void ThirdNum(void);
};


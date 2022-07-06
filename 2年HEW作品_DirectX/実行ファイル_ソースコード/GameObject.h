#pragma once
//---------------------------
//	[GameObject.h]
//	Yuta Yanagisawa 
//---------------------------

//�V�����Q�[���I�u�W�F�N�g���쐬����ꍇ�̓Q�[���I�u�W�F�N�g��K���p�����Ă��������B

//�p�������Ɏg�������ꍇ�͌����Ă��������B

#include "main.h"
#include "Texture.h"
#include "sprite.h"
#include "input.h"
#include "GameScene.h"

class GameObject {
public:
	GameObject(){}
	virtual ~GameObject() {}

	virtual void Initialize(void) = 0;
	virtual void Finalize(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual int GetGameScene(void) = 0;
};


#pragma once
//---------------------------
//	[GO_Player.h]
//	Yuta Yanagisawa 
//---------------------------
#include "GameObject.h"

class GO_Player :public GameObject
{
public:
	// GameObject ����Čp������܂���
	virtual void Initialize(void) override;

	virtual void Finalize(void) override;

	virtual void Update(void) override;

	virtual void Draw(void) override;

	virtual int GetGameScene(void) override { return m_GameScene; }

	D3DXVECTOR2 GetPos() { return Player_Vertex.pos; }

private:
	//�e�N�X�`���̃C���f�b�N�X
	int Player_Texture;

	//�e�N�X�`���̖��O
	char PLAYER_TEX_NAME[128] = "data/TEXTURE/player.png";

	VERTEX_T Player_Vertex;

	const int m_GameScene = GAMESCENE_SCRAMBLE;
};


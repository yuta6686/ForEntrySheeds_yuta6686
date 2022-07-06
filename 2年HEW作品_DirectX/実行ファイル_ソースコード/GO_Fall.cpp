//----------------------------------------------------------------------------
//  �v���C���[�������鏈���@[GO_Fall.cpp]         Author:Yanagisawa
//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
#include "GO_Fall.h"

void GO_Fall::Initialize(void)
{
	//Texture�ǂݍ���
	Texture_Fall = LoadTexture(TEX_NAME_FALL);
	Texture_Walk = LoadTexture(TEX_NAME_WALK);
	Texture_Wall = LoadTexture(TEX_NAME_WALL);

	nowTexture = Texture_Walk;

	//Fall_Vertex������
	Fall_Vertex.pos = D3DXVECTOR2(150.0f, 125.0f);
	Fall_Vertex.size = D3DXVECTOR2(200.0f, 200.0f);
	Fall_Vertex.counter = 0;
	Fall_Vertex.use = true;
}

void GO_Fall::Finalize(void)
{

}

void GO_Fall::Update(void)
{
	Jump();
}

void GO_Fall::Draw(void)
{
	DrawSprite(Texture_Wall, 100.0f, 500.0f, 200.0f, 600.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	DrawSprite(nowTexture, Fall_Vertex.pos.x, Fall_Vertex.pos.y,
		Fall_Vertex.size.x, Fall_Vertex.size.y, 1.0f,1.0f, 1.0f, 1.0f);

}

void GO_Fall::Jump()
{
	//�W�����v���Ă���(JUMPING_FRAME)�Ԃ̓C���v�b�g���󂯕t���Ȃ�
	if (!m_IsJump)
		m_IsJump = InputJump();
	
	//(JUMPING_FRAME)�O�ŉ����ĂȂ�������return;
	if (!m_IsJump)return;

	//(JUMPING_FRAME)���Ń|�W�V�����𓮂���
	if (m_JumpFrame >= JUMPING_FRAME) {
		m_JumpFrame = 0;
		m_IsJump = false;

		IsTransition = false;
	}
	else {
		m_JumpFrame++;
		Fall_Vertex.pos.x += m_RightSpeed;
		Fall_Vertex.pos.y -= m_UpSpeed;
		m_UpSpeed -= m_Gravity;
	}

	ChangeTextureFall();
}

void GO_Fall::ChangeTextureFall()
{
	if (m_JumpFrame == 30) {
		nowTexture = Texture_Fall;
	}
}


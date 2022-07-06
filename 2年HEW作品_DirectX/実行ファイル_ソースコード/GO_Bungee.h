#pragma once
#include "GameObject.h"

class GO_Bungee :
    public GameObject
{
public:
    // GameObject ����Čp������܂���
    virtual void Initialize(void) override;

    virtual void Finalize(void) override;

    virtual void Update(void) override;

    virtual void Draw(void) override;

    virtual int GetGameScene(void) override { return GAME_SCENE; }
    
    FLOAT GetPosY(void) { return Player_Vertex.pos.y; }

private:
    //�W�����v�p�ϐ�
    float m_Gravity;                        //�d��
    float m_Jump = -15.0f;                  //�W�����v
    const float GRAVITY_ACCELERATION = 0.3f;      //�d�͉����x
    const float DEFAULT_GRAVITY = 1.0f;     //�d�͂����ɖ߂��p


    //�e�N�X�`���p�ϐ�
    int Player_Texture;
    char TEX_NAME[128] = "data/TEXTURE/fall1.png";

    //�Q�[���V�[���p�ϐ�
    const int GAME_SCENE = GAMESCENE_BUNGEE_JUMP;


    //���_�f�[�^
    VERTEX_NOMAL Player_Vertex;
};


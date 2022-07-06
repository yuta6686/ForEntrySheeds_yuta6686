//----------------------------------------------------------------------------
//  �v���C���[�������鏈���@[GO_Fall.h]         Author:Yanagisawa
//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------

#pragma once
#include "GameObject.h"
class GO_Fall :
    public GameObject
{
public:
    GO_Fall(){}

    // GameObject ����Čp������܂���
    virtual void Initialize(void) override;

    virtual void Finalize(void) override;

    virtual void Update(void) override;

    virtual void Draw(void) override;

    virtual int GetGameScene(void) { return GAMESCENE_FALL; }

    //�V�[���J�ڂ̏���
    bool GetIsTransition(void) { return IsTransition; }
    void SetIsTransition(bool flag) { IsTransition = flag; }

private:

    //Texture �p�@�ϐ�
    int nowTexture = 0;

    int Texture_Fall = 0;
    char TEX_NAME_FALL[64] = "data/TEXTURE/fall1.png";

    int Texture_Walk = 0;
    char TEX_NAME_WALK[64] = "data/TEXTURE/walk1.png";

    int Texture_Wall = 0;
    char TEX_NAME_WALL[64] = "data/TEXTURE/wall.png";


    //�Q�[���V�[��
    const int GAME_SCENE = GAMESCENE_FALL;

    bool IsTransition = true;

    //���_�f�[�^
    VERTEX_ANIMATION_USE Fall_Vertex;

    //�W�����v�p�ϐ�
    bool    m_IsJump        = false;
    float   m_UpSpeed       = 8.0f;
    float   m_RightSpeed    = 2.0f;
    int     m_JumpFrame     = 0;

    const float m_Gravity       =   0.3f;
    const int   JUMPING_FRAME   =   180;

    //�W�����v�p�֐�
    bool InputJump() { return GetKeyboardTrigger(DIK_SPACE); }
    void Jump();
    void ChangeTextureFall();
};


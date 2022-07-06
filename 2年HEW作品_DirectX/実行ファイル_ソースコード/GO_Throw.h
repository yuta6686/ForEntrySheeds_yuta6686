#pragma once
#include "GameObject.h"
class GO_Throw :
    public GameObject
{
    // GameObject ����Čp������܂���
    virtual void Initialize(void) override;
    virtual void Finalize(void) override;
    virtual void Update(void) override;
    virtual void Draw(void) override;

    virtual int GetGameScene(void) override { return GAME_SCENE; }

private:
    //Texture�p�̃C���f�b�N�X
    int Throw_Texture;

    //�e�N�X�`���̖��O
    char TEX_NAME[128] = "data/TEXTURE/";

    //�Q�[���V�[��    -> GameScene.h���Q��
    const int GAME_SCENE = GAMESCENE_SCRAMBLE;

    
};


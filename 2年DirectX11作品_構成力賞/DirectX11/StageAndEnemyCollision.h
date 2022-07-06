//=============================================================================
//
// �X�e�[�W�ƃG�l�~�[�̏Փˏ��� [StageAndEnemyCollision.h]
// Author : Yanagisawa Yuta
//
// �����F�G�l�~�[���X�e�[�W�ɏՓ�
// �[���G�l�~�[�̃x�N�g���𔽓]
//=============================================================================
#pragma once
#include "GO_Collision.h"
#include "GO_Stage.h"
#include "GO_Enemy.h"

class StageAndEnemyCollision :
    public GO_Collision
{
public:
    StageAndEnemyCollision():m_pEnemy(nullptr),m_pStage(nullptr){}

    // GO_Collision ����Čp������܂���
    virtual void Init() override;

    virtual void Uninit() override;

    void Update();

    virtual void Draw() override;

    virtual bool IsCollision() override { return false; }
    virtual int IsCollisions(int index)override;

    virtual void CollisionUpdate(int index) override;

    void SetEnemy(GO_Enemy* p) { m_pEnemy = p; }
    void SetStage(GO_Stage* p) { m_pStage = p; }

private:
    GO_Stage* m_pStage;
    GO_Enemy* m_pEnemy;
};


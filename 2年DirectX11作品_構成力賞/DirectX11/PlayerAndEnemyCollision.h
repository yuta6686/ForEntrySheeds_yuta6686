//=============================================================================
//
// �v���C���[�ƃG�l�~�[�̓����蔻�� [PlayerAndEnemyCollision.h]
// Author : Yanagisawa Yuta
//
//=============================================================================
#pragma once

//  �C���N���[�h  //
#include "GO_Collision.h"
#include "GO_Enemy.h"
#include "GO_Player.h"
#include "fade.h"
#include "Eff_RockOn.h"
#include "Eff_Explosion.h"
#include <list>

//  �}�N����`
#define NO_RANGE 0.0f

class PlayerAndEnemyCollision :
    public GO_Collision
{
private:
    const float BULLETS_DIFFUSION = 5.0f;
public:
    PlayerAndEnemyCollision():
        m_pEnemy(nullptr),m_pPlayer(nullptr),
        m_pBullet(nullptr), m_pExpPoint(nullptr){}

    // GO_Collision ����Čp������܂���
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual bool IsCollision() override { return false; };



    void SetEnemy(GO_Enemy* p) { m_pEnemy = p; }
    void SetPlayer(GO_Player* p) { m_pPlayer = p; }

private:
    GO_Enemy* m_pEnemy;
    GO_Player* m_pPlayer;

    GO_Item* m_pBullet;
    GO_Item* m_pExpPoint;

    Eff_RockOn m_RockOn;
    Eff_Explosion m_Explosion;

    int m_CollExplosionIndex = -1;
    bool m_IsColl = false;

    int m_ClearEffectCounter = 0;

    //  ���݂̎˒����i�[����
    FLOAT m_Range = 0.0f;

    //  �ڋ߂��Ă���EXPPoint�̃C���f�b�N�X���i�[����
    std::list<int> ml_ExpPointIndex_Approach;

    //  �ڐG���Ă���ExpPoiint�̃C���f�b�N�X���i�[����i�ʏ�̓����蔻��)
    std::list<int> ml_ExpPointIndex_Contact;

    // GO_Collision ����Čp������܂���
    virtual int IsCollisions(int index) override;
    virtual void CollisionUpdate(int index) override;

    

    //  �A�C�e��
    void ItemUpdate();
    void ItemUpdate_Bullet();

    //  pos1����pos2�ւ̃x�N�g��
    D3DXVECTOR3 VectorOfPlayer_Set(D3DXVECTOR3 pos1 ,D3DXVECTOR3 pos2, FLOAT speed);

    void SetDiamondVec();

    //  �G�l�~�[�ƒe�̓����蔻��
    //  �������F�G�l�~�[�̃C���f�b�N�X
    //  �������F�o���b�g�̃C���f�b�N�X
    //  �߂�l  �F�G�l�~�[�̃C���f�b�N�X
    int IsCollisions_Bullets(int index, int index2);
    void CollisionUpdate_Bullet(int index, int index2);


    //  �˒����̐ڋߏ���[�v���C���[�ƌo���l]
    //  �����F�˒�
    //  �ߒl�Fbool
    //  �@�\�F�˒����ɓ�������A�v���C���[�ɋ߂Â��悤�ɂ���
    bool IsApproach(int index,FLOAT range);

    bool IsApproach(FLOAT range,D3DXVECTOR3 pos1, D3DXVECTOR3 pos2,FLOAT size1,FLOAT size2);

    std::list<int> InRangeEnemyIndex();

    //  �o���l�l�������玟�̃V�[����
    void ToNextScene();

    //  ��ԋ߂��G�l�~�[�̃C���f�b�N�X��Ԃ��֐�
    int NearestEnemy(void);

    //  ��ԋ߂��G�l�~�[�ɏƏ������킹��
    void RockOnNearestEnemy(void);

    //  �G�t�F�N�g���g���Ă��Ȃ����̏���
    void ClearEffect(void);

    //  �G�l�~�[1�̔���
    void EnemyExplosionOnece();
};


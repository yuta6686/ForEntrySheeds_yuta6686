//=============================================================================
//
// �G�l�~�[�̃C���^�t�F�[�X [GO_Enemy.h]
// Author : Yanagisawa Yuta
//
//=============================================================================
#pragma once
#include "GameObject.h"
#include "game.h"
#include "scene.h"

#define ENEMY_POS_MAX 1000.0f
#define ENEMY_SQUARE_X 23.19f
#define ENEMY_SQUARE_Y 23.95f
#define ENEMY_SQUARE_Z 22.07f

enum ENEMY_INDEX {
    ENEMY_NONE = -1,
    ENEMY_SQUARE,
    ENEMY_DIAMOND,
    ENEMY_MAX,
};

struct GAME_OBJECT_ENEMY :public GAME_OBJECT 
{
    int hp;
    int hp_max;
    bool IsDeath;
};

class GO_Enemy :
    public GameObject
{
private:
    static const int ENEMY_NUM_MAX = 500;
    static const int TIME_COUNT_MAX = 60 * 3;
    int NumOfEnemiesThatAppear = 5;
public:
    // GameObject ����Čp������܂���
    virtual void Init() override=0;

    virtual void Uninit() override=0;

    virtual void Update() override=0;

    virtual void Draw() override=0;

    //  ����
    virtual void Action() = 0;

    //  ���񂾂Ƃ��̏���
    virtual bool Death() = 0;

    virtual int ReturnIndex() = 0;

    virtual void HPLottery() {
        //	�G�l�~�[HP���I
        for (int i = 0; i < GetEnemyNumMax(); i++)
        {
            if (GetSelectSkillState())
            {
                if (this->ReturnIndex() == ENEMY_DIAMOND) {
                    m_ObjInfo[i].hp = 1 + rand() % (*GetStageNum());
                    m_ObjInfo[i].hp_max = m_ObjInfo[i].hp;
                }
                else {
                    m_ObjInfo[i].hp = 1 + rand() % (*GetStageNum() * 2);
                    m_ObjInfo[i].hp_max = m_ObjInfo[i].hp;
                }


                FLOAT scale = (0.5f + (m_ObjInfo[i].hp_max / A_STAGE_NUM_MAX)) * 5.0f;
                m_ObjInfo[i].scl = D3DXVECTOR3(scale, scale, scale);

                m_ObjInfo[i].size = D3DXVECTOR3(ENEMY_SQUARE_X * scale, ENEMY_SQUARE_Y * scale, ENEMY_SQUARE_Z * scale);
            }
        }
    }

//  �Z�b�^�[        
    //  �G�l�~�[�Z�b�g
    virtual void SetEnemy() = 0;
    virtual void SetEnemy(D3DXVECTOR3 pos) {}
    virtual void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 size) {}
    
    virtual void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 vec) {}

    void SetVec(int index, D3DXVECTOR3 vec) { m_ObjInfo[index].vec = vec; }

    void SetEnemeyVecX(int index) { m_ObjInfo[index].vec.x *= -1.0f; }
    void SetEnemeyVecY(int index) { m_ObjInfo[index].vec.y *= -1.0f; }
    void SetEnemeyVecZ(int index) { m_ObjInfo[index].vec.z *= -1.0f; }

    void SetUseFalse(int index) { m_ObjInfo[index].use = false; }

//  �Q�b�^�[    
    //  �G�l�~�[�̍ő吔�擾
    int GetEnemyNumMax() { return ENEMY_NUM_MAX; }

    //  ���Ԃ̃J�E���g�i�v���C���[������ł���A�G�t�F�N�g���I���܂ł̎��ԁj
    int GetTimeCounterMax() { return TIME_COUNT_MAX; }

    //  �G�l�~�[���ďo�����鎞�ԊԊu
    int GetNumOfEnemiesThatAppear() { return NumOfEnemiesThatAppear; }
    void SetNumOfEnemiesThatAppear(int num) { NumOfEnemiesThatAppear = num; }


    //  �G�l�~�[�̏��擾
    GAME_OBJECT_ENEMY GetObjInfo(int index) { return m_ObjInfo[index]; }

    
    //  �G�l�~�[��HP���炷����
    //  �������̓C���f�b�N�X
    //  ��Q�����̐��������炷
    void ReduceHpOfEnemy(int index, int damage) 
    { 
        if (m_ObjInfo[index].use == false)return;

        m_ObjInfo[index].hp -= damage; 

        if (m_ObjInfo[index].hp < 0) {
            m_ObjInfo[index].IsDeath = true;
            
            GetSEManager()->PlaySE(SE_TAIKO, 0.5f);
        }
        else {
            GetSEManager()->PlaySE(SE_EXPLOSION, 0.5f);
        }
    }

    //  �w�肵���G�l�~�[������ł�����True
    bool GetIsDeathEnemy(int index) {
        return m_ObjInfo[index].IsDeath;
    }

    int GetHpMax(int index)
    {
        return m_ObjInfo[index].hp_max;
    }
protected:
    DX11_MODEL  m_Model;
    GAME_OBJECT_ENEMY m_ObjInfo[ENEMY_NUM_MAX];

    
    float   m_modelAlpha;


};


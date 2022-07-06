#pragma once
#include "GameObject.h"
class NattoRotateObject :
    public GameObject
{
protected:
    static const int NATTO_MAX = 50;
    static const int FIRST_NATTO = 10;

    const FLOAT ANGLE_MIN = 0.0f;
    const FLOAT ANGLE_MAX = 0.1f;

public:    
    NattoRotateObject(char* texName){
        m_TexIndex = LoadTexture(texName);
    }

    virtual void Initialize(void) override;

    virtual void Finalize(void) override;

    virtual void Update(void) override;

    virtual void Draw(void) override;

    virtual int GetGameScene(void) override { return GAMESCENE_GAME_TEST; }

    virtual int GetTexIndex(void) { return m_TexIndex; }

    //  �Z�b�^�[  //
    // 
    //  ��������
    void SetNatto(void);
    
    //  �����L��
    // 
    //  D3DXVECTOR2
    void SetPos(D3DXVECTOR2 pos) { m_PlayerPos = pos; }

    // int    &   float
    void SetRots(int index, float rot) { m_Vertex[index].rot = rot; }
    void SetRadius(int index, float radius) { m_Vertex[index].radius = radius; }

    //  �Q�b�^�[   //
    //  int

    //  float
    FLOAT GetRots(int index) { return m_Vertex[index].rot; }
    FLOAT GetFirstRots(int index) { return m_Rots[index]; }

    FLOAT GetRadius(int index) { return m_Vertex[index].radius; }
    FLOAT GetFirstRadius(int index) { return m_Radius[index]; }
    
protected:
    //  �����o�ϐ�
    int m_TexIndex;

    //  ���_���
    VERTEX_NATTO m_Vertex[NATTO_MAX];

    //  �O�̃t���[���̃|�W�V����
    D3DXVECTOR2 m_PlayerPos = D3DXVECTOR2(0.0f, 0.0f);

    //  ����Rot�ۑ��p
    FLOAT m_Rots[NATTO_MAX];

    //  ����Radius
    FLOAT m_Radius[NATTO_MAX];

//  �����o�֐�
    void Rotation(int index);

    FLOAT frand();
    FLOAT frand_r();
};


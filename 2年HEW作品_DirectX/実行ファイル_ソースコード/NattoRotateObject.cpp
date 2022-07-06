#include "NattoRotateObject.h"

void NattoRotateObject::Initialize(void)
{

    for (int i = 0; i < NATTO_MAX; i++) {
        //  D3DXVECTOR2
        m_Vertex[i].pos = D3DXVECTOR2(SCREEN_WIDTH / 4 * frand(), 100.0f * frand());
        m_Vertex[i].dpos = m_Vertex[i].pos;
        m_Vertex[i].size = D3DXVECTOR2(50.0, 40.0f * frand_r() + 20.0f);

        //  FLOAT
        m_Vertex[i].angle = 0.1f;
        m_Vertex[i].rot = frand_r();       
        m_Vertex[i].alpha = 1.0f;
        m_Vertex[i].radius = frand() * 100.0f + 50.0f;

        //  bool
        m_Vertex[i].use = false;

        //  ����Rot�ۑ��p
        m_Rots[i] = m_Vertex[i].rot;

        //  ����Radius�ۑ��p
        m_Radius[i] = m_Vertex[i].radius;
    }

    //  ������Ԃ̔[���ۗL��
    for (int i = 0; i < FIRST_NATTO; i++) 
    {
        SetNatto();
    }
}

void NattoRotateObject::Finalize(void)
{
}

void NattoRotateObject::Update(void)
{
    for (int i = 0; i < NATTO_MAX; i++) {
        if (!m_Vertex[i].use)continue;

        //   �[����]�i�`�掞��]�j
        m_Vertex[i].angle += m_Vertex[i].rot;

        //  ��]����
        Rotation(i);

    }

    
}

void NattoRotateObject::Draw(void)
{
    for (int i = 0; i < NATTO_MAX; i++) {
        if (!m_Vertex[i].use)continue;
        DrawSpriteColorRotate(m_TexIndex, m_Vertex[i].pos.x, m_Vertex[i].pos.y,
            m_Vertex[i].size.x, m_Vertex[i].size.y, 1.0f, 1.0f, 1.0f, 1.0f,
            D3DXCOLOR(1.0f, 1.0f, 1.0f, m_Vertex[i].alpha),
            m_Vertex[i].angle);
    }
}

void NattoRotateObject::SetNatto(void)
{
    for (int i = 0; i < NATTO_MAX; i++) {
        if (m_Vertex[i].use)continue;
        m_Vertex[i].use = true;
        break;
    }
}

void NattoRotateObject::Rotation(int index)
{
    float hw, hh;
    hw = m_PlayerPos.x - m_Vertex[index].pos.x;
    hh = m_PlayerPos.y - m_Vertex[index].pos.y;

    // ���S�_�i�v���C���[�j����[���̍��W�ɑ΂���p�x
    float BaseAngle = atan2f(hh, hw);

    //  �v���C���[���S�ɉ�]
    float x = m_PlayerPos.x - cosf(BaseAngle + m_Vertex[index].rot) * m_Vertex[index].radius;
    float y = m_PlayerPos.y - sinf(BaseAngle + m_Vertex[index].rot) * m_Vertex[index].radius;

    //  �|�W�V�����Z�b�g
    m_Vertex[index].pos = D3DXVECTOR2(x, y);
}

FLOAT NattoRotateObject::frand()
{
    return (FLOAT)rand() / (FLOAT)RAND_MAX;
}

FLOAT NattoRotateObject::frand_r()
{
    return ANGLE_MIN + (FLOAT)(rand()) / (FLOAT)(RAND_MAX / (ANGLE_MAX - ANGLE_MIN));
}

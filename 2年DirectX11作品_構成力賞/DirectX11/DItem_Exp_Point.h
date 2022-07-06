//=============================================================================
//
// ���f���^��EXP�|�C���g [DItem_Exp_Point.h]
// Author : Yanagisawa Yuta
//
// �����F�G�l�~�[�|���Ɛ��l�ʑ̂�EXP���o�����܂�
//=============================================================================
#pragma once
#include "DropItem.h"
class DItem_Exp_Point :
    public DropItem
{
private:
    char m_TexName[64] = "data/MODEL/Experience_point.obj";

    static const int LIVE_LIMIT = 60 * 10;
public:


    // DropItem ����Čp������܂���
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual int ReturnIndex(void) override;

private:
    void Move();
};


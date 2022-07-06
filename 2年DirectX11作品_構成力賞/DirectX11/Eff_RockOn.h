//=============================================================================
//
// �G�l�~�[�փ��b�N�I������G�t�F�N�g [Eff_RockOn.h]
// Author : Yanagisawa Yuta
//
//=============================================================================
#pragma once
#include "GO_Effect.h"
class Eff_RockOn :
    public GO_Effect
{
public:

    virtual void Init() override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw() override;

    virtual void SetEffect() override;
    virtual void SetEffect(D3DXVECTOR3 pos) override;

    
private:
    MATERIAL m_Material;

    // GO_Effect ����Čp������܂���
    virtual void SetEffect(bool IsStart) override;
};


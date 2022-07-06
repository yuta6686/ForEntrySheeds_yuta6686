//=============================================================================
//
// �����G�t�F�N�g [Eff_Explosion.h]
// Author : Yanagisawa Yuta
//
// �����F�c���̉~�`�a�����g�傳��Ă���
//=============================================================================
#pragma once
#include "GO_Effect.h"
class Eff_Explosion :
    public GO_Effect
{
private:
    //char m_TexName[64] = "data/TEXTURE/";
    static const int EXPLOSION_TIME = 120;
public:
    // GO_Effect ����Čp������܂���
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void SetEffect() override;

    virtual void SetEffect(D3DXVECTOR3 pos) override;

private:
    DX11_MODEL  m_ModelCircle;
    char        m_TexNameCircle[64] = "data/MODEL/circle.obj";
    int         m_TexIndexCircle;

    // GO_Effect ����Čp������܂���
    virtual void SetEffect(bool IsStart) override;
};


//=============================================================================
//
// �U���X�L�� [Skill_Attack.h]
// Author : Yanagisawa Yuta
//
// �e�N�X�`�����[�h���邾��������A����Ȃ��������������B
//=============================================================================
#pragma once
#include "Skill.h"
class Skill_Attack :
    public Skill
{
public:
    // Skill ����Čp������܂���
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual int ReturnIndex(void) override {return SKILL_ATTACK;}

    virtual FLOAT GetValue() override { return static_cast<FLOAT>(m_SelectedNum + 1); }

    virtual void ChangeValue(FLOAT value) override {};

    char m_TexName[64] = "data/TEXTURE/Attack.png";
};


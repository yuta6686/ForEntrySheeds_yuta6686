//=============================================================================
//
// �X�L���Ǘ� [SkillManager.cpp]
// Author : Yanagisawa Yuta
//
// �����F�X�L����o�^���Ĉꊇ�Ǘ�����
//		�I�����ꂽ�X�L����V�����ǉ����邱�Ƃ͂Ȃ��B
//=============================================================================
#pragma once
#include "GameObject.h"
#include "Skill.h"
#include "SkillFactory.h"


class SkillManager :
    public GameObject
{
private:
    static const int SKILL_NUM_MAX = 24;
public:
    SkillManager();
    ~SkillManager();

    // GameObject ����Čp������܂���
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    bool Register(Skill* pSkill);

    bool Remove(int index);

    void SetPlayerPos(D3DXVECTOR3 pos);

    Skill* GetSkill(int index) { 
        if (m_pSkills == nullptr)return nullptr;
        return m_pSkills[index]; 
    }
private:
    void Create();

    
    Skill* m_pSkills[SKILL_NUM_MAX];
    
    SkillFactory m_SkillFactory;
};


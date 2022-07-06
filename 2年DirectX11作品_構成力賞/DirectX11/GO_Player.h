//=============================================================================
//
// �v���C���[�l [GO_Player.h]
// Author : Yanagisawa Yuta
//
//=============================================================================
#pragma once
#include "GameObject.h"
#include "shadow.h"
#include "ItemManager.h"
#include "ItemFactory.h"
#include "UserInterface.h"
#include "SkillManager.h"
#include "SkillFactory.h"


#define	VALUE_MOVE		(5.0f)						// �ړ���
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// ��]��

class GO_Player :
    public GameObject
{
public:
    // GameObject ����Čp������܂���
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    GAME_OBJECT GetObjInfo() { return m_Obj; }

    ItemManager* GetItemManager() { return &m_ItemManager; }
    SkillManager* GetSkillManager() { return m_SkillManeger; }

    ExperiencePoint* GetEXP() { return m_UI.GetEXP(); }

    void SetObjVec(D3DXVECTOR3 vec) { m_Obj.vec = vec; }

    void SetUse(bool flag) { m_Obj.use = flag; }

    void AddPos(D3DXVECTOR3 vec) { m_Obj.pos += vec; }

    //  �Q�[���N���A�ɂȂ�����
    bool IsClear() { return GetEXP()->GetIsClear(); }
private:
    //  ���f��
    DX11_MODEL m_Model;
    DX11_MODEL m_ChildModel;

    //  �I�u�W�F�N�g���
    GAME_OBJECT m_Obj;
    GAME_OBJECT m_ChildObj;

    //  ���C�g
    LIGHT* pLight;

    //  �J����
    CAMERA* cam;

    //  �A�C�e��
    ItemManager m_ItemManager;
    ItemFactory m_ItemFactory;

    //  �X�L��
    SkillManager* m_SkillManeger;
    SkillFactory m_SkillFactory;
    
    // UI
    UserInterface m_UI;

    float       m_Rot;		// �L�����N�^�[�̌���
    float		m_Rot_x;
    float		m_PrePlayerPosY;



//  �����o�֐�
    void CameraUpdate();
    void PlayerUpdate();
    void PlayerInputUpdate();
    void LightUpdate();


};


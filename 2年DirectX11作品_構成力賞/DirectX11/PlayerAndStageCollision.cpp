//=============================================================================
//
// �v���C���[�ƃX�e�[�W�̏Փˏ��� [PlayerAndStage.cpp]
// Author : Yanagisawa Yuta
//
// �����F�v���C���[���X�e�[�W�ɏՓ˂���Ɗɂ₩�ɖ߂���Ă���
//=============================================================================
#include "PlayerAndStageCollision.h"

void PlayerAndStageCollision::Init()
{

    m_pItem = m_pPlayer->GetItemManager()->GetItem(ITEM_BULLET);

    m_playerVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_ItemVec   = D3DXVECTOR3(1.0f, 1.0f, 1.0f);


    m_Reflect = REFLECT_DEFAULT_SPEED;

    m_Reflect_Counter = 0;
}

void PlayerAndStageCollision::Uninit()
{
}

void PlayerAndStageCollision::Update()
{
    //  �v���C���[�ƃA�C�e��(PlayerAndItem)
    Update_PAS_Reflect();

    //  �A�C�e���ƃv���C���[
    Update_IAS_Reflect();

}

void PlayerAndStageCollision::Draw()
{
}

bool PlayerAndStageCollision::IsCollision()
{
    D3DXVECTOR3 p_pos = m_pPlayer->GetObjInfo().pos;
    D3DXVECTOR3 p_size = m_pPlayer->GetObjInfo().size;

    D3DXVECTOR3 s_pos = m_pStage->GetObjInfo().pos;
    D3DXVECTOR3 s_size = m_pStage->GetObjInfo().size;

    //  ������
    m_playerVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

    //  X�������̕ǔ���
    if (s_pos.x + s_size.x <= p_pos.x + p_size.x)
    {
        m_playerVec.x = -1.0f;
        return true;
    }

    if(s_pos.x - s_size.x >= p_pos.x - p_size.x) 
    {
        m_playerVec.x = 1.0f;
        return true;
    }

    //  Y�������̕ǔ���
    if (s_pos.y + s_size.y <= p_pos.y + p_size.y) 
    {
        m_playerVec.y = -1.0f;
        return true;
    }

    if(s_pos.y - s_size.y >= p_pos.y - p_size.y) 
    {
        m_playerVec.y = 1.0f;
        return true;
    }
   

    //  Z�������̕ǔ���
    if (s_pos.z + s_size.z <= p_pos.z + p_size.z) 
    {
        m_playerVec.z = -1.0f;
        return true;
    }

    if(s_pos.z - s_size.z >= p_pos.z - p_size.z) 
    {
        m_playerVec.z = 1.0f;
        return true;
    }
   
    

    //  �������ĂȂ�������
    return false;
}

void PlayerAndStageCollision::CollisionUpdate()
{
    m_pPlayer->AddPos(m_pre * m_Reflect);
}

void PlayerAndStageCollision::Update_PAS_Reflect()
{

    //  �X�e�[�W���g���Ă��Ȃ�������A��
    if (!m_pStage->GetObjInfo().use)return;

    //  �v���C���[�ƃX�e�[�W���������Ă�����
    if (IsCollision()) {
        Update_Reflect_IsColl();
    }
    else {
        Update_Reflect_NoColl();
    }

    //  �v���C���[�ƃX�e�[�W�̏���
    CollisionUpdate();
}

void PlayerAndStageCollision::Update_Reflect_IsColl()
{
    m_Reflect_Counter++;

    if (m_Reflect >= REFLECT_MAX) {
        m_Reflect = REFLECT_MAX;
    }
    else {
        m_Reflect += REFLECT_ACCELERATION;
    }
    

    m_pre = m_playerVec;
}

void PlayerAndStageCollision::Update_Reflect_NoColl()
{
    if (m_Reflect_Counter > 0) 
    {
      
        m_Reflect -= REFLECT_ACCELERATION;

        m_Reflect_Counter--;
    }
    else {
        m_Reflect = REFLECT_DEFAULT_SPEED;
        m_pre = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;
    }
}

void PlayerAndStageCollision::Update_IAS_Reflect()
{
    for (int i = 0; i < m_pItem->GetItemNumMax();i++) {
        if (m_pItem->GetObjInfo(i).use == false)continue;
        if (IsCollisions(i) < 0)continue;

        CollisionUpdate(i);
    }
}

int PlayerAndStageCollision::IsCollisions(int index)
{
    
    D3DXVECTOR3 e_pos = m_pItem->GetObjInfo(index).pos;
    D3DXVECTOR3 e_size = m_pItem->GetObjInfo(index).size;

    D3DXVECTOR3 s_pos = m_pStage->GetObjInfo().pos;
    D3DXVECTOR3 s_size = m_pStage->GetObjInfo().size;

    m_ItemVec = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

    //  X�������̕ǔ���
    if (s_pos.x + s_size.x >= e_pos.x + e_size.x &&
        s_pos.x - s_size.x <= e_pos.x - e_size.x) {
    }
    else {
        m_ItemVec.x = -1.0f;
        return index;
    }

    //  Y�������̕ǔ���
    if (s_pos.y + s_size.y >= e_pos.y + e_size.y &&
        s_pos.y - s_size.y <= e_pos.y - e_size.y) {
    }
    else {
        m_ItemVec.y = -1.0f;
        return index;
    }

    //  Z�������̕ǔ���
    if (s_pos.z + s_size.z >= e_pos.z + e_size.z &&
        s_pos.z - s_size.z <= e_pos.z - e_size.z) {
    }
    else
    {
        m_ItemVec.z = -1.0f;
        return index;
    }

    //  �������ĂȂ�������
    return -1;
}

void PlayerAndStageCollision::CollisionUpdate(int index)
{
    m_pItem->InversionVec(index, m_ItemVec);
}





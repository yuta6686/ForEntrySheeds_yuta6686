//=============================================================================
//
// �v���C���[�ƃG�l�~�[�̏Փˏ��� [PlayerAndEnemyCollision.cpp]
// Author : Yanagisawa Yuta
//
// ����:�v���C���[�ƃG�l�~�[�����ł͂Ȃ��A
//      �v���C���[�ƌo���l
//      �o���b�g�ƃG�l�~�[�̏Փˏ���
//      �܂��A�v���C���[�ƃo���b�g�̃x�N�g�����������s
//=============================================================================
//  ���ԓI�ɃX�N�G�A���D�悳��Ă��܂��B
//  PlayerAndEnemyCollision(1) ... Enemy(1)
//  ��FSquare  -> PlayerAndEnemyCollision
//  ��FDiamond -> PlayerAndEnemyCollision
//  
//  �e�����ƃN�[���^�C������������B
//  �N�[���^�C�����͌��ĂȂ��̂ŁA���Ԃ��d�v�ɂȂ�B
//  �������@�́AEnemy�S�̂ł��̏������s���΂悢
//  �݌v�~�X��
//  �΍�āF�@DeployEnemy�ŏ�������B
//  Player�̃|�C���^���쐬���邱�Ƃɂ͂Ȃ邯�ǁA�d�����Ȃ��B

#include "PlayerAndEnemyCollision.h"
#include "result.h"
#include "game.h"


void PlayerAndEnemyCollision::Init()
{
    //  ����Ŏ��ȂȂ��Ȃ鏈��
    for (int i = 0; i < m_pEnemy->GetEnemyNumMax(); i++) 
    {
        if (!m_pEnemy)continue;

        if (IsCollisions(i) >= 0) 
        {
            m_pEnemy->SetUseFalse(false);
        }
    }

    m_CollExplosionIndex = -1;

    m_IsColl = false;

    m_Range = 0.0f;

    //�A�C�e���i�o���b�g�j�̃|�C���^���擾
    m_pBullet = m_pPlayer->GetItemManager()->GetItem(ITEM_BULLET);  

    //�A�C�e���i�o���l�j�̃|�C���^���擾
    m_pExpPoint = m_pPlayer->GetItemManager()->GetItem(ITEM_DROP_EXP_POINT);

    m_RockOn.Init();

    m_Explosion.Init();
   
}

void PlayerAndEnemyCollision::Uninit()
{
    m_RockOn.Uninit();
    m_Explosion.Uninit();
}

void PlayerAndEnemyCollision::Update()
{
    if (!m_pEnemy)return;

    SetDiamondVec();

    for (int i = 0; i < m_pEnemy->GetEnemyNumMax(); i++) 
    {
        if (m_pPlayer->IsClear())break; //  �N���A�����瓖���蔻�薳��
        if (m_pEnemy->GetObjInfo(i).free)continue;
        if (m_pEnemy->GetObjInfo(i).use == false)continue;
        

        if (IsCollisions(i) >= 0) 
        {
            CollisionUpdate(i);
           
        }
    }

    //  �˒��𓾂���
    m_Range = m_pPlayer->GetSkillManager()->GetSkill(SKILL_RANGE)->GetValue();

    //  �N�[���^�C�����ւ炷
    m_pBullet->ChangeValue(
        static_cast<int>(m_pPlayer->GetSkillManager()->GetSkill(SKILL_COOLTIME)->GetValue()));

    ItemUpdate();

    RockOnNearestEnemy();

    ToNextScene();

    m_RockOn.Update();

    m_Explosion.Update();

    //  �N���A�����𖞂����Ă���̐��b
    ClearEffect();
}

void PlayerAndEnemyCollision::Draw()
{
    m_RockOn.Draw();

    m_Explosion.Draw();
}



void PlayerAndEnemyCollision::ItemUpdate()
{
    //  �o���b�g�̏���
    ItemUpdate_Bullet();

    //  �A�C�e���ƃG�l�~�[�̓����蔻��
    for (int i = 0; i < m_pEnemy->GetEnemyNumMax(); i++) 
    {
        if (m_pEnemy->GetObjInfo(i).use == false)continue;

        for (int j = 0; j < m_pBullet->GetItemNumMax(); j++) 
        {
            if (m_pBullet->GetObjInfo(j).use == false)continue;
            int k = IsCollisions_Bullets(i, j);

            if (k < 0)continue;

            CollisionUpdate_Bullet(i,j);

           

            break;
        }      
    }

    
        
    //  �˒����̏����ƏՓ˂����Ƃ��̏���
    for (int i = 0; i < m_pExpPoint->GetItemNumMax(); i++) {
        if (m_pExpPoint->GetObjInfo(i).use == false)continue;

        //  �˒����̐ڋߏ���
        if (IsApproach(i, m_Range)) {
            ml_ExpPointIndex_Approach.push_back(i);
        }


        //  �ڐG����
        if (IsApproach(i, 0.0f)) {
            ml_ExpPointIndex_Contact.push_back(i);
        }
    }

    //  �ڋ�
    for (auto x : ml_ExpPointIndex_Approach) 
    {
        //  �v���C���[�ɋ߂Â�����
        if (m_pExpPoint->GetObjInfo(x).use == false)continue;

        //  �v���C���[�Ɍ������x�N�g��
        D3DXVECTOR3 vec = VectorOfPlayer_Set(m_pExpPoint->GetObjInfo(x).pos, m_pPlayer->GetObjInfo().pos, 3.0f);

        //  �o���l�̃x�N�g�����Z�b�g
        m_pExpPoint->SetVec(x,vec);
        

    }

    ml_ExpPointIndex_Approach.clear();

    //  �ڐG
    for (auto x : ml_ExpPointIndex_Contact) 
    {
        if (m_pExpPoint->GetObjInfo(x).use == false)continue;

        //  EXP��������鏈��
        m_pExpPoint->DeleteObj(x);

        m_pPlayer->GetEXP()->AddEXP(1);
    }

    if (!ml_ExpPointIndex_Contact.empty()) {
        GetSEManager()->PlaySE(SE_POTSUN, 0.3f);
    }

    ml_ExpPointIndex_Contact.clear();
}

void PlayerAndEnemyCollision::ItemUpdate_Bullet()
{
    if (m_pPlayer->IsClear())return;

    //  �����Œe����
    if (!m_pBullet->GetFlag())
    {
        int minIndex = NearestEnemy();

        if (minIndex < 0)return;

        //  �v���C���[�ƃG�l�~�[�̈ʒu��ϐ��ɂ����B
        D3DXVECTOR3 ppos = m_pPlayer->GetObjInfo().pos;
        D3DXVECTOR3 epos = m_pEnemy->GetObjInfo(minIndex).pos;

        //  �v���C���[�̃x�N�g���ɐݒ�       
        D3DXVECTOR3 toEnemyVec = VectorOfPlayer_Set(ppos, epos, ITEM_BULLET_SPEED);
        m_pPlayer->SetObjVec(toEnemyVec);

        //  �e�̐����擾
        int BulletsNum = 
            static_cast<int>(m_pPlayer->GetSkillManager()->GetSkill(SKILL_NEWBULLETS)->GetValue());

        //  �o���b�g�Ƀx�N�g�����Z�b�g���Ĕ���
        m_pBullet->SetItem(m_pPlayer->GetObjInfo().pos, m_pPlayer->GetObjInfo().vec);


        //  �o���b�g�̃X�L�����P�x�ł����Ƃ����ɗ����
        //  �x�N�g���𗐐��Œ���
        for (int i = 0; i < BulletsNum - 1; i++)
        {
            D3DXVECTOR3 randvec = m_pPlayer->GetObjInfo().vec;

            randvec.x += m_pBullet->ItemRand()*BULLETS_DIFFUSION;
            randvec.y += m_pBullet->ItemRand()*BULLETS_DIFFUSION;
            randvec.z += m_pBullet->ItemRand()*BULLETS_DIFFUSION;

            //  �o���b�g�Ƀx�N�g�����Z�b�g���Ĕ���
            m_pBullet->SetItem(m_pPlayer->GetObjInfo().pos, randvec);
        }
        


    }
}




int PlayerAndEnemyCollision::NearestEnemy(void)
{
    //  ��ԋ߂��G�l�~�[�̃C���f�b�N�X��ۑ�����
    int minIndex = -1;

    //  �ŒZ������ێ�
    float prelength = 10000000.0f;    

    //  �˒����̃C���f�b�N�X�����炤
    std::list<int> elist = InRangeEnemyIndex();

    for (auto x : elist) {        

        D3DXVECTOR3 dist = m_pEnemy->GetObjInfo(x).pos - m_pPlayer->GetObjInfo().pos;
        float length = D3DXVec3LengthSq(&dist);

        if (length < prelength) {
            prelength = length;
            minIndex = x;
        }        
    }  

    elist.clear();

    return minIndex;
}

void PlayerAndEnemyCollision::RockOnNearestEnemy(void)
{
    int minIndex = NearestEnemy();

    if (minIndex < 0) {
        m_RockOn.SetEffectUse(false);
        return;
    }

    D3DXVECTOR3 epos = m_pEnemy->GetObjInfo(minIndex).pos;

    epos.y -= 200.0f;

    //  �Ə��G�t�F�N�g
    m_RockOn.SetEffect(epos);
}

void PlayerAndEnemyCollision::ClearEffect(void)
{
    if (!m_pPlayer->IsClear())return;

    //  �N���A���Ă���̎���
    if (m_ClearEffectCounter <= 150 + 30) {

        //  �P�̂̃G�l�~�[������
        //  ���t���[���P�̂�����
       EnemyExplosionOnece();               

        m_ClearEffectCounter++;

        if (m_ClearEffectCounter == 1) {         
            GetClearEffect()->SetEffect(false);
        }

        
        return;
    }    
    else {
        m_ClearEffectCounter = 0;
    }

    

    /*for (int i = 0; i < m_Explosion.GetEffectNumMax(); i++) {
        if (m_Explosion.GetObjs(i)->use)
            return;                           
    }*/



    m_pPlayer->GetEXP()->NextStage();
}



//  �v���C���[�ƃG�l�~�[�������������̏���
void PlayerAndEnemyCollision::CollisionUpdate(int index)
{
    if (m_pPlayer->IsClear()) 
    {
        m_pEnemy->SetUseFalse(index);        

        //  �����Ƃ��̃G�t�F�N�g�\�����Ă�Ԃ�return;
        m_CollExplosionIndex = m_Explosion.SetEffects(m_pEnemy->GetObjInfo(index).pos);
        m_Explosion.SetEffects(m_pEnemy->GetObjInfo(index).pos, D3DX_PI / 2.0f);
    }
    else {
        m_pEnemy->SetUseFalse(index);
        m_pPlayer->SetUse(false);

        //  �����Ƃ��̃G�t�F�N�g�\�����Ă�Ԃ�return;
        m_CollExplosionIndex = m_Explosion.SetEffects(m_pEnemy->GetObjInfo(index).pos);
        m_Explosion.SetEffects(m_pEnemy->GetObjInfo(index).pos, D3DX_PI / 2.0f);
    }    
}

//  �v���C���[�̃A�C�e���ƃG�l�~�[�������������̏���
void PlayerAndEnemyCollision::CollisionUpdate_Bullet(int index,int index2)
{
    
    //  �e�ђʂ��邩���Ȃ����̏����͂������
    // 
    //  �e��������
    m_pBullet->DeleteObj(index2);

    //  HP�̏���
    {
        int attack = (int)m_pPlayer->GetSkillManager()->GetSkill(SKILL_ATTACK)->GetValue();
        m_pEnemy->ReduceHpOfEnemy(index,attack);
    }

    //  �o���l�Ƃ��̏���
    if(m_pEnemy->GetIsDeathEnemy(index))
    {
        //  �G�l�~�[���S
        m_pEnemy->SetUseFalse(index);

        //  �G�l�~�[��HP���o���l�Ƃ��Ă���
        //int hp_max = m_pEnemy->GetHpMax(index);
        //m_pPlayer->GetEXP()->AddEXP(hp_max);

        //  �G�l�~�[��HP�̐������o���l�𗎂Ƃ�
        for (int i = 0; i < m_pEnemy->GetHpMax(index); i++) 
        {
            m_pExpPoint->SetItem(m_pEnemy->GetObjInfo(index).pos);
        }
    }    

    
    m_Explosion.SetEffects(m_pEnemy->GetObjInfo(index).pos);
    m_Explosion.SetEffects(m_pEnemy->GetObjInfo(index).pos, D3DX_PI/2.0f);

    m_RockOn.SetEffectUse(false);
}

//  �v���C���[��EXPPoint�̐ڋߔ���
bool PlayerAndEnemyCollision::IsApproach(int index, FLOAT range)
{
    //  �v���C���[
    D3DXVECTOR3 ppos = m_pPlayer->GetObjInfo().pos;
    D3DXVECTOR3 psize = m_pPlayer->GetObjInfo().size;

    //  ExpPoint
    D3DXVECTOR3 epos = m_pExpPoint->GetObjInfo(index).pos;
    D3DXVECTOR3 esize = m_pExpPoint->GetObjInfo(index).size;

    //  ����
    D3DXVECTOR3 dist = ppos - epos;

    
    //  Sq�����Ă���֐��͕������̌v�Z�����Ȃ��o�[�W����
    FLOAT length = D3DXVec3LengthSq(&dist);

    //  �T�C�Y
    FLOAT size = powf(psize.x + esize.x,2.0f);

    if (length < size + powf(range,2.0f))
        return true;

    return false;
}

bool PlayerAndEnemyCollision::IsApproach(FLOAT range, D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, FLOAT size1, FLOAT size2)
{
    //  ����
    D3DXVECTOR3 dist = pos1 - pos2;


    //  Sq�����Ă���֐��͕������̌v�Z�����Ȃ��o�[�W����
    FLOAT length = D3DXVec3LengthSq(&dist);

    //  �T�C�Y
    FLOAT size = powf(size1 + size2, 2.0f);

    if (length < size + powf(range, 2.0f))
        return true;

    return false;
}

//  �v���C���[�̎˒�������G�l�~�[�̃C���f�b�N�X�𒲂ׂĕԂ�
std::list<int> PlayerAndEnemyCollision::InRangeEnemyIndex()
{
    std::list<int> nlist;

    GAME_OBJECT player = m_pPlayer->GetObjInfo();

    for (int i = 0; i < m_pEnemy->GetEnemyNumMax(); i++) 
    {
        if (m_pEnemy->GetObjInfo(i).use == false)continue;

        GAME_OBJECT enemy = m_pEnemy->GetObjInfo(i);

        //  �v���C���[�̎˒����Ȃ�
        if (IsApproach(m_Range, player.pos, enemy.pos, player.size.x, enemy.size.x)) 
        {
            nlist.push_back(i);
        }

    }


    return nlist;
}










int PlayerAndEnemyCollision::IsCollisions(int index)
{
    //  �G�l�~�[�̈ʒu�ƃT�C�Y
    D3DXVECTOR3 e_pos = m_pEnemy->GetObjInfo(index).pos;
    D3DXVECTOR3 e_size = m_pEnemy->GetObjInfo(index).size;

    //  �v���C���[�̈ʒu�ƃT�C�Y
    D3DXVECTOR3 p_pos = m_pPlayer->GetObjInfo().pos;
    D3DXVECTOR3 p_size = m_pPlayer->GetObjInfo().size / 2.0f;

    //  �����蔻��
    if (e_pos.x + e_size.x >= p_pos.x - p_size.x &&
        e_pos.x - e_size.x <= p_pos.x + p_size.x) {

        if (e_pos.y + e_size.y >= p_pos.y - p_size.y &&
            e_pos.y - e_size.y <= p_pos.y + p_size.y) {

            if (e_pos.z + e_size.z >= p_pos.z - p_size.z &&
                e_pos.z - e_size.z <= p_pos.z + p_size.z) {

                return index;
            }
        }
    }

    return -1;
}

int PlayerAndEnemyCollision::IsCollisions_Bullets(int index, int index2)
{
    //  �G�l�~�[�̈ʒu�ƃT�C�Y
    D3DXVECTOR3 e_pos = m_pEnemy->GetObjInfo(index).pos;
    D3DXVECTOR3 e_size = m_pEnemy->GetObjInfo(index).size;

    //  �v���C���[�̈ʒu�ƃT�C�Y
    D3DXVECTOR3 i_pos = m_pBullet->GetObjInfo(index2).pos;
    D3DXVECTOR3 i_size = m_pBullet->GetObjInfo(index2).size / 2.0f;

    //  �����蔻��
    if (e_pos.x + e_size.x >= i_pos.x - i_size.x &&
        e_pos.x - e_size.x <= i_pos.x + i_size.x) {

        if (e_pos.y + e_size.y >= i_pos.y - i_size.y &&
            e_pos.y - e_size.y <= i_pos.y + i_size.y) {

            if (e_pos.z + e_size.z >= i_pos.z - i_size.z &&
                e_pos.z - e_size.z <= i_pos.z + i_size.z) {

                return index;
            }
        }
    }

    return -1;
}

D3DXVECTOR3 PlayerAndEnemyCollision::VectorOfPlayer_Set(D3DXVECTOR3 pos1 ,D3DXVECTOR3 pos2,FLOAT speed)
{
    //  �e��g�̎��ɑΉ�����ʏ�ł̊p�x�擾
    float xyRot = atan2f(pos2.y - pos1.y, pos2.x - pos1.x);
    float xzRot = atan2f(pos2.z - pos1.z, pos2.x - pos1.x);
    float zyRot = atan2f(pos2.y - pos1.y, pos2.z - pos1.z);

    //  �v���C���[�ɑ���悤�̕ϐ�
    D3DXVECTOR3 vec;
    vec.x = (cosf(xyRot) + cosf(xzRot)) * speed;
    vec.y = (sinf(xyRot) + sinf(zyRot)) * speed;
    vec.z = (sinf(xzRot) + cosf(zyRot)) * speed;

    return vec;
}

void PlayerAndEnemyCollision::SetDiamondVec()
{
    //  �G�l�~�[��Diamond�̎��������s
    if (m_pEnemy[0].ReturnIndex() != ENEMY_DIAMOND)return;

    for (int i = 0; i < m_pEnemy->GetEnemyNumMax(); i++) 
    {
        if (m_pEnemy->GetObjInfo(i).use == false)continue;
        if (m_pEnemy->GetObjInfo(i).free != false)continue;

        // vec�ݒ�
        m_pEnemy->SetVec(i,VectorOfPlayer_Set( m_pEnemy->GetObjInfo(i).pos, m_pPlayer->GetObjInfo().pos, 1.0f));
    }
}

//  �G�l�~�[�E���ăG�t�F�N�g�\��
void PlayerAndEnemyCollision::EnemyExplosionOnece()
{
    for (int i = 0; i < m_pEnemy->GetEnemyNumMax(); i++)
    {
        if (m_pEnemy->GetObjInfo(i).use == false)continue;

        m_Explosion.SetEffects(m_pEnemy->GetObjInfo(i).pos);
        m_pEnemy->SetUseFalse(i);
        
    }
}

//  �v���C���[�����񂾂烊�U���g�V�[����
void PlayerAndEnemyCollision::ToNextScene()
{
    if (m_CollExplosionIndex >= 0)
        m_IsColl = true;

    if (m_IsColl)
    {
        if (m_Explosion.GetObjs(m_CollExplosionIndex)->use == false)
        {

            SetIsClear(false);
            SceneTransition(SCENE_RESULT);
        }
    }


}

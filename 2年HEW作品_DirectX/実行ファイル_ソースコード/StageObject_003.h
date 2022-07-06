#pragma once
//=============================================================================
//
// �X�e�[�W�I����ʃI�u�W�F�N�g_003 [SelectStage.h]
// Author :	yuta yanagisawa 
//
//=============================================================================
#include "StageObject_001.h"

class StageObject_003 :
    public StageObject_001
{
public:
    //  �������StageObject_001�̋@�\���g�p���Ă���

    virtual HRESULT Init(void) override;
    virtual void    Draw(void) override;
    virtual void ClickUpdate(void) override;
    virtual STAGE_NUM ReturnStageNum(void) override { return STAGE_NUM_003; }

private:
    char m_TextureName[64] = "data/TEXTURE/Select_Stage3.png";
    int  m_TextureIndex;
};


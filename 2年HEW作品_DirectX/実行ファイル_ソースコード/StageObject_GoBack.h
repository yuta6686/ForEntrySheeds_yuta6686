#pragma once
#include "StageObject_001.h"
class StageObject_GoBack :
    public StageObject_001
{
public:
    virtual HRESULT Init(void) override;
    virtual void    Draw(void) override;
    virtual void ClickUpdate(void) override;
    virtual STAGE_NUM ReturnStageNum(void) override { return STAGE_GOBACK; }

private:
    char m_TextureName[64] = "data/TEXTURE/goBack_Icon.png";
    int  m_TextureIndex;
};


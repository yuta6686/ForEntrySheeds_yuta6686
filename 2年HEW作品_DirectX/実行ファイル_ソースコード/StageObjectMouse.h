#pragma once
#include "StageObject.h"
class StageObjectMouse :
    public StageObject
{
public:
    // StageObject ����Čp������܂���
    virtual HRESULT Init(void) override =0;
    virtual void Uninit(void) override=0;
    virtual void Update(void) override=0;
    virtual void Draw(void) override=0;

    //�N���b�N
    virtual bool IsClick(void)=0;
    virtual void ClickUpdate(void)=0;

    //�}�E�X�I�[�o�[
    virtual bool IsMouseOver(void)=0;
    virtual void MouseOverUpdate(void)=0;

    virtual STAGE_NUM ReturnStageNum(void) override=0;
};


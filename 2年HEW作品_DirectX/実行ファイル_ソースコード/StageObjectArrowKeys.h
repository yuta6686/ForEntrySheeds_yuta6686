#pragma once
#include "StageObject.h"
class StageObjectArrowKeys  
{
public:
    //�\���L�[
    virtual bool IsArrowKeyTriggerd(void)= 0;
    virtual void Update_ArrowKeyTriggerd(void) = 0;

    //�G���^�[�L�[
    virtual bool IsEnterKeyTriggerd(void) = 0;
    virtual void Update_EnterKeyTriggerd(void) = 0;


};


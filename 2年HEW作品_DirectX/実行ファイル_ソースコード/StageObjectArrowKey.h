#pragma once
//=============================================================================
//
// �X�e�[�W�I����ʏ����̖��L�[�E�G���^�[�L�[���͏��� [SelectStage.h]
// Author :	yuta yanagisawa 
//
//=============================================================================
#include "StageObject.h"
class StageObjectArrowKey :
    public StageObject
{
public:
//  �p�������o�֐�-------------------------------------------------------
    virtual HRESULT Init(void) override { return E_NOTIMPL; }
    
    virtual void Update(void) override;
    virtual void Draw(void) override;

    virtual void Uninit(void) override {}           //  ��
    virtual bool IsClick(void) override             //  ��
    { return false; }
    virtual void ClickUpdate(void) override {}      //  ��
    virtual bool IsMouseOver(void) override         //  ��
    { return false; }
    virtual void MouseOverUpdate(void) override {}  //  ��

    virtual STAGE_NUM ReturnStageNum(void) override;

//  �ŗL�����o�֐�-------------------------------------------------------
    //  �I������Ă���X�e�[�W�ԍ���Ԃ�
    virtual int GetStageNumSelect(void) { return m_StageNumSelect; }

private:
//  �����o�ϐ�-----------------------------------------------------------
    //  ���L�[��Ԏ擾�p
    int m_ArrowKey = ARROW_KEY_NONE;

    //  �I������Ă���X�e�[�W�擾�p
    int m_StageNumSelect = STAGE_NUM_NONE;

//  �����o�֐�-----------------------------------------------------------
    //  ���L�[
    virtual int IsArrowKeyTriggerd(void);
    virtual void ArrowKeyUpdate(void);

    //  �G���^�[�L�[
    virtual bool IsEnterTriggerd(void);
    virtual void EnterUpdate(void);

    //  m_StageNumSelect�̐U�镑��
    virtual void SetStageNumSelect(int stageNum) 
    { m_StageNumSelect = stageNum; }   //�ő�A�ŏ��Ȃǎw��

    virtual void StageNumAdd(void) 
    { m_StageNumSelect++; }             //����

    virtual void StageNumSub(void) 
    { m_StageNumSelect--; }             //����
};


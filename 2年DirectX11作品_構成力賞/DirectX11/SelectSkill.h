//=============================================================================
//
// �X�L���I�� [SelectSkill.h]
// Author : Yanagisawa Yuta
//
// �����F�o���l����萔�l������ƁA�X�L���I����Ԃ֑J�ڂ���B
//		���̏�Ԃ̂Ƃ��ɁA2�̃X�L���𒊑I���A�v���C���[�ɑI��������
//		���I�ł͓����X�L�������Ȃ��悤�Ɏ{����Ă���
//=============================================================================
#pragma once
#include "main.h"

#include "SkillManager.h"
#include "SkillFactory.h"

struct PosSize2 {
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
};

class SelectSkill
{
private:
	static const int WIDTH_NUM = 5;

	const float UI_FIRST_POS_X = 50.0f;

	const float UI_FIRST_POS_Y = 800.0f;

	const float UI_MARGIN_X = 75.0f;
	const float UI_MARGIN_Y = 75.0f;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	SkillFactory m_SkillFactory;
private:
//	�����o�ϐ�
	bool m_once = true;

	int m_RandIndex1 = 0;
	int m_RandIndex2 = 0;

	int m_TexIndex1;
	int m_TexIndex2;

	PosSize2 m_PosSize1;
	PosSize2 m_PosSize2;	

	D3DXVECTOR2 mPos;

	SkillManager* m_SkillManager;

//	�����o�֐�
	int LotteryIndex(void) { return rand() % SKILL_MAX; }

	int Click();

	bool IsClick(PosSize2 posize);
};



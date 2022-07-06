//=============================================================================
//
// �X�L���I�� [SelectSkill.cpp]
// Author : Yanagisawa Yuta
//
// �����F�o���l����萔�l������ƁA�X�L���I����Ԃ֑J�ڂ���B
//		���̏�Ԃ̂Ƃ��ɁA2�̃X�L���𒊑I���A�v���C���[�ɑI��������
//		���I�ł͓����X�L�������Ȃ��悤�Ɏ{����Ă���
//=============================================================================
#include "SelectSkill.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "sprite.h"




void SelectSkill::Init()
{
	m_SkillManager = GetSkillManager_Scene();

	m_once = true;

	m_PosSize1.pos = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 };
	m_PosSize1.size = { SCREEN_WIDTH / 3.0f, SCREEN_WIDTH / 3.0f };

	m_PosSize2.pos = { SCREEN_WIDTH / 4 * 3, SCREEN_HEIGHT / 2 };
	m_PosSize2.size = { SCREEN_WIDTH / 3.0f, SCREEN_WIDTH / 3.0f };
}

void SelectSkill::Uninit()
{
	
}

void SelectSkill::Update()
{
	//	�ŏ��Ɉ�񒊑I����
	//	�X�L��2�𒊑I
	if (m_once) {
		m_once = false;
		m_RandIndex1 = 0;
		m_RandIndex2 = 0;

		while (m_RandIndex1 == m_RandIndex2) {
	
			//	�X�L�����I
			m_RandIndex1 = LotteryIndex();
			m_RandIndex2 = LotteryIndex();

			//	�X�L���̃A�C�R���̃e�N�X�`����ݒ�
			m_TexIndex1 = m_SkillManager->GetSkill(m_RandIndex1)->GetTexIndex();
			m_TexIndex2 = m_SkillManager->GetSkill(m_RandIndex2)->GetTexIndex();

		}
	}

#ifdef _DEBUG	
	//	�Ƃ肠�����c���Ƃ�
	if (GetKeyboardTrigger(DIK_RETURN)
		&& GetFadeState() == FADE_NONE) {
		m_once = true;
	}	
#endif
	

	//�@�N���b�N��������m_RandIndex��Ԃ�
	int iscl = Click();

	//	�N���b�N���Ă��Ȃ�������A�b�b�@�N���b�N�������ǁA�������Ă��Ȃ�������-1��Ԃ�
	if (iscl >= 0) {
		m_SkillManager->GetSkill(iscl)->AddSelectedNum();

		//	UI�ɒǉ�

		FLOAT xpos = UI_FIRST_POS_X + ((GetUIManager()->GetListSize()) % WIDTH_NUM) * UI_MARGIN_X;
		FLOAT ypos = UI_FIRST_POS_Y + ((GetUIManager()->GetListSize()) / WIDTH_NUM) * UI_MARGIN_Y;

		GetUIManager()->Add(
			new UserInterface_new(m_SkillManager->GetSkill(iscl)->GetTexIndex(),
				xpos, ypos));

		ChangeSelectSkillState(false);

		GetClearEffect()->SetEffect(true);
		m_once = true;
	}


	
}

void SelectSkill::Draw()
{
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(m_TexIndex1));

	DrawSprite(m_TexIndex1, m_PosSize1.pos.x, m_PosSize1.pos.y, m_PosSize1.size.x, m_PosSize1.size.y,
		1.0f, 1.0f, 1.0f, 1.0f);

	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(m_TexIndex2));

	DrawSprite(m_TexIndex2, m_PosSize2.pos.x, m_PosSize2.pos.y, m_PosSize2.size.x, m_PosSize2.size.y,
		1.0f, 1.0f, 1.0f, 1.0f);
}

int SelectSkill::Click()
{
	

	if (IsMouseLeftTriggered()) 
	{

		mPos = { (FLOAT)GetMousePosX(),(FLOAT)GetMousePosY() };


		if (IsClick(m_PosSize1)) 
		{			
			return m_RandIndex1;
		}

		if (IsClick(m_PosSize2)) 
		{
			return m_RandIndex2;
		}
	}

	
	return -1;
}

bool SelectSkill::IsClick(PosSize2 posize)
{
	if (mPos.x > posize.pos.x - posize.size.x &&
		mPos.x < posize.pos.x + posize.size.x) 
	{
		if (mPos.y > posize.pos.y - posize.size.y &&
			mPos.y < posize.pos.y + posize.size.y) 
		{
			return true;
		}
	}

	return false;
}

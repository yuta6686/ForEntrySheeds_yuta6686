//=============================================================================
//
//  UI���Ǘ�[UserInterface.cpp]
// Author : Yanagisawa Yuta
//
// �����FUI�Ɏg�p������̂̏����������ōs��
// ���f���o��Ver
// DrawSprite�Ȃǂ̏����łQD�`�悷��ꍇ�A�Ō�ɕ`�悷��K�v�����邽�߁B
//=============================================================================
#include "UserInterface.h"

void UserInterface::Init()
{
	m_EXP.Init();
}

void UserInterface::Uninit()
{
	m_EXP.Uninit();
}

void UserInterface::Update()
{
	m_EXP.Update();
}

void UserInterface::Draw()
{
	m_EXP.Draw();
}

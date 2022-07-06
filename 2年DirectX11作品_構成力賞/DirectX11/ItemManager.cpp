//=============================================================================
//
// �A�C�e�����ꊇ�Ǘ� [ItemManager.cpp]
// Author : Yanagisawa Yuta
//
// ���ȁ@�ėp���I�ɂ͂悩�������ǁA�g��Ȃ�������Ӗ����Ȃ��B
//=============================================================================
#include "ItemManager.h"

void ItemManager::Create(void)
{

}


ItemManager::ItemManager()
{
	for (int i = 0; i < ITEM_MAX; i++) {
		m_pItems[i] = nullptr;
	}
}

ItemManager::~ItemManager()
{
	for (int i = 0; i < ITEM_MAX; i++) {
		delete m_pItems[i];
	}
}

void ItemManager::Init()
{
	for (int i = 0; i < ITEM_MAX; i++) {
		if (!m_pItems[i])continue;
		m_pItems[i]->Init();
	}
}

void ItemManager::Uninit()
{
	for (int i = 0; i < ITEM_MAX; i++) {
		if (!m_pItems[i])continue;
		m_pItems[i]->Uninit();
	}
}

void ItemManager::Update()
{
	for (int i = 0; i < ITEM_MAX; i++) {
		if (!m_pItems[i])continue;
		m_pItems[i]->Update();
	}
}

void ItemManager::Draw()
{
	for (int i = 0; i < ITEM_MAX; i++) {
		if (!m_pItems[i])continue;
		m_pItems[i]->Draw();
	}
}

bool ItemManager::mRegister(GO_Item* pItem)
{
	for (int i = 0; i < ITEM_MAX; i++) {
		if (m_pItems[i])continue;
		m_pItems[i] = pItem;
		return true;
	}
	return false;
}


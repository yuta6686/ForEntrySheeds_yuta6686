//=============================================================================
//
// �A�C�e�����ꊇ�Ǘ� [ItemManager.h]
// Author : Yanagisawa Yuta
//
// ���ȁ@�ėp���I�ɂ͂悩�������ǁA�g��Ȃ�������Ӗ����Ȃ��B
//=============================================================================
#pragma once
#include "GameObject.h"
#include "GO_Item.h"

class ItemManager:public GameObject
{
private:
	static const int ITEM_MAX = 20;
public:
	ItemManager();
	~ItemManager();

	// GameObject ����Čp������܂���
	virtual void Init() override;

	virtual void Uninit() override;

	virtual void Update() override;

	virtual void Draw() override;

	bool mRegister(GO_Item* pItem);

	GO_Item* GetItem(int index) { 
		if (index < 0 || ITEM_MAX <= index)return nullptr;
		if (!m_pItems[index])return nullptr;
		return m_pItems[index]; 
	}

private:
	GO_Item* m_pItems[ITEM_MAX];

	void Create(void);
};


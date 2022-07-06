//=============================================================================
//
// UI�}�l�[�W���[ [UInew_Manager.cpp]
// Author : Yanagisawa Yuta
//
// �����FUI�̃C���X�^���X��List�ŊǗ�
//		�X�L���̃e�N�X�`����\�����Ă������
//=============================================================================
#pragma once
#include "UserInterface_new.h"
#include <list>

class UInew_Manager
{
public:
	UInew_Manager();
	~UInew_Manager();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Add(UserInterface_new* p);

	int GetListSize() { return m_pUIs.size(); }
private:

	std::list<UserInterface_new*> m_pUIs;
};


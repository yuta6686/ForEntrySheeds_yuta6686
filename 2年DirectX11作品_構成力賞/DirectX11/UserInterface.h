//=============================================================================
//
//  UI���Ǘ�[UserInterface.h]
// Author : Yanagisawa Yuta
//
// �����FUI�Ɏg�p������̂̏����������ōs��
// ���f���o��Ver
// DrawSprite�Ȃǂ̏����łQD�`�悷��ꍇ�A�Ō�ɕ`�悷��K�v�����邽�߁B
//=============================================================================
#pragma once
#include "GameObject.h"
#include "ExperiencePoint.h"



class UserInterface :public GameObject
{
public:
	// GameObject ����Čp������܂���
	virtual void Init() override;

	virtual void Uninit() override;

	virtual void Update() override;

	virtual void Draw() override;

	ExperiencePoint* GetEXP() { return &m_EXP; }
private:
	//  �o���l
	ExperiencePoint m_EXP;



};


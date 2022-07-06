//=============================================================================
//
// �G�l�~�[�z�u [DeployEnemy.h]
// Author : Yanagisawa Yuta
//
// �����F�G�l�~�[����莞�Ԍo�߂�����o��������
//		�_�C�������h�ƃX�N�G�A�̔䗦�[��D:S = 1:3
//=============================================================================
#pragma once
#include "Enemy_Square.h"
#include "Enemy_Diamond.h"
#include <vector>
#include <memory>

//	���̒�`�ƃG�l�~�[�̎�ސ��͈�v������K�v������
#define DEPLOY_ENEMY_MAX 2

class DeployEnemy :public GameObject
{
public:
	DeployEnemy();
	~DeployEnemy();

private:
	static const int DEPLOY_CYCLE_TIME = 7;	//����
	static const int DEPLOY_CYCLE = DEPLOY_CYCLE_TIME * 60;	//���Ԃ��t���[���ɂ��������B
public:
	virtual void Init()override;
	virtual void Uninit()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual bool Register(GO_Enemy* pEnemy);
	virtual void Create();
	
	virtual void HPLottery();

	//  ����
	virtual void Action();

	//  ���񂾂Ƃ��̏���
	virtual bool Death();
	

	virtual GO_Enemy* GetEnemy(int index) { 
		if (index > DEPLOY_ENEMY_MAX || index < 0)return nullptr;
		if (!m_pEnemys[index])return nullptr;
		return m_pEnemys[index]; 
	}
private:
	void DeployEnemyCycle(void);

	//	���x��
	int m_NowLevel;

	//	�G�l�~�[�̍ő吔
	int m_MaxEnemyNum;

	// �G�l�~�[�o���̃J�E���^�[
	int m_timeCounter = 0;
	
	GO_Enemy* m_pEnemys[DEPLOY_ENEMY_MAX];
};


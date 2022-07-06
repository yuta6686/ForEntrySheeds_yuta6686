#pragma once
#include "GameObject.h"

//	���V�ǉ�----------------------------------->>>

//	�v���C���[�����ɏՓ˂����ۂ̓���
//	movement�Ŏg�p
class PlayerMoveForFan {
private:
	const float WIND_ACCELERATION = 0.5f;	//�����x
	const float WIND_DEFAULT_SPEED = 1.0f;	//���x
public:
	void SetOnceFlag(bool flag) 
	{
		if (once == true)return;
		windSpeed = WIND_DEFAULT_SPEED;
		once = flag; 
	}

	//�X�s�[�h�̑����X�V�ƃt���O�̏���
	void ChangeWindSpeed();	

	float GetWindSpeed() { 
		ChangeWindSpeed();
		return windSpeed; 
	}

private:
	float		windSpeed = WIND_DEFAULT_SPEED;

	bool		once = false;
};

//	m_CollisionNum�p�ϐ�
//	�g�p�p�r�F�ǂ̌����ɏՓ˂��Ă��邩���ʂ���
enum FAN_COLLISION {
	FAN_COLL_NONE = -1,
	FAN_COLL_UP,
	FAN_COLL_LEFT,
};
//	���V�ǉ�-----------------------------------<<<

class GO_SS_Fan : public GameObject
{
public:		//	�ύX�\�ϐ�
	static const int FANS_MAX = 5;		//���C��̍ő吔

private:	//	�ύX�\�ϐ�
	const int GAME_SCENE = GAMESCENE_GAME_TEST;
	const int WIND_TEX_MAX = 60;
	const int WIND_HEIGHT_SPLIT = 12;
	const int WIND_WIDTH_SPLIT = 5;
	const float WIND_ADD_V = 0.083f;
	const float WIND_ADD_U = 0.2f;

	const float LEFT_QUANTITY = 4.71238898038469f;


public:
	// GameObject ����Čp������܂���
	virtual void Initialize(void) override;
	virtual void Finalize(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;
	virtual int GetGameScene(void) { return GAME_SCENE; }

	//�f���o�����̐ݒ�@����:�ʒu
	void LinkFanB(D3DXVECTOR2 pos, bool isLeft);

	//���C��̃Z�b�g�@����:�ʒu
	void SetFan(D3DXVECTOR2 pos);

	void SetCircle(VERTEX_CIRCLE* p) { m_pCircle = p; }

	FAN_VARTEX* GetFan(void) { return m_FanInfo; }

	void AddX(FLOAT x);

	inline void ResetOnce(void) {
		for (int i = 0; i < FANS_MAX; i++) {
			m_FanInfo[i].use = false;
		}
		once = true;
	}

//	���V�ǉ�----------------------------------->>>
//	m_CollisionNum�Z�b�^�[�Q�b�^�[
	void SetCollisionNum(int num) { m_CollisionNum = num; }
	int GetCollisionNum(void) { return m_CollisionNum; }

//���V�ǉ�-----------------------------------<<<

private:

	bool FCCollision(D3DXVECTOR2 pos1, D3DXVECTOR2 size1, D3DXVECTOR2 pos2, float size2);
	void DebugOut(void);

	int m_FanATex;
	int m_FanBTex;
	int m_WindTex;

	FAN_VARTEX m_FanInfo[FANS_MAX];

	VERTEX_CIRCLE* m_pCircle;
	bool once;

//	���V�ǉ�----------------------------------->>>
		//	�Փ�: -1 ,�� 0 ,��1
	int m_CollisionNum = -1;

//	���V�ǉ�-----------------------------------<<<
};
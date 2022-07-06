//=============================================================================
//
// �o���l���� [ExperiencePoint.h]
// Author : Yanagisawa Yuta
//
// �����F�o���l�̃Q�[�W����
// 
//=============================================================================
#pragma once

#include "UserInterfaceItem.h"
#include "scene.h"

class ExperiencePoint :public UserInterfaceItem
{
private:
	static const int EXP_MAX_DEFAULT = 10;
	int m_exp_max = EXP_MAX_DEFAULT;
	const float EXP_GAUGE_XMAX = 300.0f;
	float m_Exp_Gauge = EXP_GAUGE_XMAX / m_exp_max;
	

	char m_pTexName[128] = "data/TEXTURE/EXP1.png";
public:
	//	�����͊l������exp
	//	�l������exp���A�Q�[�W�𑝂₷	
	void AddEXP(int exp) 
	{ 
		if (m_Obj.size.x >= EXP_GAUGE_XMAX) {
			m_EXP = m_exp_max;
			m_Obj.size.x = EXP_GAUGE_XMAX;
		}
		else {
			m_EXP += exp;
			m_Obj.size.x += (float)exp * m_Exp_Gauge;
		}
		
	}
	void NextStage();

	void SetExpMax() 
	{
		m_exp_max = EXP_MAX_DEFAULT + static_cast<int>(powf((static_cast<float>(*GetStageNum()*2)), 2.0f));
		m_Exp_Gauge = EXP_GAUGE_XMAX / m_exp_max;
	}

	bool GetIsClear(void) { return m_EXP >= m_exp_max; }

	// GameObject ����Čp������܂���
	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;

private:

	int m_EXP;
	FLOAT m_Alpha = 1.0f;

	GAME_OBJECT m_Obj_EXPMAX;

	MATERIAL m_Material2;
	
	VERTEX_3D* vertex;
	VERTEX_3D* vertex_max;

	ID3D11Buffer* m_VertexBuffer_max = NULL;
};


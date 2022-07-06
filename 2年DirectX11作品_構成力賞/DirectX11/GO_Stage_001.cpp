//=============================================================================
//
// �X�e�[�W1 [GO_Stage_001.cpp]
// Author : Yanagisawa Yuta
//
// �����F������
//=============================================================================
#include "GO_Stage_001.h"
#include "CoordinateTransformation.h"

void GO_Stage_001::Init()
{
	//LoadModel("data/MODEL/stage_sozai.obj", &m_Model);
	LoadModel((char*)"data/MODEL/cross.obj", &m_Model);

	m_Obj.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Obj.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Obj.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	
	m_Obj.scl = D3DXVECTOR3(STAGE_SIZE, STAGE_SIZE, STAGE_SIZE);

	m_Obj.size = D3DXVECTOR3(STAGE_X * STAGE_SIZE/2,STAGE_Y * STAGE_SIZE/2,STAGE_Z * STAGE_SIZE/2);
	m_Obj.idxShadow = 0;
	m_Obj.use = true;
	
	for (unsigned short i = 0; i < m_Model.SubsetNum; i++)
	{
		m_Model.SubsetArray[i].Material.Material.Diffuse.a = 1.0f;
		m_Model.SubsetArray[i].Material.Material.Emission = D3DXCOLOR(0.0f, 0.0f,1.0f, 0.0f);

		
	}

	// �_�����̐ݒ�
	pLight = NULL;
	pLight = GetLightData(2);
	pLight->Position = D3DXVECTOR4(0.0f, 3200.0f, 0.0f, 0.0f);
	pLight->Direction = D3DXVECTOR4(0.0f, -1.0f, 0.0f, 0.0f);// ���̌���
	pLight->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// ���̐F
	pLight->Attenuation = 10.0f;							// ��������
	pLight->Type = LIGHT_TYPE_DIRECTIONAL;						// �_����
	pLight->Enable = true;									// ���̃��C�g��ON
	SetLightData(2, pLight);								// ����Őݒ肵�Ă���

		// �_�����̐ݒ�
	pLight = NULL;
	pLight = GetLightData(3);
	pLight->Position = D3DXVECTOR4(0.0f, -3200.0f, 0.0f, 0.0f);
	pLight->Direction = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.0f);// ���̌���
	pLight->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// ���̐F
	pLight->Attenuation = 10.0f;							// ��������
	pLight->Type = LIGHT_TYPE_DIRECTIONAL;						// �_����
	pLight->Enable = true;									// ���̃��C�g��ON
	SetLightData(3, pLight);								// ����Őݒ肵�Ă���

}

void GO_Stage_001::Uninit()
{
	UnloadModel(&m_Model);

}

void GO_Stage_001::Update()
{
}

void GO_Stage_001::Draw()
{
	//	�A���t�@�e�X�g��L����
	//SetAlphaTestEnable(true);

	//SetCullingMode(CULL_MODE_FRONT);
	//SetCullingMode(CULL_MODE_NONE);
	//SetCullingMode(CULL_MODE_BACK);

	CoordinateTransformation(&m_Obj);

	//SetBlendState(BLEND_MODE_ADD);
	//SetBlendState(BLEND_MODE_ALPHABLEND);

	DrawModel(&m_Model);

	//SetBlendState(BLEND_MODE_ALPHABLEND);

	//SetCullingMode(CULL_MODE_BACK);


	//SetAlphaTestEnable(false);
}


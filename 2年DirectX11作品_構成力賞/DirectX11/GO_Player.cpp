//=============================================================================
//
// �v���C���[�l [GO_Player.cpp]
// Author : Yanagisawa Yuta
//
//=============================================================================
#include "GO_Player.h"
#include "CoordinateTransformation.h"
#include "main.h"
#include "scene.h"
#include "game.h"

void GO_Player::Init()
{
	LoadModel((char*)"data/MODEL/player_001.obj", &m_Model);
	LoadModel((char*)"data/MODEL/player_child.obj", &m_ChildModel);
		
	//�e
	{
		m_Obj.pos = D3DXVECTOR3(0.0f, 35.0f, 0.0f);
		m_Obj.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Obj.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Obj.vec = D3DXVECTOR3(10.0f, 0.0f, 0.0f);

		float scale = 2.5f;
		m_Obj.scl = D3DXVECTOR3(scale, scale, scale);
		m_Obj.size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
		m_Obj.idxShadow = 0;
		m_Obj.use = true;
	}

	//�q
	{
		m_ChildObj.pos = D3DXVECTOR3(0.0f, 35.0f, 0.0f);
		m_ChildObj.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_ChildObj.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		float scale = 5.0f;
		m_ChildObj.scl = D3DXVECTOR3(scale, scale, scale);
		m_ChildObj.size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
		m_ChildObj.idxShadow = 0;
		m_ChildObj.use = true;
	}

	// �_�����̐ݒ�
	//pLight = NULL;
	//pLight = GetLightData(1);
	//pLight->Position = D3DXVECTOR4(0.0f, 500.0f, 0.0f, 0.0f);
	//pLight->Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);// ���̌���
	//pLight->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// ���̐F
	//pLight->Attenuation = 1000.0f;							// ��������
	//pLight->Type = LIGHT_TYPE_POINT;						// �_����
	//pLight->Enable = true;									// ���̃��C�g��ON
	//SetLightData(1, pLight);								// ����Őݒ肵�Ă���


	SetCameraAT(m_Obj.pos);
	SetCamera();

	m_ItemManager.mRegister(m_ItemFactory.CreateBullet());
	m_ItemManager.mRegister(m_ItemFactory.CreateExpPoint());

	m_ItemManager.Init();

	//	SelectSkill�ɂ���匳�̃X�L���Ǘ��ϐ������炤
	m_SkillManeger = GetSkillManager_Scene();

	

	m_SkillManeger->Init();
	

	m_UI.Init();
}

void GO_Player::Uninit()
{
	UnloadModel(&m_Model);
	UnloadModel(&m_ChildModel);

	m_ItemManager.Uninit();

	m_SkillManeger->Uninit();

	m_UI.Uninit();
	
}

void GO_Player::Update()
{

	cam = GetCamera();

	CameraUpdate();

	LightUpdate();

	if (m_Obj.use == false)return;

	PlayerUpdate();	


	m_ChildObj.pos = m_Obj.pos;

	m_ChildObj.rot.y += 0.01f;


	m_SkillManeger->SetPlayerPos(m_Obj.pos);

	m_ItemManager.Update();

	m_SkillManeger->Update();

	

	m_UI.GetEXP()->SetPos(D3DXVECTOR3(m_Obj.pos.x, m_Obj.pos.y + 50.0f, m_Obj.pos.z));

	m_UI.Update();

	

	m_PrePlayerPosY = m_Obj.pos.y;
}

void GO_Player::Draw()
{
	if (m_Obj.use == false)return;

	//�J�����O�Ȃ�
	SetCullingMode(CULL_MODE_NONE);

	//	���W�ϊ�
	CoordinateTransformation(&m_Obj);

	

	DrawModel(&m_Model);



	CoordinateTransformation(&m_ChildObj);

	DrawModel(&m_ChildModel);

	SetCullingMode(CULL_MODE_BACK);

	m_ItemManager.Draw();
	m_SkillManeger->Draw();
	m_UI.Draw();
}



void GO_Player::PlayerUpdate()
{
	//�ړ����x�̌�������
	m_Obj.spd *= 0.9f;

	PlayerInputUpdate();

	// �����������Ƀv���C���[���ړ�������
	// �����������Ƀv���C���[���������Ă��鏊
	m_Obj.rot.y = m_Rot + cam->rot.y;

	m_Obj.pos.x += sinf(m_Obj.rot.y) * m_Obj.spd;
	m_Obj.pos.z += cosf(m_Obj.rot.y) * m_Obj.spd;


	m_Obj.rot.x = m_Rot_x + cam->rot.x;

	m_Obj.pos.y -= sinf(m_Obj.rot.x) * m_Obj.spd;



#ifdef _DEBUG	// �f�o�b�O�ł̎�����Angle��\������
	


	sprintf(&GetDebugStr()[strlen(GetDebugStr())], " X:%.2f Y:%.2f Z:%.2f",m_Obj.pos.x, m_Obj.pos.y, m_Obj.pos.z);

	SetWindowText(GethWnd()[0], GetDebugStr());
#endif
}

void GO_Player::CameraUpdate()
{
	// �J�����̒����_���v���C���[�̍��W�ɂ��Ă݂�
	cam->at = m_Obj.pos;

	// �J�����̎��_���J������Y����]�ɑΉ������Ă���
	cam->pos.x = cam->at.x - sinf(cam->rot.y) * cam->len;
	cam->pos.z = cam->at.z - cosf(cam->rot.y) * cam->len;

	cam->pos.y = cam->at.y + sinf(cam->rot.x) * cam->len ;
	//cam->pos.y = cam->at.y + cam->len;

	SetCameraAT(m_Obj.pos);
	SetCamera();
}

void GO_Player::PlayerInputUpdate()
{
	//	�X�L���I�����̓C���v�b�g���ւ���
	if (GetSelectSkillState())return;

	if (GetKeyboardPress(DIK_A))
	{
		m_Obj.spd = VALUE_MOVE;
		m_Rot = -D3DX_PI / 2;
	}
	if (GetKeyboardPress(DIK_D))
	{
		m_Obj.spd = VALUE_MOVE;
		m_Rot = D3DX_PI / 2;
	}

	if (GetKeyboardPress(DIK_W))
	{
		m_Obj.spd = VALUE_MOVE;
		m_Rot = 0.0f;
	}
	if (GetKeyboardPress(DIK_S))
	{
		m_Obj.spd = VALUE_MOVE;
		m_Rot = D3DX_PI;
	}
}

void GO_Player::LightUpdate()
{
	//pLight->Position =
	//	D3DXVECTOR4(m_Obj.pos.x, m_Obj.pos.y + 100.0f, m_Obj.pos.z, 0.0f);

	//SetLightData(1, pLight);	// ����Őݒ肵�Ă���
}

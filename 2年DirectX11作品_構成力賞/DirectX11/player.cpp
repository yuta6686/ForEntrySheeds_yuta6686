//=============================================================================
//
// �|���S���\������ [player.cpp]
// Author : YanagisawaYuta
// �T���v���Ƃ��Ďc��
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "player.h"
#include "texture.h"
#include "model.h"
#include "light.h"
#include "bullet.h"
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************



struct KEYFRAME {
	D3DXVECTOR3 rot;
	int key;
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static DX11_MODEL	g_Model;	// ���f���ǂݍ���

static DX11_MODEL	g_Model_Miku_Body;
static DX11_MODEL	g_Model_Miku_ArmR;
static DX11_MODEL	g_Model_Miku_ArmL;

static PLAYER	g_Player;	// �v���C���[���		
static PLAYER	g_MikuArmR;
static PLAYER	g_MikuArmL;

static float        g_Rot;		// �L�����N�^�[�̌���
static float		g_Rot_x;
static float		g_ArmRot;
static float		g_PrePlayerPosY;

static int g_frame;

static KEYFRAME g_ArmAnimation[5] = {
	{{0.0f,0.0f,0.0f},0},
	{{1.0f,0.0f,0.0f},40},
	{{0.0f,0.0f,0.0f},80},
	{{-1.0f,0.0f,0.0f},120},
	{{0.0f,0.0f,0.0f},160},
};

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(void)
{
	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	g_Player.pos = D3DXVECTOR3(0.0f, 35.0f, 0.0f);
	g_Player.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.scl = D3DXVECTOR3(5.0f, 5.0f, 5.0f);
	g_Player.use = true;

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	g_MikuArmR.pos = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);
	g_MikuArmR.offset = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	g_MikuArmR.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MikuArmR.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_MikuArmR.use = true;
	

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	g_MikuArmL.pos = D3DXVECTOR3(2.0f, -2.0f, 0.0f);
	g_MikuArmL.offset = D3DXVECTOR3(0.0f,-1.0f, 0.0f);
	g_MikuArmL.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MikuArmL.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_MikuArmL.use = true;



	//�����蔻��p�T�C�Y�̏����ݒ�
	g_Player.size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);

	//obj���f���̓ǂݍ���
	LoadModel((char*)"data/MODEL/miku_01.obj", &g_Model);

	LoadModel((char*)"data/MODEL/miku_body.obj", &g_Model_Miku_Body);
	LoadModel((char*)"data/MODEL/miku_arm_r.obj", &g_Model_Miku_ArmR);
	LoadModel((char*)"data/MODEL/miku_arm_l.obj", &g_Model_Miku_ArmL);


	g_ArmRot = 0.1f;
	g_PrePlayerPosY = 0.0f;

	//�e�̐ݒ�
	D3DXVECTOR3 sPos = g_Player.pos;
	sPos.y = 0.0f;
	g_Player.idxShadow = CreateShadow(sPos, 100.0f, 100.0f);

	// ���s�����̐ݒ�i���E���Ƃ炷���j
	//LIGHT *pLight = NULL;
	//pLight = GetLightData(0);
	//pLight->Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);// ���̌���
	//pLight->Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);	// ���̐F
	//pLight->Type = LIGHT_TYPE_DIRECTIONAL;					// ���s����
	//pLight->Enable = false;									// ���̃��C�g��ON
	//SetLightData(0, pLight);									// ����Őݒ肵�Ă���

	//// �_�����̐ݒ�
	//pLight = GetLightData(1);
	//pLight->Position = D3DXVECTOR4(0.0f,500.0f, 0.0f, 0.0f);
	//pLight->Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);// ���̌���
	//pLight->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// ���̐F
	//pLight->Attenuation = 1000.0f;							// ��������
	//pLight->Type = LIGHT_TYPE_POINT;						// ���s����
	//pLight->Enable = true;									// ���̃��C�g��ON
	//SetLightData(1, pLight);								// ����Őݒ肵�Ă���

	

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	//obj���f���̉��
	UnloadModel(&g_Model);
	UnloadModel(&g_Model_Miku_Body);
	UnloadModel(&g_Model_Miku_ArmL);
	UnloadModel(&g_Model_Miku_ArmR);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	CAMERA *cam = GetCamera();

	//�ړ����x�̌�������
	g_Player.spd *= 0.9f;

	

	if (GetKeyboardPress(DIK_A) ||
		GetKeyboardPress(DIK_S) ||
		GetKeyboardPress(DIK_D) ||
		GetKeyboardPress(DIK_W)) {

		if (g_frame >= 160) {
			g_frame = 0;
		}
		else {
			g_frame++;
			
			for (int i = 0; i < 4; i++) {
				if (g_frame >= g_ArmAnimation[i].key &&
					g_frame <= g_ArmAnimation[i + 1].key) {
					D3DXVec3Lerp(&g_MikuArmL.rot, &g_ArmAnimation[0].rot,
						&g_ArmAnimation[4].rot, g_frame/160);
					
				}
			}
		}

		//D3DXVECTOR3 kekka, saisho, saigo;
		//�}��ϐ� t(0.0 �` 1.0)
		//D3DXVec3Lerp(&kekka, &saisho, &saigo, t);

		

		/*if (g_MikuArmL.rot.x >= D3DX_PI / 2.0f) {
			g_ArmRot *= -1.0f;
		}
		if (g_MikuArmL.rot.x <= -D3DX_PI / 2.0f) {
			g_ArmRot *= -1.0f;
		}

		g_MikuArmL.rot.x += g_ArmRot;
		g_MikuArmR.rot.x -= g_ArmRot;*/


	}
	else {
		g_MikuArmL.rot.x *= 0.9f;
		g_MikuArmR.rot.x *= 0.9f;
	}

	if (GetKeyboardPress(DIK_A))
	{
		g_Player.spd = VALUE_MOVE;
		g_Rot = -D3DX_PI / 2;
	}
	if (GetKeyboardPress(DIK_D))
	{
		g_Player.spd = VALUE_MOVE;
		g_Rot = D3DX_PI / 2;
	}

	if (GetKeyboardPress(DIK_W))
	{
		g_Player.spd = VALUE_MOVE;
		g_Rot = 0.0f;
	}
	if (GetKeyboardPress(DIK_S))
	{
		g_Player.spd = VALUE_MOVE;
		g_Rot = D3DX_PI;
	}

	{	// �����������Ƀv���C���[���ړ�������
		// �����������Ƀv���C���[���������Ă��鏊
		g_Player.rot.y = g_Rot + cam->rot.y;

		g_Player.pos.x += sinf(g_Player.rot.y) * g_Player.spd;
		g_Player.pos.z += cosf(g_Player.rot.y) * g_Player.spd;

		
		g_Player.rot.x = g_Rot_x + cam->rot.x;

		g_Player.pos.y -= sinf(g_Player.rot.x) * g_Player.spd;
		
	}

	// �J�����̒����_���v���C���[�̍��W�ɂ��Ă݂�
	cam->at = g_Player.pos;

	// �J�����̎��_���J������Y����]�ɑΉ������Ă���
	cam->pos.x = cam->at.x - sinf(cam->rot.y) * cam->len;
	cam->pos.z = cam->at.z - cosf(cam->rot.y) * cam->len;

	cam->pos.y = cam->at.y + sinf(cam->rot.x) * cam->len + g_PrePlayerPosY * 1.5f;
	//cam->pos.y = cam->at.y + cam->len;

	// �e������
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		SetBullet(g_Player.pos);
	}

	//�e�̈ʒu�̍X�V
	D3DXVECTOR3 sPos = g_Player.pos;
	sPos.y = 0.0f;
	SetPositionShadow(g_Player.idxShadow, sPos);

//#ifdef _DEBUG	// �f�o�b�O����\������
//	char* str = GetDebugStr();
//	sprintf(&str[strlen(str)], " rotX:%.2f rotY:%.2f", g_Player.rot.x, g_Player.rot.y);
//
//#endif

	g_PrePlayerPosY = g_Player.pos.y;
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ���[���h�}�g���b�N�X�̏������i�P�ʍs������֐��j
	D3DXMatrixIdentity(&g_Player.mtxWorld);	

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, g_Player.scl.x, g_Player.scl.y, g_Player.scl.z);

	                   //��1���� ��          ��2����      ��    ��3����
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&g_Player.mtxWorld);

	//�J�����O�Ȃ�
	SetCullingMode(CULL_MODE_NONE);


	DrawModel(&g_Model_Miku_Body);



	SetCullingMode(CULL_MODE_BACK);

	///***	�q	***///

	// ���[���h�}�g���b�N�X�̏������i�P�ʍs������֐��j
	D3DXMatrixIdentity(&g_MikuArmL.mtxWorld);
	
	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, g_MikuArmL.scl.x, g_MikuArmL.scl.y, g_MikuArmL.scl.z);

	//��1���� ��          ��2����      ��    ��3����
	D3DXMatrixMultiply(&g_MikuArmL.mtxWorld, &g_MikuArmL.mtxWorld, &mtxScl);

	//�I�t�Z�b�g�ړ����s��
	D3DXMatrixTranslation(&mtxTranslate, g_MikuArmL.offset.x,g_MikuArmL.offset.y, g_MikuArmL.offset.z);
	D3DXMatrixMultiply(&g_MikuArmL.mtxWorld, &g_MikuArmL.mtxWorld, &mtxTranslate);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MikuArmL.rot.y, g_MikuArmL.rot.x, g_MikuArmL.rot.z);
	D3DXMatrixMultiply(&g_MikuArmL.mtxWorld, &g_MikuArmL.mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, g_MikuArmL.pos.x, g_MikuArmL.pos.y, g_MikuArmL.pos.z);
	D3DXMatrixMultiply(&g_MikuArmL.mtxWorld, &g_MikuArmL.mtxWorld, &mtxTranslate);

	//�e�̕ϊ��𔽉f������
	D3DXMatrixMultiply(&g_MikuArmL.mtxWorld, &g_MikuArmL.mtxWorld, &g_Player.mtxWorld);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&g_MikuArmL.mtxWorld);

	//�J�����O�Ȃ�
	SetCullingMode(CULL_MODE_NONE);

	DrawModel(&g_Model_Miku_ArmL);

	SetCullingMode(CULL_MODE_BACK);

	///***	�q	***///

	// ���[���h�}�g���b�N�X�̏������i�P�ʍs������֐��j
	D3DXMatrixIdentity(&g_MikuArmR.mtxWorld);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, g_MikuArmR.scl.x, g_MikuArmR.scl.y, g_MikuArmR.scl.z);

	//��1���� ��          ��2����      ��    ��3����
	D3DXMatrixMultiply(&g_MikuArmR.mtxWorld, &g_MikuArmR.mtxWorld, &mtxScl);

	//�I�t�Z�b�g�ړ����s��
	D3DXMatrixTranslation(&mtxTranslate, g_MikuArmR.offset.x, g_MikuArmR.offset.y, g_MikuArmR.offset.z);
	D3DXMatrixMultiply(&g_MikuArmR.mtxWorld, &g_MikuArmR.mtxWorld, &mtxTranslate);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MikuArmR.rot.y, g_MikuArmR.rot.x, g_MikuArmR.rot.z);
	D3DXMatrixMultiply(&g_MikuArmR.mtxWorld, &g_MikuArmR.mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, g_MikuArmR.pos.x, g_MikuArmR.pos.y, g_MikuArmR.pos.z);
	D3DXMatrixMultiply(&g_MikuArmR.mtxWorld, &g_MikuArmR.mtxWorld, &mtxTranslate);

	//�e�̕ϊ��𔽉f������
	D3DXMatrixMultiply(&g_MikuArmR.mtxWorld, &g_MikuArmR.mtxWorld, &g_Player.mtxWorld);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&g_MikuArmR.mtxWorld);

	//�J�����O�Ȃ�
	SetCullingMode(CULL_MODE_NONE);

	DrawModel(&g_Model_Miku_ArmR);

	SetCullingMode(CULL_MODE_BACK);
}


//=============================================================================
// �v���C���[�����擾
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_Player;
}


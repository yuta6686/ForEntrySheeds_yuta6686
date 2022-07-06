//=============================================================================
//
// �|���S���\������ [enemy.cpp]
// Author : Yanagisawa Yuta
// 
// �T���v���Ƃ��Ďc���Ă���
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "enemy.h"
#include "texture.h"
#include "model.h"
#include "light.h"
#include "player.h"
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	VALUE_MOVE		(5.0f)						// �ړ���
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// ��]��


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static DX11_MODEL	g_Model;			// ���f���ǂݍ���
static ENEMY		g_Enemy[ENEMY_NUM];	// �G�l�~�[���		
static float        g_Rot;				// �L�����N�^�[�̌���

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy(void)
{
	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		g_Enemy[i].pos = D3DXVECTOR3(frand()*1000 - 500.0f, 35.0f, frand() * 1000 - 500.0f);
		g_Enemy[i].rot = D3DXVECTOR3(frand()*D3DX_PI, 0.0f, frand()*D3DX_PI);
		g_Enemy[i].scl = D3DXVECTOR3(3.0f, 3.0f, 3.0f);
		g_Enemy[i].dir = D3DXVECTOR3(frand() - 0.5f, 0.0f, frand() - 0.5f);
		g_Enemy[i].spd = 1.0f;
		g_Enemy[i].use = true;

		g_Enemy[i].size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);

		//�P�ʃx�N�g��������
		D3DXVec3Normalize(&g_Enemy[i].dir, &g_Enemy[i].dir);

		D3DXVECTOR3 sPos = g_Enemy[i].pos;
		sPos.y = 0.0f;
		g_Enemy[i].idxShadow = CreateShadow(sPos, 100.0f, 100.0f);
	}

	//obj���f���̓ǂݍ���
	LoadModel((char*)"data/MODEL/torus.obj", &g_Model);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	//obj���f���̉��
	UnloadModel(&g_Model);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		//use�t���O���I�t�̏ꍇ�̓X�L�b�v����
		if (g_Enemy[i].use == false)
			continue;

		//���W�̍X�V
		g_Enemy[i].pos += g_Enemy[i].dir * g_Enemy[i].spd;

		//��]�̍X�V
		g_Enemy[i].rot.x += 0.05f;
		g_Enemy[i].rot.y += 0.05f;

		if (g_Enemy[i].pos.x > 500.0f)
			g_Enemy[i].dir.x *= -1;

		if (g_Enemy[i].pos.x < -500.0f)
			g_Enemy[i].dir.x *= -1;

		if (g_Enemy[i].pos.z > 500.0f)
			g_Enemy[i].dir.z *= -1;

		if (g_Enemy[i].pos.z < -500.0f)
			g_Enemy[i].dir.z *= -1;

		//�e�̈ʒu�̍X�V
		D3DXVECTOR3 sPos = g_Enemy[i].pos;
		sPos.y = 0.0f;
		SetPositionShadow(g_Enemy[i].idxShadow, sPos);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	for (int i = 0; i < ENEMY_NUM; i++)
	{
		//use�t���O���I�t�̏ꍇ�̓X�L�b�v����
		if (g_Enemy[i].use == false)
			continue;

		// ���[���h�}�g���b�N�X�̏������i�P�ʍs������֐��j
		D3DXMatrixIdentity(&g_Enemy[i].mtxWorld);

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScl, g_Enemy[i].scl.x, g_Enemy[i].scl.y, g_Enemy[i].scl.z);
		D3DXMatrixMultiply(&g_Enemy[i].mtxWorld, &g_Enemy[i].mtxWorld, &mtxScl);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[i].rot.y, g_Enemy[i].rot.x, g_Enemy[i].rot.z);
		D3DXMatrixMultiply(&g_Enemy[i].mtxWorld, &g_Enemy[i].mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, g_Enemy[i].pos.x, g_Enemy[i].pos.y, g_Enemy[i].pos.z);
		D3DXMatrixMultiply(&g_Enemy[i].mtxWorld, &g_Enemy[i].mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		SetWorldMatrix(&g_Enemy[i].mtxWorld);

		//obj���f���̕`��
		DrawModel(&g_Model);
	}
}


//=============================================================================
// �G�l�~�[�����擾
//=============================================================================
ENEMY *GetEnemy(void)
{
	return g_Enemy;
}


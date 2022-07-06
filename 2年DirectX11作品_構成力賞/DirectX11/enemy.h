//=============================================================================
//
// �n�ʏ��� [enemy.h]
// Author : Yanagisawa Yuta
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "renderer.h"
#include "GameObject.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ENEMY_NUM 10

struct ENEMY
{
	D3DXVECTOR3		pos;		// �ʒu
	D3DXVECTOR3		rot;		// ����(��])
	D3DXVECTOR3		scl;		// �傫��(�X�P�[��)
	D3DXVECTOR3		dir;		// �ړ�����
	float			spd;		// �ړ��X�s�[�h
	bool			use;		// �\���t���O

	int				idxShadow;	// �e�̎��ʎq

	D3DXVECTOR3     size;		// �����蔻��p�T�C�Y

	D3DXMATRIX		mtxWorld;	// ���[���h�}�g���b�N�X
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

ENEMY *GetEnemy(void);


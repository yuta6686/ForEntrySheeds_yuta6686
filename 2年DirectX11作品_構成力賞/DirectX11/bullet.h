//=============================================================================
//
// �e���� [bullet.h]
// Author : Yanagisawa Yuta
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BULLET_MAX		(10)		// �o���b�g��Max��
#define BULLET_SPEED	(10.0f)		// �o���b�g�̈ړ��X�s�[�h


// �o���b�g�\����
struct BULLET
{
	D3DXMATRIX				mtxWorld;
	bool					use;	// true:�g���Ă���  false:���g�p
	D3DXVECTOR3				pos;	// �o���b�g�̍��W
	D3DXVECTOR3				move;	// �o���b�g�̈ړ���
	float					frame;	// �t���[����
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

BULLET *GetBullet(void);
void SetBullet(D3DXVECTOR3 pos);


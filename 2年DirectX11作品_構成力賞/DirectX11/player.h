//=============================================================================
//
// �n�ʏ��� [player.h]
// Author : Yanagisawa Yuta
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	VALUE_MOVE		(5.0f)						// �ړ���
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// ��]��
struct PLAYER
{
	D3DXVECTOR3		pos;		// �ʒu
	D3DXVECTOR3		rot;		// ����(��])
	D3DXVECTOR3		scl;		// �傫��(�X�P�[��)
	D3DXVECTOR3		offset;		// �I�t�Z�b�g���W

	float			spd;		// �ړ��X�s�[�h
	bool			use;		// �\���t���O

	int				idxShadow;	// �e�̎��ʎq

	D3DXVECTOR3     size;		// �����蔻��p�T�C�Y

	D3DXMATRIX		mtxWorld;	// ���[���h�}�g���b�N�X
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

//PLAYER *GetPlayer(void);

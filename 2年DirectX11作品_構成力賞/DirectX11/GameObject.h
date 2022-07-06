//=============================================================================
//
// �Q�[���I�u�W�F�N�g�̃C���^�t�F�[�X [GameObject.h]
// Author : Yanagisawa Yuta
//
//=============================================================================
#pragma once
#include "main.h"
#include "input.h"
#include "camera.h"
#include "texture.h"
#include "model.h"
#include "light.h"


struct GAME_OBJECT 
{
	D3DXVECTOR3		pos;		// �ʒu
	D3DXVECTOR3		rot;		// ����(��])
	D3DXVECTOR3		scl;		// �傫��(�X�P�[��)
	D3DXVECTOR3		offset;		// �I�t�Z�b�g���W

	D3DXCOLOR		col;

	float			spd;		// �ړ��X�s�[�h
	
	bool			use;		// �\���t���O

	bool			free;		//	��������Ŏg����

	int				idxShadow;	// �e�̎��ʎq
	int				counter;

	D3DXVECTOR3     size;		// �����蔻��p�T�C�Y

	D3DXVECTOR3		vec;

	D3DXMATRIX		mtxWorld;	// ���[���h�}�g���b�N�X
};



class GameObject
{
public:
	GameObject() {}
	

	virtual void Init()=0;
	virtual void Uninit()=0;
	virtual void Update()=0;
	virtual void Draw()=0;


	
	
};


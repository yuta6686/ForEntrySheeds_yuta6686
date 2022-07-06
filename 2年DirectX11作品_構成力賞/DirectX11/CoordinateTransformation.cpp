//=============================================================================
//
// ���W�ϊ������܂Ƃ� [CoordinateTransformation.cpp]
// Author : Yanagisawa Yuta
//
//=============================================================================
#include "CoordinateTransformation.h"

void CoordinateTransformation(GAME_OBJECT* go) {

	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

// ���[���h�}�g���b�N�X�̏������i�P�ʍs������֐��j
	D3DXMatrixIdentity(&go->mtxWorld);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, go->scl.x, go->scl.y, go->scl.z);

	//��1���� ��          ��2����      ��    ��3����
	D3DXMatrixMultiply(&go->mtxWorld, &go->mtxWorld, &mtxScl);

	//�I�t�Z�b�g�ړ����s��
	D3DXMatrixTranslation(&mtxTranslate, go->offset.x, go->offset.y, go->offset.z);
	D3DXMatrixMultiply(&go->mtxWorld, &go->mtxWorld, &mtxTranslate);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, go->rot.y, go->rot.x, go->rot.z);
	D3DXMatrixMultiply(&go->mtxWorld, &go->mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, go->pos.x, go->pos.y, go->pos.z);
	D3DXMatrixMultiply(&go->mtxWorld, &go->mtxWorld, &mtxTranslate);

	//�e�̕ϊ��𔽉f������
	//D3DXMatrixMultiply(&go->mtxWorld, &go->mtxWorld, &g_Player.mtxWorld);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&go->mtxWorld);
}
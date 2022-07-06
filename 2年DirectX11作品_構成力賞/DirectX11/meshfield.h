//=============================================================================
//
// ���b�V���n�ʂ̏��� [meshfield.h]
// Author : Yanagisawa Yuta
//
//=============================================================================
#pragma once

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitMeshField(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int numBlockX, int numBlockZ, float sizeX, float sizeZ);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);


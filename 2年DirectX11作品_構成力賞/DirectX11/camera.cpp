//=============================================================================
//
// �J�������� [camera.cpp]
// Author : Yanagisawa Yuta
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	POS_X_CAM		(0.0f)			// �J�����̏����ʒu(X���W)
#define	POS_Y_CAM		(200.0f)		// �J�����̏����ʒu(Y���W)
#define	POS_Z_CAM		(-400.0f)		// �J�����̏����ʒu(Z���W)

#define	VIEW_ANGLE		(D3DXToRadian(45.0f))							// �r���[���ʂ̎���p
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��	
#define	VIEW_NEAR_Z		(10.0f)											// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z		(10000.0f)										// �r���[���ʂ�FarZ�l

#define	VALUE_MOVE_CAMERA	(20.0f)										// �J�����̈ړ���
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)							// �J�����̉�]��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static CAMERA			g_Camera;		// �J�����f�[�^

//=============================================================================
// ����������
//=============================================================================
void InitCamera(void)
{
	g_Camera.pos = D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);
	g_Camera.at = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_Camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���_�ƒ����_�̋������v�Z
	float vx, vz;
	vx = g_Camera.pos.x - g_Camera.at.x;
	vz = g_Camera.pos.z - g_Camera.at.z;
	g_Camera.len = sqrtf(vx * vx + vz * vz);

}


//=============================================================================
// �J�����̏I������
//=============================================================================
void UninitCamera(void)
{

}


void InitialCameraUpdate();
//=============================================================================
// �J�����̍X�V����
//=============================================================================
void UpdateCamera(void)
{
	if (GetSelectSkillState())return;

	if (IsMouseRightPressed()) {

		//	������@�}�E�X
		g_Camera.rot.y += VALUE_ROTATE_CAMERA * GetMouseX()/10.0f;
		if (g_Camera.rot.y > D3DX_PI)
		{
			g_Camera.rot.y -= D3DX_PI * 2.0f;
		}

		g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;
		
		//	�c����@�}�E�X
		g_Camera.rot.x += VALUE_ROTATE_CAMERA * GetMouseY() / 10.0f;

		if (g_Camera.rot.x <= 0.0f - D3DX_PI /4.0f) {
			g_Camera.rot.x = 0.0f - D3DX_PI / 4.0f;
		}

		//	�������@���E�l
		if (g_Camera.rot.x >= D3DX_PI)
		{
			g_Camera.rot.x = D3DX_PI;
		}

		//�@������@���E�l
		if (g_Camera.rot.x < D3DX_PI / -4.0f)
		{
			g_Camera.rot.x = D3DX_PI / -4.0f;
		}

		//	������������X�i�b�v���������B
		/*if (g_Camera.rot.x > D3DX_PI / 4.0f &&
			g_Camera.rot.x < D3DX_PI / 4.0f * 3.0f) {
			g_Camera.rot.x = D3DX_PI / 4.0f;
		}*/


#ifdef _DEBUG	// �f�o�b�O����\������
		char* str = GetDebugStr();
		wsprintf(&str[strlen(str)], " rotX:%.2f rotY:%.2f", g_Camera.rot.x, g_Camera.rot.y);
	

#endif
		if (g_Camera.rot.x > D3DX_PI)
		{
			g_Camera.rot.x = D3DX_PI;
		}
		g_Camera.pos.y = g_Camera.at.y + sinf(g_Camera.rot.x) * g_Camera.len;
		g_Camera.pos.z = g_Camera.at.z + cosf(g_Camera.rot.x) * g_Camera.len;
	}

	InitialCameraUpdate();

}

void InitialCameraUpdate() 
{
#ifdef _DEBUG

	if (GetKeyboardPress(DIK_Z))
	{// ���_����u���v
		g_Camera.rot.y += VALUE_ROTATE_CAMERA;
		if (g_Camera.rot.y > D3DX_PI)
		{
			g_Camera.rot.y -= D3DX_PI * 2.0f;
		}

		g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;
	}

	if (GetKeyboardPress(DIK_C))
	{// ���_����u�E�v
		g_Camera.rot.y -= VALUE_ROTATE_CAMERA;
		if (g_Camera.rot.y < -D3DX_PI)
		{
			g_Camera.rot.y += D3DX_PI * 2.0f;
		}

		g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;
	}

	if (GetKeyboardPress(DIK_Y))
	{// ���_�ړ��u��v
		g_Camera.pos.y += VALUE_MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_N))
	{// ���_�ړ��u���v
		g_Camera.pos.y -= VALUE_MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_Q))
	{// �����_����u���v
		g_Camera.rot.y -= VALUE_ROTATE_CAMERA;
		if (g_Camera.rot.y < -D3DX_PI)
		{
			g_Camera.rot.y += D3DX_PI * 2.0f;
		}

		g_Camera.at.x = g_Camera.pos.x + sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.at.z = g_Camera.pos.z + cosf(g_Camera.rot.y) * g_Camera.len;
	}

	if (GetKeyboardPress(DIK_E))
	{// �����_����u�E�v
		g_Camera.rot.y += VALUE_ROTATE_CAMERA;
		if (g_Camera.rot.y > D3DX_PI)
		{
			g_Camera.rot.y -= D3DX_PI * 2.0f;
		}

		g_Camera.at.x = g_Camera.pos.x + sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.at.z = g_Camera.pos.z + cosf(g_Camera.rot.y) * g_Camera.len;
	}

	if (GetKeyboardPress(DIK_T))
	{// �����_�ړ��u��v
		g_Camera.at.y += VALUE_MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_B))
	{// �����_�ړ��u���v
		g_Camera.at.y -= VALUE_MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_U))
	{// �߂Â�
		g_Camera.len -= VALUE_MOVE_CAMERA;
		g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;
	}

	if (GetKeyboardPress(DIK_M))
	{// �����
		g_Camera.len += VALUE_MOVE_CAMERA;
		g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;
	}

#endif
	// �J�����������ɖ߂�
	if (GetKeyboardPress(DIK_P))
	{
		UninitCamera();
		InitCamera();
	}
}

//=============================================================================
// �J�����̍X�V
//=============================================================================
void SetCamera(void) 
{
	// �r���[�}�g���b�N�X�ݒ�
	D3DXMatrixLookAtLH(&g_Camera.mtxView, &g_Camera.pos, &g_Camera.at, &g_Camera.up);

	SetViewMatrix(&g_Camera.mtxView);


//	float det;
//	D3DXMatrixInverse(&g_Camera.mtxInvView, &det, &g_Camera.mtxView);


	// �v���W�F�N�V�����}�g���b�N�X�ݒ�
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection, 1.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, VIEW_NEAR_Z, VIEW_FAR_Z);

	SetProjectionMatrix(&g_Camera.mtxProjection);
}


//=============================================================================
// �J�����̎擾
//=============================================================================
CAMERA *GetCamera(void) 
{
	return &g_Camera;
}


// �J�����̎��_�ƒ����_���Z�b�g
void SetCameraAT(D3DXVECTOR3 pos)
{
	// �J�����̒����_���v���C���[�̍��W�ɂ��Ă݂�
	g_Camera.at = pos;

	// �J�����̎��_���J������Y����]�ɑΉ������Ă���
	g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
	g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;

	
}


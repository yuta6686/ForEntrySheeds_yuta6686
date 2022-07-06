//=============================================================================
//
// �e���� [bullet.cpp]
// Author : Yanagisawa Yuta
//
// �T���v���Ƃ��Ďc��
//=============================================================================
#include "bullet.h"
#include "camera.h"
#include "texture.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer		*g_VertexBuffer = NULL;	// ���_�o�b�t�@

static BULLET		g_Bullet[BULLET_MAX];	// �e�f�[�^
static MATERIAL		g_Material;
static int			g_texNo = 0;


//=============================================================================
// ����������
//=============================================================================
void InitBullet(void)
{
	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);


	// ���_�o�b�t�@�ɒl���Z�b�g����
	{
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		float width = 50.0f;
		float height = 50.0f;

		// ���_���W�̐ݒ�
		vertex[0].Position = D3DXVECTOR3(-width / 2.0f, 0.0f, 0.0f);
		vertex[1].Position = D3DXVECTOR3(-width / 2.0f, height, 0.0f);
		vertex[2].Position = D3DXVECTOR3(width / 2.0f, 0.0f, 0.0f);
		vertex[3].Position = D3DXVECTOR3(width / 2.0f, height, 0.0f);

		// ���_�J���[�̐ݒ�
		vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		vertex[0].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
		vertex[2].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

		GetDeviceContext()->Unmap(g_VertexBuffer, 0);
	}

	// �e�N�X�`������
	g_texNo = LoadTexture((char*)"data/TEXTURE/bullet000.png");

	// �}�e���A��������
	ZeroMemory(&g_Material, sizeof(g_Material));
	g_Material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ������
	for(int i = 0; i < BULLET_MAX; i++)
	{
		g_Bullet[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[i].use = false;
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
{
	if(g_VertexBuffer != NULL)
	{// ���_�o�b�t�@�̉��
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBullet(void)
{
	for(int i = 0; i < BULLET_MAX; i++)
	{
		if(g_Bullet[i].use)
		{
			//���ŏ���
			if (g_Bullet[i].frame > 100.0f)
			{
				g_Bullet[i].use = false;
			}

			//���W�̍X�V
			g_Bullet[i].pos += g_Bullet[i].move;

			//���Ԍo��
			g_Bullet[i].frame += 1.0f;

		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBullet(void)
{
	// ���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���C�e�B���O�𖳌�
	SetLightEnable(false);

	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	for(int i = 0; i < BULLET_MAX; i++)
	{
		if(g_Bullet[i].use)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Bullet[i].mtxWorld);

			CAMERA *cam = GetCamera();

			// �|���S���𐳖ʂɌ�����
#if 0
			// �r���[�}�g���b�N�X�̋t�s����擾
			g_Bullet[i].mtxWorld = cam->mtxInvView;
			g_Bullet[i].mtxWorld._41 = 0.0f;
			g_Bullet[i].mtxWorld._42 = 0.0f;
			g_Bullet[i].mtxWorld._43 = 0.0f;
#else
			// �r���[�}�g���b�N�X���擾
			D3DXMATRIX mtxView = cam->mtxView;

			g_Bullet[i].mtxWorld._11 = mtxView._11;
			g_Bullet[i].mtxWorld._12 = mtxView._21;
			g_Bullet[i].mtxWorld._13 = mtxView._31;
			g_Bullet[i].mtxWorld._21 = mtxView._12;
			g_Bullet[i].mtxWorld._22 = mtxView._22;
			g_Bullet[i].mtxWorld._23 = mtxView._32;
			g_Bullet[i].mtxWorld._31 = mtxView._13;
			g_Bullet[i].mtxWorld._32 = mtxView._23;
			g_Bullet[i].mtxWorld._33 = mtxView._33;
#endif


			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, g_Bullet[i].pos.x,
												 g_Bullet[i].pos.y,
												 g_Bullet[i].pos.z);
			D3DXMatrixMultiply(&g_Bullet[i].mtxWorld, &g_Bullet[i].mtxWorld, &mtxTranslate);


			// ���[���h�}�g���b�N�X�̐ݒ�
			SetWorldMatrix(&g_Bullet[i].mtxWorld);

			// �}�e���A���ݒ�
			SetMaterial(g_Material);

			// �e�N�X�`���ݒ�
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_texNo));

			// �|���S���̕`��
			GetDeviceContext()->Draw(4, 0);
		}
	}

	// ���C�e�B���O��L����
	SetLightEnable(true);

	// ���e�X�g�𖳌���
	SetAlphaTestEnable(false);
}


//=============================================================================
// �e�̃p�����[�^���Z�b�g
//=============================================================================
void SetBullet(D3DXVECTOR3 pos)
{
	for(int i = 0; i < BULLET_MAX; i++)
	{
		//�܂��\������Ă��Ȃ��ꏊ��T��
		if(g_Bullet[i].use == false)
		{
			g_Bullet[i].pos = pos;
			g_Bullet[i].move = D3DXVECTOR3(0.0f, 0.0f, BULLET_SPEED);
			g_Bullet[i].frame = 0.0f;
			g_Bullet[i].use = true;

			break;
		}
	}
}

BULLET* GetBullet(void)
{
	return &g_Bullet[0];
}

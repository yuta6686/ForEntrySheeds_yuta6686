//=============================================================================
//
// ���b�V���n�ʂ̏��� [meshfield.cpp]
// Author : YanagisawaYuta
// �T���v���Ƃ��Ďc��
//=============================================================================
#include "main.h"
#include "input.h"
#include "texture.h"
#include "meshfield.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
struct FIELD
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scl;
	D3DXMATRIX  mtxWorld;
};

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;	// ���_�o�b�t�@
static ID3D11Buffer					*g_IndexBuffer = NULL;	// �C���f�b�N�X�o�b�t�@

static FIELD	g_Field;	// �t�B�[���h���
static int		g_TexNo;	// �e�N�X�`���ԍ�

static int numVertex = 8;
static int numIndex = 8;


//=============================================================================
// ����������
//=============================================================================
HRESULT InitMeshField(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int numBlockX, int numBlockZ, float sizeX, float sizeZ)
{
	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	g_Field.pos = pos;
	g_Field.rot = rot;
	g_Field.scl = D3DXVECTOR3(3.0f, 2.0f,2.0f);

	// �e�N�X�`������
	g_TexNo = LoadTexture((char*)"data/TEXTURE/Razer.png");


	int yoko = numBlockX;
	int tate = numBlockZ;

	//�K�v�Ȓ��_�����v�Z����
	numVertex = (yoko + 1) * (tate + 1);
	numIndex = (yoko + 1) * 2 * tate + (tate - 1) * 2;

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * numVertex;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);


	// �C���f�b�N�X�o�b�t�@����
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(unsigned short) * numIndex;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	GetDevice()->CreateBuffer(&bd, NULL, &g_IndexBuffer);


	{//���_�o�b�t�@�̒��g�𖄂߂�

		// ���_�o�b�t�@�ւ̃|�C���^���擾
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

		//1�c�ɂ�2�񃋁[�v����
		for (int y = 0; y < (tate + 1); y++)
		{
			//���ɂ͕K�v����+1�񃋁[�v����
			for (int x = 0; x < (yoko + 1); x++)
			{
				//�z��̃C���f�b�N�X���v�Z����
				int i = y * (yoko + 1) + x;

				// ���_���W�̐ݒ�
				pVtx[i].Position = D3DXVECTOR3(-(yoko / 2.0f) * sizeX + x * sizeX, 0.0f, (tate / 2.0f) * sizeZ - y * sizeZ);
				// UV�l�̐ݒ�
				pVtx[i].TexCoord = D3DXVECTOR2(x * 1.0f, y * 1.0f);

				// �@���̐ݒ�
				pVtx[i].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				// ���_�J���[�̐ݒ�
				pVtx[i].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
			}
		}
		GetDeviceContext()->Unmap(g_VertexBuffer, 0);
	}

	{//�C���f�b�N�X�o�b�t�@�̒��g�𖄂߂�

		// �C���f�b�N�X�o�b�t�@�̃|�C���^���擾
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(g_IndexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		unsigned short *pIdx = (unsigned short*)msr.pData;

		int idx = 0;

		for (int y = 0; y < tate; y++)
		{
			//1�s�ڂ̃|���S���̃C���f�b�N�X
			for (int x = 0; x < (yoko + 1); x++)
			{
				pIdx[idx] = (yoko + 1) + x + (yoko + 1) * y;
				idx++;
				pIdx[idx] = 0 + x + (yoko + 1) * y;
				idx++;
			}

			//�k�ރ|���S�����̃C���f�b�N�X
			if (y < (tate - 1))
			{
				pIdx[idx] = yoko + (yoko + 1) * y;
				idx++;
				pIdx[idx] = (yoko + 1) * 2 + (yoko + 1) * y;
				idx++;
			}
		}

 		GetDeviceContext()->Unmap(g_IndexBuffer, 0);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshField(void)
{
	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_IndexBuffer)
		g_IndexBuffer->Release();

	//���_�o�b�t�@�̉��
	if (g_VertexBuffer)
		g_VertexBuffer->Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshField(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshField(void)
{
	SetCullingMode(CULL_MODE_BACK);
	
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�ݒ�
	GetDeviceContext()->IASetIndexBuffer(g_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 5.1f);
	material.Emission = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TexNo));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Field.mtxWorld);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, g_Field.scl.x, g_Field.scl.y, g_Field.scl.z);
	D3DXMatrixMultiply(&g_Field.mtxWorld, &g_Field.mtxWorld, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Field.rot.y, g_Field.rot.x, g_Field.rot.z);
	D3DXMatrixMultiply(&g_Field.mtxWorld, &g_Field.mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, g_Field.pos.x, g_Field.pos.y, g_Field.pos.z);
	D3DXMatrixMultiply(&g_Field.mtxWorld, &g_Field.mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&g_Field.mtxWorld);


	SetCullingMode(CULL_MODE_NONE);
	SetBlendState(BLEND_MODE_ADD);

	

	// �|���S���̕`��
	GetDeviceContext()->DrawIndexed(numIndex, 0, 0);

	SetBlendState(BLEND_MODE_ALPHABLEND);
	SetCullingMode(CULL_MODE_BACK);

	
}


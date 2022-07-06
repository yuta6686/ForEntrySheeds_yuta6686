//=============================================================================
//
// �G�l�~�[�փ��b�N�I������G�t�F�N�g [Eff_RockOn.cpp]
// Author : Yanagisawa Yuta
//
//=============================================================================
#include "Eff_RockOn.h"

static ID3D11Buffer* g_VertexBuffer = NULL;	// ���_�o�b�t�@

void Eff_RockOn::Init()
{
	m_TexIndex = LoadTexture((char*)"data/TEXTURE/rockOn1.png");
	
	float width = 400.0f;
	float height = 400.0f;

	
	m_Obj.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Obj.scl = D3DXVECTOR3(width, height, 0.0f);
	m_Obj.use = false;
	
	
	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	g_VertexBuffer = NULL;

	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);

	// ���_�o�b�t�@�ɒl���Z�b�g����
	{
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;



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

	// �}�e���A��������
	ZeroMemory(&m_Material, sizeof(m_Material));
	m_Material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

}

void Eff_RockOn::Uninit()
{
	if (g_VertexBuffer != NULL)
	{// ���_�o�b�t�@�̉��
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

void Eff_RockOn::Update()
{

}

void Eff_RockOn::Draw()
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

	{
		if (m_Obj.use == false)return;

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_Obj.mtxWorld);

		CAMERA* cam = GetCamera();

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

		m_Obj.mtxWorld._11 = mtxView._11;
		m_Obj.mtxWorld._12 = mtxView._21;
		m_Obj.mtxWorld._13 = mtxView._31;
		m_Obj.mtxWorld._21 = mtxView._12;
		m_Obj.mtxWorld._22 = mtxView._22;
		m_Obj.mtxWorld._23 = mtxView._32;
		m_Obj.mtxWorld._31 = mtxView._13;
		m_Obj.mtxWorld._32 = mtxView._23;
		m_Obj.mtxWorld._33 = mtxView._33;
#endif


		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, m_Obj.pos.x,
			m_Obj.pos.y,
			m_Obj.pos.z);
		D3DXMatrixMultiply(&m_Obj.mtxWorld, &m_Obj.mtxWorld, &mtxTranslate);


		// ���[���h�}�g���b�N�X�̐ݒ�
		SetWorldMatrix(&m_Obj.mtxWorld);

		// �}�e���A���ݒ�
		SetMaterial(m_Material);

		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(m_TexIndex));

		// �|���S���̕`��
		GetDeviceContext()->Draw(4, 0);
	}
}

void Eff_RockOn::SetEffect()
{
	m_Obj.use = true;
	
}

void Eff_RockOn::SetEffect(D3DXVECTOR3 pos)
{
	m_Obj.use = true;
	m_Obj.pos = pos;	
}

void Eff_RockOn::SetEffect(bool IsStart)
{

}

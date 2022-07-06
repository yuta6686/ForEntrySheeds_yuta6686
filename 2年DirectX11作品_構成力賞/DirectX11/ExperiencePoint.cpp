//=============================================================================
//
// �o���l���� [ExperiencePoint.cpp]
// Author : Yanagisawa Yuta
//
// �����F�o���l�̃Q�[�W����
// 
//=============================================================================
#include "ExperiencePoint.h"
#include "CoordinateTransformation.h"
#include "fade.h"
#include "result.h"
#include "game.h"

void ExperiencePoint::NextStage()
{

	
	if (m_EXP >= m_exp_max) 
	{
		m_EXP = 0;

		if (*GetStageNum() >= A_STAGE_NUM_MAX) {
			SetIsClear(true);
			SceneTransition(SCENE_RESULT);
			*GetStageNum() = 0;
		}
		else 
		{
			AddStageNum(1);
			ChangeSelectSkillState(true);
			m_Obj.size.x = 0.0f;
		}
		
	}

}

void ExperiencePoint::Init()
{
	m_exp_max = EXP_MAX_DEFAULT;

	//	�Q�[�W�̕�
	{
		m_Obj.pos = D3DXVECTOR3(0.0f, 35.0f, 0.0f);
		m_Obj.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Obj.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Obj.vec = D3DXVECTOR3(10.0f, 0.0f, 0.0f);

		float scale = 2.5f;
		m_Obj.scl = D3DXVECTOR3(scale, scale, scale);
		m_Obj.size = D3DXVECTOR3(m_Exp_Gauge, 10.0f, 50.0f);
		m_Obj.idxShadow = 0;
		m_Obj.use = true;
	}

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	GetDevice()->CreateBuffer(&bd, NULL, &m_VertexBuffer);

	// ���_�o�b�t�@�ɒl���Z�b�g����
	{
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		vertex = (VERTEX_3D*)msr.pData;

		float width = m_Obj.size.x;
		float height = m_Obj.size.y;

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

		GetDeviceContext()->Unmap(m_VertexBuffer, 0);
	}

	//	MAX�̕�
	{
		m_Obj_EXPMAX.pos = D3DXVECTOR3(0.0f, 35.0f, 0.0f);
		m_Obj_EXPMAX.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Obj_EXPMAX.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Obj_EXPMAX.vec = D3DXVECTOR3(10.0f, 0.0f, 0.0f);

		float scale = 2.5f;
		m_Obj_EXPMAX.scl = D3DXVECTOR3(scale, scale, scale);
		m_Obj_EXPMAX.size = D3DXVECTOR3(EXP_GAUGE_XMAX, 10.0f, 50.0f);
		m_Obj_EXPMAX.idxShadow = 0;
		m_Obj_EXPMAX.use = true;
	}

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd2;
	ZeroMemory(&bd2, sizeof(bd2));
	bd2.Usage = D3D11_USAGE_DYNAMIC;
	bd2.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd2.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd2.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	GetDevice()->CreateBuffer(&bd2, NULL, &m_VertexBuffer_max);
	
	// ���_�o�b�t�@�ɒl���Z�b�g����
	{
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(m_VertexBuffer_max, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		vertex_max = (VERTEX_3D*)msr.pData;

		float width = m_Obj_EXPMAX.size.x;
		float height = m_Obj_EXPMAX.size.y;

		// ���_���W�̐ݒ�
		vertex_max[0].Position = D3DXVECTOR3(-width / 2.0f, 0.0f, 0.0f);
		vertex_max[1].Position = D3DXVECTOR3(-width / 2.0f, height, 0.0f);
		vertex_max[2].Position = D3DXVECTOR3(width / 2.0f, 0.0f, 0.0f);
		vertex_max[3].Position = D3DXVECTOR3(width / 2.0f, height, 0.0f);

		// ���_�J���[�̐ݒ�
		vertex_max[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		vertex_max[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		vertex_max[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		vertex_max[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);


		// �e�N�X�`�����W�̐ݒ�
		vertex_max[0].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
		vertex_max[1].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
		vertex_max[2].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
		vertex_max[3].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

		GetDeviceContext()->Unmap(m_VertexBuffer_max, 0);
	}

	m_texIndex = LoadTexture(m_pTexName);

	// �}�e���A��������
	ZeroMemory(&m_Material, sizeof(m_Material));
	m_Material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_Alpha);

	// �}�e���A��������
	ZeroMemory(&m_Material2, sizeof(m_Material2));
	m_Material2.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_Alpha);
}

void ExperiencePoint::Uninit()
{
	UnloadModel(&m_Model);

	if (m_VertexBuffer != NULL)
	{// ���_�o�b�t�@�̉��
		m_VertexBuffer->Release();
		m_VertexBuffer = NULL;
	}

	
}

void ExperiencePoint::Update()
{
#ifdef _DEBUG	// �f�o�b�O�ł̎�����Angle��\������

	sprintf(&GetDebugStr()[strlen(GetDebugStr())], "�o���l�F%d", m_EXP);

	SetWindowText(GethWnd()[0], GetDebugStr());
#endif

	SetExpMax();

	float width = m_Obj.size.x;
	float height = m_Obj.size.y;

	vertex[0].Position = D3DXVECTOR3(-width / 2.0f, 0.0f, 0.0f);
	vertex[1].Position = D3DXVECTOR3(-width / 2.0f, height, 0.0f);
	vertex[2].Position = D3DXVECTOR3(width / 2.0f, 0.0f, 0.0f);
	vertex[3].Position = D3DXVECTOR3(width / 2.0f, height, 0.0f);

	m_Obj_EXPMAX.pos = m_Obj.pos;
}

void ExperiencePoint::Draw()
{
	//	�r���{�[�h�ŕ\��
	{
		//	�A���t�@�e�X�g��L����
		SetAlphaTestEnable(true);

		// ���C�e�B���O�𖳌�
		SetLightEnable(false);

		//SetBlendState(BLEND_MODE_ADD);
		SetBlendState(BLEND_MODE_ALPHABLEND);


		D3DXMATRIX mtxView, mtxScale, mtxTranslate;

		// ���_�o�b�t�@�ݒ�
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

		// �v���~�e�B�u�g�|���W�ݒ�
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		if (m_Obj.use) {
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&m_Obj.mtxWorld);

			CAMERA* cam = GetCamera();

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

			//// �X�P�[���𔽉f
			//D3DXMatrixScaling(&mtxScale, m_Obj.size.x,m_Obj.size.y,m_Obj.size.z);

			////��1���� ��          ��2����      ��    ��3����
			//D3DXMatrixMultiply(&m_Obj.mtxWorld, &m_Obj.mtxWorld, &mtxScale);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, m_Obj.pos.x,m_Obj.pos.y,m_Obj.pos.z);

			D3DXMatrixMultiply(&m_Obj.mtxWorld, &m_Obj.mtxWorld, &mtxTranslate);

			SetWorldMatrix(&m_Obj.mtxWorld);

			SetMaterial(m_Material);

			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(m_texIndex));

			GetDeviceContext()->Draw(4, 0);
		}


		GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer_max, &stride, &offset);

		// �v���~�e�B�u�g�|���W�ݒ�
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		if (m_Obj_EXPMAX.use) {
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&m_Obj_EXPMAX.mtxWorld);

			CAMERA* cam = GetCamera();

			// �r���[�}�g���b�N�X���擾
			D3DXMATRIX mtxView = cam->mtxView;

			m_Obj_EXPMAX.mtxWorld._11 = mtxView._11;
			m_Obj_EXPMAX.mtxWorld._12 = mtxView._21;
			m_Obj_EXPMAX.mtxWorld._13 = mtxView._31;
			m_Obj_EXPMAX.mtxWorld._21 = mtxView._12;
			m_Obj_EXPMAX.mtxWorld._22 = mtxView._22;
			m_Obj_EXPMAX.mtxWorld._23 = mtxView._32;
			m_Obj_EXPMAX.mtxWorld._31 = mtxView._13;
			m_Obj_EXPMAX.mtxWorld._32 = mtxView._23;
			m_Obj_EXPMAX.mtxWorld._33 = mtxView._33;

			//// �X�P�[���𔽉f
			//D3DXMatrixScaling(&mtxScale, m_Obj.size.x,m_Obj.size.y,m_Obj.size.z);

			////��1���� ��          ��2����      ��    ��3����
			//D3DXMatrixMultiply(&m_Obj.mtxWorld, &m_Obj.mtxWorld, &mtxScale);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, m_Obj_EXPMAX.pos.x, m_Obj_EXPMAX.pos.y, m_Obj_EXPMAX.pos.z);

			D3DXMatrixMultiply(&m_Obj_EXPMAX.mtxWorld, &m_Obj_EXPMAX.mtxWorld, &mtxTranslate);

			SetWorldMatrix(&m_Obj_EXPMAX.mtxWorld);

			SetMaterial(m_Material2);

			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(m_texIndex));

			GetDeviceContext()->Draw(4, 0);
		}
	}

	SetBlendState(BLEND_MODE_ALPHABLEND);

	// ���C�e�B���O��L����
	SetLightEnable(true);

	// ���e�X�g�𖳌���
	SetAlphaTestEnable(false);
}

//=============================================================================
//
// �����_�����O���� [renderer.cpp]
// Author : Yanagisawa Yuta
//
//=============================================================================
#include "renderer.h"



//*********************************************************
// �\����
//*********************************************************
// �}�e���A���p�萔�o�b�t�@�\����
struct MATERIAL_CBUFFER
{
	D3DXCOLOR	Ambient;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Specular;
	D3DXCOLOR	Emission;
	float		Shininess;
	int			noTexSampling;
	float		Dummy[2];				// 16byte���E�p
};

// ���C�g�p�t���O�\����
struct LIGHTFLAGS
{
	int			Type;		//���C�g�^�C�v�ienum LIGHT_TYPE�j
	int         OnOff;		//���C�g�̃I��or�I�t�X�C�b�`
	int			Dummy[2];
};

// ���C�g�p�萔�o�b�t�@�\����
struct LIGHT_CBUFFER
{
	D3DXVECTOR4	Direction[LIGHT_MAX];	// ���C�g�̕���
	D3DXVECTOR4	Position[LIGHT_MAX];	// ���C�g�̈ʒu
	D3DXCOLOR	Diffuse[LIGHT_MAX];		// �g�U���̐F
	D3DXCOLOR	Ambient[LIGHT_MAX];		// �����̐F
	D3DXVECTOR4	Attenuation[LIGHT_MAX];	// ������
	LIGHTFLAGS	Flags[LIGHT_MAX];		// ���C�g���
	int			Enable;					// ���C�e�B���O�L���E�����t���O
	int			Dummy[3];				// 16byte���E�p
};


//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
D3D_FEATURE_LEVEL       g_FeatureLevel = D3D_FEATURE_LEVEL_11_0;

ID3D11Device*           g_D3DDevice = NULL;
ID3D11DeviceContext*    g_ImmediateContext = NULL;
IDXGISwapChain*         g_SwapChain = NULL;
ID3D11RenderTargetView* g_RenderTargetView = NULL;
ID3D11DepthStencilView* g_DepthStencilView = NULL;

ID3D11VertexShader*     g_VertexShader = NULL;
ID3D11PixelShader*      g_PixelShader = NULL;
ID3D11InputLayout*      g_VertexLayout = NULL;
ID3D11Buffer*			g_WorldBuffer = NULL;
ID3D11Buffer*			g_ViewBuffer = NULL;
ID3D11Buffer*			g_ProjectionBuffer = NULL;
ID3D11Buffer*			g_MaterialBuffer = NULL;
ID3D11Buffer*			g_LightBuffer = NULL;

ID3D11DepthStencilState* g_DepthStateEnable;
ID3D11DepthStencilState* g_DepthStateDisable;

ID3D11BlendState*		g_BlendStateNone;
ID3D11BlendState*		g_BlendStateAlphaBlend;
ID3D11BlendState*		g_BlendStateAdd;
ID3D11BlendState*		g_BlendStateSubtract;
BLEND_MODE				g_BlendStateParam;

ID3D11RasterizerState*	g_RasterStateCullOff;
ID3D11RasterizerState*	g_RasterStateCullCW;
ID3D11RasterizerState*	g_RasterStateCullCCW;

static D3DXCOLOR		g_BorderColor;

static MATERIAL_CBUFFER	g_Material;
static LIGHT_CBUFFER	g_Light;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
static void SetLightBuffer(void);


ID3D11Device* GetDevice( void )
{
	return g_D3DDevice;
}


ID3D11DeviceContext* GetDeviceContext( void )
{
	return g_ImmediateContext;
}


void SetDepthEnable( bool Enable )
{
	if( Enable )
		g_ImmediateContext->OMSetDepthStencilState( g_DepthStateEnable, NULL );
	else
		g_ImmediateContext->OMSetDepthStencilState( g_DepthStateDisable, NULL );

}

void SetBlendState(BLEND_MODE bm)
{
	g_BlendStateParam = bm;

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	switch (g_BlendStateParam)
	{
	case BLEND_MODE_NONE:
		g_ImmediateContext->OMSetBlendState(g_BlendStateNone, blendFactor, 0xffffffff);
		break;
	case BLEND_MODE_ALPHABLEND:
		g_ImmediateContext->OMSetBlendState(g_BlendStateAlphaBlend, blendFactor, 0xffffffff);
		break;
	case BLEND_MODE_ADD:
		g_ImmediateContext->OMSetBlendState(g_BlendStateAdd, blendFactor, 0xffffffff);
		break;
	case BLEND_MODE_SUBTRACT:
		g_ImmediateContext->OMSetBlendState(g_BlendStateSubtract, blendFactor, 0xffffffff);
		break;
	}
}

void SetCullingMode(CULL_MODE cm)
{
	switch (cm)
	{
	case CULL_MODE_NONE:
		g_ImmediateContext->RSSetState(g_RasterStateCullOff);
		break;
	case CULL_MODE_FRONT:
		g_ImmediateContext->RSSetState(g_RasterStateCullCW);
		break;
	case CULL_MODE_BACK:
		g_ImmediateContext->RSSetState(g_RasterStateCullCCW);
		break;
	}
}

void SetSamplerState(FILTER_MODE fm, ADDRESS_MODE am)
{
	// �T���v���[�X�e�[�g�ݒ�
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(samplerDesc));

	switch (fm)
	{
	case FILTER_MODE_POINT:
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		break;
	case FILTER_MODE_LINEAR:
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		break;
	case FILTER_MODE_ANISOTROPIC:
		samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		break;
	}

	//�e�N�X�`���̃A�h���b�V���O���[�h�̐ݒ�		
	switch (am)
	{
	case ADDRESS_MODE_WRAP:
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		break;
	case ADDRESS_MODE_MIRROR:
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
		break;
	case ADDRESS_MODE_CLAMP:
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		break;
	case ADDRESS_MODE_BORDER:
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
		break;
	}

	samplerDesc.BorderColor[0] = g_BorderColor.r;
	samplerDesc.BorderColor[1] = g_BorderColor.g;
	samplerDesc.BorderColor[2] = g_BorderColor.b;
	samplerDesc.BorderColor[3] = g_BorderColor.a;

	samplerDesc.MipLODBias = 0;
	samplerDesc.MaxAnisotropy = 16;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	ID3D11SamplerState* samplerState = NULL;
	g_D3DDevice->CreateSamplerState(&samplerDesc, &samplerState);

	g_ImmediateContext->PSSetSamplers(0, 1, &samplerState);

	samplerState->Release();
	samplerState = NULL;
}

void SetSamplerBorderColor(D3DXCOLOR col)
{
	g_BorderColor = col;
}

void SetAlphaTestEnable(BOOL flag)
{
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));

	if(flag)
		blendDesc.AlphaToCoverageEnable = TRUE;
	else
		blendDesc.AlphaToCoverageEnable = FALSE;

	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;

	switch(g_BlendStateParam)
	{
	case BLEND_MODE_NONE:
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		break;
	case BLEND_MODE_ALPHABLEND:
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		break;
	case BLEND_MODE_ADD:
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		break;
	case BLEND_MODE_SUBTRACT:
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		break;
	}

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	ID3D11BlendState* blendState = NULL;
	g_D3DDevice->CreateBlendState(&blendDesc, &blendState);
	g_ImmediateContext->OMSetBlendState(blendState, blendFactor, 0xffffffff);

	if (blendState != NULL)
		blendState->Release();
}


void SetWorldViewProjection2D( void )
{
	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);
	D3DXMatrixTranspose(&world, &world);
	GetDeviceContext()->UpdateSubresource(g_WorldBuffer, 0, NULL, &world, 0, 0);

	D3DXMATRIX view;
	D3DXMatrixIdentity(&view);
	D3DXMatrixTranspose(&view, &view);
	GetDeviceContext()->UpdateSubresource(g_ViewBuffer, 0, NULL, &view, 0, 0);

	D3DXMATRIX worldViewProjection;
	D3DXMatrixOrthoOffCenterLH(&worldViewProjection, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f);
	D3DXMatrixTranspose(&worldViewProjection, &worldViewProjection);
	GetDeviceContext()->UpdateSubresource( g_ProjectionBuffer, 0, NULL, &worldViewProjection, 0, 0 );
}


void SetWorldMatrix( D3DXMATRIX *WorldMatrix )
{
	D3DXMATRIX world;
	world = *WorldMatrix;
	D3DXMatrixTranspose(&world, &world);

	GetDeviceContext()->UpdateSubresource( g_WorldBuffer, 0, NULL, &world, 0, 0 );
}

void SetViewMatrix( D3DXMATRIX *ViewMatrix )
{
	D3DXMATRIX view;
	view = *ViewMatrix;
	D3DXMatrixTranspose(&view, &view);

	GetDeviceContext()->UpdateSubresource(g_ViewBuffer, 0, NULL, &view, 0, 0);
}

void SetProjectionMatrix( D3DXMATRIX *ProjectionMatrix )
{
	D3DXMATRIX projection;
	projection = *ProjectionMatrix;
	D3DXMatrixTranspose(&projection, &projection);

	GetDeviceContext()->UpdateSubresource(g_ProjectionBuffer, 0, NULL, &projection, 0, 0);
}


void SetMaterial( MATERIAL Material )
{
	g_Material.Diffuse = Material.Diffuse;
	g_Material.Ambient = Material.Ambient;
	g_Material.Specular = Material.Specular;
	g_Material.Emission = Material.Emission;
	g_Material.Shininess = Material.Shininess;
	g_Material.noTexSampling = Material.noTexSampling;

	GetDeviceContext()->UpdateSubresource(g_MaterialBuffer, 0, NULL, &g_Material, 0, 0);
}

void SetLightBuffer(void)
{
	GetDeviceContext()->UpdateSubresource(g_LightBuffer, 0, NULL, &g_Light, 0, 0);
}

void SetLightEnable(BOOL flag)
{
	// �t���O���X�V����
	g_Light.Enable = flag;

	SetLightBuffer();
}

void SetLight(int index, LIGHT *pLight)
{
	g_Light.Position[index] = D3DXVECTOR4(pLight->Position.x, pLight->Position.y, pLight->Position.z, 0.0f);
	g_Light.Direction[index] = D3DXVECTOR4(pLight->Direction.x, pLight->Direction.y, pLight->Direction.z, 0.0f);
	g_Light.Diffuse[index] = pLight->Diffuse;
	g_Light.Ambient[index] = pLight->Ambient;
	g_Light.Flags[index].Type = pLight->Type;
	g_Light.Flags[index].OnOff = pLight->Enable;
	g_Light.Attenuation[index].x = pLight->Attenuation;

	SetLightBuffer();
}


//=============================================================================
// ����������
//=============================================================================
HRESULT InitRenderer(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	HRESULT hr = S_OK;

	// �f�o�C�X�A�X���b�v�`�F�[���A�R���e�L�X�g����
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof( sd ) );
	sd.BufferCount = 1;
	sd.BufferDesc.Width = SCREEN_WIDTH;
	sd.BufferDesc.Height = SCREEN_HEIGHT;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	hr = D3D11CreateDeviceAndSwapChain( NULL,
										D3D_DRIVER_TYPE_HARDWARE,
										NULL,
										0,
										NULL,
										0,
										D3D11_SDK_VERSION,
										&sd,
										&g_SwapChain,
										&g_D3DDevice,
										&g_FeatureLevel,
										&g_ImmediateContext );
	if( FAILED( hr ) )
		return hr;


	// �����_�[�^�[�Q�b�g�r���[�����A�ݒ�
	ID3D11Texture2D* pBackBuffer = NULL;
	g_SwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
	g_D3DDevice->CreateRenderTargetView( pBackBuffer, NULL, &g_RenderTargetView );
	pBackBuffer->Release();



	//�X�e���V���p�e�N�X�`���[�쐬
	ID3D11Texture2D* depthTexture = NULL;
	D3D11_TEXTURE2D_DESC td;
	ZeroMemory( &td, sizeof(td) );
	td.Width			= sd.BufferDesc.Width;
	td.Height			= sd.BufferDesc.Height;
	td.MipLevels		= 1;
	td.ArraySize		= 1;
	td.Format			= DXGI_FORMAT_D24_UNORM_S8_UINT;
	td.SampleDesc		= sd.SampleDesc;
	td.Usage			= D3D11_USAGE_DEFAULT;
	td.BindFlags		= D3D11_BIND_DEPTH_STENCIL;
    td.CPUAccessFlags	= 0;
    td.MiscFlags		= 0;
	g_D3DDevice->CreateTexture2D( &td, NULL, &depthTexture );

	//�X�e���V���^�[�Q�b�g�쐬
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory( &dsvd, sizeof(dsvd) );
	dsvd.Format			= td.Format;
	dsvd.ViewDimension	= D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Flags			= 0;
	g_D3DDevice->CreateDepthStencilView( depthTexture, &dsvd, &g_DepthStencilView );

	g_ImmediateContext->OMSetRenderTargets( 1, &g_RenderTargetView, g_DepthStencilView );


	// �r���[�|�[�g�ݒ�
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)SCREEN_WIDTH;
	vp.Height = (FLOAT)SCREEN_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_ImmediateContext->RSSetViewports( 1, &vp );



	// ���X�^���C�U�X�e�[�g�ݒ�
	D3D11_RASTERIZER_DESC rd; 
	ZeroMemory( &rd, sizeof( rd ) );
	rd.FillMode = D3D11_FILL_SOLID; 
	rd.CullMode = D3D11_CULL_NONE; 
	rd.DepthClipEnable = TRUE; 
	rd.MultisampleEnable = FALSE; 
	g_D3DDevice->CreateRasterizerState( &rd, &g_RasterStateCullOff );

	rd.CullMode = D3D11_CULL_FRONT;
	g_D3DDevice->CreateRasterizerState(&rd, &g_RasterStateCullCW);

	rd.CullMode = D3D11_CULL_BACK;
	g_D3DDevice->CreateRasterizerState(&rd, &g_RasterStateCullCCW);

	// �J�����O���[�h�ݒ�iCCW�j
	SetCullingMode(CULL_MODE_BACK);




	// �u�����h�X�e�[�g�ݒ�
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory( &blendDesc, sizeof( blendDesc ) );
	blendDesc.AlphaToCoverageEnable = FALSE;
	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	float blendFactor[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	g_D3DDevice->CreateBlendState( &blendDesc, &g_BlendStateAlphaBlend );

	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	g_D3DDevice->CreateBlendState(&blendDesc, &g_BlendStateNone);

	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	g_D3DDevice->CreateBlendState(&blendDesc, &g_BlendStateAdd);

	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	g_D3DDevice->CreateBlendState(&blendDesc, &g_BlendStateSubtract);

	// �A���t�@�u�����h�ݒ�
	SetBlendState(BLEND_MODE_ALPHABLEND);


	// �[�x�X�e���V���X�e�[�g�ݒ�
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory( &depthStencilDesc, sizeof( depthStencilDesc ) );
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask	= D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilDesc.StencilEnable = FALSE;

	g_D3DDevice->CreateDepthStencilState( &depthStencilDesc, &g_DepthStateEnable );//�[�x�L���X�e�[�g

	//depthStencilDesc.DepthEnable = FALSE;
	depthStencilDesc.DepthWriteMask	= D3D11_DEPTH_WRITE_MASK_ZERO;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;
	g_D3DDevice->CreateDepthStencilState( &depthStencilDesc, &g_DepthStateDisable );//�[�x�����X�e�[�g

	g_ImmediateContext->OMSetDepthStencilState( g_DepthStateEnable, NULL );




	// �T���v���[�X�e�[�g�ݒ�
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory( &samplerDesc, sizeof( samplerDesc ) );
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	g_BorderColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	samplerDesc.BorderColor[0] = g_BorderColor.r;//BORDER�̐F���w��
	samplerDesc.BorderColor[1] = g_BorderColor.g;
	samplerDesc.BorderColor[2] = g_BorderColor.b;
	samplerDesc.BorderColor[3] = g_BorderColor.a;

	samplerDesc.MipLODBias = 0;
	samplerDesc.MaxAnisotropy = 16;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	ID3D11SamplerState* samplerState = NULL;
	g_D3DDevice->CreateSamplerState( &samplerDesc, &samplerState );

	g_ImmediateContext->PSSetSamplers( 0, 1, &samplerState );
	samplerState->Release();


	// ���_�V�F�[�_�R���p�C���E����
	ID3DBlob* pErrorBlob;
	ID3DBlob* pVSBlob = NULL;
//	hr = D3DX11CompileFromFile( "shader.hlsl", NULL, NULL, "VertexShaderPolygon", "vs_4_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, NULL, &pVSBlob, &pErrorBlob, NULL );
	hr = D3DX11CompileFromFile("shader.hlsl", NULL, NULL, "VertexShaderPolygon", "vs_4_0", D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION, 0, NULL, &pVSBlob, &pErrorBlob, NULL);
	if( FAILED(hr) )
	{
		MessageBox( NULL , (char*)pErrorBlob->GetBufferPointer(), "VS", MB_OK | MB_ICONERROR );
	}

	g_D3DDevice->CreateVertexShader( pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &g_VertexShader );

	// ���̓��C�A�E�g����
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,			0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE( layout );

	g_D3DDevice->CreateInputLayout( layout,
		numElements,
		pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(),
		&g_VertexLayout );

	pVSBlob->Release();


	// �s�N�Z���V�F�[�_�R���p�C���E����
	ID3DBlob* pPSBlob = NULL;
//	hr = D3DX11CompileFromFile( "shader.hlsl", NULL, NULL, "PixelShaderPolygon", "ps_4_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, NULL, &pPSBlob, &pErrorBlob, NULL );
	hr = D3DX11CompileFromFile("shader.hlsl", NULL, NULL, "PixelShaderPolygon", "ps_4_0", D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION, 0, NULL, &pPSBlob, &pErrorBlob, NULL);
	if( FAILED(hr) )
	{
		MessageBox( NULL , (char*)pErrorBlob->GetBufferPointer(), "PS", MB_OK | MB_ICONERROR );
	}

	g_D3DDevice->CreatePixelShader( pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &g_PixelShader );
	
	pPSBlob->Release();


	// �萔�o�b�t�@����
	D3D11_BUFFER_DESC hBufferDesc;
	hBufferDesc.ByteWidth = sizeof(D3DXMATRIX);
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;
	hBufferDesc.MiscFlags = 0;
	hBufferDesc.StructureByteStride = sizeof(float);

	//���[���h�}�g���N�X
	g_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &g_WorldBuffer);
	g_ImmediateContext->VSSetConstantBuffers(0, 1, &g_WorldBuffer);
	g_ImmediateContext->PSSetConstantBuffers(0, 1, &g_WorldBuffer);

	//�r���[�}�g���N�X
	g_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &g_ViewBuffer);
	g_ImmediateContext->VSSetConstantBuffers(1, 1, &g_ViewBuffer);
	g_ImmediateContext->PSSetConstantBuffers(1, 1, &g_ViewBuffer);

	//�v���W�F�N�V�����}�g���N�X
	g_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &g_ProjectionBuffer);
	g_ImmediateContext->VSSetConstantBuffers(2, 1, &g_ProjectionBuffer);
	g_ImmediateContext->PSSetConstantBuffers(2, 1, &g_ProjectionBuffer);

	//�}�e���A�����
	hBufferDesc.ByteWidth = sizeof(MATERIAL_CBUFFER);
	g_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &g_MaterialBuffer);
	g_ImmediateContext->VSSetConstantBuffers(3, 1, &g_MaterialBuffer);
	g_ImmediateContext->PSSetConstantBuffers(3, 1, &g_MaterialBuffer);

	//���C�g���
	hBufferDesc.ByteWidth = sizeof(LIGHT_CBUFFER);
	g_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &g_LightBuffer);
	g_ImmediateContext->VSSetConstantBuffers(4, 1, &g_LightBuffer);
	g_ImmediateContext->PSSetConstantBuffers(4, 1, &g_LightBuffer);


	// ���̓��C�A�E�g�ݒ�
	g_ImmediateContext->IASetInputLayout( g_VertexLayout );

	// �V�F�[�_�ݒ�
	g_ImmediateContext->VSSetShader( g_VertexShader, NULL, 0 );
	g_ImmediateContext->PSSetShader( g_PixelShader, NULL, 0 );


	//���C�g������
	ZeroMemory(&g_Light, sizeof(LIGHT_CBUFFER));
	g_Light.Direction[0] = D3DXVECTOR4(0.0f, -1.0f, 0.0f, 0.0f);
	g_Light.Diffuse[0] = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);
	g_Light.Ambient[0] = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	SetLightBuffer();


	//�}�e���A��������
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);


	return S_OK;
}


//=============================================================================
// �I������
//=============================================================================
void UninitRenderer(void)
{
	// �I�u�W�F�N�g���
	if (g_DepthStateEnable)		g_DepthStateEnable->Release();
	if (g_DepthStateDisable)	g_DepthStateDisable->Release();

	if (g_BlendStateNone)		g_BlendStateNone->Release();
	if (g_BlendStateAlphaBlend) g_BlendStateAlphaBlend->Release();
	if (g_BlendStateAdd)		g_BlendStateAdd->Release();
	if (g_BlendStateSubtract)	g_BlendStateSubtract->Release();

	if (g_RasterStateCullOff)	g_RasterStateCullOff->Release();
	if (g_RasterStateCullCW)	g_RasterStateCullCW->Release();
	if (g_RasterStateCullCCW)	g_RasterStateCullCCW->Release();

	// �I�u�W�F�N�g���
	if (g_WorldBuffer)			g_WorldBuffer->Release();
	if (g_ViewBuffer)			g_ViewBuffer->Release();
	if (g_ProjectionBuffer)		g_ProjectionBuffer->Release();
	if( g_MaterialBuffer )		g_MaterialBuffer->Release();
	if( g_VertexLayout )		g_VertexLayout->Release();
	if( g_VertexShader )		g_VertexShader->Release();
	if( g_PixelShader )			g_PixelShader->Release();

	if( g_ImmediateContext )	g_ImmediateContext->ClearState();
	if( g_RenderTargetView )	g_RenderTargetView->Release();
	if( g_SwapChain )			g_SwapChain->Release();
	if( g_ImmediateContext )	g_ImmediateContext->Release();
	if( g_D3DDevice )			g_D3DDevice->Release();

}



//=============================================================================
// �o�b�N�o�b�t�@�N���A
//=============================================================================
void Clear(void)
{
	// �o�b�N�o�b�t�@�N���A
	float ClearColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
	g_ImmediateContext->ClearRenderTargetView( g_RenderTargetView, ClearColor );
	g_ImmediateContext->ClearDepthStencilView( g_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}


//=============================================================================
// �v���[���g
//=============================================================================
void Present(void)
{
	g_SwapChain->Present( 0, 0 );
}


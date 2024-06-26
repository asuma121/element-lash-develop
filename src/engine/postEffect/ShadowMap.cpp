/**
 * @file ShadowMap.cpp
 * @brief ポストエフェクト シャドウマップ
 * @author Asuma Syota
 * @date 2023/4
 */


#include "ShadowMap.h"
#include "string.h"
#include "WinApp.h"
#include "mathOriginal.h"
#include <d3dcompiler.h>
#include <DirectXTex.h>

#pragma comment(lib, "d3dcompiler.lib")

using namespace Microsoft::WRL;

ID3D12Device* ShadowMap::device = nullptr;
SrvManager* ShadowMap::srvManager = nullptr;
ComPtr<ID3D12RootSignature>ShadowMap::rootsignature0;
ComPtr<ID3D12PipelineState>ShadowMap::pipelinestate0;
const float ShadowMap::clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

ShadowMap::~ShadowMap()
{
}

void ShadowMap::Initialize()
{
	HRESULT result;

	SetScale({ width,height });
	SetPosition({ 0.0f, 0.0 });

	//頂点データ
	vertices[0] = { {    0.0f, scale.y, 0.0f },{ 0.0f,1.0f } };	//左下
	vertices[1] = { {    0.0f,    0.0f, 0.0f },{ 0.0f,0.0f } };	//左上
	vertices[2] = { { scale.x, scale.y, 0.0f },{ 1.0f,1.0f } };	//右下
	vertices[3] = { { scale.x, scale.y, 0.0f },{ 1.0f,1.0f } };	//右下
	vertices[4] = { {    0.0f,    0.0f, 0.0f },{ 0.0f,0.0f } };	//左上
	vertices[5] = { { scale.x,    0.0f, 0.0f },{ 1.0f,0.0f } };	//右上

	//頂点データのサイズ
	UINT sizeVB = static_cast<UINT>(sizeof(Vertex) * _countof(vertices));

	//頂点バッファの設定
	D3D12_HEAP_PROPERTIES heapProp{};	//ヒープ設定
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;	//GPUへの転送用
	//リソース設定
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeVB;
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//頂点バッファの生成
	ComPtr<ID3D12Resource>vertBuff;
	result = device->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff)
	);
	assert(SUCCEEDED(result));

	//GPU上のバッファに対応した仮想メモリを取得
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));
	//全頂点に対して
	for (int i = 0; i < _countof(vertices); i++)
	{
		vertMap[i] = vertices[i];	//座標をコピー
	}
	//繋がりを解除
	vertBuff->Unmap(0, nullptr);

	//頂点バッファビューの作成
	//GPU仮想アドレス
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	//頂点バッファのサイズ
	vbView.SizeInBytes = sizeVB;
	//頂点1つ分のデータサイズ
	vbView.StrideInBytes = sizeof(Vertex);

	//定数バッファの設定
	//ヒープ設定
	D3D12_HEAP_PROPERTIES v0{};
	v0.Type = D3D12_HEAP_TYPE_UPLOAD;
	//リソース設定
	D3D12_RESOURCE_DESC v1{};
	v1.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	v1.Width = (sizeof(ConstBuffMaterial) + 0xff) & ~0xff;
	v1.Height = 1;
	v1.DepthOrArraySize = 1;
	v1.MipLevels = 1;
	v1.SampleDesc.Count = 1;
	v1.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	//定数バッファの生成
	result = device->CreateCommittedResource(
		&v0,
		D3D12_HEAP_FLAG_NONE,
		&v1,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffMaterial)
	);
	assert(SUCCEEDED(result));

	//定数バッファマッピング
	result = constBuffMaterial->Map(0, nullptr, (void**)&constMapMaterial);
	assert(SUCCEEDED(result));

	//行列用定数バッファ設定
	D3D12_HEAP_PROPERTIES v2{};
	v2.Type = D3D12_HEAP_TYPE_UPLOAD;
	//リソース設定
	D3D12_RESOURCE_DESC v3{};
	v3.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	v3.Width = (sizeof(ConstBuffTransform) + 0xff) & ~0xff;
	v3.Height = 1;
	v3.DepthOrArraySize = 1;
	v3.MipLevels = 1;
	v3.SampleDesc.Count = 1;
	v3.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	//定数バッファの生成
	result = device->CreateCommittedResource(
		&v2,
		D3D12_HEAP_FLAG_NONE,
		&v3,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffTransform)
	);

	//定数バッファマッピング
	result = constBuffTransform->Map(0, nullptr, (void**)&constMapTransform);
	assert(SUCCEEDED(result));
	constMapTransform->mat = DirectX::XMMatrixIdentity();

	//リソース設定
	D3D12_RESOURCE_DESC textureResourceDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
		(UINT64)width,
		(UINT64)height,
		1, 0, 1, 0,
		D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET
	);

	CD3DX12_HEAP_PROPERTIES a0 = CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0);
	CD3DX12_CLEAR_VALUE a1 = CD3DX12_CLEAR_VALUE(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, clearColor);
	//テクスチャバッファの生成
	result = device->CreateCommittedResource(
		&a0,
		D3D12_HEAP_FLAG_NONE,
		&textureResourceDesc,
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
		&a1,
		IID_PPV_ARGS(&textureBuff)
	);
	assert(SUCCEEDED(result));

	//テクスチャ生成用設定
	const UINT pixelCount = (UINT)width * (UINT)height;
	const UINT rowPitch = sizeof(UINT) * (UINT)width;
	const UINT depthPitch = rowPitch * (UINT)height;
	//画像イメージ
	UINT* img = new UINT[pixelCount];
	for (int i = 0; i < (int)pixelCount; i++)
	{
		img[i] = 0xff0000ff;
	}

	//テクスチャバッファにデータ送信
	result = textureBuff->WriteToSubresource(
		0,
		nullptr,
		img,
		rowPitch,
		depthPitch
	);
	assert(SUCCEEDED(result));
	delete[] img;

	//シェーダリソースビューの作成
	srvManager->CreateSRVForShadowMap(textureBuff.Get(), DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, 1);


	//RTV用デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC rtvDesc{};
	rtvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvDesc.NumDescriptors = 2;
	//RTV用デスクリプタヒープを生成
	result = device->CreateDescriptorHeap(&rtvDesc, IID_PPV_ARGS(&descHeapRTV));
	assert(SUCCEEDED(result));


	//レンダーターゲットビューの設定
	D3D12_RENDER_TARGET_VIEW_DESC renderDesc{};
	renderDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	renderDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
	//デスクリプタヒープにRTV作成
	device->CreateRenderTargetView(
		textureBuff.Get(),
		&renderDesc,
		descHeapRTV->GetCPUDescriptorHandleForHeapStart()
	);


	//深度バッファの作成
	D3D12_RESOURCE_DESC depthResDesc = {};
	depthResDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthResDesc.Width = (UINT64)width;
	depthResDesc.Height = (UINT)height;
	depthResDesc.DepthOrArraySize = 1;
	depthResDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthResDesc.SampleDesc.Count = 1;
	depthResDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	//深度値用ヒープ設定
	D3D12_HEAP_PROPERTIES depthHeapProp = {};
	depthHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
	depthHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	depthHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

	//クリアバッファビュー
	D3D12_CLEAR_VALUE depthClearValue = {};
	depthClearValue.DepthStencil.Depth = 1.0f;
	depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;

	result = device->CreateCommittedResource(
		&depthHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&depthResDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&depthClearValue,
		IID_PPV_ARGS(&depthBuff)
	);
	assert(SUCCEEDED(result));
	//light目線
	//バッファ作成
	result = device->CreateCommittedResource(
		&depthHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&depthResDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&depthClearValue,
		IID_PPV_ARGS(&lightDepthBuff)
	);
	assert(SUCCEEDED(result));

	//でスクリプタ用設定
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
	dsvHeapDesc.NumDescriptors = 2;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	result = device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&descHeapDSV));

	//深度ビュー作成
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Flags = D3D12_DSV_FLAG_NONE;
	D3D12_CPU_DESCRIPTOR_HANDLE handle = descHeapDSV->GetCPUDescriptorHandleForHeapStart();
	device->CreateDepthStencilView(
		depthBuff.Get(),
		&dsvDesc,
		handle
	);
	assert(SUCCEEDED(result));
	handle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	//深度ステンシルビュー作成
	device->CreateDepthStencilView(
		lightDepthBuff.Get(),
		&dsvDesc,
		handle
	);
	assert(SUCCEEDED(result));

	//深度のシェーダリソースビューの作成
	srvManager->CreateDepthSRVForShadowMap(depthBuff.Get(), DXGI_FORMAT_R32_FLOAT, 1);

	//ライト深度のシェーダリソースビューの作成
	srvManager->CreateDepthSRVForShadowMap(lightDepthBuff.Get(), DXGI_FORMAT_R32_FLOAT, 1);
}


void ShadowMap::Update()
{
	std::copy(std::begin(vertices), std::end(vertices), vertMap);

	//マテリアル
	constMapMaterial->color = color;
	constMapMaterial->window.x = width;
	constMapMaterial->window.y = height;
	constMapMaterial->resolution = resolution;
	constMapMaterial->lightvp = lightVP;

	//変形行列
	//ワールド変換行列
	XMMATRIX matWorld;
	matWorld = DirectX::XMMatrixIdentity();
	//回転
	XMMATRIX matRot;
	matRot = DirectX::XMMatrixIdentity();
	matRot *= DirectX::XMMatrixRotationZ(rotation);
	matWorld *= matRot;
	//平行移動
	XMMATRIX matTrans;
	matTrans = DirectX::XMMatrixTranslation(position.x, position.y, 0.0f);
	matWorld *= matTrans;

	//合成
	constMapTransform->mat = matWorld;
	//2D座標に変換
	constMapTransform->mat.r[0].m128_f32[0] = 2.0f / width;
	constMapTransform->mat.r[1].m128_f32[1] = -2.0f / height;
	constMapTransform->mat.r[3].m128_f32[0] = -1.0f + (position.x / width) * 2;
	constMapTransform->mat.r[3].m128_f32[1] = 1.0f - (position.y / height) * 2;
}

void ShadowMap::CreateGraphicsPipeLine0()
{
	HRESULT result;

	ID3DBlob* vsBlob = nullptr;	//頂点シェーダーオブジェクト
	ID3DBlob* psBlob = nullptr;	//ピクセルシェーダーオブジェクト
	ID3DBlob* errorBlob = nullptr;	//エラーオブジェクト

	//頂点シェーダの読み込み コンパイル
	result = D3DCompileFromFile(
		L"Resources/Shaders/ShadowMap/ShadowMapVertexShader.hlsl",
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main", "vs_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&vsBlob, &errorBlob);

	//エラーの場合
	if (FAILED(result)) {
		// errorBlobからエラー内容をstring型にコピー
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "\n";
		// エラー内容を出力ウィンドウに表示
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}

	//ピクセルシェーダの読み込み コンパイル
	result = D3DCompileFromFile(
		L"Resources/Shaders/ShadowMap/ShadowMapPixelShader.hlsl",
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main", "ps_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&psBlob, &errorBlob);

	//エラーの場合
	if (FAILED(result)) {
		// errorBlobからエラー内容をstring型にコピー
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "\n";
		// エラー内容を出力ウィンドウに表示
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}

	//頂点レイアウト
	D3D12_INPUT_ELEMENT_DESC inputLayout[] =
	{
		{
			"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0
		},
		{
			"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0
		},
	};

	//グラフィックスパイプライン設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};

	//シェーダの設定
	pipelineDesc.VS.pShaderBytecode = vsBlob->GetBufferPointer();
	pipelineDesc.VS.BytecodeLength = vsBlob->GetBufferSize();
	pipelineDesc.PS.pShaderBytecode = psBlob->GetBufferPointer();
	pipelineDesc.PS.BytecodeLength = psBlob->GetBufferSize();

	//サンプルマスクの設定
	pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;	//標準設定

	//ラスタライザの設定
	pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;	//カリングしない
	pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;	//ポリゴン内塗りつぶし
	pipelineDesc.RasterizerState.DepthClipEnable = true;	//深度クリッピングを有効に
	pipelineDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	pipelineDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	pipelineDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;

	//ブレンドステート
	pipelineDesc.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

	//共通の設定
	pipelineDesc.BlendState.RenderTarget[0].BlendEnable = false;
	//pipelineDesc.BlendState.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	//pipelineDesc.BlendState.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	//pipelineDesc.BlendState.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;

	////アルファブレンド
	//pipelineDesc.BlendState.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	//pipelineDesc.BlendState.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
	//pipelineDesc.BlendState.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;

	//頂点レイアウトの設定
	pipelineDesc.InputLayout.pInputElementDescs = inputLayout;
	pipelineDesc.InputLayout.NumElements = _countof(inputLayout);

	//図形の形状
	pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	//その他設定
	pipelineDesc.NumRenderTargets = 3;	//描画対象は1
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;	//RGBA
	pipelineDesc.RTVFormats[1] = DXGI_FORMAT_R8_UNORM;	//RGBA
	pipelineDesc.SampleDesc.Count = 1;	//1ピクセルにつき1回サンプリング

	//テクスチャサンプラーの設定
	D3D12_STATIC_SAMPLER_DESC samplerDesc{};
	samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
	samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
	samplerDesc.MinLOD = 0.0f;
	samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	//デスクリプタレンジの設定
	D3D12_DESCRIPTOR_RANGE descriptorRange0{};
	descriptorRange0.NumDescriptors = 1;
	descriptorRange0.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange0.BaseShaderRegister = 0;
	descriptorRange0.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	D3D12_DESCRIPTOR_RANGE descriptorRange1{};
	descriptorRange1.NumDescriptors = 1;
	descriptorRange1.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange1.BaseShaderRegister = 1;

	D3D12_DESCRIPTOR_RANGE descriptorRange2{};
	descriptorRange2.NumDescriptors = 1;
	descriptorRange2.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange2.BaseShaderRegister = 2;

	//ルートパラメータの設定
	D3D12_ROOT_PARAMETER rootParameter[5] = {};
	//定数バッファ0番
	rootParameter[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameter[0].Descriptor.ShaderRegister = 0;
	rootParameter[0].Descriptor.RegisterSpace = 0;
	rootParameter[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	//定数バッファ1番
	rootParameter[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameter[1].Descriptor.ShaderRegister = 1;
	rootParameter[1].Descriptor.RegisterSpace = 0;
	rootParameter[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	//テクスチャレジスタ0番
	rootParameter[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameter[2].DescriptorTable.pDescriptorRanges = &descriptorRange0;
	rootParameter[2].DescriptorTable.NumDescriptorRanges = 1;
	rootParameter[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	//テクスチャレジスタ1番
	rootParameter[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameter[3].DescriptorTable.pDescriptorRanges = &descriptorRange1;
	rootParameter[3].DescriptorTable.NumDescriptorRanges = 1;
	rootParameter[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	//テクスチャレジスタ1番
	rootParameter[4].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameter[4].DescriptorTable.pDescriptorRanges = &descriptorRange2;
	rootParameter[4].DescriptorTable.NumDescriptorRanges = 1;
	rootParameter[4].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	//ルートシグネチャの設定
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	rootSignatureDesc.pParameters = rootParameter;
	rootSignatureDesc.NumParameters = _countof(rootParameter);
	rootSignatureDesc.pStaticSamplers = &samplerDesc;
	rootSignatureDesc.NumStaticSamplers = 1;

	//ルートシグネチャのシリアライズ
	ID3DBlob* rootSigBlob = nullptr;
	result = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0,
		&rootSigBlob, &errorBlob);
	assert(SUCCEEDED(result));
	result = device->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(),
		IID_PPV_ARGS(&rootsignature0));
	assert(SUCCEEDED(result));
	rootSigBlob->Release();
	//パイプラインにルートシグネチャをセット
	pipelineDesc.pRootSignature = rootsignature0.Get();

	//パイプラインステートの生成
	result = device->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(pipelinestate0.ReleaseAndGetAddressOf()));
	assert(SUCCEEDED(result));
}

void ShadowMap::PreDrawScene0(ID3D12GraphicsCommandList* cmdList)
{
	frame++;

	//リソースバリアを変更
	CD3DX12_RESOURCE_BARRIER a0 = CD3DX12_RESOURCE_BARRIER::Transition(
		textureBuff.Get(),
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
		D3D12_RESOURCE_STATE_RENDER_TARGET
	);
	cmdList->ResourceBarrier(1, &a0);

	//レンダーターゲットビュー用デスクリプタヒープのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = descHeapRTV->GetCPUDescriptorHandleForHeapStart();
	//震度ステンシルビュー用デスクリプタヒープのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = descHeapDSV->GetCPUDescriptorHandleForHeapStart();
	dsvHandle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	//レンダーターゲットをセット
	cmdList->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);

	//ビューポートの設定
	CD3DX12_VIEWPORT a1 = CD3DX12_VIEWPORT(0.0f, 0.0f, width, height);
	cmdList->RSSetViewports(1, &a1);
	//シザー矩形の設定
	CD3DX12_RECT a2 = CD3DX12_RECT(0, 0, (LONG)width, (LONG)height);
	cmdList->RSSetScissorRects(1, &a2);

	//震度バッファのクリア
	cmdList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void ShadowMap::PostDrawScene0(ID3D12GraphicsCommandList* cmdList)
{
	//リソースバリアを変更
	CD3DX12_RESOURCE_BARRIER a0 = CD3DX12_RESOURCE_BARRIER::Transition(
		textureBuff.Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET,
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE
	);
	cmdList->ResourceBarrier(1, &a0);
}

void ShadowMap::Shake()
{
	if (shakeFlag == true)
	{
		shakeTimer++;
		shakePos = position + XMFLOAT2(0.0f, shake((int)position.y, 5));
		SetPosition(shakePos);
		if (shakeTimer >= shakeMaxTime)
		{
			shakeFlag = false;
			SetPosition(position);
			shakeTimer = 0;
		}
	}
}

#include "ElecParticle.h"
#include "mathOriginal.h"

#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")

ComPtr<ID3D12RootSignature>ElecParticle::rootsignature;
ComPtr<ID3D12PipelineState>ElecParticle::pipelinestate;
SrvManager* ElecParticle::srvManager = nullptr;
ID3D12Device* ElecParticle::device = nullptr;
Camera* ElecParticle::camera = nullptr;


void ElecParticle::CreateGraphicsPipeline() 
{
	HRESULT result = S_FALSE;
	ComPtr<ID3DBlob> vsBlob; // 頂点シェーダオブジェクト
	ComPtr<ID3DBlob> gsBlob;    // ジオメトリシェーダオブジェクト
	ComPtr<ID3DBlob> psBlob;    // ピクセルシェーダオブジェクト
	ComPtr<ID3DBlob> errorBlob; // エラーオブジェクト

	assert(device);

	// 頂点シェーダの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"Resources/Shaders/ElecParticle/ElecParticleVertexShader.hlsl",     // シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
		"main", "vs_5_0",    // エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
		0,
		&vsBlob, &errorBlob);
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

	// ジオメトリシェーダの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"Resources/Shaders/ElecParticle/ElecParticleGeometryShader.hlsl",     // シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
		"main", "gs_5_0",    // エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
		0,
		&gsBlob, &errorBlob);
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

	// ピクセルシェーダの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"Resources/Shaders/ElecParticle/ElecParticlePixelShader.hlsl",   // シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
		"main", "ps_5_0",    // エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
		0,
		&psBlob, &errorBlob);
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

	// 頂点レイアウト
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		{ // xy座標(1行で書いたほうが見やすい)
			"POSITIONA", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		{ // xy座標(1行で書いたほうが見やすい)
			"POSITIONB", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		{	//スケール
			"SCALE",0,DXGI_FORMAT_R32_FLOAT,0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0
		},
		{	//フレーム
			"FRAME",0,DXGI_FORMAT_R32_FLOAT,0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0
		}
	};

	// グラフィックスパイプラインの流れを設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline{};
	gpipeline.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
	gpipeline.GS = CD3DX12_SHADER_BYTECODE(gsBlob.Get());
	gpipeline.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());

	// サンプルマスク
	gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // 標準設定
	// ラスタライザステート
	gpipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	gpipeline.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
	/*gpipeline.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;*/
	gpipeline.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
	// デプスステンシルステート
	gpipeline.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	gpipeline.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;

	// レンダーターゲットのブレンド設定
	D3D12_RENDER_TARGET_BLEND_DESC blenddesc{};
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;    // RBGA全てのチャンネルを描画
	blenddesc.BlendEnable = true;
	/*blenddesc.BlendOp = D3D12_BLEND_OP_ADD;
	blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
	blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;*/
	//加算合成
	blenddesc.BlendOp = D3D12_BLEND_OP_ADD;
	blenddesc.SrcBlend = D3D12_BLEND_ONE;
	blenddesc.DestBlend = D3D12_BLEND_ONE;
	//減算合成
	/*blenddesc.BlendOp = D3D12_BLEND_OP_REV_SUBTRACT;
	blenddesc.SrcBlend = D3D12_BLEND_ONE;
	blenddesc.DestBlend = D3D12_BLEND_ONE;*/

	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;

	// ブレンドステートの設定
	gpipeline.BlendState.RenderTarget[0] = blenddesc;

	// 深度バッファのフォーマット
	gpipeline.DSVFormat = DXGI_FORMAT_D32_FLOAT;

	// 頂点レイアウトの設定
	gpipeline.InputLayout.pInputElementDescs = inputLayout;
	gpipeline.InputLayout.NumElements = _countof(inputLayout);

	// 図形の形状設定（三角形）
	gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;

	gpipeline.NumRenderTargets = 1;    // 描画対象は1つ
	gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0～255指定のRGBA
	gpipeline.SampleDesc.Count = 1; // 1ピクセルにつき1回サンプリング

	// デスクリプタレンジ
	CD3DX12_DESCRIPTOR_RANGE descRangeSRV;
	descRangeSRV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0); // t0 レジスタ

	// ルートパラメータ
	CD3DX12_ROOT_PARAMETER rootparams[2];
	// CBV（座標変換行列用）
	rootparams[0].InitAsConstantBufferView(0, 0, D3D12_SHADER_VISIBILITY_ALL);
	// SRV（テクスチャ）
	rootparams[1].InitAsDescriptorTable(1, &descRangeSRV, D3D12_SHADER_VISIBILITY_ALL);

	// スタティックサンプラー
	CD3DX12_STATIC_SAMPLER_DESC samplerDesc = CD3DX12_STATIC_SAMPLER_DESC(0);

	// ルートシグネチャの設定
	CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init_1_0(_countof(rootparams), rootparams, 1, &samplerDesc, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ComPtr<ID3DBlob> rootSigBlob;
	// バージョン自動判定のシリアライズ
	result = D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
	// ルートシグネチャの生成
	result = device->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(rootsignature.ReleaseAndGetAddressOf()));
	if (FAILED(result)) { assert(0); }

	gpipeline.pRootSignature = rootsignature.Get();

	// グラフィックスパイプラインの生成
	result = device->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(pipelinestate.ReleaseAndGetAddressOf()));
	if (FAILED(result)) { assert(0); }
}

void ElecParticle::CreateBuffers()
{
	HRESULT result;

	//頂点データ生成
	/*CreateVertex();*/

	//頂点データ全体のサイズ
	UINT sizeVB = static_cast<UINT>(sizeof(VertexPos)) * vertexCount;

	//頂点バッファの設定
	D3D12_HEAP_PROPERTIES heapProp{};	//ヒープ設定
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;	//CPUへの転送用
	//リソース設定
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeVB;	//頂点データ全体のサイズ
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	result = device->CreateCommittedResource(
		&heapProp,	//ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&resDesc,	//リソース設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff)
	);
	assert(SUCCEEDED(result));

	//頂点バッファへのデータ転送
	//GPU上のバッファに対応した仮想メモリ（メインメモリ上）を取得
	//VertexPos* vertMap = nullptr;
	//result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	//assert(SUCCEEDED(result));
	//for (int i = 0; i <= 30; i++)
	//{
	//	vertMap[i].pos = XMFLOAT3(i, 0, 0);
	//}
	////つながりを解除
	//vertBuff->Unmap(0, nullptr);

	//頂点バッファビューの作成
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	vbView.SizeInBytes = sizeVB;
	vbView.StrideInBytes = sizeof(VertexPos);

	//定数バッファの生成
	CD3DX12_HEAP_PROPERTIES v1 = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	CD3DX12_RESOURCE_DESC v2 = CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataTransform) + 0xff) & ~0xff);
	result = device->CreateCommittedResource(
		&v1,
		D3D12_HEAP_FLAG_NONE,
		&v2,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffTransform)
	);
}

void ElecParticle::Update()
{
	//-----この上に頂点の更新処理を書く-----

	HRESULT result;

	//パーティクルの更新処理
	UpdateParticle();

	//頂点バッファへデータ転送
	//GPU上のバッファに対応した仮想メモリ（メインメモリ上）を取得
	VertexPos* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));
	for (std::forward_list<Particle>::iterator it = particles.begin(); it != particles.end(); it++)
	{
		//座標
		vertMap->pos1 = it->position1;
		vertMap->pos2 = it->position2;
		vertMap->scale = it->scale;
		vertMap->frame = (float)it->frame / (float)it->num_frame;
		//次の頂点へ
		vertMap++;
	}
	//つながりを解除
	vertBuff->Unmap(0, nullptr);

	//定数バッファへデータ転送
	//ビュープロジェクション行列
	const XMMATRIX& matProjection = camera->GetMatProjection();
	const XMMATRIX& matView = camera->GetMatView();
	ConstBufferDataTransform* constMap = nullptr;
	result = constBuffTransform->Map(0, nullptr, (void**)&constMap);
	if (SUCCEEDED(result))
	{
		constMap->mat = matView * matProjection;
		constMap->matBillboard = camera->GetMatBillboard();
		/*constMap->world = matWorld;*/
		constBuffTransform->Unmap(0, nullptr);
	}
}

void ElecParticle::UpdateParticle()
{
	//寿命が尽きたパーティクルを全削除
	particles.remove_if([](Particle& x)
		{
			return x.frame >= x.num_frame;
		}
	);

	//全パーティクル更新
	for (std::forward_list<Particle>::iterator it = particles.begin(); it != particles.end(); it++)
	{
		//経過フレーム数をカウント
		it->frame++;

		//進行度を0~1の範囲に換算
		float f = (float)it->frame / it->num_frame;
		//スケールの線形補間
		it->scale = (it->endScale - it->startScale) * f;
		it->scale += it->startScale;
	}
}

void ElecParticle::Draw(ID3D12GraphicsCommandList* cmdList)
{
	//パイプラインステートの設定
	cmdList->SetPipelineState(pipelinestate.Get());
	//ルートシグネチャの設定
	cmdList->SetGraphicsRootSignature(rootsignature.Get());
	//プリミティブ形状の設定
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
	//定数バッファビューをセット
	cmdList->SetGraphicsRootConstantBufferView(0, constBuffTransform->GetGPUVirtualAddress());

	//頂点バッファをセット
	cmdList->IASetVertexBuffers(0, 1, &vbView);

	//描画用のデスクリプタヒープ設定
	srvManager->PreDraw();
	//ルートパラメーター1番にセット
	srvManager->SetGraphicsRootDescriptorTable(1, textureNum);

	//描画コマンド
	cmdList->DrawInstanced((UINT)std::distance(particles.begin(), particles.end()), 1, 0, 0);
}

void ElecParticle::Add(XMFLOAT3 pos, float startScale)
{
	/*float randPos = 10.0f;
	float randVelo = 0.2f;
	float randAcc = 0.0001f;
	for (int i = 0; i < sparkCount; i++)
	{
		XMFLOAT3 p = pos;
		XMFLOAT3 velocity((float)rand() / RAND_MAX * randVelo - randVelo / 2.0f, (float)rand() / RAND_MAX * randVelo - randVelo / 2.0f
			, (float)rand() / RAND_MAX * randVelo - randVelo / 2.0f);
		XMFLOAT3 accel(0.0f, (float)rand() / RAND_MAX * randAcc, 0.0f);

		AddParticle(30, p, velocity, accel, startScale, 0.0f);
	}*/
}

void ElecParticle::AddParticle(int life, XMFLOAT3 startPosition, XMFLOAT3 endPosition, 
	float startScale, float endScale, int diveNum, float strength)
{
	int d = diveNum;
	Particle p2;
	//各点の設定
	for (int i = 0; i < diveNum; i++)
	{
		//リストに要素を追加
		particles.emplace_front();
		//追加した要素の参照
		Particle& p = particles.front();
		//最初の点
		if (i == 0)
		{
			p2.position2 = startPosition;
			p2.num_frame = life;
			continue;
		}
		//最後の点
		if (i == diveNum - 1)
		{
			p2.position1 = p2.position2;
			p2.position2 = endPosition;
			p2.scale = 0.0f;
			p2.num_frame = life;
			p2.startScale = startScale;
			p2.endScale = endScale;
			p = p2;
			continue;
		}
		//それ以外
		//前の点→最終地点のベクトルを求める
		XMFLOAT3 vec1 = endPosition - p2.position2;
		//ベクトルを分割
		vec1 = vec1 / (float)d;
		XMFLOAT3 vec2 = vec1;
		//乱数のために絶対値に直す
		if (vec2.x < 0)vec2.x *= -1;
		if (vec2.y < 0)vec2.y *= -1;
		if (vec2.z < 0)vec2.z *= -1;
		//乱数取得
		float x = GetRand((-vec2.x / strength),(vec2.x / strength));
		float y = GetRand((-vec2.y / strength),(vec2.y / strength));
		float z = GetRand((-vec2.z / strength),(vec2.z / strength));
		//乱数を加算
		vec1 = vec1 + XMFLOAT3(x, y, z);
		//前の座標+生成したベクトル
		p2.position1 = p2.position2;
		p2.position2 = p2.position2 + vec1;
		p2.num_frame = life;
		p2.scale = 0.0f;
		p2.startScale = startScale;
		p2.endScale = endScale;
		p = p2;
		//分割数を減らす
		d -= 1;
	}

	//int d = diveNum;
	//Particle p2;
	////各点の設定
	//for (int i = 0; i < diveNum; i++)
	//{
	//	//リストに要素を追加
	//	particles.emplace_front();
	//	//追加した要素の参照
	//	Particle& p = particles.front();
	//	//最初の点
	//	if (i == 0)
	//	{
	//		p2.position = startPosition;
	//		p2.num_frame = life;
	//		p = p2;
	//		continue;
	//	}
	//	//最後の点
	//	if (i == diveNum - 1)
	//	{
	//		p2.position = endPosition;
	//		p2.num_frame = life;
	//		p = p2;
	//		continue;
	//	}
	//	//それ以外
	//	//前の点→最終地点のベクトルを求める
	//	XMFLOAT3 vec1 = endPosition - p2.position;
	//	//ベクトルを分割
	//	vec1 = vec1 / d;
	//	XMFLOAT3 vec2 = vec1;
	//	//乱数のために絶対値に直す
	//	if (vec2.x < 0)vec2.x *= -1;
	//	if (vec2.y < 0)vec2.y *= -1;
	//	if (vec2.z < 0)vec2.z *= -1;
	//	//乱数取得
	//	int x = RNG((int)(-vec2.x / strength), (int)(vec2.x / strength), 1);
	//	int y = RNG((int)(-vec2.y / strength), (int)(vec2.y / strength), 1);
	//	int z = RNG((int)(-vec2.z / strength), (int)(vec2.z / strength), 1);
	//	//乱数を加算
	//	vec1 = vec1 + XMFLOAT3(x, y,z);
	//	//前の座標+生成したベクトル
	//	p2.position = p2.position + vec1;
	//	p2.num_frame = life;
	//	p = p2;
	//	//分割数を減らす
	//	d -= 1;
	//}
}
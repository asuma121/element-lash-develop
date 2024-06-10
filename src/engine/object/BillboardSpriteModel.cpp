/**
 * @file BillboardSprite.cpp
 * @brief ビルボードのスプライト モデル
 *
 * @author Asuma Syota
 * @date 2023/4
 */

#include "BillboardSpriteModel.h"

SrvManager* BillboardSpriteModel::srvManager = nullptr;
ID3D12Device* BillboardSpriteModel::device = nullptr;

void BillboardSpriteModel::CreateBuffers()
{
	HRESULT result;

	//頂点、インデックスサイズ設定
	vertices.resize(12);
	indices.resize(18);

	//頂点データ生成
	CreateVertex();

	//頂点データ全体のサイズ
	UINT sizeVB = static_cast<UINT>(sizeof(VertexPosNormalUv)) * (UINT)vertices.size();

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
	VertexPosNormalUv* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));
	//全頂点に対して
	for (int i = 0; i < vertices.size(); i++)
	{
		vertMap[i] = vertices[i];	//座標をコピー
	}
	//つながりを解除
	vertBuff->Unmap(0, nullptr);

	//頂点バッファビューの作成
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	vbView.SizeInBytes = sizeVB;
	vbView.StrideInBytes = sizeof(vertices[0]);

	//頂点インデックス全体のサイズ
	UINT sizeIB = static_cast<UINT>(sizeof(unsigned short) * indices.size());

	//インデックスバッファ設定
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;	//CPUへの転送用
	//リソース設定
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeIB;	//インデックス情報が入る分のサイズ
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//インデックスバッファ生成
	result = device->CreateCommittedResource(
		&heapProp,	//ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&resDesc,	//リソース設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&indexBuff)
	);

	//インデックスバッファをマッピング
	uint16_t* indexMap = nullptr;
	result = indexBuff->Map(0, nullptr, (void**)&indexMap);
	//全インデックスに対して
	for (int i = 0; i < indices.size(); i++)
	{
		indexMap[i] = indices[i];	//インデックスをコピー
	}
	//マッピング解除
	indexBuff->Unmap(0, nullptr);

	//インデックスバッファビューの作成
	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes = sizeIB;
}

void BillboardSpriteModel::CreateVertex()
{
	//球体一つの基礎サイズ
	XMFLOAT3 size = { 1.0f,1.0f,1.0f };
	//頂点データ
	VertexPosNormalUv v[] = {
		//前
		{{-size.x / 2,-size.y / 2,-size.z / 2},{},{0.0f,1.0f} },	//0
		{{-size.x / 2, size.y / 2,-size.z / 2},{},{0.0f,0.0f} },	//1 
		{{ size.x / 2,-size.y / 2,-size.z / 2},{},{1.0f,1.0f} },	//2 
		{{ size.x / 2, size.y / 2,-size.z / 2},{},{1.0f,0.0f} },	//3
		//後				 	   
		{{-size.x / 2,-size.y / 2,-size.z / 2},{},{0.0f,1.0f} },	//4
		{{-size.x / 2, size.y / 2,-size.z / 2},{},{0.0f,0.0f} },	//5
		{{ size.x / 2,-size.y / 2,-size.z / 2},{},{1.0f,1.0f} },	//6
		{{ size.x / 2, size.y / 2,-size.z / 2},{},{1.0f,0.0f} },	//7
		//左				 	    
		{{-size.x / 2,-size.y / 2,-size.z / 2},{},{0.0f,1.0f} },	//8
		{{-size.x / 2, size.y / 2,-size.z / 2},{},{0.0f,0.0f} },	//9
		{{ size.x / 2,-size.y / 2,-size.z / 2},{},{1.0f,1.0f} },	//10
		{{ size.x / 2, size.y / 2,-size.z / 2},{},{1.0f,0.0f} },	//11
	};
	//インデックスデータ
	unsigned short in[] =
	{
		//前
		0,1,2,	//三角形1つ目
		2,1,3,	//三角形2つ目
		//後
		4,5,6,
		6,5,7,
		//左
		8,9,10,
		10,9,11,
	};

	for (int i = 0; i < vertices.size(); i++)
	{
		vertices[i] = v[i];
	}

	for (int i = 0; i < indices.size(); i++)
	{
		indices[i] = in[i];
	}

	//法線の計算
	for (int i = 0; i < indices.size() / 3; i++)
	{//三角形1つごとに計算していく
		//三角形のインデックスを取り出して、一時的な変数に入れる
		unsigned short indices0 = indices[i * 3 + 0];
		unsigned short indices1 = indices[i * 3 + 1];
		unsigned short indices2 = indices[i * 3 + 2];
		//三角形を構成する頂点座標をベクトルに代入
		XMVECTOR p0 = XMLoadFloat3(&vertices[indices0].pos);
		XMVECTOR p1 = XMLoadFloat3(&vertices[indices1].pos);
		XMVECTOR p2 = XMLoadFloat3(&vertices[indices2].pos);
		//p0→p1ベクトル、p0→p2ベクトルを計算　(ベクトルの減算)
		XMVECTOR v1 = DirectX::XMVectorSubtract(p1, p0);
		XMVECTOR v2 = DirectX::XMVectorSubtract(p2, p0);
		//外積は両方から垂直なベクトル
		XMVECTOR normal = DirectX::XMVector3Cross(v1, v2);
		//正規化
		normal = DirectX::XMVector3Normalize(normal);
		//求めた法線を頂点データに代入
		DirectX::XMStoreFloat3(&vertices[indices0].normal, normal);
		DirectX::XMStoreFloat3(&vertices[indices1].normal, normal);
		DirectX::XMStoreFloat3(&vertices[indices2].normal, normal);
	}
}

void BillboardSpriteModel::Update()
{
	//-----この上に頂点の更新処理を書く-----

	HRESULT result;
	//頂点データ全体のサイズ
	UINT sizeVB = static_cast<UINT>(sizeof(VertexPosNormalUv)) * (UINT)vertices.size();

	//頂点バッファへのデータ転送
	//GPU上のバッファに対応した仮想メモリ（メインメモリ上）を取得
	VertexPosNormalUv* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));
	//全頂点に対して
	for (int i = 0; i < vertices.size(); i++)
	{
		vertMap[i] = vertices[i];	//座標をコピー
	}
	//つながりを解除
	vertBuff->Unmap(0, nullptr);
}

void BillboardSpriteModel::Draw(ID3D12GraphicsCommandList* cmdList)
{
	//頂点バッファをセット
	cmdList->IASetVertexBuffers(0, 1, &vbView);

	//描画用のデスクリプタヒープ設定
	srvManager->PreDraw();
	//ルートパラメーター1番にセット
	srvManager->SetGraphicsRootDescriptorTable(1, textureNum);

	//描画コマンド
	cmdList->DrawIndexedInstanced((UINT)indices.size(), 1, 0, 0, 0);
}
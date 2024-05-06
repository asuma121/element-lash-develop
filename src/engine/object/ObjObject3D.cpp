/**
 * @file ObjModel.cpp
 * @brief 変換したObjファイルを描画
 * @author Asuma Syota
 * @date 2023/4
 */

#include "ObjObject3D.h"

Camera* ObjObject3D::camera = nullptr;

void ObjObject3D::Initialize(ID3D12Device* device, ObjModel* model, Camera* camera)
{
	this->device = device;
	this->model = model;
	this->camera = camera;

	// ヒーププロパティ
	CD3DX12_HEAP_PROPERTIES heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	// リソース設定
	CD3DX12_RESOURCE_DESC resourceDesc =
		CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataB0) + 0xff) & ~0xff);

	HRESULT result;

	// 定数バッファの生成
	result = this->device->CreateCommittedResource(
		&heapProps, // アップロード可能
		D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&constBuffB0));
	assert(SUCCEEDED(result));

	// リソース設定
	resourceDesc =
		CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataB1) + 0xff) & ~0xff);

	// 定数バッファの生成
	result = this->device->CreateCommittedResource(
		&heapProps, // アップロード可能
		D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&constBuffB1));
	assert(SUCCEEDED(result));
}

void ObjObject3D::Update()
{
	HRESULT result;
	XMMATRIX matScale, matRot, matTrans;

	// スケール、回転、平行移動行列の計算
	matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
	matRot = XMMatrixIdentity();
	/*matRot *= XMMatrixRotationY(rotation.y);
	matRot *= XMMatrixRotationZ(rotation.z);
	matRot *= XMMatrixRotationX(rotation.x);*/
	matRot *= XMMatrixRotationZ(rotation.z);
	matRot *= XMMatrixRotationX(rotation.x);
	matRot *= XMMatrixRotationY(rotation.y);
	matTrans = XMMatrixTranslation(position.x, position.y, position.z);

	//ワールド行列の合成
	matWorld = XMMatrixIdentity(); // 変形をリセット
	matWorld *= matScale; // ワールド行列にスケーリングを反映
	matWorld *= matRot; // ワールド行列に回転を反映
	matWorld *= matTrans; // ワールド行列に平行移動を反映

	//// 親オブジェクトがあれば
	//if (parent != nullptr) {
	//	// 親オブジェクトのワールド行列を掛ける
	//	matWorld *= parent->matWorld;
	//}

	// 定数バッファへデータ転送
	ConstBufferDataB0* constMap0 = nullptr;
	result = constBuffB0->Map(0, nullptr, (void**)&constMap0);
	constMap0->mat = matWorld * camera->GetMatView() * camera->GetMatProjection();	// 行列の合成
	constBuffB0->Unmap(0, nullptr);

	//定数バッファへデータ転送
	ConstBufferDataB1* constMap1 = nullptr;
	result = constBuffB1->Map(0, nullptr, (void**)&constMap1);
	constMap1->ambient = model->GetMaterial().ambient;
	constMap1->diffuse = model->GetMaterial().diffuse;
	constMap1->specular = model->GetMaterial().specular;
	constMap1->alpha = model->GetMaterial().alpha;
	constBuffB1->Unmap(0, nullptr);
}

void ObjObject3D::Draw(ID3D12GraphicsCommandList* cmdList, D3D12_VERTEX_BUFFER_VIEW& vbView, D3D12_INDEX_BUFFER_VIEW& ibView)
{
	this->cmdList = cmdList;
	// パイプラインステートの設定
	cmdList->SetPipelineState(model->GetPipelinestate());
	// ルートシグネチャの設定
	cmdList->SetGraphicsRootSignature(model->GetRootSignature());
	// プリミティブ形状を設定
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// 頂点バッファの設定
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	// インデックスバッファの設定
	cmdList->IASetIndexBuffer(&ibView);

	// デスクリプタヒープの配列
	ID3D12DescriptorHeap* ppHeaps[] = { model->GetDescHeap() };
	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

	// 定数バッファビューをセット
	cmdList->SetGraphicsRootConstantBufferView(0, constBuffB0->GetGPUVirtualAddress());
	cmdList->SetGraphicsRootConstantBufferView(1, constBuffB1->GetGPUVirtualAddress());
	// シェーダリソースビューをセット
	cmdList->SetGraphicsRootDescriptorTable(2, model->GetSrv());
	// 描画コマンド
	cmdList->DrawIndexedInstanced(model->GetIndicesSize(), 1, 0, 0, 0);
}

void ObjObject3D::Delete()
{
}

void ObjObject3D::setPosition(XMFLOAT3 pos)
{
	position = pos;
}

void ObjObject3D::setRotation(XMFLOAT3 rot)
{
	rotation = rot;
}

void ObjObject3D::setScale(XMFLOAT3 sca)
{
	scale = sca;
}

ObjObject3D* ObjObject3D::GetInstance()
{
	static ObjObject3D instance;
	return &instance;
}

ObjObject3D::ObjObject3D()
{
}

ObjObject3D::~ObjObject3D()
{
	/*delete model;*/
}
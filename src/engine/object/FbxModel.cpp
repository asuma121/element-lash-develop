/**
 * @file FbxModel.cpp
 * @brief FbxLoaderで変換したFBXファイルを保持する
 * @author Asuma Syota
 * @date 2023/4
 */

#include "FbxModel.h"

using namespace Microsoft::WRL;

SrvManager* FbxModel::srvManager = nullptr;
ID3D12Device* FbxModel::device = nullptr;

FbxModel::~FbxModel()
{
	//FBXシーンの解放
	fbxScene->Destroy();
}

void FbxModel::CreateBuffers()
{
	HRESULT result;

	//頂点データ全体のサイズ
	UINT sizeVB = static_cast<UINT>(sizeof(VertexPosNormalUvSkin)) * (UINT)vertices.size();

	//頂点バッファ生成
	CD3DX12_HEAP_PROPERTIES v1 = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	CD3DX12_RESOURCE_DESC v2 = CD3DX12_RESOURCE_DESC::Buffer(sizeVB);
	result = device->CreateCommittedResource(
		&v1,
		D3D12_HEAP_FLAG_NONE,
		&v2,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff));

	//頂点バッファへのデータ転送
	VertexPosNormalUvSkin* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	if (SUCCEEDED(result))
	{
		std::copy(vertices.begin(), vertices.end(), vertMap);
		vertBuff->Unmap(0, nullptr);
	}

	//頂点バッファビューの生成
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	vbView.SizeInBytes = sizeVB;
	vbView.StrideInBytes = sizeof(vertices[0]);

	//頂点インデックス全体のサイズ
	UINT sizeIB = static_cast<UINT>(sizeof(unsigned short) * indices.size());

	//インデックスバッファ生成
	v1 = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	v2 = CD3DX12_RESOURCE_DESC::Buffer(sizeIB);
	result = device->CreateCommittedResource(
		&v1,
		D3D12_HEAP_FLAG_NONE,
		&v2,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&indexBuff));

	//インデックスバッファへのデータ転送
	unsigned short* indexMap = nullptr;
	result = indexBuff->Map(0, nullptr, (void**)&indexMap);
	if (SUCCEEDED(result)) {
		std::copy(indices.begin(), indices.end(), indexMap);
		indexBuff->Unmap(0, nullptr);
	}

	//インデックスバッファビューの作成
	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes = sizeIB;
}

void FbxModel::Draw(ID3D12GraphicsCommandList* cmdList, int textureNum)
{
	//頂点バッファをセット
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	//インデックスバッファをセット
	cmdList->IASetIndexBuffer(&ibView);

	//描画用のデスクリプタヒープ設定
	srvManager->PreDraw();
	//ルートパラメーター1番にセット
	srvManager->SetGraphicsRootDescriptorTable(1, textureNum);

	//描画コマンド
	cmdList->DrawIndexedInstanced((UINT)indices.size(), 1, 0, 0, 0);
}

void FbxModel::DrawTexture1(ID3D12GraphicsCommandList* cmdList, int textureNum)
{
	//描画コマンド
	cmdList->DrawIndexedInstanced((UINT)indices.size(), 1, 0, 0, 0);

	//頂点バッファをセット
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	//インデックスバッファをセット
	cmdList->IASetIndexBuffer(&ibView);

	//描画用のデスクリプタヒープ設定
	srvManager->PreDraw();
	//ルートパラメーター1番にセット
	srvManager->SetGraphicsRootDescriptorTable(1, textureNum);
}

void FbxModel::DrawTexture2(ID3D12GraphicsCommandList* cmdList, int textureNum1, int textureNum2)
{
	//頂点バッファをセット
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	//インデックスバッファをセット
	cmdList->IASetIndexBuffer(&ibView);

	//描画用のデスクリプタヒープ設定
	srvManager->PreDraw();
	//ルートパラメーター1番にセット
	srvManager->SetGraphicsRootDescriptorTable(1, textureNum1);
	//ルートパラメーター6番にセット
	srvManager->SetGraphicsRootDescriptorTable(6, textureNum2);
}

void FbxModel::DrawTexture3(ID3D12GraphicsCommandList* cmdList, int textureNum1, int textureNum2, int textureNum3)
{
	//頂点バッファをセット
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	//インデックスバッファをセット
	cmdList->IASetIndexBuffer(&ibView);

	//描画用のデスクリプタヒープ設定
	srvManager->PreDraw();
	//ルートパラメーター1番にセット
	srvManager->SetGraphicsRootDescriptorTable(1, textureNum1);
	//ルートパラメーター6番にセット
	srvManager->SetGraphicsRootDescriptorTable(6, textureNum2);
	//ルートパラメーター7番にセット
	srvManager->SetGraphicsRootDescriptorTable(7, textureNum3);
}

void FbxModel::DrawTexture4(ID3D12GraphicsCommandList* cmdList, int textureNum1, int textureNum2, int textureNum3, int textureNum4)
{
	//頂点バッファをセット
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	//インデックスバッファをセット
	cmdList->IASetIndexBuffer(&ibView);

	//描画用のデスクリプタヒープ設定
	srvManager->PreDraw();
	//ルートパラメーター1番にセット
	srvManager->SetGraphicsRootDescriptorTable(1, textureNum1);
	//ルートパラメーター6番にセット
	srvManager->SetGraphicsRootDescriptorTable(6, textureNum2);
	//ルートパラメーター7番にセット
	srvManager->SetGraphicsRootDescriptorTable(7, textureNum3);
	//ルートパラメーター8番にセット
	srvManager->SetGraphicsRootDescriptorTable(8, textureNum3);
}

void FbxModel::PreDraw(ID3D12GraphicsCommandList* cmdList)
{
	//描画コマンド
	cmdList->DrawIndexedInstanced((UINT)indices.size(), 1, 0, 0, 0);
}
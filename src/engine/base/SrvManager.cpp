#include "SrvManager.h"

const uint32_t SrvManager::kMaxSRVCount = 512;

void SrvManager::Initialize()
{
	HRESULT result;

	//デスクリプタヒープの設定
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	srvHeapDesc.NumDescriptors = kMaxSRVCount;

	//デスクリプタヒープの生成
	result = directXCommon->GetDevice()->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&descriptorHeap));
	assert(SUCCEEDED(result));

	//デスクリプタ1つのサイズを取得して記録
	descriptorSize = directXCommon->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

void SrvManager::CreateSRVForTexture2D(uint32_t srvIndex, ID3D12Resource* pResource, DXGI_FORMAT format, UINT mipLevel)
{
	//SRVインデックスを加算
	Allocate();

	//シェーダリソースビューの設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = mipLevel;

	//ハンドルの指す位置にシェーダリソースビュー作成
	directXCommon->GetDevice()->CreateShaderResourceView(pResource, &srvDesc, GetCPUDescriptorHandle(srvIndex));
}

void SrvManager::CreateSRVForShadowMap(ID3D12Resource* pResource, DXGI_FORMAT format, UINT mipLevel)
{
	//シェーダリソースビューの設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = mipLevel;

	//ハンドルの指す位置にシェーダリソースビュー作成
	directXCommon->GetDevice()->CreateShaderResourceView(pResource, &srvDesc, GetCPUDescriptorHandle(Allocate() + 1));
}

void SrvManager::CreateDepthSRVForShadowMap(ID3D12Resource* pResource, DXGI_FORMAT format, UINT mipLevel)
{
	//設定するインデックスの番号取得
	int indexNum = Allocate() + 1;

	//シャドウマップのインデックスの番号として末尾に追加
	shadowDepthIndexNum.emplace_back(indexNum);

	//シェーダリソースビューの設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = mipLevel;

	//ハンドルの指す位置にシェーダリソースビュー作成
	directXCommon->GetDevice()->CreateShaderResourceView(pResource, &srvDesc, GetCPUDescriptorHandle(indexNum));
}

void SrvManager::PreDraw()
{
	//描画用のデスクリプタヒープ設定
	ID3D12DescriptorHeap* descriptorHeaps[] = { descriptorHeap.Get()};
	directXCommon->GetCommandList()->SetDescriptorHeaps(1, descriptorHeaps);
}

void SrvManager::SetGraphicsRootDescriptorTable(UINT RootParameterIndex, uint32_t srvIndex)
{
	//ルートパラメーターをセット
	directXCommon->GetCommandList()->SetGraphicsRootDescriptorTable(RootParameterIndex, GetGPUDescriptorHandle(srvIndex));
}

uint32_t SrvManager::Allocate()
{
	//returnする番号を一旦記録しておく
	uint32_t index = useIndex;
	//次回のために番号を1進める
	useIndex++;
	//上で記録したものをreturn
	return index;
}

D3D12_CPU_DESCRIPTOR_HANDLE SrvManager::GetCPUDescriptorHandle(uint32_t index)
{
	//デスクリプタヒープの先頭ハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE handleCPU = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
	handleCPU.ptr += (descriptorSize * index);

	return handleCPU;
}

D3D12_GPU_DESCRIPTOR_HANDLE SrvManager::GetGPUDescriptorHandle(uint32_t index)
{
	//デスクリプタヒープの先頭ハンドルを取得
	D3D12_GPU_DESCRIPTOR_HANDLE handleGPU = descriptorHeap->GetGPUDescriptorHandleForHeapStart();
	handleGPU.ptr += (descriptorSize * index);

	return handleGPU;
}

/**
 * @file TextureManager.cpp
 * @brief ゲームで使うテクスチャをすべて管理
 * @author Asuma Syota
 * @date 2023/4
 */

#include "TextureManager.h"

//静的メンバ変数
ID3D12Device* TextureManager::device = nullptr;
SrvManager* TextureManager::srvManager = nullptr;

void TextureManager::Initialize()
{
	/*HRESULT result;*/

	metadata.resize(kMaxSrvCount);
	scratchImg.resize(kMaxSrvCount);
}

void TextureManager::LoadFile(int number, const wchar_t* fileName)
{
	HRESULT result;

	//WICテクスチャのロード
	result = DirectX::LoadFromWICFile(
		fileName,
		DirectX::WIC_FLAGS_NONE,
		&metadata[number],
		scratchImg[number]
	);

	DirectX::ScratchImage mipChain{};

	//ミップマップ生成
	result = DirectX::GenerateMipMaps(
		scratchImg[number].GetImages(),
		scratchImg[number].GetImageCount(),
		scratchImg[number].GetMetadata(),
		DirectX::TEX_FILTER_DEFAULT,
		0,
		mipChain
	);
	if (SUCCEEDED(result))
	{
		scratchImg[number] = std::move(mipChain);
		metadata[number] = scratchImg[number].GetMetadata();
	}

	//読み込んだディフューズテクスチャをSRGBとして扱う
	metadata[number].format = DirectX::MakeSRGB(metadata[number].format);

	//リソース設定
	D3D12_RESOURCE_DESC textureResourceDesc{};
	textureResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	textureResourceDesc.Format = metadata[number].format;
	textureResourceDesc.Width = metadata[number].width;
	textureResourceDesc.Height = (UINT)metadata[number].height;
	textureResourceDesc.DepthOrArraySize = (UINT)metadata[number].arraySize;
	textureResourceDesc.MipLevels = (UINT)metadata[number].mipLevels;
	textureResourceDesc.SampleDesc.Count = 1;

	//テクスチャバッファ設定
	D3D12_HEAP_PROPERTIES textureHeapProp{};
	textureHeapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
	textureHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	textureHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;

	//テクスチャバッファの生成
	result = device->CreateCommittedResource(
		&textureHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&textureResourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&textureBuff[number])
	);

	for (size_t i = 0; i < metadata[number].mipLevels; i++)
	{
		//ミップマップレベルを指定してイメージを取得
		const DirectX::Image* img = scratchImg[number].GetImage(i, 0, 0);
		//テクスチャバッファにデータ転送
		result = textureBuff[number]->WriteToSubresource(
			(UINT)i,
			nullptr,
			img->pixels,
			(UINT)img->rowPitch,
			(UINT)img->slicePitch
		);
		assert(SUCCEEDED(result));
	}

	//SRV生成
	srvManager->CreateSRVForTexture2D(number, textureBuff[number].Get(), textureResourceDesc.Format, textureResourceDesc.MipLevels);

}
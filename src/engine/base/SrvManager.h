#pragma once
#include "DirectXCommon.h"

class SrvManager {

public:	//メンバ関数

	//DirecrXCommonをセット
	void SetDxCommon(DirectXCommon* directXCommon) { this->directXCommon = directXCommon; }

	//初期化
	void Initialize();

	//SRV生成(テクスチャ用)
	void CreateSRVForTexture2D(uint32_t srvIndex, ID3D12Resource* pResource, DXGI_FORMAT format, UINT mipLevel);

	//SRV生成(シャドウマップ用)
	void CreateSRVForShadowMap(ID3D12Resource* pResource, DXGI_FORMAT format, UINT mipLevel);

	//SRV生成(シャドウマップ用)
	void CreateDepthSRVForShadowMap(ID3D12Resource* pResource, DXGI_FORMAT format, UINT mipLevel);

	//描画前処理
	void PreDraw();

	//描画のためのハンドルをセットする関数
	void SetGraphicsRootDescriptorTable(UINT RootParameterIndex, uint32_t srvIndex);

	//次に使用するSRVインデックスの番号を計算して返す
	uint32_t Allocate();

	//シャドウマップのインデックスの番号を取得
	std::vector<int>GetShadowDepthIndexNum() { return shadowDepthIndexNum; };

	//CPUハンドル計算用関数
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(uint32_t index);
	//GPUハンドル計算用関数
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(uint32_t index);

private:	//メンバ変数

	//DirectXCommon
	DirectXCommon* directXCommon = nullptr;

	//最大SRV数
	static const uint32_t kMaxSRVCount;
	//SRV用デスクリプタサイズ
	uint32_t descriptorSize;
	//SRV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descriptorHeap;
	//次に使用するSRVインデックス
	uint32_t useIndex = 0;

	//シャドウマップのインデックスの番号
	std::vector<int>shadowDepthIndexNum;
};
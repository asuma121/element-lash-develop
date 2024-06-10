/**
 * @file BillboardSprite.h
 * @brief ビルボードのスプライト モデル
 *
 * @author Asuma Syota
 * @date 2023/4
 */

#pragma once
#include "vector"
#include "DirectXMath.h"
#include "DirectXCommon.h"
#include "DirectXTex.h"
#include "windows.h"
#include "wrl.h"
#include "d3d12.h"
#include "d3dx12.h"
#include "TextureManager.h"

class BillboardSpriteModel
{
private:	//エイリアス
	//Microsoft::WRL::を省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
	using TexMetadata = DirectX::TexMetadata;
	using ScracthImage = DirectX::ScratchImage;
	//std::を省略
	using string = std::string;
	template<class T>using vector = std::vector<T>;

public:	//静的メンバ関数

	/// <summary>
	///SrvManagerセット
	/// </summary>
	static void SetSrvManager(SrvManager* srvManager) { BillboardSpriteModel::srvManager = srvManager; }

	/// <summary>
	///デバイスセット
	/// </summary>
	static void SetDevice(ID3D12Device* device) { BillboardSpriteModel::device = device; }
public:

	/// <summary>
	///バッファ設定、作成
	/// </summary>
	void CreateBuffers();

	/// <summary>
	///頂点生成
	/// </summary>
	void CreateVertex();

	/// <summary>
	///更新
	/// </summary>
	void Update();

	/// <summary>
	///描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///テクスチャの番号セット
	/// </summary>
	void SetTextureNum(int num) { textureNum = num; }
	
public:
	//頂点データ配列
	struct VertexPosNormalUv
	{
		XMFLOAT3 pos;	//座標
		XMFLOAT3 normal;	//法線ベクトル
		XMFLOAT2 uv;	//uv座標
		VertexPosNormalUv* parent = nullptr;	//uv座標
	};
	//頂点データ配列
	vector<VertexPosNormalUv>vertices;
	//頂点インデックス配列
	vector<unsigned short>indices;
private:
	//頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	//インデックスバッファ
	ComPtr<ID3D12Resource>indexBuff;
	//テクスチャバッファ
	ComPtr<ID3D12Resource>texBuff;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView = {};
	//インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW ibView = {};
	//アンビエント係数
	XMFLOAT3 ambient = { 1,1,1 };
	//ディフューズ係数
	XMFLOAT3 diffuse = { 1,1,1 };

	//SrvManger
	static SrvManager* srvManager;
	//デバイス
	static ID3D12Device* device;
	int textureNum = 0;
};

/**
 * @file ObjModel.h
 * @brief ObjファイルをDirectXで描画できるように変換して保持する
 * @author Asuma Syota
 * @date 2023/4
 */

#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <string>
#include <DirectXCommon.h>

using namespace Microsoft::WRL;
using namespace DirectX;

class ObjModel
{
public:
	// 頂点データ構造体
	struct VertexPosNormalUv
	{
		XMFLOAT3 pos; // xyz座標
		XMFLOAT3 normal; // 法線ベクトル
		XMFLOAT2 uv;  // uv座標
	};

	//// 定数バッファ用データ構造体B0
	//struct ConstBufferDataB0
	//{
	//	XMMATRIX mat;	// ３Ｄ変換行列
	//};
	//// 定数バッファ用データ構造体B1
	//struct ConstBufferDataB1
	//{
	//	XMFLOAT3 ambient;	//アンビエント係数
	//	float pad1;			//パディング
	//	XMFLOAT3 diffuse;	//ディフューズ係数
	//	float pad2;			//パディング
	//	XMFLOAT3 specular;	//スペキュラー係数
	//	float alpha;		//アルファ
	//};
	//マテリアル
	struct Material
	{
		std::string name;	//マテリアル名
		XMFLOAT3 ambient;	//アンビエント影響度
		XMFLOAT3 diffuse;	//ディフューズ影響度
		XMFLOAT3 specular;	//スペキュラー影響度
		float alpha;	//アルファ
		std::string textureFilename;	//テクスチャファイル名
		//コンストラクタ
		Material()
		{
			ambient = { 0.3f,0.3f,0.3f };
			diffuse = { 0.0f,0.0f,0.0f };
			specular = { 0.0f,0.0f,0.0f };
			alpha = 1.0f;
		}
	};
public:

	/// <summary>
	///インスタンス取得
	/// </summary>
	ObjModel* GetInstance();

	/// <summary>
	///初期化
	/// </summary>
	void Initialize(ID3D12Device* device, const std::string& filename, const std::string& resourcename);

	/// <summary>
	///頂点初期化
	/// </summary>
	void InitializeVertex(const std::string& filename);

	/// <summary>
	///デスクリプタ初期化
	/// </summary>
	void InitializeDesc();

	/// <summary>
	///シェーダ読み込
	/// </summary>
	void CompileShader(const wchar_t* file, const wchar_t* file2);	//シェーダ読み込み

	/// <summary>
	///マテリアル読み込み
	/// </summary>
	void LoadMaterial(const std::string& directoryPath, const std::string& filename);

	/// <summary>
	///テクスチャ読み込み
	/// </summary>
	void LoadTexture(const std::string& resourcename);

	/// <summary>
	///更新
	/// </summary>
	void Update();

	/// <summary>
	///マテリアル取得
	/// </summary>
	Material GetMaterial() { return material; };

	/// <summary>
	///デスクリプタヒープ取得
	/// </summary>
	ID3D12DescriptorHeap* GetDescHeap() { return descHeap.Get(); };

	/// <summary>
	///パイプライン取得
	/// </summary>
	ID3D12PipelineState* GetPipelinestate() { return pipelinestate.Get(); };

	/// <summary>
	///ルートシグネチャ取得
	/// </summary>
	ID3D12RootSignature* GetRootSignature() { return rootsignature.Get(); };

	/// <summary>
	///srv取得
	/// </summary>
	CD3DX12_GPU_DESCRIPTOR_HANDLE GetSrv() { return gpuDescHandleSRV; };

	/// <summary>
	///インデックスバッファ取得
	/// </summary>
	UINT GetIndicesSize() { return indices.size(); };

	/// <summary>
	///インデックスバッファビュー取得
	/// </summary>
	D3D12_INDEX_BUFFER_VIEW GetIbView() { return ibView; }

	/// <summary>
	///頂点バッファビュー取得
	/// </summary>
	D3D12_VERTEX_BUFFER_VIEW GetVbView() { return vbView; }

public:
	/*DirectXCommon* dx = nullptr;*/
	ID3D12Device* device;
	ComPtr<ID3D12Resource> constBuffMaterial;
public:
	D3D12_RECT scissorRect{};
	D3D12_VIEWPORT viewport{};

	D3D12_INDEX_BUFFER_VIEW ibView;
	D3D12_VERTEX_BUFFER_VIEW vbView;		//頂点バッファビュー
private:
	//頂点データ構造体
	struct Vertex
	{
		XMFLOAT3 pos;	//座標
		XMFLOAT3 normalize;	//法線ベクトル
		XMFLOAT2 uv;	//uv座標
		Vertex* parent = nullptr;
	};

	struct Indices
	{
		int num;
	};
	//Vertex関連
	size_t verticesCount = 24;
	std::vector<VertexPosNormalUv> vertices;	//外部に渡す用の頂点データ
	size_t indicesCount = 36;
	std::vector<unsigned short> indices;
	//インデックスバッファ関連
	ComPtr<ID3D12Resource> indexBuff;
	//頂点バッファ初期化
	ComPtr<ID3D12Resource> vertBuff;
	//ルートシグネチャ
	ComPtr<ID3D12RootSignature> rootsignature;
	//パイプライン
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};	//グラフィックスパイプライン
	//パイプラインステート
	ComPtr<ID3D12PipelineState> pipelinestate;
	//マテリアル
	Material material;
	// デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeap;
	// デスクリプタサイズ
	UINT descriptorHandleIncrementSize;
	// テクスチャバッファ
	ComPtr<ID3D12Resource> texbuff;
	// シェーダリソースビューのハンドル(CPU)
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// シェーダリソースビューのハンドル(CPU)
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
};

/**
 * @file ExplosionParticle1.h
 * @brief ゲームオブジェクト 爆発のパーティクル
 * @author Asuma Syota
 * @date 2023/4
 */

#pragma once

#include "TextureManager.h"
#include "vector"
#include "DirectXMath.h"
#include "DirectXCommon.h"
#include "DirectXTex.h"
#include "windows.h"
#include "wrl.h"
#include "d3d12.h"
#include "d3dx12.h"
#include "Camera.h"
#include "string.h"
#include "input.h"
#include "forward_list"

class ExplosionParticle1
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

public://サブクラス
	//定数バッファ用データ構造体
	struct ConstBufferDataTransform
	{
		XMMATRIX mat;
		XMMATRIX matBillboard;
	};

	//パーティクル1粒
	struct Particle
	{
		//座標
		XMFLOAT3 position = {};
		//元となる座標
		XMFLOAT3 basePosition = {};
		//速度
		XMFLOAT3 velocity = {};
		//加速度
		XMFLOAT3 accel = {};
		//現在フレーム
		int frame = 0;
		//終了フレーム
		int num_frame = 0;
		//スケール
		float scale = 1.0f;
		//初期値
		float startScale = 10.0f;
		//最終地
		float endScale = 0.0f;
	};

	//頂点データ配列
	struct VertexPos
	{
		XMFLOAT3 pos;	//座標
		float scale;
		XMFLOAT3 velocity;
	};

public:	//静的メンバ関数

	/// <summary>
	///SrvManagerセット
	/// </summary>
	static void SetSrvManager(SrvManager* srvManager) { ExplosionParticle1::srvManager = srvManager; }

	/// <summary>
	///デバイスセット
	/// </summary>
	static void SetDevice(ID3D12Device* device) { ExplosionParticle1::device = device; }

	/// <summary>
	///カメラセット
	/// </summary>
	static void SetCamera(Camera* camera) { ExplosionParticle1::camera = camera; }

	/// <summary>
	///パイプライン設定、作成
	/// </summary>
	static void CreateGraphicsPipeline();

public:

	/// <summary>
	///バッファ設定、作成
	/// </summary>
	void CreateBuffers();

	/// <summary>
	///更新
	/// </summary>
	void Update();

	/// <summary>
	///更新 パーティクル
	/// </summary>
	void UpdateParticle();

	/// <summary>
	///描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///パーティクルを追加
	/// </summary>
	void Add(XMFLOAT3 pos);

	/// <summary>
	///パーティクルを追加
	/// </summary>
	void AddParticle(int life, XMFLOAT3 position, XMFLOAT3 velocity, XMFLOAT3 accel, float startScale, float endScale);

	/// <summary>
	///テクスチャの番号セット
	/// </summary>
	void SetTextureNum(int num) { textureNum = num; }

public:	//静的メンバ変数

	//SrvManger
	static SrvManager* srvManager;
	//デバイス
	static ID3D12Device* device;
	//カメラ
	static Camera* camera;
	//頂点最大数
	static const int vertexCount = 4096;
	//火花1回に使う頂点数
	static const int sparkCount = 64;

private:
	//定数バッファ
	ComPtr<ID3D12Resource>constBuffTransform;
	//ルートシグネチャ
	static ComPtr<ID3D12RootSignature>rootsignature;
	//パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState>pipelinestate;

	//頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	//テクスチャバッファ
	ComPtr<ID3D12Resource>texBuff;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView = {};

	//パーティクル配列
	std::forward_list<Particle>particles;
	//テクスチャの番号
	int textureNum = 0;

	//爆発の範囲
	float explosionRange = 10.0;
};

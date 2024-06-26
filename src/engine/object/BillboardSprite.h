/**
 * @file BillboardSprite.h
 * @brief ビルボードのスプライト オブジェクト
 * 
 * @author Asuma Syota
 * @date 2023/4
 */

#pragma once
#include "BillboardSpriteModel.h"
#include "Camera.h"
#include "string.h"

class BillboardSprite
{
private:	//エイリアス
	//Microsoft::WRL::を省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public://サブクラス
	//定数バッファ用データ構造体
	struct ConstBufferDataTransform
	{
		XMMATRIX viewproj;
		XMMATRIX world;
		XMFLOAT3 cameraPos;
		XMFLOAT4 color;
	};
public:	//静的メンバ関数

	/// <summary>
	///デバイスセット
	/// </summary>
	static void SetDevice(ID3D12Device* device) { BillboardSprite::device = device; }

	/// <summary>
	///カメラセット
	/// </summary>
	static void SetCamera(Camera* camera) { BillboardSprite::camera = camera; }

private://静的メンバ変数
	static ID3D12Device* device;
	static Camera* camera;

public://メンバ関数

	/// <summary>
	///初期化
	/// </summary>
	void Initialize();

	/// <summary>
	///更新
	/// </summary>
	void Update();

	/// <summary>
	///ビルボード行列の更新
	/// </summary>
	void UpdateBillboard();

	/// <summary>
	///移動
	/// </summary>
	void Move();

	/// <summary>
	///描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///パイプライン設定、作成
	/// </summary>
	static void CreateGraphicsPipeline();

	/// <summary>
	///モデルセット
	/// </summary>
	void SetModel(BillboardSpriteModel* model) { this->model = model; }

	/// <summary>
	///座標セット
	/// </summary>
	void SetPosition(XMFLOAT3 pos) { position = pos; }

	/// <summary>
	///角度セット
	/// </summary>
	void SetRotation(XMFLOAT3 rot) { rotation = rot; }

	/// <summary>
	///スケールセット
	/// </summary>
	void SetScale(XMFLOAT3 sca) { scale = sca; }

	/// <summary>
	///色セット
	/// </summary>
	void SetColor(XMFLOAT4 color) { this->color = color; }

	/// <summary>
	///座標取得
	/// </summary>
	XMFLOAT3 GetPosition() { return position; }

	/// <summary>
	///角度取得
	/// </summary>
	XMFLOAT3 GetRotation() { return rotation; }
	
	/// <summary>
	///スケール取得
	/// </summary>
	XMFLOAT3 GetScale() { return scale; }

private://メンバ変数
	//定数バッファ
	ComPtr<ID3D12Resource>constBuffTransform;
	//ルートシグネチャ
	static ComPtr<ID3D12RootSignature>rootsignature;
	//パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState>pipelinestate;

private:
	//ローカルスケール
	XMFLOAT3 scale = { 1,1,1 };
	//X,Y,Z軸回りのローカル行列
	XMFLOAT3 rotation = { 0,0,0 };
	//ローカル座標
	XMFLOAT3 position = { 0,0,0 };
	//ローカルワールド変換行列
	XMMATRIX matWorld;
	//ビルボード行列
	XMMATRIX matBillboard = XMMatrixIdentity();
	//色
	XMFLOAT4 color = { 1,1,1,1 };
	//モデル
	BillboardSpriteModel* model = nullptr;
};

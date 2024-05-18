/**
 * @file ObjModel.h
 * @brief 変換したObjファイルを描画
 * @author Asuma Syota
 * @date 2023/4
 */

#pragma once
#include "Windows.h"
#include "d3d12.h"
#include "dxgi1_6.h"
#include "cassert"
#include "vector"
#include "string"
#include "DirectXMath.h"
#include "assert.h"
#include "DirectXTex.h"
#include "wrl.h"
#include "ObjModel.h"
#include "DirectXCommon.h"
#include "Camera.h"

using namespace DirectX;
using namespace Microsoft::WRL;

class ObjObject3D
{
public:

	/// <summary>
	///インスタンス取得
	/// </summary>
	ObjObject3D* GetInstance();

	//インストラクタ デストラクタ
	ObjObject3D();
	~ObjObject3D();

	/// <summary>
	///初期化
	/// </summary>
	void Initialize(ID3D12Device* device, ObjModel* model, Camera* camera);

	/// <summary>
	///更新
	/// </summary>
	void Update();

	/// <summary>
	///描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList, D3D12_VERTEX_BUFFER_VIEW& vbView, D3D12_INDEX_BUFFER_VIEW& ibView);

	/// <summary>
	///終了時処理
	/// </summary>
	void Delete();

	/// <summary>
	///座標取得
	/// </summary>
	XMFLOAT3 GetPosition() { return position; };

	/// <summary>
	///角度取得
	/// </summary>
	XMFLOAT3 GetRotation() { return rotation; };

	/// <summary>
	///スケール取得
	/// </summary>
	XMFLOAT3 GetScale() { return scale; };

	/// <summary>
	///座標セット
	/// </summary>
	void setPosition(XMFLOAT3 pos);

	/// <summary>
	///角度セット
	/// </summary>
	void setRotation(XMFLOAT3 rot);

	/// <summary>
	///スケールセット
	/// </summary>
	void setScale(XMFLOAT3 sca);

	/// <summary>
	///アルファ値セット
	/// </summary>
	void SetAlpha(float alpha);
		
	/// <summary>
	///更新 追従
	/// </summary>
	void HomingUpdate(XMFLOAT3 pos) { position = pos; }

private://静的メンバ変数
	static Camera* camera;

public:
	// 定数バッファ用データ構造体B0
	struct ConstBufferDataB0
	{
		XMMATRIX mat;	// ３Ｄ変換行列
		float alpha;	// 画像のアルファ
	};
	// 定数バッファ用データ構造体B1
	struct ConstBufferDataB1
	{
		XMFLOAT3 ambient;	//アンビエント係数
		float pad1;			//パディング
		XMFLOAT3 diffuse;	//ディフューズ係数
		float pad2;			//パディング
		XMFLOAT3 specular;	//スペキュラー係数
		float alpha;		//アルファ
	};
	//定数バッファ用データ構造体（3D変換行列）
	/*struct ConstBufferDataTransform
	{
		XMMATRIX mat;
	};*/
private:
	//定数バッファマップ
	/*ConstBufferDataTransform* constMapTransform;*/
	//モデル
	ObjModel* model = nullptr;
	//デバイス
	/*DirectXCommon* dx = nullptr;*/
	ID3D12Device* device;
	//定数バッファ
	ComPtr<ID3D12Resource> constBuffB0;
	ComPtr<ID3D12Resource> constBuffB1;
	// コマンドリスト
	ID3D12GraphicsCommandList* cmdList;
private:
	//アフィン変換情報
	XMFLOAT3 scale = { 1,1,1 };
	XMFLOAT3 rotation = { 0,0,0 };
	XMFLOAT3 position = { 0,0,0 };
	//ワールド変換行列
	XMMATRIX matWorld;
	//テクスチャのアルファ値
	float alpha = 1.0f;
};
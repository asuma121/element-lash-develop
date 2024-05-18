
//コロシアム 天球 地形 床
#pragma once
#include "ObjObject3D.h"
#include "vector"
#include "JSONLoader.h"

class Terrain
{
private:	//エイリアス
	//Microsoft::WRL::を省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:	//静的メンバ関数

	//カメラセット
	static void SetCamera(Camera* camera) { Terrain::camera = camera; }

public:	//メンバ関数

	//デストラクタ コンストラクタ
	Terrain() {};
	~Terrain();

	//初期化
	void Initialize(ID3D12Device* device);
	//更新
	void Update();
	//描画
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//描画
	void DrawTitle(ID3D12GraphicsCommandList* cmdList);
	//コライダー取得
	std::vector<JSONLoader::ColliderData> GetColliderData() { return colliderData; }
	//コライダーの数取得
	int GetColliderNum() { return colliderNum; }

private:	//静的メンバ変数
	
	static Camera* camera;

private:	//メンバ変数

	//天球モデル
	ObjModel* skySphereModel = nullptr;
	//天球オブジェクト
	ObjObject3D* skySphereObject = nullptr;
	//スケール
	XMFLOAT3 skySphereScale = { 50.0f,50.0f,50.0f };
	//座標
	XMFLOAT3 skySpherePos = { 0.0f,0.0f,0.0f };
	//角度
	XMFLOAT3 skySphereRotation = { 0.0f,0.0f,0.0f };

	//コロシアムモデル
	ObjModel* coliseumModel = nullptr;
	//コロシアムオブジェクト
	ObjObject3D* coliseumObject = nullptr;
	//スケール
	XMFLOAT3 coliseumScale = { 1.0f,1.0f,1.0f };
	//座標
	XMFLOAT3 coliseumPos = { 0.0f,0.0f,0.0f };
	//角度
	XMFLOAT3 coliseumRotation = { 0.0f,0.0f,0.0f };

	//コロシアムモデル2
	ObjModel* coliseum2Model = nullptr;
	//コロシアムオブジェクト2
	ObjObject3D* coliseum2Object = nullptr;
	//コロシアムの背面のアルファ
	float backAlpha = 0.5f;

	//柱モデル
	ObjModel* pillerModel = nullptr;
	
	//天球以外のオブジェクト
	std::vector<ObjObject3D*> objects;

	//判定を持つオブジェクトすべてのコライダーデータ
	std::vector<JSONLoader::ColliderData>colliderData;
	//コライダーの数
	int colliderNum = 0;

	//jsonから受け取ったオブジェクトのデータ
	std::vector<JSONLoader::ObjectData>objectData;
};
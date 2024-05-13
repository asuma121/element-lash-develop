#pragma once
#include "DirectXMath.h"
#include "BillboardSprite.h"
#include "Sprite.h"
#include "vector"
#include "Camera.h"

class LockOn
{
private:	//エイリアス
	//Microsoft::WRL::を省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:	//メンバ関数

	LockOn() {};
	~LockOn() {};

	/// <summary>
	///初期化
	/// </summary>
	void Initialize();

	/// <summary>
	///更新
	/// </summary>
	void Update();

	/// <summary>
	///敵の座標を追加
	/// </summary>
	void AddEnemyPos(XMFLOAT3 position);

	/// <summary>
	///描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///セッター
	/// </summary>
	void SetCamera(Camera* camera) { this->camera = camera; }

	/// <summary>
	///セッター
	/// </summary>
	void SetPlayerRotation(XMFLOAT3 rot) { this->playerRotation = rot; }

	/// <summary>
	///セッター
	/// </summary>
	void SetPlayerPosition(XMFLOAT3 pos) { this->playerPosition = pos; }

	/// <summary>
	///ロックオン対象を取得
	/// </summary>
	XMFLOAT3 GetTarget() { return target; }

	/// <summary>
	///ロックオンフラグを取得
	/// </summary>
	bool GetLockOnFlag() { return lockOnFlag; }

private:	//メンバ変数

	//カメラ
	Camera* camera = nullptr;

	//照準のビルボード
	BillboardSpriteModel* lockOnSpriteModel1 = nullptr;
	BillboardSprite* lockOnSprite1 = nullptr;

	//照準の画像
	Sprite* lockOnSprite2 = nullptr;
	//照準の画像のスプライトの大きさ、座標
	XMFLOAT2 lockOnSpriteScale = { 96.0f,96.0f };
	XMFLOAT2 lockOnSpritePos = { 1280.0f / 2.0f - lockOnSpriteScale.x / 2.0f,120.0f };

	//敵の座標
	std::vector<XMFLOAT3> enemyPosition;
	//プレイヤーの角度
	XMFLOAT3 playerRotation = { 0.0f,0.0f,0.0f };
	XMFLOAT3 playerPosition = { 0.0f,0.0f,0.0f };

	//ロックオン対象の座標
	XMFLOAT3 target = {0.0f,0.0f,0.0f};

	//判定の画角
	float hitAngle = 1.3f;
	//判定の長さ
	float hitLength = 350.0f;

	//ロックオンしているかのフラグ
	bool lockOnFlag = false;

	//デバッグ用
	float debugTimer[1] = { 0 };
	float debugTimer2[1] = { 0 };
	float debugTimer3[1] = { 0 };
	float debugNum[1] = { 0 };
	float debugTargetPos[3] = { 0,0,0 };
	float debugTargetFlag[1] = { 0 };
};
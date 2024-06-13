/**
 * @file Camera.h
 * @brief カメラ ゲームで使うビュー行列を管理
 * @author Asuma Syota
 * @date 2023/4
 */

#pragma once
#include "DirectXMath.h"
#include "KeyManager.h"
#include "JSONLoader.h"
#include "WinApp.h"
//#include "Player.h"
#define PI 3.14159265359

using namespace DirectX;

//クラスの前方宣言
class CameraState;
class Camera
{
public://静的メンバ変数

	/// <summary>
	///入力セット
	/// </summary>
	static void SetKeyManager(KeyManager* keyManager);

	//コンストラクタ デストラクタ
	Camera();
	~Camera();

public:

	/// <summary>
	///インスタンス取得
	/// </summary>
	static Camera* GetInstance();

	/// <summary>
	///初期化
	/// </summary>
	void Initialize();

	/// <summary>
	///更新
	/// </summary>
	void Update();

	/// <summary>
	///視点座標取得
	/// </summary>
	XMFLOAT3 GetEye();

	/// <summary>
	///注視点座標取得
	/// </summary>
	XMFLOAT3 GetTarget();

	/// <summary>
	///天井座標取得
	/// </summary>
	XMFLOAT3 GetUp();

	/// <summary>
	///角度取得
	/// </summary>
	XMFLOAT3 GetRotation();

	/// <summary>
	///射影変換取得
	/// </summary>
	XMMATRIX GetMatProjection();

	/// <summary>
	///ビュー変換行列取得
	/// </summary>
	XMMATRIX GetMatView();

	/// <summary>
	///ビュープロジェクション取得
	/// </summary>
	XMMATRIX GetMatViewProjection();

	/// <summary>
	///ビルボード用ビュー変換行列取得
	/// </summary>
	XMMATRIX GetMatBillboard();

	/// <summary>
	///ゲームシーンタイマーのセット
	/// </summary>
	void SetPhaseTimer(int timer);

	/// <summary>
	///オブジェクトの当たり判定セット
	/// /// </summary>
	void SetObjectCollider(std::vector<JSONLoader::ColliderData> colliderData);

	/// <summary>
	///プレイヤーの座標セット
	///</summary>
	void SetPlayerPos(XMFLOAT3 playerPos);

	/// <summary>
	///プレイヤーの角度セット
	///</summary>
	void SetPlayerRot(XMFLOAT3 playerRot);

	/// <summary>
	///敵の座標セット
	///</summary>
	void SetEnemyPos(XMFLOAT3 enemyPos);

	/// <summary>
	///ステートの変更 
	/// </summary>
	void ChangeState(CameraState* newState);

	//カメラのセット
	void SetTitle();
	void SetTutorial();
	void SetMovePhase();
	void SetClear();
	void SetFollowPlayer();

private:
	//入力
	//キーボード
	static KeyManager* keyManager;

	//カメラステート
	CameraState* cameraState = nullptr;
};

class CameraState
{
public:	//メンバ関数

	//仮想関数
	//コライダーの処理
	virtual void UpdateCollider() {};
	//ステートごとの動き
	virtual void Move() = 0;

	//通常関数
	//初期化
	void Initialize();
	//更新
	void Update();
	//角度更新
	void UpdateRotation();
	//ビルボード行列の更新>
	void BillboardUpdate();
	//カメラと壁との当たり判定
	void UpdateHitWall(JSONLoader::ColliderData objectColliderData);
	//シーンタイマーのセット
	void SetPhaseTimer(int timer) { phaseTimer = timer; }
	//オブジェクトの当たり判定セット
	void SetObjectCollider(std::vector<JSONLoader::ColliderData> colliderData) { objectColliderData = colliderData; };
	//プレイヤーの座標セット
	void SetPlayerPos(XMFLOAT3 playerPos) { this->playerPos = playerPos; };
	//プレイヤーの角度セット
	void SetPlayerRot(XMFLOAT3 playerRot) { this->playerRot = playerRot; };
	//敵の座標セット
	void SetEnemyPos(XMFLOAT3 enemyPos) { this->enemyPos = enemyPos; };
	//キーマネージャーセット
	static void SetKeyManager(KeyManager* keyManager) {CameraState::keyManager = keyManager;}

	//ゲッター
	//視点座標取得
	XMFLOAT3 GetEye() { return eye_; };
	//注視点座標取得
	XMFLOAT3 GetTarget() { return target_; };
	//天井座標取得
	XMFLOAT3 GetUp() { return up_; };
	//角度取得
	XMFLOAT3 GetRotation() { return rotation; }
	//射影変換取得//
	XMMATRIX GetMatProjection() { return matProjection_; };
	//ビュー変換行列取得
	XMMATRIX GetMatView() { return matView_; };
	//ビュープロジェクション取得
	XMMATRIX GetMatViewProjection() { return matView_ * matProjection_; };
	//ビルボード用ビュー変換行列取得
	XMMATRIX GetMatBillboard() { return matBillboard_; }

protected:	//静的メンバ変数

	//キーボード
	static KeyManager* keyManager;
	//射影変換
	static XMMATRIX matProjection_;
	//ビュー変換行列
	static XMMATRIX matView_;
	//ビルボード行列
	static XMMATRIX matBillboard_;
	//視点座標、注視点、上方向、角度
	static XMFLOAT3 eye_;
	static XMFLOAT3 target_;
	static XMFLOAT3 up_;
	static XMFLOAT3 rotation;

	//コライダーデータ
	static JSONLoader::ColliderData colliderData;

protected:	//メンバ変数

	//プレイヤーの座標、角度
	XMFLOAT3 playerPos = { 0.0f,0.0f,0.0f };
	XMFLOAT3 playerRot = { 0.0f,0.0f,0.0f };

	//敵の座標
	XMFLOAT3 enemyPos = { 0.0f,0.0f,0.0f };

	//ターゲットまでの距離
	float DebugTargetDistance = 40.0f;
	//加算用
	float DebugChangeRot = (float)PI;
	float DebugChangeRot2 = (float)PI * (13.0f / 40.0f);
	float maxDebugChangeRot2 = (float)PI * (19.0f / 40.0f);
	float minDebugChangeRot2 = (float)PI * (8.0f / 40.0f);
	float DebugChangeDistance = 0.0f;

	XMFLOAT3 colliderScale = { 0.00001f,0.00001f,0.00001f };
	XMFLOAT3 colliderRotation = { 0.0f,0.0f,0.0f };
	//オブジェクトのコライダーデータ
	std::vector<JSONLoader::ColliderData> objectColliderData;
	//オブジェクト衝突時の押し戻し
	float knockBackSpeed = 0.1f;

	//プレイヤー
	//ターゲットまでの距離
	float playerTargetDistance = 50.0f;
	//加算用
	float playerChangeRot = (float)PI;
	float playerChangeRot2 = 0.5f;
	float playerChangeDistance = 0.0f;
	float playerAddRot = 0.0f;
	float rotSpeed = (float)PI * 1.5f / 180.0f;

	//シーン遷移用
	XMFLOAT3 originalPlayerPos = { 0.0f,0.0f,0.0f };
	XMFLOAT3 originalPlayerRot = { 0.0f,0.0f,0.0f };

	//ゲームシーンタイマー
	int phaseTimer = 0;

	//フェーズ移動の注視点、座標
	XMFLOAT3 movePhaseTarget = { -8.0f, 26.0f, 0.0f };
	XMFLOAT3 movePhaseEye = { 37.0f, 20.0f, -100.0f };

	XMFLOAT3 clearAddPos = { 0.0f,60.0f,0.0f };
};
/**
 * @file Camera.h
 * @brief カメラ ゲームで使うビュー行列を管理
 * @author Asuma Syota
 * @date 2023/4
 */

#pragma once
#include "DirectXMath.h"
#include "KeyManager.h"
#include "WinApp.h"
//#include "Player.h"
#define PI 3.14159265359

using namespace DirectX;

class Camera
{
public://静的メンバ変数

	/// <summary>
	///入力セット
	/// </summary>
	static void SetKeyManager(KeyManager* keyManager) { Camera::keyManager = keyManager; }

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
	///タイトルの更新
	/// </summary>
	void TitleUpdate(XMFLOAT3 playerPos, XMFLOAT3 playerRot, float timer);

	/// <summary>
	///プレイヤー追尾の更新
	/// </summary>
	void UpdatePlayer(XMFLOAT3 playerPos, XMFLOAT3 playerRot);

	/// <summary>
	///プレイヤー追尾の更新
	/// </summary>
	void UpdateMovePhase();

	/// <summary>
	///チュートリアルの更新
	/// </summary>
	void UpdateTutorial(int tutorialTimer);

	/// <summary>
	///クリア画面の更新
	/// </summary>
	void UpdateClear(XMFLOAT3 enemyPos, float timer);

	/// <summary>
	///ビルボード行列の更新
	/// </summary>
	void BillboardUpdate();

	/// <summary>
	///注視点セット
	/// </summary>
	void SetTarget(XMFLOAT3 pos);

	/// <summary>
	///視点座標セット
	/// </summary>
	void SetEye(XMFLOAT3 pos);

	/// <summary>
	///視点座標取得
	/// </summary>
	XMFLOAT3 GetEye() { return eye_; };

	/// <summary>
	///注視点座標取得
	/// </summary>
	XMFLOAT3 GetTarget() { return target_; };

	/// <summary>
	///天井座標取得
	/// </summary>
	XMFLOAT3 GetUp() { return up_; };

	/// <summary>
	///角度取得
	/// </summary>
	XMFLOAT3 GetRotation() { return rotation; }

	/// <summary>
	///射影変換取得
	/// </summary>
	XMMATRIX GetMatProjection() { return matProjection_; };

	/// <summary>
	///ビュー変換行列取得
	/// </summary>
	XMMATRIX GetMatView() { return matView_; };

	/// <summary>
	///ビュープロジェクション取得
	/// </summary>
	XMMATRIX GetMatViewProjection() { return matView_ * matProjection_; };

	/// <summary>
	///ビルボード用ビュー変換行列取得
	/// </summary>
	XMMATRIX GetMatBillboard() { return matBillboard_; }

	/// <summary>
	///デバッグフラグのセット
	/// </summary>
	void SetDebugFlag(bool flag) { debugFlag = flag; }

	/// <summary>
	///ゲームシーンタイマーのセット
	/// </summary>
	void SetPhaseTimer(int timer) { phaseTimer = timer; }

private:
	//入力
	//キーボード
	static KeyManager* keyManager;
	//射影変換
	XMMATRIX matProjection_ = XMMatrixIdentity();
	//ビュー変換行列
	XMMATRIX matView_ = XMMatrixIdentity();
	XMFLOAT3 eye_ = { 0, 20, -100 };
	XMFLOAT3 target_ = { 0, 0, 0 };
	XMFLOAT3 up_ = { 0, 1, 0 };
	XMFLOAT3 debugEye_ = { 0, 100, -100 };
	XMFLOAT3 debugTarget_ = { 0, 0, 0 };
	XMFLOAT3 debugUp_ = { 0, 100, 0 };
	//ビルボード行列
	XMMATRIX matBillboard_ = XMMatrixIdentity();
	//カメラの向いてる角度
	XMFLOAT3 rotation = { 0.0f,0.0f,0.0f };

	//ターゲットまでの距離
	float DebugTargetDistance = 40.0f;
	//加算用
	float DebugChangeRot = (float)PI;
	float DebugChangeRot2 = PI * (13.0f / 40.0f);
	float maxDebugChangeRot2 = PI * (19.0f / 40.0f);
	float minDebugChangeRot2 = PI * (8.0f / 40.0f);
	float DebugChangeDistance = 0.0f;

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

	//デバッグ用
	bool debugFlag = false;
	float debugEye[3] = { 0.0f,0.0f,0.0f };
	float debugTarget[3] = { 0.0f,0.0f,0.0f };

	XMFLOAT3 clearAddPos = { 0.0f,60.0f,0.0f };
};
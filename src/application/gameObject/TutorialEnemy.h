/**
 * @file TutorialEnemy.h
 * @brief ゲームオブジェクト 敵
 * @author Asuma Syota
 * @date 2023/4
 */

#pragma once
#include "DirectXMath.h"
#include "FbxObject3D.h"
#include "Sprite.h"
#include "JSONLoader.h"

class TutorialEnemy
{
private:	//エイリアス
	//Microsoft::WRL::を省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public://メンバ関数

	/// <summary>
	///カメラセット
	/// </summary>
	static void SetCamera(Camera* camera) { TutorialEnemy::camera = camera; }

	/// <summary>
	/// インストラクタ デストラクタ
	/// </summary>
	TutorialEnemy() {};
	~TutorialEnemy();

	/// <summary>
	///初期化
	/// </summary>
	void Initialize();

	/// <summary>
	///更新
	/// </summary>
	void UpdateTutorial();

	/// <summary>
	///更新
	/// </summary>
	void UpdateGame();

	/// <summary>
	///更新
	/// </summary>
	void UpdateMovePhase();

	/// <summary>
	///チュートリアル専用のステート更新
	/// </summary>
	void UpdateStateTutorial();

	/// <summary>
	///オブジェクト更新
	/// </summary>
	void UpdateObject();

	/// <summary>
	///スプライト更新
	/// </summary>
	void UpdateSprite();

	/// <summary>
	///コライダー
	/// </summary>
	void UpdateCollider();

	/// <summary>
	///コライダー
	/// </summary>
	void UpdateObjectCollider();

	/// <summary>
	///ダメージ系全般
	/// </summary>
	void UpdateDamage();

	/// <summary>
	///ダメージ系全般
	/// </summary>
	void UpdateDamageTutorial();

	/// <summary>
	///描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///ライト視点描画
	/// </summary>
	void DrawLightView(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///スプライト描画
	/// </summary>
	void DrawSprite(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///挙動全般
	/// </summary>
	void MoveGame();

	/// <summary>
	///挙動全般
	/// </summary>
	void MoveMovePhase();

	/// <summary>
	///ステータスマネージャー
	/// </summary>
	void StatusManager();

	/// <summary>
	///座標セット
	/// </summary>
	void SetPosition(XMFLOAT3 position) { this->position = position; };

	/// <summary>
	///ダッシュにセット
	/// </summary>
	void SetDash();

	/// <summary>
	///ダウンにセット
	/// </summary>
	void SetDown();

	/// <summary>
	///立つにセット
	/// </summary>
	void SetStand();

	/// <summary>
	///チュートリアルシーンセット
	/// </summary>
	void SetTutorial();

	/// <summary>
	///ゲームシーンセット
	/// </summary>
	void SetGameScene();

	/// <summary>
	///フェーズ移動セット
	/// </summary>
	void SetMovePhase();

	/// <summary>
	///プレイヤーの座標セット
	/// </summary>
	void SetPlayerPos(XMFLOAT3 pos) { playerPos = pos; };

	/// <summary>
	///指定した座標にセット
	/// </summary>
	void AddEnemy(XMFLOAT3 pos);

	/// <summary>
	///指定した座標にセット
	/// </summary>
	void AddEnemyTutorialScene(XMFLOAT3 pos);

	/// <summary>
	///指定した座標にセット
	/// </summary>
	void AddEnemyGameScene(XMFLOAT3 pos);

	/// <summary>
	///指定した座標にセット
	/// </summary>
	void AddEnemyMovePhase(XMFLOAT3 pos);

	/// <summary>
	///リセット
	/// </summary>
	void Reset();

	/// <summary>
	///時機の弾被弾時
	/// </summary>
	void HitBullet1();

	/// <summary>
	///雷被弾時
	/// </summary>
	void HitElec() { hitElec = true; };

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

	/// <summary>
	///高さ取得
	/// </summary>
	XMFLOAT3 GetAddPos() { return addPos; }

	/// <summary>
	///コライダー取得
	/// </summary>
	JSONLoader::ColliderData GetColliderData() { return colliderData; }

	/// <summary>
	/// チュートリアルのフラグをセットする
	/// </summary>
	void SetTutorialFlag(int tutorialFlag) { this->tutorialFlag = tutorialFlag; };

	/// <summary>
	///死亡フラグ取得
	/// </summary>
	bool GetIsDead() { return isDead3; }

	/// <summary>
	///プレイヤーとヒット時
	/// </summary>
	void SetHitPlayer();

	bool GetCallFlag();

	/// <summary>
	///チュートリアルシーン倒れた時のフラグ
	/// </summary>
	bool GetTutorialDownFlag() { return downFlag; };

	/// <summary>
	///チュートリアルシーンダッシュをセットするフラグ
	/// </summary>
	void SetTutorialDashFlag() { this->tutorialDashFlag = true; };

	/// <summary>
	///オブジェクトの当たり判定セット
	/// </summary>
	void SetObjectCollider(std::vector<JSONLoader::ColliderData> colliderData) {
		this->objectColliderData = colliderData;};

	/// <summary>
	//壁との当たり判定処理
	/// <summary>
	void UpdateHitWall(JSONLoader::ColliderData objectColliderData);

	/// <summary>
	//柱との当たり判定処理
	/// <summary>
	void UpdateHitPiller(JSONLoader::ColliderData objectColliderData);

	/// <summary>
	//柱との当たり判定処理
	/// <summary>
	void UpdateHitObject();

	//チュートリアル12用の更新
	void UpdateTutorial12();

	//静的メンバ変数
private:
	//カメラ
	static Camera* camera;

	//メンバ変数
public:

	//コライダーデータ
	JSONLoader::ColliderData colliderData;

	//オブジェクトのコライダーデータ
	std::vector<JSONLoader::ColliderData> objectColliderData;

	//オブジェクト
	FbxObject3D* object = nullptr;
	//モデル
	FbxModel* modelDash = nullptr;
	FbxModel* modelDown = nullptr;
	FbxModel* modelStand= nullptr;

	//スプライト
	std::unique_ptr<Sprite>hpBar1;	//HPバーの枠
	std::unique_ptr<Sprite>hpBar2;	//HPバー
	std::unique_ptr<Sprite>hpBar3;	//現在のHPのとこにつけるやつ
	std::unique_ptr<Sprite>hpBar4;	//BOSS HPのテキスト

	//チュートリアルのフラグ
	int tutorialFlag = 0;
	//チュートリアルのダッシュのフラグ
	bool tutorialDashFlag = false;
	//チュートリアルの転んだフラグ
	bool downFlag = false;

	//変形行列
	//平行移動
	XMFLOAT3 position = { 0.0f,0.0f,30.0f };
	//回転
	XMFLOAT3 rotation = { 0.0f,0.0f,0.0f };
	//サイズ
	XMFLOAT3 scale = { 1.0f,1.0f,1.0f };

	//コライダーのサイズ
	XMFLOAT3 colliderScale = { 20.0f,10.0f,10.0f };

	//HP
	float maxHP = 20;
	float HP = maxHP;

	//スプライト用
	//HPバー1
	XMFLOAT2 hpBar1Pos = { 320.0f,-15.0f };
	XMFLOAT2 hpBar1Scale = { 640.0f,96.0f };
	//HPバー2
	XMFLOAT2 hpBar2Pos = { 349.0f,26.0f };
	XMFLOAT2 hpBar2OriginalScale = { 605.0f,15.0f };
	XMFLOAT2 hpBar2Scale = hpBar2OriginalScale;
	//HPバー3
	XMFLOAT2 hpBar3OriginalPos = { 938.0f,25.0f };
	XMFLOAT2 hpBar3Pos = hpBar3OriginalPos;
	XMFLOAT2 hpBar3Scale = { 16.0f,16.0f };
	//Hpバー4
	XMFLOAT2 hpBar4Pos = { 230.0f,25.0f };
	XMFLOAT2 hpBar4Scale = { 96.0f,16.0f };

	//被弾
	bool hitFlag1 = false;
	bool hitElec = false;

	//死亡フラグ
	bool isDead1 = true;
	bool isDead2 = true;
	bool isDead3 = true;

	//高さ
	XMFLOAT3 addPos = { 0.0f,15.0f,0.0f };

	//プレイヤーの座標
	XMFLOAT3 playerPos = { 0.0f,0.0f,0.0f };
	//移動攻撃のスピード
	float speed = 0.7f;

	//ダウンのアニメーション
	int deadTime = 130;
	int deadTimer = 0;

	//呼び出しに入るか
	float callTimer = 0.0f;
	float callTime = 500.0f;
	bool callFlag = false;

	//オブジェクトと衝突フラグ
	bool hitObjectFlag = false;

	//オブジェクト衝突時の押し戻し
	float knockBackSpeed = 0.001f;

	//転ぶ状態のアニメーションのフレーム
	float frameFallDownEnemy = 125.0f - 10.0f;
	int tutorial12Timer = 0;
};
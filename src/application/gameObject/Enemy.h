/**
 * @file Enemy.h
 * @brief ゲームオブジェクト 敵
 * @author Asuma Syota
 * @date 2023/4
 */

/*
	フェーズ1
	攻撃前兆→ダッシュ→攻撃前兆→弾の繰り返し
	フェーズ2
	攻撃全前兆→敵呼び出し→ダッシュ→攻撃前兆→弾の繰り返し
*/

#pragma once
#include "DirectXMath.h"
#include "FbxObject3D.h"
#include "Sprite.h"
#include "EnemyBullet.h"
#include "JSONLoader.h"
#include "ElecParticle.h"
#include "ExplosionParticle1.h"
#include "ExplosionParticle2.h"

class EnemyState;	//クラスの前方宣言
class Enemy
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
	static void SetCamera(Camera* camera) { Enemy::camera = camera; }

	/// <summary>
	/// インストラクタ デストラクタ
	/// </summary>
	Enemy();
	~Enemy();

	/// <summary>
	///初期化
	/// </summary>
	void Initialize();

	/// <summary>
	///更新
	/// </summary>
	void UpdateGame1();

	/// <summary>
	///更新
	/// </summary>
	void UpdateGame2();

	/// <summary>
	///更新
	/// </summary>
	void UpdateMovePhase();

	/// <summary>
	///チュートリアルの時の更新
	/// </summary>
	void UpdateTutorial(int tutorialTimer);

	/// <summary>
	///チュートリアルの時の更新
	/// </summary>
	void UpdateClear(int clearTimer);

	/// <summary>
	///ステート更新
	/// </summary>
	void UpdateStateGame();

	/// <summary>
	///ステート更新 チュートリアル用
	/// </summary>
	void UpdateStateTutorial();

	/// <summary>
	///ステート更新 ゲーム用
	/// </summary>
	void UpdateStateMovePhase();

	/// <summary>
	///ステート更新 クリア用
	/// </summary>
	void UpdateStateClear();

	/// <summary>
	///描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///ライト視点描画
	/// </summary>
	void DrawLightView(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///パーティクル描画
	/// </summary>
	void DrawParticle(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///ダメージ系全般
	/// </summary>
	void UpdateDamage();

	/// <summary>
	///コライダー
	/// </summary>
	void UpdateCollider();

	/// <summary>
	///ステータスマネージャー
	/// </summary>
	void StatusManagerTutorial(int tutorialTimer);

	/// <summary>
	///srvセット
	/// </summary>
	void SetSRV(ID3D12DescriptorHeap* SRV);

	/// <summary>
	///プレイヤーの座標セット
	/// </summary>
	void SetPlayerPos(XMFLOAT3 playerPos);

	/// <summary>
	///タイマーセット
	/// </summary>
	void SetPhaseTimer(int phaseTimer);

	/// <summary>
	///オブジェクトの当たり判定セット
	/// </summary>
	void SetObjectCollider(std::vector<JSONLoader::ColliderData> colliderData);

	/// <summary>
	///プレイヤーにダッシュを当てたら
	/// </summary>
	void SetHitPlayer();

	/// <summary>
	///時機の弾被弾時
	/// </summary>
	void HitBullet1();

	/// <summary>
	///リセット
	/// </summary>
	void Reset();

	/// <summary>
	///チュートリアルシーンに移る
	/// </summary>
	void SetTutorial();

	/// <summary>
	///ゲームシーンに移る
	/// </summary>
	void SetGameScene();

	/// <summary>
	///ゲームシーンに移る
	/// </summary>
	void SetMovePhase();

	/// <summary>
	///クリアシーンに移る
	/// </summary>
	void SetClear();

	/// <summary>
	///座標取得
	/// </summary>
	XMFLOAT3 GetPosition();

	/// <summary>
	///角度取得
	/// </summary>
	XMFLOAT3 GetRotation();

	/// <summary>
	///スケール取得
	/// </summary>
	XMFLOAT3 GetScale();

	/// <summary>
	///高さ取得
	/// </summary>
	XMFLOAT3 GetAddPos() { return addPos; }

	/// <summary>
	///コライダー取得
	/// </summary>
	JSONLoader::ColliderData GetColliderData();

	/// <summary>
	///弾のコライダー取得
	/// </summary>
	JSONLoader::ColliderData GetBulletColliderData(int num);

	/// <summary>
	///弾のコライダー取得
	/// </summary>
	size_t GetBulletNum();

	/// <summary>
	///敵呼び出しフラグ取得
	/// </summary>
	bool GetCallEnemyFlag();

	// <summary>
	///HP取得
	/// </summary>
	int GetHP() { return HP; };

	// <summary>
	///最大HP取得
	/// </summary>
	int GetMaxHP() { return maxHP; };

	/// <summary>
	///敵呼び出し座標取得
	/// </summary>
	XMFLOAT3 GetCallEnemyPos(); 

	/// <summary>
	///死亡フラグ取得
	/// </summary>
	bool GetIsDead() { return isDead; }

	/// <summary>
	///雷被弾時
	/// </summary>
	void HitElec() { hitElec = true; };

	/// <summary>
	///状態変更
	/// </summary>
	void ChangeState(EnemyState* newState);

	/// <summary>
	///敵呼び出しフラグを立てる
	/// </summary>
	void SetCallMiniEnemy();

	//静的メンバ変数
private:
	//カメラ
	static Camera* camera;

	//メンバ変数
private:

	//ステート
	EnemyState* enemyState = nullptr;

	//状態遷移用タイマー
	float statusTimer = 0.0f;

	//フェーズ1の攻撃遷移用フラグ
	bool dashFlag = true;
	bool attack1Flag = false;

	//フェーズ2の攻撃遷移用フラグ
	bool phase2CallEnemyFlag = true;
	bool phase2DashFlag = false;
	bool phase2Attack1Flag = false;

	//プレイヤーにダッシュを当てたフラグ
	bool hitPlayer = false;

	//被弾
	bool HitFlag1 = false;
	bool hitElec = false;

	//挙動関連

	//落下
	//落下ベクトル
	XMFLOAT3 fallVelocity = { 0.0f,0.0f,0.0f };
	//落下タイマー
	float fallTimer = 0.0f;
	//落下最大値までにかかる時間
	float fallTime = 1.0f;
	//1フレームあたりの落下量
	float fallFrame = 1.0f / 60.0f;

	//ジャンプ
	float jumpHeight = 0.4;

	//スピード
	float speed = 0.15f;
	float walkSpeed = 1.0f;

	//HP
	float maxHP = 100;
	float HP = maxHP;

	//デバッグ用
	float bulletPos[3] = { 0.0f,0.0f,0.0f };

	//一度に発射する弾の数
	int bulletVol = 5;
	//弾の時間差
	float bulletTimeLag = 30.0f;
	//弾の大きさ
	XMFLOAT3 bulletScale = { 3.0f,3.0f,3.0f };
	//弾の角度
	XMFLOAT3 bulletLastScale = { 3.0f,3.0f,3.0f };

	//ダッシュ用のベクトル
	XMFLOAT3 dashVector = { 0.0f,0.0f,0.0f };
	float dashSpeed = 1.4f;

	//imgui用
	int debugNum[1] = { 0};
	float pos2[2] = { 605.0f,15.0f };
	float pos3[2] = { 938.0f,25.0f };
	float pos4[2] = { 230.0f,25.0f };

	//死亡フラグ
	bool isDead = false;

	//高さ
	XMFLOAT3 addPos = { 0.0f,50.0f,0.0f };
};

class EnemyState
{
public:	//静的メンバ関数

	//静的メンバ変数初期化
	static void StaticInitialize();

public:	//メンバ関数

	//コンストラクタ デストラクタ
	EnemyState() {};
	~EnemyState() {};

	//仮想関数
	//各ステート初期化
	virtual void Initialize() = 0;
	//攻撃処理
	virtual void UpdateAttack() {};
	//攻撃処理
	virtual void UpdateAttackMovePhase() {};
	//移動処理
	virtual void Move() = 0;
	//ステートの変更
	virtual void UpdateState(Enemy* enemy) = 0;
	//ステートの変更 チュートリアルシーン
	virtual void UpdateStateTutorial(Enemy* enemy) {};
	//ステートの変更 フェーズ移動
	virtual void UpdateStateMovePhase(Enemy* enemy) {};
	//ステートの変更 クリアシーン
	virtual void UpdateStateClear(Enemy* enemy) {};
	//クリア専用更新
	virtual void UpdateParticleClear() {};
	//描画
	virtual void Draw(ID3D12GraphicsCommandList* cmdList) = 0;
	//ライト目線描画
	virtual void DrawLightView(ID3D12GraphicsCommandList* cmdList) = 0;
	//SRVセット
	virtual void SetSRV(ID3D12DescriptorHeap* SRV) = 0;
	//オブジェクトの更新
	virtual void UpdateObject() = 0;
	//壁との当たり判定処理 歩き、ダッシュのみ 
	virtual void UpdateHitWall(JSONLoader::ColliderData objectColliderData) {};
	//柱との当たり判定処理 歩き、ダッシュのみ
	virtual void UpdateHitPiller(JSONLoader::ColliderData objectColliderData){};

	//通常関数
	//パーティクル描画
	void DrawParticle(ID3D12GraphicsCommandList* cmdList);
	//更新
	void Update();
	//フェーズ移動用の更新
	void UpdateMovePhase();
	//チュートリアル用の更新
	void UpdateTutorial(int timer);
	//クリア用の更新
	void UpdateClear(int timer);
	//チュートリアルの動き
	void MoveTutorail();
	//判定更新
	void UpdateCollider();
	//オブジェクトの当たり判定セット
	void SetObjectCollider(std::vector<JSONLoader::ColliderData> colliderData) { objectColliderData = colliderData; };
	//プレイヤーの座標セット
	void SetPlayerPos(XMFLOAT3 playerPos) { EnemyState::playerPos = playerPos; };
	//プレイヤーに当たったら
	void SetHitPlayer(bool hitPlayerFlag) { EnemyState::hitPlayerFlag = hitPlayerFlag; };
	//タイマーセット
	void SetPhaseTimer(int phaseTimer) { EnemyState::phaseTimer = phaseTimer; }
	//敵呼び出しフラグを呼び出す
	void SetCallMiniEnemy() { nextCallMiniEnemy = true; }

	//座標取得
	XMFLOAT3 GetPosition() { return position; }
	//角度取得
	XMFLOAT3 GetRotation() { return rotation; }
	//スケール取得
	XMFLOAT3 GetScale() { return scale; }
	//コライダー取得
	JSONLoader::ColliderData GetColliderData() { return colliderData; }
	//弾のコライダー取得
	JSONLoader::ColliderData GetBullet1ColliderData(int num) { return bullet->GetColliderData(num); }
	//弾のコライダー取得
	size_t GetBullet1Num() { return  bullet->GetBulletNum(); }
	//リセット
	void Reset();
	//チュートリアルシーンに移る際に呼び出す
	void SetTutorial(Enemy* enemy);
	//ゲームシーンに移る際に呼び出す
	void SetGame(Enemy* enemy);
	//クリアシーンに移る際に呼び出す
	void SetClear(Enemy* enemy);
	//ゲームシーンに移る際に呼び出す
	void SetMovePhase(Enemy* enemy);
	bool GetCallEnemyFlag() { return callEnemyFlag; };
	XMFLOAT3 GetCallEnemyPos() { return callEnemyPos; };

protected:	//静的メンバ変数

	//立っている状態のオブジェクト
	static FbxObject3D* objectStand;
	//立っている状態のモデル
	static FbxModel* modelStand;

	//歩いている状態のオブジェクト
	static FbxObject3D* objectWalk;
	//歩いている状態のモデル
	static FbxModel* modelWalk;

	//攻撃1状態のオブジェクト
	static FbxObject3D* objectAttack1;
	//攻撃1状態のモデル
	static FbxModel* modelAttack1;

	//攻撃1前兆のオブジェクト
	static FbxObject3D* objectAttackOmen1;
	//攻撃1前兆のモデル
	static FbxModel* modelAttackOmen1;

	//ダッシュのオブジェクト
	static FbxObject3D* objectDash;
	//ダッシュのモデル
	static FbxModel* modelDash;

	//敵呼び出しのオブジェクト
	static FbxObject3D* objectCallMiniEnemy;

	//転ぶオブジェクト
	static FbxObject3D* objectFallDown;
	//転ぶモデル
	static FbxModel* modelFallDown;

	//立ち上がるオブジェクト
	static FbxObject3D* objectGetUp;
	//立ち上がるモデル
	static FbxModel* modelGetUp;

	//コライダーデータ
	static JSONLoader::ColliderData colliderData;

	//敵の弾
	static EnemyBullet* bullet;

	//雷パーティクル 敵呼び出しで描画
	static ElecParticle* elecParticle;

	//爆発パーティクル 敵呼び出しで描画
	static ExplosionParticle1* explosionParticle1;
	static ExplosionParticle2* explosionParticle2;

	//変形行列
	//平行移動
	static XMFLOAT3 position;
	//回転
	static XMFLOAT3 rotation;
	//サイズ
	static XMFLOAT3 scale;

	//次の行動を決めるフラグ
	static bool nextCallMiniEnemy ;
	static bool nextDash ;
	static bool nextAttack01;

protected:	//メンバ変数

	//オブジェクトごとのタイマー
	int objectTimer = 0;
	//オブジェクトに時間の設定がある場合
	int objectTime = 0;
	//オブジェクトごとに時間の設定があるか
	bool objectTimeFlag = false;

	//フェーズごとのタイマー
	int phaseTimer = 0;

	//プレイヤーの座標
	XMFLOAT3 playerPos = { 0.0f,0.0f,0.0f };

	//攻撃1状態のアニメーションのフレーム
	float frameStand = 250.0f;
	//攻撃1状態のアニメーションのフレーム
	float frameWalk = 82.0f * 3.0f;
	//攻撃1状態のアニメーションのフレーム
	float frameAttack1 = 190.0f;
	//攻撃1前兆状態のアニメーションのフレーム
	float frameAttackOmen1 = 143.0f;
	//ダッシュ状態のアニメーションのフレーム
	float frameDash = 53.0f * 4;
	//敵を呼び出すフレーム
	float frameCallMiniEnemy2 = 40.0f;
	//敵呼び出し状態のアニメーションのフレーム
	float frameCallMiniEnemy = 190.0f;
	//転ぶ状態のアニメーションのフレーム
	float frameFallDownEnemy = 250.0f;
	//立ち上がる状態のアニメーションのフレーム
	float frameGetUpEnemy = 163.0f;
	//柱の判定を取らない時間
	float frameNoPillerHit = 90.0f;

	//一度に出す雷パーティクルの数
	int elecVol = 5;
	//雷パーティクルを出すフレームの間隔
	int elecInterval = 7;
	//雷を出しているフレーム数
	int elecFrame = 40.0f;
	//でかい雷のスケール
	float elecStartSlace1 = 10.0f;
	float elecEndSlace1 = 10.0f;
	//細かい雷のスケール
	float elecStartSlace2 = 0.7f;
	float elecEndSlace2 = 0.1f;
	//雷の横揺れの強さ
	float elecStrength = 1.1f;

	//弾を出す位置
	XMFLOAT3 bulletAddPos = { 30.0f, 50.0f, -50.0f };
	//一度に発射する弾の数
	int bulletVol = 10;
	//弾の時間差
	float bulletTimeLag = 15.0f;
	//弾の大きさ
	XMFLOAT3 bulletScale = { 5.0f,5.0f,5.0f };
	//弾の角度
	XMFLOAT3 bulletLastScale = { 3.0f,3.0f,3.0f };

	//歩くスピード
	float walkSpeed = 1.0f;
	//ダッシュのスピード
	float dashSpeed = 1.2f;
	//ダッシュ攻撃に移らない範囲
	float dashLength = 50.0f;

	//プレイヤーにダッシュを当てたフラグ
	bool hitPlayerFlag = false;

	//敵呼び出しフラグ
	bool callEnemyFlag = false;
	//呼び出す敵の座標
	XMFLOAT3 callEnemyPos = { 0.0f,0.0f,0.0f };
	XMFLOAT3 callEnemyPos1 = { 0.0f,0.0f,40.0f };	//フェーズ移動用

	//コライダー
	//コライダーの大きさ
	XMFLOAT3 colliderScale = { 30.0f,30.0f,30.0f };

	//オブジェクトのコライダーデータ
	std::vector<JSONLoader::ColliderData> objectColliderData;

	//チュートリアルの座標
	XMFLOAT3 tutorialPos = { 0.0f,0.0f,0.0f };
	//チュートリアル用のタイマー
	int tutorialTimer = 0;
	//チュートリアル 立ちアニメーションのフレーム
	int tutorialStandFrame = 180;

	XMFLOAT3 addElecPos1 = XMFLOAT3(150.0f, 500.0f, 150.0f);
	XMFLOAT3 addElecPos2 = XMFLOAT3(40.0f, 500.0f, 40.0f);

	//クリアのタイマー
	int clearTimer = 0;

	//爆発用
	float explosionTime = 5.0f;
	float explosionTimer = explosionTime;
};
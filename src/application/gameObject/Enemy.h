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

private:

	enum Status	//敵の状態
	{
		Stand,
		Walk,
		Attack1,
		AttackOmen1,
		Dash,
		CallMiniEnemy,
	};

public://メンバ関数

	/// <summary>
	///カメラセット
	/// </summary>
	static void SetCamera(Camera* camera) { Enemy::camera = camera; }

	/// <summary>
	///入力セット
	/// </summary>
	static void SetInput(Input* input) { Enemy::input = input; }

	/// <summary>
	///デバイスセット
	/// </summary>
	static void SetDXInput(DXInput* dxInput) { Enemy::dxInput = dxInput; }

	/// <summary>
	/// インストラクタ デストラクタ
	/// </summary>
	Enemy() {};
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
	///チュートリアルの時の更新
	/// </summary>
	void UpdateTutorial(int tutorialTimer);

	/// <summary>
	///オブジェクト更新
	/// </summary>
	void UpdateObject();

	/// <summary>
	///オブジェクト更新
	/// </summary>
	void UpdateObject(const Status& status, FbxObject3D* object);

	/// <summary>
	///スプライト更新
	/// </summary>
	void UpdateSpriteGame1();

	/// <summary>
	///スプライト更新
	/// </summary>
	void UpdateSpriteGame2();

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
	void DrawSpriteGame1(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///スプライト描画
	/// </summary>
	void DrawSpriteGame2(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///パーティクル描画
	/// </summary>
	void DrawParticle(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///挙動全般
	/// </summary>
	void Move();

	/// <summary>
	///歩くモーション自の挙動
	/// </summary>
	void MoveWalk();

	/// <summary>
	///ダッシュ自の挙動
	/// </summary>
	void MoveDash();

	/// <summary>
	///落下
	/// </summary>
	void UpdateGravity();

	/// <summary>
	///ジャンプ
	/// </summary>
	void UpdateJump();

	/// <summary>
	///攻撃系全般
	/// </summary>
	void UpdateAttack();

	/// <summary>
	///攻撃1の更新
	/// </summary>
	void UpdateAttack1();

	/// <summary>
	///攻撃前兆の更新
	/// </summary>
	void UpdateAttackOmen();

	/// <summary>
	///ダメージ系全般
	/// </summary>
	void UpdateDamage();

	/// <summary>
	///コライダー
	/// </summary>
	void UpdateCollider();

	/// <summary>
	///パーティクル
	/// </summary>
	void UpdateParticle();

	/// <summary>
	///ステータスマネージャー
	/// </summary>
	void StatusManagerGame1();

	/// <summary>
	///ステータスマネージャー
	/// </summary>
	void StatusManagerGame2();

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
	void SetPlayerPos(XMFLOAT3 playerPos) { Enemy::playerPos = playerPos; };

	/// <summary>
	///地面との判定
	/// </summary>
	void HitPlane();

	/// <summary>
	///時機の弾被弾時
	/// </summary>
	void HitBullet1();

	/// <summary>
	///リセット
	/// </summary>
	void Reset();

	/// <summary>
	///ゲームシーンに移る
	/// </summary>
	void SetGameScene();

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
	///コライダー取得
	/// </summary>
	JSONLoader::ColliderData GetColliderData() { return colliderData; }

	/// <summary>
	///弾のコライダー取得
	/// </summary>
	JSONLoader::ColliderData GetBulletColliderData(int num) { return bullet->GetColliderData(num); }

	/// <summary>
	///弾のコライダー取得
	/// </summary>
	size_t GetBulletNum() { return  bullet->GetBulletNum(); }

	/// <summary>
	///敵呼び出しフラグ取得
	/// </summary>
	bool GetCallEnemyFlag() { return callEnemyFlag; }

	/// <summary>
	///敵呼び出し座標取得
	/// </summary>
	XMFLOAT3 GetCallEnemyPos() { return callEnemyPos; }

	/// <summary>
	///死亡フラグ取得
	/// </summary>
	bool GetIsDead() { return isDead; }

	/// <summary>
	///雷被弾時
	/// </summary>
	void HitElec() { hitElec = true; };

	//静的メンバ変数
private:
	//カメラ
	static Camera* camera;
	//キーボード
	static Input* input;
	//コントローラー
	static DXInput* dxInput;

	//メンバ変数
public:

	//敵の状態
	Status status = AttackOmen1;
	Status preStatus = Stand;
	//状態遷移用タイマー
	float statusTimer = 0.0f;

	//フェーズ1の攻撃遷移用フラグ
	bool dashFlag = true;
	bool attack1Flag = false;

	//フェーズ2の攻撃遷移用フラグ
	bool phase2CallEnemyFlag = true;
	bool phase2DashFlag = false;
	bool phase2Attack1Flag = false;

	//敵の弾
	EnemyBullet* bullet = nullptr;

	//敵呼び出しフラグ
	bool callEnemyFlag = false;
	//呼び出す敵の座標
	XMFLOAT3 callEnemyPos = { 0.0f,0.0f,0.0f };

	//コライダーデータ
	JSONLoader::ColliderData colliderData;

	//雷パーティクル 敵呼び出しで描画
	ElecParticle* elecParticle = nullptr;
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

	//爆発パーティクル 敵呼び出しで描画
	ExplosionParticle1* explosionParticle1 = nullptr;
	ExplosionParticle2* explosionParticle2 = nullptr;

	//立っている状態のオブジェクト
	FbxObject3D* objectStand = nullptr;
	//立っている状態のモデル
	FbxModel* modelStand = nullptr;
	//攻撃1状態のアニメーションのフレーム
	float frameStand = 250.0f;

	//歩いている状態のオブジェクト
	FbxObject3D* objectWalk = nullptr;
	//歩いている状態のモデル
	FbxModel* modelWalk = nullptr;
	//攻撃1状態のアニメーションのフレーム
	float frameWalk = 82.0f * 3.0f;

	//攻撃1状態のオブジェクト
	FbxObject3D* objectAttack1 = nullptr;
	//攻撃1状態のモデル
	FbxModel* modelAttack1 = nullptr;
	//攻撃1状態のアニメーションのフレーム
	float frameAttack1 = 190.0f;

	//攻撃1前兆のオブジェクト
	FbxObject3D* objectAttackOmen1 = nullptr;
	//攻撃1前兆のモデル
	FbxModel* modelAttackOmen1 = nullptr;
	//攻撃1前兆状態のアニメーションのフレーム
	float frameAttackOmen1 = 143.0f;

	//ダッシュのオブジェクト
	FbxObject3D* objectDash = nullptr;
	//ダッシュのモデル
	FbxModel* modelDash = nullptr;
	//ダッシュ状態のアニメーションのフレーム
	float frameDash = 53.0f * 4;

	//敵呼び出しのオブジェクト
	FbxObject3D* objectCallMiniEnemy = nullptr;
	//敵呼び出し状態のアニメーションのフレーム
	float frameCallMiniEnemy = 190.0f;
	//敵を呼び出すフレーム
	float frameCallMiniEnemy2 = 40.0f;

	//スプライト
	Sprite* hpBar1 = nullptr;	//HPバーの枠
	Sprite* hpBar2 = nullptr;	//HPバー
	Sprite* hpBar3 = nullptr;	//現在のHPのとこにつけるやつ
	Sprite* hpBar4 = nullptr;	//BOSS HPのテキスト
	Sprite* hpBar5 = nullptr;	//HPバーオレンジ

	//変形行列
	//平行移動
	XMFLOAT3 position = { 0.0f,0.0f,30.0f };
	//回転
	XMFLOAT3 rotation = { 0.0f,0.0f,0.0f };
	//サイズ
	XMFLOAT3 scale = { 5.0f,5.0f,5.0f };


	//当たり判定関連
	//接地フラグ
	bool groundFlag = false;

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

	//プレイヤーの座標
	XMFLOAT3 playerPos = { 0.0f,0.0f,0.0f };

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
	//HPバー5
	XMFLOAT2 hpBar5Pos = { 349.0f,26.0f };
	XMFLOAT2 hpBar5OriginalScale = { 605.0f,15.0f };
	XMFLOAT2 hpBar5Scale = hpBar2OriginalScale;

	//imgui用
	int debugNum[1] = { 0};
	float pos2[2] = { 605.0f,15.0f };
	float pos3[2] = { 938.0f,25.0f };
	float pos4[2] = { 230.0f,25.0f };

	//死亡フラグ
	bool isDead = false;
};

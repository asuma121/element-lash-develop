/**
 * @file Player.h
 * @brief ゲームオブジェクト プレイヤー
 * @author Asuma Syota
 * @date 2023/4
 */

#pragma once
#include "DirectXMath.h"
#include "FbxObject3D.h"
#include "PlayerBullet.h"
#include "JSONLoader.h"
#include "Sprite.h"
#include "LockOn.h"
#include "ElecParticle.h"
#include "EnemyBulletParticle.h"

//クラスの前方宣言
class PlayerState;
class Player
{
private:	//エイリアス
	//Microsoft::WRL::を省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:

	enum Form	//プレイヤーのフォルム
	{
		Fire,	//炎
		Elec,	//電気
	};

	//メンバ関数
public:

	//インストラクタ コンストラクタ
	Player();
	~Player();

	//静的メンバ関数

	/// <summary>
	///カメラセット
	/// </summary>
	static void SetCamera(Camera* camera) { Player::camera = camera; }

	/// <summary>
	///入力セット
	/// </summary>
	static void SetInput(Input* input) { Player::input = input; }

	/// <summary>
	///コントローラー入力セット
	/// </summary>
	static void SetDXInput(DXInput* dxInput) { Player::dxInput = dxInput; }


	/// <summary>
	///ロックオンセット
	/// </summary>
	static void SetLockOn(LockOn* lockOn) { Player::lockOn = lockOn; }

	/// <summary>
	///初期化
	/// </summary>
	void Initialize();

	/// <summary>
	///更新 ゲームシーン
	/// </summary>
	void UpdateGame();

	/// <summary>
	///更新 チュートリアルシーン
	/// </summary>
	void UpdateTutorial();
	 
	/// <summary>
	///更新 タイトルシーン
	/// </summary>
	void UpdateTitle(float timer);

	/// <summary>
	///更新 スプライト
	/// </summary>
	void UpdateSprite();

	/// <summary>
	///更新 コライダー
	/// </summary>
	void UpdateCollider();

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
	///スプライト描画
	/// </summary>
	void DrawSpriteGame(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///スプライト描画
	/// </summary>
	void DrawSpriteTutorial(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///更新 フォルム
	/// </summary>
	void UpdateForm();

	/// <summary>
	///更新 フォルム
	/// </summary>
	void UpdateFormTutorial();

	/// <summary>
	///srvセット
	/// </summary>
	void SetSRV(ID3D12DescriptorHeap* SRV);

	/// <summary>
	///座標セット
	/// </summary>
	void SetPosition(XMFLOAT3 pos) {};

	/// <summary>
	///オブジェクトの当たり判定セット
	/// </summary>
	void SetObjectCollider(std::vector<JSONLoader::ColliderData> colliderData);

	/// <summary>
	///敵の座標取得
	/// </summary>
	void SetEnemyPos(XMFLOAT3 position) { enemyPos.emplace_back(position); }

	/// <summary>
	///プレイヤーの弾命中時
	/// </summary>
	void HitBullet1(int num);

	/// <summary>
	///敵の弾命中時
	/// </summary>
	void HitEnemy();

	/// <summary>
	///リセット
	/// </summary>
	void Reset();

	/// <summary>
	///チュートリアルシーンに移る際に呼び出す
	/// </summary>
	void SetTutorial();

	/// <summary>
	///ゲームシーンに移る際に呼び出す
	/// </summary>
	void SetGameScene();

	/// <summary>
	///チュートリアルのフェーズセット
	/// </summary>
	void SetTutorialFlag(int tutorialFlag) { this->tutorialFlag = tutorialFlag; }

	/// <summary>
	///座標取得
	/// </summary>
	XMFLOAT3 GetPosition();

	/// <summary>
	///角度取得
	/// </summary>
	XMFLOAT3 GetRotation0();

	/// <summary>
	///角度取得
	/// </summary>
	XMFLOAT3 GetRotation1();

	/// <summary>
	///スケール取得
	/// </summary>
	XMFLOAT3 GetScale();

	/// <summary>
	///コライダー取得 
	/// </summary>
	JSONLoader::ColliderData GetColliderData();

	/// <summary>
	///弾のコライダー取得
	/// </summary>
	JSONLoader::ColliderData GetBullet1ColliderData(int num);

	/// <summary>
	///弾のコライダー取得
	/// </summary>
	size_t GetBullet1Num();

	/// <summary>
	///プレイヤーが無敵状態か取得
	/// </summary>
	bool GetInvincibleFlag();

	/// <summary> 
	///死亡フラグ取得
	/// </summary>
	bool GetIsDead() { return isDead; }

	/// <summary>
	///死亡フラグ取得
	/// </summary>
	bool GetHitElec();

	/// <summary>
	///属性チェンジフラグ取得
	/// </summary>
	int GetFormChangeFlag() { return formChangeFlag; }

	/// <summary>
	///属性取得
	/// </summary>
	int GetPlayerForm() { return form; }

	/// <summary>
	///プレイヤーの状態変更
	/// </summary>
	void ChangeState(PlayerState* playerState);

	//静的メンバ変数
private:
	//カメラ
	static Camera* camera;
	//キーボード
	static Input* input;
	//コントローラー
	static DXInput* dxInput;	
	//ロックオン
	static LockOn* lockOn;

	//メンバ変数
private:

	//プレイヤー
	PlayerState* playerState = nullptr;

	//チュートリアルのフェーズ
	int tutorialFlag = 0;

	//HP用スプライト
	Sprite* hpSprite1[5];	//緑のHP
	Sprite* hpSprite2 = nullptr;	//赤いHP
	Sprite* hpSprite3 = nullptr;	//HPの枠
	//HP用スプライトの大きさ、座標
	XMFLOAT2 hpSpritePos = { 490.0f,660.0f };
	XMFLOAT2 hpSprite1Scale = { 32.0f * 1.5f,16.0f * 1.5f };
	XMFLOAT2 hpSprite2Scale = { 32.0f * 1.5f,16.0f * 1.5f };
	XMFLOAT2 hpSprite3Scale = { 196.0f * 1.5,28.0f * 1.5 };
	//HP枠の大きさ
	float hpFrameScale1 = 10.0f * 1.5f;	//外枠 左右
	float hpFrameScale2 = 4.0f * 1.5f;	//内側の枠
	float hpFrameScale3 = 6.0f * 1.5f;	//外枠 上下

	//属性変化のUIスプライト
	Sprite* changeElementSprite1 = nullptr;	//電気
	Sprite* changeElementSprite2 = nullptr;	//炎
	Sprite* changeElementSprite3 = nullptr;	//チェンジ
	Sprite* changeElementSprite4 = nullptr;	//罰マーク
	XMFLOAT2 changeElementSpritePos = { 1200.0f,50.0f };
	XMFLOAT2 changeElementspriteScale = { 64.0f,64.0f };

	//攻撃のUIスプライト
	Sprite* attackElecSprite = nullptr;
	Sprite* attackFireSprite = nullptr;
	XMFLOAT2 attackSpritePos = { 1200.0f,124.0f };
	XMFLOAT2 attackSpriteScale = { 64.0f,64.0f };

	//RBボタン LBボタンのスプライト
	Sprite*LBButtonSprite = nullptr;
	Sprite*LBButtonPushSprite = nullptr;
	Sprite*RBButtonSprite = nullptr;
	Sprite*RBButtonPushSprite = nullptr;
	//RBボタン LBボタン 座標 スケール
	XMFLOAT2 LBButtonSpritePos = { 1126.0f,50.0f };
	XMFLOAT2 RBButtonSpritePos = { 1126.0f,124.0f };
	XMFLOAT2 BButtonSpriteScale = { 64.0f,64.0f };

	float debugPos[2] = {320.0f,120.0f};

	//ステータス関連
	//プレイヤーのHP
	float MaxHP = 5;
	float HP = MaxHP;

	//フォルム
	Form form = Fire;
	Form preForm = Fire;
	//フォルムチェンジに使うタイマー
	int formTimer = 0;
	int formMaxTime = 120;
	//フォルムチェンジに使うフラグ
	bool formChangeFlag = false;

	//走ってるアニメーションに無理やりするフラグ
	bool runAnimationFlag = false;
	//シーン遷移に使う角度
	float addRot = 0.0f;
	float originalRot = 0.0f;

	//敵の座標
	std::vector<XMFLOAT3>enemyPos;

	//死亡フラグ
	bool isDead = false;


	//デバッグ用
	float debugTimer[1] = { 0 };
	float debugNum[1] = { 0 };
};

class PlayerState
{

public:	//静的メンバ関数

	//静的メンバ変数初期化
	static void StaticInitialize();

public:	//メンバ関数

	//コンストラクタ デストラクタ
	PlayerState() {};
	~PlayerState() {};

	//仮想関数
	//各ステート初期化
	virtual void Initialize() = 0;
	//攻撃処理
	virtual void UpdateAttack() {};
	//移動処理
	virtual void Move();
	//ステートの変更
	virtual void UpdateState(Player* player) = 0;
	//描画
	virtual void Draw(ID3D12GraphicsCommandList* cmdList) = 0;
	//ライト目線描画
	virtual void DrawLightView(ID3D12GraphicsCommandList* cmdList) = 0;
	//SRVセット
	virtual void SetSRV(ID3D12DescriptorHeap* SRV) = 0;
	//オブジェクトの更新
	virtual void UpdateObject() = 0;

	//通常関数
	//パーティクル描画
	void DrawParticle(ID3D12GraphicsCommandList* cmdList);
	//更新
	void Update();
	//判定更新
	void UpdateCollider();
	//ダウン状態更新
	void UpdateDown();
	//壁との当たり判定処理
	void UpdateHitWall(JSONLoader::ColliderData objectColliderData);
	//柱との当たり判定処理
	void UpdateHitPiller(JSONLoader::ColliderData objectColliderData);
	//オブジェクトの当たり判定セット
	void SetObjectCollider(std::vector<JSONLoader::ColliderData> colliderData) { objectColliderData = colliderData; };

	//座標取得
	XMFLOAT3 GetPosition() { return position; }
	//角度取得
	XMFLOAT3 GetRotation0() { return rotation0; }
	//角度取得
	XMFLOAT3 GetRotation1() { return rotation1; }
	//スケール取得
	XMFLOAT3 GetScale() { return scale; }
	//プレイヤーの弾命中時
	void HitBullet1(int num) { bullet->SetHitFlag(num); };
	//コライダー取得
	JSONLoader::ColliderData GetColliderData() { return colliderData; }
	//弾のコライダー取得
	JSONLoader::ColliderData GetBullet1ColliderData(int num) { return bullet->GetColliderData(num); }
	//弾のコライダー取得
	size_t GetBullet1Num() { return  bullet->GetBulletNum(); }
	//プレイヤーが無敵状態か取得
	bool GetInvincibleFlag() { return invincibleFlag; }
	//ヒットフラグ取得
	bool GetHitElec() { return hitElecFlag; }
	//リセット
	void Reset();
	//チュートリアルシーンに移る際に呼び出す
	void SetTutorial();
	//ゲームシーンに移る際に呼び出す
	void SetGameScene();

	//プレイヤー本体からセットする系
	void SetLockOn(bool lockOnFlag, XMFLOAT3 lockOnPos);
	void SetDXInput(DXInput* dxInput) { this->dxInput = dxInput; };
	void SetPlayerForm(Player::Form form) { this->form = form; }
	void HitEnemy();

protected:	//静的メンバ変数

	//モデル
	static FbxModel* modelWait;
	static FbxModel* modelRun;
	static FbxModel* modelAttack1;
	static FbxModel* modelAttack2;
	static FbxModel* modelAttack3;
	static FbxModel* modelDown;
	//オブジェクト
	static FbxObject3D* objectWait;
	static FbxObject3D* objectRun;
	static FbxObject3D* objectAttack1;
	static FbxObject3D* objectAttack2;
	static FbxObject3D* objectAttack3;
	static FbxObject3D* objectDown;
	//コライダーデータ
	static JSONLoader::ColliderData colliderData;
	//シェーダのデータ
	static JSONLoader::TextureData textureData;

	//平行移動
	static XMFLOAT3 position;
	//回転
	static XMFLOAT3 rotation0;
	static XMFLOAT3 rotation1;
	//サイズ
	static XMFLOAT3 scale;
	//弾 炎
	static PlayerBullet* bullet;
	//雷パーティクル
	static ElecParticle* elecParticle1;
	//雷パーティクルに使うパーティクル 敵の弾のもので代用
	static EnemyBulletParticle* elecParticle2;

protected:	//メンバ変数

	//コントローラー
	DXInput* dxInput = nullptr;

	//オブジェクトごとのタイマー
	int objectTimer = 0;
	//オブジェクトに時間の設定がある場合
	int objectTime = 0;
	//オブジェクトごとに時間の設定があるか
	bool objectTimeFlag = false;

	//雷を発生させる場所
	XMFLOAT3 addElecPos2;

	//ロックオン
	bool lockOnFlag = false;
	XMFLOAT3 lockOnPos = {0.0f,0.0f,0.0f};

	//フォルム
	Player::Form form;

	//回転の速度
	float rot0Speed = (float)PI * 1.5f / 180.0f;

	//移動スピード
	float posSpeed = 1.0f;

	//当たりフラグ
	bool hitFlag = false;
	bool hitElecFlag = false;
	float hitTimer = 0.0f;
	//被ダメージ時の無敵時間
	bool invincibleFlag = false;

	//被ダメージアニメーションのフレーム数
	float frameDown = 138.0f;
	//進行ベクトル
	XMFLOAT3 posVelocity = { 0.0f,0.0f,0.0f };
	//角度ベクトル
	XMFLOAT3 rotVelocity = { 0.0f,0.0f,0.0f };

	//オブジェクトのコライダーデータ
	std::vector<JSONLoader::ColliderData> objectColliderData;
	//オブジェクト衝突時の押し戻し
	float knockBackSpeed = 0.05f;
};
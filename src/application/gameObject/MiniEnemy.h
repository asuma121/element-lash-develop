/**
 * @file TutorialEnemy.h
 * @brief ゲームオブジェクト 敵
 * @author Asuma Syota
 * @date 2023/4
 */

#pragma once
#include "DirectXMath.h"
#include "FbxObject3D.h"
#include "JSONLoader.h"
#include "BillboardSprite.h"

class MiniEnemy
{
private:	//エイリアス
	//Microsoft::WRL::を省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private:	//サブクラス

	enum Status	//敵の状態
	{
		Dash,
		Down,
	};

	struct Enemy
	{
		//オブジェクト
		FbxObject3D* objectDash;
		FbxObject3D* objectDown;
		//コライダーデータ
		JSONLoader::ColliderData colliderData;
		//座標
		XMFLOAT3 position;
		//角度
		XMFLOAT3 rotation;
		//ステータス
		Status status;
		//ステータス
		Status preStatus;
		//HP
		int HP;
		//当たりフラグ
		bool hitFireFlag;
		//当たりフラグ
		bool hitElecFlag;
		//死亡フラグ
		bool deadFlag;
		//死亡タイマー
		int deadTimer;
	};

public://メンバ関数

	/// <summary>
	///カメラセット
	/// </summary>
	static void SetCamera(Camera* camera) { MiniEnemy::camera = camera; }

	/// <summary>
	///入力セット
	/// </summary>
	static void SetInput(Input* input) { MiniEnemy::input = input; }

	/// <summary>
	/// インストラクタ デストラクタ
	/// </summary>
	MiniEnemy() {};
	~MiniEnemy() {};

	/// <summary>
	///初期化
	/// </summary>
	void Initialize();

	/// <summary>
	///更新
	/// </summary>
	void Update();

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
	///ダメージ系全般
	/// </summary>
	void UpdateDamage();

	/// <summary>
	///敵削除
	/// </summary>
	void DeleteEnemy();

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
	///攻撃の処理
	/// </summary>
	void UpdateAttack();

	/// <summary>
	///ステータスマネージャー
	/// </summary>
	void StatusManager();

	/// <summary>
	///srvセット
	/// </summary>
	void SetSRV(ID3D12DescriptorHeap* SRV);

	/// <summary>
	///座標セット
	/// </summary>
	/*void SetPosition(XMFLOAT3 position) { this->position = position; };*/

	/// <summary>
	///リセット
	/// </summary>
	void Reset();

	/// <summary>
	///敵を追加する
	/// </summary>
	void AddEnemy(XMFLOAT3 pos);

	/// <summary>
	///時機の弾被弾時
	/// </summary>
	void HitFire(int num) { enemys[num].hitFireFlag = true; };

	/// <summary>
	///雷被弾時
	/// </summary>
	/*void HitElec() { hitElec = true; };*/

	/// <summary>
	///敵の数取得
	/// </summary>
	int GetEnemyNum() { return enemys.size(); }

	/// <summary>
	///スケール取得
	/// </summary>
	XMFLOAT3 GetScale() { return scale; }

	/// <summary>
	///コライダー取得
	/// </summary>
	JSONLoader::ColliderData GetColliderData(int num) { return enemys[num].colliderData; }

	/// <summary>
	///死亡フラグ取得
	/// </summary>
	/*bool GetIsDead() { return isDead; }*/

	/// <summary>
	///プレイヤーの座標取得
	/// </summary>
	void SetPlayerPos(XMFLOAT3 playerPos) { this->playerPos = playerPos; }

	//静的メンバ変数
private:
	//カメラ
	static Camera* camera;
	//キーボード
	static Input* input;

	//メンバ変数
public:

	//敵データ
	std::vector<Enemy>enemys;

	//モデル
	FbxModel* modelDash = nullptr;
	FbxModel* modelDown= nullptr;

	//HPのビルボード
	BillboardSpriteModel* hpFrameSpriteModel = nullptr;
	BillboardSprite* hpFrameSprite = nullptr;
	BillboardSpriteModel* hpBarSpriteModel = nullptr;
	BillboardSprite* hpBarSprite = nullptr;

	//HPのビルボードの座標、スケール
	XMFLOAT3 hpFrameScale = { 64.0f,9.6f,1.0f };
	XMFLOAT3 hpBarOriginalScale = { 60.5f,1.5f,1.0f };
	XMFLOAT3 hpBarScale = hpBarOriginalScale;
	XMFLOAT3 hpBarAddPos = { 0.0f,5.0f,0.0f };

	//サイズ
	XMFLOAT3 scale = { 0.7f,0.7f,0.7f };

	//コライダー関連
	//コライダーのスケール
	XMFLOAT3 colliderScale = { 3.0f,3.0f,3.0f };

	//HP
	float maxHP = 30;

	//炎攻撃のダメージ
	int fireDamage = 1;

	//スピード
	float speed = 0.4f;

	//敵の番号
	int number = 0;

	//死ぬまでの時間
	int deadTime = 130;

	//プレイヤーの座標
	XMFLOAT3 playerPos = { 0.0f,0.0f,0.0f };

	//デバッグ
	int debugNum[1] = { 0 };
};
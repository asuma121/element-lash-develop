#pragma once

#include "memory"
#include "list"
#include "DirectXMath.h"
#include "Input.h"
#include "DXInput.h"
#include "DirectXCommon.h"
#include "Camera.h"
#include "Sprite.h"
#include "Player.h"
#include "Enemy.h"
#include "Plane.h"
#include "UI.h"
#include "SceneManager.h"

class ClearScene : public SceneState
{
private:	//エイリアス
	//Microsoft::WRL::を省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:	//静的メンバ変数

	/// <summary>
	///初期化
	/// </summary>
	static void SetDevice(DirectXCommon* dxCommon, Input* input, DXInput* dxInput);

	/// <summary>
	///ゲームシーンで使うオブジェクトセット
	/// </summary>
	static void SetGameObject(Player* player, Enemy* enemy, Plane* plane, Camera* camera, Light* light, UI* ui);

public: //メンバ関数

	ClearScene();
	~ClearScene();

	/// <summary>
	///初期化
	/// </summary>
	void Initialize();

	/// <summary>
	///更新
	/// </summary>
	void Update();

	/// <summary>
	///次のシーンへ移動
	/// </summary>
	void NextScene(Scene* pScene);

	/// <summary>
	///オブジェクト更新
	/// </summary>
	void UpdateObject();

	/// <summary>
	///スプライト更新
	/// </summary>
	void UpdateSprite();

	/// <summary>
	///パーティクル更新
	/// </summary>
	void UpdateParticle();

	/// <summary>
	///描画
	/// </summary>
	void Draw();

	/// <summary>
	///FBX描画
	/// </summary>
	void DrawFBX();

	/// <summary>
	///スプライト描画
	/// </summary>
	void DrawSprite();

	/// <summary>
	///パーティクル描画
	/// </summary>
	void DrawParticle();

	/// <summary>
	///ライト目線の描画
	/// </summary>
	void DrawFBXLightView();

	/// <summary>
	///セッター
	/// </summary>
	void SetSRV(ID3D12DescriptorHeap* SRV);

	/// <summary>
	///ゲッター
	/// </summary>
	DirectX::XMMATRIX GetLightViewProjection();
	bool GetMoveTitle() { return moveTitleFlag; }
	bool GetMoveTutorial() { return moveTutorialFlag; }
	bool GetMoveGame() { return moveGameFlag; }
	bool GetMoveGame2() { return moveGame2Flag; }

private:	//静的メンバ変数
	//デバイスとinput
	static DirectXCommon* dxCommon;
	static Input* input;
	static DXInput* dxInput;
	//カメラ
	static Camera* camera;
	//ライト
	static Light* light;
	//プレイヤー
	static Player* player;
	//敵
	static Enemy* enemy;
	//床
	static Plane* plane;
	//UI
	static UI* ui;

public:	//メンバ変数

	float lightDir[3] = { 0.0f,-1.0f , -1.0f };
	float lightPos[3] = { 0.0f,25.0f,25.0f };
	float lightTarget[3] = { 0.0f,0.0f,0.0f };
	float lightFactorAngle[2] = { 20.0f,30.0f, };
	float lightAtten[3] = { 0.0f,0.0f,0.0f };

	//黒いスプライト
	std::unique_ptr<Sprite>blackSprite1;
	std::unique_ptr<Sprite>blackSprite2;
	//黒いスプライト 座標 スケール
	XMFLOAT2 black1Pos = { 0.0f, 0.0f };
	XMFLOAT2 black1Scale = { 1280.0f, 720.0f };
	XMFLOAT2 black2Pos = { 0.0f, 0.0f };
	XMFLOAT2 black2Scale = { 1280.0f, 720.0f };
	//クリアシーン用スプライト
	std::unique_ptr<Sprite>clear1Sprite;
	//クリアシーン用スプライト 座標 スケール
	XMFLOAT2 clear1Pos = { 150.0f, 300.0f };
	XMFLOAT2 clear1Scale = { 860.0f, 77.0f };

	//タイマー
	float gameTimer = 0.0f;

	//シーン遷移用
	bool clearFromGameFlag = false;
	float clearFromGameTimer = 0.0f;
	float clearFromGameTime = 500.0f;

	bool moveTitleFlag = false;
	bool moveGameFlag = false;
	bool moveGame2Flag = false;
	bool moveTutorialFlag = false;
};
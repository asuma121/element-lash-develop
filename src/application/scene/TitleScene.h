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
#include "Terrain.h"
#include "UI.h"
#include "SceneManager.h"

class TitleScene : public SceneState
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
	static void SetGameObject(Player* player, Terrain* terrain, Camera* camera, Light* light, UI* ui);

public: //メンバ関数

	TitleScene();
	~TitleScene();

	/// <summary>
	///初期化
	/// </summary>
	void Initialize();

	/// <summary>
	///更新
	/// </summary>
	void Update();

	/// <summary>
	///シーン遷移
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
	///シーン遷移更新
	/// </summary>
	void UpdateMoveScene();

	/// <summary>
	///リセット
	/// </summary>
	void Reset();

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
	//オブジェクト
	static Terrain* terrain;
	//UI
	static UI* ui;

public:	//メンバ変数

	//シーン全体のタイマー
	int sceneTimer = 0;

	//ライト
	float lightDir[3] = { 0.0f,-1.0f , -1.0f };
	float lightPos[3] = { 0.0f,25.0f,25.0f };
	float lightTarget[3] = { 0.0f,0.0f,0.0f };
	float lightFactorAngle[2] = { 20.0f,30.0f, };
	float lightAtten[3] = { 0.0f,0.0f,0.0f };

	//シーン遷移用
	int titleMoveTime = 120.0f;

	//黒いスプライト
	std::unique_ptr<Sprite>blackSprite1;
	//黒いスプライト 座標 スケール
	XMFLOAT2 black1Pos = { 0.0f, 0.0f };
	XMFLOAT2 black1Scale = { 1280.0f, 720.0f };
	//黒いスプライト用の時間
	int blackSpriteTime = 220;

	//シーン遷移用フラグ シーンマネージャーに渡す
	bool moveTutorialFlag1 = false;

	//シーン遷移用フラグ こちらで管理する用
	bool moveTutorialFlag2 = false;

	//シーン遷移用タイマー
	int moveTutorialTimer = 0;
	//シーン遷移の時間
	int moveTutorialTime = 300;

	float debugNum[1] = { 0.0f };
};
#pragma once

#include "memory"
#include "list"
#include "DirectXMath.h"
#include "DirectXCommon.h"
#include "Camera.h"
#include "Sprite.h"
#include "Player.h"
#include "Enemy.h"
#include "TutorialEnemy.h"
#include "Plane.h"
#include "UI.h"
#include "SceneManager.h"
#include "Terrain.h"

//クラスの前方宣言
class PhaseState;

class GameScene : public SceneState
{
private:	//エイリアス
	//Microsoft::WRL::を省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: //メンバ関数

	GameScene();
	~GameScene();

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
	///描画
	/// </summary>
	void Draw();

	/// <summary>
	///ライト目線の描画
	/// </summary>
	void DrawFBXLightView();

	/// <summary>
	///セッター
	/// </summary>
	void SetSRV(ID3D12DescriptorHeap* SRV);

	/// <summary>
	///フェーズ移動
	/// </summary>
	void ChangePhase(PhaseState* newPhase);

	/// <summary>
	///セッター
	/// </summary>
	void SetMoveClearFlag(bool moveClearFlag) { this->moveClearFlag = true; };

private:
	//フェーズ
	PhaseState* phaseState;

	//クリアに移るフラグ
	bool moveClearFlag = false;

	//デバッグ用
	int debugNum[1] = { 0 };
};

class PhaseState
{

public:	//静的メンバ変数

	/// <summary>
	///初期化
	/// </summary>
	static void SetDevice(DirectXCommon* dxCommon, KeyManager* keyManager);

	/// <summary>
	///ゲームシーンで使うオブジェクトセット
	/// </summary>
	static void SetGameObject(Player* player, Enemy* enemy,
		TutorialEnemy* tutorialEnemy,Plane* plane, Terrain* terrain, Camera* camera, Light* light, UI* ui);

public:	//仮想関数
	void Initialize();
	//フェーズごとの初期化
	virtual void PhaseInitialize() = 0;
	virtual void Update();
	virtual void Draw();
	virtual void DrawFBXLightView() = 0;
	virtual void SetSRV(ID3D12DescriptorHeap* SRV) = 0;
	virtual void NextPhase(GameScene* gameScene) = 0;

public:
	virtual void UpdateObject() = 0;
	virtual void UpdateCollider() = 0;
	virtual void DrawFBX() = 0;
	virtual void DrawSprite() = 0;
	virtual void DrawParticle() = 0;

protected:	//静的メンバ変数
	//デバイスとinput
	static DirectXCommon* dxCommon;
	static KeyManager* keyManager;
	//カメラ
	static Camera* camera;
	//ライト
	static Light* light;
	//プレイヤー
	static Player* player;
	//敵
	static Enemy* enemy;
	//敵 チュートリアルのものをそのまま流用
	static TutorialEnemy* tutorialEnemy;
	//床
	static Plane* plane;
	//地形
	static Terrain* terrain;
	//UI
	static UI* ui;

protected:	//メンバ変数

	//タイマー
	int phaseTimer = 0;

	//フェーズチェンジフラグ
	bool phaseChangeFlag = false;

	//ライト関連
	float lightDir[3] = { 0.0f,-1.0f , -1.0f };
	float lightPos[3] = { 125.0f,125.0f,200.0f };
	float lightTarget[3] = { 0.0f,0.0f,0.0f };
	float lightFactorAngle[2] = { 20.0f,30.0f, };
	float lightAtten[3] = { 0.0f,0.0f,0.0f };
};
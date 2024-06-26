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
#include "TutorialEnemy.h"
#include "Plane.h"
#include "UI.h"
#include "SceneManager.h"
#include "Terrain.h"

class TutorialScene : public SceneState
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
	static void SetDevice(DirectXCommon* dxCommon, KeyManager* keyManager);

	/// <summary>
	///チュートリアルシーンで使うオブジェクトセット
	/// </summary>
	static void SetGameObject(Player* player, Enemy* enemy,TutorialEnemy* tutorialEnemy,Plane* plane, Terrain* terrain, Camera* camera, Light* light, UI* ui);

public: //メンバ関数

	TutorialScene();
	~TutorialScene();

	/// <summary>
	///初期化
	/// </summary>
	void Initialize();

	/// <summary>
	///更新
	/// </summary>
	void Update();

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
	///コライダー更新
	/// </summary>
	void UpdateCollider();

	/// <summary>
	///パーティクル更新
	/// </summary>
	void UpdateParticle();

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
	///ゲッター
	/// </summary>
	DirectX::XMMATRIX GetLightViewProjection();

private:	//静的メンバ変数
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
	//チュートリアル用敵
	static TutorialEnemy* tutorialEnemy;
	//床
	static Plane* plane;
	//地形
	static Terrain* terrain;
	//UI
	static UI* ui;

private:	//メンバ変数

	float lightDir[3] = { 0.0f,-1.0f , -1.0f };
	float lightPos[3] = { 0.0f,25.0f,25.0f };
	float lightTarget[3] = { 0.0f,0.0f,0.0f };
	float lightFactorAngle[2] = { 20.0f,30.0f, };
	float lightAtten[3] = { 0.0f,0.0f,0.0f };
	
	//スプライト用タイマー
	float blackSpriteTimer = 0.0f;
	float blackSpriteMaxTime = 120.0f;
	int tutorialSpriteFlag = 1;	//その番号のスプライト描画
	int tutorialLStickTimer = 0;
	int tutorialLStickMaxTime = 240;
	int tutorialRStickTimer = 0;
	int tutorialRStickMaxTime = 240;
	int tutorialIikannjiTimer = 0;
	int tutorialIikannjiMaxTime = 200;
	int tutorialAttackTimer = 0;
	int tutorialAttackMaxTime = 200;
	int tutorialAttack2Timer = 0;
	int tutorialAttack2MaxTime = 2;
	int tutorial12Timer = 0;
	int tutorial12MaxTime = 120;
	int tutorial13Timer = 0;
	int tutorial13MaxTime = 320;
	//敵が真ん中に現れた
	int tutorial10Timer = 0;
	int tutorial10MaxTime = 150;

	//タイマー
	float gameTimer = 0.0f;

	//シーン遷移フラグ
	bool moveGameFlag = false;
};
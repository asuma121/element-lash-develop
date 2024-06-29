#include "DevelopScene.h"
#include "mathOriginal.h"
#include "imgui.h"

KeyManager* DevelopScene::keyManager = nullptr;
DirectXCommon* DevelopScene::dxCommon = nullptr;
Camera* DevelopScene::camera = nullptr;
Light* DevelopScene::light = nullptr;
Player* DevelopScene::player = nullptr;
Enemy* DevelopScene::enemy = nullptr;
Plane* DevelopScene::plane = nullptr;
UI* DevelopScene::ui = nullptr;
Terrain* DevelopScene::terrain = nullptr;

DevelopScene::DevelopScene()
{
}
 
DevelopScene::~DevelopScene()
{
}

void DevelopScene::Initialize()
{
	//シーン遷移時に初期化
	if (sceneTimer == 0)
	{
		//プレイヤーをタイトル用にセット
		player->SetDevelop();

		//敵をタイトル用にセット
		enemy->SetTitle();

		//カメラをデバッグ用にセット
		camera->SetDevelop();
	}
}

void DevelopScene::Update()
{
	//タイトルに戻った時にフラグリセット
	if (sceneTimer == 0)
	{
		moveTutorialFlag1 = false;
	}

	//タイマー更新
	sceneTimer++;

	//オブジェクト更新
	UpdateObject();

	//スプライト更新
	UpdateSprite();

	//シーン遷移更新
	UpdateMoveScene();
}

void DevelopScene::NextScene(Scene* pScene)
{
}

void DevelopScene::UpdateObject()
{
	//カメラ更新
	camera->SetPhaseTimer(moveTutorialTimer);
	camera->SetPlayerPos(player->GetPosition());
	camera->SetPlayerRot(player->GetRotation0());
	camera->Update();

	//ライト
	light->SetEye(XMFLOAT3(lightPos));
	light->SetTarget(XMFLOAT3(lightTarget));
	light->SetDir(XMFLOAT3(lightDir));
	light->Update();

	//オブジェクト
	terrain->Update();

	//床更新
	plane->Update();

	////敵更新
	//enemy->Update();

	//プレイヤー
	player->Update();
}

void DevelopScene::UpdateSprite()
{
}

void DevelopScene::UpdateMoveScene()
{
	//スペースかAボタン押されたら
	if (keyManager->TriggerKey(KeyManager::PAD_A) && sceneTimer >= 100)
	{
		//シーン遷移フラグオン
		moveTutorialFlag2 = true;
	}
	//シーン遷移フラグが立ったら
	if (moveTutorialFlag2)
	{
		//タイマー加算
		moveTutorialTimer++;
		//タイマーが規定のタイムに達したら
		if (moveTutorialTimer >= moveTutorialTime)
		{
			//リセット
			Reset();
			//モードをゲームへ
			moveTutorialFlag1 = true;
		}
	}
}

void DevelopScene::Reset()
{
	//タイマーを元に戻す
	moveTutorialTimer = 0;
	sceneTimer = 0;
	//フラグを元に戻す
	moveTutorialFlag2 = false;
}

void DevelopScene::Draw()
{
	//FBX描画
	DrawFBX();

	//パーティクル描画
	DrawParticle();

	//スプライト描画
	DrawSprite();
}

void DevelopScene::DrawFBX()
{
	player->Draw(dxCommon->GetCommandList());
	plane->Draw(dxCommon->GetCommandList());
	/*enemy->Draw(dxCommon->GetCommandList());*/
	terrain->Draw(dxCommon->GetCommandList());

	/*player->UpdateState();*/
	enemy->UpdateState();
}

void DevelopScene::DrawSprite()
{
}

void DevelopScene::DrawParticle()
{
	//プレイヤーのパーティクル描画
	player->DrawParticle(dxCommon->GetCommandList());
}

void DevelopScene::DrawFBXLightView()
{
	player->DrawLightView(dxCommon->GetCommandList());
	//enemy->DrawLightView(dxCommon->GetCommandList());
}

void DevelopScene::SetDevice(DirectXCommon* dxCommon, KeyManager* keyManager)
{
	//引数から代入
	DevelopScene::dxCommon = dxCommon;
	DevelopScene::keyManager = keyManager;
}

void DevelopScene::SetGameObject(Player* player, Enemy* enemy, Plane* plane, Terrain* terrain, Camera* camera, Light* light, UI* ui)
{
	DevelopScene::player = player;
	DevelopScene::enemy = enemy;
	DevelopScene::plane = plane;
	DevelopScene::terrain = terrain;
	DevelopScene::camera = camera;
	DevelopScene::light = light;
	DevelopScene::ui = ui;
}

DirectX::XMMATRIX DevelopScene::GetLightViewProjection()
{
	return light->GetMatViewProjection();
}

#include "ClearScene.h"
#include "mathOriginal.h"
#include "TitleScene.h"

KeyManager* ClearScene::keyManager = nullptr;
DirectXCommon* ClearScene::dxCommon = nullptr;
Camera* ClearScene::camera = nullptr;
Light* ClearScene::light = nullptr;
Player* ClearScene::player = nullptr;
Enemy* ClearScene::enemy = nullptr;
Plane* ClearScene::plane = nullptr;
Terrain* ClearScene::terrain = nullptr;
UI* ClearScene::ui = nullptr;

void ClearScene::SetDevice(DirectXCommon* dxCommon, KeyManager* keyManager)
{
	//引数から代入
	ClearScene::dxCommon = dxCommon; 
	ClearScene::keyManager = keyManager;
}

void ClearScene::SetGameObject(Player* player, Enemy* enemy, Plane* plane, Terrain* terrain,Camera* camera, Light* light, UI* ui)
{
	ClearScene::player = player;
	ClearScene::enemy = enemy;
	ClearScene::plane = plane;
	ClearScene::terrain = terrain;
	ClearScene::camera = camera;
	ClearScene::light = light;
	ClearScene::ui = ui;
}

ClearScene::ClearScene()
{
}

ClearScene::~ClearScene()
{
}

void ClearScene::Initialize()
{
	//シーン遷移時に初期化
	if (clearFromGameTimer == 0)
	{
		//プレイヤーをタイトル用にセット
		enemy->SetClear();
		player->SetClear();
		camera->SetClear();
	}
}

void ClearScene::Update()
{
	//タイマー更新
	if (clearFromGameTimer <= clearFromGameTime)
	{
		clearFromGameTimer++;
	}

	if (gameTimer == 0.0f)
	{
		player->SetPosition(XMFLOAT3(0.0f, 0.0f, 0.0f));
	}
	gameTimer += 1.0f;

	//オブジェクト更新
	UpdateObject();

	//スプライト更新
	UpdateSprite();

	//パーティクル更新
	UpdateParticle();
}

void ClearScene::NextScene(Scene* pScene)
{
	if (moveTitleFlag)
	{
		pScene->ChangeScene(new TitleScene());
	}
}

void ClearScene::UpdateObject()
{
	if (clearFromGameTimer >= clearFromGameTime && keyManager->TriggerKey(KeyManager::PAD_X) == 1)
	{
		moveTitleFlag = true;
	}

	//カメラ更新
	camera->SetPhaseTimer((int)clearFromGameTimer);
	camera->SetEnemyPos(enemy->GetPosition());
	camera->SetPlayerPos(player->GetPosition());
	camera->SetPlayerRot(player->GetRotation0());
	camera->Update();

	//ライト
	light->SetEye(XMFLOAT3(lightPos) + player->GetPosition());
	light->SetTarget(XMFLOAT3(lightTarget) + player->GetPosition());
	light->SetDir(XMFLOAT3(lightDir));
	light->Update();

	//プレイヤー
	player->Update();

	//ui
	ui->SetClearTimer((int)clearFromGameTimer, (int)clearFromGameTime);
	ui->UpdateClear();

	//敵
	enemy->SetPlayerPos(player->GetPosition());
	enemy->SetClearTimer((int)clearFromGameTimer);
	enemy->Update();

	//地面
	plane->Update();

	//地形
	terrain->Update();
}

void ClearScene::UpdateParticle()
{
}

void ClearScene::Draw()
{
	//FBX描画
	DrawFBX();

	//パーティクル描画
	DrawParticle();

	//スプライト描画
	DrawSprite();
}

void ClearScene::DrawFBX()
{
	player->Draw(dxCommon->GetCommandList());
	enemy->Draw(dxCommon->GetCommandList());
	plane->Draw(dxCommon->GetCommandList());
	terrain->Draw(dxCommon->GetCommandList());
}

void ClearScene::DrawSprite()
{
	ui->DrawClear(dxCommon->GetCommandList());

	//ステート更新
	enemy->UpdateState();
}

void ClearScene::DrawParticle()
{
	//プレイヤーのパーティクル描画
	player->DrawParticle(dxCommon->GetCommandList());
	//敵のパーティクル描画
	enemy->DrawParticle(dxCommon->GetCommandList());
}

void ClearScene::DrawFBXLightView()
{
	player->DrawLightView(dxCommon->GetCommandList());
	enemy->DrawLightView(dxCommon->GetCommandList());
}

DirectX::XMMATRIX ClearScene::GetLightViewProjection()
{
	return light->GetMatViewProjection();
}

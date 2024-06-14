#include "TitleScene.h"
#include "mathOriginal.h"
#include "imgui.h"
#include "TutorialScene.h"

KeyManager* TitleScene::keyManager = nullptr;
DirectXCommon* TitleScene::dxCommon = nullptr;
Camera* TitleScene::camera = nullptr;
Light* TitleScene::light = nullptr;
Player* TitleScene::player = nullptr;
Enemy* TitleScene::enemy = nullptr;
Plane* TitleScene::plane = nullptr;
UI* TitleScene::ui = nullptr;
Terrain* TitleScene::terrain = nullptr;

TitleScene::TitleScene()
{
}
 
TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	//シーン遷移時に初期化
	if (sceneTimer == 0)
	{
		//プレイヤーをタイトル用にセット
		player->SetTitle();

		//敵をタイトル用にセット
		enemy->SetTitle();

		//カメラをタイトル用にセット
		camera->SetTitle();
	}
}

void TitleScene::Update()
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

void TitleScene::NextScene(Scene* pScene)
{
	if (moveTutorialFlag1)
	{
		Reset();
		pScene->ChangeScene(new TutorialScene());
	}
}

void TitleScene::UpdateObject()
{
	//カメラ更新
	camera->SetPhaseTimer(moveTutorialTimer);
	camera->SetPlayerPos(player->GetPosition());
	camera->SetPlayerRot(player->GetRotation0());
	camera->Update();

	//ライト
	lightTarget[0] = player->GetPosition().x + 25;
	lightTarget[1] = player->GetPosition().y + 25;
	lightTarget[2] = player->GetPosition().z + 25;
	lightPos[0] = player->GetPosition().x;
	lightPos[1] = player->GetPosition().y;
	lightPos[2] = player->GetPosition().z;
	light->SetEye(XMFLOAT3(lightPos));
	light->SetTarget(XMFLOAT3(lightTarget));
	light->SetDir(XMFLOAT3(lightDir));
	light->Update();

	//オブジェクト
	terrain->Update();

	//UIの更新
	ui->SetTitleTimer(moveTutorialTimer, titleMoveTime);
	ui->UpdateTitle();

	//床更新
	plane->Update();

	//敵更新
	enemy->UpdateTitle();

	//プレイヤー
	player->UpdateTitle((float)moveTutorialTimer);
}

void TitleScene::UpdateSprite()
{
}

void TitleScene::UpdateMoveScene()
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

void TitleScene::Reset()
{
	//タイマーを元に戻す
	moveTutorialTimer = 0;
	sceneTimer = 0;
	//フラグを元に戻す
	moveTutorialFlag2 = false;
}

void TitleScene::Draw()
{
	//FBX描画
	DrawFBX();

	//パーティクル描画
	DrawParticle();

	//スプライト描画
	DrawSprite();
}

void TitleScene::DrawFBX()
{
	player->Draw(dxCommon->GetCommandList());
	plane->Draw(dxCommon->GetCommandList());
	enemy->Draw(dxCommon->GetCommandList());
	terrain->Draw(dxCommon->GetCommandList());

	enemy->UpdateStateTitle();
}

void TitleScene::DrawSprite()
{
	//UI描画
	ui->DrawTitle(dxCommon->GetCommandList());
}

void TitleScene::DrawParticle()
{
	//プレイヤーのパーティクル描画
	player->DrawParticle(dxCommon->GetCommandList());
}

void TitleScene::DrawFBXLightView()
{
	player->DrawLightView(dxCommon->GetCommandList());
	enemy->DrawLightView(dxCommon->GetCommandList());
}

void TitleScene::SetDevice(DirectXCommon* dxCommon, KeyManager* keyManager)
{
	//引数から代入
	TitleScene::dxCommon = dxCommon;
	TitleScene::keyManager = keyManager;
}

void TitleScene::SetGameObject(Player* player, Enemy* enemy, Plane* plane, Terrain* terrain, Camera* camera, Light* light, UI* ui)
{
	TitleScene::player = player;
	TitleScene::enemy = enemy;
	TitleScene::plane = plane;
	TitleScene::terrain = terrain;
	TitleScene::camera = camera;
	TitleScene::light = light;
	TitleScene::ui = ui;
}

DirectX::XMMATRIX TitleScene::GetLightViewProjection()
{
	return light->GetMatViewProjection();
}

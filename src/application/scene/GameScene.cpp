#include "GameScene.h"
#include "mathOriginal.h"
#include "ColliderManager.h"
#include "ClearScene.h"
#include "TitleScene.h"
#include "PhaseList.h"

KeyManager* PhaseState::keyManager = nullptr;
DirectXCommon* PhaseState::dxCommon = nullptr;
Camera* PhaseState::camera = nullptr;
Light* PhaseState::light = nullptr;
Player* PhaseState::player = nullptr;
Enemy* PhaseState::enemy = nullptr;
TutorialEnemy* PhaseState::tutorialEnemy = nullptr;
Plane* PhaseState::plane = nullptr;
Terrain* PhaseState::terrain = nullptr;
UI* PhaseState::ui = nullptr;

GameScene::GameScene()
{
	phaseState = new MovePhase();
}

GameScene::~GameScene()
{
	delete phaseState;
}

void GameScene::Initialize()
{
	phaseState->Initialize();
}

void GameScene::NextScene(Scene* pScene)
{
	if (moveClearFlag)
	{
		pScene->ChangeScene(new ClearScene());
		moveClearFlag = false;
		return;
	}
	if (moveTitleFlag)
	{
		pScene->ChangeScene(new TitleScene());
		moveTitleFlag = false;
	}
}

void GameScene::Update()
{
	phaseState->Update();
}

void GameScene::Draw()
{
	phaseState->Draw();

	//フェーズ移動
	phaseState->NextPhase(this);
}

void GameScene::DrawFBXLightView()
{
	phaseState->DrawFBXLightView();
}

void GameScene::ChangePhase(PhaseState* newPhase)
{
	debugNum[0] = 1;
	delete phaseState;
	phaseState = newPhase;
}

void PhaseState::SetDevice(DirectXCommon* dxCommon, KeyManager* keyManager)
{
	//引数から代入
	PhaseState::dxCommon = dxCommon;
	PhaseState::keyManager = keyManager;
}

void PhaseState::SetGameObject(Player* player, Enemy* enemy,
	TutorialEnemy* tutorialEnemy, Plane* plane, Terrain* terrain, Camera* camera, Light* light, UI* ui)
{
	PhaseState::player = player;
	PhaseState::enemy = enemy;
	PhaseState::tutorialEnemy = tutorialEnemy;
	PhaseState::plane = plane;
	PhaseState::terrain = terrain;
	PhaseState::camera = camera;
	PhaseState::light = light;
	PhaseState::ui = ui;
}

void PhaseState::Initialize()
{
	//シーン遷移時初期化
	if (phaseTimer == 0)
	{
		PhaseInitialize();
	}
}

void PhaseState::Update()
{
	//フェーズタイマー更新
	phaseTimer += 1;

	//オブジェクト更新
	UpdateObject();

	//コライダー更新
	UpdateCollider();

	if (enemy->GetIsDead() == true)
	{
		//フェーズチェンジフラグ
		phaseChangeFlag = true;
	}
}

void PhaseState::Draw()
{
	//FBX描画
	DrawFBX();

	//パーティクル描画
	DrawParticle();

	//スプライト描画
	DrawSprite();
}

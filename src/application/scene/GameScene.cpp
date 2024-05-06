#include "GameScene.h"
#include "mathOriginal.h"
#include "ColliderManager.h"
#include "imgui.h"
#include "ClearScene.h"
#include "PhaseList.h"

DXInput* PhaseState::dxInput = nullptr;
Input* PhaseState::input = nullptr;
DirectXCommon* PhaseState::dxCommon = nullptr;
Camera* PhaseState::camera = nullptr;
Light* PhaseState::light = nullptr;
Player* PhaseState::player = nullptr;
Enemy* PhaseState::enemy = nullptr;
MiniEnemy* PhaseState::miniEnemy = nullptr;
Plane* PhaseState::plane = nullptr;
UI* PhaseState::ui = nullptr;

GameScene::GameScene()
{
	phaseState = new Phase1();
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

	//ImGui
	ImGui::Begin("GameScene");
	ImGui::SetWindowPos(ImVec2(0, 0));
	ImGui::SetWindowSize(ImVec2(500, 150));
	ImGui::InputInt("debugNum", debugNum);
	ImGui::End();
}

void GameScene::DrawFBXLightView()
{
	phaseState->DrawFBXLightView();
}

void GameScene::SetSRV(ID3D12DescriptorHeap* SRV)
{
	phaseState->SetSRV(SRV);
}

void GameScene::ChangePhase(PhaseState* newPhase)
{
	debugNum[0] = 1;
	delete phaseState;
	phaseState = newPhase;
}

void PhaseState::SetDevice(DirectXCommon* dxCommon, Input* input, DXInput* dxInput)
{
	//引数から代入
	PhaseState::dxCommon = dxCommon;
	PhaseState::input = input;
	PhaseState::dxInput = dxInput;
}

void PhaseState::SetGameObject(Player* player, Enemy* enemy,
	MiniEnemy* miniEnemy, Plane* plane, Camera* camera, Light* light, UI* ui)
{
	PhaseState::player = player;
	PhaseState::enemy = enemy;
	PhaseState::miniEnemy = miniEnemy;
	PhaseState::plane = plane;
	PhaseState::camera = camera;
	PhaseState::light = light;
	PhaseState::ui = ui;
}

void PhaseState::Initialize()
{
	//シーン遷移時初期化
	if (phaseTimer == 0)
	{
		ui->SetGame();
		player->SetGameScene();
	}
}

void PhaseState::Update()
{
	//フェーズタイマー更新
	phaseTimer += 1.0f;

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

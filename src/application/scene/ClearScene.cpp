#include "ClearScene.h"
#include "mathOriginal.h"
#include "TitleScene.h"

DXInput* ClearScene::dxInput = nullptr;
Input* ClearScene::input = nullptr;
DirectXCommon* ClearScene::dxCommon = nullptr;
Camera* ClearScene::camera = nullptr;
Light* ClearScene::light = nullptr;
Player* ClearScene::player = nullptr;
Enemy* ClearScene::enemy = nullptr;
Plane* ClearScene::plane = nullptr;
UI* ClearScene::ui = nullptr;

void ClearScene::SetDevice(DirectXCommon* dxCommon, Input* input, DXInput* dxInput)
{
	//引数から代入
	ClearScene::dxCommon = dxCommon;
	ClearScene::input = input;
	ClearScene::dxInput = dxInput;
}

void ClearScene::SetGameObject(Player* player, Enemy* enemy, Plane* plane, Camera* camera, Light* light, UI* ui)
{
	ClearScene::player = player;
	ClearScene::enemy = enemy;
	ClearScene::plane = plane;
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
	//黒いスプライト1
	Sprite* newBlackSprite1 = new Sprite();
	newBlackSprite1->Initialize();
	blackSprite1.reset(newBlackSprite1);
	blackSprite1->SetTextureNum(14);
	blackSprite1->SetPosition(black1Pos);
	blackSprite1->SetScale(black1Scale);
	//黒いスプライト2
	Sprite* newBlackSprite2 = new Sprite();
	newBlackSprite2->Initialize();
	blackSprite2.reset(newBlackSprite2);
	blackSprite2->SetTextureNum(14);
	blackSprite2->SetPosition(black2Pos);
	blackSprite2->SetScale(black2Scale);
	//クリアのスプライト1
	Sprite* newClear1Sprite = new Sprite();
	newClear1Sprite->Initialize();
	clear1Sprite.reset(newClear1Sprite);
	clear1Sprite->SetTextureNum(21);
	clear1Sprite->SetPosition(clear1Pos);
	clear1Sprite->SetScale(clear1Scale);
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
	//カメラ更新
	camera->UpdateClear(enemy->GetPosition(), clearFromGameTimer);
	camera->Update();

	//ライト
	light->SetEye(XMFLOAT3(lightPos) + player->GetPosition());
	light->SetTarget(XMFLOAT3(lightTarget) + player->GetPosition());
	light->SetDir(XMFLOAT3(lightDir));
	light->Update();

	//プレイヤー
	player->UpdateGame();

	//敵
	enemy->UpdateGame1();
}

void ClearScene::UpdateSprite()
{
	//スプライト更新
	blackSprite1->SetPosition(XMFLOAT2(0.0f, -620.0f));
	blackSprite1->SetScale(XMFLOAT2(1280.0f, 720.0f));
	blackSprite1->SetAlpha(1.0f);
	blackSprite2->SetPosition(XMFLOAT2(0.0f, 620.0f));
	blackSprite2->SetScale(XMFLOAT2(1280.0f, 720.0f));
	blackSprite2->SetAlpha(1.0f);
	blackSprite1->Update();
	blackSprite2->Update();
	clear1Sprite->Update();
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
}

void ClearScene::DrawSprite()
{
	blackSprite1->Draw(dxCommon->GetCommandList());
	blackSprite2->Draw(dxCommon->GetCommandList());
	if (clearFromGameTimer >= clearFromGameTime)clear1Sprite->Draw(dxCommon->GetCommandList());
}

void ClearScene::DrawParticle()
{
	//プレイヤーのパーティクル描画
	player->DrawParticle(dxCommon->GetCommandList());
}

void ClearScene::DrawFBXLightView()
{
	player->DrawLightView(dxCommon->GetCommandList());
	enemy->DrawLightView(dxCommon->GetCommandList());
}

void ClearScene::SetSRV(ID3D12DescriptorHeap* SRV)
{
	player->SetSRV(SRV);
	enemy->SetSRV(SRV);
}

DirectX::XMMATRIX ClearScene::GetLightViewProjection()
{
	return light->GetMatViewProjection();
}

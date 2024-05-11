#include "TutorialScene.h"
#include "mathOriginal.h"
#include "ColliderManager.h"
#include "GameScene.h"

DXInput* TutorialScene::dxInput = nullptr;
Input* TutorialScene::input = nullptr;
DirectXCommon* TutorialScene::dxCommon = nullptr;
Camera* TutorialScene::camera = nullptr;
Light* TutorialScene::light = nullptr;
Player* TutorialScene::player = nullptr;
Enemy* TutorialScene::enemy = nullptr;
TutorialEnemy* TutorialScene::tutorialEnemy = nullptr;
Plane* TutorialScene::plane = nullptr;
Terrain* TutorialScene::terrain = nullptr;
UI* TutorialScene::ui = nullptr;

TutorialScene::TutorialScene()
{
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::Initialize()
{
	//シーン繊維したタイミングで初期化
	if (gameTimer == 0)
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
		//黒いスプライト2
		Sprite* newBlackSprite3 = new Sprite();
		newBlackSprite3->Initialize();
		blackSprite3.reset(newBlackSprite3);
		blackSprite3->SetTextureNum(14);
		blackSprite3->SetPosition(black3Pos);
		blackSprite3->SetScale(black3Scale);
	}
}

void TutorialScene::Update()
{
	if (gameTimer == 0.0f)
	{
		player->SetPosition(XMFLOAT3(0.0f, 0.0f, 0.0f));
	}
	gameTimer += 1.0f;

	//オブジェクト更新
	UpdateObject();

	//スプライト更新
	UpdateSprite();

	//コライダー更新
	UpdateCollider();

	//パーティクル更新
	UpdateParticle();
}

void TutorialScene::NextScene(Scene* pScene)
{
	if (moveGameFlag)
	{
		pScene->ChangeScene(new GameScene());
	}
}

void TutorialScene::UpdateObject()
{
	//カメラ更新
	if (tutorialSpriteFlag == 13)
	{
		camera->UpdateTutorial(tutorial13Timer);
	}
	else
	{
		camera->UpdatePlayer(player->GetPosition(), player->GetRotation0());
	}
	/*camera_->DebugUpdate();*/
	camera->Update();

	//ライト
	light->SetEye(XMFLOAT3(lightPos) + player->GetPosition());
	light->SetTarget(XMFLOAT3(lightTarget) + player->GetPosition());
	light->SetDir(XMFLOAT3(lightDir));
	light->Update();

	//敵
	enemy->UpdateTutorial(tutorial13Timer);

	//チュートリアルの敵
	if (tutorialSpriteFlag == 10)
	{
		tutorialEnemy->Update();
		//敵を倒したら次へ
		if (tutorialEnemy->GetIsDead())
		{
			tutorialSpriteFlag = 11;
			tutorialEnemy->Reset();
		}
	}

	//UI
	ui->SetTutorialFlag(tutorialSpriteFlag);
	ui->SetPlayerForm(player->GetPlayerForm(),player->GetFormChangeFlag());
	ui->SetTutorialTimer(tutorialLStickTimer, tutorialLStickMaxTime, tutorialRStickTimer, tutorialRStickMaxTime,
		tutorialAttackTimer, tutorialAttackMaxTime, tutorialAttack2Timer
		, tutorialAttack2MaxTime,tutorialIikannjiTimer, tutorialIikannjiMaxTime,tutorial12Timer, tutorial12MaxTime);
	ui->UpdateTutorial();

	//プレイヤー
	player->SetEnemyPos(tutorialEnemy->GetPosition());
	player->SetEnemyPos(enemy->GetPosition());
	player->SetTutorialFlag(tutorialSpriteFlag);
	player->UpdateTutorial();

	//床
	plane->Update();

	//地形
	terrain->Update();
}

void TutorialScene::UpdateSprite()
{
	//スキップ
	if (tutorialSpriteFlag < 12 && dxInput->TriggerKey(DXInput::PAD_START))
	{
		tutorialSpriteFlag = 12;
	}
	//スプライトの処理
	//黒幕
	if (tutorialSpriteFlag == 1)
	{
		blackSpriteTimer++;
		blackSprite3->SetAlpha((blackSpriteMaxTime - blackSpriteTimer) / blackSpriteMaxTime);
		//時間経過でスティック操作チュートリアルへ
		if (blackSpriteTimer >= blackSpriteMaxTime)
		{
			blackSpriteTimer = 0;
			tutorialSpriteFlag = 2;
		}
	}
	//スティック操作チュートリアル
	if (tutorialSpriteFlag == 2)
	{
		//Rスティックの入力があればタイマー更新
		if (dxInput->GetStick(DXInput::RStickX) >= 0.4 || dxInput->GetStick(DXInput::RStickX) <= -0.4 ||
			dxInput->GetStick(DXInput::RStickY) >= 0.4 || dxInput->GetStick(DXInput::RStickY) <= -0.4)
		{
			tutorialRStickTimer++;
		}
		//Lスティックの入力があればタイマー更新
		if (dxInput->GetStick(DXInput::LStickX) >= 0.4 || dxInput->GetStick(DXInput::LStickX) <= -0.4 ||
			dxInput->GetStick(DXInput::LStickY) >= 0.4 || dxInput->GetStick(DXInput::LStickY) <= -0.4)
		{
			tutorialLStickTimer++;
		}
		//どっちも達成で次へ
		if (tutorialLStickTimer >= tutorialLStickMaxTime && tutorialRStickTimer >= tutorialRStickMaxTime)
		{
			tutorialSpriteFlag = 3;
		}
	}
	//いい感じチュートリアル
	if (tutorialSpriteFlag == 3)
	{
		tutorialIikannjiTimer++;
		//時間経過で攻撃チュートリアルへ
		if (tutorialIikannjiTimer >= tutorialIikannjiMaxTime)
		{
			tutorialIikannjiTimer = 0;
			tutorialSpriteFlag = 4;
		}
	}
	//攻撃チュートリアル
	if (tutorialSpriteFlag == 4)
	{
		if (dxInput->PushKey(DXInput::PAD_RIGHT_SHOULDER) == 1)
		{
			tutorialAttackTimer++;
		}
		//達成で次へ
		if (tutorialAttackTimer >= tutorialAttackMaxTime)
		{
			tutorialSpriteFlag = 5;
		}
	}
	//いい感じチュートリアル
	if (tutorialSpriteFlag == 5)
	{
		tutorialIikannjiTimer++;
		//時間経過で攻撃チュートリアルへ
		if (tutorialIikannjiTimer >= tutorialIikannjiMaxTime)
		{
			tutorialIikannjiTimer = 0;
			tutorialSpriteFlag = 6;
		}
	}
	//属性変化チュートリアル
	if (tutorialSpriteFlag == 6)
	{
		if (dxInput->PushKey(DXInput::PAD_LEFT_SHOULDER) == 1)
		{
			tutorialSpriteFlag = 7;
		}
	}
	//属性変化チュートリアル2
	if (tutorialSpriteFlag == 7)
	{
		tutorialIikannjiTimer++;
		//時間経過で攻撃チュートリアルへ
		if (tutorialIikannjiTimer >= tutorialIikannjiMaxTime)
		{
			tutorialIikannjiTimer = 0;
			tutorialSpriteFlag = 8;
		}
	}
	//攻撃チュートリアル
	if (tutorialSpriteFlag == 8)
	{
		if (dxInput->TriggerKey(DXInput::PAD_RIGHT_SHOULDER) == 1)
		{
			tutorialAttack2Timer++;
		}
		//達成で次へ
		if (tutorialAttack2Timer >= tutorialAttack2MaxTime)
		{
			tutorialSpriteFlag = 9;
		}
	}
	//属性変化チュートリアル2
	if (tutorialSpriteFlag == 9)
	{
		tutorialIikannjiTimer++;
		//時間経過で攻撃チュートリアルへ
		if (tutorialIikannjiTimer >= tutorialIikannjiMaxTime)
		{
			//カメラの向きのベクトル取得
			XMFLOAT3 velo = camera->GetTarget() - camera->GetEye();
			velo = normalize(velo);
			velo = velo * 20.0f;
			//カメラ方向に敵配置
			tutorialEnemy->SetPosition({ velo.x,0.0f, velo.z });
			tutorialSpriteFlag = 10;
		}
	}
	//いい感じチュートリアル
	if (tutorialSpriteFlag == 11)
	{
		tutorialIikannjiTimer++;
		//時間経過でチュートリアル終了
		if (tutorialIikannjiTimer >= tutorialIikannjiMaxTime)
		{
			tutorialSpriteFlag = 12;
			tutorialIikannjiTimer = 0;
		}
	}
	//敵登場までの間
	if (tutorialSpriteFlag == 12)
	{
		tutorial12Timer++;
		//時間経過でチュートリアル終了
		if (tutorial12Timer >= tutorial12MaxTime)
		{
			tutorialSpriteFlag = 13;
		}
	}
	if (tutorialSpriteFlag == 13)
	{
		tutorial13Timer++;
		//黒幕
		if (tutorial13Timer >= tutorial13MaxTime)
		{
			blackSpriteTimer++;
		}
		blackSprite3->SetAlpha(blackSpriteTimer / blackSpriteMaxTime);
		//時間経過でチュートリアル終了
		if (tutorial13Timer >= tutorial13MaxTime + blackSpriteMaxTime)
		{
			//リセット
			Reset();
			//プレイヤーをゲームにセット
			player->SetGameScene();
			//敵をゲームにセット
			enemy->SetGameScene();
			//ゲームに移る
			moveGameFlag = true;
		}
	}
	//スプライト更新
	blackSprite1->Update();
	blackSprite2->Update();
	blackSprite3->Update();
}

void TutorialScene::UpdateCollider()
{
	//事前処理
	ColliderManager::PreUpdate();

	//時機の弾(炎)と敵の当たり判定
	for (int i = 0; i < player->GetBullet1Num(); i++)
	{
		if (ColliderManager::CheckCollider(tutorialEnemy->GetColliderData(), player->GetBullet1ColliderData(i)))
		{
			//敵にヒットフラグ送信
			tutorialEnemy->HitBullet1();
			//自機にヒットフラグ送信
			player->HitBullet1(i);
		}
	}

	//雷攻撃が当たったら
	if (player->GetHitElec())
	{
		//敵にヒットフラグ送信
		tutorialEnemy->HitElec();
	}

	//後処理
	ColliderManager::PostUpdate();
}

void TutorialScene::UpdateParticle()
{
}

void TutorialScene::Reset()
{
	//タイマーリセット
	blackSpriteTimer = 0;
	tutorialLStickTimer = 0.0f;
	tutorialRStickTimer = 0.0f;
	tutorialIikannjiTimer = 0.0f;
	tutorialAttackTimer = 0.0f;
	tutorialAttack2Timer = 0.0f;
	tutorial12Timer = 0;
	tutorial13Timer = 0;
	//フラグを元に戻す
	tutorialSpriteFlag = 1;
}

void TutorialScene::Draw()
{
	//FBX描画
	DrawFBX();

	//パーティクル描画
	DrawParticle();

	//スプライト描画
	DrawSprite();

	ColliderManager::Draw(dxCommon->GetCommandList());
}

void TutorialScene::DrawFBX()
{
	player->Draw(dxCommon->GetCommandList());
	enemy->Draw(dxCommon->GetCommandList());
	if (tutorialSpriteFlag == 10)tutorialEnemy->Draw(dxCommon->GetCommandList());
	plane->Draw(dxCommon->GetCommandList());
	terrain->Draw(dxCommon->GetCommandList());
}

void TutorialScene::DrawSprite()
{
	//黒幕
	if (tutorialSpriteFlag == 13)
	{
		blackSprite1->Draw(dxCommon->GetCommandList());
		blackSprite2->Draw(dxCommon->GetCommandList());
	}
	if (tutorialSpriteFlag == 1 || tutorialSpriteFlag == 13)
	{
		blackSprite3->Draw(dxCommon->GetCommandList());
	}
	//UI描画
	ui->DrawTutorial(dxCommon->GetCommandList());
	player->DrawSpriteTutorial(dxCommon->GetCommandList());
	if(tutorialSpriteFlag == 10)tutorialEnemy->DrawSprite(dxCommon->GetCommandList());
}

void TutorialScene::DrawParticle()
{
	//プレイヤーのパーティクル描画
	player->DrawParticle(dxCommon->GetCommandList());
}

void TutorialScene::DrawFBXLightView()
{
	player->DrawLightView(dxCommon->GetCommandList());
	enemy->DrawLightView(dxCommon->GetCommandList());
	if (tutorialSpriteFlag == 10)tutorialEnemy->DrawLightView(dxCommon->GetCommandList());
}

void TutorialScene::SetSRV(ID3D12DescriptorHeap* SRV)
{
	player->SetSRV(SRV);
	enemy->SetSRV(SRV);
	if (tutorialSpriteFlag == 10)tutorialEnemy->SetSRV(SRV);
	plane->SetSRV(SRV);
}

void TutorialScene::SetDevice(DirectXCommon* dxCommon, Input* input, DXInput* dxInput)
{
	// 引数から代入
	TutorialScene::dxCommon = dxCommon;
	TutorialScene::input = input;
	TutorialScene::dxInput = dxInput;
}

void TutorialScene::SetGameObject(Player* player, Enemy* enemy, TutorialEnemy* tutorialEnemy,
	Plane* plane, Terrain* terrain, Camera* camera, Light* light, UI* ui)
{
	TutorialScene::player = player;
	TutorialScene::enemy = enemy;
	TutorialScene::tutorialEnemy = tutorialEnemy;
	TutorialScene::plane = plane;
	TutorialScene::terrain = terrain;
	TutorialScene::camera = camera;
	TutorialScene::light = light;
	TutorialScene::ui = ui;
}

//void TutorialScene::SetGameObject(Player* player, Enemy* enemy, TutorialEnemy* tutorialEnemy, Plane* plane, Camera* camera, Light* light, UI* ui)
//{
//	this->player = player;
//	this->enemy = enemy;
//	this->tutorialEnemy = tutorialEnemy;
//	this->plane = plane;
//	this->camera = camera;
//	this->light = light;
//	this->ui = ui;
//}

DirectX::XMMATRIX TutorialScene::GetLightViewProjection()
{
	return light->GetMatViewProjection();
}

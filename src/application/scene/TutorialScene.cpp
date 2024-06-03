#include "TutorialScene.h"
#include "mathOriginal.h"
#include "ColliderManager.h"
#include "GameScene.h"

KeyManager* TutorialScene::keyManager = nullptr;
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
		//プレイヤーをチュートリアル用にセット
		player->SetTutorial();

		//敵をチュートリアル用にセット
		enemy->SetTutorial();

		//チュートリアルの敵をセット
		tutorialEnemy->SetTutorial();

		//UIをセット
		ui->SetTutorial();
	}
}

void TutorialScene::Update()
{
	if (gameTimer == 0.0f)
	{
		player->SetPosition(XMFLOAT3(0.0f, 0.0f, 0.0f));
	}
	gameTimer += 1.0f;

	//スプライト更新
	UpdateSprite();

	//パーティクル更新
	UpdateParticle();

	//オブジェクト更新
	UpdateObject();

	//コライダー更新
	UpdateCollider();

	//カメラ更新
	if (tutorialSpriteFlag == 15)
	{
		camera->UpdateTutorial(tutorial13Timer);
	}
	else
	{
		camera->UpdatePlayer(player->GetPosition(), player->GetRotation0());
	}
	/*camera_->DebugUpdate();*/
	camera->Update();
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
	//ライト
	light->SetEye(XMFLOAT3(lightPos) + player->GetPosition());
	light->SetTarget(XMFLOAT3(lightTarget) + player->GetPosition());
	light->SetDir(XMFLOAT3(lightDir));
	light->Update();

	//敵
	enemy->UpdateTutorial(tutorial13Timer);

	//チュートリアルの敵
	tutorialEnemy->SetPlayerPos(player->GetPosition());
	tutorialEnemy->SetTutorialFlag(tutorialSpriteFlag);
	tutorialEnemy->UpdateTutorial();
	//敵を倒したら次へ
	if (tutorialEnemy->GetIsDead() && tutorialSpriteFlag == 10)
	{
		tutorialSpriteFlag = 11;
	}

	//UI
	ui->SetTutorialFlag(tutorialSpriteFlag);
	ui->SetPlayerForm(player->GetPlayerForm(),player->GetFormChangeFlag());
	ui->SetTutorialTimer(tutorialLStickTimer, tutorialLStickMaxTime, tutorialRStickTimer, tutorialRStickMaxTime,
		tutorialAttackTimer, tutorialAttackMaxTime, tutorialAttack2Timer
		, tutorialAttack2MaxTime,tutorialIikannjiTimer, tutorialIikannjiMaxTime,tutorial12Timer, tutorial12MaxTime,
		tutorial13Timer, tutorial13MaxTime);
	ui->UpdateTutorial();

	//プレイヤー
	player->SetEnemyPos(tutorialEnemy->GetPosition(), tutorialEnemy->GetAddPos());
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
	if (tutorialSpriteFlag < 14 && keyManager->TriggerKey(KeyManager::PAD_START))
	{
		tutorialSpriteFlag = 14;
	}
	//スプライトの処理
	//黒幕
	if (tutorialSpriteFlag == 1)
	{
		blackSpriteTimer++;
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
		if (keyManager->GetStick(KeyManager::RStickX) >= 0.4 || keyManager->GetStick(KeyManager::RStickX) <= -0.4 ||
			keyManager->GetStick(KeyManager::RStickY) >= 0.4 || keyManager->GetStick(KeyManager::RStickY) <= -0.4)
		{
			tutorialRStickTimer++;
		}
		//Lスティックの入力があればタイマー更新
		if (keyManager->GetStick(KeyManager::LStickX) >= 0.4 || keyManager->GetStick(KeyManager::LStickX) <= -0.4 ||
			keyManager->GetStick(KeyManager::LStickY) >= 0.4 || keyManager->GetStick(KeyManager::LStickY) <= -0.4)
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
		if (keyManager->PushKey(KeyManager::PAD_RIGHT_SHOULDER) == 1)
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
		if (keyManager->PushKey(KeyManager::PAD_LEFT_SHOULDER) == 1)
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
		if (keyManager->TriggerKey(KeyManager::PAD_RIGHT_SHOULDER) == 1)
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
			//カメラ方向に敵配置
			tutorialIikannjiTimer = 0;
			tutorialEnemy->AddEnemyTutorialScene(XMFLOAT3(0.0f,0.0f,0.0f));
			tutorialSpriteFlag = 10;
		}
	}
	//敵が登場した
	if (tutorialSpriteFlag == 10)
	{
		tutorial10Timer++;
		//時間経過で攻撃チュートリアルへ
		if (tutorial10Timer >= tutorial10MaxTime)
		{
			tutorialSpriteFlag = 11;
			tutorial10Timer = 0;
			//ダッシュフラグをセットする
			tutorialEnemy->SetTutorialDashFlag();
		}
	}
	//走ってくる
	if (tutorialSpriteFlag == 11)
	{
		//柱にぶつけて倒したら次へ
		if (tutorialEnemy->GetTutorialDownFlag())
		{
			tutorialSpriteFlag = 12;
		}
	}
	//敵が倒れているうちに攻撃
	if (tutorialSpriteFlag == 12)
	{
		//敵を倒したら次へ移動
		if (tutorialEnemy->GetIsDead() == true)
		{
			tutorialSpriteFlag = 13;
		}
	}
	//敵を倒した！
	if (tutorialSpriteFlag == 13)
	{
		tutorialIikannjiTimer++;
		//時間経過でチュートリアル終了
		if (tutorialIikannjiTimer >= tutorialIikannjiMaxTime)
		{
			tutorialSpriteFlag = 14;
			tutorialIikannjiTimer = 0;
		}
	}
	//ボス登場までの間 
	if (tutorialSpriteFlag == 14)
	{
		tutorial12Timer++;
		//時間経過でチュートリアル終了
		if (tutorial12Timer >= tutorial12MaxTime)
		{
			tutorialSpriteFlag = 15;
		}
	}
	//ボス登場
	if (tutorialSpriteFlag == 15)
	{
		tutorial13Timer++;
		//黒幕
		if (tutorial13Timer >= tutorial13MaxTime)
		{
			blackSpriteTimer++;
		}
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
}

void TutorialScene::UpdateCollider()
{
	//カメラ当たり判定更新
	camera->SetObjectCollider(terrain->GetColliderData());

	//敵の当たり判定更新
	tutorialEnemy->SetObjectCollider(terrain->GetColliderData());
	tutorialEnemy->UpdateObjectCollider();

	//プレイヤー当たり判定更新
	player->SetObjectCollider(terrain->GetColliderData());
	player->UpdateCollider();

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
}

void TutorialScene::UpdateParticle()
{
}

void TutorialScene::Reset()
{
	//タイマーリセット
	blackSpriteTimer = 0;
	tutorialLStickTimer = 0;
	tutorialRStickTimer = 0;
	tutorialIikannjiTimer = 0;
	tutorialAttackTimer = 0;
	tutorialAttack2Timer = 0;
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
}

void TutorialScene::DrawFBX()
{
	//オブジェクト描画
	player->Draw(dxCommon->GetCommandList());
	enemy->Draw(dxCommon->GetCommandList());
	tutorialEnemy->Draw(dxCommon->GetCommandList());
	plane->Draw(dxCommon->GetCommandList());
	terrain->Draw(dxCommon->GetCommandList());

	//ステート更新
	player->UpdateState();
	enemy->UpdateStateTutorial();
}

void TutorialScene::DrawSprite()
{
	//UI描画
	ui->DrawTutorial(dxCommon->GetCommandList());
	player->DrawSpriteTutorial(dxCommon->GetCommandList());
	if(tutorialSpriteFlag == 10 || tutorialSpriteFlag == 11 || tutorialSpriteFlag == 12)tutorialEnemy->DrawSprite(dxCommon->GetCommandList());
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
	tutorialEnemy->DrawLightView(dxCommon->GetCommandList());
}

void TutorialScene::SetSRV(ID3D12DescriptorHeap* SRV)
{
	player->SetSRV(SRV);
	enemy->SetSRV(SRV);
	tutorialEnemy->SetSRV(SRV);
	plane->SetSRV(SRV);
}

void TutorialScene::SetDevice(DirectXCommon* dxCommon, KeyManager* keyManager)
{
	// 引数から代入
	TutorialScene::dxCommon = dxCommon;
	TutorialScene::keyManager = keyManager;
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

DirectX::XMMATRIX TutorialScene::GetLightViewProjection()
{
	return light->GetMatViewProjection();
}

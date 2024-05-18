#include "PhaseList.h"
#include "mathOriginal.h"
#include "ColliderManager.h"
#include "imgui.h"

void Phase1::PhaseInitialize()
{
	ui->SetGame();
	player->SetGameScene();
	enemy->SetGameScene();
}

void Phase1::DrawFBXLightView()
{
	//SRVをセット
	player->DrawLightView(dxCommon->GetCommandList());
	enemy->DrawLightView(dxCommon->GetCommandList());
}

void Phase1::SetSRV(ID3D12DescriptorHeap* SRV)
{
	//SRVをセット
	player->SetSRV(SRV);
	enemy->SetSRV(SRV);
	plane->SetSRV(SRV);
}

void Phase1::NextPhase(GameScene* gameScene)
{
	//フェーズチェンジフラグがたったら
	if (phaseChangeFlag == true)
	{
		//タイマーリセット
		phaseTimer = 0;
		//敵リセット
		enemy->Reset();
		//次のフェーズへ
		gameScene->ChangePhase(new MovePhase());
	}
}

void Phase1::UpdateObject()
{
	//カメラ更新
	camera->UpdatePlayer(player->GetPosition(), player->GetRotation0());
	camera->Update();

	//ライト更新
	light->SetEye(XMFLOAT3(lightPos) + player->GetPosition());
	light->SetTarget(XMFLOAT3(lightTarget) + player->GetPosition());
	light->SetDir(XMFLOAT3(lightDir));
	/*light->SetEye(XMFLOAT3(debugLightPos));
	light->SetTarget(XMFLOAT3(debugLightTarget));
	light->SetDir(XMFLOAT3(debugLightDir));*/
	light->Update();

	//敵
	enemy->SetPlayerPos(player->GetPosition());
	enemy->SetPhaseTimer(phaseTimer);
	enemy->UpdateGame1();

	//UI
	ui->SetPlayerForm(player->GetPlayerForm(), player->GetFormChangeFlag());
	ui->SetPhaseTimer(phaseTimer);
	ui->SetHP(player->GetHP(), player->GetMaxHP(), enemy->GetHP(), enemy->GetMaxHP());
	ui->UpdateGame1();

	//プレイヤー
	player->SetEnemyPos(enemy->GetPosition(), enemy->GetAddPos());
	player->UpdateGame();

	//床
	plane->Update();

	//地形
	terrain->Update();
}

void Phase1::UpdateCollider()
{
	//事前処理
	ColliderManager::PreUpdate();

	//プレイヤー当たり判定更新
	player->SetObjectCollider(terrain->GetColliderData());
	player->UpdateCollider();

	//敵のあたり判定更新
	enemy->SetObjectCollider(terrain->GetColliderData());
	enemy->UpdateCollider();

	//敵の弾と時機の当たり判定
	if (player->GetInvincibleFlag() == false)
	{
		for (int i = 0; i < enemy->GetBulletNum(); i++)
		{
			if (ColliderManager::CheckCollider(player->GetColliderData(), enemy->GetBulletColliderData(i)))
			{
				//自機にヒットフラグ送信
				player->HitEnemy();
			}
		}
	}

	//敵と時機の当たり判定
	if (player->GetInvincibleFlag() == false)
	{
		if (ColliderManager::CheckCollider(player->GetColliderData(), enemy->GetColliderData()))
		{
			//自機にヒットフラグ送信
			player->HitEnemy();
			//敵にヒットフラグ送信
			enemy->SetHitPlayer();
		}
	}

	////時機の弾(炎)と敵の当たり判定
	for (int i = 0; i < player->GetBullet1Num(); i++)
	{
		if (ColliderManager::CheckCollider(enemy->GetColliderData(), player->GetBullet1ColliderData(i)))
		{
			//敵にヒットフラグ送信
			enemy->HitBullet1();
			//自機にヒットフラグ送信
			player->HitBullet1(i);
		}
	}

	//雷攻撃が当たったら
	if (player->GetHitElec())
	{
		//敵にヒットフラグ送信
		enemy->HitElec();
	}

	//敵の弾と平面の判定
	//for (std::unique_ptr<FbxObject3D>& object1 : object)
	//{
	//	if (object1->GetFileName() == "plane")
	//	{
	//		for (int i = 0; i < enemy->GetBulletNum(); i++)
	//		{
	//			if (ColliderManager::CheckCollider(object1->GetColliderData(), enemy->GetBulletColliderData(i)))
	//			{
	//				//当たったらパーティクル発生
	//				sparkParticle2->Add(XMFLOAT3(enemy->GetBulletColliderData(i).center));
	//				explosionParticle1->Add(XMFLOAT3(enemy->GetBulletColliderData(i).center));
	//				explosionParticle2->Add(XMFLOAT3(enemy->GetBulletColliderData(i).center));
	//			}
	//		}
	//	}
	//}

	//後処理
	ColliderManager::PostUpdate();
}

void Phase1::DrawFBX()
{
	//FBX描画
	player->Draw(dxCommon->GetCommandList());
	enemy->Draw(dxCommon->GetCommandList());
	plane->Draw(dxCommon->GetCommandList());
	terrain->Draw(dxCommon->GetCommandList());

	//ステート更新
	player->UpdateState();
	enemy->UpdateStateGame();

	//コライダー描画
	ColliderManager::Draw(dxCommon->GetCommandList());

	//ImGui
	//ImGui::Begin("Phase1");
	//ImGui::SetWindowPos(ImVec2(500, 300));
	//ImGui::SetWindowSize(ImVec2(500, 150));
	////ImGui::InputFloat2("debugPos", debugPos);
	//ImGui::InputFloat3("lightPos", debugLightPos);
	//ImGui::InputFloat3("lightTarget", debugLightTarget);
	//ImGui::InputFloat3("lightDir", debugLightDir);
	//ImGui::End();
}

void Phase1::DrawSprite()
{
	//UI描画
	ui->DrawGame1(dxCommon->GetCommandList());

	//プレイヤーのスプライト描画
	player->DrawSpriteGame(dxCommon->GetCommandList());
}

void Phase1::DrawParticle()
{
	//プレイヤーのパーティクル描画
	player->DrawParticle(dxCommon->GetCommandList());
	//敵のパーティクル描画
	enemy->DrawParticle(dxCommon->GetCommandList());
}

void Phase2::PhaseInitialize()
{
	ui->SetGame();
	player->SetGameScene();
	enemy->SetGameScene();
}

void Phase2::DrawFBXLightView()
{
	/*miniEnemy->DrawLightView(dxCommon->GetCommandList());*/
	player->DrawLightView(dxCommon->GetCommandList());
	enemy->DrawLightView(dxCommon->GetCommandList());
}

void Phase2::SetSRV(ID3D12DescriptorHeap* SRV)
{	
	//SRVをセット
	/*miniEnemy->SetSRV(SRV);*/
	player->SetSRV(SRV);
	enemy->SetSRV(SRV);
	plane->SetSRV(SRV);;
}

void Phase2::NextPhase(GameScene* gameScene)
{
	//フェーズチェンジフラグがたったら
	if (phaseChangeFlag == true)
	{
		//タイマーリセット
		phaseTimer = 0;
		//敵リセット
		enemy->Reset();
		//クリアシーンへ
		gameScene->SetMoveClearFlag(true);
	}
}

void Phase2::UpdateObject()
{
	//カメラ更新
	camera->UpdatePlayer(player->GetPosition(), player->GetRotation0());
	camera->Update();

	//ライト更新
	light->SetEye(XMFLOAT3(lightPos) + player->GetPosition());
	light->SetTarget(XMFLOAT3(lightTarget) + player->GetPosition());
	light->SetDir(XMFLOAT3(lightDir));
	/*light->SetEye(XMFLOAT3(debugLightPos));
	light->SetTarget(XMFLOAT3(debugLightTarget));
	light->SetDir(XMFLOAT3(debugLightDir));*/
	light->Update();

	//敵
	enemy->SetPlayerPos(player->GetPosition());
	enemy->SetPhaseTimer(phaseTimer);
	enemy->UpdateGame2();

	//小さい敵
	/*if (enemy->GetCallEnemyFlag())
	{
		miniEnemy->AddEnemy(enemy->GetCallEnemyPos());
	}
	miniEnemy->SetPlayerPos(player->GetPosition());
	miniEnemy->Update();*/

	//UI
	ui->SetPlayerForm(player->GetPlayerForm(), player->GetFormChangeFlag());
	ui->SetPhaseTimer(phaseTimer);
	ui->SetHP(player->GetHP(),player->GetMaxHP(), enemy->GetHP(), enemy->GetMaxHP());
	ui->UpdateGame2();

	//プレイヤー
	player->SetEnemyPos(enemy->GetPosition(), enemy->GetAddPos());
	player->UpdateGame();

	//床
	plane->Update();

	//地形
	terrain->Update();
}

void Phase2::UpdateCollider()
{
	//事前処理
	ColliderManager::PreUpdate();

	//プレイヤー当たり判定更新
	player->SetObjectCollider(terrain->GetColliderData());
	player->UpdateCollider();

	//敵のあたり判定更新
	enemy->SetObjectCollider(terrain->GetColliderData());
	enemy->UpdateCollider();

	//敵の弾と時機の当たり判定
	if (player->GetInvincibleFlag() == false)
	{
		for (int i = 0; i < enemy->GetBulletNum(); i++)
		{
			if (ColliderManager::CheckCollider(player->GetColliderData(), enemy->GetBulletColliderData(i)))
			{
				//自機にヒットフラグ送信
				player->HitEnemy();
			}
		}
	}

	//敵と時機の当たり判定
	if (player->GetInvincibleFlag() == false)
	{
		if (ColliderManager::CheckCollider(player->GetColliderData(), enemy->GetColliderData()))
		{
			//自機にヒットフラグ送信
			player->HitEnemy();
			//敵にヒットフラグ送信
			enemy->SetHitPlayer();
		}
	}

	////時機の弾(炎)と敵の当たり判定
	for (int i = 0; i < player->GetBullet1Num(); i++)
	{
		if (ColliderManager::CheckCollider(enemy->GetColliderData(), player->GetBullet1ColliderData(i)))
		{
			//敵にヒットフラグ送信
			enemy->HitBullet1();
			//自機にヒットフラグ送信
			player->HitBullet1(i);
		}
	}

	//雷攻撃が当たったら
	if (player->GetHitElec())
	{
		//敵にヒットフラグ送信
		enemy->HitElec();
	}

	//時機と小さい敵の当たり判定
	//for (int i = 0; i < miniEnemy->GetEnemyNum(); i++)
	//{
	//	for (int j = 0; j < player->GetBullet1Num(); j++)
	//	{
	//		if (ColliderManager::CheckCollider(miniEnemy->GetColliderData(i), player->GetBullet1ColliderData(j)))
	//		{
	//			//敵にヒットフラグ送信
	//			miniEnemy->HitFire(i);
	//			//自機にヒットフラグ送信
	//			player->HitBullet1(j);
	//		}
	//	}
	//}

	//後処理
	ColliderManager::PostUpdate();
}

void Phase2::DrawFBX()
{
	//FBX描画
	/*miniEnemy->Draw(dxCommon->GetCommandList());*/
	player->Draw(dxCommon->GetCommandList());
	enemy->Draw(dxCommon->GetCommandList());
	plane->Draw(dxCommon->GetCommandList());
	terrain->Draw(dxCommon->GetCommandList());

	//ステート更新
	player->UpdateState();
	enemy->UpdateStateGame();
}

void Phase2::DrawSprite()
{
	//UI描画
	ui->DrawGame2(dxCommon->GetCommandList());

	//プレイヤーのスプライト描画
	player->DrawSpriteGame(dxCommon->GetCommandList());
}

void Phase2::DrawParticle()
{
	//プレイヤーのパーティクル描画
	player->DrawParticle(dxCommon->GetCommandList());
	//敵のパーティクル描画
	enemy->DrawParticle(dxCommon->GetCommandList());
}

void MovePhase::PhaseInitialize()
{
	ui->SetMovePhase();
	player->SetMovePhase();
	enemy->SetMovePhase();
}

void MovePhase::DrawFBXLightView()
{
	//ライト目線描画
	//miniEnemy->DrawLightView(dxCommon->GetCommandList());
	player->DrawLightView(dxCommon->GetCommandList());
	enemy->DrawLightView(dxCommon->GetCommandList());
}

void MovePhase::SetSRV(ID3D12DescriptorHeap* SRV)
{
	//SRVをセット
	/*miniEnemy->SetSRV(SRV);*/
	player->SetSRV(SRV);
	enemy->SetSRV(SRV);
	plane->SetSRV(SRV);
}

void MovePhase::NextPhase(GameScene* gameScene)
{
	//フェーズチェンジフラグがたったら
	if (phaseChangeFlag == true)
	{
		//タイマーリセット
		phaseTimer = 0;
		//敵リセット
		enemy->Reset();

		//次のフェーズへ
		gameScene->ChangePhase(new Phase2());
	}
}

void MovePhase::UpdateObject()
{
	//カメラ更新
	camera->UpdateMovePhase();
	camera->Update();

	//ライト更新
	light->SetEye(XMFLOAT3(lightPos) + player->GetPosition());
	light->SetTarget(XMFLOAT3(lightTarget) + player->GetPosition());
	light->SetDir(XMFLOAT3(lightDir));
	light->Update();

	//敵
	enemy->SetPlayerPos(player->GetPosition());
	enemy->SetPhaseTimer(phaseTimer);
	enemy->UpdateMovePhase();

	////小さい敵
	//if (enemy->GetCallEnemyFlag())
	//{
	//	miniEnemy->AddEnemy(enemy->GetCallEnemyPos());
	//}
	//miniEnemy->SetPlayerPos(player->GetPosition());
	//miniEnemy->Update();

	//UI
	ui->SetPlayerForm(player->GetPlayerForm(), player->GetFormChangeFlag());
	ui->SetPhaseTimer(phaseTimer);
	ui->UpdateMovePhase();

	//プレイヤー
	player->SetEnemyPos(enemy->GetPosition(), enemy->GetAddPos());
	player->UpdateMovePhase();

	//床
	plane->Update();

	//地形
	terrain->Update();

	if (phaseTimer > movePhaseTime)
	{
		phaseChangeFlag = true;
	}
}

void MovePhase::UpdateCollider()
{
}

void MovePhase::DrawFBX()
{
	//FBX描画
	/*miniEnemy->Draw(dxCommon->GetCommandList());*/
	player->Draw(dxCommon->GetCommandList());
	enemy->Draw(dxCommon->GetCommandList());
	plane->Draw(dxCommon->GetCommandList());
	terrain->Draw(dxCommon->GetCommandList());

	//ステート更新
	enemy->UpdateStateMovePhase();
}

void MovePhase::DrawSprite()
{
	//UI描画
	ui->DrawMovePhase(dxCommon->GetCommandList());
}

void MovePhase::DrawParticle()
{
	//敵のパーティクル描画
	enemy->DrawParticle(dxCommon->GetCommandList());
}

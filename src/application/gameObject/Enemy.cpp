/**
 * @file Enemy.cpp
 * @brief ゲームオブジェクト 敵
 * @author Asuma Syota
 * @date 2023/4
 */

#include "Enemy.h"
#include "mathOriginal.h"
#include "FbxLoader.h"
#include "imgui.h"
#include "ColliderManager.h"
#include "EnemyStateManager.h"
#define G 6.674	//万有引力定数
#define GAcceleration 9.80665 * 1/10	//重力加速度

Camera* Enemy::camera = nullptr;
Input* Enemy::input = nullptr;
DXInput* Enemy::dxInput = nullptr;
//立っている状態のオブジェクト
FbxObject3D* EnemyState::objectStand = nullptr;
//立っている状態のモデル
FbxModel* EnemyState::modelStand = nullptr;
//歩いている状態のオブジェクト
FbxObject3D* EnemyState::objectWalk = nullptr;
//歩いている状態のモデル
FbxModel* EnemyState::modelWalk = nullptr;
//攻撃1状態のオブジェクト
FbxObject3D* EnemyState::objectAttack1 = nullptr;
//攻撃1状態のモデル
FbxModel* EnemyState::modelAttack1 = nullptr;
//攻撃1前兆のオブジェクト
FbxObject3D* EnemyState::objectAttackOmen1 = nullptr;
//攻撃1前兆のモデル
FbxModel* EnemyState::modelAttackOmen1 = nullptr;
//ダッシュのオブジェクト
FbxObject3D* EnemyState::objectDash = nullptr;
//ダッシュのモデル
FbxModel* EnemyState::modelDash = nullptr;
//敵呼び出しのオブジェクト
FbxObject3D* EnemyState::objectCallMiniEnemy = nullptr;
//平行移動
XMFLOAT3 EnemyState::position = { 0.0f,0.0f,30.0f };
//回転
XMFLOAT3 EnemyState::rotation;
//サイズ
XMFLOAT3 EnemyState::scale = { 5.0f,5.0f,5.0f };
//雷パーティクル 敵呼び出しで描画
ElecParticle* EnemyState::elecParticle = nullptr;
//爆発パーティクル 敵呼び出しで描画
ExplosionParticle1* EnemyState::explosionParticle1 = nullptr;
ExplosionParticle2* EnemyState::explosionParticle2 = nullptr;
//弾
EnemyBullet* EnemyState::bullet = nullptr;
//コライダーデータ
JSONLoader::ColliderData EnemyState::colliderData;

Enemy::Enemy()
{
	enemyState = new Dash();
}

Enemy::~Enemy()
{
	delete enemyState;
}

void Enemy::Initialize()
{
	//ステートの初期化
	enemyState->Initialize();

	//HPバーのスプライト
	hpBar1 = new Sprite();
	hpBar1->Initialize();
	hpBar1->SetTextureNum(23);
	hpBar2 = new Sprite();
	hpBar2->Initialize();
	hpBar2->SetTextureNum(24);
	hpBar3 = new Sprite();
	hpBar3->Initialize();
	hpBar3->SetTextureNum(25);
	hpBar4 = new Sprite();
	hpBar4->Initialize();
	hpBar4->SetTextureNum(26);
	hpBar5 = new Sprite();
	hpBar5->Initialize();
	hpBar5->SetTextureNum(58);
}

void Enemy::UpdateGame1()
{
	//ステート更新
	enemyState->Update();

	//ステータスマネージャー
	StatusManagerGame1();

	//スプライト更新
	UpdateSpriteGame1();

	//ダメージ更新
	UpdateDamage();
}

void Enemy::UpdateGame2()
{
	////動く
	//Move();

	////ステータスマネージャー
	//StatusManagerGame2();

	////オブジェクト更新
	//UpdateObject();

	////スプライト更新
	//UpdateSpriteGame2();

	////ダメージ更新
	//UpdateDamage();

	////パーティクル更新
	//UpdateParticle();

	////コライダー更新
	//UpdateCollider();
}

void Enemy::UpdateTutorial(int tutorialTimer)
{
	//position.y = 1000.0f;
	//if (tutorialTimer == 0)return;

	//position = XMFLOAT3(0.0f, 0.0f, 0.0f);

	////ステータスマネージャー
	//StatusManagerTutorial(tutorialTimer);

	////オブジェクト更新
	//UpdateObject();

	////スプライト更新
	//UpdateSpriteGame1();

	////1フレーム前の状態を代入
	//preStatus = status;
}

void Enemy::UpdateSpriteGame1()
{
	//HPバーを現在のHPに
	hpBar2Scale.x = hpBar2OriginalScale.x * (HP / maxHP);
	hpBar3Pos.x = hpBar3OriginalPos.x - (hpBar2OriginalScale.x * ((maxHP - HP) / maxHP));

	//更新
	hpBar1->Update(hpBar1Pos, hpBar1Scale);
	hpBar2->Update(hpBar2Pos, hpBar2Scale);
	hpBar3->Update(hpBar3Pos, hpBar3Scale);
	hpBar4->Update(hpBar4Pos, hpBar4Scale);
	hpBar5->Update(hpBar5Pos, hpBar5Scale);
}

void Enemy::UpdateSpriteGame2()
{
	//HPバーを現在のHPに
	hpBar5Scale.x = hpBar2OriginalScale.x * (HP / maxHP);
	hpBar3Pos.x = hpBar3OriginalPos.x - (hpBar2OriginalScale.x * ((maxHP - HP) / maxHP));

	//更新
	hpBar1->Update(hpBar1Pos, hpBar1Scale);
	hpBar3->Update(hpBar3Pos, hpBar3Scale);
	hpBar4->Update(hpBar4Pos, hpBar4Scale);
	hpBar5->Update(hpBar5Pos, hpBar5Scale);
}

void Enemy::Draw(ID3D12GraphicsCommandList* cmdList)
{
	//ステート描画
	enemyState->Draw(cmdList);

	//ステート更新
	enemyState->UpdateState(this);

	//ImGui
	/*ImGui::Begin("Enemy");
	ImGui::SetWindowPos(ImVec2(0, 0));
	ImGui::SetWindowSize(ImVec2(500, 150));
	ImGui::InputFloat3("playerPos", bulletPos);
	ImGui::End();*/
}

void Enemy::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	enemyState->DrawLightView(cmdList);
}

void Enemy::DrawSpriteGame1(ID3D12GraphicsCommandList* cmdList)
{
	hpBar5->Draw(cmdList);
	hpBar2->Draw(cmdList);
	hpBar4->Draw(cmdList);
	hpBar1->Draw(cmdList);
	hpBar3->Draw(cmdList);
}

void Enemy::DrawSpriteGame2(ID3D12GraphicsCommandList* cmdList)
{
	hpBar5->Draw(cmdList);
	hpBar1->Draw(cmdList);
	hpBar3->Draw(cmdList);
}

void Enemy::DrawParticle(ID3D12GraphicsCommandList* cmdList)
{
	enemyState->DrawParticle(cmdList);
}

void Enemy::UpdateDamage()
{
	//炎攻撃をくらった際
	if (HitFlag1 == true)
	{
		//HPを減らす
		HP -= 1.0f;
	}

	//雷攻撃をくらった際
	if (hitElec == true)
	{
		//HPを減らす
		HP -= 7.0f;
	}

	//死亡
	if (HP <= 0)
	{
		isDead = true;
	}

	//フラグをもとに戻す
	HitFlag1 = false;
	hitElec = false;
}

void Enemy::UpdateCollider()
{
	enemyState->UpdateCollider();
}

void Enemy::StatusManagerGame1()
{
//	//攻撃前兆の場合
//	if (status == AttackOmen1)
//	{
//		//次の攻撃がダッシュの時
//		if (dashFlag == true)
//		{
//			if (statusTimer >= frameAttackOmen1)
//			{
//				//敵→プレイヤーのベクトル取得
//				dashVector = XMFLOAT3(playerPos.x - position.x,0.0f, playerPos.z - position.z);
//				dashVector = normalize(dashVector);
//				dashVector = dashVector * dashSpeed;
//				statusTimer = 0.0f;
//				status = Dash;
//				return;
//			}
//		}
//		//次の攻撃が攻撃1の時
//		if (attack1Flag == true)
//		{
//			//弾をセット
//			if (statusTimer == 0.0f)
//			{
//				XMFLOAT3 addPos(-20, 40, 50);
//				addPos = position + rollRotation(addPos, rotation);
//				for (int i = 0; i < bulletVol; i++)
//				{
//					bullet->SetBullet(addPos, bulletScale, bulletLastScale, 0.0f,
//						frameAttackOmen1 + bulletTimeLag * i, frameAttack1);
//				}
//			}
//			if (statusTimer >= frameAttackOmen1)
//			{
//				statusTimer = 0.0f;
//				status = Attack1;
//				return;
//			}
//		}
//		//タイマー更新
//		statusTimer += 1.0f;
//	}
//	//攻撃1の場合
//	if (status == Attack1)
//	{
//		//タイマー更新
//		statusTimer += 1.0f;
//		if (statusTimer >= frameAttack1)
//		{
//			statusTimer = 0.0f;
//			status = AttackOmen1;
//			//ダッシュのフラグを立てる
//			dashFlag = true;
//			attack1Flag = false;
//			return;
//		}
//	}
//	//立っているの場合
//	if (status == Stand)
//	{
//		//タイマー更新
//		statusTimer += 1.0f;
//		if (statusTimer >= frameStand)
//		{
//			statusTimer = 0.0f;
//			status = AttackOmen1;
//			return;
//		}
//	}
//	//歩きの場合
//	if (status == Walk)
//	{
//		//タイマー更新
//		statusTimer += 1.0f;
//		//プレイヤーとの距離が近い場合も終了
//		if (statusTimer >= frameWalk || length(position - playerPos) <= 10.0f)
//		{
//			statusTimer = 0.0f;
//			status = AttackOmen1;
//			return;
//		}
//	}
//	//ダッシュの場合
//	if (status == Dash)
//	{
//		//タイマー更新
//		statusTimer += 1.0f;
//		//プレイヤーとの距離が近い場合も終了
//		if (statusTimer >= frameDash || length(position - playerPos) <= 10.0f)
//		{
//			statusTimer = 0.0f;
//			status = AttackOmen1;
//			//攻撃1のフラグを立てる
//			dashFlag = false;
//			attack1Flag = true;
//			return;
//		}
//	}
//}
//
//void Enemy::StatusManagerGame2()
//{
//	//デバッグ用
//	//if (status == AttackOmen1)//タイマー更新
//	//{
//	//	statusTimer += 1.0f;
//	//	if (statusTimer >= frameAttackOmen1)
//	//	{
//	//		statusTimer = 0.0f;
//	//		status = AttackOmen1;
//	//		return;
//	//	}
//	//	return;
//	//}
//	
//
//
//	//攻撃前兆の場合
//	if (status == AttackOmen1)
//	{
//		//タイマー更新
//		statusTimer += 1.0f;
//		//次の行動が敵呼び出しの時
//		if (phase2CallEnemyFlag == true)
//		{
//			if (statusTimer >= frameAttackOmen1)
//			{
//				statusTimer = 0.0f;
//				status = CallMiniEnemy;
//				phase2CallEnemyFlag = false;
//				phase2Attack1Flag = true;
//				return;
//			}
//		}
//		//次の行動が攻撃1の時
//		if (phase2Attack1Flag == true)
//		{
//			if (statusTimer >= frameAttackOmen1)
//			{
//				statusTimer = 0.0f;
//				status = Attack1;
//				phase2CallEnemyFlag = true;
//				phase2Attack1Flag = false;
//				return;
//			}
//		}
//	}
//
//	//敵呼び出しの場合
//	if (status == CallMiniEnemy)
//	{
//		//タイマー更新
//		statusTimer += 1.0f;
//		callEnemyFlag = false;
//		//敵呼び出し
//		if (statusTimer == frameCallMiniEnemy2)
//		{
//			//フラグを立てる
//			callEnemyFlag = true;
//			//ベクトル取得
//			XMFLOAT3 velo = playerPos - position;
//			callEnemyPos = velo / 2;
//		}
//		//ダッシュへ移動
//		if (statusTimer >= frameCallMiniEnemy)
//		{
//			//敵→プレイヤーのベクトル取得
//			dashVector = XMFLOAT3(playerPos.x - position.x, 0.0f, playerPos.z - position.z);
//			dashVector = normalize(dashVector);
//			dashVector = dashVector * dashSpeed;
//			statusTimer = 0.0f;
//			status = Dash;
//			return;
//		}
//	}
//
//	//ダッシュ呼び出しの場合
//	if (status == Dash)
//	{
//		//タイマー更新
//		statusTimer += 1.0f;
//		//攻撃前兆へ移動
//		if (statusTimer >= frameDash)
//		{
//			statusTimer = 0.0f;
//			status = AttackOmen1;
//			return;
//		}
//	}
//
//	//攻撃1の場合
//	if (status == Attack1)
//	{
//		//弾をセット
//		if (statusTimer == 0.0f)
//		{
//			XMFLOAT3 addPos(-20, 40, 50);
//			addPos = position + rollRotation(addPos, rotation);
//			for (int i = 0; i < bulletVol; i++)
//			{
//				bullet->SetBullet(addPos, bulletScale, bulletLastScale, 0.0f,
//					frameAttackOmen1 + bulletTimeLag * i, frameAttack1);
//			}
//		}
//		//タイマー更新
//		statusTimer += 1.0f;
//		//攻撃前兆へ移動
//		if (statusTimer >= frameAttack1)
//		{
//			statusTimer = 0.0f;
//			status = AttackOmen1;
//			return;
//		}
//	}
}

void Enemy::StatusManagerTutorial(int tutorialTimer)
{
	////しばらく立ってる
	//if (tutorialTimer < 180)
	//{
	//	status = Stand;
	//	return;
	//}
	////攻撃前兆モーション
	//if (tutorialTimer < 180 + frameAttackOmen1)
	//{
	//	status = AttackOmen1;
	//	return;
	//}
	////しばらく立ってる
	//else
	//{
	//	status = Stand;
	//	return;
	//}
}

void Enemy::SetSRV(ID3D12DescriptorHeap* SRV)
{
	enemyState->SetSRV(SRV);
}

void Enemy::SetPlayerPos(XMFLOAT3 playerPos)
{
	enemyState->SetPlayerPos(playerPos);
}

void Enemy::SetObjectCollider(std::vector<JSONLoader::ColliderData> colliderData)
{
	enemyState->SetObjectCollider(colliderData);
}

void Enemy::HitBullet1()
{
	//被弾フラグを立てる
	HitFlag1 = true;
}

void Enemy::Reset()
{
	HP = maxHP;
	isDead = false;
	enemyState->Reset();
}

void Enemy::SetGameScene()
{
	HP = maxHP;
	isDead = false;
	statusTimer = 0;
	enemyState->SetGameScene();
}

XMFLOAT3 Enemy::GetPosition()
{
	return enemyState->GetPosition();
}

XMFLOAT3 Enemy::GetRotation()
{
	return enemyState->GetRotation();
}

XMFLOAT3 Enemy::GetScale()
{
	return enemyState->GetScale();
}

JSONLoader::ColliderData Enemy::GetColliderData()
{
	return enemyState->GetColliderData();
}

void Enemy::ChangeState(EnemyState* newState)
{
	delete enemyState;
	enemyState = newState;

	//初期化
	enemyState->Initialize();
}

void EnemyState::StaticInitialize()
{
	//立っているモデル
	modelStand = FbxLoader::GetInstance()->LoadModelFromFile("enemyStand");
	//立っているオブジェクト
	objectStand = new FbxObject3D;
	objectStand->Initialize();
	objectStand->SetModel(modelStand);
	objectStand->SetTextureNum(0);
	objectStand->PlayAnimation();

	//歩いているモデル
	modelWalk = FbxLoader::GetInstance()->LoadModelFromFile("enemyWalk");
	//歩いているオブジェクト
	objectWalk = new FbxObject3D;
	objectWalk->Initialize();
	objectWalk->SetModel(modelWalk);
	objectWalk->SetTextureNum(0);
	objectWalk->StopAnimation();

	//攻撃1のモデル
	modelAttack1 = FbxLoader::GetInstance()->LoadModelFromFile("enemyAttack1");
	//攻撃1のオブジェクト
	objectAttack1 = new FbxObject3D;
	objectAttack1->Initialize();
	objectAttack1->SetModel(modelAttack1);
	objectAttack1->SetTextureNum(0);
	objectAttack1->StopAnimation();

	//攻撃前兆のモデル
	modelAttackOmen1 = FbxLoader::GetInstance()->LoadModelFromFile("enemyAttack1Omen");
	//攻撃前兆のオブジェクト
	objectAttackOmen1 = new FbxObject3D;
	objectAttackOmen1->Initialize();
	objectAttackOmen1->SetModel(modelAttackOmen1);
	objectAttackOmen1->SetTextureNum(0);
	objectAttackOmen1->StopAnimation();

	//ダッシュのモデル
	modelDash = FbxLoader::GetInstance()->LoadModelFromFile("enemyDash");
	//ダッシュのオブジェクト
	objectDash = new FbxObject3D;
	objectDash->Initialize();
	objectDash->SetModel(modelDash);
	objectDash->SetTextureNum(0);
	objectDash->StopAnimation();

	//敵呼び出しのオブジェクト
	objectCallMiniEnemy = new FbxObject3D;
	objectCallMiniEnemy->Initialize();
	objectCallMiniEnemy->SetModel(modelAttack1);
	objectCallMiniEnemy->SetTextureNum(0);
	objectCallMiniEnemy->StopAnimation();

	//コライダーの設定
	colliderData.type = "Sphere";	//判定を球体で取るため
	colliderData.objectName = "enemy";
	colliderData.scale = scale;
	colliderData.rotation = rotation;
	colliderData.center = position;
	//コライダーマネージャーにセット
	ColliderManager::SetCollider(colliderData);

	//雷パーティクル
	elecParticle = new ElecParticle();
	elecParticle->CreateBuffers();
	elecParticle->SetTextureNum(0);

	//爆発パーティクル
	explosionParticle1 = new ExplosionParticle1();
	explosionParticle1->CreateBuffers();
	explosionParticle1->SetTextureNum(16);

	//爆発パーティクル
	explosionParticle2 = new ExplosionParticle2();
	explosionParticle2->CreateBuffers();
	explosionParticle2->SetTextureNum(16);

	//敵の弾
	bullet = new EnemyBullet;
	bullet->Initialize();
}

void EnemyState::DrawParticle(ID3D12GraphicsCommandList* cmdList)
{
	//弾のパーティクル描画
	bullet->DrawParticle(cmdList);

	//雷描画
	elecParticle->Draw(cmdList);

	//爆発描画
	explosionParticle1->Draw(cmdList);
	explosionParticle2->Draw(cmdList);
}

void EnemyState::Update()
{
	//タイマー更新
	objectTimer++;

	//オブジェクト更新
	UpdateObject();

	////ダウン状態更新
	//UpdateDown();

	//コライダーデータ更新
	colliderData.scale = colliderScale;
	colliderData.rotation = rotation;
	colliderData.center = position;

	//攻撃更新
	UpdateAttack();

	//弾更新
	bullet->Update();

	//パーティクル更新
	explosionParticle1->Update();
	explosionParticle2->Update();
	elecParticle->Update();

	//動き
	Move();

	//当たりフラグを元に戻す
	/*hitFlag = false;*/
}

void EnemyState::UpdateCollider()
{
	for (int i = 0; i < objectColliderData.size(); i++)
	{
		//壁との当たり判定処理
		if (objectColliderData[i].objectName.substr(0, 4) == "wall")
		{
			UpdateHitWall(objectColliderData[i]);
		}
		//壁との当たり判定処理
		if (objectColliderData[i].objectName.substr(0, 6) == "piller")
		{
			UpdateHitPiller(objectColliderData[i]);
		}
	}
}

void EnemyState::Reset()
{
	position = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

void EnemyState::SetTutorial()
{
	position = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

void EnemyState::SetGameScene()
{
	position = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

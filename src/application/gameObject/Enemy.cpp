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
#define G 6.674	//万有引力定数
#define GAcceleration 9.80665 * 1/10	//重力加速度

Camera* Enemy::camera = nullptr;
Input* Enemy::input = nullptr;
DXInput* Enemy::dxInput = nullptr;

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
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

	//敵の弾
	bullet = new EnemyBullet;
	bullet->Initialize();

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
}

void Enemy::UpdateGame1()
{
	//動く
	Move();

	//ステータスマネージャー
	StatusManagerGame1();

	//オブジェクト更新
	UpdateObject();

	//スプライト更新
	UpdateSpriteGame1();

	//ダメージ更新
	UpdateDamage();

	//コライダー更新
	UpdateCollider();

	//1フレーム前の状態を代入
	preStatus = status;
}

void Enemy::UpdateGame2()
{
	//動く
	Move();

	//ステータスマネージャー
	StatusManagerGame2();

	//オブジェクト更新
	UpdateObject();

	//スプライト更新
	UpdateSpriteGame2();

	//ダメージ更新
	UpdateDamage();

	//パーティクル更新
	UpdateParticle();

	//コライダー更新
	UpdateCollider();

	//1フレーム前の状態を代入
	preStatus = status;
}

void Enemy::UpdateTutorial(int tutorialTimer)
{
	position.y = 1000.0f;
	if (tutorialTimer == 0)return;

	position = XMFLOAT3(0.0f, 0.0f, 0.0f);

	//ステータスマネージャー
	StatusManagerTutorial(tutorialTimer);

	//オブジェクト更新
	UpdateObject();

	//スプライト更新
	UpdateSpriteGame1();

	//1フレーム前の状態を代入
	preStatus = status;
}

void Enemy::UpdateObject()
{
	//オブジェクト更新
	UpdateObject(Stand, objectStand);
	UpdateObject(Walk, objectWalk);
	UpdateObject(Attack1, objectAttack1);
	UpdateObject(AttackOmen1, objectAttackOmen1);
	UpdateObject(Dash, objectDash);
	UpdateObject(CallMiniEnemy, objectCallMiniEnemy);

	//弾更新
	bullet->SetPlayerPos(playerPos);
	bullet->Update();
}

void Enemy::UpdateObject(const Status& status, FbxObject3D* object)
{
	//引数のステータスと違う場合早期リターン
	if (this->status != status)
	{
		object->StopAnimation();
		return;
	}

	//引数のステータスと同じ場合のみ更新
	object->SetPosition(position);
	object->SetRotation(rotation);
	object->SetScale(scale);
	if (this->status != preStatus)
	{
			object->PlayAnimation();
	}

	object->Update();
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
	//ImGui
	ImGui::Begin("Enemy");
	ImGui::SetWindowPos(ImVec2(0, 150));
	ImGui::SetWindowSize(ImVec2(500, 150));
	ImGui::InputInt("debugNum", debugNum);
	ImGui::End();

	if (status == Stand)
	{
		objectStand->Draw(cmdList);
	}
	if (status == Walk)
	{
		objectWalk->Draw(cmdList);
	}
	if (status == Attack1)
	{
		objectAttack1->Draw(cmdList);
	}
	if (status == AttackOmen1)
	{
		objectAttackOmen1->Draw(cmdList);
	}
	if (status == Dash)
	{
		objectDash->Draw(cmdList);
	}
	if (status == CallMiniEnemy)
	{
		objectCallMiniEnemy->Draw(cmdList);
	}

	//弾
	bullet->Draw();

	//ImGui
	/*ImGui::Begin("Enemy");
	ImGui::SetWindowPos(ImVec2(0, 0));
	ImGui::SetWindowSize(ImVec2(500, 150));
	ImGui::InputFloat3("playerPos", bulletPos);
	ImGui::End();*/
}

void Enemy::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	if (status == Stand)
	{
		objectStand->DrawLightView(cmdList);
	}
	if (status == Walk)
	{
		objectWalk->DrawLightView(cmdList);
	}
	if (status == Attack1)
	{
		objectAttack1->DrawLightView(cmdList);
	}
	if (status == AttackOmen1)
	{
		objectAttackOmen1->DrawLightView(cmdList);
	}
	if (status == Dash)
	{
		objectDash->DrawLightView(cmdList);
	}
	if (status == CallMiniEnemy)
	{
		objectCallMiniEnemy->DrawLightView(cmdList);
	}
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
	//弾のパーティクル描画
	bullet->DrawParticle(cmdList);

	//雷描画
	elecParticle->Draw(cmdList);

	//爆発描画
	explosionParticle1->Draw(cmdList);
	explosionParticle2->Draw(cmdList);
}

void Enemy::Move()
{
	//歩きモーション時の動き
	if (status == Walk)
	{
		MoveWalk();
	}
	//ダッシュモーション時の動き
	if (status == Dash)
	{
		MoveDash();
	}
}

void Enemy::MoveWalk()
{
	//プレイヤーと敵のベクトル取得
	XMFLOAT3 velo = playerPos - position;
	//敵がプレイヤーの向きを向くようにする
	rotation.y = getVectorRotation(velo).y;

	//プレイヤーに近づく
	position = position + normalize(velo) * walkSpeed;
}

void Enemy::MoveDash()
{
	//敵がプレイヤーの向きを向くようにする
	rotation.y = getVectorRotation(dashVector).y;

	//プレイヤーに近づく
	position = position + dashVector;
}

void Enemy::UpdateGravity()
{
	//接地していたらタイマーとベクトルリセット
	if (groundFlag == true)
	{
		fallTimer = 0.0f;
		fallVelocity = XMFLOAT3(0.0f, 0.0f, 0.0f);
	}

	//接地していなければ
	if (groundFlag == false)
	{
		//落下タイマーが最大値より小さければ
		if (fallTimer < fallTime)
		{
			fallTimer += fallFrame;
		}
	}

	//落下ベクトル計算
	fallVelocity.y = -(GAcceleration * fallTimer);

	//座標に落下ベクトルを加算
	position.x += fallVelocity.x;
	position.y += fallVelocity.y;
	position.z += fallVelocity.z;
}

void Enemy::UpdateJump()
{
	//接地していたら
	if (groundFlag == true)
	{
		//スペースキーでジャンプ
		if (input->TriggerKey(DIK_SPACE))
		{
			groundFlag = false;
			fallTimer = -jumpHeight;
			fallVelocity = XMFLOAT3(0.0f, 0.0f, 0.0f);
		}
	}
}

void Enemy::UpdateAttack()
{
	
}

void Enemy::UpdateAttack1()
{
}

void Enemy::UpdateAttackOmen()
{
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
	colliderData.scale = XMFLOAT3(20.0f,10.0f,10.0f);
	colliderData.rotation = rotation;
	colliderData.center = position + XMFLOAT3(0.0f,5.0f,0.0f);
}

void Enemy::UpdateParticle()
{
	//敵呼び出しの場合
	if (status == CallMiniEnemy)
	{
		//敵呼び出し
		if (statusTimer == frameCallMiniEnemy2)
		{
			elecParticle->AddParticle(elecFrame, callEnemyPos + XMFLOAT3(150.0f,500.0f, 150.0f),
				callEnemyPos, elecStartSlace1, elecEndSlace1, 60.0f, elecStrength);
			explosionParticle1->Add(callEnemyPos);
			explosionParticle2->Add(callEnemyPos);
		}
		//敵呼び出し
		if (statusTimer <= frameCallMiniEnemy2)
		{
			if ((int)statusTimer % elecInterval == 0)
			{
				for (int i = 0; i < elecVol; i++)
				{
					elecParticle->AddParticle(3.0f, callEnemyPos + XMFLOAT3(40.0f, 500.0f, 40.0f),
						callEnemyPos, elecStartSlace2, elecEndSlace2, 15.0f, elecStrength);
				}
			}
		}
	}
	explosionParticle1->Update();
	explosionParticle2->Update();
	elecParticle->Update();
}

void Enemy::StatusManagerGame1()
{
	//攻撃前兆の場合
	if (status == AttackOmen1)
	{
		//次の攻撃がダッシュの時
		if (dashFlag == true)
		{
			if (statusTimer >= frameAttackOmen1)
			{
				//敵→プレイヤーのベクトル取得
				dashVector = XMFLOAT3(playerPos.x - position.x,0.0f, playerPos.z - position.z);
				dashVector = normalize(dashVector);
				dashVector = dashVector * dashSpeed;
				statusTimer = 0.0f;
				status = Dash;
				return;
			}
		}
		//次の攻撃が攻撃1の時
		if (attack1Flag == true)
		{
			//弾をセット
			if (statusTimer == 0.0f)
			{
				XMFLOAT3 addPos(-20, 40, 50);
				addPos = position + rollRotation(addPos, rotation);
				for (int i = 0; i < bulletVol; i++)
				{
					bullet->SetBullet(addPos, bulletScale, bulletLastScale, 0.0f,
						frameAttackOmen1 + bulletTimeLag * i, frameAttack1);
				}
			}
			if (statusTimer >= frameAttackOmen1)
			{
				statusTimer = 0.0f;
				status = Attack1;
				return;
			}
		}
		//タイマー更新
		statusTimer += 1.0f;
	}
	//攻撃1の場合
	if (status == Attack1)
	{
		//タイマー更新
		statusTimer += 1.0f;
		if (statusTimer >= frameAttack1)
		{
			statusTimer = 0.0f;
			status = AttackOmen1;
			//ダッシュのフラグを立てる
			dashFlag = true;
			attack1Flag = false;
			return;
		}
	}
	//立っているの場合
	if (status == Stand)
	{
		//タイマー更新
		statusTimer += 1.0f;
		if (statusTimer >= frameStand)
		{
			statusTimer = 0.0f;
			status = Stand;
			return;
		}
	}
	//歩きの場合
	if (status == Walk)
	{
		//タイマー更新
		statusTimer += 1.0f;
		//プレイヤーとの距離が近い場合も終了
		if (statusTimer >= frameWalk || length(position - playerPos) <= 10.0f)
		{
			statusTimer = 0.0f;
			status = AttackOmen1;
			return;
		}
	}
	//ダッシュの場合
	if (status == Dash)
	{
		//タイマー更新
		statusTimer += 1.0f;
		//プレイヤーとの距離が近い場合も終了
		if (statusTimer >= frameDash || length(position - playerPos) <= 10.0f)
		{
			statusTimer = 0.0f;
			status = AttackOmen1;
			//攻撃1のフラグを立てる
			dashFlag = false;
			attack1Flag = true;
			return;
		}
	}
}

void Enemy::StatusManagerGame2()
{
	//デバッグ用
	//if (status == AttackOmen1)//タイマー更新
	//{
	//	statusTimer += 1.0f;
	//	if (statusTimer >= frameAttackOmen1)
	//	{
	//		statusTimer = 0.0f;
	//		status = AttackOmen1;
	//		return;
	//	}
	//	return;
	//}
	


	//攻撃前兆の場合
	if (status == AttackOmen1)
	{
		//タイマー更新
		statusTimer += 1.0f;
		//次の行動が敵呼び出しの時
		if (phase2CallEnemyFlag == true)
		{
			if (statusTimer >= frameAttackOmen1)
			{
				statusTimer = 0.0f;
				status = CallMiniEnemy;
				phase2CallEnemyFlag = false;
				phase2Attack1Flag = true;
				return;
			}
		}
		//次の行動が攻撃1の時
		if (phase2Attack1Flag == true)
		{
			if (statusTimer >= frameAttackOmen1)
			{
				statusTimer = 0.0f;
				status = Attack1;
				phase2CallEnemyFlag = true;
				phase2Attack1Flag = false;
				return;
			}
		}
	}

	//敵呼び出しの場合
	if (status == CallMiniEnemy)
	{
		//タイマー更新
		statusTimer += 1.0f;
		callEnemyFlag = false;
		//敵呼び出し
		if (statusTimer == frameCallMiniEnemy2)
		{
			//フラグを立てる
			callEnemyFlag = true;
			//ベクトル取得
			XMFLOAT3 velo = playerPos - position;
			callEnemyPos = velo / 2;
		}
		//ダッシュへ移動
		if (statusTimer >= frameCallMiniEnemy)
		{
			//敵→プレイヤーのベクトル取得
			dashVector = XMFLOAT3(playerPos.x - position.x, 0.0f, playerPos.z - position.z);
			dashVector = normalize(dashVector);
			dashVector = dashVector * dashSpeed;
			statusTimer = 0.0f;
			status = Dash;
			return;
		}
	}

	//ダッシュ呼び出しの場合
	if (status == Dash)
	{
		//タイマー更新
		statusTimer += 1.0f;
		//攻撃前兆へ移動
		if (statusTimer >= frameDash)
		{
			statusTimer = 0.0f;
			status = AttackOmen1;
			return;
		}
	}

	//攻撃1の場合
	if (status == Attack1)
	{
		//弾をセット
		if (statusTimer == 0.0f)
		{
			XMFLOAT3 addPos(-20, 40, 50);
			addPos = position + rollRotation(addPos, rotation);
			for (int i = 0; i < bulletVol; i++)
			{
				bullet->SetBullet(addPos, bulletScale, bulletLastScale, 0.0f,
					frameAttackOmen1 + bulletTimeLag * i, frameAttack1);
			}
		}
		//タイマー更新
		statusTimer += 1.0f;
		//攻撃前兆へ移動
		if (statusTimer >= frameAttack1)
		{
			statusTimer = 0.0f;
			status = AttackOmen1;
			return;
		}
	}
}

void Enemy::StatusManagerTutorial(int tutorialTimer)
{
	//しばらく立ってる
	if (tutorialTimer < 180)
	{
		status = Stand;
		return;
	}
	//攻撃前兆モーション
	if (tutorialTimer < 180 + frameAttackOmen1)
	{
		status = AttackOmen1;
		return;
	}
	//しばらく立ってる
	else
	{
		status = Stand;
		return;
	}
}

void Enemy::SetSRV(ID3D12DescriptorHeap* SRV)
{
	if (status == Stand)
	{
		objectStand->SetSRV(SRV);
	}
	if (status == Walk)
	{
		objectWalk->SetSRV(SRV);
	}
	if (status == Attack1)
	{
		objectAttack1->SetSRV(SRV);
	}
	if (status == AttackOmen1)
	{
		objectAttackOmen1->SetSRV(SRV);
	}
	if (status == Dash)
	{
		objectDash->SetSRV(SRV);
	}
	if (status == CallMiniEnemy)
	{
		objectCallMiniEnemy->SetSRV(SRV);
	}
}

void Enemy::HitPlane()
{
	//接地フラグを立てる
	groundFlag = true;

	//めり込まなくなるまで加算
	position.y += 0.1f;

	//オブジェクト更新
	UpdateObject();
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
	position = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

void Enemy::SetGameScene()
{
	HP = maxHP;
	isDead = false;
	status = AttackOmen1;
	statusTimer = 0;
	position = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

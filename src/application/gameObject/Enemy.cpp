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
//転ぶオブジェクト
FbxObject3D* EnemyState::objectFallDown = nullptr;
//転ぶモデル
FbxModel* EnemyState::modelFallDown = nullptr;
//立ち上がるオブジェクト
FbxObject3D* EnemyState::objectGetUp = nullptr;
//立ち上がるモデル
FbxModel* EnemyState::modelGetUp = nullptr;
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
//次の行動を決めるフラグ
bool EnemyState::nextCallMiniEnemy;
bool EnemyState::nextDash;
bool EnemyState::nextAttack01;

Enemy::Enemy()
{
	enemyState = new AttackOmen1();
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
	enemyState->SetHitPlayer(hitPlayer);
	enemyState->Update();

	//フラグを戻す
	hitPlayer = false;

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
	//ステート更新
	enemyState->SetHitPlayer(hitPlayer);
	enemyState->UpdateTutorial(tutorialTimer);

	//フラグを戻す
	hitPlayer = false;

	//スプライト更新
	UpdateSpriteGame1();

	//ダメージ更新
	UpdateDamage();
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

void Enemy::UpdateStateGame()
{
	//ステート更新
	enemyState->UpdateState(this);
}

void Enemy::UpdateStateTutorial()
{
	//ステート更新
	enemyState->UpdateStateTutorial(this);
}

void Enemy::Draw(ID3D12GraphicsCommandList* cmdList)
{
	//ステート描画
	enemyState->Draw(cmdList);
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
//}

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

void Enemy::SetTutorial()
{
	enemyState->SetTutorial(this);
}

void Enemy::SetGameScene()
{
	HP = maxHP;
	isDead = false;
	statusTimer = 0;
	enemyState->SetGame(this);
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

JSONLoader::ColliderData Enemy::GetBulletColliderData(int num)
{
	return enemyState->GetBullet1ColliderData(num);
}

size_t Enemy::GetBulletNum()
{
	return enemyState->GetBullet1Num();
}

void Enemy::SetHitPlayer()
{
	hitPlayer = true;
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

	//転ぶモデル
	modelFallDown = FbxLoader::GetInstance()->LoadModelFromFile("enemyFallDown");
	//転ぶオブジェクト
	objectFallDown = new FbxObject3D;
	objectFallDown->Initialize();
	objectFallDown->SetModel(modelFallDown);
	objectFallDown->SetTextureNum(0);
	objectFallDown->StopAnimation();

	//立ち上がるモデル
	modelGetUp = FbxLoader::GetInstance()->LoadModelFromFile("enemyGetUp");
	//立ち上がるオブジェクト
	objectGetUp = new FbxObject3D;
	objectGetUp->Initialize();
	objectGetUp->SetModel(modelGetUp);
	objectGetUp->SetTextureNum(0);
	objectGetUp->StopAnimation();

	//コライダーの設定
	colliderData.type = "Sphere";	//判定を球体で取るため
	colliderData.objectName = "enemy";
	colliderData.scale = { 30.0f,30.0f,30.0f };
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

	//行動を決めるフラグ
	nextCallMiniEnemy = false;
	nextDash = false;
	nextAttack01 = true;
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

	////ダウン状態更新
	//UpdateDown();

	//コライダーデータ更新
	colliderData.scale = colliderScale;
	colliderData.rotation = rotation;
	colliderData.center = position;

	//攻撃更新
	UpdateAttack();

	//弾更新
	bullet->SetPlayerPos(playerPos);
	bullet->Update();

	//パーティクル更新
	explosionParticle1->Update();
	explosionParticle2->Update();
	elecParticle->Update();

	//動き
	Move();

	//オブジェクト更新
	UpdateObject();
}

void EnemyState::UpdateTutorial(int timer)
{
	//タイマー更新
	objectTimer++;

	//引数からチュートリアルタイマー代入
	tutorialTimer = timer;

	//コライダーデータ更新
	colliderData.scale = colliderScale;
	colliderData.rotation = rotation;
	colliderData.center = position;

	//攻撃更新
	UpdateAttack();

	//弾更新
	bullet->SetPlayerPos(playerPos);
	bullet->Update();

	//パーティクル更新
	explosionParticle1->Update();
	explosionParticle2->Update();
	elecParticle->Update();

	//動き
	MoveTutorail();

	//オブジェクト更新
	UpdateObject();
}

void EnemyState::MoveTutorail()
{
	//敵登場のフェーズになったら
	if (tutorialTimer > 0)
	{
		position = tutorialPos;
	}
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

void EnemyState::SetTutorial(Enemy* enemy)
{
	//立つモデルに変更
	enemy->ChangeState(new Stand());
	//タイマー更新
	tutorialTimer = 0;
	//最後しか描画しないため、それまで画面外
	position = XMFLOAT3(0.0f, 1000.0f, 0.0f);
}

void EnemyState::SetGame(Enemy* enemy)
{
	//攻撃前兆にセット
	enemy->ChangeState(new AttackOmen1());
	position = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

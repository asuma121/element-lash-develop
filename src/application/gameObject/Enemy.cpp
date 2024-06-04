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
//オブジェクト
FbxObject3D* EnemyState::object = nullptr;
//立っている状態のモデル
FbxModel* EnemyState::modelStand = nullptr;
//歩いている状態のモデル
FbxModel* EnemyState::modelWalk = nullptr;
//攻撃1状態のモデル
FbxModel* EnemyState::modelAttack1 = nullptr;
//攻撃1前兆のモデル
FbxModel* EnemyState::modelAttackOmen1 = nullptr;
//ダッシュのモデル
FbxModel* EnemyState::modelDash = nullptr;
//転ぶモデル
FbxModel* EnemyState::modelFallDown = nullptr;
//立ち上がるモデル
FbxModel* EnemyState::modelGetUp = nullptr;
//平行移動
XMFLOAT3 EnemyState::position = { 0.0f,0.0f,30.0f };
//回転
XMFLOAT3 EnemyState::rotation = {0.0f,0.0f,0.0f};
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
	enemyState = new Stand();
}

Enemy::~Enemy()
{
	enemyState->Finalize();
	delete enemyState;
}

void Enemy::Initialize()
{
	//ステートの初期化
	enemyState->Initialize();
	enemyState->InitializeState();
}

void Enemy::UpdateGame1()
{
	//ステート更新
	enemyState->SetHitPlayer(hitPlayer);
	hitBodyFlag = enemyState->GetHitBodyFlag();
	addPos = enemyState->GetAddPos();
	enemyState->Update();

	//フラグを戻す
	hitPlayer = false;

	//ダメージ更新
	UpdateDamage();
}

void Enemy::UpdateGame2()
{
	//ステート更新
	enemyState->SetHitPlayer(hitPlayer);
	hitBodyFlag = enemyState->GetHitBodyFlag();
	addPos = enemyState->GetAddPos();
	enemyState->Update();

	//フラグを戻す
	hitPlayer = false;

	//ダメージ更新
	UpdateDamage();
}

void Enemy::UpdateMovePhase()
{
	//ステート更新
	enemyState->SetHitPlayer(hitPlayer);
	enemyState->UpdateMovePhase();

	//フラグを戻す
	hitPlayer = false;

	//ダメージ更新
	UpdateDamage();
}

void Enemy::UpdateTutorial(int tutorialTimer)
{
	//ステート更新
	enemyState->SetHitPlayer(hitPlayer);
	enemyState->UpdateTutorial(tutorialTimer);

	//フラグを戻す
	hitPlayer = false;

	//ダメージ更新
	UpdateDamage();
}

void Enemy::UpdateClear(int clearTimer)
{
	//ステート更新
	enemyState->SetHitPlayer(hitPlayer);
	enemyState->UpdateClear(clearTimer);

	//フラグを戻す
	hitPlayer = false;

	//ダメージ更新
	UpdateDamage();
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

void Enemy::UpdateStateMovePhase()
{
	//ステート更新
	enemyState->UpdateStateMovePhase(this);
}

void Enemy::UpdateStateClear()
{
	//ステート更新
	enemyState->UpdateStateClear(this);
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
		HP -= fireDamege;
	}

	//雷攻撃をくらった際
	if (hitElec == true)
	{
		//HPを減らす
		HP -= elecDamege;
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

void Enemy::SetSRV(ID3D12DescriptorHeap* SRV)
{
	enemyState->SetSRV(SRV);
}

void Enemy::SetPlayerPos(XMFLOAT3 playerPos)
{
	enemyState->SetPlayerPos(playerPos);
}

void Enemy::SetPhaseTimer(int phaseTimer)
{
	enemyState->SetPhaseTimer(phaseTimer);
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

void Enemy::SetMovePhase()
{
	enemyState->SetMovePhase(this);
}

void Enemy::SetClear()
{
	enemyState->SetClear(this);
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

bool Enemy::GetCallEnemyFlag()
{
	return enemyState->GetCallEnemyFlag();
}

XMFLOAT3 Enemy::GetCallEnemyPos()
{
	return enemyState->GetCallEnemyPos();
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
	enemyState->InitializeState();
}

void Enemy::SetCallMiniEnemy()
{
	enemyState->SetCallMiniEnemy();
}

void EnemyState::Initialize()
{
	//プレイヤーのシェーダを別に設定
	JSONLoader::TextureData textureData;
	textureData.textureVol = 2;
	textureData.shaderVol = 1;
	textureData.textureNum1 = 71;	//白いテクスチャ
	textureData.textureNum2 = 88;	//炎のテクスチャ
	textureData.shaderName = "Enemy";	//シェーダの名前

	//立っているモデル
	modelStand = new FbxModel();
	modelStand = FbxLoader::GetInstance()->LoadModelFromFile("enemyStand");
	//歩いているモデル
	modelWalk = new FbxModel();
	modelWalk = FbxLoader::GetInstance()->LoadModelFromFile("enemyWalk");
	//攻撃1のモデル
	modelAttack1 = new FbxModel();
	modelAttack1 = FbxLoader::GetInstance()->LoadModelFromFile("enemyAttack1");
	//攻撃前兆のモデル
	modelAttackOmen1 = new FbxModel();
	modelAttackOmen1 = FbxLoader::GetInstance()->LoadModelFromFile("enemyAttack1Omen");
	//ダッシュのモデル
	modelDash = new FbxModel();
	modelDash = FbxLoader::GetInstance()->LoadModelFromFile("enemyDash");
	//転ぶモデル
	modelFallDown = new FbxModel();
	modelFallDown = FbxLoader::GetInstance()->LoadModelFromFile("enemyFallDown");
	//立ち上がるモデル
	modelGetUp = new FbxModel();
	modelGetUp = FbxLoader::GetInstance()->LoadModelFromFile("enemyGetUp");

	//オブジェクト
	object = new FbxObject3D;
	object->Initialize(modelStand, textureData);
	object->PlayAnimation();

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
	explosionParticle1->SetTextureNum(79);

	//爆発パーティクル
	explosionParticle2 = new ExplosionParticle2();
	explosionParticle2->CreateBuffers();
	explosionParticle2->SetTextureNum(79);

	//敵の弾
	bullet = new EnemyBullet;
	bullet->Initialize();

	//行動を決めるフラグ
	nextCallMiniEnemy = false;
	nextDash = false;
	nextAttack01 = false;
}

void EnemyState::Finalize()
{
	delete object;
	delete modelStand;
	delete modelWalk;
	delete modelAttack1;
	delete modelAttackOmen1;
	delete modelDash;
	delete modelFallDown;
	delete modelGetUp;
	delete bullet;
	delete elecParticle;
	delete explosionParticle1;
	delete explosionParticle2;
}

void EnemyState::UpdateColliderDate()
{
	colliderData.scale = colliderScale;
	colliderData.rotation = rotation;
	colliderData.center = position;
}

void EnemyState::Draw(ID3D12GraphicsCommandList* cmdList)
{
	object->Draw(cmdList);
}

void EnemyState::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	object->DrawLightView(cmdList);
}

void EnemyState::SetSRV(ID3D12DescriptorHeap* SRV)
{
	object->SetSRV(SRV);
}

void EnemyState::UpdateObject()
{
	object->SetPosition(position);
	object->SetRotation(rotation);
	object->SetScale(scale);
	object->Update();
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

	//コライダーデータ更新
	UpdateColliderDate();

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

void EnemyState::UpdateMovePhase()
{
	//タイマー更新
	objectTimer++;

	//コライダーデータ更新
	UpdateColliderDate();

	//攻撃更新
	UpdateAttackMovePhase();

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
	UpdateColliderDate();

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

void EnemyState::UpdateClear(int timer)
{
	//タイマー更新
	objectTimer++;

	//引数からチュートリアルタイマー代入
	clearTimer = timer;

	//コライダーデータ更新
	colliderData.scale = colliderScale;
	colliderData.rotation = rotation;
	colliderData.center = position;

	//攻撃更新
	UpdateAttack();

	//クリア用パーティクル更新
	UpdateParticleClear();

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
	nextCallMiniEnemy = false;
	nextDash = false;
	nextAttack01 = true;
	enemy->ChangeState(new AttackOmen1());
	position = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

void EnemyState::SetClear(Enemy* enemy)
{
	//攻撃前兆にセット
	enemy->ChangeState(new AttackOmen1());
	position = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

void EnemyState::SetMovePhase(Enemy* enemy)
{
	//転ぶアニメーションにセット
	enemy->ChangeState(new FallDown());
	rotation = XMFLOAT3(0.0f, (float)PI, 0.0f);
	position = XMFLOAT3(0.0f, 0.0f, 100.0f);
}

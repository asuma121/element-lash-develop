/**
 * @file Player.cpp
 * @brief ゲームオブジェクト プレイヤー
 * @author Asuma Syota
 * @date 2023/4
 */

#include "Player.h"
#include "mathOriginal.h"
#include "FbxLoader.h"
#include "ColliderManager.h"
#include "imgui.h"
#include "PlayerStateManager.h"
#define G 6.674	//万有引力定数
#define GAcceleration 9.80665 * 1/10	//重力加速度

Camera* Player::camera = nullptr;
KeyManager* Player::keyManager = nullptr;
LockOn* Player::lockOn = nullptr;
//オブジェクト
FbxObject3D* PlayerState::object = nullptr;
//モデル
FbxModel* PlayerState::modelWait = nullptr;
FbxModel* PlayerState::modelRun = nullptr;
FbxModel* PlayerState::modelAttack1 = nullptr;
FbxModel* PlayerState::modelAttack2 = nullptr;
FbxModel* PlayerState::modelAttack3 = nullptr;
FbxModel* PlayerState::modelDown = nullptr;
FbxModel* PlayerState::modelStandUp = nullptr;
//コライダーデータ
JSONLoader::ColliderData PlayerState::colliderData;
//シェーダのデータ
JSONLoader::TextureData PlayerState::textureData;
//平行移動
XMFLOAT3 PlayerState::position;
//回転
XMFLOAT3 PlayerState::rotation0;
XMFLOAT3 PlayerState::rotation1;
//サイズ
XMFLOAT3 PlayerState::scale;
//弾 炎
PlayerBullet* PlayerState::bullet = nullptr;
//雷パーティクル
ElecParticle* PlayerState::elecParticle1 = nullptr;
//雷パーティクルに使うパーティクル 敵の弾のもので代用
EnemyBulletParticle* PlayerState::elecParticle2 = nullptr;
//被ダメージ時の無敵時間
bool PlayerState::invincibleFlag;
float PlayerState::hitTimer;

Player::Player()
{
	playerState = new Wait();
}

Player::~Player()
{
	playerState->Finalize();
	delete playerState;
}

void Player::Initialize()
{
	//プレイヤーステートの初期化
	playerState->Initialize();
	playerState->InitializeState();

}

void Player::Update()
{
	//フォルム更新
	UpdateForm();

	//ロックオンの更新
	lockOn->SetPlayerRotation(playerState->GetRotation0());
	lockOn->SetPlayerPosition(playerState->GetPosition());
	if (tutorialFlag > 8 && playerState->GetElecAttackFlag() != true)
	{
		for (int i = 0; i < enemyPos.size(); i++)
		{
			lockOn->AddEnemyPos(enemyPos[i], enemyAddPos[i]);
		}
		lockOn->Update();
	}

	//プレイヤーステート更新
	playerState->SetKeyManager(keyManager);
	playerState->SetPlayerForm(form);
	playerState->SetLockOn(lockOn->GetLockOnFlag(), lockOn->GetTarget());
	playerState->SetHP((int)HP);
	playerState->SetMovePhaseFlag(movePhaseFlag);
	playerState->Update();

	//1フレーム前のフォルムを代入
	preForm = form;

	//敵クリア
	enemyPos.clear();
	enemyAddPos.clear();
}

void Player::UpdateCollider()
{
	playerState->UpdateCollider();
}

void Player::Draw(ID3D12GraphicsCommandList* cmdList)
{
	//プレイヤーの描画
	playerState->Draw(cmdList);
}

void Player::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	//プレイヤーの描画
	playerState->DrawLightView(cmdList);
}

void Player::DrawParticle(ID3D12GraphicsCommandList* cmdList)
{
	//パーティクル描画
	playerState->DrawParticle(cmdList);
}

void Player::SetObjectCollider(std::vector<JSONLoader::ColliderData> colliderData)
{
	playerState->SetObjectCollider(colliderData);
}

void Player::DrawSpriteGame(ID3D12GraphicsCommandList* cmdList)
{
	//電気フォームだったら
	if (form == Elec && playerState->GetElecAttackFlag() != true)
	{
		lockOn->Draw(cmdList);
	}
}

void Player::DrawSpriteTutorial(ID3D12GraphicsCommandList* cmdList)
{
	//電気フォームだったら
	if (form == Elec && playerState->GetElecAttackFlag() != true && tutorialFlag < 12)
	{
		lockOn->Draw(cmdList);
	}
}

void Player::UpdateForm()
{
	//Lボタンでフォルムチェンジフラグを立てる
	if (keyManager->TriggerKey(KeyManager::PAD_LEFT_SHOULDER) && formChangeFlag == false)
	{
		if (preForm == Fire && tutorialFlag > 5)form = Elec;	//炎だったら電気に変える
		else if (preForm == Elec && tutorialFlag != 6 && tutorialFlag != 7 && tutorialFlag != 8)form = Fire;	//電気だったら炎に帰る
		formChangeFlag = true;
	}
	//フォルムチェンジフラグがたったら
	if (formChangeFlag == true)
	{
		//タイマー更新
		formTimer++;
		//タイマー最大まで経ったら
		if (formTimer >= formMaxTime)
		{
			formChangeFlag = false;
			formTimer = 0;
		}
	}
}

void Player::UpdateState()
{
	//ステート更新
	playerState->UpdateState(this);
}

void Player::HitBullet1(int num)
{
	this->playerState->HitBullet1(num);
}

void Player::HitEnemy()
{
	//当たりフラグを立てる
	playerState->HitEnemy();

	//HPを減らす
	HP--;

	if (HP <= 0)
	{
		isDead = true;
	}
}

void Player::Reset()
{
	HP = MaxHP;
	playerState->Reset();
}

void Player::SetTitle()
{
	playerState->SetTitle(this);
	movePhaseFlag = true;
}

void Player::SetTutorial()
{
	form = Fire;
	playerState->SetTutorial();
	tutorialFlag = 1;
	movePhaseFlag = false;
}

void Player::SetGameScene()
{
	HP = MaxHP;
	playerState->SetGameScene();
	tutorialFlag = 15;
	movePhaseFlag = false;
}

void Player::SetMovePhase()
{
	playerState->SetMovePhase(this);
	movePhaseFlag = true;
}

void Player::SetClear()
{
	playerState->SetClear(this);
	movePhaseFlag = true;
}

void Player::SetDevelop()
{
	form = Elec;
	playerState->SetDevelop(this);
	movePhaseFlag = true;
}

XMFLOAT3 Player::GetPosition()
{
	return playerState->GetPosition();
}

XMFLOAT3 Player::GetRotation0()
{
	return playerState->GetRotation0();
}

XMFLOAT3 Player::GetRotation1()
{
	return playerState->GetRotation1();
}

XMFLOAT3 Player::GetScale()
{
	return playerState->GetScale();
}

JSONLoader::ColliderData Player::GetColliderData()
{
	return playerState->GetColliderData();
}

JSONLoader::ColliderData Player::GetBullet1ColliderData(int num)
{
	return playerState->GetBullet1ColliderData(num);
}

size_t Player::GetBullet1Num()
{
	return playerState->GetBullet1Num();
}

bool Player::GetInvincibleFlag()
{
	return playerState->GetInvincibleFlag();
}

bool Player::GetHitElec()
{
	return playerState->GetHitElec();
}

void Player::ChangeState(PlayerState* newState)
{
	delete playerState;
	playerState = newState;

	//初期化
	playerState->InitializeState();
}

void PlayerState::DrawParticle(ID3D12GraphicsCommandList* cmdList)
{
	if (movePhaseFlag == false)
	{
		bullet->DrawParticle(cmdList);
		elecParticle1->Draw(cmdList);
		elecParticle2->Draw(cmdList);
	}
}

void PlayerState::Draw(ID3D12GraphicsCommandList* cmdList)
{
	object->Draw(cmdList);

	hitElecFlag = false;
}

void PlayerState::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	object->DrawLightView(cmdList);
}

void PlayerState::UpdateObject()
{
	object->SetPosition(position);
	object->SetRotation(rotation0 + rotation1);
	object->SetScale(scale);
	object->SetDrawShaderNum(form);
	object->UpdateTimer();
	object->Update();
}

void PlayerState::Update()
{
	//タイマー更新
	objectTimer++;

	//オブジェクト更新
	UpdateObject();

	//ダウン状態更新
	UpdateDown();

	//コライダーデータ更新
	colliderData.rotation = rotation0;
	colliderData.center = position;

	//攻撃更新
	UpdateAttack();

	//弾更新
	bullet->Update();

	//パーティクル更新
	elecParticle1->Update();
	elecParticle2->Update();

	//動き
	if(movePhaseFlag == false)Move();

	//当たりフラグを元に戻す
	hitFlag = false;
}

void PlayerState::UpdateCollider()
{
	for (int i = 0; i < objectColliderData.size(); i++)
	{
		//壁との当たり判定処理
		if (objectColliderData[i].objectName.substr(0, 11) == "wall_player")
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

void PlayerState::UpdateDown()
{
	//ヒットフラグがたったら
	if (hitFlag == true)
	{
		invincibleFlag = true;
	}

	//無敵時間が終わったらフラグを元に戻す
	if (hitTimer >= frameDown * 4.0f) 
	{
		invincibleFlag = false;
		hitTimer = 0.0f;
	}

	//無敵時間中
	if (invincibleFlag == true)
	{
		//タイマー更新
		hitTimer++;
	}
}

void PlayerState::UpdateHitWall(JSONLoader::ColliderData objectColliderData)
{
	//プレイヤーから原点のベクトル
	XMFLOAT3 vec = XMFLOAT3(0.0f, 0.0f, 0.0f) - position;
	//プレイヤーから原点のベクトルを正規化
	vec = normalize(vec);
	//壁の外にいる時のみ
	while (ColliderManager::CheckCollider(colliderData, objectColliderData) == false)
	{
		//壁の中に戻るまで加算
		position = position + (vec * knockBackSpeed);
		//コライダーデータの座標更新
		colliderData.center = position;
	}
}

void PlayerState::UpdateHitPiller(JSONLoader::ColliderData objectColliderData)
{
	//柱にめり込んでいる間
	while (ColliderManager::CheckCollider(colliderData, objectColliderData) == true)
	{
		//柱からプレイヤーのベクトル
		XMFLOAT3 vec = objectColliderData.center - colliderData.center;
		//プレイヤーから原点のベクトルを正規化
		vec = normalize(vec);
		//壁の中に戻るまで加算
		position = position - (vec * knockBackSpeed);
		//コライダーデータの座標更新
		colliderData.center = position;
	}
}

void PlayerState::Initialize()
{
	//モデルの読み込み
	modelWait = new FbxModel();
	modelWait = FbxLoader::GetInstance()->LoadModelFromFile("playerWait");
	modelRun = new FbxModel();
	modelRun = FbxLoader::GetInstance()->LoadModelFromFile("playerRun");
	modelAttack1 = new FbxModel();
	modelAttack1 = FbxLoader::GetInstance()->LoadModelFromFile("playerAttack1");
	modelAttack2 = new FbxModel();
	modelAttack2 = FbxLoader::GetInstance()->LoadModelFromFile("playerAttack2");
	modelAttack3 = new FbxModel();
	modelAttack3 = FbxLoader::GetInstance()->LoadModelFromFile("playerAttack3");
	modelDown = new FbxModel();
	modelDown = FbxLoader::GetInstance()->LoadModelFromFile("playerDown");
	modelStandUp = new FbxModel();
	modelStandUp = FbxLoader::GetInstance()->LoadModelFromFile("playerStandUp");

	//コライダーの設定
	colliderData.type = "Sphere";	//判定を球体で取るため
	colliderData.objectName = "player";
	colliderData.scale = { 5.0f,5.0f,5.0f };
	colliderData.rotation = { 0.0f,0.0f,0.0f };
	colliderData.center = { 0.0f,0.0f,0.0f };
	//コライダーマネージャーにセット
	ColliderManager::SetCollider(colliderData);

	//プレイヤーのシェーダを別に設定
	textureData.textureVol = 2;
	textureData.shaderVol = 2;
	textureData.textureNum1 = 71;	//白いテクスチャ
	textureData.textureNum2 = 70;	//炎のテクスチャ
	textureData.shaderName = "PlayerFire";	//シェーダの名前
	textureData.shaderName2 = "PlayerElec";	//シェーダの名前

	//オブジェクト
	object = new FbxObject3D;
	object->Initialize(modelWait, textureData);
	object->PlayAnimation();

	//弾
	bullet = new PlayerBullet;
	bullet->Initialize();

	//雷パーティクル
	elecParticle1 = new ElecParticle();
	elecParticle1->CreateBuffers();
	elecParticle1->SetTextureNum(0);

	//雷パーティクル2
	elecParticle2 = new EnemyBulletParticle();
	elecParticle2->CreateBuffers();
	elecParticle2->SetTextureNum(80);

	//座標
	position = { 0.0f,0.0f,0.0f };
	//回転
	rotation0 = { 0.0f,0.0f,0.0f };
	rotation1 = { 0.0f,0.0f,0.0f };
	//スケール
	scale = { 1.0f,1.0f,1.0f };

	//あたりフラグ
	invincibleFlag = false;
	hitTimer = 0;
}

void PlayerState::Finalize()
{
	delete object;
	delete modelRun;
	delete modelWait;
	delete modelAttack1;
	delete modelAttack2;
	delete modelAttack3;
	delete modelDown;
	delete modelStandUp;
	delete bullet;
	delete elecParticle1;
	delete elecParticle2;
}

void PlayerState::Move()
{
	//プレイヤーの元になる角度
	//AROWキーで角度変更
	rotVelocity.y = keyManager->GetStick(KeyManager::RStickX) * rot0Speed;
	//角度ベクトルを加算
	rotation0 = rotation0 + rotVelocity;
	rotation1 = rotation1 - rotVelocity;

	//左スティック入力による角度変更
	//左スティックの入力がある場合
	if (keyManager->GetStick(KeyManager::LStick) != 0.0f)
	{
		rotation1.y = keyManager->GetStickRot(KeyManager::LStick);
	}
	//左スティックの入力がないけど右スティックの入力はある場合
	else if(keyManager->GetStick(KeyManager::RStick) && keyManager->GetStickRot(KeyManager::RStick) <= PI)
	{
		rotation1 = rotation1 - rotVelocity;
	}
	else if (keyManager->GetStick(KeyManager::RStick))
	{
		rotation1 = rotation1 + rotVelocity;
	}

	//座標
	//左スティックで移動
	XMFLOAT2 stick = normalize(keyManager->GetStick(KeyManager::LStickX), keyManager->GetStick(KeyManager::LStickY));

	//移動速度
	posVelocity.x = stick.x * posSpeed;
	posVelocity.z = stick.y * posSpeed;

	//進行ベクトルを回転
	posVelocity = rollRotation(posVelocity, rotation0);
	//進行ベクトルを加算
	position = position + posVelocity;
}

void PlayerState::Reset()
{
	position = XMFLOAT3(0.0f, 0.0f, -20.0f);
}

void PlayerState::SetTitle(Player* player)
{
	//座標更新
	position = titlePos;

	rotation1 = titleRotation;

	//立ち状態に変更
	player->ChangeState(new Wait());
}

void PlayerState::SetTutorial()
{
	position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	rotation0 = { 0.0f,0.0f,0.0f };
	rotation1 = { 0.0f,0.0f,0.0f };
}

void PlayerState::SetGameScene()
{
	position = gameScenePos;
	rotation0 = { 0.0f,0.0f,0.0f };
	rotation1 = { 0.0f,0.0f,0.0f };
}

void PlayerState::SetMovePhase(Player* player)
{
	position = movePhasePos;
	rotation0 = { 0.0f,0.0f,0.0f };
	rotation1 = { 0.0f,0.0f,0.0f };
	player->ChangeState(new Wait());
}

void PlayerState::SetClear(Player* player)
{
	position = clearPos;
	rotation0 = { 0.0f,0.0f,0.0f };
	rotation1 = { 0.0f,0.0f,0.0f };
	player->ChangeState(new Wait());
}

void PlayerState::SetDevelop(Player* player)
{
	position = developPos;
	rotation0 = { 0.0f,0.0f,0.0f };
	rotation1 = developRot;
	player->ChangeState(new DevelopWait());
}

void PlayerState::SetLockOn(bool lockOnFlag, XMFLOAT3 lockOnPos)
{
	this->lockOnFlag = lockOnFlag;
	this->lockOnPos = lockOnPos;
}

void PlayerState::HitEnemy()
{
	//当たりフラグを立てる
	hitFlag = true;
}

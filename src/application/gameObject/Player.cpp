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
Input* Player::input = nullptr;
DXInput* Player::dxInput = nullptr;
LockOn* Player::lockOn = nullptr;
FbxModel* PlayerState::modelWait = nullptr;
FbxModel* PlayerState::modelRun = nullptr;
FbxModel* PlayerState::modelAttack1 = nullptr;
FbxModel* PlayerState::modelAttack2 = nullptr;
FbxModel* PlayerState::modelAttack3 = nullptr;
FbxModel* PlayerState::modelDown = nullptr;
FbxObject3D* PlayerState::objectWait = nullptr;
FbxObject3D* PlayerState::objectRun = nullptr;
FbxObject3D* PlayerState::objectAttack1 = nullptr;
FbxObject3D* PlayerState::objectAttack2 = nullptr;
FbxObject3D* PlayerState::objectAttack3 = nullptr;
FbxObject3D* PlayerState::objectDown = nullptr;
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

Player::Player()
{
	playerState = new Wait();
}

Player::~Player()
{
	delete playerState;
}

void Player::Initialize()
{
	//プレイヤーステートの初期化
	playerState->Initialize();

	//HP用スプライト
	//緑のHP
	for (int i = 0; i < MaxHP; i++)
	{
		hpSprite1[i] = new Sprite();
		hpSprite1[i]->Initialize();
		hpSprite1[i]->SetTextureNum(28);
	}
	//赤いHP
	hpSprite2 = new Sprite();
	hpSprite2->Initialize();
	hpSprite2->SetTextureNum(29);
	//HPの枠
	hpSprite3 = new Sprite();
	hpSprite3->Initialize();
	hpSprite3->SetTextureNum(30);
}
void Player::UpdateGame()
{
	//フォルム更新
	UpdateForm();

	//プレイヤーステート更新
	playerState->SetDXInput(dxInput);
	playerState->SetPlayerForm(form);
	playerState->SetLockOn(lockOn->GetLockOnFlag(), lockOn->GetTarget());
	playerState->Update();

	//ロックオンの更新
	lockOn->SetPlayerRotation(playerState->GetRotation0());
	lockOn->SetPlayerPosition(playerState->GetPosition());
	if (1)
	{
		for (int i = 0; i < enemyPos.size(); i++)
		{
			lockOn->AddEnemyPos(enemyPos[i]);
		}
		lockOn->Update();
	}


	//スプライト更新
	UpdateSprite();

	//1フレーム前のフォルムを代入
	preForm = form;

	if (HP <= 0)HP = MaxHP;

	//敵クリア
	enemyPos.clear();
}

void Player::UpdateTutorial()
{
	//フォルム更新
	UpdateFormTutorial();

	//フォルム更新
	UpdateForm();

	//プレイヤーステート更新
	playerState->SetDXInput(dxInput);
	playerState->SetPlayerForm(form);
	playerState->SetLockOn(lockOn->GetLockOnFlag(), lockOn->GetTarget());
	playerState->Update();

	//ロックオンの更新
	lockOn->SetPlayerRotation(playerState->GetRotation0());
	lockOn->SetPlayerPosition(playerState->GetPosition());
	if (1)
	{
		for (int i = 0; i < enemyPos.size(); i++)
		{
			lockOn->AddEnemyPos(enemyPos[i]);
		}
		lockOn->Update();
	}


	//スプライト更新
	UpdateSprite();

	//1フレーム前のフォルムを代入
	preForm = form;

	if (HP <= 0)HP = MaxHP;

	//敵クリア
	enemyPos.clear();
}

void Player::UpdateTitle(float timer)
{
	//フォルム更新
	UpdateForm();

	//プレイヤーステート更新
	playerState->SetDXInput(dxInput);
	playerState->SetPlayerForm(form);
	playerState->SetLockOn(lockOn->GetLockOnFlag(), lockOn->GetTarget());
	playerState->Update();

	//ロックオンの更新
	lockOn->SetPlayerRotation(playerState->GetRotation0());
	lockOn->SetPlayerPosition(playerState->GetPosition());
	if (1)
	{
		for (int i = 0; i < enemyPos.size(); i++)
		{
			lockOn->AddEnemyPos(enemyPos[i]);
		}
		lockOn->Update();
	}


	//スプライト更新
	UpdateSprite();

	//1フレーム前のフォルムを代入
	preForm = form;

	if (HP <= 0)HP = MaxHP;

	//敵クリア
	enemyPos.clear();
}

void Player::UpdateSprite()
{
	//緑のHP
	for (int i = 0; i < HP; i++)
	{
		XMFLOAT2 addPos(hpFrameScale1 + (hpFrameScale2 * i) + (hpSprite1Scale.x * i), hpFrameScale3);
		hpSprite1[i]->Update(hpSpritePos + addPos, hpSprite1Scale);
	}
	//赤いHP
	hpSprite2->Update(hpSpritePos + XMFLOAT2(hpFrameScale1, hpFrameScale3), hpSprite2Scale);
	//HPの枠
	hpSprite3->Update(hpSpritePos, hpSprite3Scale);
	//攻撃UIのスプライト
	/*attackElecSprite->Update();
	attackFireSprite->Update();*/
}

void Player::Draw(ID3D12GraphicsCommandList* cmdList)
{
	//プレイヤーの描画
	playerState->Draw(cmdList);

	//ステート更新
	playerState->UpdateState(this);
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

void Player::SetSRV(ID3D12DescriptorHeap* SRV)
{
	//パーティクル描画
	playerState->SetSRV(SRV);
}

void Player::DrawSpriteGame(ID3D12GraphicsCommandList* cmdList)
{
	//電気フォームだったら
	if (form == Elec)
	{
		lockOn->Draw(cmdList);
	}

	//緑のHP
	for (int i = 0; i < HP; i++)
	{
		hpSprite1[i]->Draw(cmdList);
	}
	//赤いHP
	if (HP == 1)
	{
		hpSprite2->Draw(cmdList);
	}
	//HPの枠
	hpSprite3->Draw(cmdList);
}

void Player::DrawSpriteTutorial(ID3D12GraphicsCommandList* cmdList)
{
	//電気フォームだったら
	if (form == Elec)
	{
		lockOn->Draw(cmdList);
	}
}

//void Player::TitleControl(float timer)
//{
//	//移動
//	TitleMove(timer);
//}

void Player::UpdateForm()
{
	//Lボタンでフォルムチェンジフラグを立てる
	if (dxInput->TriggerKey(DXInput::PAD_LEFT_SHOULDER) && formChangeFlag == false)
	{
		if (preForm == Fire)form = Elec;	//炎だったら電気に変える
		else if (preForm == Elec)form = Fire;	//電気だったら炎に帰る
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

void Player::UpdateFormTutorial()
{
	//Lボタンでフォルムチェンジフラグを立てる
	if (dxInput->TriggerKey(DXInput::PAD_LEFT_SHOULDER) && formChangeFlag == false)
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

void Player::SetTutorial()
{
	playerState->SetTutorial();
}

void Player::SetGameScene()
{
	playerState->SetGameScene();
	tutorialFlag = 1;
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
	playerState->Initialize();
}

void PlayerState::DrawParticle(ID3D12GraphicsCommandList* cmdList)
{
	bullet->DrawParticle(cmdList);
	elecParticle1->Draw(cmdList);
	elecParticle2->Draw(cmdList);
}

void PlayerState::Update()
{
	//タイマー更新
	objectTimer++;

	//オブジェクト更新
	UpdateObject();

	////ダウン状態更新
	//UpdateDown();

	//コライダー更新
	UpdateCollider();

	//攻撃更新
	UpdateAttack();

	//弾更新
	bullet->Update();

	//パーティクル更新
	elecParticle1->Update();
	elecParticle2->Update();

	//動き
	Move();

	//当たりフラグを元に戻す
	hitFlag = false;
}

void PlayerState::UpdateCollider()
{
	colliderData.scale = scale;
	colliderData.rotation = rotation0;
	colliderData.center = position;
}

void PlayerState::UpdateDown()
{
	//ヒットフラグがたったら
	if (hitFlag == true)
	{
		invincibleFlag = true;
	}

	//無敵時間が終わったらフラグを元に戻す
	if (hitTimer >= frameDown * 2.0f) 
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

void PlayerState::StaticInitialize()
{
	//コライダーの設定
	colliderData.type = "Sphere";	//判定を球体で取るため
	colliderData.objectName = "player";
	colliderData.scale = { 1.0f,1.0f,1.0f };
	colliderData.rotation = { 0.0f,0.0f,0.0f };
	colliderData.center = { 0.0f,0.0f,0.0f };
	//コライダーマネージャーにセット
	ColliderManager::SetCollider(colliderData);

	//プレイヤーのシェーダを別に設定
	textureData.textureVol = 2;
	textureData.shaderVol = 2;
	textureData.textureNum1 = 27;	//白いテクスチャ
	textureData.textureNum2 = 31;	//炎のテクスチャ
	textureData.shaderName = "PlayerFire";	//シェーダの名前
	textureData.shaderName2 = "PlayerElec";	//シェーダの名前

	//モデル
	modelWait = FbxLoader::GetInstance()->LoadModelFromFile("playerWait");
	modelRun = FbxLoader::GetInstance()->LoadModelFromFile("playerRun");
	modelAttack1 = FbxLoader::GetInstance()->LoadModelFromFile("playerAttack1");
	modelAttack2 = FbxLoader::GetInstance()->LoadModelFromFile("playerAttack2");
	modelAttack3 = FbxLoader::GetInstance()->LoadModelFromFile("playerAttack3");
	modelDown = FbxLoader::GetInstance()->LoadModelFromFile("playerDown");

	//オブジェクト
	objectWait = new FbxObject3D;
	objectWait->Initialize(modelWait, textureData);
	objectWait->PlayAnimation();

	objectRun = new FbxObject3D;
	objectRun->Initialize(modelRun, textureData);
	objectRun->PlayAnimation();

	objectAttack1 = new FbxObject3D;
	objectAttack1->Initialize(modelAttack1, textureData);
	objectAttack1->PlayAnimation();

	objectAttack2 = new FbxObject3D;
	objectAttack2->Initialize(modelAttack2, textureData);
	objectAttack2->PlayAnimation();

	objectAttack3 = new FbxObject3D;
	objectAttack3->Initialize(modelAttack3, textureData);
	objectAttack3->PlayAnimation();

	objectDown = new FbxObject3D;
	objectDown->Initialize(modelDown, textureData);
	objectDown->PlayAnimation();

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
	elecParticle2->SetTextureNum(4);

	//座標
	position = { 0.0f,0.0f,0.0f };
	//回転
	rotation0 = { 0.0f,0.0f,0.0f };
	rotation1 = { 0.0f,0.0f,0.0f };
	//スケール
	scale = { 1.0f,1.0f,1.0f };
}

void PlayerState::Move()
{
	//プレイヤーの元になる角度
	//AROWキーで角度変更
	rotVelocity.y = dxInput->GetStick(DXInput::RStickX) * rot0Speed;
	/*rotVelocity.y = (input->PushKey(DIK_RIGHT) - input->PushKey(DIK_LEFT)) * rotSpeed;*/
	//角度ベクトルを加算
	rotation0 = rotation0 + rotVelocity;

	//左スティック入力による角度変更
	//左スティックの入力がある場合
	if (dxInput->GetStick(DXInput::LStick) != 0.0f)
	{
		rotation1.y = dxInput->GetStickRot(DXInput::LStick);
	}
	//左スティックの入力がないけど右スティックの入力はある場合
	else if(dxInput->GetStick(DXInput::RStick) && dxInput->GetStickRot(DXInput::RStick) <= PI)
	{
		rotation1 = rotation1 - rotVelocity;
	}
	else if (dxInput->GetStick(DXInput::RStick))
	{
		rotation1 = rotation1 + rotVelocity;
	}

	//座標
	//左スティックで移動
	XMFLOAT2 stick = normalize(dxInput->GetStick(DXInput::LStickX), dxInput->GetStick(DXInput::LStickY));

	//移動速度
	posVelocity.x = stick.x * posSpeed;
	posVelocity.z = stick.y * posSpeed;
	/*posVelocity.x = (input->PushKey(DIK_D) - input->PushKey(DIK_A)) * posSpeed;
	posVelocity.z = (input->PushKey(DIK_W) - input->PushKey(DIK_S)) * posSpeed;*/

	//進行ベクトルを回転
	posVelocity = rollRotation(posVelocity, rotation0);
	//進行ベクトルを加算
	position = position + posVelocity;
}

void PlayerState::Reset()
{
	position = XMFLOAT3(0.0f, 0.0f, -20.0f);
}

void PlayerState::SetTutorial()
{
	position = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

void PlayerState::SetGameScene()
{
	position = XMFLOAT3(0.0f, 0.0f, -100.0f);
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

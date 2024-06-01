#include "TutorialEnemy.h"
#include "mathOriginal.h"
#include "FbxLoader.h"
#include "imgui.h"
#include "ColliderManager.h"
#define G 6.674	//万有引力定数
#define GAcceleration 9.80665 * 1/10	//重力加速度

Camera* TutorialEnemy::camera = nullptr;

TutorialEnemy::~TutorialEnemy()
{
	delete object;
	delete modelDash;
	delete modelDown;
	delete modelStand;
	delete hpBar1;
	delete hpBar2;
	delete hpBar3;
	delete hpBar4;
}


void TutorialEnemy::Initialize()
{
	//HPバーのスプライト
	hpBar1 = new Sprite();
	hpBar1->Initialize();
	hpBar1->SetTextureNum(58);
	hpBar2 = new Sprite();
	hpBar2->Initialize();
	hpBar2->SetTextureNum(59);
	hpBar3 = new Sprite();
	hpBar3->Initialize();
	hpBar3->SetTextureNum(60);
	hpBar4 = new Sprite();
	hpBar4->Initialize();
	hpBar4->SetTextureNum(61);

	//モデル
	modelDash = FbxLoader::GetInstance()->LoadModelFromFile("enemyDash");
	modelDown = FbxLoader::GetInstance()->LoadModelFromFile("enemyDown");
	modelStand = FbxLoader::GetInstance()->LoadModelFromFile("enemyStand");
	//オブジェクト
	object = new FbxObject3D;
	object->Initialize();
	object->SetModel(modelStand);
	object->SetTextureNum(0);
	object->PlayAnimation();

	//コライダーの設定
	colliderData.type = "Sphere";	//判定を球体で取るため
	colliderData.objectName = "tutorialEnemy";
	colliderData.scale = scale;
	colliderData.rotation = rotation;
	colliderData.center = position;
	//コライダーマネージャーにセット
	ColliderManager::SetCollider(colliderData);
}

void TutorialEnemy::UpdateTutorial()
{
	if (isDead2 == true)return;

	//コライダー更新
	UpdateCollider();

	//スプライト更新
	UpdateSprite();

	//ダッシュ中
	if (tutorialFlag == 11)
	{
		//ステート更新
		UpdateStateTutorial();
		//プレイヤーに向かって走る
		if(tutorialDashFlag == false)MoveGame();
		//オブジェクトとの当たり判定をとる
		UpdateHitObject();
	}

	//転んでいる最中
	if (tutorialFlag == 12)
	{
		//チュートリアル12用の更新
		UpdateTutorial12();
		//チュートリアル12用ダメージ更新
		UpdateDamageTutorial();
	}

	//オブジェクト更新
	UpdateObject();
}

void TutorialEnemy::UpdateGame()
{
	if (isDead2 == true)return;

	//コライダー更新
	UpdateCollider();

	//ダメージ更新
	UpdateDamage();

	if (isDead3 == false)MoveGame();
	
	//オブジェクト更新
	UpdateObject();
}

void TutorialEnemy::UpdateMovePhase()
{
	if (isDead2 == true)return;

	//コライダー更新
	UpdateCollider();

	//ダメージ更新
	UpdateDamage();

	//挙動
	MoveMovePhase();

	//オブジェクト更新
	UpdateObject();
}

void TutorialEnemy::UpdateStateTutorial()
{
	//ダッシュシーンに移ったら
	if (tutorialDashFlag == true && length(position - playerPos) >= 20)
	{
		tutorialDashFlag = false;
		SetDash();
	}
	else if (tutorialDashFlag == false && length(position - playerPos) < 20)
	{
		tutorialDashFlag = true;
		SetStand();
	}
}

void TutorialEnemy::UpdateObject()
{
	object->SetPosition(position);
	object->SetRotation(rotation);
	object->SetScale(scale);
	
	object->Update();
}

void TutorialEnemy::UpdateSprite()
{
	//HPバーを現在のHPに
	hpBar2Scale.x = hpBar2OriginalScale.x * (HP / maxHP);
	hpBar3Pos.x = hpBar3OriginalPos.x - (hpBar2OriginalScale.x * ((maxHP - HP) / maxHP));

	//更新
	hpBar1->Update(hpBar1Pos, hpBar1Scale);
	hpBar2->Update(hpBar2Pos, hpBar2Scale);
	hpBar3->Update(hpBar3Pos, hpBar3Scale);
	hpBar4->Update(hpBar4Pos, hpBar4Scale);
}

void TutorialEnemy::UpdateCollider()
{
	//コライダーデータ更新
	colliderData.scale = colliderScale;
	colliderData.rotation = rotation;
	colliderData.center = position;
}

void TutorialEnemy::UpdateObjectCollider()
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

void TutorialEnemy::UpdateDamage()
{
	//炎攻撃をくらった際
	if (hitFlag1 == true)
	{
		//HPを減らす
		HP -= 1.0f;
	}

	//雷攻撃をくらった際
	if (hitElec == true)
	{
		//HPを減らす
		HP -= 5.0f;
	}

	//死亡
	if (HP <= 0)
	{
		isDead1 = true;
	}

	//死亡したフレームの処理
	if (isDead1 == true && isDead3 == false)
	{
		SetDown();
		isDead3 = true;
	}

	//死亡したら
	if (isDead3 == true)
	{
		deadTimer++;
		if (deadTimer >= deadTime)
		{
			isDead2 = true;
		}
	}

	//フラグをもとに戻す
	hitFlag1 = false;
	hitElec = false;
}

void TutorialEnemy::UpdateDamageTutorial()
{
	//炎攻撃をくらった際
	if (hitFlag1 == true)
	{
		//HPを減らす
		HP -= 1.0f;
	}

	//雷攻撃をくらった際
	if (hitElec == true)
	{
		//HPを減らす
		HP -= 5.0f;
	}

	//死亡
	if (HP <= 0)
	{
		isDead1 = true;
	}

	//死亡したフレームの処理
	if (isDead1 == true && isDead3 == false)
	{
		isDead3 = true;
	}

	//死亡したら
	if (isDead3 == true)
	{
		deadTimer++;
		if (deadTimer >= deadTime)
		{
			isDead2 = true;
		}
	}

	//フラグをもとに戻す
	hitFlag1 = false;
	hitElec = false;
}

void TutorialEnemy::Draw(ID3D12GraphicsCommandList* cmdList)
{
	if (isDead2 == false)
	{
		object->Draw(cmdList);
	}
}

void TutorialEnemy::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	if (isDead2 == false)
	{
		object->DrawLightView(cmdList);
	}
}

void TutorialEnemy::DrawSprite(ID3D12GraphicsCommandList* cmdList)
{
	if (isDead3 == true)return;
	hpBar2->Draw(cmdList);
	hpBar1->Draw(cmdList);
	hpBar3->Draw(cmdList);
}

void TutorialEnemy::MoveGame()
{
	//プレイヤーまでのベクトルを求める
	XMFLOAT3 velo = XMFLOAT3(playerPos.x - position.x, 0.0f, playerPos.z - position.z);
	//正規化
	velo = normalize(velo) * speed;
	//座標に加算
	position = position + velo;

	XMFLOAT3 rot = getVectorRotation(velo);
	rotation = rot;
}

void TutorialEnemy::MoveMovePhase()
{
	//プレイヤーまでのベクトルを求める
	XMFLOAT3 velo = XMFLOAT3(playerPos.x - position.x, 0.0f, playerPos.z - position.z);

	XMFLOAT3 rot = getVectorRotation(velo);
	rotation = rot;
}

void TutorialEnemy::StatusManager()
{
}

void TutorialEnemy::SetSRV(ID3D12DescriptorHeap* SRV)
{
	object->SetSRV(SRV);
}

void TutorialEnemy::SetDash()
{
	//ダッシュモデルをセットしてアニメーション開始
	object->SetModel(modelDash);
	object->PlayAnimation();
}

void TutorialEnemy::SetDown()
{
	//ダウンモデルをセットしてアニメーション開始
	object->SetModel(modelDown);
	object->PlayAnimation();
}

void TutorialEnemy::SetStand()
{
	//立つモデルをセットしてアニメーション開始
	object->SetModel(modelStand);
	object->PlayAnimation();
}

void TutorialEnemy::SetTutorial()
{
	hitFlag1 = false;
	hitElec = false;
	hitObjectFlag = false;
	downFlag = false;
	tutorial12Timer = 0;
	SetStand();
}

void TutorialEnemy::SetGameScene()
{
	SetDash();
}

void TutorialEnemy::SetMovePhase()
{
	//敵消す
	isDead1 = true;
	isDead2 = true;
	isDead3 = true;
	SetStand();
}

void TutorialEnemy::AddEnemy(XMFLOAT3 pos)
{
	//生き返らせる
	isDead1 = false;
	isDead2 = false;
	isDead3 = false;
	deadTimer = 0;
	HP = maxHP;
	//指定の座標に配置
	position = pos;
}

void TutorialEnemy::AddEnemyTutorialScene(XMFLOAT3 pos)
{
	//まだ死んでない場合スルー
	if (isDead2 == false)return;
	downFlag = false;
	tutorialDashFlag = false;
	SetStand();
	AddEnemy(pos);
}

void TutorialEnemy::AddEnemyGameScene(XMFLOAT3 pos)
{
	//まだ死んでない場合スルー
	if (isDead2 == false)return;
	SetDash();
	AddEnemy(pos);
}

void TutorialEnemy::AddEnemyMovePhase(XMFLOAT3 pos)
{
	//まだ死んでない場合スルー
	if (isDead2 == false)return;
	SetStand();
	AddEnemy(pos);
}

void TutorialEnemy::Reset()
{
	HP = maxHP;
	isDead1 = false;
	isDead2 = false;
	isDead3 = false;
	deadTimer = 0;
}

void TutorialEnemy::HitBullet1()
{
	//被弾フラグを立てる
	hitFlag1 = true;
}

void TutorialEnemy::SetHitPlayer()
{
	isDead1 = true;
}

bool TutorialEnemy::GetCallFlag()
{
	if (isDead2 == true)
	{
		callTimer++;
		if (callTimer >= callTime)
		{
			callTimer = 0;
			return true;
		}
	}
	return false;
}

void TutorialEnemy::UpdateHitWall(JSONLoader::ColliderData objectColliderData)
{
	//壁の中にいたら処理終了
	if (ColliderManager::CheckCollider(colliderData, objectColliderData, true) == true)return;

	//壁の外にいる時のみ
	while (ColliderManager::CheckCollider(colliderData, objectColliderData, true) == false)
	{
		//プレイヤーから原点のベクトル
		XMFLOAT3 vec = XMFLOAT3(0.0f, 0.0f, 0.0f) - position;
		//プレイヤーから原点のベクトルを正規化
		vec = normalize(vec);
		//壁の中に戻るまで加算
		position = position + (vec * knockBackSpeed);
		//コライダーデータの座標更新
		colliderData.center = position;
	}
	//フラグを立てる
	hitObjectFlag = true;
}

void TutorialEnemy::UpdateHitPiller(JSONLoader::ColliderData objectColliderData)
{
	//柱に衝突してなかったら処理終了
	if (ColliderManager::CheckCollider(colliderData, objectColliderData) == false)return;

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
	//フラグを立てる
	hitObjectFlag = true;
}

void TutorialEnemy::UpdateHitObject()
{
	//オブジェクトに当たってなかったらスキップ
	if (hitObjectFlag != true)return;

	//ダウンモデルをセット
	SetDown();

	//チュートリアルシーンに送る用
	downFlag = true;

	hitObjectFlag = false;
}

void TutorialEnemy::UpdateTutorial12()
{
	//タイマー更新
	tutorial12Timer++;

	//倒れているときにアニメーションを止める
	if (tutorial12Timer >= frameFallDownEnemy)
	{
		object->StopAnimation();
	}
}

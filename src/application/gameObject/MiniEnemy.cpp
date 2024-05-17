#include "MiniEnemy.h"
#include "mathOriginal.h"
#include "FbxLoader.h"
#include "imgui.h"
#include "ColliderManager.h"

Camera* MiniEnemy::camera = nullptr;
Input* MiniEnemy::input = nullptr;

void MiniEnemy::Initialize()
{
	//HPフレームのビルボード モデル
	//hpFrameSpriteModel = new BillboardSpriteModel();
	//hpFrameSpriteModel->CreateBuffers();
	//hpFrameSpriteModel->SetTextureNum(23);

	////HPフレームのビルボード
	//hpFrameSprite = new BillboardSprite();
	//hpFrameSprite->Initialize();
	//hpFrameSprite->SetModel(hpFrameSpriteModel);
	//hpFrameSprite->SetScale(hpFrameScale);

	////HPゲージのビルボード モデル
	//hpBarSpriteModel = new BillboardSpriteModel();
	//hpBarSpriteModel->CreateBuffers();
	//hpBarSpriteModel->SetTextureNum(24);

	////HPゲージのビルボード
	//hpBarSprite = new BillboardSprite();
	//hpBarSprite->Initialize();
	//hpBarSprite->SetModel(hpBarSpriteModel);

	//モデル
	modelDash = FbxLoader::GetInstance()->LoadModelFromFile("miniEnemyDash");
	modelDown = FbxLoader::GetInstance()->LoadModelFromFile("enemyDown");
}

void MiniEnemy::Update()
{
	//攻撃更新
	UpdateAttack();

	//オブジェクト更新
	UpdateObject();

	//コライダー更新
	UpdateCollider();

	//スプライト更新
	UpdateSprite();

	//ダメージ更新
	UpdateDamage();

	//死亡処理
	DeleteEnemy();
}

void MiniEnemy::UpdateObject()
{

	for (int i = 0; i < enemys.size(); i++)
	{
		if (enemys[i].status == Dash)
		{
			enemys[i].objectDash->SetPosition(enemys[i].position);
			enemys[i].objectDash->SetRotation(enemys[i].rotation);
			enemys[i].objectDash->Update();
		}
		else
		{
			enemys[i].objectDown->SetPosition(enemys[i].position);
			enemys[i].objectDown->SetRotation(enemys[i].rotation);
			enemys[i].objectDown->Update();
		}
	}
}

void MiniEnemy::UpdateSprite()
{
	//HPバーを現在のHPに
	//hpBar2Scale.x = hpBar2OriginalScale.x * (HP / maxHP);
	//hpBar3Pos.x = hpBar3OriginalPos.x - (hpBar2OriginalScale.x * ((maxHP - HP) / maxHP));

	/*hpFrameSprite->SetPosition(XMFLOAT3(0.0f, 5.0f, 0.0f));
	hpBarSprite->SetPosition(XMFLOAT3(0.0f, 5.0f, 0.0f));
	hpBarSprite->SetScale(hpBarScale);

	hpFrameSprite->Update();
	hpBarSprite->Update();*/
}

void MiniEnemy::UpdateCollider()
{
	for (int i = 0; i < enemys.size(); i++)
	{
		enemys[i].colliderData.rotation = enemys[i].rotation;
		enemys[i].colliderData.center = enemys[i].position + XMFLOAT3(0.0f, 5.0f, 0.0f);
	}
}

void MiniEnemy::UpdateDamage()
{
	for (int i = 0; i < enemys.size(); i++)
	{
		//炎攻撃をくらった際
		if (enemys[i].hitFireFlag == true)
		{
			//HPを減らす
			enemys[i].HP -= fireDamage;
			//フラグをもとに戻す
			enemys[i].hitFireFlag = false;
		}
		//HP0の場合
		if (enemys[i].HP <= 0)
		{
			enemys[i].deadFlag = true;
			enemys[i].status = Down;
		}
		//ダウン状態になったとき
		if (enemys[i].status == Down && enemys[i].preStatus == Dash)
		{
			enemys[i].objectDash->StopAnimation();
			enemys[i].objectDown->PlayAnimation();
		}
	}
}

void MiniEnemy::DeleteEnemy()
{
	for (int i = 0; i < enemys.size(); i++)
	{
		//死亡タイマー更新
		if (enemys[i].deadFlag == true)
		{
			enemys[i].deadTimer++;
			if (enemys[i].deadTimer >= deadTime)
			{
				enemys.erase(enemys.begin() + i);
			}
		}
	}
}

void MiniEnemy::Draw(ID3D12GraphicsCommandList* cmdList)
{
	//ImGui
	ImGui::Begin("miniEnemy");
	ImGui::SetWindowPos(ImVec2(0, 600));
	ImGui::SetWindowSize(ImVec2(700, 150));
	ImGui::InputInt("debugNum", debugNum);
	ImGui::End();

	for (int i = 0; i < enemys.size(); i++)
	{
		if (enemys[i].status == Dash)
		{
			enemys[i].objectDash->Draw(cmdList);
		}
		else
		{
			enemys[i].objectDown->Draw(cmdList);
		}
	}

	//前フレームのステータス更新
	for (int i = 0; i < enemys.size(); i++)
	{
		enemys[i].preStatus = enemys[i].status;
	}
}

void MiniEnemy::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{

	for (int i = 0; i < enemys.size(); i++)
	{
		if (enemys[i].status == Dash)
		{
			enemys[i].objectDash->DrawLightView(cmdList);
		}
		else
		{
			enemys[i].objectDown->DrawLightView(cmdList);
		}
	}
}

void MiniEnemy::DrawSprite(ID3D12GraphicsCommandList* cmdList)
{
	//hpFrameSprite->Draw(cmdList);
	//hpBarSprite->Draw(cmdList);
}

void MiniEnemy::UpdateAttack()
{
	for (int i = 0; i < enemys.size(); i++)
	{
		//ダッシュ中
		if (enemys[i].status == Dash)
		{
			//プレイヤーまでのベクトルを求める
			XMFLOAT3 velo = XMFLOAT3(playerPos.x - enemys[i].position.x, 0.0f, playerPos.z - enemys[i].position.z);
			//正規化
			velo = normalize(velo) * speed;
			//座標に加算
			enemys[i].position = enemys[i].position + velo;

			XMFLOAT3 rot = getVectorRotation(velo);
			enemys[i].rotation = rot;
		}
	}
}

void MiniEnemy::StatusManager()
{
}

void MiniEnemy::SetSRV(ID3D12DescriptorHeap* SRV)
{
	for (int i = 0; i < enemys.size(); i++)
	{
		if (enemys[i].status == Dash)
		{
			enemys[i].objectDash->SetSRV(SRV);
		}
		else
		{
			enemys[i].objectDown->SetSRV(SRV);
		}
	}
}

void MiniEnemy::Reset()
{
}

void MiniEnemy::AddEnemy(XMFLOAT3 pos)
{
	Enemy enemy;

	//与えられた座標をもとにオブジェクト生成
	enemy.objectDash = new FbxObject3D;
	enemy.objectDash->Initialize();
	enemy.objectDash->SetModel(modelDash);
	enemy.objectDash->SetTextureNum(0);
	enemy.objectDash->PlayAnimation();
	enemy.objectDash->SetPosition(pos);
	enemy.objectDash->SetScale(scale);

	//与えられた座標をもとにオブジェクト生成
	enemy.objectDown = new FbxObject3D;
	enemy.objectDown->Initialize();
	enemy.objectDown->SetModel(modelDown);
	enemy.objectDown->SetTextureNum(0);
	enemy.objectDown->StopAnimation();
	enemy.objectDown->SetPosition(pos);
	enemy.objectDown->SetScale(scale);

	//コライダーの設定
	//コライダーごとに名前をつける
	std::string objectName = "miniEnemy" + std::to_string(number);
	//コライダーデータの生成
	enemy.colliderData.type = "Sphere";	//判定を球体で取るため
	enemy.colliderData.objectName = objectName;
	enemy.colliderData.scale = colliderScale;
	enemy.colliderData.rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	enemy.colliderData.center = pos;
	//コライダーマネージャーにセット
	ColliderManager::SetCollider(enemy.colliderData);

	//ステータス
	enemy.status = Dash;
	enemy.preStatus = Dash;
	//座標設定
	enemy.position = pos;
	//角度
	enemy.rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	//HP
	enemy.HP = maxHP;
	//当たりフラグ
	enemy.hitFireFlag = false;
	enemy.hitElecFlag = false;
	//死亡フラグ
	enemy.deadFlag = false;
	//死亡タイマー
	enemy.deadTimer = 0;

	enemys.emplace_back(enemy);

	//弾につける番号を増やす
	number++;
}
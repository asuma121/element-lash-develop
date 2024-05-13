#include "LockOn.h"
#include "mathOriginal.h"
#include "imgui.h"

void LockOn::Initialize()
{
	//ビルボードのスプライト モデル
	lockOnSpriteModel1 = new BillboardSpriteModel();
	lockOnSpriteModel1->CreateBuffers();
	lockOnSpriteModel1->SetTextureNum(22);

	//ビルボードのスプライト
	lockOnSprite1 = new BillboardSprite();
	lockOnSprite1->Initialize();
	lockOnSprite1->SetModel(lockOnSpriteModel1);

	//ロックオンしていない時のスプライト
	lockOnSprite2 = new Sprite();
	lockOnSprite2->Initialize();
	lockOnSprite2->SetTextureNum(22);
	lockOnSprite2->SetAlpha(0.2f);
	lockOnSprite2->SetScale(lockOnSpriteScale);
	lockOnSprite2->SetPosition(lockOnSpritePos);
	lockOnSprite2->Update();
}

void LockOn::Update()
{
	//最大射程に設定
	target = { hitLength,hitLength,hitLength };

	//全ての敵にロックオン判定
	for (int i = 0; i < enemyPosition.size(); i++)
	{
		//カメラからプレイヤーのベクトルの角度を取得
		float rot1 = getVectorRotation(playerPosition - camera->GetEye()).y;
		//プレイヤーから敵のベクトルの角度を取得
		float rot2 = getVectorRotation(enemyPosition[i] - playerPosition).y;

		debugTimer[0] = rot1;
		debugTimer2[0] = rot1 - rot2;

		//カメラの画角内にいなければスルー
		if (-hitAngle > rot1 - rot2 || rot1 - rot2 > hitAngle)
		{
			if( -2*PI + hitAngle < rot1 - rot2 || 2 * PI - hitAngle > rot1 - rot2)
			continue;
		}
		//判定の距離以内にいなければスルー
		if (length(playerPosition - enemyPosition[i]) > hitLength)continue;
		//ロックオンしているのでフラグを立てる
		lockOnFlag = true;
		//カメラから最短の敵を計算
		if (length(target) > length(camera->GetEye() - enemyPosition[i]))
		{
			target = enemyPosition[i];
		}
	}

	if (lockOnFlag)
	{
		//ロックオンスプライトの座標
		XMFLOAT3 sprite1Pos = target;

		//敵の足元を参照しているのでいい感じにする
		sprite1Pos.y += 50.0f;

		//ターゲット→カメラのベクトルを求める
		XMFLOAT3 vec = sprite1Pos - camera->GetEye();
		//ターゲット→カメラのベクトルの長さを求める
		float len = length(vec);
		//正規化
		vec = normalize(vec);
		//ターゲットより少し前に出す
		sprite1Pos = sprite1Pos - XMFLOAT3(vec.x * (len * 0.8f), vec.y * (len * 0.8f), vec.z * (len * 0.8f));

		//スプライト更新
		lockOnSprite1->SetPosition(sprite1Pos);
		lockOnSprite1->SetScale(XMFLOAT3(2.5f, 2.5f, 2.5f));
		lockOnSprite1->Update();

		debugTargetPos[0] = sprite1Pos.x;
		debugTargetPos[1] = sprite1Pos.y;
		debugTargetPos[2] = sprite1Pos.z;
	}
	//ロックオンしていない時のターゲットを設定する
	else
	{
		//カメラの向きのベクトル取得
		XMFLOAT3 velo = (camera->GetTarget() + XMFLOAT3(0.0f,3.0f,0.0f)) - camera->GetEye();
		velo = normalize(velo);
		velo = velo * hitLength;
		target = camera->GetEye() + velo;
	}

	if (lockOnFlag)debugNum[0] = 1;
	else { debugNum[0] = 0; }

	//敵の座標をクリアする
	enemyPosition.clear();
}

void LockOn::AddEnemyPos(XMFLOAT3 position)
{
	//敵の座標を追加
	enemyPosition.emplace_back(position);
}

void LockOn::Draw(ID3D12GraphicsCommandList* cmdList)
{
	//ロックオンしているとき描画
	if (lockOnFlag == true)
	{
		lockOnSprite1->Draw(cmdList);
	}

	//ロックオンしていない時描画
	else
	{
		lockOnSprite2->Draw(cmdList);
	}

	debugTargetFlag[0] = lockOnFlag;

	//ロックオンフラグを戻す
	lockOnFlag = false;

	//ImGui
	ImGui::Begin("LockOn");
	ImGui::SetWindowPos(ImVec2(500, 300));
	ImGui::SetWindowSize(ImVec2(500, 150));
	//ImGui::InputFloat2("debugPos", debugPos);
	ImGui::InputFloat3("targetPos", debugTargetPos);
	ImGui::InputFloat("targetFlag", debugTargetFlag);
	ImGui::End();
}

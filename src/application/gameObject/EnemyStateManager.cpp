#include "EnemyStateManager.h"
#include "mathOriginal.h"
#include "ColliderManager.h"
#include "MiniEnemy.h"

void Stand::Initialize()
{
	//アニメーションの設定
	objectStand->StopAnimation();
	objectStand->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;
}

void Stand::Move()
{
}

void Stand::UpdateState(Enemy* enemy)
{
}

void Stand::UpdateStateTutorial(Enemy* enemy)
{
	//攻撃前兆のアニメーションも終わったら
	if (tutorialTimer > tutorialStandFrame + frameAttackOmen1)
	{
		return;
	}

	//しばらく立ってる
	if (tutorialTimer > tutorialStandFrame)
	{
		enemy->ChangeState(new AttackOmen1());
		return;
	}
}

void Stand::Draw(ID3D12GraphicsCommandList* cmdList)
{
	objectStand->Draw(cmdList);
}

void Stand::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	objectStand->DrawLightView(cmdList);
}

void Stand::SetSRV(ID3D12DescriptorHeap* SRV)
{
	objectStand->SetSRV(SRV);
}

void Stand::UpdateObject()
{
	objectStand->SetPosition(position);
	objectStand->SetRotation(rotation);
	objectStand->SetScale(scale);
	objectStand->Update();
}

void Walk::Initialize()
{
	//アニメーションの設定
	objectWalk->StopAnimation();
	objectWalk->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;
}

void Walk::Move()
{
	//プレイヤーと敵のベクトル取得
	XMFLOAT3 velo = playerPos - position;
	//敵がプレイヤーの向きを向くようにする
	rotation.y = getVectorRotation(velo).y;

	//プレイヤーに近づく
	position = position + normalize(velo) * walkSpeed;
}

void Walk::UpdateState(Enemy* enemy)
{
}

void Walk::Draw(ID3D12GraphicsCommandList* cmdList)
{
	objectWalk->Draw(cmdList);
}

void Walk::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	objectWalk->DrawLightView(cmdList);
}

void Walk::SetSRV(ID3D12DescriptorHeap* SRV)
{
	objectWalk->SetSRV(SRV);
}

void Walk::UpdateObject()
{
	objectWalk->SetPosition(position);
	objectWalk->SetRotation(rotation);
	objectWalk->SetScale(scale);
	objectWalk->Update();
}

void Attack01::Initialize()
{
	//アニメーションの設定
	objectAttack1->StopAnimation();
	objectAttack1->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;
}

void Attack01::Move()
{
}

void Attack01::UpdateState(Enemy* enemy)
{
	//弾を打ち終えたら攻撃前兆へ
	if (objectTimer >= frameAttack1)
	{
		//プレイヤーとの距離が近い場合もう一度弾
		if (dashLength >= length(playerPos - position))
		{
			nextAttack01 = true;
		}
		//プレイヤーとの距離が遠い場合ダッシュ
		else
		{
			nextDash = true;
		}
		enemy->ChangeState(new AttackOmen1());
		return;
	}
}

void Attack01::Draw(ID3D12GraphicsCommandList* cmdList)
{
	objectAttack1->Draw(cmdList);
}

void Attack01::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	objectAttack1->DrawLightView(cmdList);
}

void Attack01::SetSRV(ID3D12DescriptorHeap* SRV)
{
	objectAttack1->SetSRV(SRV);
}

void Attack01::UpdateObject()
{
	objectAttack1->SetPosition(position);
	objectAttack1->SetRotation(rotation);
	objectAttack1->SetScale(scale);
	objectAttack1->Update();
}

void AttackOmen1::Initialize()
{
	//アニメーションの設定
	objectAttackOmen1->StopAnimation();
	objectAttackOmen1->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;
}

void AttackOmen1::Move()
{
	if (objectTimer == 1)
	{
		//プレイヤーと敵のベクトル取得
		XMFLOAT3 velo = playerPos - position;

		//敵がプレイヤーの向きを向くようにする
		rotation.y = getVectorRotation(velo).y;
	}
}

void AttackOmen1::UpdateState(Enemy* enemy)
{
	//アニメーションが終わったら
	if (objectTimer >= frameAttackOmen1)
	{
		//次の行動が敵呼び出しの時
		if (nextCallMiniEnemy)
		{
			nextCallMiniEnemy = false;
			enemy->ChangeState(new CallMiniEnemy());
			return;
		}
		//次の行動がダッシュの時
		if (nextDash)
		{
			nextDash = false;
			enemy->ChangeState(new Dash());
			return;
		}
		//次の行動が敵呼び出しの時
		if (nextAttack01)
		{
			nextAttack01 = false;
			enemy->ChangeState(new Attack01());
			return;
		}
	}
}

void AttackOmen1::UpdateStateTutorial(Enemy* enemy)
{
	//アニメーションが終わったら
	if (objectTimer >= frameAttackOmen1)
	{
		enemy->ChangeState(new Stand());
		return;
	}
}

void AttackOmen1::UpdateStateMovePhase(Enemy* enemy)
{
	// アニメーションが終わったら
	if (objectTimer >= frameAttackOmen1)
	{
		enemy->ChangeState(new Stand());
		return;
	}
}

void AttackOmen1::UpdateStateClear(Enemy* enemy)
{
	return;
}

void AttackOmen1::UpdateAttack()
{
	//弾をセット
	if (objectTimer == 1.0f && nextAttack01)
	{
		//弾を出す位置を回転
		bulletAddPos = position + rollRotation(bulletAddPos, rotation);
		//弾をセット
		for (int i = 0; i < bulletVol; i++)
		{
			bullet->SetBullet(bulletAddPos, bulletScale, bulletLastScale, 0.0f,
				frameAttackOmen1 + bulletTimeLag * i, frameAttack1);
		}
	}
}

void AttackOmen1::Draw(ID3D12GraphicsCommandList* cmdList)
{
	objectAttackOmen1->Draw(cmdList);
}

void AttackOmen1::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	objectAttackOmen1->DrawLightView(cmdList);
}

void AttackOmen1::SetSRV(ID3D12DescriptorHeap* SRV)
{
	objectAttackOmen1->SetSRV(SRV);
}

void AttackOmen1::UpdateObject()
{
	objectAttackOmen1->SetPosition(position);
	objectAttackOmen1->SetRotation(rotation);
	objectAttackOmen1->SetScale(scale);
	objectAttackOmen1->Update();
}

void Dash::Initialize()
{
	//アニメーションの設定
	objectDash->StopAnimation();
	objectDash->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;
}

void Dash::Move()
{
	//プレイヤーにすでにヒットしている場合
	if (dashFlag == true)
	{
		//プレイヤーに近づく
		position = position + dashVec * dashSpeed;

		//敵がプレイヤーの向きを向くようにする
		rotation.y = getVectorRotation(dashVec).y;

		return;
	}
	//プレイヤーと敵のベクトル取得
	XMFLOAT3 velo = playerPos - position;

	velo = normalize(velo);

	//敵がプレイヤーの向きを向くようにする
	rotation.y = getVectorRotation(velo).y;

	//プレイヤーにまだヒットしてない場合
	if (dashFlag == false)
	{
		//プレイヤーに近づく
		position = position + velo * dashSpeed;
	}
}

void Dash::UpdateState(Enemy* enemy)
{
	//オブジェクトに衝突したら倒れるモーションへ
	if (hitObjectFlag == true)
	{
		enemy->ChangeState(new FallDown());
		return;
	}
}

void Dash::Draw(ID3D12GraphicsCommandList* cmdList)
{
	objectDash->Draw(cmdList);
}

void Dash::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	objectDash->DrawLightView(cmdList);
}

void Dash::SetSRV(ID3D12DescriptorHeap* SRV)
{
	objectDash->SetSRV(SRV);
}

void Dash::UpdateObject()
{
	if (hitPlayerFlag == true && dashFlag == false)
	{
		//プレイヤーと敵のベクトル取得
		dashVec = playerPos - position;
		dashVec = normalize(dashVec);

		dashFlag = true;
	}

	objectDash->SetPosition(position);
	objectDash->SetRotation(rotation);
	objectDash->SetScale(scale);
	objectDash->Update();
}

void Dash::UpdateHitWall(JSONLoader::ColliderData objectColliderData)
{
	//壁の中にいたら処理終了
	if (ColliderManager::CheckCollider(colliderData, objectColliderData,true) == true)return;

	//壁の外にいる時のみ
	while (ColliderManager::CheckCollider(colliderData, objectColliderData,true) == false)
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

void Dash::UpdateHitPiller(JSONLoader::ColliderData objectColliderData)
{
	//タイマー90フレーム以内は判定をとらない
	if (objectTimer < frameNoPillerHit)return;

	//柱に衝突してなかったら処理終了
	if(ColliderManager::CheckCollider(colliderData, objectColliderData) == false)return;

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

void CallMiniEnemy::Initialize()
{
	//アニメーションの設定
	objectCallMiniEnemy->StopAnimation();
	objectCallMiniEnemy->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;
}

void CallMiniEnemy::Move()
{
}

void CallMiniEnemy::UpdateState(Enemy* enemy)
{
}

void CallMiniEnemy::UpdateStateMovePhase(Enemy* enemy)
{
	//アニメーションが終わったら
	if (objectTimer >= frameCallMiniEnemy)
	{
		enemy->ChangeState(new AttackOmen1());
		return;
	}
}

void CallMiniEnemy::UpdateAttackMovePhase()
{
	//敵呼び出しフラグをもとに戻す
	callEnemyFlag = false;
	//敵呼び出し 2回呼び出す
	if (objectTimer == 40)
	{
		//フラグを立てる
		callEnemyFlag = true;
		//敵を呼び出す場所
		if (objectTimer == frameCallMiniEnemy2)callEnemyPos = callEnemyPos1;
	}

	//敵呼び出し 雷パーティクル
	if (objectTimer == frameCallMiniEnemy2)
	{
		elecParticle->AddParticle(elecFrame, callEnemyPos1 + addElecPos1,
			callEnemyPos1, elecStartSlace1, elecEndSlace1, 60.0f, elecStrength);
		explosionParticle1->Add(callEnemyPos1);
	}
	//敵呼び出し
	if (objectTimer <= frameCallMiniEnemy2)
	{
		if ((int)objectTimer % elecInterval == 0)
		{
			for (int i = 0; i < elecVol; i++)
			{
				elecParticle->AddParticle(3.0f, callEnemyPos1 + addElecPos2,
					callEnemyPos1, elecStartSlace2, elecEndSlace2, 15.0f, elecStrength);
			}
		}
	}
}

void CallMiniEnemy::Draw(ID3D12GraphicsCommandList* cmdList)
{
	objectCallMiniEnemy->Draw(cmdList);
}

void CallMiniEnemy::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	objectCallMiniEnemy->DrawLightView(cmdList);
}

void CallMiniEnemy::SetSRV(ID3D12DescriptorHeap* SRV)
{
	objectCallMiniEnemy->SetSRV(SRV);
}

void CallMiniEnemy::UpdateObject()
{
	objectCallMiniEnemy->SetPosition(position);
	objectCallMiniEnemy->SetRotation(rotation);
	objectCallMiniEnemy->SetScale(scale);
	objectCallMiniEnemy->Update();
}

void FallDown::Initialize()
{
	//アニメーションの設定
	objectFallDown->StopAnimation();
	objectFallDown->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;
}

void FallDown::Move()
{
}

void FallDown::UpdateState(Enemy* enemy)
{
	//時間が立ったら立ちあがるアニメーションへ
	if (objectTimer >= frameFallDownEnemy)
	{
		enemy->ChangeState(new GetUp());
		return;
	}
}

void FallDown::UpdateStateMovePhase(Enemy* enemy)
{
	//時間が立ったら立ちあがるアニメーションへ
	if (objectTimer >= frameFallDownEnemy)
	{
		enemy->ChangeState(new GetUp());
		return;
	}
}

void FallDown::Draw(ID3D12GraphicsCommandList* cmdList)
{
	objectFallDown->Draw(cmdList);
}

void FallDown::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	objectFallDown->DrawLightView(cmdList);
}

void FallDown::SetSRV(ID3D12DescriptorHeap* SRV)
{
	objectFallDown->SetSRV(SRV);
}

void FallDown::UpdateObject()
{
	objectFallDown->SetPosition(position);
	objectFallDown->SetRotation(rotation);
	objectFallDown->SetScale(scale);
	objectFallDown->Update();
}

void GetUp::Initialize()
{
	//アニメーションの設定
	objectGetUp->StopAnimation();
	objectGetUp->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;
}

void GetUp::Move()
{
}

void GetUp::UpdateState(Enemy* enemy)
{
	//立ち上がったら攻撃モーションへ
	if (objectTimer >= frameGetUpEnemy)
	{
		//次の攻撃を弾に設定
		nextAttack01 = true;
		enemy->ChangeState(new AttackOmen1());
		return;
	}
}

void GetUp::UpdateStateMovePhase(Enemy* enemy)
{
	//立ち上がったら敵呼び出しへ
	if (objectTimer >= frameGetUpEnemy)
	{
		//次の攻撃を弾に設定
		nextAttack01 = true;
		enemy->ChangeState(new CallMiniEnemy());
		return;
	}
}

void GetUp::Draw(ID3D12GraphicsCommandList* cmdList)
{
	objectGetUp->Draw(cmdList);
}

void GetUp::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	objectGetUp->DrawLightView(cmdList);
}

void GetUp::SetSRV(ID3D12DescriptorHeap* SRV)
{
	objectGetUp->SetSRV(SRV);
}

void GetUp::UpdateObject()
{
	objectGetUp->SetPosition(position);
	objectGetUp->SetRotation(rotation);
	objectGetUp->SetScale(scale);
	objectGetUp->Update();
}
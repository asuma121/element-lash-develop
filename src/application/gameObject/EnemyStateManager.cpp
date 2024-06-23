#include "EnemyStateManager.h"
#include "mathOriginal.h"
#include "ColliderManager.h"

void TitleAttackOmen1::InitializeState()
{
	//アニメーションの設定
	object->StopAnimation();
	object->SetModel(modelAttackOmen1);
	object->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;

	//体の当たり判定の処理
	hitBodyFlag = true;

	//高さの処理
	addPos = standAddPos;
}

void TitleAttackOmen1::Move()
{
	if (objectTimer == 1)
	{
		//プレイヤーと敵のベクトル取得
		XMFLOAT3 velo = playerPos - position;
	}
}

void TitleAttackOmen1::UpdateState(Enemy* enemy)
{
	//アニメーションを止める
	object->StopAnimation();
}

void TutorialStand::InitializeState()
{
	//アニメーションの設定
	object->StopAnimation();
	object->SetModel(modelStand);
	object->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;

	//体の当たり判定の処理
	hitBodyFlag = true;

	//高さの処理
	addPos = standAddPos;
}

void TutorialStand::Move()
{
	//敵登場のフェーズになったら
	if (tutorialTimer > 0)
	{
		position = tutorialPos;
	}
}

void TutorialStand::UpdateState(Enemy* enemy)
{
	//攻撃前兆のアニメーションも終わったら
	if (tutorialTimer > tutorialStandFrame + frameAttackOmen1)
	{
		return;
	}

	//しばらく立ってる
	if (tutorialTimer > tutorialStandFrame)
	{
		object->SetInterpolation(frameInterpolation);
		enemy->ChangeState(new TutorialAttackOmen1());
		return;
	}
}

void TutorialAttackOmen1::InitializeState()
{
	//アニメーションの設定
	object->StopAnimation();
	object->SetModel(modelAttackOmen1);
	object->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;

	//体の当たり判定の処理
	hitBodyFlag = true;

	//高さの処理
	addPos = standAddPos;
}

void TutorialAttackOmen1::Move()
{
}

void TutorialAttackOmen1::UpdateState(Enemy* enemy)
{
	//アニメーションが終わったら
	if (objectTimer >= frameAttackOmen1)
	{
		object->SetInterpolation(frameInterpolation);
		enemy->ChangeState(new TutorialStand());
		return;
	}
}

void MovePhaseAttackOmen1::InitializeState()
{
	//アニメーションの設定
	object->StopAnimation();
	object->SetModel(modelAttackOmen1);
	object->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;

	//体の当たり判定の処理
	hitBodyFlag = true;

	//高さの処理
	addPos = standAddPos;
}

void MovePhaseAttackOmen1::Move()
{
	if (objectTimer == 1)
	{
		//プレイヤーと敵のベクトル取得
		XMFLOAT3 velo = playerPos - position;

		//敵がプレイヤーの向きを向くようにする
		rotation.y = getVectorRotation(velo).y;
	}
}

void MovePhaseAttackOmen1::UpdateState(Enemy* enemy)
{
	// アニメーションが終わったら
	if (objectTimer >= frameAttackOmen1)
	{
		object->SetInterpolation(frameInterpolation);
		enemy->ChangeState(new Stand());
		return;
	}
}

void MovePhaseCallMiniEnemy::InitializeState()
{
	//アニメーションの設定
	object->StopAnimation();
	object->SetModel(modelAttack1);
	object->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;

	//体の当たり判定の処理
	hitBodyFlag = true;

	//高さの処理
	addPos = standAddPos;
}

void MovePhaseCallMiniEnemy::Move()
{
}

void MovePhaseCallMiniEnemy::UpdateState(Enemy* enemy)
{
	//アニメーションが終わったら
	if (objectTimer >= frameCallMiniEnemy)
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
		object->SetInterpolation(frameInterpolation);
		enemy->ChangeState(new MovePhaseAttackOmen1());
		return;
	}
}

void MovePhaseCallMiniEnemy::UpdateAttack()
{
	//敵呼び出しフラグをもとに戻す
	callEnemyFlag = false;
	//敵呼び出し 2回呼び出す
	if (objectTimer == frameCallMiniEnemy2)
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
			callEnemyPos1, elecStartSlace1, elecEndSlace1, 60, elecStrength);
		explosionParticle1->Add(callEnemyPos1);
	}
	//敵呼び出し
	if (objectTimer <= frameCallMiniEnemy2)
	{
		if ((int)objectTimer % elecInterval == 0)
		{
			for (int i = 0; i < elecVol; i++)
			{
				elecParticle->AddParticle(3, callEnemyPos1 + addElecPos2,
					callEnemyPos1, elecStartSlace2, elecEndSlace2, 15, elecStrength);
			}
		}
	}
}

void MovePhaseFallDown::InitializeState()
{
	//アニメーションの設定
	object->StopAnimation();
	object->SetModel(modelFallDown);
	object->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;

	//体の当たり判定の処理
	hitBodyFlag = false;

	//高さの処理
	addPos = standAddPos;
	//高さの加算の値の処理
	//角度の向きに回転
	XMFLOAT3 addPos1 = rollRotation(fallDownAddPos, rotation);
	addAddPos = (addPos1 - addPos) / (frameFallDownEnemy / 2.0f);
}

void MovePhaseFallDown::Move()
{
	if ((frameFallDownEnemy / 2.0f) > objectTimer)
	{
		addPos = addPos + addAddPos;
	}
}

void MovePhaseFallDown::UpdateState(Enemy* enemy)
{
	//時間が立ったら立ちあがるアニメーションへ
	if (objectTimer >= frameFallDownEnemy - 1)
	{
		object->SetInterpolation(frameInterpolation);
		enemy->ChangeState(new MovePhaseGetUp());
		return;
	}
}

void MovePhaseGetUp::InitializeState()
{
	//アニメーションの設定
	object->StopAnimation();
	object->SetModel(modelGetUp);
	object->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;

	//体の当たり判定の処理
	hitBodyFlag = true;

	//高さの加算の値の処理
	//角度の向きに回転
	XMFLOAT3 addPos1 = rollRotation(fallDownAddPos, rotation);
	addAddPos = (standAddPos - addPos1) / (frameGetUpEnemy / 2.0f);
}

void MovePhaseGetUp::Move()
{
	if ((frameGetUpEnemy / 2.0f) > objectTimer)
	{
		addPos = addPos + addAddPos;
	}
}

void MovePhaseGetUp::UpdateState(Enemy* enemy)
{
	//立ち上がったら敵呼び出しへ
	if (objectTimer >= frameGetUpEnemy)
	{
		//次の攻撃を弾に設定
		nextAttack01 = true;
		object->SetInterpolation(frameInterpolation);
		enemy->ChangeState(new MovePhaseCallMiniEnemy());
		return;
	}
}

void ClearAttackOmen1::InitializeState()
{
	//アニメーションの設定
	object->StopAnimation();
	object->SetModel(modelAttackOmen1);
	object->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;

	//体の当たり判定の処理
	hitBodyFlag = true;

	//高さの処理
	addPos = standAddPos;
}

void ClearAttackOmen1::Move()
{
	if (objectTimer == 1)
	{
		//プレイヤーと敵のベクトル取得
		XMFLOAT3 velo = playerPos - position;

		//敵がプレイヤーの向きを向くようにする
		rotation.y = getVectorRotation(velo).y;
	}
}

void ClearAttackOmen1::UpdateParticleClear()
{
	if (clearTimer == clearFromGameTime)
	{
		object->StopAnimation();
		object->SetTimer1(1000.0f);
	}
	return;
}

void ClearAttackOmen1::UpdateState(Enemy* enemy)
{
	//石化してたらリターン
	if (clearTimer >= clearFromGameTime)
	{
		return;
	}

	if ((int)clearTimer % (int)explosionTime == 0)
	{
		//乱数を生成
		float xRand, yRand, zRand, randWidth;
		XMFLOAT3 randVec(30.0f, 30.0f, 30.0f);
		randWidth = 90.0f;
		xRand = (GetRand(100.0f - randWidth, 100.0f + randWidth) - 100.0f) / 100.0f;
		yRand = (GetRand(100.0f - randWidth, 100.0f + randWidth) - 100.0f) / 100.0f;
		zRand = (GetRand(100.0f - randWidth, 100.0f + randWidth) - 100.0f) / 100.0f;
		randVec = XMFLOAT3(randVec.x * xRand, randVec.y * yRand + 50, randVec.z * zRand);

		explosionParticle1->Add(position + randVec);
		explosionParticle2->Add(position + randVec);
	}
}

void Stand::InitializeState()
{
	//アニメーションの設定
	object->StopAnimation();
	object->SetModel(modelStand);
	object->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;

	//体の当たり判定の処理
	hitBodyFlag = true;

	//高さの処理
	addPos = standAddPos;
}

void Stand::Move()
{
}

void Stand::UpdateState(Enemy* enemy)
{
}

void Walk::InitializeState()
{
	//アニメーションの設定
	object->StopAnimation();
	object->SetModel(modelWalk);
	object->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;

	//体の当たり判定の処理
	hitBodyFlag = true;

	//高さの処理
	addPos = standAddPos;
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

void Attack01::InitializeState()
{
	//アニメーションの設定
	object->StopAnimation();
	object->SetModel(modelAttack1);
	object->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;

	//体の当たり判定の処理
	hitBodyFlag = true;

	//高さの処理
	addPos = standAddPos;
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
		object->SetInterpolation(frameInterpolation);
		enemy->ChangeState(new AttackOmen1());
		return;
	}
}

void AttackOmen1::InitializeState()
{
	//アニメーションの設定
	object->StopAnimation();
	object->SetModel(modelAttackOmen1);
	object->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;

	//体の当たり判定の処理
	hitBodyFlag = true;

	//高さの処理
	addPos = standAddPos;
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
			object->SetInterpolation(frameInterpolation);
			enemy->ChangeState(new CallMiniEnemy());
			return;
		}
		//次の行動がダッシュの時
		if (nextDash)
		{
			nextDash = false;
			object->SetInterpolation(frameInterpolation);
			enemy->ChangeState(new Dash());
			return;
		}
		//次の行動が敵呼び出しの時
		if (nextAttack01)
		{
			nextAttack01 = false;
			object->SetInterpolation(frameInterpolation);
			enemy->ChangeState(new Attack01());
			return;
		}
	}
}

void AttackOmen1::UpdateAttack()
{
	if (nextAttack01 == true)
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
}

void Dash::InitializeState()
{
	//アニメーションの設定
	object->StopAnimation();
	object->SetModel(modelDash);
	object->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;

	//体の当たり判定の処理
	hitBodyFlag = true;

	//高さの処理
	addPos = standAddPos;
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

	if (hitPlayerFlag == true && dashFlag == false)
	{
		//プレイヤーと敵のベクトル取得
		dashVec = playerPos - position;
		dashVec = normalize(dashVec);

		dashFlag = true;
	}
}

void Dash::UpdateState(Enemy* enemy)
{
	//オブジェクトに衝突したら倒れるモーションへ
	if (hitObjectFlag == true)
	{
		object->SetInterpolation(frameInterpolation);
		enemy->ChangeState(new FallDown());
		return;
	}
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

void Dash::UpdateHitPiller(JSONLoader::ColliderData objectColliderData, int pillerNum)
{
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
	if (hitPillerFlag == true && pillerNum != hitPillerNum)hitObjectFlag = true;
	else if(hitPillerFlag == false)hitObjectFlag = true;

	//まだそのシーンで柱に衝突していなかったらフラグを戻す
	if (hitPillerFlag == false)hitPillerFlag = true;
	//最後に当たった柱の番号を残す
	hitPillerNum = pillerNum;
}

void CallMiniEnemy::InitializeState()
{
	//アニメーションの設定
	object->StopAnimation();
	object->SetModel(modelAttack1);
	object->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;

	//体の当たり判定の処理
	hitBodyFlag = true;

	//高さの処理
	addPos = standAddPos;
}

void CallMiniEnemy::Move()
{
}

void CallMiniEnemy::UpdateState(Enemy* enemy)
{
	//アニメーションが終わったら
	if (objectTimer >= frameCallMiniEnemy)
	{
		object->SetInterpolation(frameInterpolation);
		enemy->ChangeState(new AttackOmen1());
		return;
	}
}

void CallMiniEnemy::UpdateAttack()
{
	//敵呼び出しフラグをもとに戻す
	callEnemyFlag = false;
	if (objectTimer == 1)
	{
		callEnemyPos = (playerPos - position) / 2;
	}
	//敵呼び出し 2回呼び出す
	if (objectTimer == frameCallMiniEnemy2)
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
			callEnemyPos1, elecStartSlace1, elecEndSlace1, 60, elecStrength);
		explosionParticle1->Add(callEnemyPos1);
	}
	//敵呼び出し
	if (objectTimer <= frameCallMiniEnemy2)
	{
		if ((int)objectTimer % elecInterval == 0)
		{
			for (int i = 0; i < elecVol; i++)
			{
				elecParticle->AddParticle(3, callEnemyPos1 + addElecPos2,
					callEnemyPos1, elecStartSlace2, elecEndSlace2, 15, elecStrength);
			}
		}
	}
}

void FallDown::InitializeState()
{
	//アニメーションの設定
	object->StopAnimation();
	object->SetModel(modelFallDown);
	object->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;

	//体の当たり判定の処理
	hitBodyFlag = false;

	//高さの処理
	addPos = standAddPos;
	//高さの加算の値の処理
	//角度の向きに回転
	XMFLOAT3 addPos1 = rollRotation(fallDownAddPos, rotation);
	addAddPos = (addPos1 - addPos) / (frameFallDownEnemy / 2.0f);
}

void FallDown::Move()
{
	if ((frameFallDownEnemy / 2.0f) > objectTimer)
	{
		addPos = addPos + addAddPos;
	}
}

void FallDown::UpdateState(Enemy* enemy)
{
	//倒れている間アニメーションをストップ
	if (objectTimer >= frameFallDownEnemy - 1.0f)
	{
		object->StopAnimation();
	}

	//時間が立ったら立ちあがるアニメーションへ
	if (objectTimer >= frameFallDownEnemy + downAddFrame)
	{
		object->SetInterpolation(frameInterpolation);
		enemy->ChangeState(new GetUp());
		return;
	}
}

void FallDown::UpdateColliderDate()
{
	colliderData.scale = fallDownColliderScale;
	colliderData.rotation = rotation;
	//角度の向きに回転
	XMFLOAT3 addPosition = rollRotation(fallDownCollderAddPos, rotation);
	colliderData.center = position + addPosition;
}

void GetUp::InitializeState()
{
	//アニメーションの設定
	object->StopAnimation();
	object->SetModel(modelGetUp);
	object->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;

	//体の当たり判定の処理
	hitBodyFlag = true;

	//高さの加算の値の処理
	//角度の向きに回転
	XMFLOAT3 addPos1 = rollRotation(fallDownAddPos, rotation);
	addAddPos = (standAddPos - addPos1) / (frameGetUpEnemy / 2.0f);
}

void GetUp::Move()
{
	if ((frameGetUpEnemy / 2.0f) > objectTimer)
	{
		addPos = addPos + addAddPos;
	}
}

void GetUp::UpdateState(Enemy* enemy)
{
	//立ち上がったら攻撃モーションへ
	if (objectTimer >= frameGetUpEnemy)
	{
		//次の攻撃を弾に設定
		nextAttack01 = true;
		object->SetInterpolation(frameInterpolation);
		enemy->ChangeState(new AttackOmen1());
		return;
	}
}


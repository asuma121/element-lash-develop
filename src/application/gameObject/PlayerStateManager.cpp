#include "PlayerStateManager.h"
#include "mathOriginal.h"

void Wait::Initialize()
{
	//アニメーションの設定
	object->StopAnimation();
	object->SetModel(modelWait);
	object->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;
}

void Wait::UpdateState(Player* player)
{
	//ヒットフラグが立っていたら	被ダメージモーションへ
	if (hitTimer <= frameDown && invincibleFlag == true) 
	{
		player->ChangeState(new Down());
		return;
	} 

	//炎状態でRボタンを押していたら攻撃3へ
	if (keyManager->PushKey(KeyManager::PAD_RIGHT_SHOULDER) == 1 && form == Player::Fire)
	{
		player->ChangeState(new Attack3());
		return;
	} 

	//Rボタンで攻撃1
	else if (form == Player::Elec && keyManager->TriggerKey(KeyManager::PAD_RIGHT_SHOULDER) == 1)
	{
		player->ChangeState(new Attack1());
		return;
	}
	//立ち止まっている場合
	else if (length(posVelocity) <= 0.01f)
	{
		return;
	}
	//普通に走っている場合
	else
	{
		player->ChangeState(new Run());
		return;
	}
}

void Run::Initialize()
{
	//アニメーションの設定
	object->StopAnimation();
	object->SetModel(modelRun);
	object->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;
}

void Run::UpdateState(Player* player)
{
	//ヒットフラグが立っていたら	被ダメージモーションへ
	if (hitTimer <= frameDown && invincibleFlag == true)
	{
		player->ChangeState(new Down());
		return;
	}

	//炎状態でRボタンを押していたら攻撃3へ
	if (keyManager->PushKey(KeyManager::PAD_RIGHT_SHOULDER) == 1 && form == Player::Fire)
	{
		player->ChangeState(new Attack3());
		return;
	}

	//Rボタンで攻撃1
	else if (form == Player::Elec && keyManager->TriggerKey(KeyManager::PAD_RIGHT_SHOULDER))
	{
		player->ChangeState(new Attack1());
		return;
	}
	//立ち止まっている場合
	else if (length(posVelocity) <= 0.01f)
	{
		player->ChangeState(new Wait());
		return;
	}
	//普通に走っている場合
	else
	{
		return;
	}
}

void Run::MoveTitle(float timer)
{
	//シーン遷移が始まってない場面
	//通常のタイトルシーン
	if (timer == 0)
	{
		//角度ベクトル調整
		rotVelocity.y = 0.01f;
		//角度ベクトルを加算
		rotation0 = rotation0 + rotVelocity;

		//座標加算
		posVelocity.x = 0.9;
		posVelocity.z = -0.1;
	}

	//シーン遷移タイマーが始動したら
	if (timer > 0)
	{
		if (timer == 1)
		{
			//最初に加算する角度を取得
			addRot = rotation0.y - (float)PI / 2.0f; 
			originalRot = rotation0.y;
			//ベクトルを固定
			posVelocity.x = 0.0;
			posVelocity.z = 0.0;
		}
		//角度加算 プレイヤーが背を向けるように
		if (timer < 120)
		{
			rotation0.y = (originalRot - addRot) * easeOutCirc(timer / 120.0f);
		}
		if (timer > 120)
		{
			posVelocity.x = 0.0;
			posVelocity.z += 3.0;
		}
	}

	//進行ベクトルを回転
	posVelocity = rollRotation(posVelocity, rotation0);
	//進行ベクトルを加算
	position = position + posVelocity;
}

void Attack1::Initialize()
{
	//アニメーションの設定
	object->StopAnimation();
	object->SetModel(modelAttack1);
	object->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;
}

void Attack1::UpdateState(Player* player)
{
	//ヒットフラグが立っていたら	被ダメージモーションへ
	if (hitTimer <= frameDown && invincibleFlag == true)
	{
		player->ChangeState(new Down());
		return;
	}

	//インターバル中にRボタンで連続攻撃 攻撃2へ
	if (keyManager->TriggerKey(KeyManager::PAD_RIGHT_SHOULDER) && 0 <=
		attack1Time - objectTimer && attack1Time - objectTimer <= AttackIntervalTime)
	{
		player->ChangeState(new Attack2());
		return;
	}
	//攻撃が終わって立ち止まっている場合
	else if (objectTimer >= attack1Time && length(posVelocity) <= 0.01f)
	{
		player->ChangeState(new Wait());
		return;
	}
	//攻撃が終わって普通に走っている場合
	else if(objectTimer >= attack1Time)
	{
		player->ChangeState(new Run());
		return;
	}
}

void Attack1::UpdateAttack()
{
	//ロックオンの更新を止める
	elecAttackFlag = true;
	//40フレームでヒットフラグを立てる(手を振ってる位のタイミング)
	if (objectTimer == elecFlame && lockOnFlag == true)
	{
		hitElecFlag = true;
	}

	//雷を出す場所を調整
	if (objectTimer == 2)
	{
		addElecPos2 = rollRotation(XMFLOAT3(addElecPos1.x, addElecPos1.y, addElecPos1.z), rotation1);
	}
	elecParticle2->Add(position + addElecPos2);
	//40フレーム(手を振ってる位のタイミングで太い1本の雷)
	if (objectTimer == elecFlame)
	{
		elecParticle1->AddParticle(attack1Time - elecFlame, position + addElecPos2,
			lockOnPos, elecStartSlace1, elecEndSlace1, 10.0f, elecStrength);
	}
	if (objectTimer > elecFlame && (int)objectTimer % elecInterval == 0)
	{
		for (int i = 0; i < elecVol; i++)
		{
			elecParticle1->AddParticle(20.0f, position + addElecPos2,
				lockOnPos, elecStartSlace2, elecEndSlace2, 20.0f, elecStrength);
		}
	}
}

void Attack1::Move()
{
	//プレイヤーの元になる角度
	//AROWキーで角度変更
	rotVelocity.y = keyManager->GetStick(KeyManager::RStickX) * rot0Speed;
	//角度ベクトルを加算
	rotation0 = rotation0 + rotVelocity;

	//プレイヤー→敵のベクトル取得して角度取得
	XMFLOAT3 rot = getVectorRotation(lockOnPos - position);
	//モデルを敵の方に向かせる
	rotation1 = XMFLOAT3(rot.x, 0.0f, rot.z);

	return;
}

void Attack2::Initialize()
{
	//アニメーションの設定
	object->StopAnimation();
	object->SetModel(modelAttack2);
	object->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;
	objectTime = attack2Time;
}

void Attack2::UpdateState(Player* player)
{
	//ヒットフラグが立っていたら	被ダメージモーションへ
	if (hitTimer <= frameDown && invincibleFlag == true)
	{
		player->ChangeState(new Down());
		return;
	}
	//攻撃が終わって立ち止まっている場合
	else if (objectTimer >= attack2Time && length(posVelocity) <= 0.01f)
	{
		player->ChangeState(new Wait());
		return;
	}
	//攻撃が終わって普通に走っている場合
	else if (objectTimer >= attack2Time)
	{
		player->ChangeState(new Run());
		return;
	}
}


void Attack2::UpdateAttack()
{
	//ロックオンの更新を止める
	elecAttackFlag = true;
	//40フレームでヒットフラグを立てる(手を振ってる位のタイミング)
	if (objectTimer == elecFlame && lockOnFlag == true)
	{
		hitElecFlag = true;
	}

	//雷を出す場所を調整
	if (objectTimer == 2)
	{
		addElecPos2 = rollRotation(XMFLOAT3(addElecPos1.x, addElecPos1.y, addElecPos1.z), rotation1);
	}
	elecParticle2->Add(position + addElecPos2);
	//40フレーム(手を振ってる位のタイミングで太い1本の雷)
	if (objectTimer == elecFlame)
	{
		elecParticle1->AddParticle(attack2Time - elecFlame, position + addElecPos2,
			lockOnPos, elecStartSlace1, elecEndSlace1, 10.0f, elecStrength);
	}
	if (objectTimer > elecFlame && (int)objectTimer % elecInterval == 0)
	{
		for (int i = 0; i < elecVol; i++)
		{
			elecParticle1->AddParticle(20.0f, position + addElecPos2,
				lockOnPos, elecStartSlace2, elecEndSlace2, 20.0f, elecStrength);
		}
	}
}

void Attack2::Move()
{
	//プレイヤーの元になる角度
	//AROWキーで角度変更
	rotVelocity.y = keyManager->GetStick(KeyManager::RStickX) * rot0Speed;
	//角度ベクトルを加算
	rotation0 = rotation0 + rotVelocity;
	
	//プレイヤー→敵のベクトル取得して角度取得
	XMFLOAT3 rot = getVectorRotation(lockOnPos - position);
	//モデルを敵の方に向かせる
	rotation1 = XMFLOAT3(rot.x, 0.0f, rot.z);

	return;
}

void Attack3::Initialize()
{
	//アニメーションの設定
	object->StopAnimation();
	object->SetModel(modelAttack3);
	object->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;
}

void Attack3::UpdateState(Player* player)
{
	//ヒットフラグが立っていたら	被ダメージモーションへ
	if (hitTimer <= frameDown && invincibleFlag == true)
	{
		player->ChangeState(new Down());
		return;
	}

	//立ち止まっている場合
	else if (keyManager->PushKey(KeyManager::PAD_RIGHT_SHOULDER) != 1 && length(posVelocity) <= 0.01f)
	{
		player->ChangeState(new Wait());
		return;
	}
	//普通に走っている場合
	else if(keyManager->PushKey(KeyManager::PAD_RIGHT_SHOULDER) != 1)
	{
		player->ChangeState(new Run());
	}
}

void Attack3::UpdateAttack()
{
	//弾追加
	if (objectTimer % bullet1Interval == 0.0f)
	{
		XMFLOAT3 velo = rollRotation(XMFLOAT3(0.0f, 0.0f, 1.0f), rotation0);
		float rand1 = GetRand(0.9f, 1.1f);
		float rand2 = GetRand(0.9f, 1.1f);
		float rand3 = GetRand(-0.1f, 0.1f);
		float rand4 = GetRand(0.9f, 1.1f);
		velo = normalize(velo) * (bullet1Speed * rand1);
		velo.x = velo.x * rand2;
		velo.y = velo.y + rand3;
		velo.z = velo.z * rand4;
		bullet->SetBullet(position + bullet1AddPosition, velo, 0.0f, bullet1Frame);
	}
}

void Attack3::Move()
{
	//プレイヤーの元になる角度
	//AROWキーで角度変更
	rotVelocity.y = keyManager->GetStick(KeyManager::RStickX) * rot0Speed;
	//角度ベクトルを加算
	rotation0 = rotation0 + rotVelocity;

	rotation1 = XMFLOAT3(0.0f, 0.0f, 0.0f);

	//座標
	//左スティックで移動
	XMFLOAT2 stick = normalize(keyManager->GetStick(KeyManager::LStickX), keyManager->GetStick(KeyManager::LStickY));
	posVelocity.x = stick.x * attack3PosSpeed;
	posVelocity.z = stick.y * attack3PosSpeed;
	//進行ベクトルを回転
	posVelocity = rollRotation(posVelocity, rotation0);
	//進行ベクトルを加算
	position = position + posVelocity;
}

void Down::Initialize()
{
	//アニメーションの設定
	object->StopAnimation();
	object->SetModel(modelDown);
	object->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;
}

void Down::UpdateState(Player* player)
{
	//ゲームオーバー自
	if (HP <= 0)
	{
		if (objectTimer == frameDown - 3)
		{
			object->StopAnimation();
		}
		return;
	}

	//ヒットフラグが戻ったら
	if (objectTimer >= frameDown)
	{
		player->ChangeState(new Wait());
		return;
	}
}

void Down::Move()
{
	//プレイヤーの元になる角度
	//AROWキーで角度変更
	rotVelocity.y = keyManager->GetStick(KeyManager::RStickX) * rot0Speed;
	//角度ベクトルを加算
	rotation0 = rotation0 + rotVelocity;
}

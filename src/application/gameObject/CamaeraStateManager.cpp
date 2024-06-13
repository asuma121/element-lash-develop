#include "CamaeraStateManager.h"

void FollowPlayer::UpdateCollider()
{
	//コライダーデータの更新
	colliderData.center = eye_;

	for (int i = 0; i < objectColliderData.size(); i++)
	{
		//壁との当たり判定処理
		if (objectColliderData[i].objectName.substr(0, 11) == "wall_camera")
		{
			UpdateHitWall(objectColliderData[i]);
		}
	}
}

void FollowPlayer::Move()
{
	target_ = { playerPos.x,10.0f,playerPos.z };

	//1フレームあたりの移動量
	float rot = ((float)PI / 200.0f) * (-keyManager->GetStick(KeyManager::RStickY));

	//視点座標を変更
	if (DebugChangeRot2 < maxDebugChangeRot2 && DebugChangeRot2 > minDebugChangeRot2)
	{
		DebugChangeRot2 += (float)rot;
	}
	if (DebugChangeRot2 > maxDebugChangeRot2)DebugChangeRot2 = maxDebugChangeRot2 - 0.001f;
	if (DebugChangeRot2 < minDebugChangeRot2)DebugChangeRot2 = minDebugChangeRot2 + 0.001f;

	eye_.x = playerPos.x + (cos(-playerRot.y - ((float)PI / 2)) * playerTargetDistance);
	eye_.y = playerPos.y + (cos(-playerRot.x + DebugChangeRot2) * playerTargetDistance);
	eye_.z = playerPos.z + (sin(-playerRot.y - ((float)PI / 2)) * playerTargetDistance);
}

void Title::Move()
{
	float distance = 60.0f;
	//シーン遷移タイマーが動いていない時
	if (phaseTimer < 119)
	{
		eye_.x = playerPos.x + (cos(-playerRot.y - ((float)PI / 2)) * distance);
		eye_.y = playerPos.y + (cos(-playerRot.x + ((float)PI * 15 / 40)) * distance);
		eye_.z = playerPos.z + (sin(-playerRot.y + ((float)PI / 2)) * distance);
		originalPlayerPos = playerPos;
		originalPlayerRot = playerRot;
		target_ = { playerPos.x,5.0f,playerPos.z };
	}
	//シーン遷移タイマーが動いているとき
	if (phaseTimer > 120)
	{
		eye_.x = originalPlayerPos.x + (cos(-originalPlayerRot.y - ((float)PI / 2)) * distance);
		eye_.y = originalPlayerPos.y + (cos(-originalPlayerRot.x + ((float)PI * 15 / 40)) * distance);
		eye_.z = originalPlayerPos.z + (sin(-originalPlayerRot.y + ((float)PI / 2)) * distance);
		target_ = { originalPlayerPos.x,5.0f,originalPlayerPos.z };
	}
}

void Tutorial::Move()
{
	int n = 60;
	if (phaseTimer < n)
	{
		eye_.x = -10.0f + (n - phaseTimer) * 2.0f;
	}
	eye_.y = 85.0f;
	eye_.z = 80.0f;

	if (phaseTimer < n)
	{
		target_ = { (n - phaseTimer) * 2.0f,65.0f,0.0f };
	}
}

void MovePhase1::Move()
{
	eye_ = movePhaseEye;
	target_ = movePhaseTarget;
}

void Clear::Move()
{
	target_ = clearAddPos;

	float addRot = (float)PI / 640.0f * phaseTimer;

	eye_.x = enemyPos.x + (-addRot * playerTargetDistance);
	eye_.y = enemyPos.y + (+((float)PI * 15 / 40) * playerTargetDistance);
	eye_.z = enemyPos.z + (-((float)PI / 2) * playerTargetDistance);
}

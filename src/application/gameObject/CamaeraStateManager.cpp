#include "CamaeraStateManager.h"
#include "mathOriginal.h"

void FollowPlayer::UpdateCollider()
{
	//�R���C�_�[�f�[�^�̍X�V
	colliderData.center = eye_;

	for (int i = 0; i < objectColliderData.size(); i++)
	{
		//�ǂƂ̓����蔻�菈��
		if (objectColliderData[i].objectName.substr(0, 11) == "wall_camera")
		{
			UpdateHitWall(objectColliderData[i]);
		}
	}
}

void FollowPlayer::Move()
{
	target_ = { playerPos.x,10.0f,playerPos.z };

	//1�t���[��������̈ړ���
	float rot = ((float)PI / 200.0f) * (-keyManager->GetStick(KeyManager::RStickY));

	//���_���W��ύX
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
	eye_ = playerPos + addTitleEye;

	target_ = enemyPos + addTitleTarget;
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

Develop::Develop()
{
	//���_�A�����_�������ʒu��
	eye_ = startPos;
	target_ = startTarget;
}

void Develop::Move()
{
	//���_���W��ύX
	if (keyManager->PushKeyboard(DIK_LEFT))
	{
		DebugChangeRot -= (float)addRot;
	}
	if (keyManager->PushKeyboard(DIK_RIGHT))
	{
		DebugChangeRot += (float)addRot;
	}
	if (keyManager->PushKeyboard(DIK_UP))
	{
		DebugChangeRot2 -= (float)addRot;
	}
	if (keyManager->PushKeyboard(DIK_DOWN))
	{
		DebugChangeRot2 += (float)addRot;
	}

	//�^�[�Q�b�g�܂ł̋�����ύX
	if (keyManager->PushKeyboard(DIK_O))
	{
		DebugTargetDistance -= 0.2f;
	}
	if (keyManager->PushKeyboard(DIK_P))
	{
		DebugTargetDistance += 0.2f;
	}

	//�^�[�Q�b�g��ύX
	if (keyManager->PushKeyboard(DIK_A))
	{
		target_.x -= addTarget;
	}
	if (keyManager->PushKeyboard(DIK_D))
	{
		target_.x += addTarget;
	}
	if (keyManager->PushKeyboard(DIK_W))
	{
		target_.y -= addTarget;
	}
	if (keyManager->PushKeyboard(DIK_S))
	{
		target_.y += addTarget;
	}

	//���_���W�ɑ��
	eye_.x = sin(DebugChangeRot) * DebugTargetDistance + target_.x;
	eye_.y = sin(DebugChangeRot2) * DebugTargetDistance + target_.y;
	eye_.z = cos(DebugChangeRot) * DebugTargetDistance + target_.z;
}

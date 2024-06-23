#include "EnemyStateManager.h"
#include "mathOriginal.h"
#include "ColliderManager.h"

void TitleAttackOmen1::InitializeState()
{
	//�A�j���[�V�����̐ݒ�
	object->StopAnimation();
	object->SetModel(modelAttackOmen1);
	object->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;

	//�̂̓����蔻��̏���
	hitBodyFlag = true;

	//�����̏���
	addPos = standAddPos;
}

void TitleAttackOmen1::Move()
{
	if (objectTimer == 1)
	{
		//�v���C���[�ƓG�̃x�N�g���擾
		XMFLOAT3 velo = playerPos - position;
	}
}

void TitleAttackOmen1::UpdateState(Enemy* enemy)
{
	//�A�j���[�V�������~�߂�
	object->StopAnimation();
}

void TutorialStand::InitializeState()
{
	//�A�j���[�V�����̐ݒ�
	object->StopAnimation();
	object->SetModel(modelStand);
	object->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;

	//�̂̓����蔻��̏���
	hitBodyFlag = true;

	//�����̏���
	addPos = standAddPos;
}

void TutorialStand::Move()
{
	//�G�o��̃t�F�[�Y�ɂȂ�����
	if (tutorialTimer > 0)
	{
		position = tutorialPos;
	}
}

void TutorialStand::UpdateState(Enemy* enemy)
{
	//�U���O���̃A�j���[�V�������I�������
	if (tutorialTimer > tutorialStandFrame + frameAttackOmen1)
	{
		return;
	}

	//���΂炭�����Ă�
	if (tutorialTimer > tutorialStandFrame)
	{
		object->SetInterpolation(frameInterpolation);
		enemy->ChangeState(new TutorialAttackOmen1());
		return;
	}
}

void TutorialAttackOmen1::InitializeState()
{
	//�A�j���[�V�����̐ݒ�
	object->StopAnimation();
	object->SetModel(modelAttackOmen1);
	object->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;

	//�̂̓����蔻��̏���
	hitBodyFlag = true;

	//�����̏���
	addPos = standAddPos;
}

void TutorialAttackOmen1::Move()
{
}

void TutorialAttackOmen1::UpdateState(Enemy* enemy)
{
	//�A�j���[�V�������I�������
	if (objectTimer >= frameAttackOmen1)
	{
		object->SetInterpolation(frameInterpolation);
		enemy->ChangeState(new TutorialStand());
		return;
	}
}

void MovePhaseAttackOmen1::InitializeState()
{
	//�A�j���[�V�����̐ݒ�
	object->StopAnimation();
	object->SetModel(modelAttackOmen1);
	object->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;

	//�̂̓����蔻��̏���
	hitBodyFlag = true;

	//�����̏���
	addPos = standAddPos;
}

void MovePhaseAttackOmen1::Move()
{
	if (objectTimer == 1)
	{
		//�v���C���[�ƓG�̃x�N�g���擾
		XMFLOAT3 velo = playerPos - position;

		//�G���v���C���[�̌����������悤�ɂ���
		rotation.y = getVectorRotation(velo).y;
	}
}

void MovePhaseAttackOmen1::UpdateState(Enemy* enemy)
{
	// �A�j���[�V�������I�������
	if (objectTimer >= frameAttackOmen1)
	{
		object->SetInterpolation(frameInterpolation);
		enemy->ChangeState(new Stand());
		return;
	}
}

void MovePhaseCallMiniEnemy::InitializeState()
{
	//�A�j���[�V�����̐ݒ�
	object->StopAnimation();
	object->SetModel(modelAttack1);
	object->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;

	//�̂̓����蔻��̏���
	hitBodyFlag = true;

	//�����̏���
	addPos = standAddPos;
}

void MovePhaseCallMiniEnemy::Move()
{
}

void MovePhaseCallMiniEnemy::UpdateState(Enemy* enemy)
{
	//�A�j���[�V�������I�������
	if (objectTimer >= frameCallMiniEnemy)
	{
		//�v���C���[�Ƃ̋������߂��ꍇ������x�e
		if (dashLength >= length(playerPos - position))
		{
			nextAttack01 = true;
		}
		//�v���C���[�Ƃ̋����������ꍇ�_�b�V��
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
	//�G�Ăяo���t���O�����Ƃɖ߂�
	callEnemyFlag = false;
	//�G�Ăяo�� 2��Ăяo��
	if (objectTimer == frameCallMiniEnemy2)
	{
		//�t���O�𗧂Ă�
		callEnemyFlag = true;
		//�G���Ăяo���ꏊ
		if (objectTimer == frameCallMiniEnemy2)callEnemyPos = callEnemyPos1;
	}

	//�G�Ăяo�� ���p�[�e�B�N��
	if (objectTimer == frameCallMiniEnemy2)
	{
		elecParticle->AddParticle(elecFrame, callEnemyPos1 + addElecPos1,
			callEnemyPos1, elecStartSlace1, elecEndSlace1, 60, elecStrength);
		explosionParticle1->Add(callEnemyPos1);
	}
	//�G�Ăяo��
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
	//�A�j���[�V�����̐ݒ�
	object->StopAnimation();
	object->SetModel(modelFallDown);
	object->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;

	//�̂̓����蔻��̏���
	hitBodyFlag = false;

	//�����̏���
	addPos = standAddPos;
	//�����̉��Z�̒l�̏���
	//�p�x�̌����ɉ�]
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
	//���Ԃ��������痧��������A�j���[�V������
	if (objectTimer >= frameFallDownEnemy - 1)
	{
		object->SetInterpolation(frameInterpolation);
		enemy->ChangeState(new MovePhaseGetUp());
		return;
	}
}

void MovePhaseGetUp::InitializeState()
{
	//�A�j���[�V�����̐ݒ�
	object->StopAnimation();
	object->SetModel(modelGetUp);
	object->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;

	//�̂̓����蔻��̏���
	hitBodyFlag = true;

	//�����̉��Z�̒l�̏���
	//�p�x�̌����ɉ�]
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
	//�����オ������G�Ăяo����
	if (objectTimer >= frameGetUpEnemy)
	{
		//���̍U����e�ɐݒ�
		nextAttack01 = true;
		object->SetInterpolation(frameInterpolation);
		enemy->ChangeState(new MovePhaseCallMiniEnemy());
		return;
	}
}

void ClearAttackOmen1::InitializeState()
{
	//�A�j���[�V�����̐ݒ�
	object->StopAnimation();
	object->SetModel(modelAttackOmen1);
	object->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;

	//�̂̓����蔻��̏���
	hitBodyFlag = true;

	//�����̏���
	addPos = standAddPos;
}

void ClearAttackOmen1::Move()
{
	if (objectTimer == 1)
	{
		//�v���C���[�ƓG�̃x�N�g���擾
		XMFLOAT3 velo = playerPos - position;

		//�G���v���C���[�̌����������悤�ɂ���
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
	//�Ή����Ă��烊�^�[��
	if (clearTimer >= clearFromGameTime)
	{
		return;
	}

	if ((int)clearTimer % (int)explosionTime == 0)
	{
		//�����𐶐�
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
	//�A�j���[�V�����̐ݒ�
	object->StopAnimation();
	object->SetModel(modelStand);
	object->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;

	//�̂̓����蔻��̏���
	hitBodyFlag = true;

	//�����̏���
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
	//�A�j���[�V�����̐ݒ�
	object->StopAnimation();
	object->SetModel(modelWalk);
	object->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;

	//�̂̓����蔻��̏���
	hitBodyFlag = true;

	//�����̏���
	addPos = standAddPos;
}

void Walk::Move()
{
	//�v���C���[�ƓG�̃x�N�g���擾
	XMFLOAT3 velo = playerPos - position;
	//�G���v���C���[�̌����������悤�ɂ���
	rotation.y = getVectorRotation(velo).y;

	//�v���C���[�ɋ߂Â�
	position = position + normalize(velo) * walkSpeed;
}

void Walk::UpdateState(Enemy* enemy)
{
}

void Attack01::InitializeState()
{
	//�A�j���[�V�����̐ݒ�
	object->StopAnimation();
	object->SetModel(modelAttack1);
	object->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;

	//�̂̓����蔻��̏���
	hitBodyFlag = true;

	//�����̏���
	addPos = standAddPos;
}

void Attack01::Move()
{
}

void Attack01::UpdateState(Enemy* enemy)
{
	//�e��ł��I������U���O����
	if (objectTimer >= frameAttack1)
	{
		//�v���C���[�Ƃ̋������߂��ꍇ������x�e
		if (dashLength >= length(playerPos - position))
		{
			nextAttack01 = true;
		}
		//�v���C���[�Ƃ̋����������ꍇ�_�b�V��
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
	//�A�j���[�V�����̐ݒ�
	object->StopAnimation();
	object->SetModel(modelAttackOmen1);
	object->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;

	//�̂̓����蔻��̏���
	hitBodyFlag = true;

	//�����̏���
	addPos = standAddPos;
}

void AttackOmen1::Move()
{
	if (objectTimer == 1)
	{
		//�v���C���[�ƓG�̃x�N�g���擾
		XMFLOAT3 velo = playerPos - position;

		//�G���v���C���[�̌����������悤�ɂ���
		rotation.y = getVectorRotation(velo).y;
	}
}

void AttackOmen1::UpdateState(Enemy* enemy)
{
	//�A�j���[�V�������I�������
	if (objectTimer >= frameAttackOmen1)
	{
		//���̍s�����G�Ăяo���̎�
		if (nextCallMiniEnemy)
		{
			nextCallMiniEnemy = false;
			object->SetInterpolation(frameInterpolation);
			enemy->ChangeState(new CallMiniEnemy());
			return;
		}
		//���̍s�����_�b�V���̎�
		if (nextDash)
		{
			nextDash = false;
			object->SetInterpolation(frameInterpolation);
			enemy->ChangeState(new Dash());
			return;
		}
		//���̍s�����G�Ăяo���̎�
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
		//�e���Z�b�g
		if (objectTimer == 1.0f && nextAttack01)
		{
			//�e���o���ʒu����]
			bulletAddPos = position + rollRotation(bulletAddPos, rotation);
			//�e���Z�b�g
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
	//�A�j���[�V�����̐ݒ�
	object->StopAnimation();
	object->SetModel(modelDash);
	object->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;

	//�̂̓����蔻��̏���
	hitBodyFlag = true;

	//�����̏���
	addPos = standAddPos;
}

void Dash::Move()
{
	//�v���C���[�ɂ��łɃq�b�g���Ă���ꍇ
	if (dashFlag == true)
	{
		//�v���C���[�ɋ߂Â�
		position = position + dashVec * dashSpeed;

		//�G���v���C���[�̌����������悤�ɂ���
		rotation.y = getVectorRotation(dashVec).y;

		return;
	}
	//�v���C���[�ƓG�̃x�N�g���擾
	XMFLOAT3 velo = playerPos - position;

	velo = normalize(velo);

	//�G���v���C���[�̌����������悤�ɂ���
	rotation.y = getVectorRotation(velo).y;

	//�v���C���[�ɂ܂��q�b�g���ĂȂ��ꍇ
	if (dashFlag == false)
	{
		//�v���C���[�ɋ߂Â�
		position = position + velo * dashSpeed;
	}

	if (hitPlayerFlag == true && dashFlag == false)
	{
		//�v���C���[�ƓG�̃x�N�g���擾
		dashVec = playerPos - position;
		dashVec = normalize(dashVec);

		dashFlag = true;
	}
}

void Dash::UpdateState(Enemy* enemy)
{
	//�I�u�W�F�N�g�ɏՓ˂�����|��郂�[�V������
	if (hitObjectFlag == true)
	{
		object->SetInterpolation(frameInterpolation);
		enemy->ChangeState(new FallDown());
		return;
	}
}

void Dash::UpdateHitWall(JSONLoader::ColliderData objectColliderData)
{
	//�ǂ̒��ɂ����珈���I��
	if (ColliderManager::CheckCollider(colliderData, objectColliderData,true) == true)return;

	//�ǂ̊O�ɂ��鎞�̂�
	while (ColliderManager::CheckCollider(colliderData, objectColliderData,true) == false)
	{
		//�v���C���[���猴�_�̃x�N�g��
		XMFLOAT3 vec = XMFLOAT3(0.0f, 0.0f, 0.0f) - position;
		//�v���C���[���猴�_�̃x�N�g���𐳋K��
		vec = normalize(vec);
		//�ǂ̒��ɖ߂�܂ŉ��Z
		position = position + (vec * knockBackSpeed);
		//�R���C�_�[�f�[�^�̍��W�X�V
		colliderData.center = position;
	}
	//�t���O�𗧂Ă�
	hitObjectFlag = true;
}

void Dash::UpdateHitPiller(JSONLoader::ColliderData objectColliderData, int pillerNum)
{
	//���ɏՓ˂��ĂȂ������珈���I��
	if(ColliderManager::CheckCollider(colliderData, objectColliderData) == false)return;

	//���ɂ߂荞��ł����
	while (ColliderManager::CheckCollider(colliderData, objectColliderData) == true)
	{
		//������v���C���[�̃x�N�g��
		XMFLOAT3 vec = objectColliderData.center - colliderData.center;
		//�v���C���[���猴�_�̃x�N�g���𐳋K��
		vec = normalize(vec);
		//�ǂ̒��ɖ߂�܂ŉ��Z
		position = position - (vec * knockBackSpeed);
		//�R���C�_�[�f�[�^�̍��W�X�V
		colliderData.center = position;
	}

	//�t���O�𗧂Ă�
	if (hitPillerFlag == true && pillerNum != hitPillerNum)hitObjectFlag = true;
	else if(hitPillerFlag == false)hitObjectFlag = true;

	//�܂����̃V�[���Œ��ɏՓ˂��Ă��Ȃ�������t���O��߂�
	if (hitPillerFlag == false)hitPillerFlag = true;
	//�Ō�ɓ����������̔ԍ����c��
	hitPillerNum = pillerNum;
}

void CallMiniEnemy::InitializeState()
{
	//�A�j���[�V�����̐ݒ�
	object->StopAnimation();
	object->SetModel(modelAttack1);
	object->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;

	//�̂̓����蔻��̏���
	hitBodyFlag = true;

	//�����̏���
	addPos = standAddPos;
}

void CallMiniEnemy::Move()
{
}

void CallMiniEnemy::UpdateState(Enemy* enemy)
{
	//�A�j���[�V�������I�������
	if (objectTimer >= frameCallMiniEnemy)
	{
		object->SetInterpolation(frameInterpolation);
		enemy->ChangeState(new AttackOmen1());
		return;
	}
}

void CallMiniEnemy::UpdateAttack()
{
	//�G�Ăяo���t���O�����Ƃɖ߂�
	callEnemyFlag = false;
	if (objectTimer == 1)
	{
		callEnemyPos = (playerPos - position) / 2;
	}
	//�G�Ăяo�� 2��Ăяo��
	if (objectTimer == frameCallMiniEnemy2)
	{
		//�t���O�𗧂Ă�
		callEnemyFlag = true;
		//�G���Ăяo���ꏊ
		if (objectTimer == frameCallMiniEnemy2)callEnemyPos = callEnemyPos1;
	}

	//�G�Ăяo�� ���p�[�e�B�N��
	if (objectTimer == frameCallMiniEnemy2)
	{
		elecParticle->AddParticle(elecFrame, callEnemyPos1 + addElecPos1,
			callEnemyPos1, elecStartSlace1, elecEndSlace1, 60, elecStrength);
		explosionParticle1->Add(callEnemyPos1);
	}
	//�G�Ăяo��
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
	//�A�j���[�V�����̐ݒ�
	object->StopAnimation();
	object->SetModel(modelFallDown);
	object->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;

	//�̂̓����蔻��̏���
	hitBodyFlag = false;

	//�����̏���
	addPos = standAddPos;
	//�����̉��Z�̒l�̏���
	//�p�x�̌����ɉ�]
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
	//�|��Ă���ԃA�j���[�V�������X�g�b�v
	if (objectTimer >= frameFallDownEnemy - 1.0f)
	{
		object->StopAnimation();
	}

	//���Ԃ��������痧��������A�j���[�V������
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
	//�p�x�̌����ɉ�]
	XMFLOAT3 addPosition = rollRotation(fallDownCollderAddPos, rotation);
	colliderData.center = position + addPosition;
}

void GetUp::InitializeState()
{
	//�A�j���[�V�����̐ݒ�
	object->StopAnimation();
	object->SetModel(modelGetUp);
	object->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;

	//�̂̓����蔻��̏���
	hitBodyFlag = true;

	//�����̉��Z�̒l�̏���
	//�p�x�̌����ɉ�]
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
	//�����オ������U�����[�V������
	if (objectTimer >= frameGetUpEnemy)
	{
		//���̍U����e�ɐݒ�
		nextAttack01 = true;
		object->SetInterpolation(frameInterpolation);
		enemy->ChangeState(new AttackOmen1());
		return;
	}
}


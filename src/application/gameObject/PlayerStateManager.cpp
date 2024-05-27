#include "PlayerStateManager.h"
#include "mathOriginal.h"

void Wait::Initialize()
{
	//�A�j���[�V�����̐ݒ�
	object->StopAnimation();
	object->SetModel(modelWait);
	object->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;
}

void Wait::UpdateState(Player* player)
{
	//�q�b�g�t���O�������Ă�����	��_���[�W���[�V������
	if (hitTimer <= frameDown && invincibleFlag == true) 
	{
		player->ChangeState(new Down());
		return;
	} 

	//����Ԃ�R�{�^���������Ă�����U��3��
	if (keyManager->PushKey(KeyManager::PAD_RIGHT_SHOULDER) == 1 && form == Player::Fire)
	{
		player->ChangeState(new Attack3());
		return;
	} 

	//R�{�^���ōU��1
	else if (form == Player::Elec && keyManager->TriggerKey(KeyManager::PAD_RIGHT_SHOULDER) == 1)
	{
		player->ChangeState(new Attack1());
		return;
	}
	//�����~�܂��Ă���ꍇ
	else if (length(posVelocity) <= 0.01f)
	{
		return;
	}
	//���ʂɑ����Ă���ꍇ
	else
	{
		player->ChangeState(new Run());
		return;
	}
}

void Run::Initialize()
{
	//�A�j���[�V�����̐ݒ�
	object->StopAnimation();
	object->SetModel(modelRun);
	object->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;
}

void Run::UpdateState(Player* player)
{
	//�q�b�g�t���O�������Ă�����	��_���[�W���[�V������
	if (hitTimer <= frameDown && invincibleFlag == true)
	{
		player->ChangeState(new Down());
		return;
	}

	//����Ԃ�R�{�^���������Ă�����U��3��
	if (keyManager->PushKey(KeyManager::PAD_RIGHT_SHOULDER) == 1 && form == Player::Fire)
	{
		player->ChangeState(new Attack3());
		return;
	}

	//R�{�^���ōU��1
	else if (form == Player::Elec && keyManager->TriggerKey(KeyManager::PAD_RIGHT_SHOULDER))
	{
		player->ChangeState(new Attack1());
		return;
	}
	//�����~�܂��Ă���ꍇ
	else if (length(posVelocity) <= 0.01f)
	{
		player->ChangeState(new Wait());
		return;
	}
	//���ʂɑ����Ă���ꍇ
	else
	{
		return;
	}
}

void Run::MoveTitle(float timer)
{
	//�V�[���J�ڂ��n�܂��ĂȂ����
	//�ʏ�̃^�C�g���V�[��
	if (timer == 0)
	{
		//�p�x�x�N�g������
		rotVelocity.y = 0.01f;
		//�p�x�x�N�g�������Z
		rotation0 = rotation0 + rotVelocity;

		//���W���Z
		posVelocity.x = 0.9;
		posVelocity.z = -0.1;
	}

	//�V�[���J�ڃ^�C�}�[���n��������
	if (timer > 0)
	{
		if (timer == 1)
		{
			//�ŏ��ɉ��Z����p�x���擾
			addRot = rotation0.y - (float)PI / 2.0f; 
			originalRot = rotation0.y;
			//�x�N�g�����Œ�
			posVelocity.x = 0.0;
			posVelocity.z = 0.0;
		}
		//�p�x���Z �v���C���[���w��������悤��
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

	//�i�s�x�N�g������]
	posVelocity = rollRotation(posVelocity, rotation0);
	//�i�s�x�N�g�������Z
	position = position + posVelocity;
}

void Attack1::Initialize()
{
	//�A�j���[�V�����̐ݒ�
	object->StopAnimation();
	object->SetModel(modelAttack1);
	object->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;
}

void Attack1::UpdateState(Player* player)
{
	//�q�b�g�t���O�������Ă�����	��_���[�W���[�V������
	if (hitTimer <= frameDown && invincibleFlag == true)
	{
		player->ChangeState(new Down());
		return;
	}

	//�C���^�[�o������R�{�^���ŘA���U�� �U��2��
	if (keyManager->TriggerKey(KeyManager::PAD_RIGHT_SHOULDER) && 0 <=
		attack1Time - objectTimer && attack1Time - objectTimer <= AttackIntervalTime)
	{
		player->ChangeState(new Attack2());
		return;
	}
	//�U�����I����ė����~�܂��Ă���ꍇ
	else if (objectTimer >= attack1Time && length(posVelocity) <= 0.01f)
	{
		player->ChangeState(new Wait());
		return;
	}
	//�U�����I����ĕ��ʂɑ����Ă���ꍇ
	else if(objectTimer >= attack1Time)
	{
		player->ChangeState(new Run());
		return;
	}
}

void Attack1::UpdateAttack()
{
	//���b�N�I���̍X�V���~�߂�
	elecAttackFlag = true;
	//40�t���[���Ńq�b�g�t���O�𗧂Ă�(���U���Ă�ʂ̃^�C�~���O)
	if (objectTimer == elecFlame && lockOnFlag == true)
	{
		hitElecFlag = true;
	}

	//�����o���ꏊ�𒲐�
	if (objectTimer == 2)
	{
		addElecPos2 = rollRotation(XMFLOAT3(addElecPos1.x, addElecPos1.y, addElecPos1.z), rotation1);
	}
	elecParticle2->Add(position + addElecPos2);
	//40�t���[��(���U���Ă�ʂ̃^�C�~���O�ő���1�{�̗�)
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
	//�v���C���[�̌��ɂȂ�p�x
	//AROW�L�[�Ŋp�x�ύX
	rotVelocity.y = keyManager->GetStick(KeyManager::RStickX) * rot0Speed;
	//�p�x�x�N�g�������Z
	rotation0 = rotation0 + rotVelocity;

	//�v���C���[���G�̃x�N�g���擾���Ċp�x�擾
	XMFLOAT3 rot = getVectorRotation(lockOnPos - position);
	//���f����G�̕��Ɍ�������
	rotation1 = XMFLOAT3(rot.x, 0.0f, rot.z);

	return;
}

void Attack2::Initialize()
{
	//�A�j���[�V�����̐ݒ�
	object->StopAnimation();
	object->SetModel(modelAttack2);
	object->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;
	objectTime = attack2Time;
}

void Attack2::UpdateState(Player* player)
{
	//�q�b�g�t���O�������Ă�����	��_���[�W���[�V������
	if (hitTimer <= frameDown && invincibleFlag == true)
	{
		player->ChangeState(new Down());
		return;
	}
	//�U�����I����ė����~�܂��Ă���ꍇ
	else if (objectTimer >= attack2Time && length(posVelocity) <= 0.01f)
	{
		player->ChangeState(new Wait());
		return;
	}
	//�U�����I����ĕ��ʂɑ����Ă���ꍇ
	else if (objectTimer >= attack2Time)
	{
		player->ChangeState(new Run());
		return;
	}
}


void Attack2::UpdateAttack()
{
	//���b�N�I���̍X�V���~�߂�
	elecAttackFlag = true;
	//40�t���[���Ńq�b�g�t���O�𗧂Ă�(���U���Ă�ʂ̃^�C�~���O)
	if (objectTimer == elecFlame && lockOnFlag == true)
	{
		hitElecFlag = true;
	}

	//�����o���ꏊ�𒲐�
	if (objectTimer == 2)
	{
		addElecPos2 = rollRotation(XMFLOAT3(addElecPos1.x, addElecPos1.y, addElecPos1.z), rotation1);
	}
	elecParticle2->Add(position + addElecPos2);
	//40�t���[��(���U���Ă�ʂ̃^�C�~���O�ő���1�{�̗�)
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
	//�v���C���[�̌��ɂȂ�p�x
	//AROW�L�[�Ŋp�x�ύX
	rotVelocity.y = keyManager->GetStick(KeyManager::RStickX) * rot0Speed;
	//�p�x�x�N�g�������Z
	rotation0 = rotation0 + rotVelocity;
	
	//�v���C���[���G�̃x�N�g���擾���Ċp�x�擾
	XMFLOAT3 rot = getVectorRotation(lockOnPos - position);
	//���f����G�̕��Ɍ�������
	rotation1 = XMFLOAT3(rot.x, 0.0f, rot.z);

	return;
}

void Attack3::Initialize()
{
	//�A�j���[�V�����̐ݒ�
	object->StopAnimation();
	object->SetModel(modelAttack3);
	object->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;
}

void Attack3::UpdateState(Player* player)
{
	//�q�b�g�t���O�������Ă�����	��_���[�W���[�V������
	if (hitTimer <= frameDown && invincibleFlag == true)
	{
		player->ChangeState(new Down());
		return;
	}

	//�����~�܂��Ă���ꍇ
	else if (keyManager->PushKey(KeyManager::PAD_RIGHT_SHOULDER) != 1 && length(posVelocity) <= 0.01f)
	{
		player->ChangeState(new Wait());
		return;
	}
	//���ʂɑ����Ă���ꍇ
	else if(keyManager->PushKey(KeyManager::PAD_RIGHT_SHOULDER) != 1)
	{
		player->ChangeState(new Run());
	}
}

void Attack3::UpdateAttack()
{
	//�e�ǉ�
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
	//�v���C���[�̌��ɂȂ�p�x
	//AROW�L�[�Ŋp�x�ύX
	rotVelocity.y = keyManager->GetStick(KeyManager::RStickX) * rot0Speed;
	//�p�x�x�N�g�������Z
	rotation0 = rotation0 + rotVelocity;

	rotation1 = XMFLOAT3(0.0f, 0.0f, 0.0f);

	//���W
	//���X�e�B�b�N�ňړ�
	XMFLOAT2 stick = normalize(keyManager->GetStick(KeyManager::LStickX), keyManager->GetStick(KeyManager::LStickY));
	posVelocity.x = stick.x * attack3PosSpeed;
	posVelocity.z = stick.y * attack3PosSpeed;
	//�i�s�x�N�g������]
	posVelocity = rollRotation(posVelocity, rotation0);
	//�i�s�x�N�g�������Z
	position = position + posVelocity;
}

void Down::Initialize()
{
	//�A�j���[�V�����̐ݒ�
	object->StopAnimation();
	object->SetModel(modelDown);
	object->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;
}

void Down::UpdateState(Player* player)
{
	//�Q�[���I�[�o�[��
	if (HP <= 0)
	{
		if (objectTimer == frameDown - 3)
		{
			object->StopAnimation();
		}
		return;
	}

	//�q�b�g�t���O���߂�����
	if (objectTimer >= frameDown)
	{
		player->ChangeState(new Wait());
		return;
	}
}

void Down::Move()
{
	//�v���C���[�̌��ɂȂ�p�x
	//AROW�L�[�Ŋp�x�ύX
	rotVelocity.y = keyManager->GetStick(KeyManager::RStickX) * rot0Speed;
	//�p�x�x�N�g�������Z
	rotation0 = rotation0 + rotVelocity;
}

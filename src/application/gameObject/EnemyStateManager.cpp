#include "EnemyStateManager.h"
#include "mathOriginal.h"
#include "ColliderManager.h"
#include "MiniEnemy.h"

void Stand::Initialize()
{
	//�A�j���[�V�����̐ݒ�
	objectStand->StopAnimation();
	objectStand->PlayAnimation();

	//�^�C�}�[�̐ݒ�
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
	//�U���O���̃A�j���[�V�������I�������
	if (tutorialTimer > tutorialStandFrame + frameAttackOmen1)
	{
		return;
	}

	//���΂炭�����Ă�
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
	//�A�j���[�V�����̐ݒ�
	objectWalk->StopAnimation();
	objectWalk->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;
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
	//�A�j���[�V�����̐ݒ�
	objectAttack1->StopAnimation();
	objectAttack1->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;
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
	//�A�j���[�V�����̐ݒ�
	objectAttackOmen1->StopAnimation();
	objectAttackOmen1->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;
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
			enemy->ChangeState(new CallMiniEnemy());
			return;
		}
		//���̍s�����_�b�V���̎�
		if (nextDash)
		{
			nextDash = false;
			enemy->ChangeState(new Dash());
			return;
		}
		//���̍s�����G�Ăяo���̎�
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
	//�A�j���[�V�������I�������
	if (objectTimer >= frameAttackOmen1)
	{
		enemy->ChangeState(new Stand());
		return;
	}
}

void AttackOmen1::UpdateStateMovePhase(Enemy* enemy)
{
	// �A�j���[�V�������I�������
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
	//�A�j���[�V�����̐ݒ�
	objectDash->StopAnimation();
	objectDash->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;
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
}

void Dash::UpdateState(Enemy* enemy)
{
	//�I�u�W�F�N�g�ɏՓ˂�����|��郂�[�V������
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
		//�v���C���[�ƓG�̃x�N�g���擾
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

void Dash::UpdateHitPiller(JSONLoader::ColliderData objectColliderData)
{
	//�^�C�}�[90�t���[���ȓ��͔�����Ƃ�Ȃ�
	if (objectTimer < frameNoPillerHit)return;

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
	hitObjectFlag = true;
}

void CallMiniEnemy::Initialize()
{
	//�A�j���[�V�����̐ݒ�
	objectCallMiniEnemy->StopAnimation();
	objectCallMiniEnemy->PlayAnimation();

	//�^�C�}�[�̐ݒ�
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
	//�A�j���[�V�������I�������
	if (objectTimer >= frameCallMiniEnemy)
	{
		enemy->ChangeState(new AttackOmen1());
		return;
	}
}

void CallMiniEnemy::UpdateAttackMovePhase()
{
	//�G�Ăяo���t���O�����Ƃɖ߂�
	callEnemyFlag = false;
	//�G�Ăяo�� 2��Ăяo��
	if (objectTimer == 40)
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
			callEnemyPos1, elecStartSlace1, elecEndSlace1, 60.0f, elecStrength);
		explosionParticle1->Add(callEnemyPos1);
	}
	//�G�Ăяo��
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
	//�A�j���[�V�����̐ݒ�
	objectFallDown->StopAnimation();
	objectFallDown->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;
}

void FallDown::Move()
{
}

void FallDown::UpdateState(Enemy* enemy)
{
	//���Ԃ��������痧��������A�j���[�V������
	if (objectTimer >= frameFallDownEnemy)
	{
		enemy->ChangeState(new GetUp());
		return;
	}
}

void FallDown::UpdateStateMovePhase(Enemy* enemy)
{
	//���Ԃ��������痧��������A�j���[�V������
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
	//�A�j���[�V�����̐ݒ�
	objectGetUp->StopAnimation();
	objectGetUp->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;
}

void GetUp::Move()
{
}

void GetUp::UpdateState(Enemy* enemy)
{
	//�����オ������U�����[�V������
	if (objectTimer >= frameGetUpEnemy)
	{
		//���̍U����e�ɐݒ�
		nextAttack01 = true;
		enemy->ChangeState(new AttackOmen1());
		return;
	}
}

void GetUp::UpdateStateMovePhase(Enemy* enemy)
{
	//�����オ������G�Ăяo����
	if (objectTimer >= frameGetUpEnemy)
	{
		//���̍U����e�ɐݒ�
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
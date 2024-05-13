#include "PlayerStateManager.h"
#include "mathOriginal.h"

void Wait::Initialize()
{
	//�A�j���[�V�����̐ݒ�
	objectWait->StopAnimation();
	objectWait->PlayAnimation();

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
	if (dxInput->PushKey(DXInput::PAD_RIGHT_SHOULDER) == 1 && form == Player::Fire)
	{
		player->ChangeState(new Attack3());
		return;
	} 

	//R�{�^���ōU��1
	else if (form == Player::Elec && dxInput->TriggerKey(DXInput::PAD_RIGHT_SHOULDER) == 1)
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

void Wait::Draw(ID3D12GraphicsCommandList* cmdList)
{
	objectWait->Draw(cmdList);

	hitElecFlag = false;
}

void Wait::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	objectWait->DrawLightView(cmdList);
}

void Wait::SetSRV(ID3D12DescriptorHeap* SRV)
{
	objectWait->SetSRV(SRV);
}

void Wait::UpdateObject()
{
	objectWait->SetPosition(position);
	objectWait->SetRotation(rotation0 + rotation1);
	objectWait->SetScale(scale);
	objectWait->SetDrawShaderNum(form);
	objectWait->Update();
}

void Run::Initialize()
{
	//�A�j���[�V�����̐ݒ�
	objectRun->StopAnimation();
	objectRun->PlayAnimation();

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
	if (dxInput->PushKey(DXInput::PAD_RIGHT_SHOULDER) == 1 && form == Player::Fire)
	{
		player->ChangeState(new Attack3());
		return;
	}

	//R�{�^���ōU��1
	else if (form == Player::Elec && dxInput->TriggerKey(DXInput::PAD_RIGHT_SHOULDER))
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

void Run::Draw(ID3D12GraphicsCommandList* cmdList)
{
	objectRun->Draw(cmdList);

	hitElecFlag = false;
}

void Run::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	objectRun->DrawLightView(cmdList);
}

void Run::SetSRV(ID3D12DescriptorHeap* SRV)
{
	objectRun->SetSRV(SRV);
}

void Run::UpdateObject()
{
	objectRun->SetPosition(position);
	objectRun->SetRotation(rotation0 + rotation1);
	objectRun->SetScale(scale);
	objectRun->SetDrawShaderNum(form);
	objectRun->Update();
}

void Attack1::Initialize()
{
	//�A�j���[�V�����̐ݒ�
	objectAttack1->StopAnimation();
	objectAttack1->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = true;
	objectTime = attack1Time;
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
	if (dxInput->TriggerKey(DXInput::PAD_RIGHT_SHOULDER) && 0 <= 
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
			lockOnPos + XMFLOAT3(0.0f, 50.0f, 0.0f), elecStartSlace1, elecEndSlace1, 10.0f, elecStrength);
	}
	if (objectTimer > elecFlame && (int)objectTimer % elecInterval == 0)
	{
		for (int i = 0; i < elecVol; i++)
		{
			elecParticle1->AddParticle(20.0f, position + addElecPos2,
				lockOnPos + XMFLOAT3(0.0f, 50.0f, 0.0f), elecStartSlace2, elecEndSlace2, 20.0f, elecStrength);
		}
	}
}

void Attack1::Move()
{
	//�v���C���[�̌��ɂȂ�p�x
	//AROW�L�[�Ŋp�x�ύX
	rotVelocity.y = dxInput->GetStick(DXInput::RStickX) * rot0Speed;
	/*rotVelocity.y = (input->PushKey(DIK_RIGHT) - input->PushKey(DIK_LEFT)) * rotSpeed;*/
	//�p�x�x�N�g�������Z
	rotation0 = rotation0 + rotVelocity;

	//�v���C���[���G�̃x�N�g���擾���Ċp�x�擾
	XMFLOAT3 rot = getVectorRotation(lockOnPos - position);
	//���f����G�̕��Ɍ�������
	rotation1 = XMFLOAT3(rot.x, 0.0f, rot.z);

	return;
}

void Attack1::Draw(ID3D12GraphicsCommandList* cmdList)
{
	objectAttack1->Draw(cmdList);

	hitElecFlag = false;
}

void Attack1::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	objectAttack1->DrawLightView(cmdList);
}

void Attack1::SetSRV(ID3D12DescriptorHeap* SRV)
{
	objectAttack1->SetSRV(SRV);
}

void Attack1::UpdateObject()
{
	objectAttack1->SetPosition(position);
	objectAttack1->SetRotation(rotation0 + rotation1);
	objectAttack1->SetScale(scale);
	objectAttack1->SetDrawShaderNum(form);
	objectAttack1->Update();
}

void Attack2::Initialize()
{
	//�A�j���[�V�����̐ݒ�
	objectAttack2->StopAnimation();
	objectAttack2->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = true;
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
	//40�t���[���Ńq�b�g�t���O�𗧂Ă�(���U���Ă�ʂ̃^�C�~���O)
	if (objectTimer == elecFlame && lockOnFlag == true)
	{
		hitElecFlag = true;
	}

	elecParticle2->Add(position + addElecPos2);
	//40�t���[��(���U���Ă�ʂ̃^�C�~���O�ő���1�{�̗�)
	if (objectTimer == elecFlame)
	{
		elecParticle1->AddParticle(attack2Time - elecFlame, position + addElecPos2,
			lockOnPos + XMFLOAT3(0.0f, 50.0f, 0.0f), elecStartSlace1, elecEndSlace1, 10.0f, elecStrength);
	}
	if (objectTimer > elecFlame && (int)objectTimer % elecInterval == 0)
	{
		for (int i = 0; i < elecVol; i++)
		{
			elecParticle1->AddParticle(20.0f, position + addElecPos2,
				lockOnPos + XMFLOAT3(0.0f, 50.0f, 0.0f), elecStartSlace2, elecEndSlace2, 20.0f, elecStrength);
		}
	}
}

void Attack2::Move()
{
	//�v���C���[�̌��ɂȂ�p�x
	//AROW�L�[�Ŋp�x�ύX
	rotVelocity.y = dxInput->GetStick(DXInput::RStickX) * rot0Speed;
	/*rotVelocity.y = (input->PushKey(DIK_RIGHT) - input->PushKey(DIK_LEFT)) * rotSpeed;*/
	//�p�x�x�N�g�������Z
	rotation0 = rotation0 + rotVelocity;
	
	//�v���C���[���G�̃x�N�g���擾���Ċp�x�擾
	XMFLOAT3 rot = getVectorRotation(lockOnPos - position);
	//���f����G�̕��Ɍ�������
	rotation1 = XMFLOAT3(rot.x, 0.0f, rot.z);

	return;
}

void Attack2::Draw(ID3D12GraphicsCommandList* cmdList)
{
	objectAttack2->Draw(cmdList);

	hitElecFlag = false;
}

void Attack2::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	objectAttack2->DrawLightView(cmdList);
}

void Attack2::SetSRV(ID3D12DescriptorHeap* SRV)
{
	objectAttack2->SetSRV(SRV);
}

void Attack2::UpdateObject()
{
	objectAttack2->SetPosition(position);
	objectAttack2->SetRotation(rotation0 + rotation1);
	objectAttack2->SetScale(scale);
	objectAttack2->SetDrawShaderNum(form);
	objectAttack2->Update();
}

void Attack3::Initialize()
{
	//�A�j���[�V�����̐ݒ�
	objectAttack3->StopAnimation();
	objectAttack3->PlayAnimation();

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
	else if (dxInput->PushKey(DXInput::PAD_RIGHT_SHOULDER) != 1 && length(posVelocity) <= 0.01f)
	{
		player->ChangeState(new Wait());
		return;
	}
	//���ʂɑ����Ă���ꍇ
	else if(dxInput->PushKey(DXInput::PAD_RIGHT_SHOULDER) != 1)
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
		velo = normalize(velo) * bullet1Speed; 
		bullet->SetBullet(position + bullet1AddPosition, velo, 0.0f, bullet1Frame);
	}
}

void Attack3::Move()
{
	//�v���C���[�̌��ɂȂ�p�x
	//AROW�L�[�Ŋp�x�ύX
	rotVelocity.y = dxInput->GetStick(DXInput::RStickX) * rot0Speed;
	/*rotVelocity.y = (input->PushKey(DIK_RIGHT) - input->PushKey(DIK_LEFT)) * rotSpeed;*/
	//�p�x�x�N�g�������Z
	rotation0 = rotation0 + rotVelocity;

	rotation1 = XMFLOAT3(0.0f, 0.0f, 0.0f);

	//���W
	//���X�e�B�b�N�ňړ�
	XMFLOAT2 stick = normalize(dxInput->GetStick(DXInput::LStickX), dxInput->GetStick(DXInput::LStickY));
	posVelocity.x = stick.x * attack3PosSpeed;
	posVelocity.z = stick.y * attack3PosSpeed;
	/*posVelocity.x = (input->PushKey(DIK_D) - input->PushKey(DIK_A)) * posSpeed;
	posVelocity.z = (input->PushKey(DIK_W) - input->PushKey(DIK_S)) * posSpeed;*/
	//�i�s�x�N�g������]
	posVelocity = rollRotation(posVelocity, rotation0);
	//�i�s�x�N�g�������Z
	position = position + posVelocity;
}

void Attack3::Draw(ID3D12GraphicsCommandList* cmdList)
{
	objectAttack3->Draw(cmdList);

	hitElecFlag = false;
}

void Attack3::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	objectAttack3->DrawLightView(cmdList);
}

void Attack3::SetSRV(ID3D12DescriptorHeap* SRV)
{
	objectAttack3->SetSRV(SRV);
}

void Attack3::UpdateObject()
{
	objectAttack3->SetPosition(position);
	objectAttack3->SetRotation(rotation0 + rotation1);
	objectAttack3->SetScale(scale);
	objectAttack3->SetDrawShaderNum(form);
	objectAttack3->Update();
}

void Down::Initialize()
{
	//�A�j���[�V�����̐ݒ�
	objectDown->StopAnimation();
	objectDown->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;
}

void Down::UpdateState(Player* player)
{
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
	rotVelocity.y = dxInput->GetStick(DXInput::RStickX) * rot0Speed;
	/*rotVelocity.y = (input->PushKey(DIK_RIGHT) - input->PushKey(DIK_LEFT)) * rotSpeed;*/
	//�p�x�x�N�g�������Z
	rotation0 = rotation0 + rotVelocity;
}


void Down::Draw(ID3D12GraphicsCommandList* cmdList)
{
	objectDown->Draw(cmdList);

	hitElecFlag = false;
}

void Down::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	objectDown->DrawLightView(cmdList);
}

void Down::SetSRV(ID3D12DescriptorHeap* SRV)
{
	objectDown->SetSRV(SRV);
}

void Down::UpdateObject()
{
	objectDown->SetPosition(position);
	objectDown->SetRotation(rotation0 + rotation1);
	objectDown->SetScale(scale);
	objectDown->SetDrawShaderNum(form);
	objectDown->Update();
}

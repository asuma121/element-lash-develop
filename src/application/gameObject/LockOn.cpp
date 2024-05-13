#include "LockOn.h"
#include "mathOriginal.h"
#include "imgui.h"

void LockOn::Initialize()
{
	//�r���{�[�h�̃X�v���C�g ���f��
	lockOnSpriteModel1 = new BillboardSpriteModel();
	lockOnSpriteModel1->CreateBuffers();
	lockOnSpriteModel1->SetTextureNum(22);

	//�r���{�[�h�̃X�v���C�g
	lockOnSprite1 = new BillboardSprite();
	lockOnSprite1->Initialize();
	lockOnSprite1->SetModel(lockOnSpriteModel1);

	//���b�N�I�����Ă��Ȃ����̃X�v���C�g
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
	//�ő�˒��ɐݒ�
	target = { hitLength,hitLength,hitLength };

	//�S�Ă̓G�Ƀ��b�N�I������
	for (int i = 0; i < enemyPosition.size(); i++)
	{
		//�J��������v���C���[�̃x�N�g���̊p�x���擾
		float rot1 = getVectorRotation(playerPosition - camera->GetEye()).y;
		//�v���C���[����G�̃x�N�g���̊p�x���擾
		float rot2 = getVectorRotation(enemyPosition[i] - playerPosition).y;

		debugTimer[0] = rot1;
		debugTimer2[0] = rot1 - rot2;

		//�J�����̉�p���ɂ��Ȃ���΃X���[
		if (-hitAngle > rot1 - rot2 || rot1 - rot2 > hitAngle)
		{
			if( -2*PI + hitAngle < rot1 - rot2 || 2 * PI - hitAngle > rot1 - rot2)
			continue;
		}
		//����̋����ȓ��ɂ��Ȃ���΃X���[
		if (length(playerPosition - enemyPosition[i]) > hitLength)continue;
		//���b�N�I�����Ă���̂Ńt���O�𗧂Ă�
		lockOnFlag = true;
		//�J��������ŒZ�̓G���v�Z
		if (length(target) > length(camera->GetEye() - enemyPosition[i]))
		{
			target = enemyPosition[i];
		}
	}

	if (lockOnFlag)
	{
		//���b�N�I���X�v���C�g�̍��W
		XMFLOAT3 sprite1Pos = target;

		//�G�̑������Q�Ƃ��Ă���̂ł��������ɂ���
		sprite1Pos.y += 50.0f;

		//�^�[�Q�b�g���J�����̃x�N�g�������߂�
		XMFLOAT3 vec = sprite1Pos - camera->GetEye();
		//�^�[�Q�b�g���J�����̃x�N�g���̒��������߂�
		float len = length(vec);
		//���K��
		vec = normalize(vec);
		//�^�[�Q�b�g��菭���O�ɏo��
		sprite1Pos = sprite1Pos - XMFLOAT3(vec.x * (len * 0.8f), vec.y * (len * 0.8f), vec.z * (len * 0.8f));

		//�X�v���C�g�X�V
		lockOnSprite1->SetPosition(sprite1Pos);
		lockOnSprite1->SetScale(XMFLOAT3(2.5f, 2.5f, 2.5f));
		lockOnSprite1->Update();

		debugTargetPos[0] = sprite1Pos.x;
		debugTargetPos[1] = sprite1Pos.y;
		debugTargetPos[2] = sprite1Pos.z;
	}
	//���b�N�I�����Ă��Ȃ����̃^�[�Q�b�g��ݒ肷��
	else
	{
		//�J�����̌����̃x�N�g���擾
		XMFLOAT3 velo = (camera->GetTarget() + XMFLOAT3(0.0f,3.0f,0.0f)) - camera->GetEye();
		velo = normalize(velo);
		velo = velo * hitLength;
		target = camera->GetEye() + velo;
	}

	if (lockOnFlag)debugNum[0] = 1;
	else { debugNum[0] = 0; }

	//�G�̍��W���N���A����
	enemyPosition.clear();
}

void LockOn::AddEnemyPos(XMFLOAT3 position)
{
	//�G�̍��W��ǉ�
	enemyPosition.emplace_back(position);
}

void LockOn::Draw(ID3D12GraphicsCommandList* cmdList)
{
	//���b�N�I�����Ă���Ƃ��`��
	if (lockOnFlag == true)
	{
		lockOnSprite1->Draw(cmdList);
	}

	//���b�N�I�����Ă��Ȃ����`��
	else
	{
		lockOnSprite2->Draw(cmdList);
	}

	debugTargetFlag[0] = lockOnFlag;

	//���b�N�I���t���O��߂�
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

#include "MiniEnemy.h"
#include "mathOriginal.h"
#include "FbxLoader.h"
#include "imgui.h"
#include "ColliderManager.h"

Camera* MiniEnemy::camera = nullptr;
Input* MiniEnemy::input = nullptr;

void MiniEnemy::Initialize()
{
	//HP�t���[���̃r���{�[�h ���f��
	//hpFrameSpriteModel = new BillboardSpriteModel();
	//hpFrameSpriteModel->CreateBuffers();
	//hpFrameSpriteModel->SetTextureNum(23);

	////HP�t���[���̃r���{�[�h
	//hpFrameSprite = new BillboardSprite();
	//hpFrameSprite->Initialize();
	//hpFrameSprite->SetModel(hpFrameSpriteModel);
	//hpFrameSprite->SetScale(hpFrameScale);

	////HP�Q�[�W�̃r���{�[�h ���f��
	//hpBarSpriteModel = new BillboardSpriteModel();
	//hpBarSpriteModel->CreateBuffers();
	//hpBarSpriteModel->SetTextureNum(24);

	////HP�Q�[�W�̃r���{�[�h
	//hpBarSprite = new BillboardSprite();
	//hpBarSprite->Initialize();
	//hpBarSprite->SetModel(hpBarSpriteModel);

	//���f��
	modelDash = FbxLoader::GetInstance()->LoadModelFromFile("miniEnemyDash");
	modelDown = FbxLoader::GetInstance()->LoadModelFromFile("enemyDown");
}

void MiniEnemy::Update()
{
	//�U���X�V
	UpdateAttack();

	//�I�u�W�F�N�g�X�V
	UpdateObject();

	//�R���C�_�[�X�V
	UpdateCollider();

	//�X�v���C�g�X�V
	UpdateSprite();

	//�_���[�W�X�V
	UpdateDamage();

	//���S����
	DeleteEnemy();
}

void MiniEnemy::UpdateObject()
{

	for (int i = 0; i < enemys.size(); i++)
	{
		if (enemys[i].status == Dash)
		{
			enemys[i].objectDash->SetPosition(enemys[i].position);
			enemys[i].objectDash->SetRotation(enemys[i].rotation);
			enemys[i].objectDash->Update();
		}
		else
		{
			enemys[i].objectDown->SetPosition(enemys[i].position);
			enemys[i].objectDown->SetRotation(enemys[i].rotation);
			enemys[i].objectDown->Update();
		}
	}
}

void MiniEnemy::UpdateSprite()
{
	//HP�o�[�����݂�HP��
	//hpBar2Scale.x = hpBar2OriginalScale.x * (HP / maxHP);
	//hpBar3Pos.x = hpBar3OriginalPos.x - (hpBar2OriginalScale.x * ((maxHP - HP) / maxHP));

	/*hpFrameSprite->SetPosition(XMFLOAT3(0.0f, 5.0f, 0.0f));
	hpBarSprite->SetPosition(XMFLOAT3(0.0f, 5.0f, 0.0f));
	hpBarSprite->SetScale(hpBarScale);

	hpFrameSprite->Update();
	hpBarSprite->Update();*/
}

void MiniEnemy::UpdateCollider()
{
	for (int i = 0; i < enemys.size(); i++)
	{
		enemys[i].colliderData.rotation = enemys[i].rotation;
		enemys[i].colliderData.center = enemys[i].position + XMFLOAT3(0.0f, 5.0f, 0.0f);
	}
}

void MiniEnemy::UpdateDamage()
{
	for (int i = 0; i < enemys.size(); i++)
	{
		//���U�������������
		if (enemys[i].hitFireFlag == true)
		{
			//HP�����炷
			enemys[i].HP -= fireDamage;
			//�t���O�����Ƃɖ߂�
			enemys[i].hitFireFlag = false;
		}
		//HP0�̏ꍇ
		if (enemys[i].HP <= 0)
		{
			enemys[i].deadFlag = true;
			enemys[i].status = Down;
		}
		//�_�E����ԂɂȂ����Ƃ�
		if (enemys[i].status == Down && enemys[i].preStatus == Dash)
		{
			enemys[i].objectDash->StopAnimation();
			enemys[i].objectDown->PlayAnimation();
		}
	}
}

void MiniEnemy::DeleteEnemy()
{
	for (int i = 0; i < enemys.size(); i++)
	{
		//���S�^�C�}�[�X�V
		if (enemys[i].deadFlag == true)
		{
			enemys[i].deadTimer++;
			if (enemys[i].deadTimer >= deadTime)
			{
				enemys.erase(enemys.begin() + i);
			}
		}
	}
}

void MiniEnemy::Draw(ID3D12GraphicsCommandList* cmdList)
{
	//ImGui
	ImGui::Begin("miniEnemy");
	ImGui::SetWindowPos(ImVec2(0, 600));
	ImGui::SetWindowSize(ImVec2(700, 150));
	ImGui::InputInt("debugNum", debugNum);
	ImGui::End();

	for (int i = 0; i < enemys.size(); i++)
	{
		if (enemys[i].status == Dash)
		{
			enemys[i].objectDash->Draw(cmdList);
		}
		else
		{
			enemys[i].objectDown->Draw(cmdList);
		}
	}

	//�O�t���[���̃X�e�[�^�X�X�V
	for (int i = 0; i < enemys.size(); i++)
	{
		enemys[i].preStatus = enemys[i].status;
	}
}

void MiniEnemy::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{

	for (int i = 0; i < enemys.size(); i++)
	{
		if (enemys[i].status == Dash)
		{
			enemys[i].objectDash->DrawLightView(cmdList);
		}
		else
		{
			enemys[i].objectDown->DrawLightView(cmdList);
		}
	}
}

void MiniEnemy::DrawSprite(ID3D12GraphicsCommandList* cmdList)
{
	//hpFrameSprite->Draw(cmdList);
	//hpBarSprite->Draw(cmdList);
}

void MiniEnemy::UpdateAttack()
{
	for (int i = 0; i < enemys.size(); i++)
	{
		//�_�b�V����
		if (enemys[i].status == Dash)
		{
			//�v���C���[�܂ł̃x�N�g�������߂�
			XMFLOAT3 velo = XMFLOAT3(playerPos.x - enemys[i].position.x, 0.0f, playerPos.z - enemys[i].position.z);
			//���K��
			velo = normalize(velo) * speed;
			//���W�ɉ��Z
			enemys[i].position = enemys[i].position + velo;

			XMFLOAT3 rot = getVectorRotation(velo);
			enemys[i].rotation = rot;
		}
	}
}

void MiniEnemy::StatusManager()
{
}

void MiniEnemy::SetSRV(ID3D12DescriptorHeap* SRV)
{
	for (int i = 0; i < enemys.size(); i++)
	{
		if (enemys[i].status == Dash)
		{
			enemys[i].objectDash->SetSRV(SRV);
		}
		else
		{
			enemys[i].objectDown->SetSRV(SRV);
		}
	}
}

void MiniEnemy::Reset()
{
}

void MiniEnemy::AddEnemy(XMFLOAT3 pos)
{
	Enemy enemy;

	//�^����ꂽ���W�����ƂɃI�u�W�F�N�g����
	enemy.objectDash = new FbxObject3D;
	enemy.objectDash->Initialize();
	enemy.objectDash->SetModel(modelDash);
	enemy.objectDash->SetTextureNum(0);
	enemy.objectDash->PlayAnimation();
	enemy.objectDash->SetPosition(pos);
	enemy.objectDash->SetScale(scale);

	//�^����ꂽ���W�����ƂɃI�u�W�F�N�g����
	enemy.objectDown = new FbxObject3D;
	enemy.objectDown->Initialize();
	enemy.objectDown->SetModel(modelDown);
	enemy.objectDown->SetTextureNum(0);
	enemy.objectDown->StopAnimation();
	enemy.objectDown->SetPosition(pos);
	enemy.objectDown->SetScale(scale);

	//�R���C�_�[�̐ݒ�
	//�R���C�_�[���Ƃɖ��O������
	std::string objectName = "miniEnemy" + std::to_string(number);
	//�R���C�_�[�f�[�^�̐���
	enemy.colliderData.type = "Sphere";	//��������̂Ŏ�邽��
	enemy.colliderData.objectName = objectName;
	enemy.colliderData.scale = colliderScale;
	enemy.colliderData.rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	enemy.colliderData.center = pos;
	//�R���C�_�[�}�l�[�W���[�ɃZ�b�g
	ColliderManager::SetCollider(enemy.colliderData);

	//�X�e�[�^�X
	enemy.status = Dash;
	enemy.preStatus = Dash;
	//���W�ݒ�
	enemy.position = pos;
	//�p�x
	enemy.rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	//HP
	enemy.HP = maxHP;
	//������t���O
	enemy.hitFireFlag = false;
	enemy.hitElecFlag = false;
	//���S�t���O
	enemy.deadFlag = false;
	//���S�^�C�}�[
	enemy.deadTimer = 0;

	enemys.emplace_back(enemy);

	//�e�ɂ���ԍ��𑝂₷
	number++;
}
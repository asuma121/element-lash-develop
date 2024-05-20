#include "TutorialEnemy.h"
#include "mathOriginal.h"
#include "FbxLoader.h"
#include "imgui.h"
#include "ColliderManager.h"
#define G 6.674	//���L���͒萔
#define GAcceleration 9.80665 * 1/10	//�d�͉����x

Camera* TutorialEnemy::camera = nullptr;
Input* TutorialEnemy::input = nullptr;

void TutorialEnemy::Initialize()
{
	//HP�o�[�̃X�v���C�g
	hpBar1 = new Sprite();
	hpBar1->Initialize();
	hpBar1->SetTextureNum(23);
	hpBar2 = new Sprite();
	hpBar2->Initialize();
	hpBar2->SetTextureNum(24);
	hpBar3 = new Sprite();
	hpBar3->Initialize();
	hpBar3->SetTextureNum(25);
	hpBar4 = new Sprite();
	hpBar4->Initialize();
	hpBar4->SetTextureNum(26);

	//���f��
	modelDash = FbxLoader::GetInstance()->LoadModelFromFile("enemyDash");
	modelDown = FbxLoader::GetInstance()->LoadModelFromFile("enemyDown");
	modelStand = FbxLoader::GetInstance()->LoadModelFromFile("enemyStand");
	//�I�u�W�F�N�g
	object = new FbxObject3D;
	object->Initialize();
	object->SetModel(modelStand);
	object->SetTextureNum(0);
	object->PlayAnimation();

	//�R���C�_�[�̐ݒ�
	colliderData.type = "Sphere";	//��������̂Ŏ�邽��
	colliderData.objectName = "tutorialEnemy";
	colliderData.scale = scale;
	colliderData.rotation = rotation;
	colliderData.center = position;
	//�R���C�_�[�}�l�[�W���[�ɃZ�b�g
	ColliderManager::SetCollider(colliderData);
}

void TutorialEnemy::UpdateTutorial()
{
	if (isDead2 == false)return;

	//�R���C�_�[�X�V
	UpdateCollider();

	//�X�v���C�g�X�V
	UpdateSprite();

	//�_���[�W�X�V
	UpdateDamage();

	//�I�u�W�F�N�g�X�V
	UpdateObject();
}

void TutorialEnemy::UpdateGame()
{
	if (isDead2 == true)return;

	//�R���C�_�[�X�V
	UpdateCollider();

	//�_���[�W�X�V
	UpdateDamage();

	if (isDead3 == false)MoveGame();
	
	//�I�u�W�F�N�g�X�V
	UpdateObject();
}

void TutorialEnemy::UpdateMovePhase()
{
	if (isDead2 == true)return;

	//�R���C�_�[�X�V
	UpdateCollider();

	//�_���[�W�X�V
	UpdateDamage();

	//����
	MoveMovePhase();

	//�I�u�W�F�N�g�X�V
	UpdateObject();
}

void TutorialEnemy::UpdateObject()
{
	object->SetPosition(position);
	object->SetRotation(rotation);
	object->SetScale(scale);
	
	object->Update();
}

void TutorialEnemy::UpdateSprite()
{
	//HP�o�[�����݂�HP��
	hpBar2Scale.x = hpBar2OriginalScale.x * (HP / maxHP);
	hpBar3Pos.x = hpBar3OriginalPos.x - (hpBar2OriginalScale.x * ((maxHP - HP) / maxHP));

	//�X�V
	hpBar1->Update(hpBar1Pos, hpBar1Scale);
	hpBar2->Update(hpBar2Pos, hpBar2Scale);
	hpBar3->Update(hpBar3Pos, hpBar3Scale);
	hpBar4->Update(hpBar4Pos, hpBar4Scale);
}

void TutorialEnemy::UpdateCollider()
{
	colliderData.scale = colliderScale;
	colliderData.rotation = rotation;
	colliderData.center = position + XMFLOAT3(0.0f, 5.0f, 0.0f);
}

void TutorialEnemy::UpdateDamage()
{
	//���U�������������
	if (hitFlag1 == true)
	{
		//HP�����炷
		HP -= 1.0f;
	}

	//���U�������������
	if (hitElec == true)
	{
		//HP�����炷
		HP -= 5.0f;
	}

	//���S
	if (HP <= 0)
	{
		isDead1 = true;
	}

	//���S�����t���[���̏���
	if (isDead1 == true && isDead3 == false)
	{
		SetDown();
		isDead3 = true;
	}

	//���S������
	if (isDead3 == true)
	{
		deadTimer++;
		if (deadTimer >= deadTime)
		{
			isDead2 = true;
		}
	}

	//�t���O�����Ƃɖ߂�
	hitFlag1 = false;
	hitElec = false;
}

void TutorialEnemy::Draw(ID3D12GraphicsCommandList* cmdList)
{
	if (isDead2 == false)
	{
		object->Draw(cmdList);
	}
}

void TutorialEnemy::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	if (isDead2 == false)
	{
		object->DrawLightView(cmdList);
	}
}

void TutorialEnemy::DrawSprite(ID3D12GraphicsCommandList* cmdList)
{
	hpBar2->Draw(cmdList);
	hpBar1->Draw(cmdList);
	hpBar3->Draw(cmdList);
}

void TutorialEnemy::MoveGame()
{
	//�v���C���[�܂ł̃x�N�g�������߂�
	XMFLOAT3 velo = XMFLOAT3(playerPos.x - position.x, 0.0f, playerPos.z - position.z);
	//���K��
	velo = normalize(velo) * speed;
	//���W�ɉ��Z
	position = position + velo;

	XMFLOAT3 rot = getVectorRotation(velo);
	rotation = rot;
}

void TutorialEnemy::MoveMovePhase()
{
	//�v���C���[�܂ł̃x�N�g�������߂�
	XMFLOAT3 velo = XMFLOAT3(playerPos.x - position.x, 0.0f, playerPos.z - position.z);

	XMFLOAT3 rot = getVectorRotation(velo);
	rotation = rot;
}

void TutorialEnemy::StatusManager()
{
}

void TutorialEnemy::SetSRV(ID3D12DescriptorHeap* SRV)
{
	object->SetSRV(SRV);
}

void TutorialEnemy::SetDash()
{
	//�_�b�V�����f�����Z�b�g���ăA�j���[�V�����J�n
	object->SetModel(modelDash);
	object->PlayAnimation();
}

void TutorialEnemy::SetDown()
{
	//�_�E�����f�����Z�b�g���ăA�j���[�V�����J�n
	object->SetModel(modelDown);
	object->PlayAnimation();
}

void TutorialEnemy::SetStand()
{
	//�����f�����Z�b�g���ăA�j���[�V�����J�n
	object->SetModel(modelStand);
	object->PlayAnimation();
}

void TutorialEnemy::SetTutorial()
{
	isDead1 = false;
	isDead2 = false;
	isDead3 = false;
	SetStand();
}

void TutorialEnemy::SetGameScene()
{
	SetDash();
}

void TutorialEnemy::SetMovePhase()
{
	SetStand();
}

void TutorialEnemy::AddEnemy(XMFLOAT3 pos)
{
	//�����Ԃ点��
	isDead1 = false;
	isDead2 = false;
	isDead3 = false;
	deadTimer = 0;
	HP = maxHP;
	//�w��̍��W�ɔz�u
	position = pos;
}

void TutorialEnemy::AddEnemyGameScene(XMFLOAT3 pos)
{
	//�܂�����łȂ��ꍇ�X���[
	if (isDead2 == false)return;
	SetDash();
	AddEnemy(pos);
}

void TutorialEnemy::AddEnemyMovePhase(XMFLOAT3 pos)
{
	//�܂�����łȂ��ꍇ�X���[
	if (isDead2 == false)return;
	SetStand();
	AddEnemy(pos);
}

void TutorialEnemy::Reset()
{
	HP = maxHP;
	isDead1 = false;
	isDead2 = false;
	isDead3 = false;
	deadTimer = 0;
}

void TutorialEnemy::HitBullet1()
{
	//��e�t���O�𗧂Ă�
	hitFlag1 = true;
}

void TutorialEnemy::SetHitPlayer()
{
	isDead1 = true;
}

bool TutorialEnemy::GetCallFlag()
{
	if (isDead2 == true)
	{
		callTimer++;
		if (callTimer >= callTime)
		{
			callTimer = 0;
			return true;
		}
	}
	return false;
}

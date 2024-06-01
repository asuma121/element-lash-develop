#include "TutorialEnemy.h"
#include "mathOriginal.h"
#include "FbxLoader.h"
#include "imgui.h"
#include "ColliderManager.h"
#define G 6.674	//���L���͒萔
#define GAcceleration 9.80665 * 1/10	//�d�͉����x

Camera* TutorialEnemy::camera = nullptr;

TutorialEnemy::~TutorialEnemy()
{
	delete object;
	delete modelDash;
	delete modelDown;
	delete modelStand;
	delete hpBar1;
	delete hpBar2;
	delete hpBar3;
	delete hpBar4;
}


void TutorialEnemy::Initialize()
{
	//HP�o�[�̃X�v���C�g
	hpBar1 = new Sprite();
	hpBar1->Initialize();
	hpBar1->SetTextureNum(58);
	hpBar2 = new Sprite();
	hpBar2->Initialize();
	hpBar2->SetTextureNum(59);
	hpBar3 = new Sprite();
	hpBar3->Initialize();
	hpBar3->SetTextureNum(60);
	hpBar4 = new Sprite();
	hpBar4->Initialize();
	hpBar4->SetTextureNum(61);

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
	if (isDead2 == true)return;

	//�R���C�_�[�X�V
	UpdateCollider();

	//�X�v���C�g�X�V
	UpdateSprite();

	//�_�b�V����
	if (tutorialFlag == 11)
	{
		//�X�e�[�g�X�V
		UpdateStateTutorial();
		//�v���C���[�Ɍ������đ���
		if(tutorialDashFlag == false)MoveGame();
		//�I�u�W�F�N�g�Ƃ̓����蔻����Ƃ�
		UpdateHitObject();
	}

	//�]��ł���Œ�
	if (tutorialFlag == 12)
	{
		//�`���[�g���A��12�p�̍X�V
		UpdateTutorial12();
		//�`���[�g���A��12�p�_���[�W�X�V
		UpdateDamageTutorial();
	}

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

void TutorialEnemy::UpdateStateTutorial()
{
	//�_�b�V���V�[���Ɉڂ�����
	if (tutorialDashFlag == true && length(position - playerPos) >= 20)
	{
		tutorialDashFlag = false;
		SetDash();
	}
	else if (tutorialDashFlag == false && length(position - playerPos) < 20)
	{
		tutorialDashFlag = true;
		SetStand();
	}
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
	//�R���C�_�[�f�[�^�X�V
	colliderData.scale = colliderScale;
	colliderData.rotation = rotation;
	colliderData.center = position;
}

void TutorialEnemy::UpdateObjectCollider()
{
	for (int i = 0; i < objectColliderData.size(); i++)
	{
		//�ǂƂ̓����蔻�菈��
		if (objectColliderData[i].objectName.substr(0, 4) == "wall")
		{
			UpdateHitWall(objectColliderData[i]);
		}
		//�ǂƂ̓����蔻�菈��
		if (objectColliderData[i].objectName.substr(0, 6) == "piller")
		{
			UpdateHitPiller(objectColliderData[i]);
		}
	}
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

void TutorialEnemy::UpdateDamageTutorial()
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
	if (isDead3 == true)return;
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
	hitFlag1 = false;
	hitElec = false;
	hitObjectFlag = false;
	downFlag = false;
	tutorial12Timer = 0;
	SetStand();
}

void TutorialEnemy::SetGameScene()
{
	SetDash();
}

void TutorialEnemy::SetMovePhase()
{
	//�G����
	isDead1 = true;
	isDead2 = true;
	isDead3 = true;
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

void TutorialEnemy::AddEnemyTutorialScene(XMFLOAT3 pos)
{
	//�܂�����łȂ��ꍇ�X���[
	if (isDead2 == false)return;
	downFlag = false;
	tutorialDashFlag = false;
	SetStand();
	AddEnemy(pos);
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

void TutorialEnemy::UpdateHitWall(JSONLoader::ColliderData objectColliderData)
{
	//�ǂ̒��ɂ����珈���I��
	if (ColliderManager::CheckCollider(colliderData, objectColliderData, true) == true)return;

	//�ǂ̊O�ɂ��鎞�̂�
	while (ColliderManager::CheckCollider(colliderData, objectColliderData, true) == false)
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

void TutorialEnemy::UpdateHitPiller(JSONLoader::ColliderData objectColliderData)
{
	//���ɏՓ˂��ĂȂ������珈���I��
	if (ColliderManager::CheckCollider(colliderData, objectColliderData) == false)return;

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

void TutorialEnemy::UpdateHitObject()
{
	//�I�u�W�F�N�g�ɓ������ĂȂ�������X�L�b�v
	if (hitObjectFlag != true)return;

	//�_�E�����f�����Z�b�g
	SetDown();

	//�`���[�g���A���V�[���ɑ���p
	downFlag = true;

	hitObjectFlag = false;
}

void TutorialEnemy::UpdateTutorial12()
{
	//�^�C�}�[�X�V
	tutorial12Timer++;

	//�|��Ă���Ƃ��ɃA�j���[�V�������~�߂�
	if (tutorial12Timer >= frameFallDownEnemy)
	{
		object->StopAnimation();
	}
}

#include "TutorialScene.h"
#include "mathOriginal.h"
#include "ColliderManager.h"
#include "GameScene.h"

KeyManager* TutorialScene::keyManager = nullptr;
DirectXCommon* TutorialScene::dxCommon = nullptr;
Camera* TutorialScene::camera = nullptr;
Light* TutorialScene::light = nullptr;
Player* TutorialScene::player = nullptr;
Enemy* TutorialScene::enemy = nullptr;
TutorialEnemy* TutorialScene::tutorialEnemy = nullptr;
Plane* TutorialScene::plane = nullptr;
Terrain* TutorialScene::terrain = nullptr;
UI* TutorialScene::ui = nullptr;

TutorialScene::TutorialScene() 
{
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::Initialize()
{
	//�V�[���@�ۂ����^�C�~���O�ŏ�����
	if (gameTimer == 0)
	{
		//�v���C���[���`���[�g���A���p�ɃZ�b�g
		player->SetTutorial();

		//�G���`���[�g���A���p�ɃZ�b�g
		enemy->SetTutorial();

		//�`���[�g���A���̓G���Z�b�g
		tutorialEnemy->SetTutorial();

		//UI���Z�b�g
		ui->SetTutorial();
	}
}

void TutorialScene::Update()
{
	if (gameTimer == 0.0f)
	{
		player->SetPosition(XMFLOAT3(0.0f, 0.0f, 0.0f));
	}
	gameTimer += 1.0f;

	//�X�v���C�g�X�V
	UpdateSprite();

	//�p�[�e�B�N���X�V
	UpdateParticle();

	//�I�u�W�F�N�g�X�V
	UpdateObject();

	//�R���C�_�[�X�V
	UpdateCollider();

	//�J�����X�V
	if (tutorialSpriteFlag == 15)
	{
		camera->UpdateTutorial(tutorial13Timer);
	}
	else
	{
		camera->UpdatePlayer(player->GetPosition(), player->GetRotation0());
	}
	/*camera_->DebugUpdate();*/
	camera->Update();
}

void TutorialScene::NextScene(Scene* pScene)
{
	if (moveGameFlag)
	{
		pScene->ChangeScene(new GameScene());
	}
}

void TutorialScene::UpdateObject()
{
	//���C�g
	light->SetEye(XMFLOAT3(lightPos) + player->GetPosition());
	light->SetTarget(XMFLOAT3(lightTarget) + player->GetPosition());
	light->SetDir(XMFLOAT3(lightDir));
	light->Update();

	//�G
	enemy->UpdateTutorial(tutorial13Timer);

	//�`���[�g���A���̓G
	tutorialEnemy->SetPlayerPos(player->GetPosition());
	tutorialEnemy->SetTutorialFlag(tutorialSpriteFlag);
	tutorialEnemy->UpdateTutorial();
	//�G��|�����玟��
	if (tutorialEnemy->GetIsDead() && tutorialSpriteFlag == 10)
	{
		tutorialSpriteFlag = 11;
	}

	//UI
	ui->SetTutorialFlag(tutorialSpriteFlag);
	ui->SetPlayerForm(player->GetPlayerForm(),player->GetFormChangeFlag());
	ui->SetTutorialTimer(tutorialLStickTimer, tutorialLStickMaxTime, tutorialRStickTimer, tutorialRStickMaxTime,
		tutorialAttackTimer, tutorialAttackMaxTime, tutorialAttack2Timer
		, tutorialAttack2MaxTime,tutorialIikannjiTimer, tutorialIikannjiMaxTime,tutorial12Timer, tutorial12MaxTime,
		tutorial13Timer, tutorial13MaxTime);
	ui->UpdateTutorial();

	//�v���C���[
	player->SetEnemyPos(tutorialEnemy->GetPosition(), tutorialEnemy->GetAddPos());
	player->SetTutorialFlag(tutorialSpriteFlag);
	player->UpdateTutorial();

	//��
	plane->Update();

	//�n�`
	terrain->Update();
}

void TutorialScene::UpdateSprite()
{
	//�X�L�b�v
	if (tutorialSpriteFlag < 14 && keyManager->TriggerKey(KeyManager::PAD_START))
	{
		tutorialSpriteFlag = 14;
	}
	//�X�v���C�g�̏���
	//����
	if (tutorialSpriteFlag == 1)
	{
		blackSpriteTimer++;
		//���Ԍo�߂ŃX�e�B�b�N����`���[�g���A����
		if (blackSpriteTimer >= blackSpriteMaxTime)
		{
			blackSpriteTimer = 0;
			tutorialSpriteFlag = 2;
		}
	}
	//�X�e�B�b�N����`���[�g���A��
	if (tutorialSpriteFlag == 2)
	{
		//R�X�e�B�b�N�̓��͂�����΃^�C�}�[�X�V
		if (keyManager->GetStick(KeyManager::RStickX) >= 0.4 || keyManager->GetStick(KeyManager::RStickX) <= -0.4 ||
			keyManager->GetStick(KeyManager::RStickY) >= 0.4 || keyManager->GetStick(KeyManager::RStickY) <= -0.4)
		{
			tutorialRStickTimer++;
		}
		//L�X�e�B�b�N�̓��͂�����΃^�C�}�[�X�V
		if (keyManager->GetStick(KeyManager::LStickX) >= 0.4 || keyManager->GetStick(KeyManager::LStickX) <= -0.4 ||
			keyManager->GetStick(KeyManager::LStickY) >= 0.4 || keyManager->GetStick(KeyManager::LStickY) <= -0.4)
		{
			tutorialLStickTimer++;
		}
		//�ǂ������B���Ŏ���
		if (tutorialLStickTimer >= tutorialLStickMaxTime && tutorialRStickTimer >= tutorialRStickMaxTime)
		{
			tutorialSpriteFlag = 3;
		}
	}
	//���������`���[�g���A��
	if (tutorialSpriteFlag == 3)
	{
		tutorialIikannjiTimer++;
		//���Ԍo�߂ōU���`���[�g���A����
		if (tutorialIikannjiTimer >= tutorialIikannjiMaxTime)
		{
			tutorialIikannjiTimer = 0;
			tutorialSpriteFlag = 4;
		}
	}
	//�U���`���[�g���A��
	if (tutorialSpriteFlag == 4)
	{
		if (keyManager->PushKey(KeyManager::PAD_RIGHT_SHOULDER) == 1)
		{
			tutorialAttackTimer++;
		}
		//�B���Ŏ���
		if (tutorialAttackTimer >= tutorialAttackMaxTime)
		{
			tutorialSpriteFlag = 5;
		}
	}
	//���������`���[�g���A��
	if (tutorialSpriteFlag == 5)
	{
		tutorialIikannjiTimer++;
		//���Ԍo�߂ōU���`���[�g���A����
		if (tutorialIikannjiTimer >= tutorialIikannjiMaxTime)
		{
			tutorialIikannjiTimer = 0;
			tutorialSpriteFlag = 6;
		}
	}
	//�����ω��`���[�g���A��
	if (tutorialSpriteFlag == 6)
	{
		if (keyManager->PushKey(KeyManager::PAD_LEFT_SHOULDER) == 1)
		{
			tutorialSpriteFlag = 7;
		}
	}
	//�����ω��`���[�g���A��2
	if (tutorialSpriteFlag == 7)
	{
		tutorialIikannjiTimer++;
		//���Ԍo�߂ōU���`���[�g���A����
		if (tutorialIikannjiTimer >= tutorialIikannjiMaxTime)
		{
			tutorialIikannjiTimer = 0;
			tutorialSpriteFlag = 8;
		}
	}
	//�U���`���[�g���A��
	if (tutorialSpriteFlag == 8)
	{
		if (keyManager->TriggerKey(KeyManager::PAD_RIGHT_SHOULDER) == 1)
		{
			tutorialAttack2Timer++;
		}
		//�B���Ŏ���
		if (tutorialAttack2Timer >= tutorialAttack2MaxTime)
		{
			tutorialSpriteFlag = 9;
		}
	}
	//�����ω��`���[�g���A��2
	if (tutorialSpriteFlag == 9)
	{
		tutorialIikannjiTimer++;
		//���Ԍo�߂ōU���`���[�g���A����
		if (tutorialIikannjiTimer >= tutorialIikannjiMaxTime)
		{
			//�J�����̌����̃x�N�g���擾
			//�J���������ɓG�z�u
			tutorialIikannjiTimer = 0;
			tutorialEnemy->AddEnemyTutorialScene(XMFLOAT3(0.0f,0.0f,0.0f));
			tutorialSpriteFlag = 10;
		}
	}
	//�G���o�ꂵ��
	if (tutorialSpriteFlag == 10)
	{
		tutorial10Timer++;
		//���Ԍo�߂ōU���`���[�g���A����
		if (tutorial10Timer >= tutorial10MaxTime)
		{
			tutorialSpriteFlag = 11;
			tutorial10Timer = 0;
			//�_�b�V���t���O���Z�b�g����
			tutorialEnemy->SetTutorialDashFlag();
		}
	}
	//�����Ă���
	if (tutorialSpriteFlag == 11)
	{
		//���ɂԂ��ē|�����玟��
		if (tutorialEnemy->GetTutorialDownFlag())
		{
			tutorialSpriteFlag = 12;
		}
	}
	//�G���|��Ă��邤���ɍU��
	if (tutorialSpriteFlag == 12)
	{
		//�G��|�����玟�ֈړ�
		if (tutorialEnemy->GetIsDead() == true)
		{
			tutorialSpriteFlag = 13;
		}
	}
	//�G��|�����I
	if (tutorialSpriteFlag == 13)
	{
		tutorialIikannjiTimer++;
		//���Ԍo�߂Ń`���[�g���A���I��
		if (tutorialIikannjiTimer >= tutorialIikannjiMaxTime)
		{
			tutorialSpriteFlag = 14;
			tutorialIikannjiTimer = 0;
		}
	}
	//�{�X�o��܂ł̊� 
	if (tutorialSpriteFlag == 14)
	{
		tutorial12Timer++;
		//���Ԍo�߂Ń`���[�g���A���I��
		if (tutorial12Timer >= tutorial12MaxTime)
		{
			tutorialSpriteFlag = 15;
		}
	}
	//�{�X�o��
	if (tutorialSpriteFlag == 15)
	{
		tutorial13Timer++;
		//����
		if (tutorial13Timer >= tutorial13MaxTime)
		{
			blackSpriteTimer++;
		}
		//���Ԍo�߂Ń`���[�g���A���I��
		if (tutorial13Timer >= tutorial13MaxTime + blackSpriteMaxTime)
		{
			//���Z�b�g
			Reset();
			//�v���C���[���Q�[���ɃZ�b�g
			player->SetGameScene();
			//�G���Q�[���ɃZ�b�g
			enemy->SetGameScene();
			//�Q�[���Ɉڂ�
			moveGameFlag = true;
		}
	}
}

void TutorialScene::UpdateCollider()
{
	//�J���������蔻��X�V
	camera->SetObjectCollider(terrain->GetColliderData());

	//�G�̓����蔻��X�V
	tutorialEnemy->SetObjectCollider(terrain->GetColliderData());
	tutorialEnemy->UpdateObjectCollider();

	//�v���C���[�����蔻��X�V
	player->SetObjectCollider(terrain->GetColliderData());
	player->UpdateCollider();

	//���@�̒e(��)�ƓG�̓����蔻��
	for (int i = 0; i < player->GetBullet1Num(); i++)
	{
		if (ColliderManager::CheckCollider(tutorialEnemy->GetColliderData(), player->GetBullet1ColliderData(i)))
		{
			//�G�Ƀq�b�g�t���O���M
			tutorialEnemy->HitBullet1();
			//���@�Ƀq�b�g�t���O���M
			player->HitBullet1(i);
		}
	}

	//���U��������������
	if (player->GetHitElec())
	{
		//�G�Ƀq�b�g�t���O���M
		tutorialEnemy->HitElec();
	}
}

void TutorialScene::UpdateParticle()
{
}

void TutorialScene::Reset()
{
	//�^�C�}�[���Z�b�g
	blackSpriteTimer = 0;
	tutorialLStickTimer = 0;
	tutorialRStickTimer = 0;
	tutorialIikannjiTimer = 0;
	tutorialAttackTimer = 0;
	tutorialAttack2Timer = 0;
	tutorial12Timer = 0;
	tutorial13Timer = 0;
	//�t���O�����ɖ߂�
	tutorialSpriteFlag = 1;
}

void TutorialScene::Draw()
{
	//FBX�`��
	DrawFBX();

	//�p�[�e�B�N���`��
	DrawParticle();

	//�X�v���C�g�`��
	DrawSprite();
}

void TutorialScene::DrawFBX()
{
	//�I�u�W�F�N�g�`��
	player->Draw(dxCommon->GetCommandList());
	enemy->Draw(dxCommon->GetCommandList());
	tutorialEnemy->Draw(dxCommon->GetCommandList());
	plane->Draw(dxCommon->GetCommandList());
	terrain->Draw(dxCommon->GetCommandList());

	//�X�e�[�g�X�V
	player->UpdateState();
	enemy->UpdateStateTutorial();
}

void TutorialScene::DrawSprite()
{
	//UI�`��
	ui->DrawTutorial(dxCommon->GetCommandList());
	player->DrawSpriteTutorial(dxCommon->GetCommandList());
	if(tutorialSpriteFlag == 10 || tutorialSpriteFlag == 11 || tutorialSpriteFlag == 12)tutorialEnemy->DrawSprite(dxCommon->GetCommandList());
}

void TutorialScene::DrawParticle()
{
	//�v���C���[�̃p�[�e�B�N���`��
	player->DrawParticle(dxCommon->GetCommandList());
}

void TutorialScene::DrawFBXLightView()
{
	player->DrawLightView(dxCommon->GetCommandList());
	enemy->DrawLightView(dxCommon->GetCommandList());
	tutorialEnemy->DrawLightView(dxCommon->GetCommandList());
}

void TutorialScene::SetSRV(ID3D12DescriptorHeap* SRV)
{
	player->SetSRV(SRV);
	enemy->SetSRV(SRV);
	tutorialEnemy->SetSRV(SRV);
	plane->SetSRV(SRV);
}

void TutorialScene::SetDevice(DirectXCommon* dxCommon, KeyManager* keyManager)
{
	// ����������
	TutorialScene::dxCommon = dxCommon;
	TutorialScene::keyManager = keyManager;
}

void TutorialScene::SetGameObject(Player* player, Enemy* enemy, TutorialEnemy* tutorialEnemy,
	Plane* plane, Terrain* terrain, Camera* camera, Light* light, UI* ui)
{
	TutorialScene::player = player;
	TutorialScene::enemy = enemy;
	TutorialScene::tutorialEnemy = tutorialEnemy;
	TutorialScene::plane = plane;
	TutorialScene::terrain = terrain;
	TutorialScene::camera = camera;
	TutorialScene::light = light;
	TutorialScene::ui = ui;
}

DirectX::XMMATRIX TutorialScene::GetLightViewProjection()
{
	return light->GetMatViewProjection();
}

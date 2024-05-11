#include "TutorialScene.h"
#include "mathOriginal.h"
#include "ColliderManager.h"
#include "GameScene.h"

DXInput* TutorialScene::dxInput = nullptr;
Input* TutorialScene::input = nullptr;
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
		//�����X�v���C�g1
		Sprite* newBlackSprite1 = new Sprite();
		newBlackSprite1->Initialize();
		blackSprite1.reset(newBlackSprite1);
		blackSprite1->SetTextureNum(14);
		blackSprite1->SetPosition(black1Pos);
		blackSprite1->SetScale(black1Scale);
		//�����X�v���C�g2
		Sprite* newBlackSprite2 = new Sprite();
		newBlackSprite2->Initialize();
		blackSprite2.reset(newBlackSprite2);
		blackSprite2->SetTextureNum(14);
		blackSprite2->SetPosition(black2Pos);
		blackSprite2->SetScale(black2Scale);
		//�����X�v���C�g2
		Sprite* newBlackSprite3 = new Sprite();
		newBlackSprite3->Initialize();
		blackSprite3.reset(newBlackSprite3);
		blackSprite3->SetTextureNum(14);
		blackSprite3->SetPosition(black3Pos);
		blackSprite3->SetScale(black3Scale);
	}
}

void TutorialScene::Update()
{
	if (gameTimer == 0.0f)
	{
		player->SetPosition(XMFLOAT3(0.0f, 0.0f, 0.0f));
	}
	gameTimer += 1.0f;

	//�I�u�W�F�N�g�X�V
	UpdateObject();

	//�X�v���C�g�X�V
	UpdateSprite();

	//�R���C�_�[�X�V
	UpdateCollider();

	//�p�[�e�B�N���X�V
	UpdateParticle();
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
	//�J�����X�V
	if (tutorialSpriteFlag == 13)
	{
		camera->UpdateTutorial(tutorial13Timer);
	}
	else
	{
		camera->UpdatePlayer(player->GetPosition(), player->GetRotation0());
	}
	/*camera_->DebugUpdate();*/
	camera->Update();

	//���C�g
	light->SetEye(XMFLOAT3(lightPos) + player->GetPosition());
	light->SetTarget(XMFLOAT3(lightTarget) + player->GetPosition());
	light->SetDir(XMFLOAT3(lightDir));
	light->Update();

	//�G
	enemy->UpdateTutorial(tutorial13Timer);

	//�`���[�g���A���̓G
	if (tutorialSpriteFlag == 10)
	{
		tutorialEnemy->Update();
		//�G��|�����玟��
		if (tutorialEnemy->GetIsDead())
		{
			tutorialSpriteFlag = 11;
			tutorialEnemy->Reset();
		}
	}

	//UI
	ui->SetTutorialFlag(tutorialSpriteFlag);
	ui->SetPlayerForm(player->GetPlayerForm(),player->GetFormChangeFlag());
	ui->SetTutorialTimer(tutorialLStickTimer, tutorialLStickMaxTime, tutorialRStickTimer, tutorialRStickMaxTime,
		tutorialAttackTimer, tutorialAttackMaxTime, tutorialAttack2Timer
		, tutorialAttack2MaxTime,tutorialIikannjiTimer, tutorialIikannjiMaxTime,tutorial12Timer, tutorial12MaxTime);
	ui->UpdateTutorial();

	//�v���C���[
	player->SetEnemyPos(tutorialEnemy->GetPosition());
	player->SetEnemyPos(enemy->GetPosition());
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
	if (tutorialSpriteFlag < 12 && dxInput->TriggerKey(DXInput::PAD_START))
	{
		tutorialSpriteFlag = 12;
	}
	//�X�v���C�g�̏���
	//����
	if (tutorialSpriteFlag == 1)
	{
		blackSpriteTimer++;
		blackSprite3->SetAlpha((blackSpriteMaxTime - blackSpriteTimer) / blackSpriteMaxTime);
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
		if (dxInput->GetStick(DXInput::RStickX) >= 0.4 || dxInput->GetStick(DXInput::RStickX) <= -0.4 ||
			dxInput->GetStick(DXInput::RStickY) >= 0.4 || dxInput->GetStick(DXInput::RStickY) <= -0.4)
		{
			tutorialRStickTimer++;
		}
		//L�X�e�B�b�N�̓��͂�����΃^�C�}�[�X�V
		if (dxInput->GetStick(DXInput::LStickX) >= 0.4 || dxInput->GetStick(DXInput::LStickX) <= -0.4 ||
			dxInput->GetStick(DXInput::LStickY) >= 0.4 || dxInput->GetStick(DXInput::LStickY) <= -0.4)
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
		if (dxInput->PushKey(DXInput::PAD_RIGHT_SHOULDER) == 1)
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
		if (dxInput->PushKey(DXInput::PAD_LEFT_SHOULDER) == 1)
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
		if (dxInput->TriggerKey(DXInput::PAD_RIGHT_SHOULDER) == 1)
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
			XMFLOAT3 velo = camera->GetTarget() - camera->GetEye();
			velo = normalize(velo);
			velo = velo * 20.0f;
			//�J���������ɓG�z�u
			tutorialEnemy->SetPosition({ velo.x,0.0f, velo.z });
			tutorialSpriteFlag = 10;
		}
	}
	//���������`���[�g���A��
	if (tutorialSpriteFlag == 11)
	{
		tutorialIikannjiTimer++;
		//���Ԍo�߂Ń`���[�g���A���I��
		if (tutorialIikannjiTimer >= tutorialIikannjiMaxTime)
		{
			tutorialSpriteFlag = 12;
			tutorialIikannjiTimer = 0;
		}
	}
	//�G�o��܂ł̊�
	if (tutorialSpriteFlag == 12)
	{
		tutorial12Timer++;
		//���Ԍo�߂Ń`���[�g���A���I��
		if (tutorial12Timer >= tutorial12MaxTime)
		{
			tutorialSpriteFlag = 13;
		}
	}
	if (tutorialSpriteFlag == 13)
	{
		tutorial13Timer++;
		//����
		if (tutorial13Timer >= tutorial13MaxTime)
		{
			blackSpriteTimer++;
		}
		blackSprite3->SetAlpha(blackSpriteTimer / blackSpriteMaxTime);
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
	//�X�v���C�g�X�V
	blackSprite1->Update();
	blackSprite2->Update();
	blackSprite3->Update();
}

void TutorialScene::UpdateCollider()
{
	//���O����
	ColliderManager::PreUpdate();

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

	//�㏈��
	ColliderManager::PostUpdate();
}

void TutorialScene::UpdateParticle()
{
}

void TutorialScene::Reset()
{
	//�^�C�}�[���Z�b�g
	blackSpriteTimer = 0;
	tutorialLStickTimer = 0.0f;
	tutorialRStickTimer = 0.0f;
	tutorialIikannjiTimer = 0.0f;
	tutorialAttackTimer = 0.0f;
	tutorialAttack2Timer = 0.0f;
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

	ColliderManager::Draw(dxCommon->GetCommandList());
}

void TutorialScene::DrawFBX()
{
	player->Draw(dxCommon->GetCommandList());
	enemy->Draw(dxCommon->GetCommandList());
	if (tutorialSpriteFlag == 10)tutorialEnemy->Draw(dxCommon->GetCommandList());
	plane->Draw(dxCommon->GetCommandList());
	terrain->Draw(dxCommon->GetCommandList());
}

void TutorialScene::DrawSprite()
{
	//����
	if (tutorialSpriteFlag == 13)
	{
		blackSprite1->Draw(dxCommon->GetCommandList());
		blackSprite2->Draw(dxCommon->GetCommandList());
	}
	if (tutorialSpriteFlag == 1 || tutorialSpriteFlag == 13)
	{
		blackSprite3->Draw(dxCommon->GetCommandList());
	}
	//UI�`��
	ui->DrawTutorial(dxCommon->GetCommandList());
	player->DrawSpriteTutorial(dxCommon->GetCommandList());
	if(tutorialSpriteFlag == 10)tutorialEnemy->DrawSprite(dxCommon->GetCommandList());
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
	if (tutorialSpriteFlag == 10)tutorialEnemy->DrawLightView(dxCommon->GetCommandList());
}

void TutorialScene::SetSRV(ID3D12DescriptorHeap* SRV)
{
	player->SetSRV(SRV);
	enemy->SetSRV(SRV);
	if (tutorialSpriteFlag == 10)tutorialEnemy->SetSRV(SRV);
	plane->SetSRV(SRV);
}

void TutorialScene::SetDevice(DirectXCommon* dxCommon, Input* input, DXInput* dxInput)
{
	// ����������
	TutorialScene::dxCommon = dxCommon;
	TutorialScene::input = input;
	TutorialScene::dxInput = dxInput;
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

//void TutorialScene::SetGameObject(Player* player, Enemy* enemy, TutorialEnemy* tutorialEnemy, Plane* plane, Camera* camera, Light* light, UI* ui)
//{
//	this->player = player;
//	this->enemy = enemy;
//	this->tutorialEnemy = tutorialEnemy;
//	this->plane = plane;
//	this->camera = camera;
//	this->light = light;
//	this->ui = ui;
//}

DirectX::XMMATRIX TutorialScene::GetLightViewProjection()
{
	return light->GetMatViewProjection();
}

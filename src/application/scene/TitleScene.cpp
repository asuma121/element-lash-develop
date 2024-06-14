#include "TitleScene.h"
#include "mathOriginal.h"
#include "imgui.h"
#include "TutorialScene.h"

KeyManager* TitleScene::keyManager = nullptr;
DirectXCommon* TitleScene::dxCommon = nullptr;
Camera* TitleScene::camera = nullptr;
Light* TitleScene::light = nullptr;
Player* TitleScene::player = nullptr;
Enemy* TitleScene::enemy = nullptr;
Plane* TitleScene::plane = nullptr;
UI* TitleScene::ui = nullptr;
Terrain* TitleScene::terrain = nullptr;

TitleScene::TitleScene()
{
}
 
TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	//�V�[���J�ڎ��ɏ�����
	if (sceneTimer == 0)
	{
		//�v���C���[���^�C�g���p�ɃZ�b�g
		player->SetTitle();

		//�G���^�C�g���p�ɃZ�b�g
		enemy->SetTitle();

		//�J�������^�C�g���p�ɃZ�b�g
		camera->SetTitle();
	}
}

void TitleScene::Update()
{
	//�^�C�g���ɖ߂������Ƀt���O���Z�b�g
	if (sceneTimer == 0)
	{
		moveTutorialFlag1 = false;
	}

	//�^�C�}�[�X�V
	sceneTimer++;

	//�I�u�W�F�N�g�X�V
	UpdateObject();

	//�X�v���C�g�X�V
	UpdateSprite();

	//�V�[���J�ڍX�V
	UpdateMoveScene();
}

void TitleScene::NextScene(Scene* pScene)
{
	if (moveTutorialFlag1)
	{
		Reset();
		pScene->ChangeScene(new TutorialScene());
	}
}

void TitleScene::UpdateObject()
{
	//�J�����X�V
	camera->SetPhaseTimer(moveTutorialTimer);
	camera->SetPlayerPos(player->GetPosition());
	camera->SetPlayerRot(player->GetRotation0());
	camera->Update();

	//���C�g
	lightTarget[0] = player->GetPosition().x + 25;
	lightTarget[1] = player->GetPosition().y + 25;
	lightTarget[2] = player->GetPosition().z + 25;
	lightPos[0] = player->GetPosition().x;
	lightPos[1] = player->GetPosition().y;
	lightPos[2] = player->GetPosition().z;
	light->SetEye(XMFLOAT3(lightPos));
	light->SetTarget(XMFLOAT3(lightTarget));
	light->SetDir(XMFLOAT3(lightDir));
	light->Update();

	//�I�u�W�F�N�g
	terrain->Update();

	//UI�̍X�V
	ui->SetTitleTimer(moveTutorialTimer, titleMoveTime);
	ui->UpdateTitle();

	//���X�V
	plane->Update();

	//�G�X�V
	enemy->UpdateTitle();

	//�v���C���[
	player->UpdateTitle((float)moveTutorialTimer);
}

void TitleScene::UpdateSprite()
{
}

void TitleScene::UpdateMoveScene()
{
	//�X�y�[�X��A�{�^�������ꂽ��
	if (keyManager->TriggerKey(KeyManager::PAD_A) && sceneTimer >= 100)
	{
		//�V�[���J�ڃt���O�I��
		moveTutorialFlag2 = true;
	}
	//�V�[���J�ڃt���O����������
	if (moveTutorialFlag2)
	{
		//�^�C�}�[���Z
		moveTutorialTimer++;
		//�^�C�}�[���K��̃^�C���ɒB������
		if (moveTutorialTimer >= moveTutorialTime)
		{
			//���Z�b�g
			Reset();
			//���[�h���Q�[����
			moveTutorialFlag1 = true;
		}
	}
}

void TitleScene::Reset()
{
	//�^�C�}�[�����ɖ߂�
	moveTutorialTimer = 0;
	sceneTimer = 0;
	//�t���O�����ɖ߂�
	moveTutorialFlag2 = false;
}

void TitleScene::Draw()
{
	//FBX�`��
	DrawFBX();

	//�p�[�e�B�N���`��
	DrawParticle();

	//�X�v���C�g�`��
	DrawSprite();
}

void TitleScene::DrawFBX()
{
	player->Draw(dxCommon->GetCommandList());
	plane->Draw(dxCommon->GetCommandList());
	enemy->Draw(dxCommon->GetCommandList());
	terrain->Draw(dxCommon->GetCommandList());

	enemy->UpdateStateTitle();
}

void TitleScene::DrawSprite()
{
	//UI�`��
	ui->DrawTitle(dxCommon->GetCommandList());
}

void TitleScene::DrawParticle()
{
	//�v���C���[�̃p�[�e�B�N���`��
	player->DrawParticle(dxCommon->GetCommandList());
}

void TitleScene::DrawFBXLightView()
{
	player->DrawLightView(dxCommon->GetCommandList());
	enemy->DrawLightView(dxCommon->GetCommandList());
}

void TitleScene::SetDevice(DirectXCommon* dxCommon, KeyManager* keyManager)
{
	//����������
	TitleScene::dxCommon = dxCommon;
	TitleScene::keyManager = keyManager;
}

void TitleScene::SetGameObject(Player* player, Enemy* enemy, Plane* plane, Terrain* terrain, Camera* camera, Light* light, UI* ui)
{
	TitleScene::player = player;
	TitleScene::enemy = enemy;
	TitleScene::plane = plane;
	TitleScene::terrain = terrain;
	TitleScene::camera = camera;
	TitleScene::light = light;
	TitleScene::ui = ui;
}

DirectX::XMMATRIX TitleScene::GetLightViewProjection()
{
	return light->GetMatViewProjection();
}

#include "DevelopScene.h"
#include "mathOriginal.h"
#include "imgui.h"

KeyManager* DevelopScene::keyManager = nullptr;
DirectXCommon* DevelopScene::dxCommon = nullptr;
Camera* DevelopScene::camera = nullptr;
Light* DevelopScene::light = nullptr;
Player* DevelopScene::player = nullptr;
Enemy* DevelopScene::enemy = nullptr;
Plane* DevelopScene::plane = nullptr;
UI* DevelopScene::ui = nullptr;
Terrain* DevelopScene::terrain = nullptr;

DevelopScene::DevelopScene()
{
}
 
DevelopScene::~DevelopScene()
{
}

void DevelopScene::Initialize()
{
	//�V�[���J�ڎ��ɏ�����
	if (sceneTimer == 0)
	{
		//�v���C���[���^�C�g���p�ɃZ�b�g
		player->SetDevelop();

		//�G���^�C�g���p�ɃZ�b�g
		enemy->SetTitle();

		//�J�������f�o�b�O�p�ɃZ�b�g
		camera->SetDevelop();
	}
}

void DevelopScene::Update()
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

void DevelopScene::NextScene(Scene* pScene)
{
}

void DevelopScene::UpdateObject()
{
	//�J�����X�V
	camera->SetPhaseTimer(moveTutorialTimer);
	camera->SetPlayerPos(player->GetPosition());
	camera->SetPlayerRot(player->GetRotation0());
	camera->Update();

	//���C�g
	light->SetEye(XMFLOAT3(lightPos));
	light->SetTarget(XMFLOAT3(lightTarget));
	light->SetDir(XMFLOAT3(lightDir));
	light->Update();

	//�I�u�W�F�N�g
	terrain->Update();

	//���X�V
	plane->Update();

	////�G�X�V
	//enemy->Update();

	//�v���C���[
	player->Update();
}

void DevelopScene::UpdateSprite()
{
}

void DevelopScene::UpdateMoveScene()
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

void DevelopScene::Reset()
{
	//�^�C�}�[�����ɖ߂�
	moveTutorialTimer = 0;
	sceneTimer = 0;
	//�t���O�����ɖ߂�
	moveTutorialFlag2 = false;
}

void DevelopScene::Draw()
{
	//FBX�`��
	DrawFBX();

	//�p�[�e�B�N���`��
	DrawParticle();

	//�X�v���C�g�`��
	DrawSprite();
}

void DevelopScene::DrawFBX()
{
	player->Draw(dxCommon->GetCommandList());
	plane->Draw(dxCommon->GetCommandList());
	/*enemy->Draw(dxCommon->GetCommandList());*/
	terrain->Draw(dxCommon->GetCommandList());

	/*player->UpdateState();*/
	enemy->UpdateState();
}

void DevelopScene::DrawSprite()
{
}

void DevelopScene::DrawParticle()
{
	//�v���C���[�̃p�[�e�B�N���`��
	player->DrawParticle(dxCommon->GetCommandList());
}

void DevelopScene::DrawFBXLightView()
{
	player->DrawLightView(dxCommon->GetCommandList());
	//enemy->DrawLightView(dxCommon->GetCommandList());
}

void DevelopScene::SetDevice(DirectXCommon* dxCommon, KeyManager* keyManager)
{
	//����������
	DevelopScene::dxCommon = dxCommon;
	DevelopScene::keyManager = keyManager;
}

void DevelopScene::SetGameObject(Player* player, Enemy* enemy, Plane* plane, Terrain* terrain, Camera* camera, Light* light, UI* ui)
{
	DevelopScene::player = player;
	DevelopScene::enemy = enemy;
	DevelopScene::plane = plane;
	DevelopScene::terrain = terrain;
	DevelopScene::camera = camera;
	DevelopScene::light = light;
	DevelopScene::ui = ui;
}

DirectX::XMMATRIX DevelopScene::GetLightViewProjection()
{
	return light->GetMatViewProjection();
}

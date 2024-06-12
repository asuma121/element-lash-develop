#include "ClearScene.h"
#include "mathOriginal.h"
#include "TitleScene.h"

KeyManager* ClearScene::keyManager = nullptr;
DirectXCommon* ClearScene::dxCommon = nullptr;
Camera* ClearScene::camera = nullptr;
Light* ClearScene::light = nullptr;
Player* ClearScene::player = nullptr;
Enemy* ClearScene::enemy = nullptr;
Plane* ClearScene::plane = nullptr;
Terrain* ClearScene::terrain = nullptr;
UI* ClearScene::ui = nullptr;

void ClearScene::SetDevice(DirectXCommon* dxCommon, KeyManager* keyManager)
{
	//����������
	ClearScene::dxCommon = dxCommon; 
	ClearScene::keyManager = keyManager;
}

void ClearScene::SetGameObject(Player* player, Enemy* enemy, Plane* plane, Terrain* terrain,Camera* camera, Light* light, UI* ui)
{
	ClearScene::player = player;
	ClearScene::enemy = enemy;
	ClearScene::plane = plane;
	ClearScene::terrain = terrain;
	ClearScene::camera = camera;
	ClearScene::light = light;
	ClearScene::ui = ui;
}

ClearScene::ClearScene()
{
}

ClearScene::~ClearScene()
{
}

void ClearScene::Initialize()
{
	//�V�[���J�ڎ��ɏ�����
	if (clearFromGameTimer == 0)
	{
		//�v���C���[���^�C�g���p�ɃZ�b�g
		enemy->SetClear();
		player->SetClear();
	}

	//�����X�v���C�g1
	Sprite* newBlackSprite1 = new Sprite();
	newBlackSprite1->Initialize();
	blackSprite1.reset(newBlackSprite1);
	blackSprite1->SetTextureNum(83);
	blackSprite1->SetPosition(black1Pos);
	blackSprite1->SetScale(black1Scale);
	//�����X�v���C�g2
	Sprite* newBlackSprite2 = new Sprite();
	newBlackSprite2->Initialize();
	blackSprite2.reset(newBlackSprite2);
	blackSprite2->SetTextureNum(83);
	blackSprite2->SetPosition(black2Pos);
	blackSprite2->SetScale(black2Scale);
	//�N���A�̃X�v���C�g1
	Sprite* newClear1Sprite = new Sprite();
	newClear1Sprite->Initialize();
	clear1Sprite.reset(newClear1Sprite);
	clear1Sprite->SetTextureNum(29);
	clear1Sprite->SetPosition(clear1Pos);
	clear1Sprite->SetScale(clear1Scale);
}

void ClearScene::Update()
{
	//�^�C�}�[�X�V
	if (clearFromGameTimer <= clearFromGameTime)
	{
		clearFromGameTimer++;
	}

	if (gameTimer == 0.0f)
	{
		player->SetPosition(XMFLOAT3(0.0f, 0.0f, 0.0f));
	}
	gameTimer += 1.0f;

	//�I�u�W�F�N�g�X�V
	UpdateObject();

	//�X�v���C�g�X�V
	UpdateSprite();

	//�p�[�e�B�N���X�V
	UpdateParticle();
}

void ClearScene::NextScene(Scene* pScene)
{
	if (moveTitleFlag)
	{
		pScene->ChangeScene(new TitleScene());
	}
}

void ClearScene::UpdateObject()
{
	if (clearFromGameTimer >= clearFromGameTime && keyManager->TriggerKey(KeyManager::PAD_X) == 1)
	{
		moveTitleFlag = true;
	}

	//�J�����X�V
	camera->SetPlayerPos(player->GetPosition());
	camera->SetPlayerRot(player->GetRotation0());
	camera->Update();

	//���C�g
	light->SetEye(XMFLOAT3(lightPos) + player->GetPosition());
	light->SetTarget(XMFLOAT3(lightTarget) + player->GetPosition());
	light->SetDir(XMFLOAT3(lightDir));
	light->Update();

	//�v���C���[
	player->UpdateGame();

	//�G
	enemy->UpdateClear((int)clearFromGameTimer);

	//�n��
	plane->Update();

	//�n�`
	terrain->Update();
}

void ClearScene::UpdateSprite()
{
	//�X�v���C�g�X�V
	blackSprite1->SetPosition(XMFLOAT2(0.0f, -620.0f));
	blackSprite1->SetScale(XMFLOAT2(1280.0f, 720.0f));
	blackSprite1->SetAlpha(1.0f);
	blackSprite2->SetPosition(XMFLOAT2(0.0f, 620.0f));
	blackSprite2->SetScale(XMFLOAT2(1280.0f, 720.0f));
	blackSprite2->SetAlpha(1.0f);
	blackSprite1->Update();
	blackSprite2->Update();
	clear1Sprite->Update();
}

void ClearScene::UpdateParticle()
{
}

void ClearScene::Draw()
{
	//FBX�`��
	DrawFBX();

	//�p�[�e�B�N���`��
	DrawParticle();

	//�X�v���C�g�`��
	DrawSprite();
}

void ClearScene::DrawFBX()
{
	player->Draw(dxCommon->GetCommandList());
	enemy->Draw(dxCommon->GetCommandList());
	plane->Draw(dxCommon->GetCommandList());
	terrain->Draw(dxCommon->GetCommandList());
}

void ClearScene::DrawSprite()
{
	blackSprite1->Draw(dxCommon->GetCommandList());
	blackSprite2->Draw(dxCommon->GetCommandList());
	if (clearFromGameTimer >= clearFromGameTime)clear1Sprite->Draw(dxCommon->GetCommandList());

	//�X�e�[�g�X�V
	enemy->UpdateStateClear();
}

void ClearScene::DrawParticle()
{
	//�v���C���[�̃p�[�e�B�N���`��
	player->DrawParticle(dxCommon->GetCommandList());
	//�G�̃p�[�e�B�N���`��
	enemy->DrawParticle(dxCommon->GetCommandList());
}

void ClearScene::DrawFBXLightView()
{
	player->DrawLightView(dxCommon->GetCommandList());
	enemy->DrawLightView(dxCommon->GetCommandList());
}

DirectX::XMMATRIX ClearScene::GetLightViewProjection()
{
	return light->GetMatViewProjection();
}

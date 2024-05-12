#include "WinApp.h"
#include "Message.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "DXInput.h"
#include "ImGuiManager.h"
#include "TextureManager.h"
#include "Sprite.h"
#include "FbxLoader.h"
#include "Sprite.h"
#include "Camera.h"
#include "BillboardSprite.h"
#include "Light.h"
#include "LightGroup.h"
#include "FbxObject3D.h"
#include "ColliderManager.h"
#include "PlayerBulletParticle.h"
#include "EnemyBulletParticle.h"
#include "ElecParticle.h"
#include "ExplosionParticle1.h"
#include "ExplosionParticle2.h"
#include "TitleScene.h"
#include "TutorialScene.h"
#include "GameScene.h"
#include "ClearScene.h"
#include "ShadowMap.h"
#include "ObjObject3D.h"
#include "FPS.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//ウィンドウ生成
	WinApp* winApp = nullptr;
	winApp = WinApp::GetInstance();
	winApp->CreateWindow_(L"エレメントラッシュ");

	//メッセージ
	Message* message;
	message = Message::GetInstance();

	//DirectX初期化処理
	DirectXCommon* dxCommon = nullptr;
	dxCommon = DirectXCommon::GetInstance();
	dxCommon->Initialize(winApp);

	//キーボード
	Input* input = nullptr;
	input = Input::GetInstance();
	input->Initialize(winApp);

	//コントローラー
	DXInput* dxInput = nullptr;
	dxInput = DXInput::GetInstance();

	//ImGuiManager
	ImGuiManager* imGuiManager = nullptr;
	imGuiManager = new ImGuiManager();
	imGuiManager->Initialize(winApp, dxCommon);

	//テクスチャマネージャー
	TextureManager* textureManager = nullptr;
	textureManager = new TextureManager();

	//テクスチャマネージャー
	TextureManager::SetDevice(dxCommon->GetDevice());
	//ゲームで使うテクスチャをすべてセット
	textureManager->Initialize();
	textureManager->LoadFile(0, L"Resources/pictures/white1x1.png");
	textureManager->LoadFile(1, L"Resources/pictures/toriko2.png");
	textureManager->LoadFile(2, L"Resources/pictures/GourmetSpyzer.png");
	textureManager->LoadFile(3, L"Resources/pictures/orange.png");
	textureManager->LoadFile(4, L"Resources/pictures/purple.png");
	textureManager->LoadFile(5, L"Resources/pictures/effect1.png");
	textureManager->LoadFile(6, L"Resources/pictures/effect2.png");
	textureManager->LoadFile(7, L"Resources/pictures/effect3.png");
	textureManager->LoadFile(8, L"Resources/pictures/enemyHP.png");
	textureManager->LoadFile(9, L"Resources/pictures/toriko.png");
	textureManager->LoadFile(10, L"Resources/pictures/grassFiled.png");
	textureManager->LoadFile(11, L"Resources/pictures/gravel.png");
	textureManager->LoadFile(12, L"Resources/pictures/DissolveMap.png");
	textureManager->LoadFile(13, L"Resources/pictures/mapping.png");
	textureManager->LoadFile(14, L"Resources/pictures/black.png");
	textureManager->LoadFile(15, L"Resources/pictures/blackParticle.png");
	textureManager->LoadFile(16, L"Resources/pictures/effect4.png");
	textureManager->LoadFile(17, L"Resources/pictures/skyBox.png");
	textureManager->LoadFile(18, L"Resources/pictures/title1.png");
	textureManager->LoadFile(19, L"Resources/pictures/title2.png");
	textureManager->LoadFile(20, L"Resources/pictures/game2.png");
	textureManager->LoadFile(21, L"Resources/pictures/clear.png");
	textureManager->LoadFile(22, L"Resources/pictures/rockOn.png");
	textureManager->LoadFile(23, L"Resources/pictures/enemyHP1.png");
	textureManager->LoadFile(24, L"Resources/pictures/enemyHP2.png");
	textureManager->LoadFile(25, L"Resources/pictures/enemyHP3.png");
	textureManager->LoadFile(26, L"Resources/pictures/enemyHP4.png");
	textureManager->LoadFile(27, L"Resources/pictures/fire.png");
	textureManager->LoadFile(28, L"Resources/pictures/playerHP1.png");
	textureManager->LoadFile(29, L"Resources/pictures/playerHP2.png");
	textureManager->LoadFile(30, L"Resources/pictures/playerHP3.png");
	textureManager->LoadFile(31, L"Resources/pictures/elec.jpeg");
	textureManager->LoadFile(32, L"Resources/pictures/tutorial1.png");
	textureManager->LoadFile(33, L"Resources/pictures/tutorial2.png");
	textureManager->LoadFile(34, L"Resources/pictures/tutorial3.png");
	textureManager->LoadFile(35, L"Resources/pictures/tutorial4.png");
	textureManager->LoadFile(36, L"Resources/pictures/tutorial6.png");
	textureManager->LoadFile(37, L"Resources/pictures/tutorial7.png");
	textureManager->LoadFile(38, L"Resources/pictures/tutorial8.png");
	textureManager->LoadFile(39, L"Resources/pictures/tutorial10.png");
	textureManager->LoadFile(40, L"Resources/pictures/tutorial11.png");
	textureManager->LoadFile(41, L"Resources/pictures/plane.png");
	textureManager->LoadFile(42, L"Resources/pictures/LStick.png");
	textureManager->LoadFile(43, L"Resources/pictures/RStick.png");
	textureManager->LoadFile(44, L"Resources/pictures/check.png");
	textureManager->LoadFile(45, L"Resources/pictures/checkFrame.png");
	textureManager->LoadFile(46, L"Resources/pictures/tutorialFrame.png");
	textureManager->LoadFile(47, L"Resources/pictures/LBButton.png");
	textureManager->LoadFile(48, L"Resources/pictures/RBButton.png");
	textureManager->LoadFile(49, L"Resources/pictures/LBButtonPush.png");
	textureManager->LoadFile(50, L"Resources/pictures/RBButtonPush.png");
	textureManager->LoadFile(51, L"Resources/pictures/tutorial12.png");
	textureManager->LoadFile(52, L"Resources/pictures/changeElec.png");
	textureManager->LoadFile(53, L"Resources/pictures/changeFire.png");
	textureManager->LoadFile(54, L"Resources/pictures/change.png");
	textureManager->LoadFile(55, L"Resources/pictures/change2.png");
	textureManager->LoadFile(56, L"Resources/pictures/attackElec.png");
	textureManager->LoadFile(57, L"Resources/pictures/attackFire.png");
	textureManager->LoadFile(58, L"Resources/pictures/enemyHP4.png");
	textureManager->LoadFile(59, L"Resources/pictures/spaceKey.png");
	textureManager->LoadFile(60, L"Resources/pictures/spaceKeyPush.png");
	textureManager->LoadFile(61, L"Resources/pictures/AButton.png");
	textureManager->LoadFile(62, L"Resources/pictures/AButtonPush.png");
	textureManager->LoadFile(63, L"Resources/pictures/title3.png");
	textureManager->LoadFile(64, L"Resources/pictures/AKey.png");
	textureManager->LoadFile(65, L"Resources/pictures/AKeyPush.png");
	textureManager->LoadFile(66, L"Resources/pictures/WKey.png");
	textureManager->LoadFile(67, L"Resources/pictures/WKeyPush.png");
	textureManager->LoadFile(68, L"Resources/pictures/SKey.png");
	textureManager->LoadFile(69, L"Resources/pictures/SKeyPush.png");
	textureManager->LoadFile(70, L"Resources/pictures/DKey.png");
	textureManager->LoadFile(71, L"Resources/pictures/DKeyPush.png");
	textureManager->LoadFile(72, L"Resources/pictures/LeftKey.png");
	textureManager->LoadFile(73, L"Resources/pictures/LeftKeyPush.png");
	textureManager->LoadFile(74, L"Resources/pictures/UpKey.png");
	textureManager->LoadFile(75, L"Resources/pictures/UpKeyPush.png");
	textureManager->LoadFile(76, L"Resources/pictures/DownKey.png");
	textureManager->LoadFile(77, L"Resources/pictures/DownKeyPush.png");
	textureManager->LoadFile(78, L"Resources/pictures/RightKey.png");
	textureManager->LoadFile(79, L"Resources/pictures/RightKeyPush.png");
	textureManager->LoadFile(80, L"Resources/pictures/spaceKey.png");
	textureManager->LoadFile(81, L"Resources/pictures/spaceKeyPush.png");
	textureManager->LoadFile(82, L"Resources/pictures/shiftKey.png");
	textureManager->LoadFile(83, L"Resources/pictures/shiftKeyPush.png");
	textureManager->LoadFile(84, L"Resources/pictures/escKey.png");
	textureManager->LoadFile(85, L"Resources/pictures/startButton.png");

	//スプライト
	Sprite::SetDevice(dxCommon->GetDevice());
	Sprite::SetTextureManager(textureManager);
	Sprite::CreateGraphicsPipeLine();

	//FBXローダー初期化
	FbxLoader::GetInstance()->Initialize(dxCommon->GetDevice());
	//テクスチャマネージャーセット
	FbxModel::SetTextureManager(textureManager);
	FbxModel::SetDevice(dxCommon->GetDevice());

	//カメラ初期化
	Camera::SetInput(input);
	Camera::SetDXInput(dxInput);
	Camera* camera = nullptr;
	camera = new Camera();
	camera->Initialize();

	//ビルボードのスプライト
	BillboardSpriteModel::SetDevice(dxCommon->GetDevice());
	BillboardSpriteModel::SetSpriteManager(textureManager);
	BillboardSprite::SetDevice(dxCommon->GetDevice());
	BillboardSprite::SetCamera(camera);
	BillboardSprite::SetInput(input);
	BillboardSprite::CreateGraphicsPipeline();

	//ライト(影用)初期化
	Light* light = nullptr;
	light = new Light();
	light->Initialize();

	//ライト
	LightGroup::StaticInitialize(dxCommon->GetDevice());
	LightGroup* lightGroup = nullptr;
	lightGroup = new LightGroup();
	lightGroup = LightGroup::Create();
	lightGroup->SetAmbientColor(XMFLOAT3(1, 1, 1));
	lightGroup->SetDirLightActive(0, false);
	lightGroup->SetDirLightActive(1, false);
	lightGroup->SetDirLightActive(2, false);
	lightGroup->Update();

	//FBXオブジェクト初期化
	FbxObject3D::SetDevice(dxCommon->GetDevice());
	FbxObject3D::SetCamera(camera);
	FbxObject3D::SetLight(light);
	FbxObject3D::SetLightGroup(lightGroup);
	FbxObject3D::CreateGraphicsPipelineLightView();
	FbxObject3D::CreateGraphicsPipeline();

	//コライダーの球
	ColliderSphereObject::SetDevice(dxCommon->GetDevice());
	ColliderSphereObject::SetCamera(camera);
	ColliderSphereObject::SetInput(input);

	//コライダーのキューブ
	ColliderCubeObject::SetDevice(dxCommon->GetDevice());
	ColliderCubeObject::SetCamera(camera);
	ColliderCubeObject::SetInput(input);

	//コライダーマネージャー
	ColliderManager::StaticInitialize(dxCommon->GetDevice());
	ColliderManager* colliderManager = nullptr;
	colliderManager = new ColliderManager();

	//自機の弾パーティクル
	PlayerBulletParticle::SetSpriteManager(textureManager);
	PlayerBulletParticle::SetDevice(dxCommon->GetDevice());
	PlayerBulletParticle::SetCamera(camera);
	PlayerBulletParticle::SetInput(input);
	PlayerBulletParticle::CreateGraphicsPipeline();

	//敵の弾パーティクル
	EnemyBulletParticle::SetSpriteManager(textureManager);
	EnemyBulletParticle::SetDevice(dxCommon->GetDevice());
	EnemyBulletParticle::SetCamera(camera);
	EnemyBulletParticle::SetInput(input);
	EnemyBulletParticle::CreateGraphicsPipeline();

	//雷パーティクル
	ElecParticle::SetSpriteManager(textureManager);
	ElecParticle::SetDevice(dxCommon->GetDevice());
	ElecParticle::SetCamera(camera);
	ElecParticle::SetInput(input);
	ElecParticle::CreateGraphicsPipeline();

	//爆発パーティクル
	ExplosionParticle1::SetSpriteManager(textureManager);
	ExplosionParticle1::SetDevice(dxCommon->GetDevice());
	ExplosionParticle1::SetCamera(camera);
	ExplosionParticle1::SetInput(input);
	ExplosionParticle1::CreateGraphicsPipeline();

	//爆発パーティクル
	ExplosionParticle2::SetSpriteManager(textureManager);
	ExplosionParticle2::SetDevice(dxCommon->GetDevice());
	ExplosionParticle2::SetCamera(camera);
	ExplosionParticle2::SetInput(input);
	ExplosionParticle2::CreateGraphicsPipeline();

	//ロックオン
	LockOn* lockOn = nullptr;
	lockOn = new LockOn();
	lockOn->SetCamera(camera);
	lockOn->Initialize();

	//プレイヤーステート
	PlayerState::StaticInitialize();

	//プレイヤー初期化
	Player::SetCamera(camera);
	Player::SetInput(input);
	Player::SetDXInput(dxInput);
	Player::SetLockOn(lockOn);
	Player* player = nullptr;
	player = new Player();
	player->Initialize();

	//敵初期化
	Enemy::SetCamera(camera);
	Enemy::SetInput(input);
	Enemy* enemy = nullptr;
	enemy = new Enemy();
	enemy->Initialize();
	//敵の弾初期化
	EnemyBullet::SetCamera(camera);

	//小さい敵初期化
	MiniEnemy::SetCamera(camera);
	MiniEnemy::SetInput(input);
	MiniEnemy* miniEnemy = nullptr;
	miniEnemy = new MiniEnemy();
	miniEnemy->Initialize();

	//チュートリアルの敵初期化
	TutorialEnemy::SetCamera(camera);
	TutorialEnemy::SetInput(input);
	TutorialEnemy* tutorialEnemy = nullptr;
	tutorialEnemy = new TutorialEnemy();
	tutorialEnemy->Initialize();

	//無限に続く床
	Plane::SetCamera(camera);
	Plane::SetInput(input);
	Plane* plane = nullptr;
	plane = new Plane();
	plane->Initialize();

	//UI初期化
	UI::SetInput(input);
	UI::SetDXInput(dxInput);
	UI* ui = nullptr;
	ui = new UI();
	ui->Initialize();

	//地形
	Terrain::SetCamera(camera);
	Terrain* terrain = nullptr;
	terrain = new Terrain();
	terrain->Initialize(dxCommon->GetDevice());

	//ShadowMap
	ShadowMap* shadowMap = nullptr;
	ShadowMap::SetDevice(dxCommon->GetDevice());
	shadowMap = new ShadowMap;
	shadowMap->Initialize();
	shadowMap->CreateGraphicsPipeLine0();

	//タイトルシーン
	TitleScene::SetDevice(dxCommon, input, dxInput);
	TitleScene::SetGameObject(player, camera, light, ui);

	//チュートリアルシーン
	TutorialScene::SetDevice(dxCommon, input, dxInput);
	TutorialScene::SetGameObject(player, enemy, tutorialEnemy, plane,terrain, camera, light, ui);
	
	//ゲーム フェーズ
	PhaseState::SetDevice(dxCommon, input, dxInput);
	PhaseState::SetGameObject(player, enemy, miniEnemy, plane, terrain,camera, light, ui);

	//クリアシーン
	ClearScene::SetDevice(dxCommon, input, dxInput);
	ClearScene::SetGameObject(player, enemy, plane,terrain, camera, light, ui);

	//シーン
	Scene* scene = nullptr;
	scene = new Scene();

	//FPSを固定
	FPS* fps = nullptr;
	fps = new FPS;
	fps->SetFrameRate(60.0f);
	fps->FpsControlBegin();

	//ゲームループ
	while (true)
	{
		//✖ボタンでゲームループ終了
		if (message->Update() == 1)break;

		//キーボード更新
		input->Update();

		//コントローラ更新
		dxInput->Update();

		imGuiManager->Begin();

		//shadowMap
		shadowMap->SetAlpha(1.0f);
		shadowMap->SetLightVP(light->GetMatViewProjection());
		shadowMap->Update();

		//シーン遷移時のみ初期化
		scene->Initialize();
		//シーンの更新
		scene->Update();

		//// 4. 描画コマンド

		//shadowMap
		shadowMap->PreDrawScene0(dxCommon->GetCommandList());
		scene->DrawFBXLightView();
		shadowMap->PostDrawScene0(dxCommon->GetCommandList());
		//シーンにSRVを渡す
		scene->SetSRV(shadowMap->GetSRV());

		//描画前処理
		dxCommon->PreDraw();

		//シーンの描画
		scene->Draw();

		//シーン遷移
		scene->NextScene(scene);


		imGuiManager->End();
		imGuiManager->Draw();

		//描画後処理
		dxCommon->PostDraw();
	}


	fps->FpsControlEnd();

	imGuiManager->Finalize();

	delete shadowMap;
	delete imGuiManager;
	//delete titleScene;
	//delete tutorialScene;
	//delete gameScene;
	//delete clearScene;
	delete scene;
	delete player;
	delete enemy;
	delete tutorialEnemy;

	//ウィンドウクラスを登録解除
	winApp->deleteWindow();

	return 0;
}
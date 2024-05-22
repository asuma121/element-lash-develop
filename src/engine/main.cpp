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
#include "KeyManager.h"
#include "FPS.h"
#include "imgui.h"

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

	//キーマネージャー
	KeyState::SetDXInput(dxInput);
	KeyState::SetInput(input);
	KeyManager* keyManager = nullptr;
	keyManager = new KeyManager();

	//ImGuiManager
	/*ImGuiManager* imGuiManager = nullptr;
	imGuiManager = new ImGuiManager();
	imGuiManager->Initialize(winApp, dxCommon);*/

	//テクスチャマネージャー
	TextureManager* textureManager = nullptr;
	textureManager = new TextureManager();

	//テクスチャマネージャー
	TextureManager::SetDevice(dxCommon->GetDevice());
	//ゲームで使うテクスチャをすべてセット
	textureManager->Initialize();
	textureManager->LoadFile(0, L"Resources/pictures/white1x1.png");
	textureManager->LoadFile(1, L"Resources/pictures/UI_Button/AButton.png");
	textureManager->LoadFile(2, L"Resources/pictures/UI_Button/AButtonPush.png");
	textureManager->LoadFile(3, L"Resources/pictures/UI_Button/AKey.png");
	textureManager->LoadFile(4, L"Resources/pictures/UI_Button/AKeyPush.png");
	textureManager->LoadFile(5, L"Resources/pictures/UI_Button/DKey.png");
	textureManager->LoadFile(6, L"Resources/pictures/UI_Button/DKeyPush.png");
	textureManager->LoadFile(7, L"Resources/pictures/UI_Button/DownKey.png");
	textureManager->LoadFile(8, L"Resources/pictures/UI_Button/DownKeyPush.png");
	textureManager->LoadFile(9, L"Resources/pictures/UI_Button/LBButton.png");
	textureManager->LoadFile(10, L"Resources/pictures/UI_Button/LBButtonPush.png");
	textureManager->LoadFile(11, L"Resources/pictures/UI_Button/LeftKey.png");
	textureManager->LoadFile(12, L"Resources/pictures/UI_Button/LeftKeyPush.png");
	textureManager->LoadFile(13, L"Resources/pictures/UI_Button/LStick.png");
	textureManager->LoadFile(14, L"Resources/pictures/UI_Button/RBButton.png");
	textureManager->LoadFile(15, L"Resources/pictures/UI_Button/RBButtonPush.png");
	textureManager->LoadFile(16, L"Resources/pictures/UI_Button/RightKey.png");
	textureManager->LoadFile(17, L"Resources/pictures/UI_Button/RightKeyPush.png");
	textureManager->LoadFile(18, L"Resources/pictures/UI_Button/RStick.png");
	textureManager->LoadFile(19, L"Resources/pictures/UI_Button/shiftKey.png");
	textureManager->LoadFile(20, L"Resources/pictures/UI_Button/shiftKeyPush.png");
	textureManager->LoadFile(21, L"Resources/pictures/UI_Button/UpKey.png");
	textureManager->LoadFile(22, L"Resources/pictures/UI_Button/UpKeyPush.png");
	textureManager->LoadFile(23, L"Resources/pictures/UI_Button/WKey.png");
	textureManager->LoadFile(24, L"Resources/pictures/UI_Button/WKeyPush.png");
	textureManager->LoadFile(25, L"Resources/pictures/UI_Button/SKey.png");
	textureManager->LoadFile(26, L"Resources/pictures/UI_Button/SKeyPush.png");
	textureManager->LoadFile(27, L"Resources/pictures/UI_Button/spaceKey.png");
	textureManager->LoadFile(28, L"Resources/pictures/UI_Button/spaceKeyPush.png");
	textureManager->LoadFile(29, L"Resources/pictures/UI_Text/clear.png");
	textureManager->LoadFile(30, L"Resources/pictures/UI_Text/escKey.png");
	textureManager->LoadFile(31, L"Resources/pictures/UI_Text/game1.png");
	textureManager->LoadFile(32, L"Resources/pictures/UI_Text/game2.png");
	textureManager->LoadFile(33, L"Resources/pictures/UI_Text/startButton.png");
	textureManager->LoadFile(34, L"Resources/pictures/UI_Text/title1.png");
	textureManager->LoadFile(35, L"Resources/pictures/UI_Text/title2.png");
	textureManager->LoadFile(36, L"Resources/pictures/UI_Text/title3.png");
	textureManager->LoadFile(37, L"Resources/pictures/UI_Text/tutorial2.png");
	textureManager->LoadFile(38, L"Resources/pictures/UI_Text/tutorial3.png");
	textureManager->LoadFile(39, L"Resources/pictures/UI_Text/tutorial4.png");
	textureManager->LoadFile(40, L"Resources/pictures/UI_Text/tutorial6.png");
	textureManager->LoadFile(41, L"Resources/pictures/UI_Text/tutorial7.png");
	textureManager->LoadFile(42, L"Resources/pictures/UI_Text/tutorial8.png");
	textureManager->LoadFile(43, L"Resources/pictures/UI_Text/tutorial10.png");
	textureManager->LoadFile(44, L"Resources/pictures/UI_Text/tutorial11.png");
	textureManager->LoadFile(45, L"Resources/pictures/UI_Text/tutorial12.png");
	textureManager->LoadFile(46, L"Resources/pictures/UI_Text/gameOver1.png");
	textureManager->LoadFile(47, L"Resources/pictures/UI_Text/gameOver2.png");
	textureManager->LoadFile(48, L"Resources/pictures/UI_Text/gameOver3.png");
	textureManager->LoadFile(49, L"Resources/pictures/UI_Text/gameOver4.png");
	textureManager->LoadFile(50, L"Resources/pictures/UI_Game/attackElec.png");
	textureManager->LoadFile(51, L"Resources/pictures/UI_Game/attackFire.png");
	textureManager->LoadFile(52, L"Resources/pictures/UI_Game/change.png");
	textureManager->LoadFile(53, L"Resources/pictures/UI_Game/change2.png");
	textureManager->LoadFile(54, L"Resources/pictures/UI_Game/changeElec.png");
	textureManager->LoadFile(55, L"Resources/pictures/UI_Game/changeFire.png");
	textureManager->LoadFile(56, L"Resources/pictures/UI_Game/check.png");
	textureManager->LoadFile(57, L"Resources/pictures/UI_Game/checkFrame.png");
	textureManager->LoadFile(58, L"Resources/pictures/UI_Game/enemyHP1.png");
	textureManager->LoadFile(59, L"Resources/pictures/UI_Game/enemyHP2.png");
	textureManager->LoadFile(60, L"Resources/pictures/UI_Game/enemyHP3.png");
	textureManager->LoadFile(61, L"Resources/pictures/UI_Game/enemyHP4.png");
	textureManager->LoadFile(62, L"Resources/pictures/UI_Game/enemyHP5.png");
	textureManager->LoadFile(63, L"Resources/pictures/UI_Game/playerHP1.png");
	textureManager->LoadFile(64, L"Resources/pictures/UI_Game/playerHP2.png");
	textureManager->LoadFile(65, L"Resources/pictures/UI_Game/playerHP3.png");
	textureManager->LoadFile(66, L"Resources/pictures/UI_Game/tutorial1.png");
	textureManager->LoadFile(67, L"Resources/pictures/UI_Game/tutorialFrame.png");
	textureManager->LoadFile(68, L"Resources/pictures/Object/coliseum.png");
	textureManager->LoadFile(69, L"Resources/pictures/Object/DissolveMap.png");
	textureManager->LoadFile(70, L"Resources/pictures/Object/elec.jpeg");
	textureManager->LoadFile(71, L"Resources/pictures/Object/fire.png");
	textureManager->LoadFile(72, L"Resources/pictures/Object/piller.png");
	textureManager->LoadFile(73, L"Resources/pictures/Object/skyBox.png");
	textureManager->LoadFile(74, L"Resources/pictures/Object/stoneTile.png");
	textureManager->LoadFile(75, L"Resources/pictures/Object/rockOn.png");
	textureManager->LoadFile(76, L"Resources/pictures/Particle/blackParticle.png");
	textureManager->LoadFile(77, L"Resources/pictures/Particle/effect1.png");
	textureManager->LoadFile(78, L"Resources/pictures/Particle/effect2.png");
	textureManager->LoadFile(79, L"Resources/pictures/Particle/effect4.png");
	textureManager->LoadFile(80, L"Resources/pictures/Particle/purple.png");
	textureManager->LoadFile(81, L"Resources/pictures/Particle/red.png");
	textureManager->LoadFile(82, L"Resources/pictures/orange.png");
	textureManager->LoadFile(83, L"Resources/pictures/black.png");

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
	Camera::SetKeyManager(keyManager);
	Camera* camera = nullptr;
	camera = new Camera();

	//ビルボードのスプライト
	BillboardSpriteModel::SetDevice(dxCommon->GetDevice());
	BillboardSpriteModel::SetSpriteManager(textureManager);
	BillboardSprite::SetDevice(dxCommon->GetDevice());
	BillboardSprite::SetCamera(camera);
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

	//コライダーのキューブ
	ColliderCubeObject::SetDevice(dxCommon->GetDevice());
	ColliderCubeObject::SetCamera(camera);

	camera->Initialize();

	//コライダーマネージャー
	ColliderManager::StaticInitialize(dxCommon->GetDevice());

	//自機の弾パーティクル
	PlayerBulletParticle::SetSpriteManager(textureManager);
	PlayerBulletParticle::SetDevice(dxCommon->GetDevice());
	PlayerBulletParticle::SetCamera(camera);
	PlayerBulletParticle::CreateGraphicsPipeline();

	//敵の弾パーティクル
	EnemyBulletParticle::SetSpriteManager(textureManager);
	EnemyBulletParticle::SetDevice(dxCommon->GetDevice());
	EnemyBulletParticle::SetCamera(camera);
	EnemyBulletParticle::CreateGraphicsPipeline();

	//雷パーティクル
	ElecParticle::SetSpriteManager(textureManager);
	ElecParticle::SetDevice(dxCommon->GetDevice());
	ElecParticle::SetCamera(camera);
	ElecParticle::CreateGraphicsPipeline();

	//爆発パーティクル
	ExplosionParticle1::SetSpriteManager(textureManager);
	ExplosionParticle1::SetDevice(dxCommon->GetDevice());
	ExplosionParticle1::SetCamera(camera);
	ExplosionParticle1::CreateGraphicsPipeline();

	//爆発パーティクル
	ExplosionParticle2::SetSpriteManager(textureManager);
	ExplosionParticle2::SetDevice(dxCommon->GetDevice());
	ExplosionParticle2::SetCamera(camera);
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
	Player::SetKeyManager(keyManager);
	Player::SetLockOn(lockOn);
	Player* player = nullptr;
	player = new Player();
	player->Initialize();

	//敵ステート
	EnemyState::StaticInitialize();

	//敵初期化
	Enemy::SetCamera(camera);
	Enemy* enemy = nullptr;
	enemy = new Enemy();
	enemy->Initialize();
	//敵の弾初期化
	EnemyBullet::SetCamera(camera);

	//チュートリアルの敵初期化
	TutorialEnemy::SetCamera(camera);
	TutorialEnemy* tutorialEnemy = nullptr;
	tutorialEnemy = new TutorialEnemy();
	tutorialEnemy->Initialize();

	//無限に続く床
	Plane::SetCamera(camera);
	Plane* plane = nullptr;
	plane = new Plane();
	plane->Initialize();

	//UI初期化
	UI::SetKeyManager(keyManager);
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
	TitleScene::SetDevice(dxCommon, keyManager);
	TitleScene::SetGameObject(player, terrain, camera, light, ui);

	//チュートリアルシーン
	TutorialScene::SetDevice(dxCommon, keyManager);
	TutorialScene::SetGameObject(player, enemy, tutorialEnemy, plane,terrain, camera, light, ui);
	
	//ゲーム フェーズ
	PhaseState::SetDevice(dxCommon, keyManager);
	PhaseState::SetGameObject(player, enemy, tutorialEnemy, plane, terrain,camera, light, ui);

	//クリアシーン
	ClearScene::SetDevice(dxCommon, keyManager);
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

		//キーマネージャー更新
		keyManager->Update();

		/*imGuiManager->Begin();*/

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

		//キー更新
		keyManager->UpdateState();


		/*imGuiManager->End();
		imGuiManager->Draw();*/

		//描画後処理
		dxCommon->PostDraw();
	}


	fps->FpsControlEnd();

	/*imGuiManager->Finalize();*/

	delete shadowMap;
	//delete imGuiManager;
	delete scene;
	delete player;
	delete lockOn;
	delete plane;
	delete terrain;
	delete enemy;
	delete tutorialEnemy;
	delete ui;
	delete light;
	delete lightGroup;
	delete textureManager;
	delete camera;
	delete keyManager;

	//ウィンドウクラスを登録解除
	winApp->deleteWindow();

	return 0;
}
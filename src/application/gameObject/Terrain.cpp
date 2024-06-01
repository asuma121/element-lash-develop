#include "Terrain.h"
#include "ColliderManager.h"

Camera* Terrain::camera = nullptr;

Terrain::~Terrain()
{
	delete skySphereModel;
	delete skySphereObject;
	delete coliseumModel;
	delete coliseumObject;
	delete coliseum2Model;
	delete coliseum2Object;
	delete pillerModel;
}

void Terrain::Initialize(ID3D12Device* device)
{
	//天球
	skySphereModel = new ObjModel();
	skySphereModel->Initialize(device, "skyBox", "Resources/pictures/Object/skyBox.png");
	skySphereObject = new ObjObject3D();
	skySphereObject->Initialize(device, skySphereModel, camera);
	skySphereObject->setScale(skySphereScale);
	skySphereObject->setRotation(skySpherePos);
	skySphereObject->setPosition(skySphereRotation);

	//コロシアムのモデル
	coliseumModel = new ObjModel();
	coliseumModel->Initialize(device, "coliseum", "Resources/pictures/Object/coliseum.png");
	coliseumObject = new ObjObject3D();
	coliseumObject->Initialize(device, coliseumModel, camera);
	coliseumObject->setScale(coliseumScale);
	coliseumObject->setRotation(coliseumPos);
	coliseumObject->setPosition(coliseumRotation);

	//コロシアムのモデル
	coliseum2Model = new ObjModel();
	coliseum2Model->Initialize(device, "coliseum2", "Resources/pictures/Object/coliseum.png");
	coliseum2Object = new ObjObject3D();
	coliseum2Object->Initialize(device, coliseum2Model, camera);
	coliseum2Object->setScale(coliseumScale);
	coliseum2Object->setRotation(coliseumPos);
	coliseum2Object->setPosition(coliseumRotation);
	coliseum2Object->SetAlpha(backAlpha);

	//柱のモデル
	pillerModel = new ObjModel();
	pillerModel->Initialize(device, "piller", "Resources/pictures/Object/piller.png");

	//天球以外のオブジェクト読み込み
	objectData = JSONLoader::LoadTerrainObject("Resources/json/stage.json");

	for (int i = 0; i < objectData.size(); i++)
	{
		//オブジェクト生成
		ObjObject3D* newObject = new ObjObject3D();
		//モデル読み込み
		newObject->Initialize(device, pillerModel, camera);
		//座標、スケール、角度設定
		newObject->setScale(objectData[i].scale);
		newObject->setRotation(objectData[i].rotation);
		newObject->setPosition(objectData[i].position);
		//オブジェクトの末尾に追加
		objects.emplace_back(newObject);
	}

	//コライダー
	colliderData = JSONLoader::LoadTerrainCollider("Resources/json/stage.json");
	colliderNum = colliderData.size();
	for (int i = 0; i < colliderData.size(); i++)
	{
		ColliderManager::SetCollider(colliderData[i]);
	}
}

void Terrain::Update()
{
	//オブジェクト更新
	skySphereObject->Update();
	coliseumObject->Update();
	coliseum2Object->Update();
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update();
	}
}

void Terrain::Draw(ID3D12GraphicsCommandList* cmdList)
{
	//オブジェクト描画
	skySphereObject->Draw(cmdList, skySphereModel->vbView, skySphereModel->ibView);
	coliseumObject->Draw(cmdList, coliseumModel->vbView, coliseumModel->ibView);
	coliseum2Object->Draw(cmdList, coliseum2Model->vbView, coliseum2Model->ibView);
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Draw(cmdList, pillerModel->vbView, pillerModel->ibView);
	}
}

void Terrain::DrawTitle(ID3D12GraphicsCommandList* cmdList)
{
	skySphereObject->Draw(cmdList, skySphereModel->vbView, skySphereModel->ibView);
}

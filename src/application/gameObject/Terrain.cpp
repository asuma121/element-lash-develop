#include "Terrain.h"
#include "ColliderManager.h"

Camera* Terrain::camera = nullptr;

Terrain::~Terrain()
{
	delete skySphereModel;
	delete skySphereObject;
	delete coliseumModel;
	delete coliseumObject;
}

void Terrain::Initialize(ID3D12Device* device)
{
	//天球
	skySphereModel = new ObjModel();
	skySphereModel->Initialize(device, "skyBox", "Resources/pictures/skyBox.png");
	skySphereObject = new ObjObject3D();
	skySphereObject->Initialize(device, skySphereModel, camera);
	skySphereObject->setScale(skySphereScale);
	skySphereObject->setRotation(skySpherePos);
	skySphereObject->setPosition(skySphereRotation);

	//コロシアム
	coliseumModel = new ObjModel();
	coliseumModel->Initialize(device, "coliseum", "Resources/pictures/coliseum.png");
	coliseumObject = new ObjObject3D();
	coliseumObject->Initialize(device, coliseumModel, camera);
	coliseumObject->setScale(coliseumScale);
	coliseumObject->setRotation(coliseumPos);
	coliseumObject->setPosition(coliseumRotation);

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
}

void Terrain::Draw(ID3D12GraphicsCommandList* cmdList)
{
	//オブジェクト描画
	skySphereObject->Draw(cmdList, skySphereModel->vbView, skySphereModel->ibView);
	coliseumObject->Draw(cmdList, coliseumModel->vbView, coliseumModel->ibView);
}

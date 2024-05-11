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
	//�V��
	skySphereModel = new ObjModel();
	skySphereModel->Initialize(device, "skyBox", "Resources/pictures/skyBox.png");
	skySphereObject = new ObjObject3D();
	skySphereObject->Initialize(device, skySphereModel, camera);
	skySphereObject->setScale(skySphereScale);
	skySphereObject->setRotation(skySpherePos);
	skySphereObject->setPosition(skySphereRotation);

	//�R���V�A��
	coliseumModel = new ObjModel();
	coliseumModel->Initialize(device, "coliseum", "Resources/pictures/coliseum.png");
	coliseumObject = new ObjObject3D();
	coliseumObject->Initialize(device, coliseumModel, camera);
	coliseumObject->setScale(coliseumScale);
	coliseumObject->setRotation(coliseumPos);
	coliseumObject->setPosition(coliseumRotation);

	//�R���C�_�[
	colliderData = JSONLoader::LoadTerrainCollider("Resources/json/stage.json");
	colliderNum = colliderData.size();
	for (int i = 0; i < colliderData.size(); i++)
	{
		ColliderManager::SetCollider(colliderData[i]);
	}
}

void Terrain::Update()
{
	//�I�u�W�F�N�g�X�V
	skySphereObject->Update();
	coliseumObject->Update();
}

void Terrain::Draw(ID3D12GraphicsCommandList* cmdList)
{
	//�I�u�W�F�N�g�`��
	skySphereObject->Draw(cmdList, skySphereModel->vbView, skySphereModel->ibView);
	coliseumObject->Draw(cmdList, coliseumModel->vbView, coliseumModel->ibView);
}

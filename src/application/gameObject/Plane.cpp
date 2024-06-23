/**
 * @file Plane.h
 * @brief ゲームオブジェクト 平面
 * @author Asuma Syota
 * @date 2023/4
 */

#include "Plane.h"
#include "FbxLoader.h"
#include "ColliderManager.h"

Camera* Plane::camera = nullptr;

Plane::~Plane()
{
	delete object; 
	delete model;
}

void Plane::Initialize()
{
	//シェーダを別に設定
	JSONLoader::TextureData textureData;
	textureData.textureVol = 1;
	textureData.shaderVol = 1;
	textureData.textureNum1 = 74;	//床のテクスチャ
	textureData.shaderName = "Plane";	//シェーダの名前

	//モデル
	model = FbxLoader::GetInstance()->LoadModelFromFile("plane");
	//オブジェクト
	object = new FbxObject3D;
	object->Initialize(model, textureData);
	object->StopAnimation();

	//コライダーの設定
	colliderData.type = "Plane";	//判定を球体で取るため
	colliderData.objectName = "plane";
	colliderData.scale = scale;
	colliderData.rotation = rotation;
	colliderData.center = position;
	//コライダーマネージャーにセット
	ColliderManager::SetCollider(colliderData);
}

void Plane::Update()
{
	//動く
	object->SetPosition(position);
	object->SetRotation(rotation);
	object->SetScale(scale);

	object->Update();

}

void Plane::Draw(ID3D12GraphicsCommandList* cmdList)
{
	object->Draw(cmdList);
}
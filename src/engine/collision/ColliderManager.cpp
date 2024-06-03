/**
 * @file ColliderManager.cpp
 * @brief 判定の一括管理を行う
 * @author Asuma Syota
 * @date 2023/4
 */

#include "ColliderManager.h"
#include "math.h"
#include "mathOriginal.h"
#include <functional>
#include <algorithm>
#include <cassert>

using namespace DirectX;

std::list<std::unique_ptr<ColliderManager::Collider>>ColliderManager::collider;

void ColliderManager::SetCollider(JSONLoader::ColliderData colliderData)
{
	//コライダーセット
	std::unique_ptr<Collider>newColliderData = std::make_unique<Collider>();
	newColliderData->colliderData.type = colliderData.type;
	newColliderData->colliderData.objectName = colliderData.objectName;
	newColliderData->colliderData.scale = colliderData.scale;
	newColliderData->colliderData.rotation = colliderData.rotation;
	newColliderData->colliderData.center = colliderData.center;

	collider.emplace_back(std::move(newColliderData));
}

bool ColliderManager::CheckCollider(JSONLoader::ColliderData colliderData0, JSONLoader::ColliderData colliderData1, bool wallFlag)
{

	for (std::unique_ptr<Collider>& colliders : collider)
	{
		//描画フラグを立てる 位置更新
		if (colliders->colliderData.objectName == colliderData0.objectName)
		{
			colliders->colliderData.scale = colliderData0.scale;
			colliders->colliderData.rotation = colliderData0.rotation;
			colliders->colliderData.center = colliderData0.center;
		}
		if (colliders->colliderData.objectName == colliderData1.objectName)
		{
			colliders->colliderData.scale = colliderData1.scale;
			colliders->colliderData.rotation = colliderData1.rotation;
			colliders->colliderData.center = colliderData1.center;
		}
	}

	//球と球の場合
	if (colliderData0.type == "Sphere" && colliderData1.type == "Sphere")
	{
		return CheckSphereSphere(colliderData0, colliderData1, wallFlag);
	}

	//平面と球の場合
	if (colliderData0.type == "Plane" && colliderData1.type == "Sphere")
	{
		return CheckPlaneSphere(colliderData0, colliderData1);
	}
	else if (colliderData0.type == "Sphere" && colliderData1.type == "Plane")
	{
		return CheckPlaneSphere(colliderData1, colliderData0);
	}

	//平面とボックスの場合
	if (colliderData0.type == "Plane" && colliderData1.type == "Box")
	{
		return CheckPlaneBox(colliderData0, colliderData1);
	}
	else if (colliderData0.type == "Box" && colliderData1.type == "Plane")
	{
		return CheckPlaneBox(colliderData1, colliderData0);
	}

	return false;
}

bool ColliderManager::CheckSphereSphere(JSONLoader::ColliderData colliderSphere0, JSONLoader::ColliderData colliderSphere1, bool wallFlag)
{
	//中心同士の距離を求める
	XMFLOAT3 distanceCenter0 = colliderSphere0.center - colliderSphere1.center;
	double distanceCenter1 = sqrt(pow(distanceCenter0.x, 2) + pow(distanceCenter0.y, 2) + pow(distanceCenter0.z, 2));

	//二つのコライダーの半径の合計
	float r;
	if (wallFlag == false)
	{
		r = length(colliderSphere0.scale) / 2 + length(colliderSphere1.scale) / 2;
	}
	if (wallFlag == true)
	{
		float max = comparisonMax(length(colliderSphere0.scale) / 2, length(colliderSphere1.scale) / 2);
		float min = comparisonMin(length(colliderSphere0.scale) / 2, length(colliderSphere1.scale) / 2);
		r = max - min;
	}

	//中心との距離が半径の合計より大きければ当たっていない
	if (r < (float)distanceCenter1) return false;

	return true;
}

bool ColliderManager::CheckPlaneSphere(JSONLoader::ColliderData colliderPlane, JSONLoader::ColliderData colliderSphere)
{
	//球の中心
	XMVECTOR sphereCenter = { colliderSphere.center.x, colliderSphere.center.y, colliderSphere.center.z, 1 };
	//平面の法線ベクトル
	XMVECTOR planeNormal = { 0.0f,1.0f,0.0f,0.0f };
	//座標系の原点から球の中心座標への距離
	XMVECTOR distV = { 100,100,100,100 };
	if (colliderPlane.center.x + colliderPlane.scale.x > colliderSphere.center.x - colliderSphere.scale.x &&
		colliderPlane.center.x - colliderPlane.scale.x < colliderSphere.center.x + colliderSphere.scale.x)
	{
		distV = XMVector3Dot(sphereCenter, planeNormal);
	}
	//平面の中心との距離
	double planeDistance = sqrt(pow(colliderPlane.center.x, 2) +
		pow(colliderPlane.center.y, 2) + pow(colliderPlane.center.z, 2));
	//平面の原点距離を減算することで、平面と球の中心との距離が出る
	float dist = distV.m128_f32[0] - (float)planeDistance;

	//距離の絶対値が半径より大きければ当たっていない
	if (fabsf(dist) > colliderSphere.scale.x)return false;

	//疑似交点を計算
	/*if(inter)*/

	return true;
}

bool ColliderManager::CheckPlaneBox(JSONLoader::ColliderData colliderPlane, JSONLoader::ColliderData colliderBox)
{
	//球の中心
	XMVECTOR sphereCenter = { colliderBox.center.x, colliderBox.center.y, colliderBox.center.z, 1 };
	//平面の法線ベクトル
	XMVECTOR planeNormal = { 0.0f,1.0f,0.0f,0.0f };
	//座標系の原点から球の中心座標への距離
	XMVECTOR distV = { 100,100,100,100 };
	if (colliderPlane.center.x + colliderPlane.scale.x > colliderBox.center.x - colliderBox.scale.x &&
		colliderPlane.center.x - colliderPlane.scale.x < colliderBox.center.x + colliderBox.scale.x)
	{
		distV = XMVector3Dot(sphereCenter, planeNormal);
	}
	//平面の中心との距離
	double planeDistance = sqrt(pow(colliderPlane.center.x, 2) +
		pow(colliderPlane.center.y, 2) + pow(colliderPlane.center.z, 2));
	//平面の原点距離を減算することで、平面と球の中心との距離が出る
	float dist = distV.m128_f32[0] - (float)planeDistance;

	//距離の絶対値が半径より大きければ当たっていない
	if (fabsf(dist) > colliderBox.scale.y)return false;

	//疑似交点を計算
	/*if(inter)*/

	return true;
}
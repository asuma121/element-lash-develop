/**
 * @file ColliderManager.h
 * @brief 判定の一括管理を行う
 * @author Asuma Syota
 * @date 2023/4
 */

#pragma once
#include "JSONLoader.h"

class ColliderManager
{
public:	//サブクラス
	//コライダー描画用
	struct Collider
	{
		JSONLoader::ColliderData colliderData;
	};

public:	//静的メンバ関数

	/// <summary>
	///コライダーデータセット
	/// </summary>
	static void SetCollider(JSONLoader::ColliderData colliderData);

public:	//メンバ関数

	/// <summary>
	///判定
	/// </summary>
	static bool CheckCollider(JSONLoader::ColliderData colliderData0, JSONLoader::ColliderData colliderData1,bool wallFlag = false);

	/// <summary>
	///判定 球体と球体
	/// </summary>
	static bool CheckSphereSphere(JSONLoader::ColliderData colliderSphere0, JSONLoader::ColliderData colliderSphere1,bool wallFlag = false);

	/// <summary>
	///判定 平面と球体
	/// </summary>
	static bool CheckPlaneSphere(JSONLoader::ColliderData colliderPlane, JSONLoader::ColliderData colliderSphere);

	/// <summary>
	///判定 平面とボックス
	/// </summary>
	static bool CheckPlaneBox(JSONLoader::ColliderData colliderPlane, JSONLoader::ColliderData colliderBox);

public:	//静的メンバ変数
	//コライダー
	static std::list<std::unique_ptr<Collider>>collider;
};

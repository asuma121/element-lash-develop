/**
 * @file Light.cpp
 * @brief ライトの座標 シャドウマップに使用
 * @author Asuma Syota
 * @date 2023/4
 */

#include "Light.h"
#include "imGui.h"

void Light::Initialize()
{
	//射影変換	4Kとめっちゃ奥まで描画
	matProjection_ = XMMatrixOrthographicLH(
		900, 900, 1.0f, 700.0f);

	//行列計算
	matView_ = XMMatrixLookAtLH(XMLoadFloat3(&eye_), XMLoadFloat3(&target_), XMLoadFloat3(&up_));
}

void Light::Update()
{
	matView_ = XMMatrixLookAtLH(XMLoadFloat3(&eye_), XMLoadFloat3(&target_), XMLoadFloat3(&up_));
}
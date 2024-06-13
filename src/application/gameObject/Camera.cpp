/**
 * @file Camera.cpp
 * @brief カメラ ゲームで使うビュー行列を管理
 * @author Asuma Syota
 * @date 2023/4
 */

#include "Camera.h"
#include "Math.h"
#include "mathOriginal.h"
#include "imgui.h"
#include "ColliderManager.h"
#include "CamaeraStateManager.h"
#define PI 3.14159265359

KeyManager* CameraState::keyManager = nullptr;
XMMATRIX CameraState::matProjection_;
XMMATRIX CameraState::matView_;
XMMATRIX CameraState::matBillboard_;
XMFLOAT3 CameraState::eye_;
XMFLOAT3 CameraState::target_;
XMFLOAT3 CameraState::up_;
XMFLOAT3 CameraState::rotation;
JSONLoader::ColliderData CameraState::colliderData;

Camera* Camera::GetInstance()
{
	static Camera instance;
	return &instance;
}

void Camera::SetKeyManager(KeyManager* keyManager)
{
	CameraState::SetKeyManager(keyManager);
}

Camera::Camera()
{
	cameraState = new Title();
	//ステートの初期化
	cameraState->Initialize();
}

Camera::~Camera()
{
	delete cameraState;
}

void Camera::Initialize()
{
}


void Camera::Update()
{
	cameraState->Update();
}

XMFLOAT3 Camera::GetEye()
{
	return cameraState->GetEye();
}

XMFLOAT3 Camera::GetTarget()
{
	return cameraState->GetTarget();
}

XMFLOAT3 Camera::GetUp()
{
	return cameraState->GetUp();
}

XMFLOAT3 Camera::GetRotation()
{
	return cameraState->GetRotation();
}

XMMATRIX Camera::GetMatProjection()
{
	return cameraState->GetMatProjection();
}

XMMATRIX Camera::GetMatView()
{
	return cameraState->GetMatView();
}

XMMATRIX Camera::GetMatViewProjection()
{
	return cameraState->GetMatView() * cameraState->GetMatProjection();
}

XMMATRIX Camera::GetMatBillboard()
{
	return cameraState->GetMatBillboard();
}

void Camera::SetPhaseTimer(int timer)
{
	cameraState->SetPhaseTimer(timer);
}

void Camera::SetObjectCollider(std::vector<JSONLoader::ColliderData> colliderData)
{
	cameraState->SetObjectCollider(colliderData);
}

void Camera::SetPlayerPos(XMFLOAT3 playerPos)
{
	cameraState->SetPlayerPos(playerPos);
}

void Camera::SetPlayerRot(XMFLOAT3 playerRot)
{
	cameraState->SetPlayerRot(playerRot);
}

void Camera::SetEnemyPos(XMFLOAT3 enemyPos)
{
	cameraState->SetPlayerRot(enemyPos);
}

void Camera::ChangeState(CameraState* newState)
{
	delete cameraState;
	cameraState = newState;
}

void Camera::SetTitle()
{
	ChangeState(new Title());
}

void Camera::SetTutorial()
{
	ChangeState(new Tutorial());
}

void Camera::SetMovePhase()
{
	ChangeState(new MovePhase1());
}

void Camera::SetClear()
{
	ChangeState(new Clear());
}

void Camera::SetFollowPlayer()
{
	ChangeState(new FollowPlayer());
}

void CameraState::Initialize()
{
	//射影変換の初期化
	matProjection_ = XMMatrixIdentity();
	//ビュー変換行列の初期化
	matView_ = XMMatrixIdentity();
	//ビルボード行列の初期化
	matBillboard_ = XMMatrixIdentity();

	//視点座標、注視点、上方向、角度の初期化
	eye_ = { 0, 0, 0 };
	target_ = { 0, 0, 0 };
	up_ = { 0, 1, 0 };
	rotation = { 0, 0, 0 };

	//射影変換
	matProjection_ = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(45.0f),			//上下画角45度
		(float)window_width / window_height,//アスペクト比(画面横幅/画面立幅)
		1.0f, 10000.0f						//前端、奥端
	);

	//行列計算
	matView_ = XMMatrixLookAtLH(XMLoadFloat3(&eye_), XMLoadFloat3(&target_), XMLoadFloat3(&up_));

	//コライダーデータ
	colliderData.type = "Sphere";	//判定を球体で取るため
	colliderData.objectName = "camera";
	colliderData.scale = colliderScale;
	colliderData.rotation = colliderRotation;
	colliderData.center = eye_;
	//コライダーマネージャーにセット
	ColliderManager::SetCollider(colliderData);
}

void CameraState::Update()
{
	//ビルボード行列の更新
	BillboardUpdate();

	//動き
	Move();

	//コライダーの更新
	UpdateCollider();

	//角度更新
	UpdateRotation();

	//射影変換
	matView_ = XMMatrixLookAtLH(XMLoadFloat3(&eye_), XMLoadFloat3(&target_), XMLoadFloat3(&up_));
}

void CameraState::UpdateRotation()
{
	//視点から注視点のベクトル取得
	XMFLOAT3 vec = target_ - eye_;

	//カメラの角度取得
	rotation = getVectorRotation(vec);
}

void CameraState::BillboardUpdate()
{
	XMFLOAT3 eye = eye_;
	XMFLOAT3 target = target_;
	XMFLOAT3 up = up_;
	//視点座標
	XMVECTOR eyePosition = XMLoadFloat3(&eye);
	//注視点座標
	XMVECTOR targetPosition = XMLoadFloat3(&target);
	//(仮の)上方向
	XMVECTOR upVector = XMLoadFloat3(&up);

	//カメラZ軸
	XMVECTOR cameraAxisZ = XMVectorSubtract(targetPosition, eyePosition);
	//0ベクトルだと向きが定まらないので除外
	assert(!XMVector3Equal(cameraAxisZ, XMVectorZero()));
	assert(!XMVector3IsInfinite(cameraAxisZ));
	assert(!XMVector3Equal(upVector, XMVectorZero()));
	assert(!XMVector3IsInfinite(upVector));
	//ベクトルを正規化
	cameraAxisZ = XMVector3Normalize(cameraAxisZ);

	//カメラのX軸(右方向)
	XMVECTOR cameraAxisX;
	//X軸は上方向→Z軸の外積で決まる
	cameraAxisX = XMVector3Cross(upVector, cameraAxisZ);
	//ベクトルを正規化
	cameraAxisX = XMVector3Normalize(cameraAxisX);

	//カメラのY軸
	XMVECTOR cameraAxisY;
	//Y軸はZ軸→X軸の外積で求まる
	cameraAxisY = XMVector3Cross(cameraAxisZ, cameraAxisX);
	/*cameraAxisY = XMVector3Normalize(cameraAxisY);*/

	//全方向ビルボード行列の計算
	//ビルボード行列
	matBillboard_.r[0] = cameraAxisX;
	matBillboard_.r[1] = cameraAxisY;
	matBillboard_.r[2] = cameraAxisZ;
	matBillboard_.r[3] = XMVectorSet(0, 0, 0, 1);
}

void CameraState::UpdateHitWall(JSONLoader::ColliderData objectColliderData)
{
	//プレイヤーから原点のベクトル
	XMFLOAT3 vec = XMFLOAT3(0.0f, 0.0f, 0.0f) - eye_;
	//壁の外にいる時のみ
	while (ColliderManager::CheckCollider(colliderData, objectColliderData) == false)
	{
		//プレイヤーから原点のベクトルを正規化
		vec = normalize(vec);
		//壁の中に戻るまで加算
		eye_ = eye_ + (vec * knockBackSpeed);
		//コライダーデータの座標更新
		colliderData.center = eye_;
	}
}
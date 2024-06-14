#include "Camera.h"

//プレイヤーに追従
class FollowPlayer : public CameraState
{
public:
	//コライダーの処理
	void UpdateCollider() override;
	//ステートごとの動き
	void Move();
};

//タイトル
class Title : public CameraState
{
public:
	//ステートごとの動き
	void Move();
private:
	//視点座標用
	XMFLOAT3 addTitleEye = { -10.0f,6.0f,50.0f };
	//注視点用
	XMFLOAT3 addTitleTarget = { 30.0f,40.0f,0.0f };
};

//チュートリアル
class Tutorial : public CameraState
{
public:
	//ステートごとの動き
	void Move();
};

//フェーズの移動
class MovePhase1 : public CameraState
{
public:
	//ステートごとの動き
	void Move();
};

//クリア
class Clear : public CameraState
{
public:
	//ステートごとの動き
	void Move();
};
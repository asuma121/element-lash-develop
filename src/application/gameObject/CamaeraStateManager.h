#include "Camera.h"

//プレイヤーに追従
class FallowPlayer : public CameraState
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
};

//チュートリアル
class Tutorial : public CameraState
{
public:
	//ステートごとの動き
	void Move();
};

//フェーズの移動
class MovePhase : public CameraState
{
public:
	//ステートごとの動き
	void Move();
};

//クリア
class CLear : public CameraState
{
public:
	//ステートごとの動き
	void Move();
};
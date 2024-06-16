#include "Enemy.h"

//チュートリアルシーン
class TitleAttackOmen1 : public EnemyState
{
public:
	//オブジェクトごとの初期化
	void InitializeState();
	//ステートごとの動き
	void Move();
	//ステートの更新
	void UpdateState(Enemy* enemy);
};

//チュートリアルの棒立ち
class TutorialStand : public EnemyState
{
public:
	//オブジェクトごとの初期化
	void InitializeState();
	//ステートごとの動き
	void Move();
	//ステートの更新
	void UpdateState(Enemy* enemy);
};

//チュートリアルの攻撃前兆
class TutorialAttackOmen1 : public EnemyState
{
public:
	//オブジェクトごとの初期化
	void InitializeState();
	//ステートごとの動き
	void Move();
	//ステートの更新
	void UpdateState(Enemy* enemy);
};

//フェーズ移動 攻撃前兆
class MovePhaseAttackOmen1 : public EnemyState
{
public:
	//オブジェクトごとの初期化
	void InitializeState();
	//ステートごとの動き
	void Move();
	//ステートの更新
	void UpdateState(Enemy* enemy);
};

//フェーズ移動 敵呼び出し
class MovePhaseCallMiniEnemy : public EnemyState
{
public:
	//オブジェクトごとの初期化
	void InitializeState();
	//ステートごとの動き
	void Move();
	//ステートの更新
	void UpdateState(Enemy* enemy);
	//攻撃更新
	void UpdateAttack()override;
};

//フェーズ移動 転ぶ
class MovePhaseFallDown : public EnemyState
{
public:
	//オブジェクトごとの初期化
	void InitializeState();
	//ステートごとの動き
	void Move();
	//ステートの更新
	void UpdateState(Enemy* enemy);
};

//フェーズ移動 起き上がり
class MovePhaseGetUp : public EnemyState
{
public:
	//オブジェクトごとの初期化
	void InitializeState();
	//ステートごとの動き
	void Move();
	//ステートの更新
	void UpdateState(Enemy* enemy);
};

//クリア 
class ClearAttackOmen1 : public EnemyState
{
public:
	//オブジェクトごとの初期化
	void InitializeState();
	//ステートごとの動き
	void Move();
	//クリア専用更新
	void UpdateParticleClear()override;
	//ステートの更新
	void UpdateState(Enemy* enemy);
};

//棒立ち
class Stand : public EnemyState
{
public:
	//オブジェクトごとの初期化
	void InitializeState();
	//ステートごとの動き
	void Move();
	//ステートの更新
	void UpdateState(Enemy* enemy);
};

//歩き
class Walk : public EnemyState
{
public:
	//オブジェクトごとの初期化
	void InitializeState();
	//ステートごとの動き
	void Move();
	//ステートの更新
	void UpdateState(Enemy* enemy);
};

//攻撃1
class Attack01 : public EnemyState
{
public:
	//オブジェクトごとの初期化
	void InitializeState();
	//ステートごとの動き
	void Move();
	//ステートの更新
	void UpdateState(Enemy* enemy);
};

//攻撃前兆
class AttackOmen1 : public EnemyState
{
public:
	//オブジェクトごとの初期化
	void InitializeState();
	//ステートごとの動き
	void Move();
	//ステートの更新
	void UpdateState(Enemy* enemy);
	//攻撃更新
	void UpdateAttack()override;
};

//ダッシュ
class Dash : public EnemyState
{
public:
	//オブジェクトごとの初期化
	void InitializeState();
	//ステートごとの動き
	void Move();
	//ステートの更新
	void UpdateState(Enemy* enemy);
	//壁との当たり判定処理
	void UpdateHitWall(JSONLoader::ColliderData objectColliderData) override;
	//柱との当たり判定
	void UpdateHitPiller(JSONLoader::ColliderData objectColliderData, int pillerNum)override;

public:	//メンバ変数

	//オブジェクトと衝突フラグ
	bool hitObjectFlag = false;
	//オブジェクト衝突時の押し戻し
	float knockBackSpeed = 0.1f;

	//一度プレイヤーに衝突したらオブジェクトにぶつかるまで同じ方向へダッシュ
	XMFLOAT3 dashVec = { 0.0f, 0.0f, 0.0f };
	bool dashFlag = false;
};

//敵呼び出し
class CallMiniEnemy : public EnemyState
{
	public:
		//オブジェクトごとの初期化
		void InitializeState();
		//ステートごとの動き
		void Move();
		//ステートの更新
		void UpdateState(Enemy* enemy);
		//攻撃更新
		void UpdateAttack()override;
};

//転ぶ
class FallDown : public EnemyState
{
public:
	//オブジェクトごとの初期化
	void InitializeState();
	//ステートごとの動き
	void Move();
	//ステートの更新
	void UpdateState(Enemy* enemy);
	//コライダーデータの処理
	void UpdateColliderDate()override;
};

//起き上がり
class GetUp : public EnemyState
{
public:
	//オブジェクトごとの初期化
	void InitializeState();
	//ステートごとの動き
	void Move();
	//ステートの更新
	void UpdateState(Enemy* enemy);
};
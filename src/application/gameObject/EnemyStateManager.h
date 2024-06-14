#include "Enemy.h"

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
	//チュートリアルのステート更新
	void UpdateStateTutorial(Enemy* enemy)override;
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
	//クリア専用更新
	void UpdateParticleClear()override;
	//ステートの更新
	void UpdateState(Enemy* enemy);
	//タイトルのステート更新
	void UpdateStateTitle(Enemy* enemy)override;
	//チュートリアルのステート更新
	void UpdateStateTutorial(Enemy* enemy)override;
	//ゲームのステート更新
	void UpdateStateMovePhase(Enemy* enemy)override;
	//ゲームのステート更新
	void UpdateStateClear(Enemy* enemy)override;
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
		//ゲームのステート更新
		void UpdateStateMovePhase(Enemy* enemy)override;
		//攻撃更新
		void UpdateAttack()override;
		//フェーズ移動の処理
		void UpdateAttackMovePhase()override;
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
	//ゲームのステート更新
	void UpdateStateMovePhase(Enemy* enemy)override;
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
	//ゲームのステート更新
	void UpdateStateMovePhase(Enemy* enemy)override;
};
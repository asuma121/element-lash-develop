#include "Enemy.h"

//棒立ち
class Stand : public EnemyState
{
public:
	//オブジェクトごとの初期化
	void Initialize();
	//ステートごとの動き
	void Move();
	//ステートの更新
	void UpdateState(Enemy* enemy);
	//チュートリアルのステート更新
	void UpdateStateTutorial(Enemy* enemy)override;
};

class Walk : public EnemyState
{
public:
	//オブジェクトごとの初期化
	void Initialize();
	//ステートごとの動き
	void Move();
	//ステートの更新
	void UpdateState(Enemy* enemy);
};

class Attack01 : public EnemyState
{
public:
	//オブジェクトごとの初期化
	void Initialize();
	//ステートごとの動き
	void Move();
	//ステートの更新
	void UpdateState(Enemy* enemy);
};

class AttackOmen1 : public EnemyState
{
public:
	//オブジェクトごとの初期化
	void Initialize();
	//ステートごとの動き
	void Move();
	//クリア専用更新
	void UpdateParticleClear()override;
	//ステートの更新
	void UpdateState(Enemy* enemy);
	//チュートリアルのステート更新
	void UpdateStateTutorial(Enemy* enemy)override;
	//ゲームのステート更新
	void UpdateStateMovePhase(Enemy* enemy)override;
	//ゲームのステート更新
	void UpdateStateClear(Enemy* enemy)override;
	//攻撃更新
	void UpdateAttack()override;
};

class Dash : public EnemyState
{
public:
	//オブジェクトごとの初期化
	void Initialize();
	//ステートごとの動き
	void Move();
	//ステートの更新
	void UpdateState(Enemy* enemy);
	//壁との当たり判定処理
	void UpdateHitWall(JSONLoader::ColliderData objectColliderData) override;
	//柱との当たり判定
	void UpdateHitPiller(JSONLoader::ColliderData objectColliderData)override;

public:	//メンバ変数

	//オブジェクトと衝突フラグ
	bool hitObjectFlag = false;
	//オブジェクト衝突時の押し戻し
	float knockBackSpeed = 0.001f;

	//一度プレイヤーに衝突したらオブジェクトにぶつかるまで同じ方向へダッシュ
	XMFLOAT3 dashVec = { 0.0f, 0.0f, 0.0f };
	bool dashFlag = false;
};

class CallMiniEnemy : public EnemyState
{
	public:
		//オブジェクトごとの初期化
		void Initialize();
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

class FallDown : public EnemyState
{
public:
	//オブジェクトごとの初期化
	void Initialize();
	//ステートごとの動き
	void Move();
	//ステートの更新
	void UpdateState(Enemy* enemy);
	//ゲームのステート更新
	void UpdateStateMovePhase(Enemy* enemy)override;
};

class GetUp : public EnemyState
{
public:
	//オブジェクトごとの初期化
	void Initialize();
	//ステートごとの動き
	void Move();
	//ステートの更新
	void UpdateState(Enemy* enemy);
	//ゲームのステート更新
	void UpdateStateMovePhase(Enemy* enemy)override;
};
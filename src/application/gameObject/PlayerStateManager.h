#include "Player.h"

//棒立ち
class Wait : public PlayerState
{
public:
	//オブジェクトごとの初期化
	void InitializeState();
	//ステートの更新
	void UpdateState(Player* player);
};

//走ってる状態
class Run : public PlayerState
{
public:
	//オブジェクトごとの初期化
	void InitializeState();
	//ステートの更新
	void UpdateState(Player* player);
};

//攻撃1 雷
class Attack1 : public PlayerState
{
public:
	//オブジェクトごとの初期化
	void InitializeState();
	//ステートの更新
	void UpdateState(Player* player);
	//オブジェクトごとの攻撃
	void UpdateAttack() override;
	//動き
	void Move() override;

private:

	//オブジェクトごとのタイマー
	int attack1Time = 150;

	//一度に出す雷パーティクルの数
	int elecVol = 5;
	//雷パーティクルを出すフレームの間隔
	int elecInterval = 7;
	//でかい雷のスケール
	float elecStartSlace1 = 5.0f;
	float elecEndSlace1 = 5.0f;
	//細かい雷のスケール
	float elecStartSlace2 = 0.7f;
	float elecEndSlace2 = 0.1f;
	//連続攻撃の入力フレーム
	float AttackIntervalTime = 50.0f;
	//雷を出すフレーム
	int elecFlame = 40;
	//雷の横揺れの強さ
	float elecStrength = 4.0f;
	//雷を発生させる場所
	XMFLOAT3 addElecPos1 = { 0.0f, 11.0f, 8.0f };
};

//攻撃2 雷
class Attack2 : public PlayerState
{
public:
	//オブジェクトごとの初期化
	void InitializeState();
	//ステートの更新
	void UpdateState(Player* player);
	//オブジェクトごとの攻撃
	void UpdateAttack()override;
	//動き
	void Move() override;

private:
	//オブジェクトごとのタイマー
	int attack2Time = 145;

	//一度に出す雷パーティクルの数
	int elecVol = 5;
	//雷パーティクルを出すフレームの間隔
	int elecInterval = 7;
	//でかい雷のスケール
	float elecStartSlace1 = 5.0f;
	float elecEndSlace1 = 5.0f;
	//細かい雷のスケール
	float elecStartSlace2 = 0.7f;
	float elecEndSlace2 = 0.1f;
	//連続攻撃の入力フレーム
	float AttackIntervalTime = 50.0f;
	//雷を出すフレーム
	int elecFlame = 40;
	//雷の横揺れの強さ
	float elecStrength = 4.0f;
	//雷を発生させる場所
	XMFLOAT3 addElecPos1 = { 0.0f, 11.0f, 5.0f };
};

//攻撃3 炎
class Attack3 : public PlayerState
{
public:
	//オブジェクトごとの初期化
	void InitializeState();
	//ステートの更新
	void UpdateState(Player* player);
	//オブジェクトごとの攻撃
	void UpdateAttack()override;
	//動き
	void Move() override;

private:

	//炎を出す間隔
	int bullet1Interval = 2;
	//炎のスピード
	float bullet1Speed = 1.9f;
	//炎のスケール
	XMFLOAT3  bullet1Scale = { 10.0f,10.0f,10.0f };
	XMFLOAT3  bullet1LastScale = { 1.0f,1.0f,1.0f };
	//炎を発生させる位置
	XMFLOAT3 bullet1AddPosition = { 0.0f,10.0f,0.0f };
	//炎を消すフレーム
	float bullet1Frame = 60.0f;

	//炎中の移動スピード
	float attack3PosSpeed = 0.5f;
};

//ダウン
class Down : public PlayerState
{
public:
	//オブジェクトごとの初期化
	void InitializeState();
	//ステートの更新
	void UpdateState(Player* player);
	//動き
	void Move() override;
};

//立ち上がり
class StandUp : public PlayerState
{
public:
	//オブジェクトごとの初期化
	void InitializeState();
	//ステートの更新
	void UpdateState(Player* player);
	//動き
	void Move() override;
};

//棒立ちデバッグ
class DevelopWait : public PlayerState
{
public:
	//オブジェクトごとの初期化
	void InitializeState();
	//ステートの更新
	void UpdateState(Player* player);
};

//走ってる状態デバッグ
class DevelopRun : public PlayerState
{
public:
	//オブジェクトごとの初期化
	void InitializeState();
	//ステートの更新
	void UpdateState(Player* player);
};

//ダウンデバッグ
class DevelopDown : public PlayerState
{
public:
	//オブジェクトごとの初期化
	void InitializeState();
	//ステートの更新
	void UpdateState(Player* player);
};

//炎攻撃デバッグ
class DevelopAttack3 : public PlayerState
{
public:
	//オブジェクトごとの初期化
	void InitializeState();
	//ステートの更新
	void UpdateState(Player* player);
};

//立ち上がりデバッグ
class DevelopStandUp : public PlayerState
{
public:
	//オブジェクトごとの初期化
	void InitializeState();
	//ステートの更新
	void UpdateState(Player* player);
};
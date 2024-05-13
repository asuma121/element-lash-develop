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
	//描画
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//ライト目線描画
	void DrawLightView(ID3D12GraphicsCommandList* cmdList);
	//SRVセット
	void SetSRV(ID3D12DescriptorHeap* SRV);
	//オブジェクト更新
	void UpdateObject();
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
	//描画
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//ライト目線描画
	void DrawLightView(ID3D12GraphicsCommandList* cmdList);
	//SRVセット
	void SetSRV(ID3D12DescriptorHeap* SRV);
	//オブジェクト更新
	void UpdateObject();
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
	//描画
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//ライト目線描画
	void DrawLightView(ID3D12GraphicsCommandList* cmdList);
	//SRVセット
	void SetSRV(ID3D12DescriptorHeap* SRV);
	//オブジェクト更新
	void UpdateObject();
};

class AttackOmen1 : public EnemyState
{
public:
	//オブジェクトごとの初期化
	void Initialize();
	//ステートごとの動き
	void Move();
	//ステートの更新
	void UpdateState(Enemy* enemy);
	//描画
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//ライト目線描画
	void DrawLightView(ID3D12GraphicsCommandList* cmdList);
	//SRVセット
	void SetSRV(ID3D12DescriptorHeap* SRV);
	//オブジェクト更新
	void UpdateObject();
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
	//描画
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//ライト目線描画
	void DrawLightView(ID3D12GraphicsCommandList* cmdList);
	//SRVセット
	void SetSRV(ID3D12DescriptorHeap* SRV);
	//オブジェクト更新
	void UpdateObject();
	//壁との当たり判定処理
	void UpdateHitWall(JSONLoader::ColliderData objectColliderData) override;
	//柱との当たり判定
	void UpdateHitPiller(JSONLoader::ColliderData objectColliderData)override;

public:	//メンバ変数

	//オブジェクトと衝突フラグ
	bool hitObjectFlag = false;
	//オブジェクト衝突時の押し戻し
	float knockBackSpeed = 0.001f;
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
		//描画
		void Draw(ID3D12GraphicsCommandList* cmdList);
		//ライト目線描画
		void DrawLightView(ID3D12GraphicsCommandList* cmdList);
		//SRVセット
		void SetSRV(ID3D12DescriptorHeap* SRV);
		//オブジェクト更新
		void UpdateObject();
};
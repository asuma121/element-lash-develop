#include "EnemyStateManager.h"
#include "mathOriginal.h"
#include "ColliderManager.h"

void Stand::Initialize()
{
	//アニメーションの設定
	objectStand->StopAnimation();
	objectStand->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;
}

void Stand::Move()
{
}

void Stand::UpdateState(Enemy* enemy)
{
}

void Stand::Draw(ID3D12GraphicsCommandList* cmdList)
{
	objectStand->Draw(cmdList);
}

void Stand::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	objectStand->DrawLightView(cmdList);
}

void Stand::SetSRV(ID3D12DescriptorHeap* SRV)
{
	objectStand->SetSRV(SRV);
}

void Stand::UpdateObject()
{
	objectStand->SetPosition(position);
	objectStand->SetRotation(rotation);
	objectStand->SetScale(scale);
	objectStand->Update();
}

void Walk::Initialize()
{
	//アニメーションの設定
	objectWalk->StopAnimation();
	objectWalk->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;
}

void Walk::Move()
{
	//プレイヤーと敵のベクトル取得
	XMFLOAT3 velo = playerPos - position;
	//敵がプレイヤーの向きを向くようにする
	rotation.y = getVectorRotation(velo).y;

	//プレイヤーに近づく
	position = position + normalize(velo) * walkSpeed;
}

void Walk::UpdateState(Enemy* enemy)
{
}

void Walk::Draw(ID3D12GraphicsCommandList* cmdList)
{
	objectWalk->Draw(cmdList);
}

void Walk::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	objectWalk->DrawLightView(cmdList);
}

void Walk::SetSRV(ID3D12DescriptorHeap* SRV)
{
	objectWalk->SetSRV(SRV);
}

void Walk::UpdateObject()
{
	objectWalk->SetPosition(position);
	objectWalk->SetRotation(rotation);
	objectWalk->SetScale(scale);
	objectWalk->Update();
}

void Attack01::Initialize()
{
	//アニメーションの設定
	objectAttack1->StopAnimation();
	objectAttack1->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;
}

void Attack01::Move()
{
}

void Attack01::UpdateState(Enemy* enemy)
{
}

void Attack01::Draw(ID3D12GraphicsCommandList* cmdList)
{
	objectAttack1->Draw(cmdList);
}

void Attack01::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	objectAttack1->DrawLightView(cmdList);
}

void Attack01::SetSRV(ID3D12DescriptorHeap* SRV)
{
	objectAttack1->SetSRV(SRV);
}

void Attack01::UpdateObject()
{
	objectAttack1->SetPosition(position);
	objectAttack1->SetRotation(rotation);
	objectAttack1->SetScale(scale);
	objectAttack1->Update();
}

void AttackOmen1::Initialize()
{
	//アニメーションの設定
	objectAttackOmen1->StopAnimation();
	objectAttackOmen1->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;
}

void AttackOmen1::Move()
{
}

void AttackOmen1::UpdateState(Enemy* enemy)
{
}

void AttackOmen1::Draw(ID3D12GraphicsCommandList* cmdList)
{
	objectAttackOmen1->Draw(cmdList);
}

void AttackOmen1::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	objectAttackOmen1->DrawLightView(cmdList);
}

void AttackOmen1::SetSRV(ID3D12DescriptorHeap* SRV)
{
	objectAttackOmen1->SetSRV(SRV);
}

void AttackOmen1::UpdateObject()
{
	objectAttackOmen1->SetPosition(position);
	objectAttackOmen1->SetRotation(rotation);
	objectAttackOmen1->SetScale(scale);
	objectAttackOmen1->Update();
}

void Dash::Initialize()
{
	//アニメーションの設定
	objectDash->StopAnimation();
	objectDash->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;
}

void Dash::Move()
{
	//プレイヤーと敵のベクトル取得
	XMFLOAT3 velo = playerPos - position;

	velo = normalize(velo);

	//敵がプレイヤーの向きを向くようにする
	rotation.y = getVectorRotation(velo).y;

	//プレイヤーに近づく
	position = position + velo * dashSpeed;
}

void Dash::UpdateState(Enemy* enemy)
{
	//オブジェクトに衝突したら倒れるモーションへ
	if (hitObjectFlag == true)
	{
		enemy->ChangeState(new Stand());
		return;
	}
}

void Dash::Draw(ID3D12GraphicsCommandList* cmdList)
{
	objectDash->Draw(cmdList);
}

void Dash::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	objectDash->DrawLightView(cmdList);
}

void Dash::SetSRV(ID3D12DescriptorHeap* SRV)
{
	objectDash->SetSRV(SRV);
}

void Dash::UpdateObject()
{
	objectDash->SetPosition(position);
	objectDash->SetRotation(rotation);
	objectDash->SetScale(scale);
	objectDash->Update();
}

void Dash::UpdateHitWall(JSONLoader::ColliderData objectColliderData)
{
	//壁の中にいたら処理終了
	if (ColliderManager::CheckCollider(colliderData, objectColliderData) == true)return;

	//壁の外にいる時のみ
	while (ColliderManager::CheckCollider(colliderData, objectColliderData) == false)
	{
		//プレイヤーから原点のベクトル
		XMFLOAT3 vec = XMFLOAT3(0.0f, 0.0f, 0.0f) - position;
		//プレイヤーから原点のベクトルを正規化
		vec = normalize(vec);
		//壁の中に戻るまで加算
		position = position + (vec * knockBackSpeed);
		//コライダーデータの座標更新
		colliderData.center = position;
	}
	//フラグを立てる
	hitObjectFlag = true;
}

void Dash::UpdateHitPiller(JSONLoader::ColliderData objectColliderData)
{
	//柱に衝突してなかったら処理終了
	if(ColliderManager::CheckCollider(colliderData, objectColliderData) == false)return;

	//柱にめり込んでいる間
	while (ColliderManager::CheckCollider(colliderData, objectColliderData) == true)
	{
		//柱からプレイヤーのベクトル
		XMFLOAT3 vec = objectColliderData.center - colliderData.center;
		//プレイヤーから原点のベクトルを正規化
		vec = normalize(vec);
		//壁の中に戻るまで加算
		position = position - (vec * knockBackSpeed);
		//コライダーデータの座標更新
		colliderData.center = position;
	}
	//フラグを立てる
	hitObjectFlag = true;
}

void CallMiniEnemy::Initialize()
{
	//アニメーションの設定
	objectCallMiniEnemy->StopAnimation();
	objectCallMiniEnemy->PlayAnimation();

	//タイマーの設定
	objectTimer = 0;
	objectTimeFlag = false;
}

void CallMiniEnemy::Move()
{
}

void CallMiniEnemy::UpdateState(Enemy* enemy)
{
}

void CallMiniEnemy::Draw(ID3D12GraphicsCommandList* cmdList)
{
	objectCallMiniEnemy->Draw(cmdList);
}

void CallMiniEnemy::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	objectCallMiniEnemy->DrawLightView(cmdList);
}

void CallMiniEnemy::SetSRV(ID3D12DescriptorHeap* SRV)
{
	objectCallMiniEnemy->SetSRV(SRV);
}

void CallMiniEnemy::UpdateObject()
{
	objectCallMiniEnemy->SetPosition(position);
	objectCallMiniEnemy->SetRotation(rotation);
	objectCallMiniEnemy->SetScale(scale);
	objectCallMiniEnemy->Update();
}


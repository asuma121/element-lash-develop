#include "GameScene.h"

//ゲームシーン フェーズ1
class Phase1 : public PhaseState
{
public:
	void PhaseInitialize();
	void DrawFBXLightView();
	void NextPhase(GameScene* gameScene);
	void UpdateObject();
	void UpdateCollider();
	void DrawFBX();
	void DrawSprite();
	void DrawParticle();
};

//ゲームシーン フェーズ2
class Phase2 : public PhaseState
{
public:
	void PhaseInitialize();
	void DrawFBXLightView();
	void NextPhase(GameScene* gameScene);
	void UpdateObject();
	void UpdateCollider();
	void DrawFBX();
	void DrawSprite();
	void DrawParticle();
};

//ゲームシーン フェーズ1から2へ
class MovePhase : public PhaseState
{
public:
	void PhaseInitialize();
	void DrawFBXLightView();
	void NextPhase(GameScene* gameScene);
	void UpdateObject();
	void UpdateCollider();
	void DrawFBX();
	void DrawSprite();
	void DrawParticle();
public:
	//フェーズ移動の時間 敵の全アニメーション+黒幕
	int movePhaseTime = 746 + 120;
};
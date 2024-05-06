#include "GameScene.h"

//ゲームシーン フェーズ1
class Phase1 : public PhaseState
{
public:
	void DrawFBXLightView();
	void SetSRV(ID3D12DescriptorHeap* SRV);
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
	void DrawFBXLightView();
	void SetSRV(ID3D12DescriptorHeap* SRV);
	void NextPhase(GameScene* gameScene);
	void UpdateObject();
	void UpdateCollider();
	void DrawFBX();
	void DrawSprite();
	void DrawParticle();
};
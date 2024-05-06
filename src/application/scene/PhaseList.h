#include "GameScene.h"

//�Q�[���V�[�� �t�F�[�Y1
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

//�Q�[���V�[�� �t�F�[�Y2
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
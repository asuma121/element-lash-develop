#include "GameScene.h"

//�Q�[���V�[�� �t�F�[�Y1
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

//�Q�[���V�[�� �t�F�[�Y2
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

//�Q�[���V�[�� �t�F�[�Y1����2��
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
	//�t�F�[�Y�ړ��̎��� �G�̑S�A�j���[�V����+����
	int movePhaseTime = 746 + 120;
};
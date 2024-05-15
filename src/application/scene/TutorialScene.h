#pragma once

#include "memory"
#include "list"
#include "DirectXMath.h"
#include "Input.h"
#include "DXInput.h"
#include "DirectXCommon.h"
#include "Camera.h"
#include "Sprite.h"
#include "Player.h"
#include "Enemy.h"
#include "TutorialEnemy.h"
#include "Plane.h"
#include "UI.h"
#include "SceneManager.h"
#include "Terrain.h"

class TutorialScene : public SceneState
{
private:	//�G�C���A�X
	//Microsoft::WRL::���ȗ�
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:	//�ÓI�����o�ϐ�

	/// <summary>
	///������
	/// </summary>
	static void SetDevice(DirectXCommon* dxCommon, Input* input, DXInput* dxInput);

	/// <summary>
	///�`���[�g���A���V�[���Ŏg���I�u�W�F�N�g�Z�b�g
	/// </summary>
	static void SetGameObject(Player* player, Enemy* enemy,TutorialEnemy* tutorialEnemy,Plane* plane, Terrain* terrain, Camera* camera, Light* light, UI* ui);

public: //�����o�֐�

	TutorialScene();
	~TutorialScene();

	/// <summary>
	///������
	/// </summary>
	void Initialize();

	/// <summary>
	///�X�V
	/// </summary>
	void Update();

	void NextScene(Scene* pScene);

	/// <summary>
	///�I�u�W�F�N�g�X�V
	/// </summary>
	void UpdateObject();

	/// <summary>
	///�X�v���C�g�X�V
	/// </summary>
	void UpdateSprite();

	/// <summary>
	///�R���C�_�[�X�V
	/// </summary>
	void UpdateCollider();

	/// <summary>
	///�p�[�e�B�N���X�V
	/// </summary>
	void UpdateParticle();

	/// <summary>
	///���Z�b�g
	/// </summary>
	void Reset();

	/// <summary>
	///�`��
	/// </summary>
	void Draw();

	/// <summary>
	///FBX�`��
	/// </summary>
	void DrawFBX();

	/// <summary>
	///�X�v���C�g�`��
	/// </summary>
	void DrawSprite();

	/// <summary>
	///�p�[�e�B�N���`��
	/// </summary>
	void DrawParticle();

	/// <summary>
	///���C�g�ڐ��̕`��
	/// </summary>
	void DrawFBXLightView();

	/// <summary>
	///�Z�b�^�[
	/// </summary>
	void SetSRV(ID3D12DescriptorHeap* SRV);

	/// <summary>
	///�Q�b�^�[
	/// </summary>
	DirectX::XMMATRIX GetLightViewProjection();

private:	//�ÓI�����o�ϐ�
	//�f�o�C�X��input
	static DirectXCommon* dxCommon;
	static Input* input;
	static DXInput* dxInput;
	//�J����
	static Camera* camera;
	//���C�g
	static Light* light;
	//�v���C���[
	static Player* player;
	//�G
	static Enemy* enemy;
	//�`���[�g���A���p�G
	static TutorialEnemy* tutorialEnemy;
	//��
	static Plane* plane;
	//�n�`
	static Terrain* terrain;
	//UI
	static UI* ui;

private:	//�����o�ϐ�

	float lightDir[3] = { 0.0f,-1.0f , -1.0f };
	float lightPos[3] = { 0.0f,25.0f,25.0f };
	float lightTarget[3] = { 0.0f,0.0f,0.0f };
	float lightFactorAngle[2] = { 20.0f,30.0f, };
	float lightAtten[3] = { 0.0f,0.0f,0.0f };
	
	//�X�v���C�g�p�^�C�}�[
	float blackSpriteTimer = 0.0f;
	float blackSpriteMaxTime = 120.0f;
	int tutorialSpriteFlag = 1;	//���̔ԍ��̃X�v���C�g�`��
	int tutorialLStickTimer = 0.0f;
	int tutorialLStickMaxTime = 240.0f;
	int tutorialRStickTimer = 0.0f;
	int tutorialRStickMaxTime = 240.0f;
	int tutorialIikannjiTimer = 0.0f;
	int tutorialIikannjiMaxTime = 200.0f;
	int tutorialAttackTimer = 0.0f;
	int tutorialAttackMaxTime = 200.0f;
	int tutorialAttack2Timer = 0.0f;
	int tutorialAttack2MaxTime = 2.0f;
	int tutorial12Timer = 0.0f;
	int tutorial12MaxTime = 120.0f;
	int tutorial13Timer = 0.0f;
	int tutorial13MaxTime = 320.0f;

	//�^�C�}�[
	float gameTimer = 0.0f;

	//�V�[���J�ڃt���O
	bool moveGameFlag = false;
};
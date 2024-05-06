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
#include "Plane.h"
#include "UI.h"
#include "SceneManager.h"

class ClearScene : public SceneState
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
	///�Q�[���V�[���Ŏg���I�u�W�F�N�g�Z�b�g
	/// </summary>
	static void SetGameObject(Player* player, Enemy* enemy, Plane* plane, Camera* camera, Light* light, UI* ui);

public: //�����o�֐�

	ClearScene();
	~ClearScene();

	/// <summary>
	///������
	/// </summary>
	void Initialize();

	/// <summary>
	///�X�V
	/// </summary>
	void Update();

	/// <summary>
	///���̃V�[���ֈړ�
	/// </summary>
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
	///�p�[�e�B�N���X�V
	/// </summary>
	void UpdateParticle();

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
	bool GetMoveTitle() { return moveTitleFlag; }
	bool GetMoveTutorial() { return moveTutorialFlag; }
	bool GetMoveGame() { return moveGameFlag; }
	bool GetMoveGame2() { return moveGame2Flag; }

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
	//��
	static Plane* plane;
	//UI
	static UI* ui;

public:	//�����o�ϐ�

	float lightDir[3] = { 0.0f,-1.0f , -1.0f };
	float lightPos[3] = { 0.0f,25.0f,25.0f };
	float lightTarget[3] = { 0.0f,0.0f,0.0f };
	float lightFactorAngle[2] = { 20.0f,30.0f, };
	float lightAtten[3] = { 0.0f,0.0f,0.0f };

	//�����X�v���C�g
	std::unique_ptr<Sprite>blackSprite1;
	std::unique_ptr<Sprite>blackSprite2;
	//�����X�v���C�g ���W �X�P�[��
	XMFLOAT2 black1Pos = { 0.0f, 0.0f };
	XMFLOAT2 black1Scale = { 1280.0f, 720.0f };
	XMFLOAT2 black2Pos = { 0.0f, 0.0f };
	XMFLOAT2 black2Scale = { 1280.0f, 720.0f };
	//�N���A�V�[���p�X�v���C�g
	std::unique_ptr<Sprite>clear1Sprite;
	//�N���A�V�[���p�X�v���C�g ���W �X�P�[��
	XMFLOAT2 clear1Pos = { 150.0f, 300.0f };
	XMFLOAT2 clear1Scale = { 860.0f, 77.0f };

	//�^�C�}�[
	float gameTimer = 0.0f;

	//�V�[���J�ڗp
	bool clearFromGameFlag = false;
	float clearFromGameTimer = 0.0f;
	float clearFromGameTime = 500.0f;

	bool moveTitleFlag = false;
	bool moveGameFlag = false;
	bool moveGame2Flag = false;
	bool moveTutorialFlag = false;
};
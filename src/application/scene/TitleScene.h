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
#include "Terrain.h"
#include "UI.h"
#include "SceneManager.h"

class TitleScene : public SceneState
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
	static void SetGameObject(Player* player, Terrain* terrain, Camera* camera, Light* light, UI* ui);

public: //�����o�֐�

	TitleScene();
	~TitleScene();

	/// <summary>
	///������
	/// </summary>
	void Initialize();

	/// <summary>
	///�X�V
	/// </summary>
	void Update();

	/// <summary>
	///�V�[���J��
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
	///�V�[���J�ڍX�V
	/// </summary>
	void UpdateMoveScene();

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
	//�I�u�W�F�N�g
	static Terrain* terrain;
	//UI
	static UI* ui;

public:	//�����o�ϐ�

	//�V�[���S�̂̃^�C�}�[
	int sceneTimer = 0;

	//���C�g
	float lightDir[3] = { 0.0f,-1.0f , -1.0f };
	float lightPos[3] = { 0.0f,25.0f,25.0f };
	float lightTarget[3] = { 0.0f,0.0f,0.0f };
	float lightFactorAngle[2] = { 20.0f,30.0f, };
	float lightAtten[3] = { 0.0f,0.0f,0.0f };

	//�V�[���J�ڗp
	int titleMoveTime = 120.0f;

	//�����X�v���C�g
	std::unique_ptr<Sprite>blackSprite1;
	//�����X�v���C�g ���W �X�P�[��
	XMFLOAT2 black1Pos = { 0.0f, 0.0f };
	XMFLOAT2 black1Scale = { 1280.0f, 720.0f };
	//�����X�v���C�g�p�̎���
	int blackSpriteTime = 220;

	//�V�[���J�ڗp�t���O �V�[���}�l�[�W���[�ɓn��
	bool moveTutorialFlag1 = false;

	//�V�[���J�ڗp�t���O ������ŊǗ�����p
	bool moveTutorialFlag2 = false;

	//�V�[���J�ڗp�^�C�}�[
	int moveTutorialTimer = 0;
	//�V�[���J�ڂ̎���
	int moveTutorialTime = 300;

	float debugNum[1] = { 0.0f };
};
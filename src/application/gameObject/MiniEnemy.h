/**
 * @file TutorialEnemy.h
 * @brief �Q�[���I�u�W�F�N�g �G
 * @author Asuma Syota
 * @date 2023/4
 */

#pragma once
#include "DirectXMath.h"
#include "FbxObject3D.h"
#include "JSONLoader.h"
#include "BillboardSprite.h"

class MiniEnemy
{
private:	//�G�C���A�X
	//Microsoft::WRL::���ȗ�
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private:	//�T�u�N���X

	enum Status	//�G�̏��
	{
		Dash,
		Down,
	};

	struct Enemy
	{
		//�I�u�W�F�N�g
		FbxObject3D* objectDash;
		FbxObject3D* objectDown;
		//�R���C�_�[�f�[�^
		JSONLoader::ColliderData colliderData;
		//���W
		XMFLOAT3 position;
		//�p�x
		XMFLOAT3 rotation;
		//�X�e�[�^�X
		Status status;
		//�X�e�[�^�X
		Status preStatus;
		//HP
		int HP;
		//������t���O
		bool hitFireFlag;
		//������t���O
		bool hitElecFlag;
		//���S�t���O
		bool deadFlag;
		//���S�^�C�}�[
		int deadTimer;
	};

public://�����o�֐�

	/// <summary>
	///�J�����Z�b�g
	/// </summary>
	static void SetCamera(Camera* camera) { MiniEnemy::camera = camera; }

	/// <summary>
	///���̓Z�b�g
	/// </summary>
	static void SetInput(Input* input) { MiniEnemy::input = input; }

	/// <summary>
	/// �C���X�g���N�^ �f�X�g���N�^
	/// </summary>
	MiniEnemy() {};
	~MiniEnemy() {};

	/// <summary>
	///������
	/// </summary>
	void Initialize();

	/// <summary>
	///�X�V
	/// </summary>
	void Update();

	/// <summary>
	///�I�u�W�F�N�g�X�V
	/// </summary>
	void UpdateObject();

	/// <summary>
	///�X�v���C�g�X�V
	/// </summary>
	void UpdateSprite();

	/// <summary>
	///�R���C�_�[
	/// </summary>
	void UpdateCollider();

	/// <summary>
	///�_���[�W�n�S��
	/// </summary>
	void UpdateDamage();

	/// <summary>
	///�G�폜
	/// </summary>
	void DeleteEnemy();

	/// <summary>
	///�`��
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///���C�g���_�`��
	/// </summary>
	void DrawLightView(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///�X�v���C�g�`��
	/// </summary>
	void DrawSprite(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///�U���̏���
	/// </summary>
	void UpdateAttack();

	/// <summary>
	///�X�e�[�^�X�}�l�[�W���[
	/// </summary>
	void StatusManager();

	/// <summary>
	///srv�Z�b�g
	/// </summary>
	void SetSRV(ID3D12DescriptorHeap* SRV);

	/// <summary>
	///���W�Z�b�g
	/// </summary>
	/*void SetPosition(XMFLOAT3 position) { this->position = position; };*/

	/// <summary>
	///���Z�b�g
	/// </summary>
	void Reset();

	/// <summary>
	///�G��ǉ�����
	/// </summary>
	void AddEnemy(XMFLOAT3 pos);

	/// <summary>
	///���@�̒e��e��
	/// </summary>
	void HitFire(int num) { enemys[num].hitFireFlag = true; };

	/// <summary>
	///����e��
	/// </summary>
	/*void HitElec() { hitElec = true; };*/

	/// <summary>
	///�G�̐��擾
	/// </summary>
	int GetEnemyNum() { return enemys.size(); }

	/// <summary>
	///�X�P�[���擾
	/// </summary>
	XMFLOAT3 GetScale() { return scale; }

	/// <summary>
	///�R���C�_�[�擾
	/// </summary>
	JSONLoader::ColliderData GetColliderData(int num) { return enemys[num].colliderData; }

	/// <summary>
	///���S�t���O�擾
	/// </summary>
	/*bool GetIsDead() { return isDead; }*/

	/// <summary>
	///�v���C���[�̍��W�擾
	/// </summary>
	void SetPlayerPos(XMFLOAT3 playerPos) { this->playerPos = playerPos; }

	//�ÓI�����o�ϐ�
private:
	//�J����
	static Camera* camera;
	//�L�[�{�[�h
	static Input* input;

	//�����o�ϐ�
public:

	//�G�f�[�^
	std::vector<Enemy>enemys;

	//���f��
	FbxModel* modelDash = nullptr;
	FbxModel* modelDown= nullptr;

	//HP�̃r���{�[�h
	BillboardSpriteModel* hpFrameSpriteModel = nullptr;
	BillboardSprite* hpFrameSprite = nullptr;
	BillboardSpriteModel* hpBarSpriteModel = nullptr;
	BillboardSprite* hpBarSprite = nullptr;

	//HP�̃r���{�[�h�̍��W�A�X�P�[��
	XMFLOAT3 hpFrameScale = { 64.0f,9.6f,1.0f };
	XMFLOAT3 hpBarOriginalScale = { 60.5f,1.5f,1.0f };
	XMFLOAT3 hpBarScale = hpBarOriginalScale;
	XMFLOAT3 hpBarAddPos = { 0.0f,5.0f,0.0f };

	//�T�C�Y
	XMFLOAT3 scale = { 0.7f,0.7f,0.7f };

	//�R���C�_�[�֘A
	//�R���C�_�[�̃X�P�[��
	XMFLOAT3 colliderScale = { 3.0f,3.0f,3.0f };

	//HP
	float maxHP = 30;

	//���U���̃_���[�W
	int fireDamage = 1;

	//�X�s�[�h
	float speed = 0.4f;

	//�G�̔ԍ�
	int number = 0;

	//���ʂ܂ł̎���
	int deadTime = 130;

	//�v���C���[�̍��W
	XMFLOAT3 playerPos = { 0.0f,0.0f,0.0f };

	//�f�o�b�O
	int debugNum[1] = { 0 };
};
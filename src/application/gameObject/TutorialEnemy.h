/**
 * @file TutorialEnemy.h
 * @brief �Q�[���I�u�W�F�N�g �G
 * @author Asuma Syota
 * @date 2023/4
 */

#pragma once
#include "DirectXMath.h"
#include "FbxObject3D.h"
#include "Sprite.h"
#include "JSONLoader.h"

class TutorialEnemy
{
private:	//�G�C���A�X
	//Microsoft::WRL::���ȗ�
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public://�����o�֐�

	/// <summary>
	///�J�����Z�b�g
	/// </summary>
	static void SetCamera(Camera* camera) { TutorialEnemy::camera = camera; }

	/// <summary>
	/// �C���X�g���N�^ �f�X�g���N�^
	/// </summary>
	TutorialEnemy() {};
	~TutorialEnemy();

	/// <summary>
	///������
	/// </summary>
	void Initialize();

	/// <summary>
	///�X�V
	/// </summary>
	void UpdateTutorial();

	/// <summary>
	///�X�V
	/// </summary>
	void UpdateGame();

	/// <summary>
	///�X�V
	/// </summary>
	void UpdateMovePhase();

	/// <summary>
	///�`���[�g���A����p�̃X�e�[�g�X�V
	/// </summary>
	void UpdateStateTutorial();

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
	///�R���C�_�[
	/// </summary>
	void UpdateObjectCollider();

	/// <summary>
	///�_���[�W�n�S��
	/// </summary>
	void UpdateDamage();

	/// <summary>
	///�_���[�W�n�S��
	/// </summary>
	void UpdateDamageTutorial();

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
	///�����S��
	/// </summary>
	void MoveGame();

	/// <summary>
	///�����S��
	/// </summary>
	void MoveMovePhase();

	/// <summary>
	///�X�e�[�^�X�}�l�[�W���[
	/// </summary>
	void StatusManager();

	/// <summary>
	///���W�Z�b�g
	/// </summary>
	void SetPosition(XMFLOAT3 position) { this->position = position; };

	/// <summary>
	///�_�b�V���ɃZ�b�g
	/// </summary>
	void SetDash();

	/// <summary>
	///�_�E���ɃZ�b�g
	/// </summary>
	void SetDown();

	/// <summary>
	///���ɃZ�b�g
	/// </summary>
	void SetStand();

	/// <summary>
	///�`���[�g���A���V�[���Z�b�g
	/// </summary>
	void SetTutorial();

	/// <summary>
	///�Q�[���V�[���Z�b�g
	/// </summary>
	void SetGameScene();

	/// <summary>
	///�t�F�[�Y�ړ��Z�b�g
	/// </summary>
	void SetMovePhase();

	/// <summary>
	///�v���C���[�̍��W�Z�b�g
	/// </summary>
	void SetPlayerPos(XMFLOAT3 pos) { playerPos = pos; };

	/// <summary>
	///�w�肵�����W�ɃZ�b�g
	/// </summary>
	void AddEnemy(XMFLOAT3 pos);

	/// <summary>
	///�w�肵�����W�ɃZ�b�g
	/// </summary>
	void AddEnemyTutorialScene(XMFLOAT3 pos);

	/// <summary>
	///�w�肵�����W�ɃZ�b�g
	/// </summary>
	void AddEnemyGameScene(XMFLOAT3 pos);

	/// <summary>
	///�w�肵�����W�ɃZ�b�g
	/// </summary>
	void AddEnemyMovePhase(XMFLOAT3 pos);

	/// <summary>
	///���Z�b�g
	/// </summary>
	void Reset();

	/// <summary>
	///���@�̒e��e��
	/// </summary>
	void HitBullet1();

	/// <summary>
	///����e��
	/// </summary>
	void HitElec() { hitElec = true; };

	/// <summary>
	///���W�擾
	/// </summary>
	XMFLOAT3 GetPosition() { return position; }

	/// <summary>
	///�p�x�擾
	/// </summary>
	XMFLOAT3 GetRotation() { return rotation; }

	/// <summary>
	///�X�P�[���擾
	/// </summary>
	XMFLOAT3 GetScale() { return scale; }

	/// <summary>
	///�����擾
	/// </summary>
	XMFLOAT3 GetAddPos() { return addPos; }

	/// <summary>
	///�R���C�_�[�擾
	/// </summary>
	JSONLoader::ColliderData GetColliderData() { return colliderData; }

	/// <summary>
	/// �`���[�g���A���̃t���O���Z�b�g����
	/// </summary>
	void SetTutorialFlag(int tutorialFlag) { this->tutorialFlag = tutorialFlag; };

	/// <summary>
	///���S�t���O�擾
	/// </summary>
	bool GetIsDead() { return isDead3; }

	/// <summary>
	///�v���C���[�ƃq�b�g��
	/// </summary>
	void SetHitPlayer();

	bool GetCallFlag();

	/// <summary>
	///�`���[�g���A���V�[���|�ꂽ���̃t���O
	/// </summary>
	bool GetTutorialDownFlag() { return downFlag; };

	/// <summary>
	///�`���[�g���A���V�[���_�b�V�����Z�b�g����t���O
	/// </summary>
	void SetTutorialDashFlag() { this->tutorialDashFlag = true; };

	/// <summary>
	///�I�u�W�F�N�g�̓����蔻��Z�b�g
	/// </summary>
	void SetObjectCollider(std::vector<JSONLoader::ColliderData> colliderData) {
		this->objectColliderData = colliderData;};

	/// <summary>
	//�ǂƂ̓����蔻�菈��
	/// <summary>
	void UpdateHitWall(JSONLoader::ColliderData objectColliderData);

	/// <summary>
	//���Ƃ̓����蔻�菈��
	/// <summary>
	void UpdateHitPiller(JSONLoader::ColliderData objectColliderData);

	/// <summary>
	//���Ƃ̓����蔻�菈��
	/// <summary>
	void UpdateHitObject();

	//�`���[�g���A��12�p�̍X�V
	void UpdateTutorial12();

	//�ÓI�����o�ϐ�
private:
	//�J����
	static Camera* camera;

	//�����o�ϐ�
public:

	//�R���C�_�[�f�[�^
	JSONLoader::ColliderData colliderData;

	//�I�u�W�F�N�g�̃R���C�_�[�f�[�^
	std::vector<JSONLoader::ColliderData> objectColliderData;

	//�I�u�W�F�N�g
	FbxObject3D* object = nullptr;
	//���f��
	FbxModel* modelDash = nullptr;
	FbxModel* modelDown = nullptr;
	FbxModel* modelStand= nullptr;

	//�X�v���C�g
	std::unique_ptr<Sprite>hpBar1;	//HP�o�[�̘g
	std::unique_ptr<Sprite>hpBar2;	//HP�o�[
	std::unique_ptr<Sprite>hpBar3;	//���݂�HP�̂Ƃ��ɂ�����
	std::unique_ptr<Sprite>hpBar4;	//BOSS HP�̃e�L�X�g

	//�`���[�g���A���̃t���O
	int tutorialFlag = 0;
	//�`���[�g���A���̃_�b�V���̃t���O
	bool tutorialDashFlag = false;
	//�`���[�g���A���̓]�񂾃t���O
	bool downFlag = false;

	//�ό`�s��
	//���s�ړ�
	XMFLOAT3 position = { 0.0f,0.0f,30.0f };
	//��]
	XMFLOAT3 rotation = { 0.0f,0.0f,0.0f };
	//�T�C�Y
	XMFLOAT3 scale = { 1.0f,1.0f,1.0f };

	//�R���C�_�[�̃T�C�Y
	XMFLOAT3 colliderScale = { 20.0f,10.0f,10.0f };

	//HP
	float maxHP = 20;
	float HP = maxHP;

	//�X�v���C�g�p
	//HP�o�[1
	XMFLOAT2 hpBar1Pos = { 320.0f,-15.0f };
	XMFLOAT2 hpBar1Scale = { 640.0f,96.0f };
	//HP�o�[2
	XMFLOAT2 hpBar2Pos = { 349.0f,26.0f };
	XMFLOAT2 hpBar2OriginalScale = { 605.0f,15.0f };
	XMFLOAT2 hpBar2Scale = hpBar2OriginalScale;
	//HP�o�[3
	XMFLOAT2 hpBar3OriginalPos = { 938.0f,25.0f };
	XMFLOAT2 hpBar3Pos = hpBar3OriginalPos;
	XMFLOAT2 hpBar3Scale = { 16.0f,16.0f };
	//Hp�o�[4
	XMFLOAT2 hpBar4Pos = { 230.0f,25.0f };
	XMFLOAT2 hpBar4Scale = { 96.0f,16.0f };

	//��e
	bool hitFlag1 = false;
	bool hitElec = false;

	//���S�t���O
	bool isDead1 = true;
	bool isDead2 = true;
	bool isDead3 = true;

	//����
	XMFLOAT3 addPos = { 0.0f,15.0f,0.0f };

	//�v���C���[�̍��W
	XMFLOAT3 playerPos = { 0.0f,0.0f,0.0f };
	//�ړ��U���̃X�s�[�h
	float speed = 0.7f;

	//�_�E���̃A�j���[�V����
	int deadTime = 130;
	int deadTimer = 0;

	//�Ăяo���ɓ��邩
	float callTimer = 0.0f;
	float callTime = 500.0f;
	bool callFlag = false;

	//�I�u�W�F�N�g�ƏՓ˃t���O
	bool hitObjectFlag = false;

	//�I�u�W�F�N�g�Փˎ��̉����߂�
	float knockBackSpeed = 0.001f;

	//�]�ԏ�Ԃ̃A�j���[�V�����̃t���[��
	float frameFallDownEnemy = 125.0f - 10.0f;
	int tutorial12Timer = 0;
};
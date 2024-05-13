#pragma once
#include "DirectXMath.h"
#include "BillboardSprite.h"
#include "Sprite.h"
#include "vector"
#include "Camera.h"

class LockOn
{
private:	//�G�C���A�X
	//Microsoft::WRL::���ȗ�
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:	//�����o�֐�

	LockOn() {};
	~LockOn() {};

	/// <summary>
	///������
	/// </summary>
	void Initialize();

	/// <summary>
	///�X�V
	/// </summary>
	void Update();

	/// <summary>
	///�G�̍��W��ǉ�
	/// </summary>
	void AddEnemyPos(XMFLOAT3 position);

	/// <summary>
	///�`��
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///�Z�b�^�[
	/// </summary>
	void SetCamera(Camera* camera) { this->camera = camera; }

	/// <summary>
	///�Z�b�^�[
	/// </summary>
	void SetPlayerRotation(XMFLOAT3 rot) { this->playerRotation = rot; }

	/// <summary>
	///�Z�b�^�[
	/// </summary>
	void SetPlayerPosition(XMFLOAT3 pos) { this->playerPosition = pos; }

	/// <summary>
	///���b�N�I���Ώۂ��擾
	/// </summary>
	XMFLOAT3 GetTarget() { return target; }

	/// <summary>
	///���b�N�I���t���O���擾
	/// </summary>
	bool GetLockOnFlag() { return lockOnFlag; }

private:	//�����o�ϐ�

	//�J����
	Camera* camera = nullptr;

	//�Ə��̃r���{�[�h
	BillboardSpriteModel* lockOnSpriteModel1 = nullptr;
	BillboardSprite* lockOnSprite1 = nullptr;

	//�Ə��̉摜
	Sprite* lockOnSprite2 = nullptr;
	//�Ə��̉摜�̃X�v���C�g�̑傫���A���W
	XMFLOAT2 lockOnSpriteScale = { 96.0f,96.0f };
	XMFLOAT2 lockOnSpritePos = { 1280.0f / 2.0f - lockOnSpriteScale.x / 2.0f,120.0f };

	//�G�̍��W
	std::vector<XMFLOAT3> enemyPosition;
	//�v���C���[�̊p�x
	XMFLOAT3 playerRotation = { 0.0f,0.0f,0.0f };
	XMFLOAT3 playerPosition = { 0.0f,0.0f,0.0f };

	//���b�N�I���Ώۂ̍��W
	XMFLOAT3 target = {0.0f,0.0f,0.0f};

	//����̉�p
	float hitAngle = 1.3f;
	//����̒���
	float hitLength = 350.0f;

	//���b�N�I�����Ă��邩�̃t���O
	bool lockOnFlag = false;

	//�f�o�b�O�p
	float debugTimer[1] = { 0 };
	float debugTimer2[1] = { 0 };
	float debugTimer3[1] = { 0 };
	float debugNum[1] = { 0 };
	float debugTargetPos[3] = { 0,0,0 };
	float debugTargetFlag[1] = { 0 };
};
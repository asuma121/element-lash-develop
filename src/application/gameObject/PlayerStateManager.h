#include "Player.h"

//�_����
class Wait : public PlayerState
{
public:
	//�I�u�W�F�N�g���Ƃ̏�����
	void Initialize();
	//�X�e�[�g�̍X�V
	void UpdateState(Player* player);
	//�`��
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//���C�g�ڐ��`��
	void DrawLightView(ID3D12GraphicsCommandList* cmdList);
	//SRV�Z�b�g
	void SetSRV(ID3D12DescriptorHeap* SRV);
	//�I�u�W�F�N�g�X�V
	void UpdateObject();
};

//�����Ă���
class Run : public PlayerState
{
public:
	//�I�u�W�F�N�g���Ƃ̏�����
	void Initialize();
	//�X�e�[�g�̍X�V
	void UpdateState(Player* player);
	//�^�C�g���݂̂̏���
	void MoveTitle(float timer) override;
	//�`��
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//���C�g�ڐ��`��
	void DrawLightView(ID3D12GraphicsCommandList* cmdList);
	//SRV�Z�b�g
	void SetSRV(ID3D12DescriptorHeap* SRV);
	//�I�u�W�F�N�g�X�V
	void UpdateObject();
};

//�U��1 ��
class Attack1 : public PlayerState
{
public:
	//�I�u�W�F�N�g���Ƃ̏�����
	void Initialize();
	//�X�e�[�g�̍X�V
	void UpdateState(Player* player);
	//�I�u�W�F�N�g���Ƃ̍U��
	void UpdateAttack() override;
	//����
	void Move() override;
	//�`��
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//���C�g�ڐ��`��
	void DrawLightView(ID3D12GraphicsCommandList* cmdList);
	//SRV�Z�b�g
	void SetSRV(ID3D12DescriptorHeap* SRV);
	//�I�u�W�F�N�g�X�V
	void UpdateObject();

private:

	//�I�u�W�F�N�g���Ƃ̃^�C�}�[
	int attack1Time = 150;

	//��x�ɏo�����p�[�e�B�N���̐�
	int elecVol = 5;
	//���p�[�e�B�N�����o���t���[���̊Ԋu
	int elecInterval = 7;
	//�ł������̃X�P�[��
	float elecStartSlace1 = 5.0f;
	float elecEndSlace1 = 5.0f;
	//�ׂ������̃X�P�[��
	float elecStartSlace2 = 0.7f;
	float elecEndSlace2 = 0.1f;
	//�A���U���̓��̓t���[��
	float AttackIntervalTime = 50.0f;
	//�����o���t���[��
	int elecFlame = 40;
	//���̉��h��̋���
	float elecStrength = 4.0f;
	//���𔭐�������ꏊ
	XMFLOAT3 addElecPos1 = { 0.0f, 11.0f, 5.0f };
};

//�U��2 ��
class Attack2 : public PlayerState
{
public:
	//�I�u�W�F�N�g���Ƃ̏�����
	void Initialize();
	//�X�e�[�g�̍X�V
	void UpdateState(Player* player);
	//�I�u�W�F�N�g���Ƃ̍U��
	void UpdateAttack()override;
	//����
	void Move() override;
	//�`��
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//���C�g�ڐ��`��
	void DrawLightView(ID3D12GraphicsCommandList* cmdList);
	//SRV�Z�b�g
	void SetSRV(ID3D12DescriptorHeap* SRV);
	//�I�u�W�F�N�g�X�V
	void UpdateObject();

private:
	//�I�u�W�F�N�g���Ƃ̃^�C�}�[
	int attack2Time = 145;

	//��x�ɏo�����p�[�e�B�N���̐�
	int elecVol = 5;
	//���p�[�e�B�N�����o���t���[���̊Ԋu
	int elecInterval = 7;
	//�ł������̃X�P�[��
	float elecStartSlace1 = 5.0f;
	float elecEndSlace1 = 5.0f;
	//�ׂ������̃X�P�[��
	float elecStartSlace2 = 0.7f;
	float elecEndSlace2 = 0.1f;
	//�A���U���̓��̓t���[��
	float AttackIntervalTime = 50.0f;
	//�����o���t���[��
	int elecFlame = 40;
	//���̉��h��̋���
	float elecStrength = 4.0f;
	//���𔭐�������ꏊ
	XMFLOAT3 addElecPos1 = { 0.0f, 11.0f, 5.0f };
};

//�U��3 ��
class Attack3 : public PlayerState
{
public:
	//�I�u�W�F�N�g���Ƃ̏�����
	void Initialize();
	//�X�e�[�g�̍X�V
	void UpdateState(Player* player);
	//�I�u�W�F�N�g���Ƃ̍U��
	void UpdateAttack()override;
	//����
	void Move() override;
	//�`��
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//���C�g�ڐ��`��
	void DrawLightView(ID3D12GraphicsCommandList* cmdList);
	//SRV�Z�b�g
	void SetSRV(ID3D12DescriptorHeap* SRV);
	//�I�u�W�F�N�g�X�V
	void UpdateObject();

private:

	//�����o���Ԋu
	int bullet1Interval = 4.0f;
	//���̃X�s�[�h
	float bullet1Speed = 2.0f;
	//���̃X�P�[��
	XMFLOAT3  bullet1Scale = { 10.0f,10.0f,10.0f };
	XMFLOAT3  bullet1LastScale = { 1.0f,1.0f,1.0f };
	//���𔭐�������ʒu
	XMFLOAT3 bullet1AddPosition = { 0.0f,10.0f,0.0f };
	//���������t���[��
	float bullet1Frame = 60.0f;

	//�����̈ړ��X�s�[�h
	float attack3PosSpeed = 0.5f;
};

//�_�E��
class Down : public PlayerState
{
public:
	//�I�u�W�F�N�g���Ƃ̏�����
	void Initialize();
	//�X�e�[�g�̍X�V
	void UpdateState(Player* player);
	//����
	void Move() override;
	//�`��
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//���C�g�ڐ��`��
	void DrawLightView(ID3D12GraphicsCommandList* cmdList);
	//SRV�Z�b�g
	void SetSRV(ID3D12DescriptorHeap* SRV);
	//�I�u�W�F�N�g�X�V
	void UpdateObject();
};
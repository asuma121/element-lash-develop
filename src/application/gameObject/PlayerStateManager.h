#include "Player.h"

//�_����
class Wait : public PlayerState
{
public:
	//�I�u�W�F�N�g���Ƃ̏�����
	void InitializeState();
	//�X�e�[�g�̍X�V
	void UpdateState(Player* player);
};

//�����Ă���
class Run : public PlayerState
{
public:
	//�I�u�W�F�N�g���Ƃ̏�����
	void InitializeState();
	//�X�e�[�g�̍X�V
	void UpdateState(Player* player);
};

//�U��1 ��
class Attack1 : public PlayerState
{
public:
	//�I�u�W�F�N�g���Ƃ̏�����
	void InitializeState();
	//�X�e�[�g�̍X�V
	void UpdateState(Player* player);
	//�I�u�W�F�N�g���Ƃ̍U��
	void UpdateAttack() override;
	//����
	void Move() override;

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
	XMFLOAT3 addElecPos1 = { 0.0f, 11.0f, 8.0f };
};

//�U��2 ��
class Attack2 : public PlayerState
{
public:
	//�I�u�W�F�N�g���Ƃ̏�����
	void InitializeState();
	//�X�e�[�g�̍X�V
	void UpdateState(Player* player);
	//�I�u�W�F�N�g���Ƃ̍U��
	void UpdateAttack()override;
	//����
	void Move() override;

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
	void InitializeState();
	//�X�e�[�g�̍X�V
	void UpdateState(Player* player);
	//�I�u�W�F�N�g���Ƃ̍U��
	void UpdateAttack()override;
	//����
	void Move() override;

private:

	//�����o���Ԋu
	int bullet1Interval = 2;
	//���̃X�s�[�h
	float bullet1Speed = 1.9f;
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
	void InitializeState();
	//�X�e�[�g�̍X�V
	void UpdateState(Player* player);
	//����
	void Move() override;
};

//�����オ��
class StandUp : public PlayerState
{
public:
	//�I�u�W�F�N�g���Ƃ̏�����
	void InitializeState();
	//�X�e�[�g�̍X�V
	void UpdateState(Player* player);
	//����
	void Move() override;
};

//�_�����f�o�b�O
class DevelopWait : public PlayerState
{
public:
	//�I�u�W�F�N�g���Ƃ̏�����
	void InitializeState();
	//�X�e�[�g�̍X�V
	void UpdateState(Player* player);
};

//�����Ă��ԃf�o�b�O
class DevelopRun : public PlayerState
{
public:
	//�I�u�W�F�N�g���Ƃ̏�����
	void InitializeState();
	//�X�e�[�g�̍X�V
	void UpdateState(Player* player);
};

//�_�E���f�o�b�O
class DevelopDown : public PlayerState
{
public:
	//�I�u�W�F�N�g���Ƃ̏�����
	void InitializeState();
	//�X�e�[�g�̍X�V
	void UpdateState(Player* player);
};

//���U���f�o�b�O
class DevelopAttack3 : public PlayerState
{
public:
	//�I�u�W�F�N�g���Ƃ̏�����
	void InitializeState();
	//�X�e�[�g�̍X�V
	void UpdateState(Player* player);
};

//�����オ��f�o�b�O
class DevelopStandUp : public PlayerState
{
public:
	//�I�u�W�F�N�g���Ƃ̏�����
	void InitializeState();
	//�X�e�[�g�̍X�V
	void UpdateState(Player* player);
};
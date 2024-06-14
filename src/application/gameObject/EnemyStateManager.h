#include "Enemy.h"

//�_����
class Stand : public EnemyState
{
public:
	//�I�u�W�F�N�g���Ƃ̏�����
	void InitializeState();
	//�X�e�[�g���Ƃ̓���
	void Move();
	//�X�e�[�g�̍X�V
	void UpdateState(Enemy* enemy);
	//�`���[�g���A���̃X�e�[�g�X�V
	void UpdateStateTutorial(Enemy* enemy)override;
};

//����
class Walk : public EnemyState
{
public:
	//�I�u�W�F�N�g���Ƃ̏�����
	void InitializeState();
	//�X�e�[�g���Ƃ̓���
	void Move();
	//�X�e�[�g�̍X�V
	void UpdateState(Enemy* enemy);
};

//�U��1
class Attack01 : public EnemyState
{
public:
	//�I�u�W�F�N�g���Ƃ̏�����
	void InitializeState();
	//�X�e�[�g���Ƃ̓���
	void Move();
	//�X�e�[�g�̍X�V
	void UpdateState(Enemy* enemy);
};

//�U���O��
class AttackOmen1 : public EnemyState
{
public:
	//�I�u�W�F�N�g���Ƃ̏�����
	void InitializeState();
	//�X�e�[�g���Ƃ̓���
	void Move();
	//�N���A��p�X�V
	void UpdateParticleClear()override;
	//�X�e�[�g�̍X�V
	void UpdateState(Enemy* enemy);
	//�^�C�g���̃X�e�[�g�X�V
	void UpdateStateTitle(Enemy* enemy)override;
	//�`���[�g���A���̃X�e�[�g�X�V
	void UpdateStateTutorial(Enemy* enemy)override;
	//�Q�[���̃X�e�[�g�X�V
	void UpdateStateMovePhase(Enemy* enemy)override;
	//�Q�[���̃X�e�[�g�X�V
	void UpdateStateClear(Enemy* enemy)override;
	//�U���X�V
	void UpdateAttack()override;
};

//�_�b�V��
class Dash : public EnemyState
{
public:
	//�I�u�W�F�N�g���Ƃ̏�����
	void InitializeState();
	//�X�e�[�g���Ƃ̓���
	void Move();
	//�X�e�[�g�̍X�V
	void UpdateState(Enemy* enemy);
	//�ǂƂ̓����蔻�菈��
	void UpdateHitWall(JSONLoader::ColliderData objectColliderData) override;
	//���Ƃ̓����蔻��
	void UpdateHitPiller(JSONLoader::ColliderData objectColliderData, int pillerNum)override;

public:	//�����o�ϐ�

	//�I�u�W�F�N�g�ƏՓ˃t���O
	bool hitObjectFlag = false;
	//�I�u�W�F�N�g�Փˎ��̉����߂�
	float knockBackSpeed = 0.1f;

	//��x�v���C���[�ɏՓ˂�����I�u�W�F�N�g�ɂԂ���܂œ��������փ_�b�V��
	XMFLOAT3 dashVec = { 0.0f, 0.0f, 0.0f };
	bool dashFlag = false;
};

//�G�Ăяo��
class CallMiniEnemy : public EnemyState
{
	public:
		//�I�u�W�F�N�g���Ƃ̏�����
		void InitializeState();
		//�X�e�[�g���Ƃ̓���
		void Move();
		//�X�e�[�g�̍X�V
		void UpdateState(Enemy* enemy);
		//�Q�[���̃X�e�[�g�X�V
		void UpdateStateMovePhase(Enemy* enemy)override;
		//�U���X�V
		void UpdateAttack()override;
		//�t�F�[�Y�ړ��̏���
		void UpdateAttackMovePhase()override;
};

//�]��
class FallDown : public EnemyState
{
public:
	//�I�u�W�F�N�g���Ƃ̏�����
	void InitializeState();
	//�X�e�[�g���Ƃ̓���
	void Move();
	//�X�e�[�g�̍X�V
	void UpdateState(Enemy* enemy);
	//�Q�[���̃X�e�[�g�X�V
	void UpdateStateMovePhase(Enemy* enemy)override;
	//�R���C�_�[�f�[�^�̏���
	void UpdateColliderDate()override;
};

//�N���オ��
class GetUp : public EnemyState
{
public:
	//�I�u�W�F�N�g���Ƃ̏�����
	void InitializeState();
	//�X�e�[�g���Ƃ̓���
	void Move();
	//�X�e�[�g�̍X�V
	void UpdateState(Enemy* enemy);
	//�Q�[���̃X�e�[�g�X�V
	void UpdateStateMovePhase(Enemy* enemy)override;
};
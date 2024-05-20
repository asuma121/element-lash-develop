#include "Enemy.h"

//�_����
class Stand : public EnemyState
{
public:
	//�I�u�W�F�N�g���Ƃ̏�����
	void Initialize();
	//�X�e�[�g���Ƃ̓���
	void Move();
	//�X�e�[�g�̍X�V
	void UpdateState(Enemy* enemy);
	//�`���[�g���A���̃X�e�[�g�X�V
	void UpdateStateTutorial(Enemy* enemy)override;
	//�`��
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//���C�g�ڐ��`��
	void DrawLightView(ID3D12GraphicsCommandList* cmdList);
	//SRV�Z�b�g
	void SetSRV(ID3D12DescriptorHeap* SRV);
	//�I�u�W�F�N�g�X�V
	void UpdateObject();
};

class Walk : public EnemyState
{
public:
	//�I�u�W�F�N�g���Ƃ̏�����
	void Initialize();
	//�X�e�[�g���Ƃ̓���
	void Move();
	//�X�e�[�g�̍X�V
	void UpdateState(Enemy* enemy);
	//�`��
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//���C�g�ڐ��`��
	void DrawLightView(ID3D12GraphicsCommandList* cmdList);
	//SRV�Z�b�g
	void SetSRV(ID3D12DescriptorHeap* SRV);
	//�I�u�W�F�N�g�X�V
	void UpdateObject();
};

class Attack01 : public EnemyState
{
public:
	//�I�u�W�F�N�g���Ƃ̏�����
	void Initialize();
	//�X�e�[�g���Ƃ̓���
	void Move();
	//�X�e�[�g�̍X�V
	void UpdateState(Enemy* enemy);
	//�`��
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//���C�g�ڐ��`��
	void DrawLightView(ID3D12GraphicsCommandList* cmdList);
	//SRV�Z�b�g
	void SetSRV(ID3D12DescriptorHeap* SRV);
	//�I�u�W�F�N�g�X�V
	void UpdateObject();
};

class AttackOmen1 : public EnemyState
{
public:
	//�I�u�W�F�N�g���Ƃ̏�����
	void Initialize();
	//�X�e�[�g���Ƃ̓���
	void Move();
	//�N���A��p�X�V
	void UpdateParticleClear()override;
	//�X�e�[�g�̍X�V
	void UpdateState(Enemy* enemy);
	//�`���[�g���A���̃X�e�[�g�X�V
	void UpdateStateTutorial(Enemy* enemy)override;
	//�Q�[���̃X�e�[�g�X�V
	void UpdateStateMovePhase(Enemy* enemy)override;
	//�Q�[���̃X�e�[�g�X�V
	void UpdateStateClear(Enemy* enemy)override;
	//�U���X�V
	void UpdateAttack()override;
	//�`��
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//���C�g�ڐ��`��
	void DrawLightView(ID3D12GraphicsCommandList* cmdList);
	//SRV�Z�b�g
	void SetSRV(ID3D12DescriptorHeap* SRV);
	//�I�u�W�F�N�g�X�V
	void UpdateObject();
};

class Dash : public EnemyState
{
public:
	//�I�u�W�F�N�g���Ƃ̏�����
	void Initialize();
	//�X�e�[�g���Ƃ̓���
	void Move();
	//�X�e�[�g�̍X�V
	void UpdateState(Enemy* enemy);
	//�`��
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//���C�g�ڐ��`��
	void DrawLightView(ID3D12GraphicsCommandList* cmdList);
	//SRV�Z�b�g
	void SetSRV(ID3D12DescriptorHeap* SRV);
	//�I�u�W�F�N�g�X�V
	void UpdateObject();
	//�ǂƂ̓����蔻�菈��
	void UpdateHitWall(JSONLoader::ColliderData objectColliderData) override;
	//���Ƃ̓����蔻��
	void UpdateHitPiller(JSONLoader::ColliderData objectColliderData)override;

public:	//�����o�ϐ�

	//�I�u�W�F�N�g�ƏՓ˃t���O
	bool hitObjectFlag = false;
	//�I�u�W�F�N�g�Փˎ��̉����߂�
	float knockBackSpeed = 0.001f;

	//��x�v���C���[�ɏՓ˂�����I�u�W�F�N�g�ɂԂ���܂œ��������փ_�b�V��
	XMFLOAT3 dashVec = { 0.0f, 0.0f, 0.0f };
	bool dashFlag = false;
};

class CallMiniEnemy : public EnemyState
{
	public:
		//�I�u�W�F�N�g���Ƃ̏�����
		void Initialize();
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
		//�`��
		void Draw(ID3D12GraphicsCommandList* cmdList);
		//���C�g�ڐ��`��
		void DrawLightView(ID3D12GraphicsCommandList* cmdList);
		//SRV�Z�b�g
		void SetSRV(ID3D12DescriptorHeap* SRV);
		//�I�u�W�F�N�g�X�V
		void UpdateObject();
};

class FallDown : public EnemyState
{
public:
	//�I�u�W�F�N�g���Ƃ̏�����
	void Initialize();
	//�X�e�[�g���Ƃ̓���
	void Move();
	//�X�e�[�g�̍X�V
	void UpdateState(Enemy* enemy);
	//�Q�[���̃X�e�[�g�X�V
	void UpdateStateMovePhase(Enemy* enemy)override;
	//�`��
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//���C�g�ڐ��`��
	void DrawLightView(ID3D12GraphicsCommandList* cmdList);
	//SRV�Z�b�g
	void SetSRV(ID3D12DescriptorHeap* SRV);
	//�I�u�W�F�N�g�X�V
	void UpdateObject();
};

class GetUp : public EnemyState
{
public:
	//�I�u�W�F�N�g���Ƃ̏�����
	void Initialize();
	//�X�e�[�g���Ƃ̓���
	void Move();
	//�X�e�[�g�̍X�V
	void UpdateState(Enemy* enemy);
	//�Q�[���̃X�e�[�g�X�V
	void UpdateStateMovePhase(Enemy* enemy)override;
	//�`��
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//���C�g�ڐ��`��
	void DrawLightView(ID3D12GraphicsCommandList* cmdList);
	//SRV�Z�b�g
	void SetSRV(ID3D12DescriptorHeap* SRV);
	//�I�u�W�F�N�g�X�V
	void UpdateObject();
};
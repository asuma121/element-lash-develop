#include "Camera.h"

//�v���C���[�ɒǏ]
class FollowPlayer : public CameraState
{
public:
	//�R���C�_�[�̏���
	void UpdateCollider() override;
	//�X�e�[�g���Ƃ̓���
	void Move();
};

//�^�C�g��
class Title : public CameraState
{
public:
	//�X�e�[�g���Ƃ̓���
	void Move();
private:
	//���_���W�p
	XMFLOAT3 addTitleEye = { -10.0f,6.0f,50.0f };
	//�����_�p
	XMFLOAT3 addTitleTarget = { 30.0f,40.0f,0.0f };
};

//�`���[�g���A��
class Tutorial : public CameraState
{
public:
	//�X�e�[�g���Ƃ̓���
	void Move();
};

//�t�F�[�Y�̈ړ�
class MovePhase1 : public CameraState
{
public:
	//�X�e�[�g���Ƃ̓���
	void Move();
};

//�N���A
class Clear : public CameraState
{
public:
	//�X�e�[�g���Ƃ̓���
	void Move();
};

//�f�o�b�O
class Develop : public CameraState
{
public:
	//�R���X�g���N�^
	Develop();
	//�X�e�[�g���Ƃ̓���
	void Move();

public:
	//�����ʒu
	XMFLOAT3 startPos = { 0.0f,0.0f,-100.0f };
	XMFLOAT3 startTarget = { 0.0f,0.0f,0.0f };
	//1�t���[��������̈ړ��� ���_���W
	float addRot = (float)PI / 240.0f;
	//1�t���[��������̈ړ��� �����_���W
	float addTarget = 0.05f;
};
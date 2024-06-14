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
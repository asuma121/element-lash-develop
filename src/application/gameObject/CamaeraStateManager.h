#include "Camera.h"

//�v���C���[�ɒǏ]
class FallowPlayer : public CameraState
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
};

//�`���[�g���A��
class Tutorial : public CameraState
{
public:
	//�X�e�[�g���Ƃ̓���
	void Move();
};

//�t�F�[�Y�̈ړ�
class MovePhase : public CameraState
{
public:
	//�X�e�[�g���Ƃ̓���
	void Move();
};

//�N���A
class CLear : public CameraState
{
public:
	//�X�e�[�g���Ƃ̓���
	void Move();
};
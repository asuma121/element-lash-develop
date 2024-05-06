#pragma once
#include "Sprite.h"
#include "Input.h"
#include "DxInput.h"

class UI
{
private:	//�G�C���A�X
	//Microsoft::WRL::���ȗ�
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private:
	enum Form	//�v���C���[�̃t�H����
	{
		Fire,	//��
		Elec,	//�d�C
	};

public:
	/// <summary>
	///���̓Z�b�g
	/// </summary>
	static void SetInput(Input* input) { UI::input = input; }

	/// <summary>
	///�R���g���[���[���̓Z�b�g
	/// </summary>
	static void SetDXInput(DXInput* dxInput) { UI::dxInput = dxInput; }

	/// <summary>
	///������
	/// </summary>
	void Initialize();

	/// <summary>
	///�X�V �Q�[���V�[��
	/// </summary>
	void UpdateGame();

	/// <summary>
	///�X�V �`���[�g���A���V�[��
	/// </summary>
	void UpdateTutorial();

	/// <summary>
	///�X�V �^�C�g���V�[��
	/// </summary>
	void UpdateTitle();

	/// <summary>
	///�`�� �Q�[���V�[��
	/// </summary>
	void DrawGame(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///�`�� �`���[�g���A���V�[��
	/// </summary>
	void DrawTutorial(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///�`�� �^�C�g���V�[��
	/// </summary>
	void DrawTitle(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///�Q�[���V�[���p��UI�Z�b�g
	/// </summary>
	void SetGame();

	/// <summary>
	///�^�C�g���V�[���̃V�[���J�ڗp�^�C�}�[�Z�b�g
	/// </summary>
	void SetTitleTimer(int moveTutorialTimer, int moveTutorialTime);

	/// <summary>
	///�`���[�g���A���V�[���̃t���O�Z�b�g
	/// </summary>
	void SetTutorialFlag(int tutorialFlag) { this->tutorialFlag = tutorialFlag; }

	/// <summary>
	///�`���[�g���A���V�[���̃^�C�}�[�Z�b�g
	/// </summary>
	void SetTutorialTimer(int LStickTimer, int LStickTime, int RStickTimer, int RStickTime,
			int attackTimer, int attackTime, int attackTimer2, int attackTime2, 
		int iikannjiTimer,int iikannjiTime, int tutorial12Timer, int tutorial12Time);

	/// <summary>
	///�v���C���[�̏�ԃZ�b�g
	/// </summary>
	void SetPlayerForm(int form, bool formChangeFlag);

	//�ÓI�����o�ϐ�
private:
	//�L�[�{�[�h
	static Input* input;
	//�R���g���[���[
	static DXInput* dxInput;

	//�����o�ϐ�
private:

	//�L�[�{�[�h �{�^����UI
	//���ʂ̍��W�A�X�P�[��
	XMFLOAT2 keySpriteScale1 = { 32.0f,32.0f };	//ADSW,AROW�L�[�̃X�P�[��
	XMFLOAT2 keySpriteScale2 = { 128.0f * 0.8f,64.0f * 0.8f };	//�`���[�g���A���V�[�� ����̃X�[�y�X,�V�t�g�L�[�̃X�P�[��
	XMFLOAT2 keySpriteScale3 = { 128.0f * 0.6f,64.0f * 0.6f };	//�`���[�g���A���V�[�� �������̃X�[�y�X,�V�t�g�L�[�̃X�P�[��
	XMFLOAT2 BButtonSpriteScale = { 64.0f,64.0f };	//�`���[�g���A���V�[�� RB LB�{�^���̃X�P�[��
	XMFLOAT2 stickSpriteScale = { 64.0f,64.0f };	//�`���[�g���A���V�[�� R�X�e�B�b�N L�X�e�B�b�N�̃X�P�[��
	//�X�y�[�X�L�[
	std::unique_ptr<Sprite>spaceKeySprite1;	//�X�y�[�X�L�[
	std::unique_ptr<Sprite>spaceKeyPushSprite1;	//�X�y�[�X�L�[ �����Ă�����
	std::unique_ptr<Sprite>spaceKeySprite2;	//�`���[�g���A���V�[�� �������̒��̃X�v���C�g
	XMFLOAT2 spaceKeySpritePos1 = { 700.0f,500.0f };	//�^�C�g���V�[���̍��W
	XMFLOAT2 spaceKeySpriteScale1 = { 128.0f,64.0f };	//�^�C�g���V�[���̃X�P�[��
	XMFLOAT2 SpaceKeySpritePos2 = { 58.0f,114.0f };	//�`���[�g���A���V�[�� ����̍��W
	XMFLOAT2 SpaceKeySpritePos3 = { 328.0f,580.0f };	//�`���[�g���A���V�[�� �������̍��W
	XMFLOAT2 SpaceKeySpritePos4 = { 1096.0f,132.0f };	//�`���[�g���A���V�[�� �������̍��W
	//�V�t�g�L�[
	std::unique_ptr<Sprite>shiftKeySprite1;	//�V�t�g�L�[
	std::unique_ptr<Sprite>shiftKeyPushSprite1;	//�V�t�g�L�[�����Ă�����
	std::unique_ptr<Sprite>shiftKeySprite2;	//�`���[�g���A���V�[�� �������̒��̃X�v���C�g
	XMFLOAT2 shiftKeySpritePos1 = { 58.0f,114.0f };	//�`���[�g���A���V�[�� ����̍��W
	XMFLOAT2 shiftKeySpritePos2 = { 320.0f,590.0f };	//�`���[�g���A���V�[�� �������̍��W
	XMFLOAT2 shiftKeySpritePos3 = { 1096.0f,58.0f };	//�Q�[���V�[�� �����`�F���W�̍��W
	//A�L�[
	std::unique_ptr<Sprite>AKeySprite;	//A�L�[
	std::unique_ptr<Sprite>AKeyPushSprite;	//A�L�[ �����Ă�����
	std::unique_ptr<Sprite>AKeySprite2;
	XMFLOAT2 AKeySpritePos = { 50.0f,132.0f };	//�`���[�g���A�V�[���̍��W ����̍��W
	XMFLOAT2 AKeySpritePos2 = { 326.0f,588.0f };	//�`���[�g���A���V�[�� �������̍��W
	//W�L�[
	std::unique_ptr<Sprite>WKeySprite;	//W�L�[
	std::unique_ptr<Sprite>WKeyPushSprite;	//W�L�[ �����Ă�����
	std::unique_ptr<Sprite>WKeySprite2;	//�`���[�g���A���V�[�� �������̒��̃X�v���C�g
	XMFLOAT2 WKeySpritePos = { 82.0f,100.0f };	//�`���[�g���A�V�[���̍��W ����̍��W
	XMFLOAT2 WKeySpritePos2 = { 358.0f,556.0f };	//�`���[�g���A���V�[�� �������̍��W
	//S�L�[
	std::unique_ptr<Sprite>SKeySprite;	//S�L�[
	std::unique_ptr<Sprite>SKeyPushSprite;	//S�L�[ �����Ă�����
	std::unique_ptr<Sprite>SKeySprite2;	//�`���[�g���A���V�[�� �������̒��̃X�v���C�g
	XMFLOAT2 SKeySpritePos = { 82.0f,132.0f };	//�`���[�g���A�V�[���̍��W ����̍��W
	XMFLOAT2 SKeySpritePos2 = { 358.0f,588.0f };	//�`���[�g���A���V�[�� �������̍��W
	//D�L�[
	std::unique_ptr<Sprite>DKeySprite;	//D�L�[
	std::unique_ptr<Sprite>DKeyPushSprite;	//D�L�[ �����Ă�����
	std::unique_ptr<Sprite>DKeySprite2;	//�`���[�g���A���V�[�� �������̒��̃X�v���C�g
	XMFLOAT2 DKeySpritePos = { 114.0f,132.0f };	//�`���[�g���A�V�[���̍��W ����̍��W
	XMFLOAT2 DKeySpritePos2 = { 390.0f,588.0f };	//�`���[�g���A���V�[�� �������̍��W
	//Left�L�[
	std::unique_ptr<Sprite>LeftKeySprite;	//Left�L�[
	std::unique_ptr<Sprite>LeftKeyPushSprite;	//Left�L�[ �����Ă�����
	std::unique_ptr<Sprite>LeftKeySprite2;	//�`���[�g���A���V�[�� �������̒��̃X�v���C�g
	XMFLOAT2 LeftKeySpritePos = { 50.0f,206.0f };	//�`���[�g���A�V�[���̍��W ����̍��W
	XMFLOAT2 LeftKeySpritePos2 = { 188.0f,646.0f };	//�`���[�g���A���V�[�� �������̍��W
	//Rigth�L�[
	std::unique_ptr<Sprite>RightKeySprite;	//Right�L�[
	std::unique_ptr<Sprite>RightKeyPushSprite;	//Right�L�[ �����Ă�����
	std::unique_ptr<Sprite>RightKeySprite2;	//�`���[�g���A���V�[�� �������̒��̃X�v���C�g
	XMFLOAT2 RightKeySpritePos = { 114.0f,206.0f };	//�`���[�g���A�V�[���̍��W ����̍��W
	XMFLOAT2 RightKeySpritePos2 = { 252.0f,646.0f };	//�`���[�g���A���V�[�� �������̍��W
	////Up�L�[
	std::unique_ptr<Sprite>UpKeySprite;	//Up�L�[
	std::unique_ptr<Sprite>UpKeyPushSprite;	//Up�[ �����Ă�����
	std::unique_ptr<Sprite>UpKeySprite2;	//�`���[�g���A���V�[�� �������̒��̃X�v���C�g
	XMFLOAT2 UpKeySpritePos = { 82.0f,174.0f };	//�`���[�g���A�V�[���̍��W ����̍��W
	XMFLOAT2 UpKeySpritePos2 = { 220.0f,614.0f };	//�`���[�g���A���V�[�� �������̍��W
	//Down�L�[
	std::unique_ptr<Sprite>DownKeySprite;	//Down�L�[
	std::unique_ptr<Sprite>DownKeyPushSprite;	//Down�L�[ �����Ă�����
	std::unique_ptr<Sprite>DownKeySprite2;	//�`���[�g���A���V�[�� �������̒��̃X�v���C�g
	XMFLOAT2 DownKeySpritePos = { 82.0f,206.0f };	//�`���[�g���A�V�[���̍��W ����̍��W
	XMFLOAT2 DownKeySpritePos2 = { 220.0f,646.0f };	//�`���[�g���A���V�[�� �������̍��W
	//ESC�L�[ ���F������
	std::unique_ptr<Sprite>escKeySprite;	//ESC�L�[
	XMFLOAT2 escKeySpritePos = { 0.0f,0.0f };	//�`���[�g���A�V�[���̍��W �`���[�g���A���X�L�b�v
	XMFLOAT2 escKeySpriteScale = { 109.0f * 0.7f,49.0f * 0.7f };	//�`���[�g���A�V�[���̍��W �`���[�g���A���X�L�b�v
	//A�{�^��
	std::unique_ptr<Sprite>AButtonSprite;	//�R���g���[���[A�{�^��
	std::unique_ptr<Sprite>AButtonPushSprite;	//�����Ă���R���g���[���[A�{�^��
	XMFLOAT2 AButtonPos = { 700.0f,500.0f };	//�^�C�g���V�[���̍��W
	XMFLOAT2 AButtonScale = { 64.0f,64.0f };	//�^�C�g���V�[���̃X�P�[��
	//LB�{�^��
	std::unique_ptr<Sprite>LBButtonSprite1;	//�R���g���[���[LB�{�^��
	std::unique_ptr<Sprite>LBButtonPushSprite1;	//�����Ă���R���g���[���[LB�{�^��
	std::unique_ptr<Sprite>LBButtonSprite2;	//�`���[�g���A���V�[�� �������̒��̃X�v���C�g
	XMFLOAT2 LBButtonSpritePos = { 50.0f,100.0f };	//�`���[�g���A�V�[���̍��W ����̍��W
	XMFLOAT2 LBButtonSpritePos2 = { 328.0f,576.0f };	//�`���[�g���A���V�[�� �������̍��W
	XMFLOAT2 LBButtonSpritePos3 = { 1126.0f,50.0f };	//�Q�[���V�[�� �����`�F���W�̍��W
	//RB�{�^��
	std::unique_ptr<Sprite>RBButtonSprite1;	//�R���g���[���[RB�{�^��
	std::unique_ptr<Sprite>RBButtonPushSprite1;	//�����Ă���R���g���[���[RB�{�^��
	std::unique_ptr<Sprite>RBButtonSprite2;	//�`���[�g���A���V�[�� �������̒��̃X�v���C�g
	XMFLOAT2 RBButtonSpritePos = { 50.0f,100.0f };	//�`���[�g���A�V�[���̍��W ����̍��W
	XMFLOAT2 RBButtonSpritePos2 = { 350.0f,570.0f };	//�`���[�g���A���V�[�� �������̍��W
	XMFLOAT2 RBButtonSpritePos3 = { 1126.0f,124.0f };	//�Q�[���V�[�� �����`�F���W�̍��W
	//START�{�^�� ���F������
	std::unique_ptr<Sprite>startButtonSprite;	//�R���g���[���[START�{�^��
	XMFLOAT2 startButtonSpritePos = { 0.0f,0.0f };	//�`���[�g���A�V�[���̍��W �`���[�g���A���X�L�b�v
	XMFLOAT2 startButtonSpriteScale = { 194.0f * 0.7f,49.0f * 0.7f };	//�`���[�g���A�V�[���̍��W �`���[�g���A���X�L�b�v
	//L�X�e�B�b�N�̃X�v���C�g
	std::unique_ptr<Sprite>LStickSprite;	//�R���g���[���[L�X�e�B�b�N
	std::unique_ptr<Sprite>LStickSprite2;	//�R���g���[���[L�X�e�B�b�N ������
	XMFLOAT2 LStickSpritePos = { 58.0f,100.0f };	//�`���[�g���A�V�[���̍��W ����̍��W
	XMFLOAT2 LStickSpritePos2 = { 342.0f,556.0f };	//�`���[�g���A���V�[�� �������̍��W
	//R�X�e�B�b�N�̃X�v���C�g
	std::unique_ptr<Sprite>RStickSprite;	//�R���g���[���[R�X�e�B�b�N
	std::unique_ptr<Sprite>RStickSprite2;	//�R���g���[���[R�X�e�B�b�N ������
	XMFLOAT2 RStickSpritePos = { 58.0f,174.0f };	//�`���[�g���A�V�[���̍��W ����̍��W
	XMFLOAT2 RStickSpritePos2 = { 194.0f,614.0f };	//�`���[�g���A���V�[�� �������̍��W

	//�^�C�g���V�[��
	//�^�C�g���̃X�v���C�g
	std::unique_ptr<Sprite>title1Sprite;	
	XMFLOAT2 title1Pos = { 0.0f,-150.0f };
	XMFLOAT2 title1Scale = { 1280.0f, 480.0f };
	//�^�C�g���V�[�� PUSH
	std::unique_ptr<Sprite>title2Sprite;
	XMFLOAT2 title2Pos = { 500.0f, 500.0f };
	XMFLOAT2 title2Scale = { 190.0f, 52.0f };
	//�^�C�g���V�[�� �R���g���[���[����
	std::unique_ptr<Sprite>title3Sprite;
	XMFLOAT2 title3Pos = { 928.0f, 656.0f };
	XMFLOAT2 title3Scale = { 347.0f, 56.0f };
	//�^�C�g���V�[�� �{�^���̃A�j���[�V�����p�^�C�}�[
	int buttonTimer = 0;
	int buttonChangeTime = 90;
	int buttonMaxTime = buttonChangeTime * 2;
	//�^�C�g���V�[�� �R���g���[���[�����X�v���C�g�_�ŗp��
	int titleSprite3Timer = 1;
	int titleSprite3Add = 1;
	int titleSprite3MaxTime = titleSprite3Add * 45;
	//�^�C�g���V�[�� �V�[���J�ڗp�^�C�}�[
	int titleTimer;
	//�^�C�g���V�[�� �V�[���J�ڂ̎���
	int titleTime;

	//�`���[�g���A���V�[��
	//�`���[�g���A���V�[�� �������o���g
	std::unique_ptr<Sprite>tutorial1Sprite;
	XMFLOAT2 tutorial1Pos = { 128.0f, 520.0f };
	XMFLOAT2 tutorial1Scale = { 512.0f * 2, 130.0f * 1.5 };
	//�`���[�g���A���V�[�� �܂��́u�v�ňړ��A�u�v�ŃJ�����ړ����Ă݂悤
	std::unique_ptr<Sprite>tutorial2Sprite;
	XMFLOAT2 tutorial2Pos = { 198.0f, 570.0f };
	XMFLOAT2 tutorial2Scale = { 1246.0f * 0.5, 197.0f * 0.5 };
	//�`���[�g���A���V�[�� ���������I
	std::unique_ptr<Sprite>tutorial3Sprite;	
	XMFLOAT2 tutorial3Pos = { 198.0f, 570.0f };
	XMFLOAT2 tutorial3Scale = { 104.0f * 2.0f, 42.0f * 2.0f };
	//�`���[�g���A���V�[�� ���́u�v�ōU�����Ă݂悤
	std::unique_ptr<Sprite>tutorial4Sprite;	
	XMFLOAT2 tutorial4Pos = { 198.0f, 570.0f };
	XMFLOAT2 tutorial4Scale = { 523.0f * 1.5f, 41.0f * 1.5f };
	//�`���[�g���A���V�[�� ���́u�v�������Ă݂悤
	std::unique_ptr<Sprite>tutorial6Sprite;
	XMFLOAT2 tutorial6Pos = { 198.0f, 570.0f };
	XMFLOAT2 tutorial6Scale = { 791.0f * 0.8f, 101.0f * 0.8f };
	//�`���[�g���A���V�[�� ����(�G�������g)���d�C�ɕϊ��ł���
	std::unique_ptr<Sprite>tutorial7Sprite;
	XMFLOAT2 tutorial7Pos = { 198.0f, 570.0f };
	XMFLOAT2 tutorial7Scale = { 562.0f, 45.0f };
	//�`���[�g���A���V�[�� �����ɂ������̑����ł��U�����Ă݂悤�I
	std::unique_ptr<Sprite>tutorial8Sprite;
	XMFLOAT2 tutorial8Pos = { 198.0f, 570.0f };
	XMFLOAT2 tutorial8Scale = { 791.0f, 101.0f };
	//�`���[�g���A���V�[�� �X�e�[�W�̐^�񒆂ɓˑR�G�����ꂽ�I�|���Ă݂悤
	std::unique_ptr<Sprite>tutorial10Sprite;
	XMFLOAT2 tutorial10Pos = { 198.0f, 570.0f };
	XMFLOAT2 tutorial10Scale = { 791.0f, 101.0f };
	//�`���[�g���A���V�[�� �|�����I��������
	std::unique_ptr<Sprite>tutorial11Sprite;
	XMFLOAT2 tutorial11Pos = { 198.0f, 570.0f };
	XMFLOAT2 tutorial11Scale = { 791.0f, 101.0f };
	//�`���[�g���A���V�[�� �`���[�g���A���X�L�b�v
	std::unique_ptr<Sprite>tutorial12Sprite;
	XMFLOAT2 tutorial12Pos1 = { 140.0f, 0.0f };	//�R���g���[���[�ڑ����̍��W
	XMFLOAT2 tutorial12Pos2 = { 80.0f, 0.0f };	//�R���g���[���[���ڑ����̍��W
	XMFLOAT2 tutorial12Scale = { 958.0f * 0.4f, 78.0f * 0.4f };
	//�`���[�g���A���V�[�� �`�F�b�N�}�[�N1
	std::unique_ptr<Sprite>checkSprite1;
	XMFLOAT2 checkSprite1Pos = { 24.0f,116.0f };
	XMFLOAT2 checkSpriteScale = { 32.0f,32.0f };
	//�`���[�g���A���V�[�� �`�F�b�N�}�[�N2
	std::unique_ptr<Sprite>checkSprite2;
	XMFLOAT2 checkSprite2Pos = { 24.0f,190.0f };
	//�`���[�g���A���V�[�� �`�F�b�N�}�[�N�̘g1
	std::unique_ptr<Sprite>checkFrameSprite1;
	XMFLOAT2 checkFrameSprite1Pos = { 24.0f,116.0f };
	XMFLOAT2 checkFrameSpriteScale = { 32.0f,32.0f };
	//�`���[�g���A���V�[�� �`�F�b�N�}�[�N�̘g2
	std::unique_ptr<Sprite>checkFrameSprite2;
	XMFLOAT2 checkFrameSprite2Pos = { 24.0f,190.0f };
	//�`���[�g���A���V�[�� �Q�[�W�̘g1
	std::unique_ptr<Sprite>tutorialFrameSprite1;
	XMFLOAT2 tutorialFrameSprite1Pos = { 140.0f,124.0f };
	XMFLOAT2 tutorialFrameSpriteScale = { 128.0f,16.0f };
	//�`���[�g���A���V�[�� �Q�[�W�̘g2
	std::unique_ptr<Sprite>tutorialFrameSprite2;
	XMFLOAT2 tutorialFrameSprite2Pos = { 140.0f,198.0f };
	//�`���[�g���A���V�[�� �Q�[�W1
	std::unique_ptr<Sprite>gaugeSprite1;
	XMFLOAT2 gaugeSprite1Pos = { 140.0f,124.0f };
	XMFLOAT2 gaugeSpriteScale = { 128.0f,16.0f };
	//�`���[�g���A���V�[�� �Q�[�W2
	std::unique_ptr<Sprite>gaugeSprite2;
	XMFLOAT2 gaugeSprite2Pos = { 140.0f,198.0f };
	//�`���[�g���A���V�[���̃t���O
	int tutorialFlag = 0;
	//�`���[�g���A���V�[�� L�X�e�B�b�N�̃^�C�}�[
	int LStickTimer = 0;
	int LStickTime = 0;
	//�`���[�g���A���V�[�� R�X�e�B�b�N�̃^�C�}�[
	int RStickTimer = 0;
	int RStickTime = 0;
	//�`���[�g���A���V�[�� �U���`���[�g���A���̃^�C�}�[
	int attackTimer = 0;
	int attackTime = 0;
	//�`���[�g���A���V�[�� �U���`���[�g���A���̃^�C�}�[
	int attackTimer2 = 0;
	int attackTime2 = 0;
	//�`���[�g���A���V�[�� �U���`���[�g���A���̃^�C�}�[
	int iikannjiTimer = 0;
	int iikannjiTime = 0;
	//�`���[�g���A���V�[�� �G���o�ꂷ��܂ł̃^�C�}�[
	int tutorial12Timer = 0;
	int tutorial12Time = 0;

	//�Q�[���V�[��
	//�Q�[���V�[�� �����ω�UI���ʂ̍��W �X�P�[��
	XMFLOAT2 changeElementSpritePos = { 1200.0f,50.0f };
	XMFLOAT2 changeElementspriteScale = { 64.0f,64.0f };
	//�Q�[���V�[�� �����ω���UI �d�C
	std::unique_ptr<Sprite>changeElementSprite1;
	//�Q�[���V�[�� �����ω���UI ��
	std::unique_ptr<Sprite>changeElementSprite2;
	//�Q�[���V�[�� �����ω���UI ���T�C�N���}�[�N�݂����Ȃ��
	std::unique_ptr<Sprite>changeElementSprite3;
	//�Q�[���V�[�� �����ω���UI �~�}�[�N
	std::unique_ptr<Sprite>changeElementSprite4;
	//�Q�[���V�[���@�U��UI���ʂ̍��W �X�P�[�� 
	XMFLOAT2 attackSpritePos = { 1200.0f,124.0f };
	XMFLOAT2 attackSpriteScale = { 64.0f,64.0f };
	//�Q�[���V�[�� �U��UI �d�C
	std::unique_ptr<Sprite>attackElecSprite;
	//�Q�[���V�[�� �U��UI ��
	std::unique_ptr<Sprite>attackFireSprite;

	//�v���C���[�̌��݂̑���
	Form playerForm;
	//�v���C���[�������`�F���W�ł��邩
	bool formChangeFlag;

	//�f�o�b�O
	float debugNum1[2] = { 0.0f,0.0f };
	float debugNum2[1] = { 1.0f};
	float debugNum3[2] = { 0.0f,0.0f };
	float debugNum4[1] = { 1.0f};
	float debugNum5[2] = { 0.0f,0.0f };
	float debugNum6[1] = { 1.0f};
};
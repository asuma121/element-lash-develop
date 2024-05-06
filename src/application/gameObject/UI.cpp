#include "UI.h"
#include "mathOriginal.h"
#include "imgui.h"

Input* UI::input = nullptr;
DXInput* UI::dxInput = nullptr;

void UI::Initialize()
{
	//�^�C�g���̃X�v���C�g
	Sprite* newTitle1Sprite = new Sprite();
	newTitle1Sprite->Initialize();
	title1Sprite.reset(newTitle1Sprite);
	title1Sprite->SetTextureNum(18);
	title1Sprite->Update(title1Pos,title1Scale);
	//�^�C�g���̃X�v���C�g2
	Sprite* newTitle2Sprite = new Sprite();
	newTitle2Sprite->Initialize();
	title2Sprite.reset(newTitle2Sprite);
	title2Sprite->SetTextureNum(19);
	title2Sprite->Update(title2Pos, title2Scale);
	//�^�C�g���̃X�v���C�g3
	Sprite* newTitle3Sprite = new Sprite();
	newTitle3Sprite->Initialize();
	title3Sprite.reset(newTitle3Sprite);
	title3Sprite->SetTextureNum(63);
	title3Sprite->Update(title3Pos, title3Scale);
	//�X�y�[�X�L�[��
	Sprite* newSpaceKeySprite = new Sprite();
	newSpaceKeySprite->Initialize();
	spaceKeySprite1.reset(newSpaceKeySprite);
	spaceKeySprite1->SetTextureNum(59);
	spaceKeySprite1->Update(spaceKeySpritePos1, spaceKeySpriteScale1);
	//�����Ă���X�y�[�X�L�[�̃X�v���C�g
	Sprite* newSpaceKeyPushSprite = new Sprite();
	newSpaceKeyPushSprite->Initialize();
	spaceKeyPushSprite1.reset(newSpaceKeyPushSprite);
	spaceKeyPushSprite1->SetTextureNum(60);
	spaceKeyPushSprite1->Update(spaceKeySpritePos1, spaceKeySpriteScale1);
	//A�{�^���̃X�v���C�g
	Sprite* newAButtonSprite = new Sprite();
	newAButtonSprite->Initialize();
	AButtonSprite.reset(newAButtonSprite);
	AButtonSprite->SetTextureNum(61);
	AButtonSprite->Update(AButtonPos, AButtonScale);
	//�����Ă���A�{�^���̃X�v���C�g
	Sprite* newAButtonPushSprite = new Sprite();
	newAButtonPushSprite->Initialize();
	AButtonPushSprite.reset(newAButtonPushSprite);
	AButtonPushSprite->SetTextureNum(62);
	AButtonPushSprite->Update(AButtonPos, AButtonScale);

	//�`���[�g���A���̃X�v���C�g1
	Sprite* newTutorial1Sprite = new Sprite();
	newTutorial1Sprite->Initialize();
	tutorial1Sprite.reset(newTutorial1Sprite);
	tutorial1Sprite->SetTextureNum(32);
	tutorial1Sprite->Update(tutorial1Pos, tutorial1Scale);
	//�`���[�g���A���̃X�v���C�g2
	Sprite* newTutorial2Sprite = new Sprite();
	newTutorial2Sprite->Initialize();
	tutorial2Sprite.reset(newTutorial2Sprite);
	tutorial2Sprite->SetTextureNum(33);
	tutorial2Sprite->Update(tutorial2Pos, tutorial2Scale);
	//�`���[�g���A���̃X�v���C�g3
	Sprite* newTutorial3Sprite = new Sprite();
	newTutorial3Sprite->Initialize();
	tutorial3Sprite.reset(newTutorial3Sprite);
	tutorial3Sprite->SetTextureNum(34);
	tutorial3Sprite->Update(tutorial3Pos, tutorial3Scale);
	//�`���[�g���A���̃X�v���C�g4
	Sprite* newTutorial4Sprite = new Sprite();
	newTutorial4Sprite->Initialize();
	tutorial4Sprite.reset(newTutorial4Sprite);
	tutorial4Sprite->SetTextureNum(35);
	tutorial4Sprite->Update(tutorial4Pos, tutorial4Scale);
	//�`���[�g���A���̃X�v���C�g6
	Sprite* newTutorial6Sprite = new Sprite();
	newTutorial6Sprite->Initialize();
	tutorial6Sprite.reset(newTutorial6Sprite);
	tutorial6Sprite->SetTextureNum(36);
	tutorial6Sprite->Update(tutorial6Pos, tutorial6Scale);
	//�`���[�g���A���̃X�v���C�g7
	Sprite* newTutorial7Sprite = new Sprite();
	newTutorial7Sprite->Initialize();
	tutorial7Sprite.reset(newTutorial7Sprite);
	tutorial7Sprite->SetTextureNum(37);
	tutorial7Sprite->Update(tutorial6Pos,tutorial6Scale);
	//�`���[�g���A���̃X�v���C�g8
	Sprite* newTutorial8Sprite = new Sprite();
	newTutorial8Sprite->Initialize();
	tutorial8Sprite.reset(newTutorial8Sprite);
	tutorial8Sprite->SetTextureNum(38);
	tutorial8Sprite->Update(tutorial8Pos, tutorial8Scale);
	//�`���[�g���A���̃X�v���C�g10
	Sprite* newTutorial10Sprite = new Sprite();
	newTutorial10Sprite->Initialize();
	tutorial10Sprite.reset(newTutorial10Sprite);
	tutorial10Sprite->SetTextureNum(39);
	tutorial10Sprite->Update(tutorial10Pos, tutorial10Scale);
	//�`���[�g���A���̃X�v���C�g11
	Sprite* newTutorial11Sprite = new Sprite();
	newTutorial11Sprite->Initialize();
	tutorial11Sprite.reset(newTutorial11Sprite);
	tutorial11Sprite->SetTextureNum(40);
	tutorial11Sprite->Update(tutorial11Pos, tutorial11Scale);
	//�`���[�g���A���̃X�v���C�g12
	Sprite* newTutorial12Sprite = new Sprite();
	newTutorial12Sprite->Initialize();
	tutorial12Sprite.reset(newTutorial12Sprite);
	tutorial12Sprite->SetTextureNum(51);
	if(dxInput->GetConnectFlag() == true)
		tutorial12Sprite->Update(tutorial12Pos1, tutorial12Scale);
	if (dxInput->GetConnectFlag() == false)
		tutorial12Sprite->Update(tutorial12Pos2, tutorial12Scale);
	//L�X�e�B�b�N�̃X�v���C�g
	Sprite* newLStickSprite = new Sprite();
	newLStickSprite->Initialize();
	LStickSprite.reset(newLStickSprite);
	LStickSprite->SetTextureNum(42);
	LStickSprite->Update(LStickSpritePos, stickSpriteScale);
	//R�X�e�B�b�N�̃X�v���C�g
	Sprite* newRStickSprite = new Sprite();
	newRStickSprite->Initialize();
	RStickSprite.reset(newRStickSprite);
	RStickSprite->SetTextureNum(43);
	RStickSprite->Update(RStickSpritePos, stickSpriteScale);
	//LB�{�^���̃X�v���C�g
	Sprite* newLBButtonSprite = new Sprite();
	newLBButtonSprite->Initialize();
	LBButtonSprite1.reset(newLBButtonSprite);
	LBButtonSprite1->SetTextureNum(47);
	LBButtonSprite1->Update(LBButtonSpritePos, BButtonSpriteScale);
	//LB�{�^���̃X�v���C�g �����Ă��鎞
	Sprite* newLBButtonPushSprite = new Sprite();
	newLBButtonPushSprite->Initialize();
	LBButtonPushSprite1.reset(newLBButtonPushSprite);
	LBButtonPushSprite1->SetTextureNum(49);
	LBButtonPushSprite1->Update(LBButtonSpritePos, BButtonSpriteScale);
	//RB�{�^���̃X�v���C�g
	Sprite* newRBButtonSprite = new Sprite();
	newRBButtonSprite->Initialize();
	RBButtonSprite1.reset(newRBButtonSprite);
	RBButtonSprite1->SetTextureNum(48);
	RBButtonSprite1->Update(RBButtonSpritePos, BButtonSpriteScale);
	//RB�{�^���̃X�v���C�g �����Ă��鎞
	Sprite* newRBButtonPushSprite = new Sprite();
	newRBButtonPushSprite->Initialize();
	RBButtonPushSprite1.reset(newRBButtonPushSprite);
	RBButtonPushSprite1->SetTextureNum(50);
	RBButtonPushSprite1->Update(RBButtonSpritePos, BButtonSpriteScale);
	//�`�F�b�N�}�[�N�̃X�v���C�g
	Sprite* newCheckSprite1 = new Sprite();
	newCheckSprite1->Initialize();
	checkSprite1.reset(newCheckSprite1);
	checkSprite1->SetTextureNum(44);
	checkSprite1->Update(checkSprite1Pos, checkSpriteScale);
	//�`�F�b�N�}�[�N�̃X�v���C�g
	Sprite* newCheckSprite2 = new Sprite();
	newCheckSprite2->Initialize();
	checkSprite2.reset(newCheckSprite2);
	checkSprite2->SetTextureNum(44);
	checkSprite2->Update(checkSprite2Pos, checkSpriteScale);
	//�`�F�b�N�}�[�N�̘g�̃X�v���C�g
	Sprite* newCheckFrameSprite = new Sprite();
	newCheckFrameSprite->Initialize();
	checkFrameSprite1.reset(newCheckFrameSprite);
	checkFrameSprite1->SetTextureNum(45);
	checkFrameSprite1->Update(checkFrameSprite1Pos, checkFrameSpriteScale);
	//�`�F�b�N�}�[�N�̘g�̃X�v���C�g
	Sprite* newCheckFrameSprite2 = new Sprite();
	newCheckFrameSprite2->Initialize();
	checkFrameSprite2.reset(newCheckFrameSprite2);
	checkFrameSprite2->SetTextureNum(45);
	checkFrameSprite2->Update(checkFrameSprite2Pos, checkFrameSpriteScale);
	//�g�̃X�v���C�g
	Sprite* newTutorialFrameSprite1 = new Sprite();
	newTutorialFrameSprite1->Initialize();
	tutorialFrameSprite1.reset(newTutorialFrameSprite1);
	tutorialFrameSprite1->SetTextureNum(46);
	tutorialFrameSprite1->Update(tutorialFrameSprite1Pos, tutorialFrameSpriteScale);
	//�g�̃X�v���C�g
	Sprite* newTutorialFrameSprite2 = new Sprite();
	newTutorialFrameSprite2->Initialize();
	tutorialFrameSprite2.reset(newTutorialFrameSprite2);
	tutorialFrameSprite2->SetTextureNum(46);
	tutorialFrameSprite2->Update(tutorialFrameSprite2Pos, tutorialFrameSpriteScale);
	//�Q�[�W�̃X�v���C�g
	Sprite* newGaugeSprite1 = new Sprite();
	newGaugeSprite1->Initialize();
	gaugeSprite1.reset(newGaugeSprite1);
	gaugeSprite1->SetTextureNum(24);
	gaugeSprite1->Update(gaugeSprite1Pos, { 0.0f,0.0f });
	//�Q�[�W�̃X�v���C�g
	Sprite* newGaugeSprite2 = new Sprite();
	newGaugeSprite2->Initialize();
	gaugeSprite2.reset(newGaugeSprite2);
	gaugeSprite2->SetTextureNum(24);
	gaugeSprite2->Update(gaugeSprite2Pos, { 0.0f,0.0f });
	//A�L�[�̃X�v���C�g
	Sprite* newAKeySprite = new Sprite();
	newAKeySprite->Initialize();
	AKeySprite.reset(newAKeySprite);
	AKeySprite->SetTextureNum(64);
	AKeySprite->Update(AKeySpritePos, keySpriteScale1);
	//A�L�[�̃X�v���C�g �����Ă��鎞
	Sprite* newAKeyPushSprite = new Sprite();
	newAKeyPushSprite->Initialize();
	AKeyPushSprite.reset(newAKeyPushSprite);
	AKeyPushSprite->SetTextureNum(65);
	AKeyPushSprite->Update(AKeySpritePos, keySpriteScale1);
	//D�L�[�̃X�v���C�g
	Sprite* newDKeySprite = new Sprite();
	newDKeySprite->Initialize();
	DKeySprite.reset(newDKeySprite);
	DKeySprite->SetTextureNum(70);
	DKeySprite->Update(DKeySpritePos, keySpriteScale1);
	//D�L�[�̃X�v���C�g �����Ă��鎞
	Sprite* newDKeyPushSprite = new Sprite();
	newDKeyPushSprite->Initialize();
	DKeyPushSprite.reset(newDKeyPushSprite);
	DKeyPushSprite->SetTextureNum(71);
	DKeyPushSprite->Update(DKeySpritePos, keySpriteScale1);
	//S�L�[�̃X�v���C�g
	Sprite* newSKeySprite = new Sprite();
	newSKeySprite->Initialize();
	SKeySprite.reset(newSKeySprite);
	SKeySprite->SetTextureNum(68);
	SKeySprite->Update(SKeySpritePos, keySpriteScale1);
	//S�L�[�̃X�v���C�g �����Ă��鎞
	Sprite* newSKeyPushSprite = new Sprite();
	newSKeyPushSprite->Initialize();
	SKeyPushSprite.reset(newSKeyPushSprite);
	SKeyPushSprite->SetTextureNum(69);
	SKeyPushSprite->Update(SKeySpritePos, keySpriteScale1);
	//W�L�[�̃X�v���C�g
	Sprite* newWKeySprite = new Sprite();
	newWKeySprite->Initialize();
	WKeySprite.reset(newWKeySprite);
	WKeySprite->SetTextureNum(66);
	WKeySprite->Update(WKeySpritePos, keySpriteScale1);
	//W�L�[�̃X�v���C�g �����Ă��鎞
	Sprite* newWKeyPushSprite = new Sprite();
	newWKeyPushSprite->Initialize();
	WKeyPushSprite.reset(newWKeyPushSprite);
	WKeyPushSprite->SetTextureNum(67);
	WKeyPushSprite->Update(WKeySpritePos, keySpriteScale1);
	//Left�L�[�̃X�v���C�g
	Sprite* newLeftKeySprite = new Sprite();
	newLeftKeySprite->Initialize();
	LeftKeySprite.reset(newLeftKeySprite);
	LeftKeySprite->SetTextureNum(72);
	LeftKeySprite->Update(LeftKeySpritePos, keySpriteScale1);
	//Left�L�[�̃X�v���C�g �����Ă��鎞
	Sprite* newLeftKeyPushSprite = new Sprite();
	newLeftKeyPushSprite->Initialize();
	LeftKeyPushSprite.reset(newLeftKeyPushSprite);
	LeftKeyPushSprite->SetTextureNum(73);
	LeftKeyPushSprite->Update(LeftKeySpritePos, keySpriteScale1);
	//Right�L�[�̃X�v���C�g
	Sprite* newRightKeySprite = new Sprite();
	newRightKeySprite->Initialize();
	RightKeySprite.reset(newRightKeySprite);
	RightKeySprite->SetTextureNum(78);
	RightKeySprite->Update(RightKeySpritePos, keySpriteScale1);
	//Right�L�[�̃X�v���C�g �����Ă��鎞
	Sprite* newRightKeyPushSprite = new Sprite();
	newRightKeyPushSprite->Initialize();
	RightKeyPushSprite.reset(newRightKeyPushSprite);
	RightKeyPushSprite->SetTextureNum(79);
	RightKeyPushSprite->Update(RightKeySpritePos, keySpriteScale1);
	//Up�L�[�̃X�v���C�g
	Sprite* newUpKeySprite = new Sprite();
	newUpKeySprite->Initialize();
	UpKeySprite.reset(newUpKeySprite);
	UpKeySprite->SetTextureNum(74);
	UpKeySprite->Update(UpKeySpritePos, keySpriteScale1);
	//Up�L�[�̃X�v���C�g �����Ă��鎞
	Sprite* newUpKeyPushSprite = new Sprite();
	newUpKeyPushSprite->Initialize();
	UpKeyPushSprite.reset(newUpKeyPushSprite);
	UpKeyPushSprite->SetTextureNum(75);
	UpKeyPushSprite->Update(UpKeySpritePos, keySpriteScale1);
	//Down�L�[�̃X�v���C�g
	Sprite* newDownKeySprite = new Sprite();
	newDownKeySprite->Initialize();
	DownKeySprite.reset(newDownKeySprite);
	DownKeySprite->SetTextureNum(76);
	DownKeySprite->Update(DownKeySpritePos, keySpriteScale1);
	//Down�L�[�̃X�v���C�g �����Ă��鎞
	Sprite* newDownKeyPushSprite = new Sprite();
	newDownKeyPushSprite->Initialize();
	DownKeyPushSprite.reset(newDownKeyPushSprite);
	DownKeyPushSprite->SetTextureNum(77);
	DownKeyPushSprite->Update(DownKeySpritePos, keySpriteScale1);
	//L�X�e�B�b�N�̃X�v���C�g
	Sprite* newLStickSprite2 = new Sprite();
	newLStickSprite2->Initialize();
	LStickSprite2.reset(newLStickSprite2);
	LStickSprite2->SetTextureNum(42);
	LStickSprite2->Update(LStickSpritePos2, stickSpriteScale);
	//R�X�e�B�b�N�̃X�v���C�g
	Sprite* newRStickSprite2 = new Sprite();
	newRStickSprite2->Initialize();
	RStickSprite2.reset(newRStickSprite2);
	RStickSprite2->SetTextureNum(43);
	RStickSprite2->Update(RStickSpritePos2, stickSpriteScale);
	//A�L�[�̃X�v���C�g
	Sprite* newAKeySprite2 = new Sprite();
	newAKeySprite2->Initialize();
	AKeySprite2.reset(newAKeySprite2);
	AKeySprite2->SetTextureNum(64);
	AKeySprite2->Update(AKeySpritePos2, keySpriteScale1);
	//D�L�[�̃X�v���C�g
	Sprite* newDKeySprite2 = new Sprite();
	newDKeySprite2->Initialize();
	DKeySprite2.reset(newDKeySprite2);
	DKeySprite2->SetTextureNum(70);
	DKeySprite2->Update(DKeySpritePos2, keySpriteScale1); 
	//S�L�[�̃X�v���C�g
	Sprite* newSKeySprite2 = new Sprite();
	newSKeySprite2->Initialize();
	SKeySprite2.reset(newSKeySprite2);
	SKeySprite2->SetTextureNum(68);
	SKeySprite2->Update(SKeySpritePos2, keySpriteScale1);
	//W�L�[�̃X�v���C�g
	Sprite* newWKeySprite2 = new Sprite();
	newWKeySprite2->Initialize();
	WKeySprite2.reset(newWKeySprite2);
	WKeySprite2->SetTextureNum(66);
	WKeySprite2->Update(WKeySpritePos2, keySpriteScale1);
	//Left�L�[�̃X�v���C�g
	Sprite* newLeftKeySprite2 = new Sprite();
	newLeftKeySprite2->Initialize();
	LeftKeySprite2.reset(newLeftKeySprite2);
	LeftKeySprite2->SetTextureNum(72);
	LeftKeySprite2->Update(LeftKeySpritePos2, keySpriteScale1);
	//Right�L�[�̃X�v���C�g
	Sprite* newRightKeySprite2 = new Sprite();
	newRightKeySprite2->Initialize();
	RightKeySprite2.reset(newRightKeySprite2);
	RightKeySprite2->SetTextureNum(78);
	RightKeySprite2->Update(RightKeySpritePos2, keySpriteScale1);
	//Up�L�[�̃X�v���C�g
	Sprite* newUpKeySprite2 = new Sprite();
	newUpKeySprite2->Initialize();
	UpKeySprite2.reset(newUpKeySprite2);
	UpKeySprite2->SetTextureNum(74);
	UpKeySprite2->Update(UpKeySpritePos2, keySpriteScale1);
	//Down�L�[�̃X�v���C�g
	Sprite* newDownKeySprite2 = new Sprite();
	newDownKeySprite2->Initialize();
	DownKeySprite2.reset(newDownKeySprite2);
	DownKeySprite2->SetTextureNum(76);
	DownKeySprite2->Update(DownKeySpritePos2, keySpriteScale1);
	//LB�{�^���̃X�v���C�g
	Sprite* newLBButtonSprite2 = new Sprite();
	newLBButtonSprite2->Initialize();
	LBButtonSprite2.reset(newLBButtonSprite2);
	LBButtonSprite2->SetTextureNum(47);
	LBButtonSprite2->Update(LBButtonSpritePos2, BButtonSpriteScale);
	//RB�{�^���̃X�v���C�g
	Sprite* newRBButtonSprite2 = new Sprite();
	newRBButtonSprite2->Initialize();
	RBButtonSprite2.reset(newRBButtonSprite2);
	RBButtonSprite2->SetTextureNum(48);
	RBButtonSprite2->Update(RBButtonSpritePos2, BButtonSpriteScale);
	//�X�y�[�X�L�[�̃X�v���C�g
	Sprite* newSpaceKeySprite2 = new Sprite();
	newSpaceKeySprite2->Initialize();
	spaceKeySprite2.reset(newSpaceKeySprite2);
	spaceKeySprite2->SetTextureNum(80);
	spaceKeySprite2->Update(SpaceKeySpritePos3, keySpriteScale2);
	//�V�t�g�L�[�̃X�v���C�g
	Sprite* newShiftKeySprite = new Sprite();
	newShiftKeySprite->Initialize();
	shiftKeySprite1.reset(newShiftKeySprite);
	shiftKeySprite1->SetTextureNum(82);
	shiftKeySprite1->Update(shiftKeySpritePos1, keySpriteScale2);
	//�V�t�g�L�[�̃X�v���C�g
	Sprite* newShiftKeyPushSprite = new Sprite();
	newShiftKeyPushSprite->Initialize();
	shiftKeyPushSprite1.reset(newShiftKeyPushSprite);
	shiftKeyPushSprite1->SetTextureNum(83);
	shiftKeyPushSprite1->Update(shiftKeySpritePos1, keySpriteScale2);
	//�V�t�g�L�[�̃X�v���C�g
	Sprite* newShiftKeySprite2 = new Sprite();
	newShiftKeySprite2->Initialize();
	shiftKeySprite2.reset(newShiftKeySprite2);
	shiftKeySprite2->SetTextureNum(82);
	shiftKeySprite2->Update(shiftKeySpritePos2, keySpriteScale3);
	//�����ω���UI�X�v���C�g
	Sprite* newChangeElementSprite1 = new Sprite();
	newChangeElementSprite1->Initialize();
	changeElementSprite1.reset(newChangeElementSprite1);
	changeElementSprite1->SetTextureNum(52);
	changeElementSprite1->Update(changeElementSpritePos, changeElementspriteScale);
	//�����ω���UI�X�v���C�g
	Sprite* newChangeElementSprite2 = new Sprite();
	newChangeElementSprite2->Initialize();
	changeElementSprite2.reset(newChangeElementSprite2);
	changeElementSprite2->SetTextureNum(53);
	changeElementSprite2->Update(changeElementSpritePos, changeElementspriteScale);
	//�����ω���UI�X�v���C�g
	Sprite* newChangeElementSprite3 = new Sprite();
	newChangeElementSprite3->Initialize();
	changeElementSprite3.reset(newChangeElementSprite3);
	changeElementSprite3->SetTextureNum(54);
	changeElementSprite3->SetAlpha(0.5f);
	changeElementSprite3->Update(changeElementSpritePos, changeElementspriteScale);
	//�����ω���UI�X�v���C�g
	Sprite* newChangeElementSprite4 = new Sprite();
	newChangeElementSprite4->Initialize();
	changeElementSprite4.reset(newChangeElementSprite4);
	changeElementSprite4->SetTextureNum(55);
	changeElementSprite4->SetAlpha(0.5f);
	changeElementSprite4->Update(changeElementSpritePos, changeElementspriteScale);
	//�U��UI�X�v���C�g
	Sprite* newAttackElecSpriteSprite = new Sprite();
	newAttackElecSpriteSprite->Initialize();
	attackElecSprite.reset(newAttackElecSpriteSprite);
	attackElecSprite->SetTextureNum(56);
	attackElecSprite->Update(attackSpritePos, attackSpriteScale);
	//�U��UI�X�v���C�g
	Sprite* newAttackFireSpriteSprite = new Sprite();
	newAttackFireSpriteSprite->Initialize();
	attackFireSprite.reset(newAttackFireSpriteSprite);
	attackFireSprite->SetTextureNum(57);
	attackFireSprite->Update(attackSpritePos, attackSpriteScale);
	//ESC�L�[�̃X�v���C�g
	Sprite* newEscKeySprite = new Sprite();
	newEscKeySprite->Initialize();
	escKeySprite.reset(newEscKeySprite);
	escKeySprite->SetTextureNum(84);
	escKeySprite->Update(escKeySpritePos, escKeySpriteScale);
	//START�{�^���̃X�v���C�g
	Sprite* newStartButtonSprite = new Sprite();
	newStartButtonSprite->Initialize();
	startButtonSprite.reset(newStartButtonSprite);
	startButtonSprite->SetTextureNum(85);
	startButtonSprite->Update(startButtonSpritePos, startButtonSpriteScale);
}

void UI::UpdateGame()
{
}

void UI::UpdateTutorial()
{
	//�X�e�B�b�N����`���[�g���A��
	if (tutorialFlag == 2)
	{
		//�Q�[�W�X�V
		if (RStickTimer < RStickTime)
		{
			gaugeSprite2->SetScale({ gaugeSpriteScale.x * ((float)RStickTimer / (float)RStickTime)
				,gaugeSpriteScale.y });
			//�X�v���C�g�X�V
			gaugeSprite2->Update();
		}
		//�Q�[�W�X�V
		if (LStickTimer < LStickTime)
		{
			gaugeSprite1->SetScale({ gaugeSpriteScale.x * ((float)LStickTimer / (float)LStickTime)
				,gaugeSpriteScale.y });
			//�X�v���C�g�X�V
			gaugeSprite1->Update();
		}
	}

	//���Ԍo�߂ōU���`���[�g���A����
	if (iikannjiTimer >= iikannjiTime - 1 && tutorialFlag == 3)
	{
		//�Q�[�W�̃X�P�[�������Ƃɖ߂�
		gaugeSprite1->SetScale({ 0.0f,0.0f });
		gaugeSprite2->SetScale({ 0.0f,0.0f });
		//�X�y�[�X�L�[�̃X�v���C�g�̃X�P�[���ƍ��W�X�V
		spaceKeySprite1->Update(SpaceKeySpritePos2,keySpriteScale3);
		spaceKeyPushSprite1->Update(SpaceKeySpritePos2,keySpriteScale3);
		//�X�v���C�g�X�V
		gaugeSprite1->Update();
		gaugeSprite2->Update();
	}

	//�U���`���[�g���A��
	if (tutorialFlag == 4)
	{
		if (dxInput->PushKey(DXInput::PAD_RIGHT_SHOULDER) == 1)
		{
			//�Q�[�W�X�V
			if (attackTimer < attackTime)
			{
				gaugeSprite1->SetScale({ gaugeSpriteScale.x * ((float)attackTimer / (float)attackTime)
					,gaugeSpriteScale.y });
				//�X�v���C�g�X�V
				gaugeSprite1->Update();
			}
		}
	}

	//���������`���[�g���A�� LB�{�^���A�V�t�g�L�[�̍��W��ς���
	if (iikannjiTimer >= iikannjiTime - 1 && tutorialFlag == 7)
	{
		LBButtonSprite1->Update(LBButtonSpritePos3, BButtonSpriteScale);
		LBButtonPushSprite1->Update(LBButtonSpritePos3, BButtonSpriteScale);
		shiftKeySprite1->Update(shiftKeySpritePos3, keySpriteScale2);
		shiftKeyPushSprite1->Update(shiftKeySpritePos3, keySpriteScale2);
	}

	//�|���Ă݂悤�`���[�g���A�� RB�{�^���A�X�y�[�X�L�[�̍��W��ς���
	if (iikannjiTimer >= iikannjiTime - 1 && tutorialFlag == 9)
	{
		RBButtonSprite1->Update(RBButtonSpritePos3, BButtonSpriteScale);
		RBButtonPushSprite1->Update(RBButtonSpritePos3, BButtonSpriteScale);
		spaceKeySprite1->Update(SpaceKeySpritePos4, keySpriteScale2);
		spaceKeyPushSprite1->Update(SpaceKeySpritePos4, keySpriteScale2);
	}

	//�G���o�ꂷ��܂ł̊�
	if (tutorialFlag == 12)
	{
		tutorial1Sprite->SetPosition(tutorial1Pos + XMFLOAT2(0.0f, tutorial12Timer * 2.5f));
		if (tutorial12Timer >= tutorial12Time)
		{
			tutorial1Sprite->SetPosition(tutorial1Pos);
		}
		//�X�v���C�g�X�V
		tutorial1Sprite->Update();
	}

	//�X�L�b�v�̏���
	if (dxInput->GetConnectFlag() == true && dxInput->GetOldConnectFlag() == false)
		tutorial12Sprite->Update(tutorial12Pos1, tutorial12Scale);
	if (dxInput->GetConnectFlag() == false && dxInput->GetOldConnectFlag() == true)
		tutorial12Sprite->Update(tutorial12Pos2, tutorial12Scale);

	/*shiftKeySprite1->SetPosition(XMFLOAT2(debugNum));
	shiftKeySprite1->Update();*/
	/*tutorial12Sprite->SetPosition(XMFLOAT2(debugNum1));
	tutorial12Sprite->SetScale(XMFLOAT2(tutorial12Scale * debugNum2[0]));
	escKeySprite->SetPosition(XMFLOAT2(debugNum3));
	escKeySprite->SetScale(XMFLOAT2(escKeySpriteScale * debugNum4[0]));
	startButtonSprite->SetPosition(XMFLOAT2(debugNum5));
	startButtonSprite->SetScale(XMFLOAT2(startButtonSpriteScale * debugNum6[0]));
	tutorial12Sprite->Update();
	escKeySprite->Update();
	startButtonSprite->Update();*/
}

void UI::UpdateTitle()
{
	//�^�C�g���̕��� �V�[���J�ڎ�
	if (titleTimer > titleTime)
	{
		title1Sprite->SetPosition(XMFLOAT2(title1Pos.x, title1Pos.y -
			easeOutCirc(((float)titleTimer - (float)titleTime) / 180) * (float)titleTime));
		title2Sprite->SetPosition(XMFLOAT2(title2Pos.x, title2Pos.y +
			easeOutCirc(((float)titleTimer - (float)titleTime) / 180) * (float)titleTime));
		//�R���g���[���[���ڑ���
		if (dxInput->GetConnectFlag() == false)
		{
			spaceKeySprite1->SetPosition(XMFLOAT2(spaceKeySpritePos1.x, spaceKeySpritePos1.y +
				easeOutCirc(((float)titleTimer - (float)titleTime) / 180) * (float)titleTime));
			spaceKeyPushSprite1->SetPosition(XMFLOAT2(spaceKeySpritePos1.x, spaceKeySpritePos1.y +
				easeOutCirc(((float)titleTimer - (float)titleTime) / 180) * (float)titleTime));
		}
		//�R���g���[���[�ڑ���
		if (dxInput->GetConnectFlag() == true)
		{
			AButtonSprite->SetPosition(XMFLOAT2(AButtonPos.x, AButtonPos.y +
				easeOutCirc(((float)titleTimer - (float)titleTime) / 180) * (float)titleTime));
			AButtonPushSprite->SetPosition(XMFLOAT2(AButtonPos.x, AButtonPos.y +
				easeOutCirc(((float)titleTimer - (float)titleTime) / 180) * (float)titleTime));
		}
	}
	//�^�C�g���̕��� �ʏ펞
	else
	{
		title1Sprite->SetPosition(title1Pos);
		title2Sprite->SetPosition(title2Pos);
		//�R���g���[���[���ڑ���
		if (dxInput->GetConnectFlag() == false)
		{
			spaceKeySprite1->SetPosition(spaceKeySpritePos1);
			spaceKeyPushSprite1->SetPosition(spaceKeySpritePos1);
		}
		//�R���g���[���[�ڑ���
		if (dxInput->GetConnectFlag() == true)
		{
			AButtonSprite->SetPosition(AButtonPos);
			AButtonPushSprite->SetPosition(AButtonPos);
		}
	}

	//�{�^���p�̃^�C�}�[�X�V
	buttonTimer++;
	if (buttonTimer >= buttonMaxTime)
	{
		buttonTimer = 0;
	}

	//�R���g���[���[�����X�v���C�g�̏���
	titleSprite3Timer += titleSprite3Add;
	if (titleSprite3Timer >= titleSprite3MaxTime || titleSprite3Timer <= 0)
	{
		titleSprite3Add *= -1;
	}
	title3Sprite->SetAlpha((float)titleSprite3Timer / (float)titleSprite3MaxTime);


	//�X�v���C�g�̍X�V
	title1Sprite->Update();
	title2Sprite->Update();
	title3Sprite->Update();
	spaceKeySprite1->Update();
	spaceKeyPushSprite1->Update();
	AButtonSprite->Update();
	AButtonPushSprite->Update();
}

void UI::DrawGame(ID3D12GraphicsCommandList* cmdList)
{
	//�����`�F���WUI ��
	if (playerForm == Fire)
	{
		changeElementSprite1->Draw(cmdList);
	}
	//�����`�F���WUI �d�C
	if (playerForm == Elec)
	{
		changeElementSprite2->Draw(cmdList);
	}
	//�����`�F���W��
	if (formChangeFlag == true)
	{
		changeElementSprite4->Draw(cmdList);
	}
	//�����ς������
	else
	{
		changeElementSprite3->Draw(cmdList);
	}
	//�R���g���[���[�ڑ��� LB�{�^��
	if (dxInput->GetConnectFlag() == true)
	{
		//�{�^�������Ă��鎞
		if (dxInput->PushKey(DXInput::PAD_LEFT_SHOULDER) == 1)
		{
			LBButtonPushSprite1->Draw(cmdList);
		}
		//�����Ă��Ȃ���
		else
		{
			LBButtonSprite1->Draw(cmdList);
		}
	}
	//�R���g���[���[���ڑ��� �V�t�g�L�[
	if (dxInput->GetConnectFlag() == false)
	{
		//�����Ă��鎞
		if (input->PushKey(DIK_LSHIFT) == 1 || input->PushKey(DIK_RSHIFT) == 1)
		{
			shiftKeyPushSprite1->Draw(cmdList);
		}
		//�����Ă��Ȃ���
		else
		{
			shiftKeySprite1->Draw(cmdList);
		}
	}

	if (playerForm == Fire)
	{
		attackFireSprite->Draw(cmdList);
	}
	if (playerForm == Elec)
	{
		attackElecSprite->Draw(cmdList);
	}
	//�R���g���[���[�ڑ��� RB�{�^��
	if (dxInput->GetConnectFlag() == true)
	{
		//�{�^�������Ă��鎞
		if (dxInput->PushKey(DXInput::PAD_RIGHT_SHOULDER) == 1)
		{
			RBButtonPushSprite1->Draw(cmdList);
		}
		//�����Ă��Ȃ���
		else
		{
			RBButtonSprite1->Draw(cmdList);
		}
	}
	//�R���g���[���[���ڑ��� �X�y�[�X�L�[
	if (dxInput->GetConnectFlag() == false)
	{
		//�X�y�[�X�L�[�����Ă��鎞
		if (input->PushKey(DIK_SPACE) == 1)
		{
			spaceKeyPushSprite1->Draw(cmdList);
		}
		//�����Ă��Ȃ���
		else
		{
			spaceKeySprite1->Draw(cmdList);
		}
	}
}

void UI::DrawTutorial(ID3D12GraphicsCommandList* cmdList)
{
	//�{�X�o�ꎞ�ȊO�g�ƃX�L�b�v�`��
	if (tutorialFlag < 13)tutorial1Sprite->Draw(cmdList);

	//�{�X�o�ꎞ�ȊO�X�L�b�v�`��
	if (tutorialFlag < 12)
	{
		tutorial12Sprite->Draw(cmdList);
		if (dxInput->GetConnectFlag() == true)startButtonSprite->Draw(cmdList);
		if (dxInput->GetConnectFlag() == false)escKeySprite->Draw(cmdList);
	}
	//�X�e�B�b�N���͂̕`��
	if (tutorialFlag == 2)
	{
		//����
		tutorial2Sprite->Draw(cmdList);
		//�R���g���[���[�ڑ��� �X�e�B�b�N��Ui
		if (dxInput->GetConnectFlag() == true)
		{
			LStickSprite->Draw(cmdList);
			RStickSprite->Draw(cmdList);
		}
		//�R���g���[���[���ڑ��� �L�[�{�[�h
		if (dxInput->GetConnectFlag() == false)
		{
			if(input->PushKey(DIK_A))AKeyPushSprite->Draw(cmdList);
			else { AKeySprite->Draw(cmdList); }
			if (input->PushKey(DIK_S))SKeyPushSprite->Draw(cmdList);
			else { SKeySprite->Draw(cmdList); }
			if (input->PushKey(DIK_W))WKeyPushSprite->Draw(cmdList);
			else { WKeySprite->Draw(cmdList); }
			if (input->PushKey(DIK_D))DKeyPushSprite->Draw(cmdList);
			else { DKeySprite->Draw(cmdList); }
			if (input->PushKey(DIK_LEFT))LeftKeyPushSprite->Draw(cmdList);
			else { LeftKeySprite->Draw(cmdList); }
			if (input->PushKey(DIK_RIGHT))RightKeyPushSprite->Draw(cmdList);
			else { RightKeySprite->Draw(cmdList); }
			if (input->PushKey(DIK_UP))UpKeyPushSprite->Draw(cmdList);
			else { UpKeySprite->Draw(cmdList); }
			if (input->PushKey(DIK_DOWN))DownKeyPushSprite->Draw(cmdList);
			else { DownKeySprite->Draw(cmdList); }
		}
		//�R���g���[���[�ڑ��� ���Ɏg���R���g���[���[�̃{�^��
		if (dxInput->GetConnectFlag() == true)
		{
			LStickSprite2->Draw(cmdList);
			RStickSprite2->Draw(cmdList);
		}
		//�R���g���[���[���ڑ��� ���Ɏg���L�[�{�[�h
		if (dxInput->GetConnectFlag() == false)
		{
			AKeySprite2->Draw(cmdList);
			DKeySprite2->Draw(cmdList);
			SKeySprite2->Draw(cmdList);
			WKeySprite2->Draw(cmdList);
			LeftKeySprite2->Draw(cmdList);
			RightKeySprite2->Draw(cmdList);
			UpKeySprite2->Draw(cmdList);
			DownKeySprite2->Draw(cmdList);
		}
		//�`���[�g���A���B���Ń`�F�b�N�}�[�N
		if (LStickTimer > LStickTime)
		{
			checkSprite1->Draw(cmdList);
		}
		if (RStickTimer > RStickTime)
		{
			checkSprite2->Draw(cmdList);
		}
		//�`�F�b�N�}�[�N�̃t���[��
		checkFrameSprite1->Draw(cmdList);
		checkFrameSprite2->Draw(cmdList);
		//�Q�[�W
		gaugeSprite1->Draw(cmdList);
		gaugeSprite2->Draw(cmdList);
		tutorialFrameSprite1->Draw(cmdList);
		tutorialFrameSprite2->Draw(cmdList);
	}
	//���������\�����Ă���Ԃ��`�F�b�N�}�[�N�o��
	if (tutorialFlag == 3)
	{
		//�R���g���[���[�ڑ��� �X�e�B�b�N��Ui
		if (dxInput->GetConnectFlag() == true)
		{
			LStickSprite->Draw(cmdList);
			RStickSprite->Draw(cmdList);
		}
		//�R���g���[���[���ڑ��� �L�[�{�[�h
		if (dxInput->GetConnectFlag() == false)
		{
			if (input->PushKey(DIK_A))AKeyPushSprite->Draw(cmdList);
			else { AKeySprite->Draw(cmdList); }
			if (input->PushKey(DIK_S))SKeyPushSprite->Draw(cmdList);
			else { SKeySprite->Draw(cmdList); }
			if (input->PushKey(DIK_W))WKeyPushSprite->Draw(cmdList);
			else { WKeySprite->Draw(cmdList); }
			if (input->PushKey(DIK_D))DKeyPushSprite->Draw(cmdList);
			else { DKeySprite->Draw(cmdList); }
			if (input->PushKey(DIK_LEFT))LeftKeyPushSprite->Draw(cmdList);
			else { LeftKeySprite->Draw(cmdList); }
			if (input->PushKey(DIK_RIGHT))RightKeyPushSprite->Draw(cmdList);
			else { RightKeySprite->Draw(cmdList); }
			if (input->PushKey(DIK_UP))UpKeyPushSprite->Draw(cmdList);
			else { UpKeySprite->Draw(cmdList); }
			if (input->PushKey(DIK_DOWN))DownKeyPushSprite->Draw(cmdList);
			else { DownKeySprite->Draw(cmdList); }
		}
		//�`�F�b�N�}�[�N
		checkSprite1->Draw(cmdList);
		checkSprite2->Draw(cmdList);
		//�Q�[�W
		gaugeSprite1->Draw(cmdList);
		gaugeSprite2->Draw(cmdList);
		//�`�F�b�N�}�[�N�̘g
		checkFrameSprite1->Draw(cmdList);
		checkFrameSprite2->Draw(cmdList);
		tutorialFrameSprite1->Draw(cmdList);
		tutorialFrameSprite2->Draw(cmdList);
	}
	//���������I�̃X�v���C�g
	if (tutorialFlag == 3 || tutorialFlag == 5 || tutorialFlag == 9)tutorial3Sprite->Draw(cmdList);
	//�U���`���[�g���A��
	if (tutorialFlag == 4)
	{
		tutorial4Sprite->Draw(cmdList);
		//�R���g���[���[�ڑ��� RB�{�^��
		if (dxInput->GetConnectFlag() == true)
		{
			//�{�^�������Ă��鎞
			if (dxInput->PushKey(DXInput::PAD_RIGHT_SHOULDER) == 1)
			{
				RBButtonPushSprite1->Draw(cmdList);
			}
			//�����Ă��Ȃ���
			else
			{
				RBButtonSprite1->Draw(cmdList);
			}
		}
		//�R���g���[���[���ڑ��� �X�y�[�X�L�[
		if (dxInput->GetConnectFlag() == false)
		{
			//�X�y�[�X�L�[�����Ă��鎞
			if (input->PushKey(DIK_SPACE) == 1)
			{
				spaceKeyPushSprite1->Draw(cmdList);
			}
			//�����Ă��Ȃ���
			else
			{
				spaceKeySprite1->Draw(cmdList);
			}
		}
		//�R���g���[���[�ڑ��� ���Ɏg��RB�{�^��
		if (dxInput->GetConnectFlag() == true)
		{
			RBButtonSprite2->Draw(cmdList);
		}
		//�R���g���[���[���ڑ��� ���Ɏg���X�y�[�X�L�[
		if (dxInput->GetConnectFlag() == false)
		{
			spaceKeySprite2->Draw(cmdList);
		}
		//�`�F�b�N�}�[�N
		if (attackTimer >= attackTime)
		{
			checkSprite1->Draw(cmdList);
		}
		checkFrameSprite1->Draw(cmdList);
		gaugeSprite1->Draw(cmdList);
		tutorialFrameSprite1->Draw(cmdList);
	}
	//���������\�����Ă���Ԃ��`�F�b�N�}�[�N�o��
	if (tutorialFlag == 5)
	{
		//�R���g���[���[�ڑ��� RB�{�^��
		if (dxInput->GetConnectFlag() == true)
		{
			//�{�^�������Ă��鎞
			if (dxInput->PushKey(DXInput::PAD_RIGHT_SHOULDER) == 1)
			{
				RBButtonPushSprite1->Draw(cmdList);
			}
			//�����Ă��Ȃ���
			else
			{
				RBButtonSprite1->Draw(cmdList);
			}
		}
		//�R���g���[���[���ڑ��� �X�y�[�X�L�[
		if (dxInput->GetConnectFlag() == false)
		{
			//�X�y�[�X�L�[�����Ă��鎞
			if (input->PushKey(DIK_SPACE) == 1)
			{
				spaceKeyPushSprite1->Draw(cmdList);
			}
			//�����Ă��Ȃ���
			else
			{
				spaceKeySprite1->Draw(cmdList);
			}
		}
		//�`�F�b�N�}�[�N
		if (attackTimer >= attackTime)
		{
			checkSprite1->Draw(cmdList);
		}
		checkFrameSprite1->Draw(cmdList);
		gaugeSprite1->Draw(cmdList);
		tutorialFrameSprite1->Draw(cmdList);
	}
	if (tutorialFlag == 6)
	{
		//�R���g���[���[�ڑ��� LB�{�^��
		if (dxInput->GetConnectFlag() == true)
		{
			//�{�^�������Ă��鎞
			if (dxInput->PushKey(DXInput::PAD_LEFT_SHOULDER) == 1)
			{
				LBButtonPushSprite1->Draw(cmdList);
			}
			//�����Ă��Ȃ���
			else
			{
				LBButtonSprite1->Draw(cmdList);
			}
		}
		//�R���g���[���[���ڑ��� �V�t�g�L�[
		if (dxInput->GetConnectFlag() == false)
		{
			//�����Ă��鎞
			if (input->PushKey(DIK_LSHIFT) == 1 || input->PushKey(DIK_RSHIFT) == 1)
			{
				shiftKeyPushSprite1->Draw(cmdList);
			}
			//�����Ă��Ȃ���
			else
			{
				shiftKeySprite1->Draw(cmdList);
			}
		}
		//�R���g���[���[�ڑ��� ���Ɏg��LB�{�^��
		if (dxInput->GetConnectFlag() == true)
		{
			LBButtonSprite2->Draw(cmdList);
		}
		//�R���g���[���[���ڑ��� ���Ɏg���V�t�g�L�[
		if (dxInput->GetConnectFlag() == false)
		{
			shiftKeySprite2->Draw(cmdList);
		}
		checkFrameSprite1->Draw(cmdList);
		tutorial6Sprite->Draw(cmdList);
	}
	if (tutorialFlag == 7)
	{
		tutorial7Sprite->Draw(cmdList);
		//�R���g���[���[�ڑ��� LB�{�^��
		if (dxInput->GetConnectFlag() == true)
		{
			//�{�^�������Ă��鎞
			if (dxInput->PushKey(DXInput::PAD_LEFT_SHOULDER) == 1)
			{
				LBButtonPushSprite1->Draw(cmdList);
			}
			//�����Ă��Ȃ���
			else
			{
				LBButtonSprite1->Draw(cmdList);
			}
		}
		//�R���g���[���[���ڑ��� �V�t�g�L�[
		if (dxInput->GetConnectFlag() == false)
		{
			//�����Ă��鎞
			if (input->PushKey(DIK_LSHIFT) == 1 || input->PushKey(DIK_RSHIFT) == 1)
			{
				shiftKeyPushSprite1->Draw(cmdList);
			}
			//�����Ă��Ȃ���
			else
			{
				shiftKeySprite1->Draw(cmdList);
			}
		}
		checkSprite1->Draw(cmdList);
		checkFrameSprite1->Draw(cmdList);
	}
	if (tutorialFlag == 8)
	{
		tutorial8Sprite->Draw(cmdList);
		//�R���g���[���[�ڑ��� RB�{�^��
		if (dxInput->GetConnectFlag() == true)
		{
			//�{�^�������Ă��鎞
			if (dxInput->PushKey(DXInput::PAD_RIGHT_SHOULDER) == 1)
			{
				RBButtonPushSprite1->Draw(cmdList);
			}
			//�����Ă��Ȃ���
			else
			{
				RBButtonSprite1->Draw(cmdList);
			}
		}
		//�R���g���[���[���ڑ��� �X�y�[�X�L�[
		if (dxInput->GetConnectFlag() == false)
		{
			//�X�y�[�X�L�[�����Ă��鎞
			if (input->PushKey(DIK_SPACE) == 1)
			{
				spaceKeyPushSprite1->Draw(cmdList);
			}
			//�����Ă��Ȃ���
			else
			{
				spaceKeySprite1->Draw(cmdList);
			}
		}
		checkFrameSprite1->Draw(cmdList);
	}
	if (tutorialFlag == 9)
	{
		//�R���g���[���[�ڑ��� RB�{�^��
		if (dxInput->GetConnectFlag() == true)
		{
			//�{�^�������Ă��鎞
			if (dxInput->PushKey(DXInput::PAD_RIGHT_SHOULDER) == 1)
			{
				RBButtonPushSprite1->Draw(cmdList);
			}
			//�����Ă��Ȃ���
			else
			{
				RBButtonSprite1->Draw(cmdList);
			}
		}
		//�R���g���[���[���ڑ��� �X�y�[�X�L�[
		if (dxInput->GetConnectFlag() == false)
		{
			//�X�y�[�X�L�[�����Ă��鎞
			if (input->PushKey(DIK_SPACE) == 1)
			{
				spaceKeyPushSprite1->Draw(cmdList);
			}
			//�����Ă��Ȃ���
			else
			{
				spaceKeySprite1->Draw(cmdList);
			}
		}
		//�`�F�b�N�}�[�N
		checkSprite1->Draw(cmdList);
		checkFrameSprite1->Draw(cmdList);
	}

	//�����ω�UI�̕`��
	if (tutorialFlag > 7 && tutorialFlag < 12)
	{
		//�����`�F���WUI ��
		if (playerForm == Fire)
		{
			changeElementSprite1->Draw(cmdList);
		}
		//�����`�F���WUI �d�C
		if (playerForm == Elec)
		{
			changeElementSprite2->Draw(cmdList);
		}
		//�����`�F���W��
		if (formChangeFlag == true)
		{
			changeElementSprite4->Draw(cmdList);
		}
		//�����ς������
		else
		{
			changeElementSprite3->Draw(cmdList);
		}
		//�R���g���[���[�ڑ��� LB�{�^��
		if (dxInput->GetConnectFlag() == true)
		{
			//�{�^�������Ă��鎞
			if (dxInput->PushKey(DXInput::PAD_LEFT_SHOULDER) == 1)
			{
				LBButtonPushSprite1->Draw(cmdList);
			}
			//�����Ă��Ȃ���
			else
			{
				LBButtonSprite1->Draw(cmdList);
			}
		}
		//�R���g���[���[���ڑ��� �V�t�g�L�[
		if (dxInput->GetConnectFlag() == false)
		{
			//�����Ă��鎞
			if (input->PushKey(DIK_LSHIFT) == 1 || input->PushKey(DIK_RSHIFT) == 1)
			{
				shiftKeyPushSprite1->Draw(cmdList);
			}
			//�����Ă��Ȃ���
			else
			{
				shiftKeySprite1->Draw(cmdList);
			}
		}
	}

	//�U��UI�̕`��
	if (tutorialFlag > 9 && tutorialFlag < 12)
	{
		if (playerForm == Fire)
		{
			attackFireSprite->Draw(cmdList);
		}
		if (playerForm == Elec)
		{
			attackElecSprite->Draw(cmdList);
		}
		//�R���g���[���[�ڑ��� RB�{�^��
		if (dxInput->GetConnectFlag() == true)
		{
			//�{�^�������Ă��鎞
			if (dxInput->PushKey(DXInput::PAD_RIGHT_SHOULDER) == 1)
			{
				RBButtonPushSprite1->Draw(cmdList);
			}
			//�����Ă��Ȃ���
			else
			{
				RBButtonSprite1->Draw(cmdList);
			}
		}
		//�R���g���[���[���ڑ��� �X�y�[�X�L�[
		if (dxInput->GetConnectFlag() == false)
		{
			//�X�y�[�X�L�[�����Ă��鎞
			if (input->PushKey(DIK_SPACE) == 1)
			{
				spaceKeyPushSprite1->Draw(cmdList);
			}
			//�����Ă��Ȃ���
			else
			{
				spaceKeySprite1->Draw(cmdList);
			}
		}
	}

	if (tutorialFlag == 10)tutorial10Sprite->Draw(cmdList);
	if (tutorialFlag == 11)tutorial11Sprite->Draw(cmdList);

	//ImGui
	ImGui::Begin("UI Tutorial");
	ImGui::SetWindowPos(ImVec2(600, 0));
	ImGui::SetWindowSize(ImVec2(500, 300));
	ImGui::InputFloat2("tu12Pos", debugNum1);
	ImGui::InputFloat2("tu12Size", debugNum2);
	ImGui::InputFloat2("escPos", debugNum3);
	ImGui::InputFloat2("escSize", debugNum4);
	ImGui::InputFloat2("startPos", debugNum5);
	ImGui::InputFloat2("startSize", debugNum6);
	ImGui::End();
}

void UI::DrawTitle(ID3D12GraphicsCommandList* cmdList)
{
	title1Sprite->Draw(cmdList);
	title2Sprite->Draw(cmdList);
	//�R���g���[���[���ڑ���
	if (dxInput->GetConnectFlag() == false)
	{
		//�X�y�[�X�L�[�̃A�j���[�V����
		if (buttonTimer < buttonChangeTime)
		{
			spaceKeySprite1->Draw(cmdList);
		}
		else
		{
			spaceKeyPushSprite1->Draw(cmdList);
		}
	}
	//�R���g���[���[�ڑ���
	if (dxInput->GetConnectFlag() == true)
	{
		//�{�^���̃A�j���[�V����
		if (buttonTimer < buttonChangeTime)
		{
			AButtonSprite->Draw(cmdList);
		}
		else
		{
			AButtonPushSprite->Draw(cmdList);
		}
	}
	//�R���g���[���[�����̃X�v���C�g
	if (titleTimer < titleTime)
	{
		title3Sprite->Draw(cmdList);
	}
}

void UI::SetGame()
{
	RBButtonSprite1->Update(RBButtonSpritePos3, BButtonSpriteScale);
	RBButtonPushSprite1->Update(RBButtonSpritePos3, BButtonSpriteScale);
	spaceKeySprite1->Update(SpaceKeySpritePos4, keySpriteScale2);
	spaceKeyPushSprite1->Update(SpaceKeySpritePos4, keySpriteScale2);
	LBButtonSprite1->Update(LBButtonSpritePos3, BButtonSpriteScale);
	LBButtonPushSprite1->Update(LBButtonSpritePos3, BButtonSpriteScale);
	shiftKeySprite1->Update(shiftKeySpritePos3, keySpriteScale2);
	shiftKeyPushSprite1->Update(shiftKeySpritePos3, keySpriteScale2);
}

void UI::SetTitleTimer(int moveTutorialTimer, int moveTutorialTime)
{
	this->titleTimer = moveTutorialTimer;
	this->titleTime = moveTutorialTime;
}

void UI::SetTutorialTimer(int LStickTimer, int LStickTime, int RStickTimer, int RStickTime,
	int attackTimer, int attackTime, int attackTimer2, int attackTime2,
	int iikannjiTimer, int iikannjiTime, int tutorial12Timer, int tutorial12Time)
{
	this->LStickTimer = LStickTimer;
	this->LStickTime = LStickTime;
	this->RStickTimer = RStickTimer;
	this->RStickTime = RStickTime;
	this->attackTimer = attackTimer;
	this->attackTime = attackTime;
	this->attackTimer2 = attackTimer2;
	this->attackTime2 = attackTime2;
	this->iikannjiTimer = iikannjiTimer;
	this->iikannjiTime = iikannjiTime;
	this->tutorial12Timer = tutorial12Timer;
	this->tutorial12Time = tutorial12Time;
}

void UI::SetPlayerForm(int form, bool formChangeFlag)
{
	if (form == 0)this->playerForm = Fire;
	if (form == 1)this->playerForm = Elec;
	this->formChangeFlag = formChangeFlag;
}

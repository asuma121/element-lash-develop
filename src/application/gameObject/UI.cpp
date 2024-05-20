#include "UI.h"
#include "mathOriginal.h"
#include "imgui.h"

KeyManager* UI::keyManager = nullptr;

void UI::Initialize()
{
	//�����X�v���C�g1
	Sprite* newBlackSprite1 = new Sprite();
	newBlackSprite1->Initialize();
	blackSprite1.reset(newBlackSprite1);
	blackSprite1->SetTextureNum(83);
	blackSprite1->Update(black1Pos,black1Scale);
	//�����X�v���C�g2
	Sprite* newBlackSprite2 = new Sprite();
	newBlackSprite2->Initialize();
	blackSprite2.reset(newBlackSprite2);
	blackSprite2->SetTextureNum(83);
	blackSprite2->Update(black2Pos, black2Scale);
	//�����X�v���C�g2
	Sprite* newBlackSprite3 = new Sprite();
	newBlackSprite3->Initialize();
	blackSprite3.reset(newBlackSprite3);
	blackSprite3->SetTextureNum(83);
	blackSprite3->Update(black3Pos, black3Scale);

	//�^�C�g���̃X�v���C�g
	Sprite* newTitle1Sprite = new Sprite();
	newTitle1Sprite->Initialize();
	title1Sprite.reset(newTitle1Sprite);
	title1Sprite->SetTextureNum(34);
	title1Sprite->Update(title1Pos,title1Scale);
	//�^�C�g���̃X�v���C�g2
	Sprite* newTitle2Sprite = new Sprite();
	newTitle2Sprite->Initialize();
	title2Sprite.reset(newTitle2Sprite);
	title2Sprite->SetTextureNum(35);
	title2Sprite->Update(title2Pos, title2Scale);
	//�^�C�g���̃X�v���C�g3
	Sprite* newTitle3Sprite = new Sprite();
	newTitle3Sprite->Initialize();
	title3Sprite.reset(newTitle3Sprite);
	title3Sprite->SetTextureNum(36);
	title3Sprite->Update(title3Pos, title3Scale);
	//�X�y�[�X�L�[��
	Sprite* newSpaceKeySprite = new Sprite();
	newSpaceKeySprite->Initialize();
	spaceKeySprite1.reset(newSpaceKeySprite);
	spaceKeySprite1->SetTextureNum(27);
	spaceKeySprite1->Update(spaceKeySpritePos1, spaceKeySpriteScale1);
	//�����Ă���X�y�[�X�L�[�̃X�v���C�g
	Sprite* newSpaceKeyPushSprite = new Sprite();
	newSpaceKeyPushSprite->Initialize();
	spaceKeyPushSprite1.reset(newSpaceKeyPushSprite);
	spaceKeyPushSprite1->SetTextureNum(28);
	spaceKeyPushSprite1->Update(spaceKeySpritePos1, spaceKeySpriteScale1);
	//A�{�^���̃X�v���C�g
	Sprite* newAButtonSprite = new Sprite();
	newAButtonSprite->Initialize();
	AButtonSprite.reset(newAButtonSprite);
	AButtonSprite->SetTextureNum(1);
	AButtonSprite->Update(AButtonPos, AButtonScale);
	//�����Ă���A�{�^���̃X�v���C�g
	Sprite* newAButtonPushSprite = new Sprite();
	newAButtonPushSprite->Initialize();
	AButtonPushSprite.reset(newAButtonPushSprite);
	AButtonPushSprite->SetTextureNum(2);
	AButtonPushSprite->Update(AButtonPos, AButtonScale);

	//�`���[�g���A���̃X�v���C�g1
	Sprite* newTutorial1Sprite = new Sprite();
	newTutorial1Sprite->Initialize();
	tutorial1Sprite.reset(newTutorial1Sprite);
	tutorial1Sprite->SetTextureNum(66);
	tutorial1Sprite->Update(tutorial1Pos, tutorial1Scale);
	//�`���[�g���A���̃X�v���C�g2
	Sprite* newTutorial2Sprite = new Sprite();
	newTutorial2Sprite->Initialize();
	tutorial2Sprite.reset(newTutorial2Sprite);
	tutorial2Sprite->SetTextureNum(37);
	tutorial2Sprite->Update(tutorial2Pos, tutorial2Scale);
	//�`���[�g���A���̃X�v���C�g3
	Sprite* newTutorial3Sprite = new Sprite();
	newTutorial3Sprite->Initialize();
	tutorial3Sprite.reset(newTutorial3Sprite);
	tutorial3Sprite->SetTextureNum(38);
	tutorial3Sprite->Update(tutorial3Pos, tutorial3Scale);
	//�`���[�g���A���̃X�v���C�g4
	Sprite* newTutorial4Sprite = new Sprite();
	newTutorial4Sprite->Initialize();
	tutorial4Sprite.reset(newTutorial4Sprite);
	tutorial4Sprite->SetTextureNum(39);
	tutorial4Sprite->Update(tutorial4Pos, tutorial4Scale);
	//�`���[�g���A���̃X�v���C�g6
	Sprite* newTutorial6Sprite = new Sprite();
	newTutorial6Sprite->Initialize();
	tutorial6Sprite.reset(newTutorial6Sprite);
	tutorial6Sprite->SetTextureNum(40);
	tutorial6Sprite->Update(tutorial6Pos, tutorial6Scale);
	//�`���[�g���A���̃X�v���C�g7
	Sprite* newTutorial7Sprite = new Sprite();
	newTutorial7Sprite->Initialize();
	tutorial7Sprite.reset(newTutorial7Sprite);
	tutorial7Sprite->SetTextureNum(41);
	tutorial7Sprite->Update(tutorial6Pos,tutorial6Scale);
	//�`���[�g���A���̃X�v���C�g8
	Sprite* newTutorial8Sprite = new Sprite();
	newTutorial8Sprite->Initialize();
	tutorial8Sprite.reset(newTutorial8Sprite);
	tutorial8Sprite->SetTextureNum(42);
	tutorial8Sprite->Update(tutorial8Pos, tutorial8Scale);
	//�`���[�g���A���̃X�v���C�g10
	Sprite* newTutorial10Sprite = new Sprite();
	newTutorial10Sprite->Initialize();
	tutorial10Sprite.reset(newTutorial10Sprite);
	tutorial10Sprite->SetTextureNum(43);
	tutorial10Sprite->Update(tutorial10Pos, tutorial10Scale);
	//�`���[�g���A���̃X�v���C�g11
	Sprite* newTutorial11Sprite = new Sprite();
	newTutorial11Sprite->Initialize();
	tutorial11Sprite.reset(newTutorial11Sprite);
	tutorial11Sprite->SetTextureNum(44);
	tutorial11Sprite->Update(tutorial11Pos, tutorial11Scale);
	//�`���[�g���A���̃X�v���C�g12
	Sprite* newTutorial12Sprite = new Sprite();
	newTutorial12Sprite->Initialize();
	tutorial12Sprite.reset(newTutorial12Sprite);
	tutorial12Sprite->SetTextureNum(45);
	if(keyManager->GetConnectFlag() == true)
		tutorial12Sprite->Update(tutorial12Pos1, tutorial12Scale);
	if (keyManager->GetConnectFlag() == false)
		tutorial12Sprite->Update(tutorial12Pos2, tutorial12Scale);
	//L�X�e�B�b�N�̃X�v���C�g
	Sprite* newLStickSprite = new Sprite();
	newLStickSprite->Initialize();
	LStickSprite.reset(newLStickSprite);
	LStickSprite->SetTextureNum(13);
	LStickSprite->Update(LStickSpritePos, stickSpriteScale);
	//R�X�e�B�b�N�̃X�v���C�g
	Sprite* newRStickSprite = new Sprite();
	newRStickSprite->Initialize();
	RStickSprite.reset(newRStickSprite);
	RStickSprite->SetTextureNum(18);
	RStickSprite->Update(RStickSpritePos, stickSpriteScale);
	//LB�{�^���̃X�v���C�g
	Sprite* newLBButtonSprite = new Sprite();
	newLBButtonSprite->Initialize();
	LBButtonSprite1.reset(newLBButtonSprite);
	LBButtonSprite1->SetTextureNum(9);
	LBButtonSprite1->Update(LBButtonSpritePos, BButtonSpriteScale);
	//LB�{�^���̃X�v���C�g �����Ă��鎞
	Sprite* newLBButtonPushSprite = new Sprite();
	newLBButtonPushSprite->Initialize();
	LBButtonPushSprite1.reset(newLBButtonPushSprite);
	LBButtonPushSprite1->SetTextureNum(10);
	LBButtonPushSprite1->Update(LBButtonSpritePos, BButtonSpriteScale);
	//RB�{�^���̃X�v���C�g
	Sprite* newRBButtonSprite = new Sprite();
	newRBButtonSprite->Initialize();
	RBButtonSprite1.reset(newRBButtonSprite);
	RBButtonSprite1->SetTextureNum(14);
	RBButtonSprite1->Update(RBButtonSpritePos, BButtonSpriteScale);
	//RB�{�^���̃X�v���C�g �����Ă��鎞
	Sprite* newRBButtonPushSprite = new Sprite();
	newRBButtonPushSprite->Initialize();
	RBButtonPushSprite1.reset(newRBButtonPushSprite);
	RBButtonPushSprite1->SetTextureNum(15);
	RBButtonPushSprite1->Update(RBButtonSpritePos, BButtonSpriteScale);
	//�`�F�b�N�}�[�N�̃X�v���C�g
	Sprite* newCheckSprite1 = new Sprite();
	newCheckSprite1->Initialize();
	checkSprite1.reset(newCheckSprite1);
	checkSprite1->SetTextureNum(56);
	checkSprite1->Update(checkSprite1Pos, checkSpriteScale);
	//�`�F�b�N�}�[�N�̃X�v���C�g
	Sprite* newCheckSprite2 = new Sprite();
	newCheckSprite2->Initialize();
	checkSprite2.reset(newCheckSprite2);
	checkSprite2->SetTextureNum(56);
	checkSprite2->Update(checkSprite2Pos, checkSpriteScale);
	//�`�F�b�N�}�[�N�̘g�̃X�v���C�g
	Sprite* newCheckFrameSprite = new Sprite();
	newCheckFrameSprite->Initialize();
	checkFrameSprite1.reset(newCheckFrameSprite);
	checkFrameSprite1->SetTextureNum(57);
	checkFrameSprite1->Update(checkFrameSprite1Pos, checkFrameSpriteScale);
	//�`�F�b�N�}�[�N�̘g�̃X�v���C�g
	Sprite* newCheckFrameSprite2 = new Sprite();
	newCheckFrameSprite2->Initialize();
	checkFrameSprite2.reset(newCheckFrameSprite2);
	checkFrameSprite2->SetTextureNum(57);
	checkFrameSprite2->Update(checkFrameSprite2Pos, checkFrameSpriteScale);
	//�g�̃X�v���C�g
	Sprite* newTutorialFrameSprite1 = new Sprite();
	newTutorialFrameSprite1->Initialize();
	tutorialFrameSprite1.reset(newTutorialFrameSprite1);
	tutorialFrameSprite1->SetTextureNum(67);
	tutorialFrameSprite1->Update(tutorialFrameSprite1Pos, tutorialFrameSpriteScale);
	//�g�̃X�v���C�g
	Sprite* newTutorialFrameSprite2 = new Sprite();
	newTutorialFrameSprite2->Initialize();
	tutorialFrameSprite2.reset(newTutorialFrameSprite2);
	tutorialFrameSprite2->SetTextureNum(67);
	tutorialFrameSprite2->Update(tutorialFrameSprite2Pos, tutorialFrameSpriteScale);
	//�Q�[�W�̃X�v���C�g
	Sprite* newGaugeSprite1 = new Sprite();
	newGaugeSprite1->Initialize();
	gaugeSprite1.reset(newGaugeSprite1);
	gaugeSprite1->SetTextureNum(59);
	gaugeSprite1->Update(gaugeSprite1Pos, { 0.0f,0.0f });
	//�Q�[�W�̃X�v���C�g
	Sprite* newGaugeSprite2 = new Sprite();
	newGaugeSprite2->Initialize();
	gaugeSprite2.reset(newGaugeSprite2);
	gaugeSprite2->SetTextureNum(59);
	gaugeSprite2->Update(gaugeSprite2Pos, { 0.0f,0.0f });
	//A�L�[�̃X�v���C�g
	Sprite* newAKeySprite = new Sprite();
	newAKeySprite->Initialize();
	AKeySprite.reset(newAKeySprite);
	AKeySprite->SetTextureNum(3);
	AKeySprite->Update(AKeySpritePos, keySpriteScale1);
	//A�L�[�̃X�v���C�g �����Ă��鎞
	Sprite* newAKeyPushSprite = new Sprite();
	newAKeyPushSprite->Initialize();
	AKeyPushSprite.reset(newAKeyPushSprite);
	AKeyPushSprite->SetTextureNum(4);
	AKeyPushSprite->Update(AKeySpritePos, keySpriteScale1);
	//D�L�[�̃X�v���C�g
	Sprite* newDKeySprite = new Sprite();
	newDKeySprite->Initialize();
	DKeySprite.reset(newDKeySprite);
	DKeySprite->SetTextureNum(5);
	DKeySprite->Update(DKeySpritePos, keySpriteScale1);
	//D�L�[�̃X�v���C�g �����Ă��鎞
	Sprite* newDKeyPushSprite = new Sprite();
	newDKeyPushSprite->Initialize();
	DKeyPushSprite.reset(newDKeyPushSprite);
	DKeyPushSprite->SetTextureNum(6);
	DKeyPushSprite->Update(DKeySpritePos, keySpriteScale1);
	//S�L�[�̃X�v���C�g
	Sprite* newSKeySprite = new Sprite();
	newSKeySprite->Initialize();
	SKeySprite.reset(newSKeySprite);
	SKeySprite->SetTextureNum(25);
	SKeySprite->Update(SKeySpritePos, keySpriteScale1);
	//S�L�[�̃X�v���C�g �����Ă��鎞
	Sprite* newSKeyPushSprite = new Sprite();
	newSKeyPushSprite->Initialize();
	SKeyPushSprite.reset(newSKeyPushSprite);
	SKeyPushSprite->SetTextureNum(26);
	SKeyPushSprite->Update(SKeySpritePos, keySpriteScale1);
	//W�L�[�̃X�v���C�g
	Sprite* newWKeySprite = new Sprite();
	newWKeySprite->Initialize();
	WKeySprite.reset(newWKeySprite);
	WKeySprite->SetTextureNum(23);
	WKeySprite->Update(WKeySpritePos, keySpriteScale1);
	//W�L�[�̃X�v���C�g �����Ă��鎞
	Sprite* newWKeyPushSprite = new Sprite();
	newWKeyPushSprite->Initialize();
	WKeyPushSprite.reset(newWKeyPushSprite);
	WKeyPushSprite->SetTextureNum(24);
	WKeyPushSprite->Update(WKeySpritePos, keySpriteScale1);
	//Left�L�[�̃X�v���C�g
	Sprite* newLeftKeySprite = new Sprite();
	newLeftKeySprite->Initialize();
	LeftKeySprite.reset(newLeftKeySprite);
	LeftKeySprite->SetTextureNum(11);
	LeftKeySprite->Update(LeftKeySpritePos, keySpriteScale1);
	//Left�L�[�̃X�v���C�g �����Ă��鎞
	Sprite* newLeftKeyPushSprite = new Sprite();
	newLeftKeyPushSprite->Initialize();
	LeftKeyPushSprite.reset(newLeftKeyPushSprite);
	LeftKeyPushSprite->SetTextureNum(12);
	LeftKeyPushSprite->Update(LeftKeySpritePos, keySpriteScale1);
	//Right�L�[�̃X�v���C�g
	Sprite* newRightKeySprite = new Sprite();
	newRightKeySprite->Initialize();
	RightKeySprite.reset(newRightKeySprite);
	RightKeySprite->SetTextureNum(16);
	RightKeySprite->Update(RightKeySpritePos, keySpriteScale1);
	//Right�L�[�̃X�v���C�g �����Ă��鎞
	Sprite* newRightKeyPushSprite = new Sprite();
	newRightKeyPushSprite->Initialize();
	RightKeyPushSprite.reset(newRightKeyPushSprite);
	RightKeyPushSprite->SetTextureNum(17);
	RightKeyPushSprite->Update(RightKeySpritePos, keySpriteScale1);
	//Up�L�[�̃X�v���C�g
	Sprite* newUpKeySprite = new Sprite();
	newUpKeySprite->Initialize();
	UpKeySprite.reset(newUpKeySprite);
	UpKeySprite->SetTextureNum(21);
	UpKeySprite->Update(UpKeySpritePos, keySpriteScale1);
	//Up�L�[�̃X�v���C�g �����Ă��鎞
	Sprite* newUpKeyPushSprite = new Sprite();
	newUpKeyPushSprite->Initialize();
	UpKeyPushSprite.reset(newUpKeyPushSprite);
	UpKeyPushSprite->SetTextureNum(22);
	UpKeyPushSprite->Update(UpKeySpritePos, keySpriteScale1);
	//Down�L�[�̃X�v���C�g
	Sprite* newDownKeySprite = new Sprite();
	newDownKeySprite->Initialize();
	DownKeySprite.reset(newDownKeySprite);
	DownKeySprite->SetTextureNum(7);
	DownKeySprite->Update(DownKeySpritePos, keySpriteScale1);
	//Down�L�[�̃X�v���C�g �����Ă��鎞
	Sprite* newDownKeyPushSprite = new Sprite();
	newDownKeyPushSprite->Initialize();
	DownKeyPushSprite.reset(newDownKeyPushSprite);
	DownKeyPushSprite->SetTextureNum(8);
	DownKeyPushSprite->Update(DownKeySpritePos, keySpriteScale1);
	//L�X�e�B�b�N�̃X�v���C�g
	Sprite* newLStickSprite2 = new Sprite();
	newLStickSprite2->Initialize();
	LStickSprite2.reset(newLStickSprite2);
	LStickSprite2->SetTextureNum(13);
	LStickSprite2->Update(LStickSpritePos2, stickSpriteScale);
	//R�X�e�B�b�N�̃X�v���C�g
	Sprite* newRStickSprite2 = new Sprite();
	newRStickSprite2->Initialize();
	RStickSprite2.reset(newRStickSprite2);
	RStickSprite2->SetTextureNum(18);
	RStickSprite2->Update(RStickSpritePos2, stickSpriteScale);
	//A�L�[�̃X�v���C�g
	Sprite* newAKeySprite2 = new Sprite();
	newAKeySprite2->Initialize();
	AKeySprite2.reset(newAKeySprite2);
	AKeySprite2->SetTextureNum(3);
	AKeySprite2->Update(AKeySpritePos2, keySpriteScale1);
	//D�L�[�̃X�v���C�g
	Sprite* newDKeySprite2 = new Sprite();
	newDKeySprite2->Initialize();
	DKeySprite2.reset(newDKeySprite2);
	DKeySprite2->SetTextureNum(5);
	DKeySprite2->Update(DKeySpritePos2, keySpriteScale1); 
	//S�L�[�̃X�v���C�g
	Sprite* newSKeySprite2 = new Sprite();
	newSKeySprite2->Initialize();
	SKeySprite2.reset(newSKeySprite2);
	SKeySprite2->SetTextureNum(25);
	SKeySprite2->Update(SKeySpritePos2, keySpriteScale1);
	//W�L�[�̃X�v���C�g
	Sprite* newWKeySprite2 = new Sprite();
	newWKeySprite2->Initialize();
	WKeySprite2.reset(newWKeySprite2);
	WKeySprite2->SetTextureNum(23);
	WKeySprite2->Update(WKeySpritePos2, keySpriteScale1);
	//Left�L�[�̃X�v���C�g
	Sprite* newLeftKeySprite2 = new Sprite();
	newLeftKeySprite2->Initialize();
	LeftKeySprite2.reset(newLeftKeySprite2);
	LeftKeySprite2->SetTextureNum(11);
	LeftKeySprite2->Update(LeftKeySpritePos2, keySpriteScale1);
	//Right�L�[�̃X�v���C�g
	Sprite* newRightKeySprite2 = new Sprite();
	newRightKeySprite2->Initialize();
	RightKeySprite2.reset(newRightKeySprite2);
	RightKeySprite2->SetTextureNum(16);
	RightKeySprite2->Update(RightKeySpritePos2, keySpriteScale1);
	//Up�L�[�̃X�v���C�g
	Sprite* newUpKeySprite2 = new Sprite();
	newUpKeySprite2->Initialize();
	UpKeySprite2.reset(newUpKeySprite2);
	UpKeySprite2->SetTextureNum(21);
	UpKeySprite2->Update(UpKeySpritePos2, keySpriteScale1);
	//Down�L�[�̃X�v���C�g
	Sprite* newDownKeySprite2 = new Sprite();
	newDownKeySprite2->Initialize();
	DownKeySprite2.reset(newDownKeySprite2);
	DownKeySprite2->SetTextureNum(7);
	DownKeySprite2->Update(DownKeySpritePos2, keySpriteScale1);
	//LB�{�^���̃X�v���C�g
	Sprite* newLBButtonSprite2 = new Sprite();
	newLBButtonSprite2->Initialize();
	LBButtonSprite2.reset(newLBButtonSprite2);
	LBButtonSprite2->SetTextureNum(9);
	LBButtonSprite2->Update(LBButtonSpritePos2, BButtonSpriteScale);
	//RB�{�^���̃X�v���C�g
	Sprite* newRBButtonSprite2 = new Sprite();
	newRBButtonSprite2->Initialize();
	RBButtonSprite2.reset(newRBButtonSprite2);
	RBButtonSprite2->SetTextureNum(14);
	RBButtonSprite2->Update(RBButtonSpritePos2, BButtonSpriteScale);
	//�X�y�[�X�L�[�̃X�v���C�g
	Sprite* newSpaceKeySprite2 = new Sprite();
	newSpaceKeySprite2->Initialize();
	spaceKeySprite2.reset(newSpaceKeySprite2);
	spaceKeySprite2->SetTextureNum(27);
	spaceKeySprite2->Update(SpaceKeySpritePos3, keySpriteScale2);
	//�V�t�g�L�[�̃X�v���C�g
	Sprite* newShiftKeySprite = new Sprite();
	newShiftKeySprite->Initialize();
	shiftKeySprite1.reset(newShiftKeySprite);
	shiftKeySprite1->SetTextureNum(19);
	shiftKeySprite1->Update(shiftKeySpritePos1, keySpriteScale2);
	//�V�t�g�L�[�̃X�v���C�g
	Sprite* newShiftKeyPushSprite = new Sprite();
	newShiftKeyPushSprite->Initialize();
	shiftKeyPushSprite1.reset(newShiftKeyPushSprite);
	shiftKeyPushSprite1->SetTextureNum(20);
	shiftKeyPushSprite1->Update(shiftKeySpritePos1, keySpriteScale2);
	//�V�t�g�L�[�̃X�v���C�g
	Sprite* newShiftKeySprite2 = new Sprite();
	newShiftKeySprite2->Initialize();
	shiftKeySprite2.reset(newShiftKeySprite2);
	shiftKeySprite2->SetTextureNum(19);
	shiftKeySprite2->Update(shiftKeySpritePos2, keySpriteScale3);
	//�����ω���UI�X�v���C�g
	Sprite* newChangeElementSprite1 = new Sprite();
	newChangeElementSprite1->Initialize();
	changeElementSprite1.reset(newChangeElementSprite1);
	changeElementSprite1->SetTextureNum(54);
	changeElementSprite1->Update(changeElementSpritePos, changeElementspriteScale);
	//�����ω���UI�X�v���C�g
	Sprite* newChangeElementSprite2 = new Sprite();
	newChangeElementSprite2->Initialize();
	changeElementSprite2.reset(newChangeElementSprite2);
	changeElementSprite2->SetTextureNum(55);
	changeElementSprite2->Update(changeElementSpritePos, changeElementspriteScale);
	//�����ω���UI�X�v���C�g
	Sprite* newChangeElementSprite3 = new Sprite();
	newChangeElementSprite3->Initialize();
	changeElementSprite3.reset(newChangeElementSprite3);
	changeElementSprite3->SetTextureNum(52);
	changeElementSprite3->SetAlpha(0.5f);
	changeElementSprite3->Update(changeElementSpritePos, changeElementspriteScale);
	//�����ω���UI�X�v���C�g
	Sprite* newChangeElementSprite4 = new Sprite();
	newChangeElementSprite4->Initialize();
	changeElementSprite4.reset(newChangeElementSprite4);
	changeElementSprite4->SetTextureNum(53);
	changeElementSprite4->SetAlpha(0.5f);
	changeElementSprite4->Update(changeElementSpritePos, changeElementspriteScale);
	//�U��UI�X�v���C�g
	Sprite* newAttackElecSpriteSprite = new Sprite();
	newAttackElecSpriteSprite->Initialize();
	attackElecSprite.reset(newAttackElecSpriteSprite);
	attackElecSprite->SetTextureNum(50);
	attackElecSprite->Update(attackSpritePos, attackSpriteScale);
	//�U��UI�X�v���C�g
	Sprite* newAttackFireSpriteSprite = new Sprite();
	newAttackFireSpriteSprite->Initialize();
	attackFireSprite.reset(newAttackFireSpriteSprite);
	attackFireSprite->SetTextureNum(51);
	attackFireSprite->Update(attackSpritePos, attackSpriteScale);
	//ESC�L�[�̃X�v���C�g
	Sprite* newEscKeySprite = new Sprite();
	newEscKeySprite->Initialize();
	escKeySprite.reset(newEscKeySprite);
	escKeySprite->SetTextureNum(30);
	escKeySprite->Update(escKeySpritePos, escKeySpriteScale);
	//START�{�^���̃X�v���C�g
	Sprite* newStartButtonSprite = new Sprite();
	newStartButtonSprite->Initialize();
	startButtonSprite.reset(newStartButtonSprite);
	startButtonSprite->SetTextureNum(33);
	startButtonSprite->Update(startButtonSpritePos, startButtonSpriteScale);
	//�G��HP�o�[�̘g
	Sprite* newHpBar1Sprite = new Sprite();
	newHpBar1Sprite->Initialize();
	enemyHpBar1.reset(newHpBar1Sprite);
	enemyHpBar1->SetTextureNum(58);
	enemyHpBar1->Update(enemyHpBar1Pos, enemyHpBar1Scale);
	//�G��HP�o�[
	Sprite* newHpBar2Sprite = new Sprite();
	newHpBar2Sprite->Initialize();
	enemyHpBar2.reset(newHpBar2Sprite);
	enemyHpBar2->SetTextureNum(59);
	enemyHpBar2->Update(enemyHpBar2Pos, enemyHpBar2Scale);
	//�G�̌��݂�HP�̂Ƃ��ɂ�����
	Sprite* newHpBar3Sprite = new Sprite();
	newHpBar3Sprite->Initialize();
	enemyHpBar3.reset(newHpBar3Sprite);
	enemyHpBar3->SetTextureNum(60);
	enemyHpBar3->Update(enemyHpBar3Pos, enemyHpBar3Scale);
	//�G��BOSS HP�̃e�L�X�g
	Sprite* newHpBar4Sprite = new Sprite();
	newHpBar4Sprite->Initialize();
	enemyHpBar4.reset(newHpBar4Sprite);
	enemyHpBar4->SetTextureNum(61);
	enemyHpBar4->Update(enemyHpBar4Pos, enemyHpBar4Scale);
	//�G��HP�o�[�I�����W
	Sprite* newHpBar5Sprite = new Sprite();
	newHpBar5Sprite->Initialize();
	enemyHpBar5.reset(newHpBar5Sprite);
	enemyHpBar5->SetTextureNum(61);
	enemyHpBar5->Update(enemyHpBar5Pos, enemyHpBar5Scale);
	//�v���C���[�̗΂�HP
	for (int i = 0; i < hpSprite1Num; i++)
	{
		Sprite* newHpSprite1 = new Sprite();
		newHpSprite1->Initialize();
		newHpSprite1->SetTextureNum(63);
		hpSprite1.emplace_back(newHpSprite1);
	}
	//�v���C���[�̐Ԃ�HP
	Sprite* newHpSprite2 = new Sprite();
	newHpSprite2->Initialize();
	hpSprite2.reset(newHpSprite2);
	hpSprite2->SetTextureNum(64);
	hpSprite2->Update(hpSpritePos + XMFLOAT2(hpFrameScale1, hpFrameScale3), hpSprite2Scale);
	//�v���C���[��HP�o�[�I�����W
	Sprite* newHpSprite3 = new Sprite();
	newHpSprite3->Initialize();
	hpSprite3.reset(newHpSprite3);
	hpSprite3->SetTextureNum(65);
	hpSprite3->Update(hpSpritePos, hpSprite3Scale);
}

void UI::UpdateGame1()
{
	//�G��HP
	//HP�o�[�����݂�HP��
	enemyHpBar2Scale.x = enemyHpBar2OriginalScale.x * (enemyHP / enemyMaxHP);
	enemyHpBar3Pos.x = enemyHpBar3OriginalPos.x - (enemyHpBar2OriginalScale.x * ((enemyMaxHP - enemyHP) / enemyMaxHP));

	//�v���C���[��HP
	//�΂�HP
	for (int i = 0; i < playerHP; i++)
	{
		XMFLOAT2 addPos(hpFrameScale1 + (hpFrameScale2 * i) +
			(hpSprite1Scale.x * i), hpFrameScale3);
		//�X�V
		hpSprite1[i]->Update(hpSpritePos + addPos, hpSprite1Scale);
	}

	//�X�V
	enemyHpBar1->Update(enemyHpBar1Pos, enemyHpBar1Scale);
	enemyHpBar2->Update(enemyHpBar2Pos, enemyHpBar2Scale);
	enemyHpBar3->Update(enemyHpBar3Pos, enemyHpBar3Scale);
}

void UI::UpdateGame2()
{
	//�G��HP
	//HP�o�[�����݂�HP��
	enemyHpBar5Scale.x = enemyHpBar2OriginalScale.x * (enemyHP / enemyMaxHP);
	enemyHpBar3Pos.x = enemyHpBar3OriginalPos.x - (enemyHpBar2OriginalScale.x * ((enemyMaxHP - enemyHP) / enemyMaxHP));

	//�v���C���[��HP
	//�΂�HP
	for (int i = 0; i < playerHP; i++)
	{
		XMFLOAT2 addPos(hpFrameScale1 + (hpFrameScale2 * i) + 
			(hpSprite1Scale.x * i), hpFrameScale3);
		//�X�V
		hpSprite1[i]->Update(hpSpritePos + addPos, hpSprite1Scale);
	}

	//�X�V
	enemyHpBar3->Update(enemyHpBar3Pos, enemyHpBar3Scale);
	enemyHpBar5->Update(enemyHpBar5Pos, enemyHpBar5Scale);
}

void UI::UpdateTutorial()
{
	//����
	if (tutorialFlag == 1)
	{
		//�^�C�}�[���Z
		blackSpriteTimer++;
		//���������񂾂񖾂邭����
		blackSprite3->SetAlpha((blackSpriteMaxTime - blackSpriteTimer) / blackSpriteMaxTime);
		//�X�v���C�g�X�V
		blackSprite3->Update();
		//���Ԍo�߂ŃX�e�B�b�N����`���[�g���A����
		if (blackSpriteTimer >= blackSpriteMaxTime)
		{
			blackSpriteTimer = 0;
		}
	}
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
		if (keyManager->PushKey(KeyManager::PAD_RIGHT_SHOULDER) == 1)
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
	//�����Ə㉺�̍����o�[
	if (tutorialFlag == 13)
	{
		//����
		if (tutorial13Timer >= tutorial13MaxTime)
		{
			blackSpriteTimer++;
		}
		blackSprite3->SetAlpha(blackSpriteTimer / blackSpriteMaxTime);
		blackSprite3->Update();
	}

	//�X�L�b�v�̏���
	if (keyManager->GetConnectFlag() == true && keyManager->GetOldConnectFlag() == false)
		tutorial12Sprite->Update(tutorial12Pos1, tutorial12Scale);
	if (keyManager->GetConnectFlag() == false && keyManager->GetOldConnectFlag() == true)
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
		if (keyManager->GetConnectFlag() == false)
		{
			spaceKeySprite1->SetPosition(XMFLOAT2(spaceKeySpritePos1.x, spaceKeySpritePos1.y +
				easeOutCirc(((float)titleTimer - (float)titleTime) / 180) * (float)titleTime));
			spaceKeyPushSprite1->SetPosition(XMFLOAT2(spaceKeySpritePos1.x, spaceKeySpritePos1.y +
				easeOutCirc(((float)titleTimer - (float)titleTime) / 180) * (float)titleTime));
		}
		//�R���g���[���[�ڑ���
		if (keyManager->GetConnectFlag() == true)
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
		if (keyManager->GetConnectFlag() == false)
		{
			spaceKeySprite1->SetPosition(spaceKeySpritePos1);
			spaceKeyPushSprite1->SetPosition(spaceKeySpritePos1);
		}
		//�R���g���[���[�ڑ���
		if (keyManager->GetConnectFlag() == true)
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

void UI::UpdateMovePhase()
{
	//����
	if (phaseTimer > phaseMoveTime)
	{
		blackSpriteTimer++;
		blackSprite3->SetAlpha(blackSpriteTimer / blackSpriteMaxTime);
		blackSprite3->Update();
	}
}

void UI::DrawGame1(ID3D12GraphicsCommandList* cmdList)
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
	if (keyManager->GetConnectFlag() == true)
	{
		//�{�^�������Ă��鎞
		if (keyManager->PushKey(KeyManager::PAD_LEFT_SHOULDER) == 1)
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
	if (keyManager->GetConnectFlag() == false)
	{
		//�����Ă��鎞
		if (keyManager->PushKey(KeyManager::PAD_LEFT_SHOULDER) == 1)
		{
			shiftKeyPushSprite1->Draw(cmdList);
		}
		//�����Ă��Ȃ���
		else
		{
			shiftKeySprite1->Draw(cmdList);
		}
	}

	//�U����UI
	if (playerForm == Fire)
	{
		attackFireSprite->Draw(cmdList);
	}
	if (playerForm == Elec)
	{
		attackElecSprite->Draw(cmdList);
	}
	//�R���g���[���[�ڑ��� RB�{�^��
	if (keyManager->GetConnectFlag() == true)
	{
		//�{�^�������Ă��鎞
		if (keyManager->PushKey(KeyManager::PAD_RIGHT_SHOULDER) == 1)
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
	if (keyManager->GetConnectFlag() == false)
	{
		//�X�y�[�X�L�[�����Ă��鎞
		if (keyManager->PushKey(KeyManager::PAD_RIGHT_SHOULDER) == 1)
		{
			spaceKeyPushSprite1->Draw(cmdList);
		}
		//�����Ă��Ȃ���
		else
		{
			spaceKeySprite1->Draw(cmdList);
		}
	}

	//�G��HP
	enemyHpBar5->Draw(cmdList);
	enemyHpBar2->Draw(cmdList);
	/*hpBar4->Draw(cmdList);*/
	enemyHpBar1->Draw(cmdList);
	enemyHpBar3->Draw(cmdList);

	//�v���C���[��HP
	//�΂�HP
	for (int i = 0; i < playerHP; i++)
	{
		hpSprite1[i]->Draw(cmdList);
	}
	//�Ԃ�HP
	if (playerHP == 1)
	{
		hpSprite2->Draw(cmdList);
	}
	//HP�̘g
	hpSprite3->Draw(cmdList);
}

void UI::DrawGame2(ID3D12GraphicsCommandList* cmdList)
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
	if (keyManager->GetConnectFlag() == true)
	{
		//�{�^�������Ă��鎞
		if (keyManager->PushKey(KeyManager::PAD_LEFT_SHOULDER) == 1)
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
	if (keyManager->GetConnectFlag() == false)
	{
		//�����Ă��鎞
		if (keyManager->PushKey(KeyManager::PAD_LEFT_SHOULDER) == 1)
		{
			shiftKeyPushSprite1->Draw(cmdList);
		}
		//�����Ă��Ȃ���
		else
		{
			shiftKeySprite1->Draw(cmdList);
		}
	}

	//�U����UI
	if (playerForm == Fire)
	{
		attackFireSprite->Draw(cmdList);
	}
	if (playerForm == Elec)
	{
		attackElecSprite->Draw(cmdList);
	}
	//�R���g���[���[�ڑ��� RB�{�^��
	if (keyManager->GetConnectFlag() == true)
	{
		//�{�^�������Ă��鎞
		if (keyManager->PushKey(KeyManager::PAD_RIGHT_SHOULDER) == 1)
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
	if (keyManager->GetConnectFlag() == false)
	{
		//�X�y�[�X�L�[�����Ă��鎞
		if (keyManager->PushKey(KeyManager::PAD_RIGHT_SHOULDER) == 1)
		{
			spaceKeyPushSprite1->Draw(cmdList);
		}
		//�����Ă��Ȃ���
		else
		{
			spaceKeySprite1->Draw(cmdList);
		}
	}

	//�G��HP
	enemyHpBar5->Draw(cmdList);
	enemyHpBar1->Draw(cmdList);
	enemyHpBar3->Draw(cmdList);

	//�v���C���[��HP
	//�΂�HP
	for (int i = 0; i < playerHP; i++)
	{
		hpSprite1[i]->Draw(cmdList);
	}
	//�Ԃ�HP
	if (playerHP == 1)
	{
		hpSprite2->Draw(cmdList);
	}
	//HP�̘g
	hpSprite3->Draw(cmdList);
}

void UI::DrawTutorial(ID3D12GraphicsCommandList* cmdList)
{
	//�{�X�o�ꎞ�ȊO�g�ƃX�L�b�v�`��
	if (tutorialFlag < 13)tutorial1Sprite->Draw(cmdList);

	//����
	if (tutorialFlag == 13)
	{
		blackSprite1->Draw(cmdList);
		blackSprite2->Draw(cmdList);
	}
	if (tutorialFlag == 1 || tutorialFlag == 13)
	{
		blackSprite3->Draw(cmdList);
	}

	//�{�X�o�ꎞ�ȊO�X�L�b�v�`��
	if (tutorialFlag < 12)
	{
		tutorial12Sprite->Draw(cmdList);
		if (keyManager->GetConnectFlag() == true)startButtonSprite->Draw(cmdList);
		if (keyManager->GetConnectFlag() == false)escKeySprite->Draw(cmdList);
	}
	//�X�e�B�b�N���͂̕`��
	if (tutorialFlag == 2)
	{
		//����
		tutorial2Sprite->Draw(cmdList);
		//�R���g���[���[�ڑ��� �X�e�B�b�N��Ui
		if (keyManager->GetConnectFlag() == true)
		{
			LStickSprite->Draw(cmdList);
			RStickSprite->Draw(cmdList);
		}
		//�R���g���[���[���ڑ��� �L�[�{�[�h
		if (keyManager->GetConnectFlag() == false)
		{
			if(keyManager->GetStick(KeyManager::LStickX) == -1)AKeyPushSprite->Draw(cmdList);
			else { AKeySprite->Draw(cmdList); }
			if (keyManager->GetStick(KeyManager::LStickY) == -1)SKeyPushSprite->Draw(cmdList);
			else { SKeySprite->Draw(cmdList); }
			if (keyManager->GetStick(KeyManager::LStickY) == 1)WKeyPushSprite->Draw(cmdList);
			else { WKeySprite->Draw(cmdList); }
			if (keyManager->GetStick(KeyManager::LStickX) == 1)DKeyPushSprite->Draw(cmdList);
			else { DKeySprite->Draw(cmdList); }
			if (keyManager->GetStick(KeyManager::RStickX) == -1)LeftKeyPushSprite->Draw(cmdList);
			else { LeftKeySprite->Draw(cmdList); }
			if (keyManager->GetStick(KeyManager::RStickX) == 1)RightKeyPushSprite->Draw(cmdList);
			else { RightKeySprite->Draw(cmdList); }
			if (keyManager->GetStick(KeyManager::RStickY) == 1)UpKeyPushSprite->Draw(cmdList);
			else { UpKeySprite->Draw(cmdList); }
			if (keyManager->GetStick(KeyManager::RStickY) == -1)DownKeyPushSprite->Draw(cmdList);
			else { DownKeySprite->Draw(cmdList); }
		}
		//�R���g���[���[�ڑ��� ���Ɏg���R���g���[���[�̃{�^��
		if (keyManager->GetConnectFlag() == true)
		{
			LStickSprite2->Draw(cmdList);
			RStickSprite2->Draw(cmdList);
		}
		//�R���g���[���[���ڑ��� ���Ɏg���L�[�{�[�h
		if (keyManager->GetConnectFlag() == false)
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
		if (keyManager->GetConnectFlag() == true)
		{
			LStickSprite->Draw(cmdList);
			RStickSprite->Draw(cmdList);
		}
		//�R���g���[���[���ڑ��� �L�[�{�[�h
		if (keyManager->GetConnectFlag() == false)
		{
			if (keyManager->GetStick(KeyManager::LStickX) == -1)AKeyPushSprite->Draw(cmdList);
			else { AKeySprite->Draw(cmdList); }
			if (keyManager->GetStick(KeyManager::LStickY) == -1)SKeyPushSprite->Draw(cmdList);
			else { SKeySprite->Draw(cmdList); }
			if (keyManager->GetStick(KeyManager::LStickY) == 1)WKeyPushSprite->Draw(cmdList);
			else { WKeySprite->Draw(cmdList); }
			if (keyManager->GetStick(KeyManager::LStickX) == 1)DKeyPushSprite->Draw(cmdList);
			else { DKeySprite->Draw(cmdList); }
			if (keyManager->GetStick(KeyManager::RStickX) == -1)LeftKeyPushSprite->Draw(cmdList);
			else { LeftKeySprite->Draw(cmdList); }
			if (keyManager->GetStick(KeyManager::RStickX) == 1)RightKeyPushSprite->Draw(cmdList);
			else { RightKeySprite->Draw(cmdList); }
			if (keyManager->GetStick(KeyManager::RStickY) == 1)UpKeyPushSprite->Draw(cmdList);
			else { UpKeySprite->Draw(cmdList); }
			if (keyManager->GetStick(KeyManager::RStickY) == -1)DownKeyPushSprite->Draw(cmdList);
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
		if (keyManager->GetConnectFlag() == true)
		{
			//�{�^�������Ă��鎞
			if (keyManager->PushKey(KeyManager::PAD_RIGHT_SHOULDER) == 1)
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
		if (keyManager->GetConnectFlag() == false)
		{
			//�X�y�[�X�L�[�����Ă��鎞
			if (keyManager->PushKey(KeyManager::PAD_RIGHT_SHOULDER) == 1)
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
		if (keyManager->GetConnectFlag() == true)
		{
			RBButtonSprite2->Draw(cmdList);
		}
		//�R���g���[���[���ڑ��� ���Ɏg���X�y�[�X�L�[
		if (keyManager->GetConnectFlag() == false)
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
		if (keyManager->GetConnectFlag() == true)
		{
			//�{�^�������Ă��鎞
			if (keyManager->PushKey(KeyManager::PAD_RIGHT_SHOULDER) == 1)
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
		if (keyManager->GetConnectFlag() == false)
		{
			//�X�y�[�X�L�[�����Ă��鎞
			if (keyManager->PushKey(KeyManager::PAD_RIGHT_SHOULDER) == 1)
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
		if (keyManager->GetConnectFlag() == true)
		{
			//�{�^�������Ă��鎞
			if (keyManager->PushKey(KeyManager::PAD_LEFT_SHOULDER) == 1)
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
		if (keyManager->GetConnectFlag() == false)
		{
			//�����Ă��鎞
			if (keyManager->PushKey(KeyManager::PAD_LEFT_SHOULDER) == 1)
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
		if (keyManager->GetConnectFlag() == true)
		{
			LBButtonSprite2->Draw(cmdList);
		}
		//�R���g���[���[���ڑ��� ���Ɏg���V�t�g�L�[
		if (keyManager->GetConnectFlag() == false)
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
		if (keyManager->GetConnectFlag() == true)
		{
			//�{�^�������Ă��鎞
			if (keyManager->PushKey(KeyManager::PAD_LEFT_SHOULDER) == 1)
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
		if (keyManager->GetConnectFlag() == false)
		{
			//�����Ă��鎞
			if (keyManager->PushKey(KeyManager::PAD_LEFT_SHOULDER) == 1)
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
		if (keyManager->GetConnectFlag() == true)
		{
			//�{�^�������Ă��鎞
			if (keyManager->PushKey(KeyManager::PAD_RIGHT_SHOULDER) == 1)
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
		if (keyManager->GetConnectFlag() == false)
		{
			//�X�y�[�X�L�[�����Ă��鎞
			if (keyManager->PushKey(KeyManager::PAD_RIGHT_SHOULDER) == 1)
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
		if (keyManager->GetConnectFlag() == true)
		{
			//�{�^�������Ă��鎞
			if (keyManager->PushKey(KeyManager::PAD_RIGHT_SHOULDER) == 1)
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
		if (keyManager->GetConnectFlag() == false)
		{
			//�X�y�[�X�L�[�����Ă��鎞
			if (keyManager->PushKey(KeyManager::PAD_RIGHT_SHOULDER) == 1)
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
		if (keyManager->GetConnectFlag() == true)
		{
			//�{�^�������Ă��鎞
			if (keyManager->PushKey(KeyManager::PAD_LEFT_SHOULDER) == 1)
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
		if (keyManager->GetConnectFlag() == false)
		{
			//�����Ă��鎞
			if (keyManager->PushKey(KeyManager::PAD_LEFT_SHOULDER) == 1)
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
		if (keyManager->GetConnectFlag() == true)
		{
			//�{�^�������Ă��鎞
			if (keyManager->PushKey(KeyManager::PAD_RIGHT_SHOULDER) == 1)
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
		if (keyManager->GetConnectFlag() == false)
		{
			//�X�y�[�X�L�[�����Ă��鎞
			if (keyManager->PushKey(KeyManager::PAD_RIGHT_SHOULDER) == 1)
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
}

void UI::DrawTitle(ID3D12GraphicsCommandList* cmdList)
{
	title1Sprite->Draw(cmdList);
	title2Sprite->Draw(cmdList);
	//�R���g���[���[���ڑ���
	if (keyManager->GetConnectFlag() == false)
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
	if (keyManager->GetConnectFlag() == true)
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

void UI::DrawMovePhase(ID3D12GraphicsCommandList* cmdList)
{
	//����
	blackSprite1->Draw(cmdList);
	blackSprite2->Draw(cmdList);
	blackSprite3->Draw(cmdList);
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

void UI::SetMovePhase()
{
	blackSpriteTimer = 0;
	blackSprite3->SetAlpha(0.0f);
	blackSprite3->Update();
}

void UI::SetTitleTimer(int moveTutorialTimer, int moveTutorialTime)
{
	this->titleTimer = moveTutorialTimer;
	this->titleTime = moveTutorialTime;
}

void UI::SetHP(int playerHP, int playerMaxHP, int enemyHP, int enemyMaxHP)
{
	this->playerHP = playerHP;
	this->playerMaxHP = playerMaxHP;
	this->enemyHP = enemyHP;
	this->enemyMaxHP = enemyMaxHP;
}

void UI::SetTutorialTimer(int LStickTimer, int LStickTime, int RStickTimer, int RStickTime,
	int attackTimer, int attackTime, int attackTimer2, int attackTime2,
	int iikannjiTimer, int iikannjiTime, int tutorial12Timer, int tutorial12Time,int tutorial13Timer,int tutorial13MaxTime)
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
	this->tutorial13Timer = tutorial13Timer;
	this->tutorial13MaxTime = tutorial13MaxTime;
}

void UI::SetPlayerForm(int form, bool formChangeFlag)
{
	if (form == 0)this->playerForm = Fire;
	if (form == 1)this->playerForm = Elec;
	this->formChangeFlag = formChangeFlag;
}

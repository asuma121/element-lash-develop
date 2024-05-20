#pragma once
#include "Sprite.h"
#include "KeyManager.h"

class UI
{
private:	//エイリアス
	//Microsoft::WRL::を省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private:
	enum Form	//プレイヤーのフォルム
	{
		Fire,	//炎
		Elec,	//電気
	};

public:
	/// <summary>
	///入力セット
	/// </summary>
	static void SetKeyManager(KeyManager* keyManager) { UI::keyManager = keyManager; }

	/// <summary>
	///初期化
	/// </summary>
	void Initialize();

	/// <summary>
	///更新 ゲームシーン
	/// </summary>
	void UpdateGame1();

	/// <summary>
	///更新 ゲームシーン
	/// </summary>
	void UpdateGame2();

	/// <summary>
	///更新 チュートリアルシーン
	/// </summary>
	void UpdateTutorial();

	/// <summary>
	///更新 タイトルシーン
	/// </summary>
	void UpdateTitle();

	/// <summary>
	///更新 フェーズ間の移動
	/// </summary>
	void UpdateMovePhase();

	/// <summary>
	///描画 ゲームシーン
	/// </summary>
	void DrawGame1(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///描画 ゲームシーン
	/// </summary>
	void DrawGame2(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///描画 チュートリアルシーン
	/// </summary>
	void DrawTutorial(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///描画 タイトルシーン
	/// </summary>
	void DrawTitle(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///描画 フェーズ間の移動
	/// </summary>
	void DrawMovePhase(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///ゲームシーン用にUIセット
	/// </summary>
	void SetGame();

	/// <summary>
	///ゲームシーン用にUIセット
	/// </summary>
	void SetMovePhase();

	/// <summary>
	///タイトルシーンのシーン遷移用タイマーセット
	/// </summary>
	void SetTitleTimer(int moveTutorialTimer, int moveTutorialTime);

	/// <summary>
	///チュートリアルシーンのフラグセット
	/// </summary>
	void SetTutorialFlag(int tutorialFlag) { this->tutorialFlag = tutorialFlag; }

	/// <summary>
	///敵、プレイヤーのHPセット
	/// </summary>
	void SetHP(int playerHP,int playerMaxHP,int enemyHP,int enemyMaxHP);

	/// <summary>
	///チュートリアルシーンのタイマーセット
	/// </summary>
	void SetTutorialTimer(int LStickTimer, int LStickTime, int RStickTimer, int RStickTime,
			int attackTimer, int attackTime, int attackTimer2, int attackTime2, 
		int iikannjiTimer,int iikannjiTime, int tutorial12Timer, int tutorial12Time, int tutorial13Timer, int tutorial13MaxTime);

	/// <summary>
	///ゲームシーンのタイマーセット
	/// </summary>
	void SetPhaseTimer(int phaseTimer) { this->phaseTimer = phaseTimer; }

	/// <summary>
	///プレイヤーの状態セット
	/// </summary>
	void SetPlayerForm(int form, bool formChangeFlag);

	//静的メンバ変数
private:
	//キーマネージャー
	static KeyManager* keyManager;

	//メンバ変数
private:

	//外部から受け取る変数
	//ゲームシーンで使っているタイマー
	int phaseTimer = 0;
	//プレイヤーの現在の属性
	Form playerForm;
	//プレイヤーが属性チェンジできるか
	bool formChangeFlag;
	//敵のHP
	float enemyHP = 0;
	float enemyMaxHP = 0;
	//プレイヤーのHP
	float playerHP = 0;
	float playerMaxHP = 0;

	//黒幕等に使用する黒いスプライト
	std::unique_ptr<Sprite>blackSprite1;
	std::unique_ptr<Sprite>blackSprite2;
	std::unique_ptr<Sprite>blackSprite3;
	XMFLOAT2 black1Pos = XMFLOAT2(0.0f, -620.0f);
	XMFLOAT2 black1Scale = { 1280.0f, 720.0f };
	XMFLOAT2 black2Pos = XMFLOAT2(0.0f, 620.0f);
	XMFLOAT2 black2Scale = { 1280.0f, 720.0f };
	XMFLOAT2 black3Pos = { 0.0f, 0.0f };
	XMFLOAT2 black3Scale = { 1280.0f, 720.0f };
	float blackSpriteTimer = 0.0f;
	float blackSpriteMaxTime = 120.0f;
	int phaseMoveTime = 746;
	//キーボード ボタンのUI
	//共通の座標、スケール
	XMFLOAT2 keySpriteScale1 = { 32.0f,32.0f };	//ADSW,AROWキーのスケール
	XMFLOAT2 keySpriteScale2 = { 128.0f * 0.8f,64.0f * 0.8f };	//チュートリアルシーン 左上のスーペス,シフトキーのスケール
	XMFLOAT2 keySpriteScale3 = { 128.0f * 0.6f,64.0f * 0.6f };	//チュートリアルシーン 説明文のスーペス,シフトキーのスケール
	XMFLOAT2 BButtonSpriteScale = { 64.0f,64.0f };	//チュートリアルシーン RB LBボタンのスケール
	XMFLOAT2 stickSpriteScale = { 64.0f,64.0f };	//チュートリアルシーン Rスティック Lスティックのスケール
	//スペースキー
	std::unique_ptr<Sprite>spaceKeySprite1;	//スペースキー
	std::unique_ptr<Sprite>spaceKeyPushSprite1;	//スペースキー 押している状態
	std::unique_ptr<Sprite>spaceKeySprite2;	//チュートリアルシーン 説明文の中のスプライト
	XMFLOAT2 spaceKeySpritePos1 = { 700.0f,500.0f };	//タイトルシーンの座標
	XMFLOAT2 spaceKeySpriteScale1 = { 128.0f,64.0f };	//タイトルシーンのスケール
	XMFLOAT2 SpaceKeySpritePos2 = { 58.0f,114.0f };	//チュートリアルシーン 左上の座標
	XMFLOAT2 SpaceKeySpritePos3 = { 328.0f,580.0f };	//チュートリアルシーン 説明分の座標
	XMFLOAT2 SpaceKeySpritePos4 = { 1096.0f,132.0f };	//チュートリアルシーン 説明分の座標
	//シフトキー
	std::unique_ptr<Sprite>shiftKeySprite1;	//シフトキー
	std::unique_ptr<Sprite>shiftKeyPushSprite1;	//シフトキー押している状態
	std::unique_ptr<Sprite>shiftKeySprite2;	//チュートリアルシーン 説明文の中のスプライト
	XMFLOAT2 shiftKeySpritePos1 = { 58.0f,114.0f };	//チュートリアルシーン 左上の座標
	XMFLOAT2 shiftKeySpritePos2 = { 320.0f,590.0f };	//チュートリアルシーン 説明分の座標
	XMFLOAT2 shiftKeySpritePos3 = { 1096.0f,58.0f };	//ゲームシーン 属性チェンジの座標
	//Aキー
	std::unique_ptr<Sprite>AKeySprite;	//Aキー
	std::unique_ptr<Sprite>AKeyPushSprite;	//Aキー 押している状態
	std::unique_ptr<Sprite>AKeySprite2;
	XMFLOAT2 AKeySpritePos = { 50.0f,132.0f };	//チュートリアシーンの座標 左上の座標
	XMFLOAT2 AKeySpritePos2 = { 326.0f,588.0f };	//チュートリアルシーン 説明分の座標
	//Wキー
	std::unique_ptr<Sprite>WKeySprite;	//Wキー
	std::unique_ptr<Sprite>WKeyPushSprite;	//Wキー 押している状態
	std::unique_ptr<Sprite>WKeySprite2;	//チュートリアルシーン 説明文の中のスプライト
	XMFLOAT2 WKeySpritePos = { 82.0f,100.0f };	//チュートリアシーンの座標 左上の座標
	XMFLOAT2 WKeySpritePos2 = { 358.0f,556.0f };	//チュートリアルシーン 説明分の座標
	//Sキー
	std::unique_ptr<Sprite>SKeySprite;	//Sキー
	std::unique_ptr<Sprite>SKeyPushSprite;	//Sキー 押している状態
	std::unique_ptr<Sprite>SKeySprite2;	//チュートリアルシーン 説明文の中のスプライト
	XMFLOAT2 SKeySpritePos = { 82.0f,132.0f };	//チュートリアシーンの座標 左上の座標
	XMFLOAT2 SKeySpritePos2 = { 358.0f,588.0f };	//チュートリアルシーン 説明分の座標
	//Dキー
	std::unique_ptr<Sprite>DKeySprite;	//Dキー
	std::unique_ptr<Sprite>DKeyPushSprite;	//Dキー 押している状態
	std::unique_ptr<Sprite>DKeySprite2;	//チュートリアルシーン 説明文の中のスプライト
	XMFLOAT2 DKeySpritePos = { 114.0f,132.0f };	//チュートリアシーンの座標 左上の座標
	XMFLOAT2 DKeySpritePos2 = { 390.0f,588.0f };	//チュートリアルシーン 説明分の座標
	//Leftキー
	std::unique_ptr<Sprite>LeftKeySprite;	//Leftキー
	std::unique_ptr<Sprite>LeftKeyPushSprite;	//Leftキー 押している状態
	std::unique_ptr<Sprite>LeftKeySprite2;	//チュートリアルシーン 説明文の中のスプライト
	XMFLOAT2 LeftKeySpritePos = { 50.0f,206.0f };	//チュートリアシーンの座標 左上の座標
	XMFLOAT2 LeftKeySpritePos2 = { 188.0f,646.0f };	//チュートリアルシーン 説明分の座標
	//Rigthキー
	std::unique_ptr<Sprite>RightKeySprite;	//Rightキー
	std::unique_ptr<Sprite>RightKeyPushSprite;	//Rightキー 押している状態
	std::unique_ptr<Sprite>RightKeySprite2;	//チュートリアルシーン 説明文の中のスプライト
	XMFLOAT2 RightKeySpritePos = { 114.0f,206.0f };	//チュートリアシーンの座標 左上の座標
	XMFLOAT2 RightKeySpritePos2 = { 252.0f,646.0f };	//チュートリアルシーン 説明分の座標
	////Upキー
	std::unique_ptr<Sprite>UpKeySprite;	//Upキー
	std::unique_ptr<Sprite>UpKeyPushSprite;	//Upー 押している状態
	std::unique_ptr<Sprite>UpKeySprite2;	//チュートリアルシーン 説明文の中のスプライト
	XMFLOAT2 UpKeySpritePos = { 82.0f,174.0f };	//チュートリアシーンの座標 左上の座標
	XMFLOAT2 UpKeySpritePos2 = { 220.0f,614.0f };	//チュートリアルシーン 説明分の座標
	//Downキー
	std::unique_ptr<Sprite>DownKeySprite;	//Downキー
	std::unique_ptr<Sprite>DownKeyPushSprite;	//Downキー 押している状態
	std::unique_ptr<Sprite>DownKeySprite2;	//チュートリアルシーン 説明文の中のスプライト
	XMFLOAT2 DownKeySpritePos = { 82.0f,206.0f };	//チュートリアシーンの座標 左上の座標
	XMFLOAT2 DownKeySpritePos2 = { 220.0f,646.0f };	//チュートリアルシーン 説明分の座標
	//ESCキー 黄色い文字
	std::unique_ptr<Sprite>escKeySprite;	//ESCキー
	XMFLOAT2 escKeySpritePos = { 0.0f,0.0f };	//チュートリアシーンの座標 チュートリアルスキップ
	XMFLOAT2 escKeySpriteScale = { 109.0f * 0.7f,49.0f * 0.7f };	//チュートリアシーンの座標 チュートリアルスキップ
	//Aボタン
	std::unique_ptr<Sprite>AButtonSprite;	//コントローラーAボタン
	std::unique_ptr<Sprite>AButtonPushSprite;	//押しているコントローラーAボタン
	XMFLOAT2 AButtonPos = { 700.0f,500.0f };	//タイトルシーンの座標
	XMFLOAT2 AButtonScale = { 64.0f,64.0f };	//タイトルシーンのスケール
	//LBボタン
	std::unique_ptr<Sprite>LBButtonSprite1;	//コントローラーLBボタン
	std::unique_ptr<Sprite>LBButtonPushSprite1;	//押しているコントローラーLBボタン
	std::unique_ptr<Sprite>LBButtonSprite2;	//チュートリアルシーン 説明文の中のスプライト
	XMFLOAT2 LBButtonSpritePos = { 50.0f,100.0f };	//チュートリアシーンの座標 左上の座標
	XMFLOAT2 LBButtonSpritePos2 = { 328.0f,576.0f };	//チュートリアルシーン 説明分の座標
	XMFLOAT2 LBButtonSpritePos3 = { 1126.0f,50.0f };	//ゲームシーン 属性チェンジの座標
	//RBボタン
	std::unique_ptr<Sprite>RBButtonSprite1;	//コントローラーRBボタン
	std::unique_ptr<Sprite>RBButtonPushSprite1;	//押しているコントローラーRBボタン
	std::unique_ptr<Sprite>RBButtonSprite2;	//チュートリアルシーン 説明文の中のスプライト
	XMFLOAT2 RBButtonSpritePos = { 50.0f,100.0f };	//チュートリアシーンの座標 左上の座標
	XMFLOAT2 RBButtonSpritePos2 = { 350.0f,570.0f };	//チュートリアルシーン 説明分の座標
	XMFLOAT2 RBButtonSpritePos3 = { 1126.0f,124.0f };	//ゲームシーン 属性チェンジの座標
	//STARTボタン 黄色い文字
	std::unique_ptr<Sprite>startButtonSprite;	//コントローラーSTARTボタン
	XMFLOAT2 startButtonSpritePos = { 0.0f,0.0f };	//チュートリアシーンの座標 チュートリアルスキップ
	XMFLOAT2 startButtonSpriteScale = { 194.0f * 0.7f,49.0f * 0.7f };	//チュートリアシーンの座標 チュートリアルスキップ
	//Lスティックのスプライト
	std::unique_ptr<Sprite>LStickSprite;	//コントローラーLスティック
	std::unique_ptr<Sprite>LStickSprite2;	//コントローラーLスティック 説明文
	XMFLOAT2 LStickSpritePos = { 58.0f,100.0f };	//チュートリアシーンの座標 左上の座標
	XMFLOAT2 LStickSpritePos2 = { 342.0f,556.0f };	//チュートリアルシーン 説明分の座標
	//Rスティックのスプライト
	std::unique_ptr<Sprite>RStickSprite;	//コントローラーRスティック
	std::unique_ptr<Sprite>RStickSprite2;	//コントローラーRスティック 説明文
	XMFLOAT2 RStickSpritePos = { 58.0f,174.0f };	//チュートリアシーンの座標 左上の座標
	XMFLOAT2 RStickSpritePos2 = { 194.0f,614.0f };	//チュートリアルシーン 説明分の座標

	//タイトルシーン
	//タイトルのスプライト
	std::unique_ptr<Sprite>title1Sprite;	
	XMFLOAT2 title1Pos = { 0.0f,-150.0f };
	XMFLOAT2 title1Scale = { 1280.0f, 480.0f };
	//タイトルシーン PUSH
	std::unique_ptr<Sprite>title2Sprite;
	XMFLOAT2 title2Pos = { 500.0f, 500.0f };
	XMFLOAT2 title2Scale = { 190.0f, 52.0f };
	//タイトルシーン コントローラー推奨
	std::unique_ptr<Sprite>title3Sprite;
	XMFLOAT2 title3Pos = { 928.0f, 656.0f };
	XMFLOAT2 title3Scale = { 347.0f, 56.0f };
	//タイトルシーン ボタンのアニメーション用タイマー
	int buttonTimer = 0;
	int buttonChangeTime = 90;
	int buttonMaxTime = buttonChangeTime * 2;
	//タイトルシーン コントローラー推奨スプライト点滅用の
	int titleSprite3Timer = 1;
	int titleSprite3Add = 1;
	int titleSprite3MaxTime = titleSprite3Add * 45;
	//タイトルシーン シーン遷移用タイマー
	int titleTimer;
	//タイトルシーン シーン遷移の時間
	int titleTime;

	//チュートリアルシーン
	//チュートリアルシーン 説明を出す枠
	std::unique_ptr<Sprite>tutorial1Sprite;
	XMFLOAT2 tutorial1Pos = { 128.0f, 520.0f };
	XMFLOAT2 tutorial1Scale = { 512.0f * 2, 130.0f * 1.5 };
	//チュートリアルシーン まずは「」で移動、「」でカメラ移動してみよう
	std::unique_ptr<Sprite>tutorial2Sprite;
	XMFLOAT2 tutorial2Pos = { 198.0f, 570.0f };
	XMFLOAT2 tutorial2Scale = { 1246.0f * 0.5, 197.0f * 0.5 };
	//チュートリアルシーン いい感じ！
	std::unique_ptr<Sprite>tutorial3Sprite;	
	XMFLOAT2 tutorial3Pos = { 198.0f, 570.0f };
	XMFLOAT2 tutorial3Scale = { 104.0f * 2.0f, 42.0f * 2.0f };
	//チュートリアルシーン 次は「」で攻撃してみよう
	std::unique_ptr<Sprite>tutorial4Sprite;	
	XMFLOAT2 tutorial4Pos = { 198.0f, 570.0f };
	XMFLOAT2 tutorial4Scale = { 523.0f * 1.5f, 41.0f * 1.5f };
	//チュートリアルシーン 次は「」を押してみよう
	std::unique_ptr<Sprite>tutorial6Sprite;
	XMFLOAT2 tutorial6Pos = { 198.0f, 570.0f };
	XMFLOAT2 tutorial6Scale = { 791.0f * 0.8f, 101.0f * 0.8f };
	//チュートリアルシーン 属性(エレメント)が電気に変換できた
	std::unique_ptr<Sprite>tutorial7Sprite;
	XMFLOAT2 tutorial7Pos = { 198.0f, 570.0f };
	XMFLOAT2 tutorial7Scale = { 562.0f, 45.0f };
	//チュートリアルシーン 試しにこっちの属性でも攻撃してみよう！
	std::unique_ptr<Sprite>tutorial8Sprite;
	XMFLOAT2 tutorial8Pos = { 198.0f, 570.0f };
	XMFLOAT2 tutorial8Scale = { 791.0f, 101.0f };
	//チュートリアルシーン ステージの真ん中に突然敵が現れた！倒してみよう
	std::unique_ptr<Sprite>tutorial10Sprite;
	XMFLOAT2 tutorial10Pos = { 198.0f, 570.0f };
	XMFLOAT2 tutorial10Scale = { 791.0f, 101.0f };
	//チュートリアルシーン 倒した！いい感じ
	std::unique_ptr<Sprite>tutorial11Sprite;
	XMFLOAT2 tutorial11Pos = { 198.0f, 570.0f };
	XMFLOAT2 tutorial11Scale = { 791.0f, 101.0f };
	//チュートリアルシーン チュートリアルスキップ
	std::unique_ptr<Sprite>tutorial12Sprite;
	XMFLOAT2 tutorial12Pos1 = { 140.0f, 0.0f };	//コントローラー接続時の座標
	XMFLOAT2 tutorial12Pos2 = { 80.0f, 0.0f };	//コントローラー未接続時の座標
	XMFLOAT2 tutorial12Scale = { 958.0f * 0.4f, 78.0f * 0.4f };
	//チュートリアルシーン チェックマーク1
	std::unique_ptr<Sprite>checkSprite1;
	XMFLOAT2 checkSprite1Pos = { 24.0f,116.0f };
	XMFLOAT2 checkSpriteScale = { 32.0f,32.0f };
	//チュートリアルシーン チェックマーク2
	std::unique_ptr<Sprite>checkSprite2;
	XMFLOAT2 checkSprite2Pos = { 24.0f,190.0f };
	//チュートリアルシーン チェックマークの枠1
	std::unique_ptr<Sprite>checkFrameSprite1;
	XMFLOAT2 checkFrameSprite1Pos = { 24.0f,116.0f };
	XMFLOAT2 checkFrameSpriteScale = { 32.0f,32.0f };
	//チュートリアルシーン チェックマークの枠2
	std::unique_ptr<Sprite>checkFrameSprite2;
	XMFLOAT2 checkFrameSprite2Pos = { 24.0f,190.0f };
	//チュートリアルシーン ゲージの枠1
	std::unique_ptr<Sprite>tutorialFrameSprite1;
	XMFLOAT2 tutorialFrameSprite1Pos = { 140.0f,124.0f };
	XMFLOAT2 tutorialFrameSpriteScale = { 128.0f,16.0f };
	//チュートリアルシーン ゲージの枠2
	std::unique_ptr<Sprite>tutorialFrameSprite2;
	XMFLOAT2 tutorialFrameSprite2Pos = { 140.0f,198.0f };
	//チュートリアルシーン ゲージ1
	std::unique_ptr<Sprite>gaugeSprite1;
	XMFLOAT2 gaugeSprite1Pos = { 140.0f,124.0f };
	XMFLOAT2 gaugeSpriteScale = { 128.0f,16.0f };
	//チュートリアルシーン ゲージ2
	std::unique_ptr<Sprite>gaugeSprite2;
	XMFLOAT2 gaugeSprite2Pos = { 140.0f,198.0f };
	//チュートリアルシーンのフラグ
	int tutorialFlag = 0;
	//チュートリアルシーン Lスティックのタイマー
	int LStickTimer = 0;
	int LStickTime = 0;
	//チュートリアルシーン Rスティックのタイマー
	int RStickTimer = 0;
	int RStickTime = 0;
	//チュートリアルシーン 攻撃チュートリアルのタイマー
	int attackTimer = 0;
	int attackTime = 0;
	//チュートリアルシーン 攻撃チュートリアルのタイマー
	int attackTimer2 = 0;
	int attackTime2 = 0;
	//チュートリアルシーン 攻撃チュートリアルのタイマー
	int iikannjiTimer = 0;
	int iikannjiTime = 0;
	//チュートリアルシーン 敵が登場するまでのタイマー
	int tutorial12Timer = 0;
	int tutorial12Time = 0;
	//チュートリアルシーン 黒幕のタイマー
	int tutorial13Timer = 0;
	int tutorial13MaxTime = 0;

	//ゲームシーン
	//ゲームシーン 属性変化UI共通の座標 スケール
	XMFLOAT2 changeElementSpritePos = { 1200.0f,50.0f };
	XMFLOAT2 changeElementspriteScale = { 64.0f,64.0f };
	//ゲームシーン 属性変化のUI 電気
	std::unique_ptr<Sprite>changeElementSprite1;
	//ゲームシーン 属性変化のUI 炎
	std::unique_ptr<Sprite>changeElementSprite2;
	//ゲームシーン 属性変化のUI リサイクルマークみたいなやつ
	std::unique_ptr<Sprite>changeElementSprite3;
	//ゲームシーン 属性変化のUI ×マーク
	std::unique_ptr<Sprite>changeElementSprite4;
	//ゲームシーン　攻撃UI共通の座標 スケール 
	XMFLOAT2 attackSpritePos = { 1200.0f,124.0f };
	XMFLOAT2 attackSpriteScale = { 64.0f,64.0f };
	//ゲームシーン 攻撃UI 電気
	std::unique_ptr<Sprite>attackElecSprite;
	//ゲームシーン 攻撃UI 炎
	std::unique_ptr<Sprite>attackFireSprite;

	//敵のHP
	//HPバーの枠
	std::unique_ptr<Sprite>enemyHpBar1;
	//HPバー
	std::unique_ptr<Sprite>enemyHpBar2;
	//現在のHPのとこにつけるやつ
	std::unique_ptr<Sprite>enemyHpBar3;
	//BOSS HPのテキスト
	std::unique_ptr<Sprite>enemyHpBar4;
	//HPバーオレンジ
	std::unique_ptr<Sprite>enemyHpBar5;
	//HPバー1
	XMFLOAT2 enemyHpBar1Pos = { 320.0f,-15.0f };
	XMFLOAT2 enemyHpBar1Scale = { 640.0f,96.0f };
	//HPバー2
	XMFLOAT2 enemyHpBar2Pos = { 349.0f,26.0f };
	XMFLOAT2 enemyHpBar2OriginalScale = { 605.0f,15.0f };
	XMFLOAT2 enemyHpBar2Scale = enemyHpBar2OriginalScale;
	//HPバー3
	XMFLOAT2 enemyHpBar3OriginalPos = { 938.0f,25.0f };
	XMFLOAT2 enemyHpBar3Pos = enemyHpBar3OriginalPos;
	XMFLOAT2 enemyHpBar3Scale = { 16.0f,16.0f };
	//Hpバー4
	XMFLOAT2 enemyHpBar4Pos = { 230.0f,25.0f };
	XMFLOAT2 enemyHpBar4Scale = { 96.0f,16.0f };
	//HPバー5
	XMFLOAT2 enemyHpBar5Pos = { 349.0f,26.0f };
	XMFLOAT2 enemyHpBar5OriginalScale = { 605.0f,15.0f };
	XMFLOAT2 enemyHpBar5Scale = enemyHpBar2OriginalScale;

	//プレイヤーのHP
	//緑のHP
	std::vector<Sprite*>hpSprite1;
	//赤いHP
	std::unique_ptr<Sprite>hpSprite2;	
	//HPの枠
	std::unique_ptr<Sprite>hpSprite3;	
	//緑のHPの数
	int hpSprite1Num = 5;
	//HP用スプライトの大きさ、座標
	XMFLOAT2 hpSpritePos = { 490.0f,660.0f };
	XMFLOAT2 hpSprite1Scale = { 32.0f * 1.5f,16.0f * 1.5f };
	XMFLOAT2 hpSprite2Scale = { 32.0f * 1.5f,16.0f * 1.5f };
	XMFLOAT2 hpSprite3Scale = { 196.0f * 1.5,28.0f * 1.5 };
	//HP枠の大きさ
	float hpFrameScale1 = 10.0f * 1.5f;	//外枠 左右
	float hpFrameScale2 = 4.0f * 1.5f;	//内側の枠
	float hpFrameScale3 = 6.0f * 1.5f;	//外枠 上下

	//デバッグ
	float debugNum1[2] = { 0.0f,0.0f };
	float debugNum2[1] = { 1.0f};
	float debugNum3[2] = { 0.0f,0.0f };
	float debugNum4[1] = { 1.0f};
	float debugNum5[2] = { 0.0f,0.0f };
	float debugNum6[1] = { 1.0f};
};
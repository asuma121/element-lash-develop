/**
 * @file DXInput.h
 * @brief ゲームコントローラの入力を管理
 * @author Asuma Syota
 * @date 2023/4
 */

#pragma once

#include <dwrite.h>
#include <wchar.h>
#include <wrl/client.h>
#include <random>
#include <xinput.h>
#include "WinApp.h"
#include "Input.h"
#include "DXInput.h"

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")
#pragma comment (lib, "xinput.lib")

#define MaxCountrollers 4
#define MaxVibration 65535

//クラスの前方前言
class KeyState;
class KeyManager
{
public:
    enum Pad
    {
        PAD_LEFT,
        PAD_RIGHT,
        PAD_UP,
        PAD_DOWN,
        PAD_A,
        PAD_B,
        PAD_X,
        PAD_Y,
        PAD_LEFT_SHOULDER,
        PAD_RIGHT_SHOULDER,
        PAD_START,
        PAD_BACK,
    };

    enum Stick
    {
        RStickX,
        RStickY,
        LStickX,
        LStickY,
        RStick,
        LStick,
    };

public:// メンバ関数

    //インストラクタ デストラクタ
    KeyManager();
    ~KeyManager();

    /// <summary>
    ///更新
    /// </summary>
    void Update();

    /// <summary>
    ///更新
    /// </summary>
    void UpdateState();

    /// <summary>
    ///ボタン取得
    /// </summary>  
    bool PushKey(const Pad& pad);
    
    /// <summary>
    ///トリガーボタン取得
    /// </summary>  
    bool TriggerKey(const Pad& pad);

    /// <summary>
    ///スティック取得
    /// </summary>
    float GetStick(const Stick& stick);

    /// <summary>
    ///スティックを真上から見た際の角度取得(ラジアン)
    /// </summary>
    float GetStickRot(const Stick& stick);

    /// </summary>
    ///コントローラーがつながっているか
    /// </summary>
    bool GetConnectFlag();
    bool GetOldConnectFlag();

    /// <summary>
    ///ステートチェンジ
    /// </summary>
    void ChangeState(KeyState* newState);

private:// メンバ変数

    //ステート
    KeyState* keyState;
};

class KeyState
{
public: // メンバ関数

    //ボタン取得
    virtual bool PushKey(const KeyManager::Pad& pad) = 0;

    //トリガーボタン取得
    virtual bool TriggerKey(const KeyManager::Pad& pad) = 0;

    //スティック取得
    virtual float GetStick(const KeyManager::Stick& stick) = 0;

    //スティックを真上から見た際の角度取得(ラジアン)
    virtual float GetStickRot(const KeyManager::Stick& stick) = 0;

    //コントローラーがつながっているか
    bool GetConnectFlag();
    bool GetOldConnectFlag();

    //更新
    void Update();
    //更新 ステート
    void UpdateState(KeyManager* keyManager);  //更新中

    static void SetDXInput(DXInput* dxInput) { KeyState::dxInput = dxInput; };
    static void SetInput(Input* input) { KeyState::input = input; };

protected:	//メンバ変数

    //キーボード
    static Input* input;
    //コントローラー
    static DXInput* dxInput;
};
//キーボードによる入力
class KeyInput : public KeyState
{
public:

    //ボタン取得
    bool PushKey(const KeyManager::Pad& pad);

    //トリガーボタン取得
    bool TriggerKey(const KeyManager::Pad& pad);

    //スティック取得
    float GetStick(const KeyManager::Stick& stick);

    //スティックを真上から見た際の角度取得(ラジアン)
    float GetStickRot(const KeyManager::Stick& stick);
};
//コントローラーによる入力
class KeyDXInput : public KeyState
{
public:

    //ボタン取得
    bool PushKey(const KeyManager::Pad& pad);

    //トリガーボタン取得
    bool TriggerKey(const KeyManager::Pad& pad);

    //スティック取得
    float GetStick(const KeyManager::Stick& stick);

    //スティックを真上から見た際の角度取得(ラジアン)
    float GetStickRot(const KeyManager::Stick& stick);
};
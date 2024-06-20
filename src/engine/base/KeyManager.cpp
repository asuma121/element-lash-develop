/**
 * @file KeyManager.cpp
 * @brief ゲームで使うコントローラ、キーボードの入力を管理
 * @author Asuma Syota
 * @date 2023/4
 */

#include "KeyManager.h"
#include "mathOriginal.h"

Input* KeyState::input = nullptr;
DXInput* KeyState::dxInput = nullptr;

KeyManager::KeyManager()
{
    keyState = new KeyInput;
    keyState->UpdateState(this);
}

KeyManager::~KeyManager()
{
    delete keyState;
}

void KeyManager::Update()
{
    keyState->Update();
}

void KeyManager::UpdateState()
{
    keyState->UpdateState(this);
}

bool KeyManager::PushKeyboard(BYTE keyNumber)
{
    return keyState->PushKeyboard(keyNumber);
}

bool KeyManager::PushKey(const Pad& pad)
{
    return keyState->PushKey(pad);
}

bool KeyManager::TriggerKey(const Pad& pad)
{
    return keyState->TriggerKey(pad);
}

float KeyManager::GetStick(const Stick& stick)
{
    return keyState->GetStick(stick);
}

float KeyManager::GetStickRot(const Stick& stick)
{
    return keyState->GetStickRot(stick);
}

bool KeyManager::GetConnectFlag()
{
    return keyState->GetConnectFlag();
}

bool KeyManager::GetOldConnectFlag()
{
    return keyState->GetOldConnectFlag();
}

void KeyManager::ChangeState(KeyState* newState)
{
    delete keyState;
    keyState = newState;
}

bool KeyState::PushKeyboard(BYTE keyNumber)
{
    return input->PushKey(keyNumber);
}

bool KeyState::GetConnectFlag()
{
    return dxInput->GetConnectFlag();
}

bool KeyState::GetOldConnectFlag()
{
    return dxInput->GetOldConnectFlag();
}

void KeyState::Update()
{
    //キーボード更新
    input->Update();

    //コントローラ更新
    dxInput->Update();
}

void KeyState::UpdateState(KeyManager* keyManager)
{
    if (dxInput->GetConnectFlag() == true)
    {
        keyManager->ChangeState(new KeyDXInput());
    }
    else
    {
        keyManager->ChangeState(new KeyInput());
    }
}

bool KeyInput::PushKey(const KeyManager::Pad& pad)
{
    if (pad == KeyManager::PAD_A)return input->PushKey(DIK_SPACE);
    if (pad == KeyManager::PAD_LEFT_SHOULDER)return input->PushKey(DIK_LSHIFT);
    if (pad == KeyManager::PAD_RIGHT_SHOULDER)return input->PushKey(DIK_SPACE);
    if (pad == KeyManager::PAD_START)return input->PushKey(DIK_ESCAPE);
    return false;
}

bool KeyInput::TriggerKey(const KeyManager::Pad& pad)
{
    if (pad == KeyManager::PAD_A)return input->TriggerKey(DIK_SPACE);
    if (pad == KeyManager::PAD_X)return input->TriggerKey(DIK_SPACE);
    if (pad == KeyManager::PAD_LEFT_SHOULDER)return input->TriggerKey(DIK_LSHIFT);
    if (pad == KeyManager::PAD_RIGHT_SHOULDER)return input->TriggerKey(DIK_SPACE);
    if (pad == KeyManager::PAD_START)return input->TriggerKey(DIK_ESCAPE);
    return false;
}

float KeyInput::GetStick(const KeyManager::Stick& stick)
{
    //Arowキー X軸
    if (stick == KeyManager::RStickX)
    {
        return (float)input->PushKey(DIK_RIGHT) - (float)input->PushKey(DIK_LEFT);
    }
    //Arowキー X軸
    if (stick == KeyManager::RStickY)
    {
        return (float)input->PushKey(DIK_UP) - (float)input->PushKey(DIK_DOWN);
    }
    //ADSWキー X軸
    if (stick == KeyManager::LStickX)
    {
        return (float)input->PushKey(DIK_D) - (float)input->PushKey(DIK_A);
    }
    //ADSWキー X軸
    if (stick == KeyManager::LStickY)
    {
        return (float)input->PushKey(DIK_W) - (float)input->PushKey(DIK_S);
    }
    //Arowキー
    if (stick == KeyManager::RStick)
    {
        return length(input->PushKey(DIK_RIGHT) - input->PushKey(DIK_LEFT),
            input->PushKey(DIK_UP) - input->PushKey(DIK_DOWN));
    }
    //ADSWキー
    if (stick == KeyManager::LStick)
    {
        return length(input->PushKey(DIK_D) - input->PushKey(DIK_A),
            input->PushKey(DIK_W) - input->PushKey(DIK_S));
    }
    return 0.0f;
}

float KeyInput::GetStickRot(const KeyManager::Stick& stick)
{
    float stickX = 0.0f;
    float stickY = 0.0f;
    //右スティックの角度を参照する場合
    if (stick == KeyManager::RStick || stick == KeyManager::RStickX || stick == KeyManager::RStickY)
    {
        //入力がない場合0を返す
        if (input->PushKey(DIK_RIGHT) - input->PushKey(DIK_LEFT) == 0 &&
            input->PushKey(DIK_UP) - input->PushKey(DIK_DOWN) == 0)
        {
            return 0.0f;
        }
        //正規化したYの値を代入
        stickY = normalize((float)input->PushKey(DIK_RIGHT) - (float)input->PushKey(DIK_LEFT),
            (float)input->PushKey(DIK_UP) - (float)input->PushKey(DIK_DOWN)).y;
        //ステックのYの値を代入
        stickX = (float)input->PushKey(DIK_UP) - (float)input->PushKey(DIK_DOWN);
    }
    //左スティックの角度を参考にする場合
    else if (stick == KeyManager::LStick || stick == KeyManager::LStickX || stick == KeyManager::LStickY)
    {
        //入力がない場合0を返す
        if (input->PushKey(DIK_D) - input->PushKey(DIK_A) == 0 &&
            input->PushKey(DIK_W) - input->PushKey(DIK_S) == 0)
        {
            return 0.0f;
        }
        //正規化したYの値を代入
        stickY = normalize((float)input->PushKey(DIK_D) - (float)input->PushKey(DIK_A),
            (float)input->PushKey(DIK_W) - (float)input->PushKey(DIK_S)).y;
        //ステックのYの値を代入
        stickX = (float)input->PushKey(DIK_D) - (float)input->PushKey(DIK_A);
    }
    //0~180の場合
    if (stickX >= 0.0f)
    {
        //-1する
        stickY -= 1.0f;
        //-を外す
        stickY *= -1.0f;
        //度数法に変換
        stickY *= 90.0f;
        //ラジアンに変換
        stickY *= (float(PI) / 180.0f);
    }
    //180~360の場合
    else
    {
        //+1する
        stickY += 1.0f;
        //度数法に変換
        stickY *= 90.0f;
        //180度追加
        stickY += 180.0f;
        //ラジアンに変換
        stickY *= (float(PI) / 180.0f);
    }
    return stickY;
}

bool KeyDXInput::PushKey(const KeyManager::Pad& pad)
{
    if (pad == KeyManager::PAD_A)return dxInput->PushKey(DXInput::PAD_A);
    if (pad == KeyManager::PAD_X)return dxInput->PushKey(DXInput::PAD_X);
    if (pad == KeyManager::PAD_LEFT_SHOULDER)return dxInput->PushKey(DXInput::PAD_LEFT_SHOULDER);
    if (pad == KeyManager::PAD_RIGHT_SHOULDER)return dxInput->PushKey(DXInput::PAD_RIGHT_SHOULDER);
    if (pad == KeyManager::PAD_START)return dxInput->PushKey(DXInput::PAD_START);
    return false;
}

bool KeyDXInput::TriggerKey(const KeyManager::Pad& pad)
{
    if (pad == KeyManager::PAD_A)return dxInput->TriggerKey(DXInput::PAD_A);
    if (pad == KeyManager::PAD_X)return dxInput->TriggerKey(DXInput::PAD_X);
    if (pad == KeyManager::PAD_LEFT_SHOULDER)return dxInput->TriggerKey(DXInput::PAD_LEFT_SHOULDER);
    if (pad == KeyManager::PAD_RIGHT_SHOULDER)return dxInput->TriggerKey(DXInput::PAD_RIGHT_SHOULDER);
    if (pad == KeyManager::PAD_START)return dxInput->TriggerKey(DXInput::PAD_START);
    return false;
}

float KeyDXInput::GetStick(const KeyManager::Stick& stick)
{
    if (stick == KeyManager::RStickX)return dxInput->GetStick(DXInput::RStickX);
    if (stick == KeyManager::RStickY)return dxInput->GetStick(DXInput::RStickY);
    if (stick == KeyManager::LStickX)return dxInput->GetStick(DXInput::LStickX);
    if (stick == KeyManager::LStickY)return dxInput->GetStick(DXInput::LStickY);
    if (stick == KeyManager::RStick)return dxInput->GetStick(DXInput::RStick);
    if (stick == KeyManager::LStick)return dxInput->GetStick(DXInput::LStick);
    return 0.0f;
}

float KeyDXInput::GetStickRot(const KeyManager::Stick& stick)
{
    if (stick == KeyManager::RStickX)return dxInput->GetStickRot(DXInput::RStickX);
    if (stick == KeyManager::RStickY)return dxInput->GetStickRot(DXInput::RStickY);
    if (stick == KeyManager::LStickX)return dxInput->GetStickRot(DXInput::LStickX);
    if (stick == KeyManager::LStickY)return dxInput->GetStickRot(DXInput::LStickY);
    if (stick == KeyManager::RStick)return dxInput->GetStickRot(DXInput::RStick);
    if (stick == KeyManager::LStick)return dxInput->GetStickRot(DXInput::LStick);
    return 0.0f;
}
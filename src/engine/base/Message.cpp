/**
 * @file Message.cpp
 * @brief ゲームの終了処理やデバッグ時に使う
 * @author Asuma Syota
 * @date 2023/4
 */

#include "Message.h"

Message* Message::GetInstance()
{
	static Message instance;
	return &instance;
}

bool Message::Update()
{
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) // メッセージがある？
	{
		TranslateMessage(&msg); // キー入力メッセージの処理
		DispatchMessage(&msg);  // ウィンドウプロシージャにメッセージを送る
	}

	if (msg.message == WM_QUIT) // 終了メッセージが来たらループを抜ける
	{
		return true;
	}
	return false;
}
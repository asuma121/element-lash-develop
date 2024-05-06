/**
 * @file Message.h
 * @brief ゲームの終了処理やデバッグ時に使う
 * @author Asuma Syota
 * @date 2023/4
 */

#pragma once
#include <d3d12.h>

class Message
{
public:

	/// <summary>
	///インスタンス取得
	/// </summary>
	static Message* GetInstance();

	/// <summary>
	///Xボタンで終了メッセ時が来たらゲームループを抜ける 
	/// </summary>
	bool Update();

private:
	MSG msg{};
};


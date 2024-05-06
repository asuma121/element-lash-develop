#include "WinApp.h"
#include "Message.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "DXInput.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//ウィンドウ生成
	WinApp* winApp = nullptr;
	winApp = WinApp::GetInstance();
	winApp->CreateWindow_(L"エレメントラッシュ");
	return 0;

	//メッセージ
	Message* message;
	message = MyEngine::Message::GetInstance();

	//DirectX初期化処理
	DirectXCommon* dxCommon = nullptr;
	dxCommon = DirectXCommon::GetInstance();
	dxCommon->Initialize(winApp);

	//キーボード
	Input* input = nullptr;
	input = Input::GetInstance();
	input->Initialize(winApp);

	//コントローラー
	DXInput* dxInput = nullptr;
	dxInput = DXInput::GetInstance();

}
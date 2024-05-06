#include "WinApp.h"
#include "Message.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "DXInput.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//�E�B���h�E����
	WinApp* winApp = nullptr;
	winApp = WinApp::GetInstance();
	winApp->CreateWindow_(L"�G�������g���b�V��");
	return 0;

	//���b�Z�[�W
	Message* message;
	message = MyEngine::Message::GetInstance();

	//DirectX����������
	DirectXCommon* dxCommon = nullptr;
	dxCommon = DirectXCommon::GetInstance();
	dxCommon->Initialize(winApp);

	//�L�[�{�[�h
	Input* input = nullptr;
	input = Input::GetInstance();
	input->Initialize(winApp);

	//�R���g���[���[
	DXInput* dxInput = nullptr;
	dxInput = DXInput::GetInstance();

}
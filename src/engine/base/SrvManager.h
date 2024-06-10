#pragma once
#include "DirectXCommon.h"

class SrvManager {

public:	//ƒƒ“ƒoŠÖ”

	void SetDxCommon(DirectXCommon* directXCommon) { this->directXCommon = directXCommon; }

private:
	DirectXCommon* directXCommon = nullptr;
};
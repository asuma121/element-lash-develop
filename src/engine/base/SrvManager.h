#pragma once
#include "DirectXCommon.h"

class SrvManager {

public:	//メンバ関数

	void SetDxCommon(DirectXCommon* directXCommon) { this->directXCommon = directXCommon; }

private:
	DirectXCommon* directXCommon = nullptr;
};
#pragma once
#include "DirectXCommon.h"

class SrvManager {

public:	//�����o�֐�

	void SetDxCommon(DirectXCommon* directXCommon) { this->directXCommon = directXCommon; }

private:
	DirectXCommon* directXCommon = nullptr;
};